//
//    FILE: Gauss_HX711.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//
//  can be used with plotter


#include "HX711.h"
#include "Gauss.h"

HX711 scale;
uint8_t dataPin = 6;
uint8_t clockPin = 7;

Gauss G;


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("GAUSS_LIB_VERSION:\t");
  Serial.println(GAUSS_LIB_VERSION);
  Serial.print("HX711_LIB_VERSION:\t");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  //  default weight in grams + stddev
  //  adjust to your local situation
  G.begin(100.0, 0.75);

  scale.begin(dataPin, clockPin);

  //  load cell factor 5 KG
  //  TODO: calibrate the load cell.
  scale.set_scale(420.0983);

  // reset the scale to zero = 0
  scale.tare();

  Serial.println("you may now add weights.");
}


void loop(void)
{
  //  simulation
  //  float weight = 249 + random(20) * 0.1;

  float weight = scale.get_units(5);
  float stddev = G.normalize(weight);

  Serial.print("WEIGHT: ");
  Serial.print(weight, 1);
  Serial.print("\tSTDDEV: ");
  if (stddev >= 0) Serial.print('+');
  Serial.print(stddev, 2);
  Serial.print("\t");
  if (stddev < -1)     Serial.print("LOW.");  //  TOO LOW
  else if (stddev > 1) Serial.print("HIGH.");
  else                 Serial.print("OK.");
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
