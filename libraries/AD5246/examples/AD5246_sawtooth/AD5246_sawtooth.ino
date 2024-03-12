//
//    FILE: AD5246_sawtooth.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD5246 demo program
//     URL: https://github.com/RobTillaart/AD5246


#include "AD5246.h"


AD5246 AD;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5246_LIB_VERSION: ");
  Serial.println(AD5246_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  bool b = AD.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD.isConnected());
}


void loop()
{
  for (int val = 0; val < 128; val++)
  {
    AD.write(val);
    Serial.println(val);
    delay(20);
  }
}


//  -- END OF FILE --
