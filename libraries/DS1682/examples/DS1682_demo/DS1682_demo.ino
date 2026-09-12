//
//    FILE: DS1682_demo.ino
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
  bool b = upTimer.begin();

  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.print("ADDR:\t");
  Serial.println(upTimer.getAddress());

  Serial.println("\nUPTIME\nCOUNT\tRUNTIME");
}


void loop()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.print(upTimer.getEventCounter());
  Serial.print("\t");
  Serial.print(upTimer.getElapsedSeconds());
  Serial.println();
  delay(2000);
}


//  -- END OF FILE --
