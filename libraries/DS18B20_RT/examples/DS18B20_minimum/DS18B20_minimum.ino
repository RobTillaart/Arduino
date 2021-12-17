//
//    FILE: DS18B20_minimum.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.1
// PURPOSE: most minimal sketch
//     URL: https://github.com/RobTillaart/DS18B20_RT
//
// WARNING: this sketch does not wait for isConversionComplete()
//          and therefore temperature read is probably incorrect
//          but it is fast and maybe accurate enough...


#include <OneWire.h>
#include <DS18B20.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  sensor.begin();
}


void loop(void)
{
  sensor.requestTemperatures();
  Serial.println(sensor.getTempC());
}


// -- END OF FILE --

