//
//    FILE: AD56X8_test_ESP32.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/AD56X8


#include "AD56X8.h"


#ifndef ESP32
#error ESP32 only example, please select appropriate board
#endif


//  HSPI uses default   SCLK=14, MISO=12, MOSI=13, SELECT=15
//  VSPI uses default   SCLK=18, MISO=19, MOSI=23, SELECT=5
SPIClass * myspi = new SPIClass(VSPI);
AD56X8 AD16_HW(5, myspi);
AD56X8 AD16_SW(15, 13, 14);

int value = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD56X8_LIB_VERSION: ");
  Serial.println(AD56X8_LIB_VERSION);

  myspi->begin();
  AD16_HW.begin();
  AD16_SW.begin();

  Serial.print("HWSPI: ");
  Serial.println(AD16_HW.usesHWSPI());
  Serial.print("HWSPI: ");
  Serial.println(AD16_SW.usesHWSPI());
}


void loop()
{
  AD16_SW.setValue(0, value);
  value++;
  if (value == 4096) value = 0;
  Serial.println(value);
  delay(10);
}


//  -- END OF FILE --
