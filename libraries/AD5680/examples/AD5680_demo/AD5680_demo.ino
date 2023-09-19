//
//    FILE: AD5680_demo.ino
//  AUTHOR: Rob Tillaart
// PUPROSE: test basic behaviour and performance


#include "AD5680.h"

AD5680 AD16_HW(8);
AD5680 AD16_SW(9, 10, 11);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5680_LIB_VERSION: ");
  Serial.println(AD5680_LIB_VERSION);

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
  for (uint32_t i = 0; i < 1000; i++)
  {
     AD16_HW.setValue(i);
     // AD16_SW.setValue(i);
  }
  uint32_t stop = micros();
  Serial.println(stop - start);
  
  delay(1000);
}


//  -- END OF FILE --
