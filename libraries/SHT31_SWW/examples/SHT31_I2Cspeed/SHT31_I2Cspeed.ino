//
//    FILE: SHT31_I2Cspeed
//  AUTHOR: Rob Tillaart
// PURPOSE: testing the performance at different I2C speeds
//     URL: https://github.com/RobTillaart/SHT31_SWW


#include "SHT31_SWW.h"

#define SHT31_ADDRESS   0x44


SoftwareWire sw(6, 7);

uint32_t start;
uint32_t stop;

SHT31_SWW sht(SHT31_ADDRESS, &sw);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_SWW_LIB_VERSION: \t");
  Serial.println(SHT31_SWW_LIB_VERSION);

  sw.begin();
  sw.setClock(100000);
  sht.begin();

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
}


void loop()
{
  for (uint32_t I2Cfreq = 50000; I2Cfreq < 500000; I2Cfreq += 50000)
  {
    Serial.print(I2Cfreq/1000);
    sw.setClock(I2Cfreq);
    test();
  }
}


void test()
{
  start = micros();
  sht.read(true);         //  default = true/fast       slow = false
  stop = micros();
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht.getHumidity(), 1);
  delay(1000);
}


//  -- END OF FILE --
