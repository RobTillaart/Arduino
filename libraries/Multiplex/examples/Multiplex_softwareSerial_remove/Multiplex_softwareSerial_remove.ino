//
//    FILE: Multiplex_softwareSerial_remove.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-01-17


#include "Multiplex.h"
#include <SoftwareSerial.h>


// one multiplexer
Multiplex mp;


// four serial outputs
SoftwareSerial Serial_A(-1, 8);
SoftwareSerial Serial_B(-1, 9);
SoftwareSerial Serial_C(-1, 10);
SoftwareSerial Serial_D(-1, 11);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial_A.begin(19200);
  Serial_B.begin(19200);
  Serial_C.begin(19200);
  Serial_D.begin(19200);

  mp.add(&Serial_A);
  mp.add(&Serial_B);
  mp.add(&Serial_C);
  mp.add(&Serial_D);

  mp.remove((uint8_t)0);

  Serial.println(mp.index(&Serial_A));
  Serial.println(mp.index(&Serial_B));
  Serial.println(mp.index(&Serial_C));
  Serial.println(mp.index(&Serial_D));
  Serial.println();

  mp.remove(1);

  Serial.println(mp.index(&Serial_A));
  Serial.println(mp.index(&Serial_B));
  Serial.println(mp.index(&Serial_C));
  Serial.println(mp.index(&Serial_D));
  Serial.println();

  mp.remove(2);  // will fail

  Serial.println(mp.index(&Serial_A));
  Serial.println(mp.index(&Serial_B));
  Serial.println(mp.index(&Serial_C));
  Serial.println(mp.index(&Serial_D));
  Serial.println();
  Serial.println("--------------");

  mp.reset();
  mp.add(&Serial_A);
  mp.add(&Serial_B);
  mp.add(&Serial_C);
  mp.add(&Serial_D);

  Serial.println(mp.index(&Serial_A));
  Serial.println(mp.index(&Serial_B));
  Serial.println(mp.index(&Serial_C));
  Serial.println(mp.index(&Serial_D));
  Serial.println();

  mp.remove(&Serial_A);

  Serial.println(mp.index(&Serial_A));
  Serial.println(mp.index(&Serial_B));
  Serial.println(mp.index(&Serial_C));
  Serial.println(mp.index(&Serial_D));
  Serial.println();

  mp.remove(&Serial_D);

  Serial.println(mp.index(&Serial_A));
  Serial.println(mp.index(&Serial_B));
  Serial.println(mp.index(&Serial_C));
  Serial.println(mp.index(&Serial_D));
  Serial.println();

  mp.remove(&Serial_B);

  Serial.println(mp.index(&Serial_A));
  Serial.println(mp.index(&Serial_B));
  Serial.println(mp.index(&Serial_C));
  Serial.println(mp.index(&Serial_D));
  Serial.println();

  mp.remove(&Serial_C);

  Serial.println(mp.index(&Serial_A));
  Serial.println(mp.index(&Serial_B));
  Serial.println(mp.index(&Serial_C));
  Serial.println(mp.index(&Serial_D));
  Serial.println();

  mp.println("Done...\n");
}


void loop()
{
}


// -- END OF FILE --
