//
//    FILE: DS18B20_INT.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.1
// PURPOSE: Minimalistic demo


#include "DS18B20_INT.h"

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DS18B20_INT sensor(&oneWire);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  sensor.begin();
}


void loop()
{
  int n = 0;
  start = millis();
  sensor.requestTemperatures();
  while (!sensor.isConversionComplete()) n++;
  int t = sensor.getTempC();
  stop = millis();

  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(n);
  Serial.print("\t");
  Serial.println(t);
  Serial.println();
  delay(1000);
}

// -- END OF FILE --
