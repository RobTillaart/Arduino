//
//    FILE: DS18B20_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show performance of DS18B20 lib 
//          compared to datasheet times per resolution
//     URL: https://github.com/RobTillaart/DS18B20_RT


#include <OneWire.h>
#include <DS18B20.h>

#define ONE_WIRE_BUS 2

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
}


void loop()
{
  float ti[4] = { 94, 188, 375, 750 };

  Serial.println();
  Serial.println("Test takes about 30 seconds for 4 resolutions, 20 measurements");
  Serial.println("RES\tTIME\tACTUAL\tGAIN");
  for (int r = 9; r < 13; r++)
  {
    sensor.setResolution(r);

    uint32_t duration = run(20);
    float avgDuration = duration / 20.0;

    Serial.print(r);
    Serial.print("\t");
    Serial.print(ti[r - 9]);
    Serial.print("\t");
    Serial.print(avgDuration, 2);
    Serial.print("\t");
    Serial.print(avgDuration * 100 / ti[r - 9], 1);
    Serial.println("%");
  }
  delay(1000);
}


uint32_t run(int runs)
{
  float t;
  start = millis();
  for (int i = 0; i < runs; i++)
  {
    sensor.requestTemperatures();
    while (!sensor.isConversionComplete());
    t = sensor.getTempC();
  }
  stop = millis();
  return stop - start;
}


// -- END OF FILE --

