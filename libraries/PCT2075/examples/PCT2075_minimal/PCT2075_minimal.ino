//
//    FILE: PCT2075_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PCT2075 temperature sensor
//     URL: https://github.com/RobTillaart/PCT2075
//

#include "PCT2075.h"

PCT2075 pct(0x37);

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCT2075_LIB_VERSION: ");
  Serial.println(PCT2075_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = pct.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);
}


void loop()
{
  float temperature = pct.getTemperature();
  Serial.println(temperature, 3);
  delay(1000);
}



//  -- END OF FILE --
