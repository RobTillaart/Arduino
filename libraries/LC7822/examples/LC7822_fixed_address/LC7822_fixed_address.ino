//
//    FILE: LC7822_fixed_address.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/LC7822


#include "LC7822.h"

//  LC7822(dataPin, clockPin, cePin, sPin, resetPin);
LC7821 LC1(4, 5, 6);  //  no sPin and no resetPin.
LC7822 LC2(4, 5, 6);  //  no sPin and no resetPin.
LC7823 LC3(4, 5, 6);  //  no sPin and no resetPin.


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LC7822_LIB_VERSION: ");
  Serial.println(LC7822_LIB_VERSION);
  Serial.println();

  LC1.begin(0x0A);
  Serial.println(LC1.getAddress());
  LC2.begin(0x0C);
  Serial.println(LC2.getAddress());
  LC3.begin(0x0E);
  Serial.println(LC3.getAddress());
}


void loop()
{

}


//  -- END OF FILE --
