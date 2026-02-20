//
//    FILE: MAX30205_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/MAX30205


#include "MAX30205.h"


MAX30205 M[4] = { MAX30205(0x40), MAX30205(0x41), MAX30205(0x42), MAX30205(0x43) };


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAX30205_LIB_VERSION: ");
  Serial.println(MAX30205_LIB_VERSION);
  Serial.println();

  Wire.begin();

  for (int i = 0; i < 4; i++)
  {
    if (M[i].begin() == false)
    {
      Serial.print("Could not find sensor at ");
      Serial.println(M[i].getAddress());
    }
  }
}


void loop()
{
  //  use the first sensor for timekeeping.
  if (millis() - M[0].lastRead() < 1000)
  {
    for (int i = 0; i < 4; i++)
    {
      M[i].read();
      Serial.print(M[i].getTemperature());
      if (i < 3) Serial.print(",");
    }
    Serial.println();
  }
}


//  -- END OF FILE --
