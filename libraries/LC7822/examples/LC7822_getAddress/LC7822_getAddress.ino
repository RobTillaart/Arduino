//
//    FILE: LC7822_getAddress.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/LC7822


#include "LC7822.h"

//  LC7822(dataPin, clockPin, cePin, sPin, resetPin);
LC7821 LC21(4, 5, 6, 7); //  no reset Pin.
LC7822 LC22(4, 5, 6, 7); //  no reset Pin.
LC7823 LC23(4, 5, 6, 7); //  no reset Pin.


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LC7822_LIB_VERSION: ");
  Serial.println(LC7822_LIB_VERSION);
  Serial.println();

  LC21.begin();
  LC22.begin();
  LC23.begin();
  Serial.println(LC21.getAddress());
  Serial.println(LC22.getAddress());
  Serial.println(LC23.getAddress());
}


void loop()
{
}


//  -- END OF FILE --
