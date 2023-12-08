//
//    FILE: SGP30_baseline.ino
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
}


void loop()
{
  SGP.measure(true);      //  returns false if no measurement is made

  if (count == 0)
  {
    uint16_t bl_co2 = 0;
    uint16_t bl_tvoc = 0;
    bool b = SGP.getBaseline(&bl_co2, &bl_tvoc);

    Serial.println();
    Serial.print("BASELINE GET: \t");
    Serial.println(b);
    Serial.print("BASELINE CO2: \t");
    Serial.println(bl_co2);
    Serial.print("BASELINE VOC: \t");
    Serial.println(bl_tvoc);

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
