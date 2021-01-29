//
//    FILE: DS18B20_diagnose.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.1
// PURPOSE: Minimal DS18B20 lib with async support.
//
// HISTORY:
// 0.0.1 = 2020-04-23 initial version

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

  if (sensor.begin() == false)
  {
    Serial.println("Error: Could not find sensor.");
    while (1);
  }
  sensor.setResolution(12);
  sensor.requestTemperatures();

  start = millis();
  while (!sensor.isConversionComplete());
  stop = millis();

  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(sensor.getTempC(), 2);
  Serial.println();
}


void loop()
{
  for (int res = 9; res < 13; res++)
  {
    sensor.setResolution(res);

    start = millis();
    sensor.requestTemperatures();
    while (!sensor.isConversionComplete());
    float temperature = sensor.getTempC();
    stop = millis();

    Serial.print(res);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(temperature, 1); // 1 decimal makes perfect sense
  }
  Serial.println();
  delay(1000);
}

// -- END OF FILE --
