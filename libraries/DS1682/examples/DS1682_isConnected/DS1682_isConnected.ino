//
//    FILE: DS1682_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/DS1682


#include "DS1682.h"


DS1682 upTimer;  //  0x6A default address


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS1682_LIB_VERSION: ");
  Serial.println(DS1682_LIB_VERSION);
  Serial.println();

  Wire.begin();

  //  begin() tests isConnected.
  bool b = upTimer.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.print("ERROR:\t");
  Serial.println(upTimer.getLastError());
  Serial.print("ADDR:\t");
  Serial.println(upTimer.getAddress(), HEX);

  Serial.println("\ndone...");
}


void loop()
{

}


//  -- END OF FILE --
