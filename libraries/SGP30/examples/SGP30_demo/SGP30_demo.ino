//
//    FILE: SGP30_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SGP30
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

  Serial.print("DEVID:\t");
  SGP.getID();
  for (int i = 0; i < 6; i++)
  {
    // ÏD looks like: 00.00.01.9B.57.23
    if (SGP._id[i] < 0x10) Serial.print(0);
    Serial.print(SGP._id[i], HEX);
  }
  Serial.println();
}


void loop()
{
  SGP.measure(true);      //  returns false if no measurement is made 

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


//  -- END OF FILE --
