//
//    FILE: Multiplex_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-01-09

#include "Multiplex.h"

Multiplex mp;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  mp.add(&Serial);
  mp.println("one");
  mp.add(&Serial);
  mp.println("two");

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.disable(1);
  mp.println("three");

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.disable(0);
  mp.println("four");

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.enable(0);
  mp.println("\n Done...\n");

}

void loop()
{
}


// -- END OF FILE --
