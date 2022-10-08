#include <Arduino.h>

#define SIGNAL_ARDUINO_PIN 23
#define SIGNAL_INDICATOR_DDR DDRC
#define SIGNAL_INDICATOR_PIN PINC7
#define SIGNAL_INDICATOR_PORT PORTC

#define DTACK_ARDUINO_PIN 15
#define DTACK_DDR DDRD
#define DTACK_PIN PIND7
#define DTACK_PORT PORTD

#define I2CENABLE_ARDUINO_PIN 22
#define I2CENABLE_DDR DDRC
#define I2CENABLE_PIN PINC6
#define I2CENABLE_PORT PORTC
#define I2CENABLE_INTERRUPT PCINT22

#define USE_LOW_LEVEL

#ifndef USE_LOW_LEVEL
void toggle(uint8_t level) {
#else
ISR(PCINT2_vect) {
#endif  
#ifndef USE_LOW_LEVEL
  digitalWrite(SIGNAL_ARDUINO_PIN, level);  
  digitalWrite(DTACK_ARDUINO_PIN, !level);
#else 
  SIGNAL_INDICATOR_PORT &= ~(1<<SIGNAL_INDICATOR_PIN);
  DTACK_PORT |= (1<<DTACK_PIN);
  delayMicroseconds(2);
  SIGNAL_INDICATOR_PORT |= (1<<SIGNAL_INDICATOR_PIN);
  DTACK_PORT &= ~(1<<DTACK_PIN);
#endif
}

void setup() {

#ifndef USE_LOW_LEVEL  
  pinMode(SIGNAL_ARDUINO_PIN, OUTPUT);
  digitalWrite(SIGNAL_ARDUINO_PIN, HIGH);
  pinMode(DTACK_ARDUINO_PIN, OUTPUT);
  digitalWrite(DTACK_ARDUINO_PIN, LOW);
  pinMode(I2CENABLE_ARDUINO_PIN, INPUT_PULLUP);
#else
  SIGNAL_INDICATOR_DDR |= (1<<SIGNAL_INDICATOR_PIN);
  SIGNAL_INDICATOR_PORT |= (1<<SIGNAL_INDICATOR_PIN);
  DTACK_DDR |= (1<<DTACK_PIN);
  DTACK_PORT &= ~(1<<DTACK_PIN);

  // Setup PIN Change interrupt
  PCICR  |= B00000100;
  PCMSK2 |= (1<<I2CENABLE_INTERRUPT);
#endif


}

void loop() {
#ifndef USE_LOW_LEVEL
  int pinValue = digitalRead(I2CENABLE_ARDUINO_PIN);
  if ( pinValue == LOW ) {
    toggle(HIGH);
  } else {
    toggle(LOW);
  }
#endif
}