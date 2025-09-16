//
//    FILE: DS28CM00_perf.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance test DS28CM00 lib
//    DATE: 2017-07-24
//     URL: https://github.com/RobTillaart/DS28CM00


#include "Wire.h"
#include "DS28CM00.h"

uint8_t uid[8];

DS28CM00 DS28(&Wire);

uint32_t start;
uint32_t stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("DS28CM00_LIB_VERSION: "));
  Serial.println(DS28CM00_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  DS28.begin();

  Serial.println();
}


void loop()
{
  if (DS28.getUID(uid))
  {
    perf_test();
    Serial.println();
  }
  else
  {
    Serial.println("Could not connect to DS28CM00...");
  }
  delay(1000);
}


void perf_test()
{
  Serial.println(F("DS28CM00 performance. Times in milliseconds,"));
  delay(100);


  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    DS28.getUID(uid);
  }
  stop = millis();
  Serial.print(F("1000x getUID :\t"));
  Serial.println(stop - start);
  delay(100);


  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    DS28.setI2CMode();
  }
  stop = millis();
  Serial.print(F("1000x setI2C :\t"));
  Serial.println(stop - start);
  delay(100);


  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    DS28.setSMBusMode();
  }
  stop = millis();
  Serial.print(F("1000x setSMB :\t"));
  Serial.println(stop - start);
  delay(100);


  uint8_t mode;
  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    DS28.getMode(mode);
  }
  stop = millis();
  Serial.print(F("1000x getMode:\t"));
  Serial.println(stop - start);
  delay(100);
}


//  -- END OF FILE --

