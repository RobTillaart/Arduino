//
//    FILE: LC7822_multi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/LC7822


#include "LC7822.h"

//  LC7822(dataPin, clockPin, cePin, sPin, resetPin);
LC7822 LC1(4, 5, 6, 7); //  no reset Pin.
LC7822 LC2(4, 5, 6, 8); //  no reset Pin.
LC7822 LC3(4, 5, 6, 9); //  no reset Pin.


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LC7822_LIB_VERSION: ");
  Serial.println(LC7822_LIB_VERSION);
  Serial.println();

  LC1.begin();
  LC2.begin();
  LC3.begin();

  LC1.setAll(0);
  LC2.setAll(0);
  LC3.setAll(0);

  //  should print 255 0 0.
  LC1.setAll(255);
  Serial.println(LC1.getAll());
  Serial.println(LC2.getAll());
  Serial.println(LC3.getAll());
  Serial.println();

  //  should print 255 255 0.
  LC2.setAll(255);
  Serial.println(LC1.getAll());
  Serial.println(LC2.getAll());
  Serial.println(LC3.getAll());
  Serial.println();

  //  should print 255 255 255.
  LC3.setAll(255);
  Serial.println(LC1.getAll());
  Serial.println(LC2.getAll());
  Serial.println(LC3.getAll());
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
