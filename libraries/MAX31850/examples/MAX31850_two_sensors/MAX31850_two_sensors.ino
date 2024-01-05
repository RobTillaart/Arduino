//
//    FILE: MAX31850_two_sensors.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo with two sensors (on two pins)
//     URL: https://github.com/RobTillaart/MAX31850


#include "OneWire.h"
#include "MAX31850.h"


#define ONE_WIRE_BUS    2


OneWire oneWire(ONE_WIRE_BUS);
MAX31850 sensor(&oneWire);


//  numbers chosen to match pin numbers..
#define ONE_WIRE_BUS2        2
#define ONE_WIRE_BUS3        3

OneWire oneWire2(ONE_WIRE_BUS2);
OneWire oneWire3(ONE_WIRE_BUS3);

MAX31850 inside(&oneWire2);
MAX31850 outside(&oneWire3);


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAX31850_LIB_VERSION: ");
  Serial.println(MAX31850_LIB_VERSION);

  inside.begin();
  outside.begin();

  inside.requestTemperatures();
  outside.requestTemperatures();
}


void loop(void)
{
  //  print the temperature when available and request a new reading
  if (inside.isConversionComplete())
  {
    inside.read();
    Serial.print("inside:\t\t");
    Serial.println(inside.getTempTC(), 1);
    inside.requestTemperatures();
  }
  if (outside.isConversionComplete())
  {
    outside.read();
    Serial.print("outside:\t\t");
    Serial.println(outside.getTempTC(), 1);
    outside.requestTemperatures();
  }
}


//  -- END OF FILE --
