//
//    FILE: SHT2x_demo_async_HT.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo asynchronous interface
//     URL: https://github.com/RobTillaart/SHT2x
//
//  needs version 0.3.1 or higher.


#include "Wire.h"
#include "SHT2x.h"

SHT2x sht;


//  TIMING SCHEDULE
uint32_t lastTemp = 0;
uint32_t intervalTemp = 2000;
uint32_t lastHum = 0;
uint32_t intervalHum = 5000;


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

  sht.requestTemperature();
}


void loop()
{
  uint32_t now = millis();

  //  schedule and handle temperature
  if ((now - lastTemp > intervalTemp) && (sht.getRequestType() == 0x00))
  {
    sht.requestTemperature();
  }
  if (sht.reqTempReady())
  {
    lastTemp = now;
    sht.readTemperature();
    Serial.print("TEMP:\t");
    Serial.println(sht.getTemperature(), 1);
  }

  //  schedule and handle humidity
  if ((now - lastHum > intervalHum) && (sht.getRequestType() == 0x00))
  {
    sht.requestHumidity();
  }
  if (sht.reqHumReady())
  {
    lastTemp = now;
    sht.readHumidity();
    Serial.print("HUMI:\t");
    Serial.println(sht.getHumidity(), 1);
  }

  //  do other things here
  delay(1000);
}


//  -- END OF FILE --
