//
//    FILE: Multiplex_enable_stream.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Multiplex


#include "Multiplex.h"


Multiplex mp;


void setup()
{
  //  while (!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MULTIPLEX_LIB_VERSION: ");
  Serial.println(MULTIPLEX_LIB_VERSION);
  Serial.println();

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


//  -- END OF FILE --

