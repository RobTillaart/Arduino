//
//    FILE: DS18B20_Kelvin.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: set offset to mimick Kelvin scale
//     URL: https://github.com/RobTillaart/DS18B20_RT


#include "DS18B20.h"


#define ONE_WIRE_BUS              2

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS18B20_LIB_VERSION: ");
  Serial.println(DS18B20_LIB_VERSION);
  Serial.println();

  sensor.begin();
  sensor.setResolution(12);
  sensor.setOffset(273.15);
}


void loop(void)
{
  sensor.requestTemperatures();

  //  wait until sensor is ready
  while (!sensor.isConversionComplete())
  {
    delay(1);
  }

  Serial.print("Kelvin: ");
  Serial.println(sensor.getTempC());
}


//  -- END OF FILE --
