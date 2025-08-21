//
//    FILE: Multiplex_softwareSerial_count.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Multiplex


#include "Multiplex.h"
#include <SoftwareSerial.h>


// one multiplexer
Multiplex mp;


// three serial outputs
SoftwareSerial Serial_A(-1, 8);
SoftwareSerial Serial_B(-1, 9);
SoftwareSerial Serial_C(-1, 10);


void setup()
{
  //  while (!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MULTIPLEX_LIB_VERSION: ");
  Serial.println(MULTIPLEX_LIB_VERSION);
  Serial.println();

  Serial_A.begin(19200);
  Serial_B.begin(19200);
  Serial_C.begin(19200);

  mp.add(&Serial_A);
  mp.add(&Serial_B);
  mp.add(&Serial_C);

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }
  Serial.println();

  int n = mp.println("hello world");
  Serial.print("count: ");
  Serial.println(n);
  Serial.print("output count: ");
  Serial.println(mp.getOutputCount());

  n = mp.println("hello world");
  Serial.print("count: ");
  Serial.println(n);
  Serial.print("output count: ");
  Serial.println(mp.getOutputCount());
  mp.resetOutputCount();
  Serial.println();

  mp.disableStream(&Serial_B);

  for (int i = 0; i < mp.count(); i++)
  {
    Serial.print("isEnabled ");
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(mp.isEnabled(i));
  }

  mp.println("\nThis should only print on Serial_A and Serial_C\n");

  Serial.print("output count: ");
  Serial.println(mp.getOutputCount());


  mp.println("Done...\n");
}


void loop()
{
}


//  -- END OF FILE --
