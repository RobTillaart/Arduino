//
//    FILE: Multiplex_hardwareSerial.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-11-10
//
//  example for MEGA 2560 only
//  MEGA has four serial outputs
//  Serial
//  Serial1
//  Serial2
//  Serial3


#include "Multiplex.h"


// one multiplexer
Multiplex mp;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  mp.add(&Serial1);
  mp.add(&Serial2);
  mp.add(&Serial3);

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  int n = mp.println("hello world");
  Serial.print("count: ");
  Serial.println(n);

  mp.disableStream(&Serial2);

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.println("\nThis should only print on Serial1 and Serial3n");
  mp.println("Done...\n");
}


void loop()
{
}


// -- END OF FILE --

