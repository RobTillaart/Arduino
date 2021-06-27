//
//    FILE: SGP30_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SGP30
//    DATE: 2021-06-24
//     URL: https://github.com/RobTillaart/SGP30
//          https://www.adafruit.com/product/3709


#include "SGP30.h"


SGP30 SGP;

uint8_t count = 0;


void setup()
{
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
    yield();
  };

  Serial.print(__FILE__);
  Serial.println(SGP30_LIB_VERSION);
  Serial.println();

  Serial.print("BEGIN:\t");
  Serial.println(SGP.begin());
  Serial.print("TEST:\t");
  Serial.println(SGP.measureTest());
  Serial.print("FSET:\t");
  Serial.println(SGP.getFeatureSet(), HEX);
  SGP.GenericReset();

  Serial.print("DEVID:\t");
  SGP.getID();
  for (int i = 0; i < 6; i++)
  {
    if (SGP._id[i] < 0x10) Serial.print(0);     // ÏD: 00.00.01.9B.57.23
    Serial.print(SGP._id[i], HEX);
  }
  Serial.println();
}


void loop()
{
  SGP.measure(true);      // returns false if no measurement is made 

  if (count == 0)
  {
    Serial.println("\nTVOC \teCO2 \tH2 \tETH");
    count = 10;
  }
  Serial.print(SGP.getTVOC());
  Serial.print("\t");
  Serial.print(SGP.getCO2());
  Serial.print("\t");
  Serial.print(SGP.getH2());
  Serial.print("\t");
  Serial.print(SGP.getEthanol());
  Serial.println();

  count--;

  delay(1000);
}


// -- END OF FILE --
