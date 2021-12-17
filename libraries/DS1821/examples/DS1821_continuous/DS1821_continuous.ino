//
//    FILE: DS1821_continuous.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2015-05-14
// PURPOSE: Arduino library for DS1821 temperature sensor
//     URL: https://github.com/RobTillaart/DS1821
//


#include "DS1821.h"

OneWire ds(10);     // change pin if needed
DS1821 tt(&ds);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  tt.requestTemperature();
}


void loop()
{
  if (tt.conversionReady() == 1)
  {
    float celsius = tt.readTemperature();
    // request next sample async !
    tt.requestTemperature();
    Serial.print("CELSIUS: ");
    Serial.println(celsius, 2);
  }

  // other tasks
  Serial.print(millis());
  Serial.println(": do something else");
  delay(100);
}


// -- END OF FILE --

