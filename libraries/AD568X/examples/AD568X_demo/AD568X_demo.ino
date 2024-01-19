//
//    FILE: AD568X_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD568X


#include "AD568X.h"


AD568X AD16_HW(8);
AD568X AD16_SW(9, 10, 11);


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
  uint32_t start = micros();
  for (int i = 0; i < 1000; i++)
  {
    // AD16_HW.setValue(i);
     AD16_SW.setValue(i);
  }
  uint32_t stop = micros();
  Serial.println(stop - start);
  
  delay(1000);
}


//  -- END OF FILE --
