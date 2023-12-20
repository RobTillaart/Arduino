//
//    FILE: geomath_test01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: geomath demo
//     URL: https://github.com/RobTillaart/geomath


#include "geomath.h"

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("GEOMATH_LIB_VERSION: ");
  Serial.println(GEOMATH_LIB_VERSION);

  sphere earth(6371.0088);

  for (float lat = 0; lat <= 90; lat += 0.5)  //  0.1
  {
    Serial.print(lat);
    Serial.print("\t");
    Serial.println(earth.circumference(lat));
  }

  //  returns the amount of degrees for a distance in km
  Serial.println(earth.angle(17), 6);
}


void loop()
{
}


//  -- END OF FILE --
