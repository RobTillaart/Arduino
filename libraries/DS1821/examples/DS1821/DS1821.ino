//
//    FILE: DS1821.ino
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
  Serial.println(__FILE__);

  int error = tt.requestTemperature();
  Serial.print("Error:\t");
  Serial.println(error);

  uint32_t start = millis();
  // wait max 2 seconds or do other things ...
  while ( tt.conversionReady() == 0 && (millis() - start < 2000));

  if (tt.conversionReady() == 1 )
  {
    float celsius = tt.readTemperature();
    float fahr = celsius * 1.8 + 32;
    Serial.print("CELSIUS: ");
    Serial.println(celsius, 2);
    Serial.print("FAHRENH: ");
    Serial.println(fahr, 2);
  }
  else
  {
    Serial.println("Error: could not determine temperature");
  }
  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --

