//
//    FILE: DS18B20_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Minimal DS18B20 lib with async support.
//     URL: https://github.com/RobTillaart/DS18B20_RT


#include "DS18B20.h"


#define ONE_WIRE_BUS            2

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS18B20 Library version: ");
  Serial.println(DS18B20_LIB_VERSION);

  sensor.begin();
  sensor.setResolution(12);
  sensor.requestTemperatures();

  start = millis();
  int n = 0;
  // wait until sensor ready, do some counting for fun.
  while (!sensor.isConversionComplete()) n++;
  stop = millis();

  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(n);
  Serial.print("\t");
  Serial.println(sensor.getTempC(), 4);  // 4 decimals is too much ...
  Serial.println();
}


void loop()
{
  float t;
  for (int r = 9; r < 13; r++)
  {
    sensor.setResolution(r);

    int n = 0;
    start = millis();
    sensor.requestTemperatures();
    while (!sensor.isConversionComplete()) n++;
    t = sensor.getTempC();
    stop = millis();

    Serial.print(r);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.print(n);
    Serial.print("\t");
    //  1 decimal makes perfect sense
    Serial.println( t, 1);
  }
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --

