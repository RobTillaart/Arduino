//
//    FILE: MAX31850_minimum.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal sketch
//     URL: https://github.com/RobTillaart/MAX31850


#include "OneWire.h"
#include "MAX31850.h"


#define ONE_WIRE_BUS    2


OneWire oneWire(ONE_WIRE_BUS);
MAX31850 sensor(&oneWire);


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAX31850_LIB_VERSION: ");
  Serial.println(MAX31850_LIB_VERSION);

  sensor.begin();
  sensor.requestTemperatures();
}


void loop(void)
{
  if (sensor.isConversionComplete())
  {
    sensor.read();
    Serial.print("TC:\t");
    Serial.println(sensor.getTempTC());
    Serial.print("INTERN:\t");
    Serial.println(sensor.getTempInternal());
    Serial.println();
    sensor.requestTemperatures();
  }
}


//  -- END OF FILE --

