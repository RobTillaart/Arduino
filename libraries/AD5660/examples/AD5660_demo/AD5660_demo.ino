//
//    FILE: AD5660_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD5660


#include "AD5660.h"


AD5660 AD16_HW(5, &SPI);
AD5660 AD16_SW(15, 13, 14);


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
  delay(100);

  AD16_HW.setSPIspeed(16000000);
  
  Serial.println();
  Serial.println("usec\tcalls/sec");
}


void loop()
{
  uint32_t start = micros();
  for (uint16_t i = 0; i < 1000; i++)
  {
    AD16_HW.setValue(i);
    // AD16_SW.setValue(i);
  }
  uint32_t duration = micros() - start;
  Serial.print(duration * 0.001);
  Serial.print("\t");
  Serial.println(round(1e9 / duration));

  delay(1000);
}


//  -- END OF FILE --
