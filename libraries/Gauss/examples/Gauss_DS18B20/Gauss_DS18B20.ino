//
//    FILE: Gauss_DS18B20.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//
//  can be used with plotter


#include "DS18B20.h"
#include "Gauss.h"

#define ONE_WIRE_BUS              2

OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);

Gauss G;


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("GAUSS_LIB_VERSION:\t");
  Serial.println(GAUSS_LIB_VERSION);
  Serial.print("DS18B20_LIB_VERSION:\t");
  Serial.println(DS18B20_LIB_VERSION);
  Serial.println();

  //  default temperature + stddev 
  //  adjust to your local situation
  G.begin(26.00, 0.2);
  sensor.begin();
  sensor.setResolution(12);

  Serial.println("\ndone...");
}


void loop(void)
{
  //  simulation
  //  float temp = 18 + random(800) * 0.01;

  sensor.requestTemperatures();
  while (!sensor.isConversionComplete());
  float temp = sensor.getTempC();
  float stddev = G.normalize(temp);

  Serial.print("TEMP: ");
  Serial.print(temp, 2);
  Serial.print("\tSTDDEV: ");
  if (stddev >= 0) Serial.print('+');
  Serial.print(stddev, 2);
  Serial.println();
}


//  -- END OF FILE --
