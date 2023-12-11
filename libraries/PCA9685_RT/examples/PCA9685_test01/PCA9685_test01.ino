//
//    FILE: PCA9685_test01.ino
//  AUTHOR: Rob Tillaart
// PUPROSE: test PCA9685 library
//     URL: https://github.com/RobTillaart/PCA9685_RT

#include "Arduino.h"
#include "Wire.h"
#include "PCA9685.h"


PCA9685 ledArray(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9685 LIB version: ");
  Serial.println(PCA9685_LIB_VERSION);
  Serial.println();

  Wire.begin();
  ledArray.begin();

  testSetON();
  testPWMMode();
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
  Serial.println("Test - setHIGH");
  for (uint8_t channel = 0; channel < ledArray.channelCount(); channel++)
  {
    ledArray.digitalWrite(channel, HIGH);
  }
}


void testSetOFF()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println("Test - setLOW");
  for (uint8_t channel = 0; channel < ledArray.channelCount(); channel++)
  {
    ledArray.digitalWrite(channel, LOW);
  }
}


void testPWMMode()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println("Test - setPwm getPWM");
  for (uint16_t channel = 0; channel < ledArray.channelCount(); channel++)
  {
    //  every next line ~twice as much time
    ledArray.setPWM(channel, channel * 127, channel * 255);
    uint16_t a, b;
    ledArray.getPWM(channel, &a, &b);
    if ((a != channel * 127) || (b != channel * 255))
    {
      Serial.println(channel);
    }
  }
}


void loop()
{
}


//  -- END OF FILE --

