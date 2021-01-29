//
//    FILE: DS18B20_test_disconnect.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.1
// PURPOSE: Minimal DS18B20 lib with async support.
//
// HISTORY:
// 0.0.1 = 2020-04-29 initial version

#include <OneWire.h>
#include <DS18B20.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);

uint32_t start, stop;
uint8_t res = 12;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS18B20 Library version: ");
  Serial.println(DS18B20_LIB_VERSION);

  // wait until address found
  if (sensor.begin() == false)
  {
    Serial.println("ERROR: No device found");
    while (!sensor.begin()); // wait until device comes available.
  }

  sensor.setResolution(12);
  sensor.setConfig(DS18B20_CRC);  // or 1
  sensor.requestTemperatures();
}


void loop()
{
  start = millis();
  sensor.requestTemperatures();

  // wait for data AND detect disconnect
  uint32_t timeout = millis();
  while (!sensor.isConversionComplete())
  {
    if (millis() - timeout >= 800) // check for timeout
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

  Serial.print(res);
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println( t, 1); // 1 decimal makes perfect sense
  delay(1000);
}

// -- END OF FILE --
