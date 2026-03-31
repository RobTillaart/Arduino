//
//    FILE: HX712_performance2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX712 performance measurements
//     URL: https://github.com/RobTillaart/HX712


#include "HX712.h"

HX712 scale;

//  adjust pins if needed
uint8_t dataPin = 6;
uint8_t clockPin = 7;

uint32_t start, stop;
volatile float f;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HX712_LIB_VERSION: ");
  Serial.println(HX712_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  //  TODO find a nice solution for this calibration..
  //  load cell factor 20 KG
  //  scale.set_scale(127.15);

  //  load cell factor 5 KG
  scale.set_scale(420.0983);       //  TODO you need to calibrate this yourself.
  //  reset the scale to zero = 0
  scale.tare();

  measure();

  scale.set_gain_rate(128, 40);
}


void loop()
{
}


void measure()
{
  Serial.println("Counting get_units() calls for 1 minute...");
  delay(20);
  uint32_t count = 0;
  uint32_t start = millis();
  while (millis() - start < 60000)
  {
    if (scale.is_ready())
    {
      count++;
      scale.get_units(1);
    }
  }
  Serial.print("calls per minute: ");
  Serial.println(count);
  Serial.print("calls per second: ");
  Serial.println(count / 60.0);
  Serial.print(" micros per call: ");
  Serial.println(60e6 / count);
}


//  -- END OF FILE --
