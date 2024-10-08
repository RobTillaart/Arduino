//
//    FILE: DS18B20_offset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo offset
//     URL: https://github.com/RobTillaart/DS18B20_RT
//
// WARNING: this sketch does not wait for isConversionComplete()
//          and therefore temperature read is probably incorrect
//          but it is fast and maybe accurate enough...


#include "DS18B20.h"


#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS18B20_LIB_VERSION: ");
  Serial.println(DS18B20_LIB_VERSION);
  Serial.println();

  sensor.begin();
  //  arbitrary number for the demo
  sensor.setOffset(0.25);
}


void loop(void)
{
  sensor.requestTemperatures();
  Serial.println(sensor.getTempC());
}


//  -- END OF FILE --
