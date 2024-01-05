//
//    FILE: PCA9685_test02.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9685 library
//     URL: https://github.com/RobTillaart/PCA9685_RT


#include "PCA9685.h"


PCA9685 ledArray(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9685_LIB_VERSION: ");
  Serial.println(PCA9685_LIB_VERSION);
  Serial.println();

  Wire.begin();
  ledArray.begin();

  testWrite1(HIGH);
  testPWM(0);
  testPWMMode();
  testFrequency();
  delay(2000);
  testWrite1(LOW);

  Serial.print(millis());
  Serial.print("\t");
  Serial.println("done...");
}


void testWrite1(uint8_t mode)
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  for (int channel = 0; channel < ledArray.channelCount(); channel++)
  {
    ledArray.write1(channel, mode);
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
  for (uint16_t channel = 1; channel < ledArray.channelCount(); channel++)
  {
    //  every next line ~twice as much time
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
  for (uint16_t freq = 12; freq < 2000; freq *= 2)
  {
    Serial.print(freq);
    ledArray.setFrequency(freq);
    //  if freq is out of range => report
    if (ledArray.getFrequency() != freq)
    {
      Serial.print("\tconstrained to : ");
      Serial.println(ledArray.getFrequency());
    }
    else
    {
      Serial.println("\tOK");
    }
    delay(2000);
  }
  ledArray.setOFF(0);
  Serial.println();
}


void loop()
{
  //  testPWM(0);
}


//  -- END OF FILE --

