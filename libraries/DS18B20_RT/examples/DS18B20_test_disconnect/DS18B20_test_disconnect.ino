//
//    FILE: DS18B20_test_disconnect.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Minimal DS18B20 lib with async support.
//     URL: https://github.com/RobTillaart/DS18B20_RT


#include "DS18B20.h"


#define ONE_WIRE_BUS            2

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire, 10);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS18B20_LIB_VERSION: ");
  Serial.println(DS18B20_LIB_VERSION);
  Serial.println();

  //  wait until address found
  if (sensor.begin() == false)
  {
    Serial.println("ERROR: No device found");
    while (!sensor.begin());  //  wait until device comes available.
  }

  Serial.println(sensor.getResolution());

  sensor.setResolution(12);
  sensor.setConfig(DS18B20_CRC);  // or 1
  sensor.requestTemperatures();
}


void loop()
{
  start = millis();
  sensor.requestTemperatures();

  //  wait for data AND detect disconnect
  uint32_t timeout = millis();
  while (!sensor.isConversionComplete())
  {
    if (millis() - timeout >= 800)  //  check for timeout
    {
      Serial.println("ERROR: timeout or disconnect");
      break;
    }
  }

  float t = sensor.getTempC();

  if (t == DEVICE_CRC_ERROR)
  {
    Serial.println("ERROR: CRC error");
  }
  stop = millis();

  Serial.print(millis());
  Serial.print("\t");
  Serial.print(sensor.getResolution());  //  from cache !!
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println( t, 3);
  delay(1000);
}


//  -- END OF FILE --
