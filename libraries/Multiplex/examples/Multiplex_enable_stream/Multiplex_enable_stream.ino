//
//    FILE: Multiplex_enable_stream.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-089-10


#include "Multiplex.h"


Multiplex mp;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  mp.add(&Serial);
  mp.println("one");
  mp.add(&Serial);
  mp.println("one++");

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.disableStream(&Serial);
  mp.println("two");

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.disableStream(&Serial);
  mp.println("three");

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.enableStream(&Serial);
  mp.println("\n Done...\n");
}


void loop()
{
}


// -- END OF FILE --

