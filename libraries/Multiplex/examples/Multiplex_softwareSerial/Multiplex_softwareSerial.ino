//
//    FILE: Multiplex_softwareSerial.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-01-17

#include "Multiplex.h"
#include "SoftwareSerial.h"

// one multiplexer
Multiplex mp;

// three serial outputs
SoftwareSerial Serial_A(-1, 8);
SoftwareSerial Serial_B(-1, 9);
SoftwareSerial Serial_C(-1, 10);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

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

  int n = mp.println("hello world");
  Serial.print("count: ");
  Serial.println(n);

  mp.println("\n Done...\n");

}

void loop()
{
}


// -- END OF FILE --
