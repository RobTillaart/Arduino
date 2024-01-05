//
//    FILE: MAX31850_test_disconnect.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Minimal MAX31850 lib with async support.
//     URL: https://github.com/RobTillaart/MAX31850


#include "OneWire.h"
#include "MAX31850.h"


#define ONE_WIRE_BUS    2


OneWire oneWire(ONE_WIRE_BUS);
MAX31850 sensor(&oneWire);


uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAX31850_LIB_VERSION: ");
  Serial.println(MAX31850_LIB_VERSION);

  //  wait until address found
  if (sensor.begin() == false)
  {
    Serial.println("ERROR: No device found");
    while (!sensor.begin());  //  wait until device comes available.
  }

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
    if (millis() - timeout >= 1000)    //  check for timeout
    {
      Serial.println("ERROR: timeout or disconnect");
      break;
    }
  }

  sensor.read();
  float temperature = sensor.getTempTC();
  stop = millis();

  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(temperature, 1);    //  1 decimal makes perfect sense
  delay(1000);
}


//  -- END OF FILE --
