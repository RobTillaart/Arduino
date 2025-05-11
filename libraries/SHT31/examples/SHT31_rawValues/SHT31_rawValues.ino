//
//    FILE: SHT31_rawValues.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo reading raw data
//     URL: https://github.com/RobTillaart/SHT31


#include "Wire.h"
#include "SHT31.h"

#define SHT31_ADDRESS   0x44

uint32_t start;
uint32_t stop;
uint32_t cnt;

SHT31 sht(SHT31_ADDRESS);  //  uses explicit address


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
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

      //  This formula comes from page 14 of the SHT31 datasheet
      Serial.print(rawTemperature * (175.0 / 65535) - 45, 1);
      Serial.print("°C\t");
      Serial.print(sht.getRawHumidity(), HEX);
      Serial.print(" = ");

      //  This formula comes from page 14 of the SHT31 datasheet
      Serial.print(rawHumidity * (100.0 / 65535), 1);
      Serial.print("%\t");
      Serial.println(cnt);
      cnt = 0;
    }
  }
  cnt++;  //  simulate other activity
}


//  -- END OF FILE --

