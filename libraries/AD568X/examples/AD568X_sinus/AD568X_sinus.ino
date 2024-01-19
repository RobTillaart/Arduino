//
//    FILE: AD568X_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD568X


#include "AD568X.h"


AD5683 AD16_HW(8);
AD5683 AD16_SW(9, 10, 11);

float frequency = 100.0;
float amplitude = 32768;  //  50% of 16 bits


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD568X_LIB_VERSION: ");
  Serial.println(AD568X_LIB_VERSION);

  SPI.begin();
  AD16_HW.begin();
  AD16_SW.begin();

  Serial.print("HWSPI: ");
  Serial.println(AD16_HW.usesHWSPI());
  Serial.print("HWSPI: ");
  Serial.println(AD16_SW.usesHWSPI());
}


void loop()
{
  float phase  = fmod(micros() * (frequency * (TWO_PI * 1e-6)), TWO_PI);
  float x = (1 + sin(phase)) * amplitude;
  AD16_HW.setValue(x);
  //  Serial.println(x);  //  test
}


//  -- END OF FILE --
