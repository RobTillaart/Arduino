//
//    FILE: DS18B20_two_sensors.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo with two sensors on two different pins
//     URL: https://github.com/RobTillaart/DS18B20_RT


#include "DS18B20.h"


//  numbers chosen to match pin numbers.
#define ONE_WIRE_BUS2               2
#define ONE_WIRE_BUS3               3

OneWire oneWire2(ONE_WIRE_BUS2);
OneWire oneWire3(ONE_WIRE_BUS3);

DS18B20 inside(&oneWire2);
DS18B20 outside(&oneWire3);


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS18B20_LIB_VERSION: ");
  Serial.println(DS18B20_LIB_VERSION);
  Serial.println();

  inside.begin();
  outside.begin();

  //  different resolution shows nicely the async behavior
  inside.setResolution(12);
  outside.setResolution(10);

  inside.requestTemperatures();
  outside.requestTemperatures();
}


void loop(void)
{
  //  print the temperature when available and request a new reading
  if (inside.isConversionComplete())
  {
    Serial.print("inside:\t");
    Serial.println(inside.getTempC(),1);
    inside.requestTemperatures();
  }
  if (outside.isConversionComplete())
  {
    Serial.print("outside:\t\t");
    Serial.println(outside.getTempC(),1);
    outside.requestTemperatures();
  }
}


//  -- END OF FILE --

