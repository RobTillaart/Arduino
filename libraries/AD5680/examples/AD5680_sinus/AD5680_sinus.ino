//
//    FILE: AD5680_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD5680


#include "AD5680.h"


AD5680 AD16_HW(8, &SPI);
AD5680 AD16_SW(5, 6, 7);

float frequency = 100.0;
float amplitude = 131072;  //  50% of 18 bits

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5680_LIB_VERSION: ");
  Serial.println(AD5680_LIB_VERSION);

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
  Serial.println(x);
}


//  -- END OF FILE --
