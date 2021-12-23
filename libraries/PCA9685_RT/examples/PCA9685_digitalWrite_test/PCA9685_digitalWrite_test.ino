//
//    FILE: PCA9685_digitalWrite_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-11-21
// PUPROSE: test PCA9685 library
//
// sets one channel to max PWM 0..4095
// and connect the output to an interrupt pin 2
// to see the frequency of the PWM


#include "PCA9685.h"


PCA9685 PCA(0x40);

const uint8_t IRQ_PIN = 2;
volatile uint16_t count = 0;
uint32_t lastTime = 0;


void setup()
{
  Wire.begin();
  PCA.begin();

  Serial.begin(115200);
  Serial.print("PCA9685 LIB version: ");
  Serial.println(PCA9685_LIB_VERSION);
  Serial.println();

  pinMode(IRQ_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQ_PIN), irq, CHANGE);

  // PCA.setPWM(15, 0, 1000);    // works OK - reference to test irq()
  // PCA.digitalWrite(15, LOW);  // works OK
  PCA.digitalWrite(15, HIGH);    // works OK
}


// INTERRUPT ROUTINE TO COUNT THE PULSES
void irq()
{
  count++;
}


void loop()
{
  uint32_t now = millis();
  if (now - lastTime >= 1000)
  {
    lastTime = now;
    // make a copy
    noInterrupts();
    uint16_t t = count;
    count = 0;
    interrupts();

    Serial.print(t);
    Serial.print("\t");
    Serial.println(digitalRead(IRQ_PIN));
  }
}


// -- END OF FILE --

