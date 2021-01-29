//
//    FILE: SHT31_I2Cspeed
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: testing the performance at different I2C speeds
//     URL: https://github.com/RobTillaart/SHT31

#include "Wire.h"
#include "SHT31.h"

#define SHT31_ADDRESS   0x44

uint32_t start;
uint32_t stop;

SHT31 sht;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  sht.begin(SHT31_ADDRESS);
  Wire.setClock(100000);

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
}

void loop()
{
  for (uint32_t I2Cfreq = 100000; I2Cfreq < 900000; I2Cfreq += 50000)
  {
    Serial.print(I2Cfreq/1000);
    Wire.setClock(I2Cfreq);
    test();
  }
}


void test()
{
  start = micros();
  sht.read(true);         // default = true/fast       slow = false
  stop = micros();
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht.getHumidity(), 1);
  delay(100);
}

// -- END OF FILE --
