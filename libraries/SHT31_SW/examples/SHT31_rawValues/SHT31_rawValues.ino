//
//    FILE: SHT31_async.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo async interface
//     URL: https://github.com/RobTillaart/SHT31_SW


#include "SoftWire.h"
#include "SHT31_SW.h"

#define SHT31_ADDRESS   0x44


SoftWire sw(6, 7);

uint32_t start;
uint32_t stop;
uint32_t cnt;

SHT31_SW sht(SHT31_ADDRESS, &sw);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_SW_LIB_VERSION: \t");
  Serial.println(SHT31_SW_LIB_VERSION);

  sw.begin();
  sw.setClock(100000);
  sht.begin();


  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
  
  sht.requestData();
  cnt = 0;
}


void loop()
{
  uint16_t rawTemperature;
  uint16_t rawHumidity;

  if (sht.dataReady())
  {
    start = micros();
    bool success  = sht.readData();   //  default = true = fast
    stop = micros();
    sht.requestData();                //  request for next sample

    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    if (success == false)
    {
      Serial.println("Failed read");
    }
    else
    {
      rawTemperature = sht.getRawTemperature();
      rawHumidity = sht.getRawHumidity();
      Serial.print(rawTemperature, HEX);
      Serial.print(" = ");

      // This formula comes from page 14 of the SHT31 datasheet
      Serial.print(rawTemperature * (175.0 / 65535) - 45, 1);
      Serial.print("°C\t");
      Serial.print(sht.getRawHumidity(), HEX);
      Serial.print(" = ");

      // This formula comes from page 14 of the SHT31 datasheet
      Serial.print(rawHumidity * (100.0 / 65535), 1);
      Serial.print("%\t");
      Serial.println(cnt);
      cnt = 0;
    }
  }
  cnt++;  //  simulate other activity
}


//  -- END OF FILE --

