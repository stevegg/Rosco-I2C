#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_7segment matrix = Adafruit_7segment();

#define DTACK_DDR DDRD
#define DTACK_PIN PIND7
#define DTACK_PORT PORTD

#define I2CENABLE_DDR DDRD
#define I2CENABLE_PIN PIND3
#define I2CENABLE_PINS PIND
#define I2CENABLE_PORT PORTD

#define RW_DDR          DDRD
#define RW_PINS         PIND
#define RW_PIN          PIND5
#define RW_PORT         PORTD

#define DATA_PORT       PORTA
#define DATA_DDR        DDRA
#define DATA_PINS       PINA

#define ADDRESS_PORT    PORTB
#define ADDRESS_PINS    PINB
#define ADDRESS_DDR     DDRB

void setup() {

  Wire.setClock(400000L);

  // Setup Address Port as INPUT
  ADDRESS_DDR = 0x00;
  // Setup Data Port initially as INPUT
  DATA_DDR = 0x00;

  // RW pin is an INPUT
  RW_DDR &= ~(1<<RW_PIN);

  // Set DTACK as INPUT so we can tristate it
  DTACK_DDR &= ~(1<<DTACK_PIN);

  // I2CENABLE is an INPUT
  I2CENABLE_DDR &= ~(1<<I2CENABLE_PIN);
  // Pullup
  PORTD |= (1<<I2CENABLE_PIN);

  // Disable timer
  TIMSK0 &= ~_BV(TOIE0);

  // Setup the 7 segment display
  matrix.begin(0x70);
  matrix.print("Rdy");
  matrix.writeDisplay();
}

void loop() {
  byte address = 0x00;
  byte data = 0x00;
  boolean RW = false;
  unsigned long count = 0;

  while (true) {
    if ( !(I2CENABLE_PINS & (1<<I2CENABLE_PIN) ) ) {
      // Read data, address and RW ports/pins
      data = DATA_PINS;
      address = ADDRESS_PINS;
      RW = (RW_PORT & (1<<RW_PIN));

      // Set as Output
      DTACK_DDR |= (1<<DTACK_PIN);
      // Assert DTACK
      DTACK_PORT &= ~(1<<DTACK_PIN);
      DTACK_PORT |= (1<<DTACK_PIN);
      // Set as Input
      DTACK_DDR &= ~(1<<DTACK_PIN);
      if ( !RW ) {
        matrix.print(data, DEC);
        matrix.writeDisplay();
      }
    }
  }
}