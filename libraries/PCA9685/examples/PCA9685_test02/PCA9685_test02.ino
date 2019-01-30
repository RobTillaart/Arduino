//
//    FILE: PCA9685_test02.ino
//  AUTHOR: Rob Tillaart
//    DATE: 24-APR-2016
// VERSION: 0.1.0
// PUPROSE: test PCA9685 library
//

#include "PCA9685.h"
#include <Wire.h>

PCA9685 ledArray(0x40);

void setup()
{
  Wire.begin();
  ledArray.begin();

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9685 LIB version: ");
  Serial.println(PCA9685_LIB_VERSION);
  Serial.println();

  testSetON();
  testPWM(0);
  testPWMMode();
  testFrequency();
  delay(2000);
  testSetOFF();

  Serial.print(millis());
  Serial.print("\t");
  Serial.println("done...");
}


void testSetON()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  for (int channel = 0; channel < 16; channel++)
  {
    ledArray.setON(channel);
    delay(100);
  }
}

void testSetOFF()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  for (int channel = 0; channel < 16; channel++)
  {
    ledArray.setOFF(channel);
    delay(100);
  }
}

void testPWM(uint8_t channel)
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  uint16_t i = 0;
  while (i < 4096)
  {
    ledArray.setPWM(channel, 0, i);
    delay(1);
    i++;
  }
  while (i > 0)
  {
    ledArray.setPWM(channel, 0, i);
    delay(1);
    i--;
  }
}

void testPWMMode()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  for (uint16_t channel = 1; channel < 16; channel++)
  {
    // every next line ~twice as much time
    ledArray.setPWM(channel, channel * 127, channel * 255);
    uint16_t a = 0, b = 0;
    ledArray.getPWM(channel, &a, &b);
    if (a != channel * 127 || b != channel * 255)
    {
      Serial.print("Error channel:\t");
      Serial.println(channel);
    }
  }
}

void testFrequency()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(__FUNCTION__);

  ledArray.setPWM(0, 1000, 3000);
  for (uint16_t freq = 24; freq < 2000; freq *= 2)
  {
    Serial.println(freq);
    ledArray.setFrequency(freq);
    delay(2000);
  }
  ledArray.setOFF(0);
}


void loop()
{
  //testPWM(0);
}
