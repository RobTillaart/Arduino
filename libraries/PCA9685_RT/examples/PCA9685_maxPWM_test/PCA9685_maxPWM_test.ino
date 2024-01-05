//
//    FILE: PCA9685_maxPWM_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9685 library
//     URL: https://github.com/RobTillaart/PCA9685_RT
//
//  sets one channel to max PWM 0..4095
//  and connect the output to an interrupt pin 2
//  to see the frequency of the PWM


#include "PCA9685.h"


PCA9685 PCA(0x40);

const uint8_t IRQ_PIN = 2;
volatile uint16_t count = 0;
uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9685_LIB_VERSION: ");
  Serial.println(PCA9685_LIB_VERSION);
  Serial.println();

  Wire.begin();
  PCA.begin();

  pinMode(IRQ_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQ_PIN), irq, RISING);  //  CHANGE

  Serial.println(PCA.getFrequency());
  PCA.setFrequency(200);
  Serial.println(PCA.lastError());
  Serial.println(PCA.getFrequency(false));  //  do not fetch from cache.

  PCA.setPWM(15, 0, 4095);    //  gives 2 changes per interval
}


//  INTERRUPT ROUTINE TO COUNT THE PULSES
void irq()
{
  count++;
}


void loop()
{
  uint32_t now = millis();
  if (now - lastTime >= 1000)
  {
    lastTime += 1000;
    //  make a working copy of count
    noInterrupts();
    uint16_t t = count;
    count = 0;
    interrupts();

    Serial.print(t);
    Serial.print("\t");
    Serial.println(digitalRead(IRQ_PIN));
  }
}


//  -- END OF FILE --

