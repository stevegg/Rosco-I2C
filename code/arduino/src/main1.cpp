// #include <Arduino.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_LEDBackpack.h>

// /**
//  * Notes:
//  * 
//  * Port Manipulation
//  *    DDR 1 = OUTPUT, 0 = INPUT
//  *    Use PIN to read
//  *    Use PORT to write
//  */

// Adafruit_7segment matrix = Adafruit_7segment();

// #define DTACK_ARDUINO_PIN 15
// #define DTACK_DDR DDRD
// #define DTACK_PIN PIND7
// #define DTACK_PORT PORTD

// #define I2CENABLE_ARDUINO_PIN 11
// #define I2CENABLE_DDR DDRD
// #define I2CENABLE_PIN PIND3
// #define I2CENABLE_PINS PIND
// #define I2CENABLE_PORT PORTD
// #define I2CENABLE_INTERRUPT PCINT27

// #define AS_ARDUINO_PIN  10
// #define AS_DDR          DDRD
// #define AS_PIN          PIND2
// #define AS_PORT         PORTD

// #define RW_ARDUINO_PIN  13
// #define RW_DDR          DDRD
// #define RW_PIN          PIND5
// #define RW_PORT         PORTD

// #define LDS_ARDUINO_PIN 14
// #define LDS_DDR         DDRD
// #define LDS_PIN         PIND6
// #define LDS_PORT        PORTD

// #define DATA_PORT       PORTA
// #define DATA_DDR        DDRA
// #define DATA_PIN        PINA

// #define ADDRESS_PORT    PORTB
// #define ADDRESS_PIN     PINB
// #define ADDRESS_DDR     DDRB

// // ISR (INT1_vect) {
// //   // Assert DTACK signal LOW
// //   DTACK_PORT &= ~(1<<DTACK_PIN);
// //   DTACK_DDR |= (1<<DTACK_PIN);
// //   // Read data, address and RW ports/pins
// //   gvData = DATA_PIN;
// //   gvAddress = ADDRESS_PIN;
// //   DTACK_DDR &= ~(1<<DTACK_PIN);
// //   DTACK_PORT |= (1<<DTACK_PIN);
// //   gvRW = (RW_PORT & (1<<RW_PIN));

// //   // Flag to indicate that the bus needs processing
// //   gvProcessBus = true;
// // }

// void setup() {
//   // Setup Address Port as INPUT
//   ADDRESS_DDR = 0x00;
//   // Setup Data Port initially as INPUT
//   DATA_DDR = 0x00;
//   // TriState DTACK using DDR as INPUT to turn it off
//   DTACK_DDR &= ~(1<<DTACK_PIN);
//   // Set hi
//   DTACK_PORT |= (1<<DTACK_PIN);

//   // I2CENABLE is an INPUT
//   I2CENABLE_DDR &= ~(1<<I2CENABLE_PIN);
//   // Pullup
//   PORTD |= (1<<I2CENABLE_PIN);

//   // AS is an INPUT
//   AS_DDR &= ~(1<<AS_PIN);

//   // RW pin is an INPUT
//   RW_DDR &= ~(1<<RW_PIN);

//   // LDS pin is an INPUT
//   LDS_DDR &= ~(1<<LDS_PIN);

//   // cli();
//   // EICRA &= ~(bit(ISC00) | bit (ISC01));  // clear existing flags
//   // EICRA |= bit (ISC01);    // set wanted flags (falling level interrupt)
//   // EIMSK |= bit (INT1);     // enable it
//   // Disable timers
//   TIMSK0 &= ~_BV(TOIE0);
//   // TCCR1A &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
//   // TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
//   // sei();
// }

// void loop() {

//   // byte address = 0x00;
//   // byte data = 0x00;
//   // boolean RW = false;

//   if ( !(I2CENABLE_PINS & (1<<I2CENABLE_PIN) ) ) {
//     DTACK_PORT &= ~(1<<DTACK_PIN);
//     DTACK_DDR |= (1<<DTACK_PIN);
//     // Read data, address and RW ports/pins
//     // data = DATA_PIN;
//     // address = ADDRESS_PIN;
//     // RW = (RW_PORT & (1<<RW_PIN));
//     DTACK_DDR &= ~(1<<DTACK_PIN);
//     DTACK_PORT |= (1<<DTACK_PIN);
//   }

//   // // Did an interrupt get triggered?
//   // if ( gvProcessBus ) {
//   //   // Serial.println("processBus...");

//   //   // char buffer[128];

//   //   // sprintf(buffer, "I2C: %c %02X : %02X", (gvRW)?'R':'W', gvAddress, gvData);
//   //   // Serial.println(buffer);

//   //   // if gvRW is false then we've got a write from the processor
//   //   if ( !gvRW ) {
//   //     // Write data to the 7 segment LED
//   //     matrix.print(gvData, HEX);
//   //     matrix.writeDisplay();
//   //   }

//   //   // Finished
//   //   gvProcessBus = false;    
//   // }
// }