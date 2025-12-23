//
//    FILE: LC7822_multi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/LC7822


#include "LC7822.h"

//  LC7822(dataPin, clockPin, cePin, sPin, resetPin);
LC7822 LC1(4, 5, 6, 7);  //  no resetPin, unique sPin
LC7822 LC2(4, 5, 6, 8);  //  no resetPin, unique sPin
LC7822 LC3(4, 5, 6, 9);  //  no resetPin, unique sPin


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LC7822_LIB_VERSION: ");
  Serial.println(LC7822_LIB_VERSION);
  Serial.println();

  Serial.println(LC1.begin());  //  use default addresses
  Serial.println(LC2.begin());  //  use default addresses
  Serial.println(LC3.begin());  //  use default addresses

  LC1.setAll(0);
  LC2.setAll(0);
  LC3.setAll(0);
  //  should print 0 0 0.
  Serial.print(LC1.getAll());
  Serial.print("  ");
  Serial.print(LC2.getAll());
  Serial.print("  ");
  Serial.println(LC3.getAll());

  //  should print 255 0 0.
  LC1.setAll(255);
  Serial.print(LC1.getAll());
  Serial.print("  ");
  Serial.print(LC2.getAll());
  Serial.print("  ");
  Serial.println(LC3.getAll());

  //  should print 255 255 0.
  LC2.setAll(255);
  Serial.print(LC1.getAll());
  Serial.print("  ");
  Serial.print(LC2.getAll());
  Serial.print("  ");
  Serial.println(LC3.getAll());

  //  should print 255 255 255.
  LC3.setAll(255);
  Serial.print(LC1.getAll());
  Serial.print("  ");
  Serial.print(LC2.getAll());
  Serial.print("  ");
  Serial.println(LC3.getAll());
}


void loop()
{
}


//  -- END OF FILE --
