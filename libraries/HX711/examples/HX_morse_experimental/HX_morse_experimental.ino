//
//    FILE: HX_morse_experimental.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711
//
//  far from a morse decoder but a start to show a different
//  application for loadcells.
//  discriminate between long and short presses.


#include "HX711.h"

HX711 scale;

uint8_t dataPin = 6;
uint8_t clockPin = 7;

uint32_t start = 0, duration = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  // TODO find a nice solution for this calibration..
  // load cell factor 20 KG
  // scale.set_scale(127.15);

  // load cell factor 5 KG
  scale.set_scale(420.0983);       // TODO you need to calibrate this yourself.
  // reset the scale to zero = 0
  scale.tare(20);
}


void loop()
{
  if (scale.is_ready())
  {
    float val = scale.get_units(1);
    if (start == 0 && val > 10)
    {
      start = millis();
    }
    if (start > 0 && val < 1)
    {
      duration = millis() - start;
      start = 0;

      Serial.print(duration);
      Serial.print("\t");
      if (duration < 700) Serial.println(".");
      else if (duration < 1400) Serial.println("-");
      else Serial.println("---");
    }
  }
}


// -- END OF FILE --
