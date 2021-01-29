//
//    FILE: HX_performance.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711
//
// HISTORY:
// 0.1.0    2020-06-15 initial version
//

#include "HX711.h"

HX711 scale;

uint8_t dataPin = 6;
uint8_t clockPin = 7;

uint32_t start, stop;
volatile float f;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  Serial.println("\nUNCONFIGURED");
  delay(1000);
  measure(10);

  // TODO find a nice solution for this calibration..
  // loadcell factor 20 KG
  // scale.set_scale(127.15);

  // loadcell factor 5 KG
  scale.set_scale(420.0983);
  // reset the scale to zero = 0
  scale.tare();

  Serial.println("\nCONFIGURED");
  delay(1000);
  measure(10);

  Serial.println("\nSLEEP");
  scale.power_down();
  delay(2000);
  scale.power_up();
  Serial.println("\nWAKE UP");
  delay(1000);
  measure(10);

  Serial.println("\nPERFORMANCE");
  start = micros();
  f = 0;
  for (int i = 0; i < 100; i++)
  {
    f = scale.get_units(1);
  }
  stop = micros();
  Serial.print("100x get_units(1) = ");
  Serial.println(stop - start);
  Serial.print("  VAL: ");
  Serial.println(f, 2);

  Serial.println("\nPRECISSION");
  f = 0;
  for (int i = 0; i < 100; i++)
  {
    f += scale.get_units(1);
  }
  Serial.print("  VAL:");
  Serial.println(f * 0.01, 4);

}

void loop()
{
  // continuous scale 4x per second
  f = scale.get_units(5);
  Serial.println(f);
  delay(250);
}

void measure(uint8_t cnt)
{
  Serial.print("  RAW: ");
  Serial.println(scale.read());
  Serial.print("  AVG: ");
  Serial.println(scale.read_average(cnt));
  Serial.print("VALUE: ");
  Serial.println(scale.get_value(cnt));
  Serial.print("UNITS: ");
  Serial.println(scale.get_units(cnt), 1);
}


// -- END OF FILE --
