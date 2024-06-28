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
  Serial.print("DS18B20_LIB_VERSION: ");
  Serial.println(DS18B20_LIB_VERSION);
  Serial.println();
  delay(100);

  sensor.begin();
  sensor.setResolution(12);
  sensor.requestTemperatures();

  start = millis();
  int n = 0;
  //  wait until sensor ready, do some counting for fun.
  while (!sensor.isConversionComplete()) n++;
  stop = millis();


  delay(100);
  start = micros();
  float f = sensor.getTempC();
  stop = micros();

  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(n);
  Serial.print("\t");
  Serial.println(f, 4);  //  4 decimals is too much ...
  Serial.println();
  delay(100);
}


void loop()
{
  float t;
  for (int r = 9; r < 13; r++)
  {
    sensor.setResolution(r);

    int n = 0;
    sensor.requestTemperatures();
    while (!sensor.isConversionComplete()) n++;

    start = micros();
    t = sensor.getTempC();
    stop = micros();

    Serial.print(r);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.print(n);
    Serial.print("\t");
    //  1 decimal makes perfect sense
    Serial.println( t, 1);
    delay(100);
  }
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
