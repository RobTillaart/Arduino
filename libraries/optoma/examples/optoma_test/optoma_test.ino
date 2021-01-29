//
//    FILE: optoma_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo vertical keystone.
//    DATE: 2020
//    (c) : MIT
//

// Test with TeraTerm or an Optoma beamer)
// TeraTerm: Newline Receive mode = CR + LF + 9600 baud.

#include "optoma.h"

Optoma beamer;

void setup()
{
  beamer.init(22);

  beamer.switchOn();
  delay(10000);  // wait until lamp is warm

  for (int i = 0; i < 20; i++)
  {
    beamer.increaseVKS();
    delay(100);  // give beamer some time to adjust
  }
  for (int i = 0; i < 20; i++)
  {
    beamer.decreaseVKS();
    delay(100);  // give beamer some time to adjust
  }
  delay(5000);
  beamer.switchOff();
}

void loop()
{

}