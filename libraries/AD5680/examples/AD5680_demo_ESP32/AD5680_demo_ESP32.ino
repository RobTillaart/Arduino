//
//    FILE: AD5680_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD5680


#include "AD5680.h"


#ifndef ESP32
#error ESP32 only example, please select appropriate board
#endif


//  HSPI uses default   SCLK=14, MISO=12, MOSI=13, SELECT=15
//  VSPI uses default   SCLK=18, MISO=19, MOSI=23, SELECT=5
SPIClass * myspi = new SPIClass(VSPI);
AD5680 AD16_HW(5, myspi);
AD5680 AD16_SW(15, 13, 14);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5680_LIB_VERSION: ");
  Serial.println(AD5680_LIB_VERSION);

  myspi->begin();
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
     // AD16_HW.setValue(i);
     AD16_SW.setValue(i);
  }
  uint32_t duration = micros() - start;
  Serial.print(duration);
  Serial.print("\t");
  Serial.println(1e9 / duration);
  
  delay(1000);
}


//  -- END OF FILE --
