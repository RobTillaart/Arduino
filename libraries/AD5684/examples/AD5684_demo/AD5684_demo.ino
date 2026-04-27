//
//    FILE: AD5684_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD5684


#include "AD5684.h"


AD5684 AD16_HW(5, &SPI);
AD5684 AD16_SW(15, 13, 14);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5684_LIB_VERSION: ");
  Serial.println(AD5684_LIB_VERSION);
  Serial.println();

  SPI.begin();
  AD16_HW.begin();
  AD16_SW.begin();

  Serial.print("HWSPI: ");
  Serial.println(AD16_HW.usesHWSPI());
  Serial.print("HWSPI: ");
  Serial.println(AD16_SW.usesHWSPI());
  delay(100);
}


void loop()
{
  uint32_t start = micros();
  for (uint32_t i = 0; i < 1000; i++)
  {
    //  AD16_HW.setValue(i);
    AD16_SW.setValue(0, i);
    AD16_SW.setValue(1, i);
    AD16_SW.setValue(2, i);
    AD16_SW.setValue(3, 1000 - i);
  }
  uint32_t duration = micros() - start;
  Serial.print(duration);
  Serial.print("\t");
  Serial.println(4e9 / duration);

  delay(1000);
}


//  -- END OF FILE --
