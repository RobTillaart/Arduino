//
//    FILE: AnalogPin_prescaler.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: example sketch
//     URL: https://github.com/RobTillaart/AnalogPin
//


#include "AnalogPin.h"


AnalogPin AR(A0);

uint32_t start, stop;
uint32_t val;


void setup()
{
  Serial.begin(115200);
  Serial.print("\nExample AnalogPin_prescaler, LIB VERSION: ");
  Serial.println(ANALOGPIN_LIB_VERSION);
  Serial.println("\ntime in msec for 1000 reads");

  for (int ps = 2; ps < 8; ps++)
  {
    Serial.print("\nAR.setPrescaler: ");
    Serial.println(ps);
    AR.setPrescaler(ps);

    Serial.println("AR.read()");
    delay(100);

    val = 0;
    start = millis();
    for (int i = 0; i < 1000; i++)
    {
      val += AR.read();
    }
    stop = millis();
    Serial.print("TIME:\t ");
    Serial.println(stop - start);
    Serial.print("VALUE:\t ");
    Serial.println(val / 1000);
  }
  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --

