//
//    FILE: AD5660_triangle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD5660


#include "AD5660.h"


AD5660 AD16_HW(8, &SPI);
AD5660 AD16_SW(5, 6, 7);

float frequency = 10.0;
float amplitude = 65535;  //  16 bits


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5660_LIB_VERSION: ");
  Serial.println(AD5660_LIB_VERSION);

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
  float period = 1000000.0 / frequency;
  float value = 2 * fmod(micros(), period);   //  0..period
  if (value < period)
  {
    value = amplitude * value / period;
  }
  else
  {
    value -= period;
    value = amplitude * (1 - value / period);
  }
  AD16_HW.setValue(value);
  Serial.println(value);
}


//  -- END OF FILE --
