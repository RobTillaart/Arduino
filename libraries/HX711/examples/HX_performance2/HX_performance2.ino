//
//    FILE: HX_performance2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 performance measurements
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
  //  scale.set_scale(127.15);

  //  load cell factor 5 KG
  scale.set_scale(420.0983);       //  TODO you need to calibrate this yourself.
  //  reset the scale to zero = 0
  scale.tare();

  measure();
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
}


//  -- END OF FILE --

