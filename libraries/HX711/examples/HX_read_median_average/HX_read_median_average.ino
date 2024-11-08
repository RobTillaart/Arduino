//
//    FILE: HX_read_median_average.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711


#include "HX711.h"

HX711 scale;

//  adjust pins if needed
uint8_t dataPin = 6;
uint8_t clockPin = 7;

uint32_t start, stop;
volatile float f;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HX711_LIB_VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  //  TODO find a nice solution for this calibration..
  //  load cell factor 20 KG
  scale.set_scale(127.15);

  //  load cell factor 5 KG
  //  scale.set_scale(420.0983);
  //  reset the scale to zero = 0
  scale.tare();

  Serial.println("\nPERFORMANCE");
  start = micros();
  f = 0;
  for (int i = 0; i < 100; i++)
  {
    f = scale.read_medavg(7);
  }
  stop = micros();
  Serial.print("100x read_medavg(7) = ");
  Serial.println(stop - start);
  Serial.print("  VAL: ");
  Serial.println(f, 2);
}


void loop()
{
  //  continuous scale once per second
  f = scale.read_medavg(7);
  Serial.println(f);
  delay(1000);
}


//  -- END OF FILE --

