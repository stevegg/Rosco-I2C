#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

/**
 * Fuse settings for ATMega 1284 for 16mhz external oscillator
 * Low Byte: 0xFF (blank all)
 * High Byte: 0xDE (Check SPIEN and BOOTRST)
 * Extended: 0xFD (Check BODLEVEL1)
 * 
 * Fuse settings for ATMega 32a for 16mhz external oscillator
 * Low Byte: 0xFF (blank all)
 * High Byte: 0xD8 (Check SPIEN, BOOTSZ1, BOOTSZ0, BOOTRST) 
 * 
 * Port Manipulation
 *    DDR 1 = OUTPUT, 0 = INPUT
 *    Use PIN to read
 *    Use PORT to write
 * 
 */

Adafruit_7segment matrix = Adafruit_7segment();

volatile boolean gvProcessBus = false;
volatile byte gvAddress = 0x00;
volatile byte gvData = 0x00;
volatile boolean gvReading = false;

#define SIGNAL_PORT     PORTD
#define I2C_SEL_PIN     10
#define I2CENABLE_PIN   PIND2
#define AS_PIN          PIND3
#define DTACK_PIN       PIND4
#define RW_PIN          PIND5
#define LDS_PIN         PIND6

#define DATA_PORT       PORTB
#define DATA_PIN        PINB
#define ADDRESS_PORT    PORTA
#define ADDRESS_PIN     PINA

// Called whenever the I2C_SEL pin goes LOW
void processBusInterruptHandler() {
  if (!gvProcessBus) {
    gvAddress = ADDRESS_PIN;
    gvData = DATA_PIN;
    gvReading = (SIGNAL_PORT & (1<<RW_PIN)) == 1;
    // Now assert I2C_DTACK
    // SIGNAL_PORT &= ~(1<<DTACK_PIN);
    gvProcessBus = true;
    // Set DTACK back to high
    // SIGNAL_PORT |= (1<<DTACK_PIN);
  }
}

void setup() {

  Serial.begin(9600);

  // Setup Address Port as INPUT
  DDRA = 0x00;
  // Setup Data Port initially as INPUT
  DDRB = 0x00;

  // DTACK_PIN is an OUTPUT
  DDRD |= (1<<DTACK_PIN);
  // Set it's state to HI
  SIGNAL_PORT |= (1<<DTACK_PIN);

  // I2CENABLE is an INPUT
  DDRD &= ~(1<<I2CENABLE_PIN);

  // AS is an INPUT
  DDRD &= ~(1<<AS_PIN);

  // RW pin is an INPUT
  DDRD &= ~(1<<RW_PIN);

  // LDS pin is an INPUT
  DDRD &= ~(1<<LDS_PIN);

  matrix.begin(0x70);
  // Show Rdy on Display
  matrix.print("Rdy");
  matrix.writeDisplay();

  // Setup an interrupt on the falling edge of I2CENABLE pin
  attachInterrupt(digitalPinToInterrupt(I2C_SEL_PIN), processBusInterruptHandler, FALLING);

  Serial.println("Initialization complete.");
}

void loop() {

  if ( gvProcessBus ) {
    Serial.println("processBus...");

    char buffer[128];


    sprintf(buffer, "I2C: %c %02X : %02X", (gvReading)?'R':'W', gvAddress, gvData);
    Serial.println(buffer);

    if ( !gvReading ) {
      // Write data to the 7 segment LED
      matrix.print(gvData, HEX);
      matrix.writeDisplay();
    }

    gvProcessBus = false;    
  }
}