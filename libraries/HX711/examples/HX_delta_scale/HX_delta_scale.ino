//
//    FILE: HX_kitchen_scale.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711


// to be tested

#include "HX711.h"

HX711 scale;

uint8_t dataPin = 6;
uint8_t clockPin = 7;
float w1, w2, previous = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));

  // load cell factor 20 KG
  // scale.set_scale(127.15);
  // load cell factor 5 KG
  scale.set_scale(420.0983);       // TODO you need to calibrate this yourself.
  scale.tare();

  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));
}


void loop()
{
  // read until stable
  w1 = scale.get_units(10);
  delay(100);
  w2 = scale.get_units();
  while (abs(w1 - w2) > 10)
  {
     w1 = w2;
     w2 = scale.get_units();
     delay(100);
  }

  Serial.print("UNITS: ");
  Serial.print(w1);
  if (w1 == 0)
  {
    Serial.println();
  }
  else
  {
    Serial.print("\t\tDELTA: ");
    Serial.println(w1 - previous);
    previous = w1;
  }
  delay(100);
}


// -- END OF FILE --

