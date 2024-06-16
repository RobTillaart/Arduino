//
//    FILE: M5ROTATE8_address_change.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "m5rotate8.h"


M5ROTATE8 MM;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("M5ROTATE8_LIB_VERSION: ");
  Serial.println(M5ROTATE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();
  MM.resetAll();

  Serial.print("Before: \t");
  Serial.println(MM.getAddress());
  Serial.print("Connect: \t");
  Serial.println(MM.isConnected());

  //  assumes not out of range.
  MM.setAddress(MM.getAddress() + 2);

  Serial.print("After: \t");
  Serial.println(MM.getAddress());
  Serial.print("Connect: \t");
  Serial.println(MM.isConnected());

  
}


void loop()
{ 

}


//  -- END OF FILE --
