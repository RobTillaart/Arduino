//
//    FILE: SGP30_demo_async.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SGP30
//     URL: https://github.com/RobTillaart/SGP30
//          https://www.adafruit.com/product/3709


#include "SGP30.h"

SGP30 SGP;

uint8_t count = 0;
uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  while (!Serial) delay(1);

  Serial.println(__FILE__);
  Serial.print("SGP30_LIB_VERSION: ");
  Serial.println(SGP30_LIB_VERSION);
  Serial.println();

  Wire.begin();

  Serial.print("BEGIN:\t");
  Serial.println(SGP.begin());
  Serial.print("TEST:\t");
  Serial.println(SGP.measureTest());
  Serial.print("FSET:\t");
  Serial.println(SGP.getFeatureSet(), HEX);
  SGP.GenericReset();

  Serial.println();
  SGP.request();
}


void loop()
{
  if (SGP.read())
  {
    if (count == 0)
    {
      Serial.println("\nTVOC \teCO2");
      count = 10;
    }
    Serial.print(SGP.getTVOC());
    Serial.print("\t");
    Serial.print(SGP.getCO2());
    Serial.println();
    count--;
  }

  if (millis() - lastTime > 1000)
  {
    lastTime = millis();
    SGP.request();
  }
}


//  -- END OF FILE --

