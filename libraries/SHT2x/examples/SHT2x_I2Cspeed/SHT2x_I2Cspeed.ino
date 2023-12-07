//
//    FILE: SHT2x_I2Cspeed
//  AUTHOR: Rob Tillaart
// PURPOSE: testing the performance at different I2C speeds
//     URL: https://github.com/RobTillaart/SHT2x


#include "Wire.h"
#include "SHT2x.h"

uint32_t start, stop;

SHT2x sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);

  Wire.begin();
  sht.begin();

  uint8_t stat = sht.getStatus();
  Serial.print(stat, HEX);
  Serial.println();
}


void loop()
{
  for (uint32_t I2Cfreq = 100000; I2Cfreq < 600000; I2Cfreq += 50000)
  {
    Serial.print(I2Cfreq / 1000);
    Wire.setClock(I2Cfreq);
    test();
  }
}


void test()
{
  start = micros();
  sht.read();
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

