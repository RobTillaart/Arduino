//
//    FILE: SGP30_setHumidity.ino
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

  SGP.begin();
  Serial.println(SGP.setRelHumidity(21, 50), HEX);
  Serial.println();
}


void loop()
{
  SGP.measure(false);      //  returns false if no measurement is made

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

  delay(1000);
}


//  -- END OF FILE --

