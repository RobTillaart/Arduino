//
//    FILE: DS18B20_simple.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: equivalent of DallasTemperature library Simple
//     URL: https://github.com/RobTillaart/DS18B20_INT


#include "DS18B20_INT.h"


#define ONE_WIRE_BUS            2

OneWire     oneWire(ONE_WIRE_BUS);
DS18B20_INT sensor(&oneWire);


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS18B20_INT_LIB_VERSION: ");
  Serial.println(DS18B20_INT_LIB_VERSION);

  if (sensor.begin() == false)
  {
    Serial.println("not connected!");
  }
}


void loop(void)
{ 
  sensor.requestTemperatures();

  //  BLOCKING!!  blocks until sensor is ready
  while (!sensor.isConversionComplete())
  {
    delay(1);
  }

  Serial.print("Temp: ");
  Serial.println(sensor.getTempC());
}


//  -- END OF FILE --

