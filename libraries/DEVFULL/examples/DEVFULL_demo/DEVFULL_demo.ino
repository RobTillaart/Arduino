//
//    FILE: DEVFULL_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DEVFULL


#include "DEVFULL.h"

DEVFULL df;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.print("PRINTLN:   ");
  //  returns 65480 == -28 + -28 = -56 println() is split in 2 write calls.
  Serial.println(df.println("it is full in here..."));

  Serial.print("PRINT:     ");
  //  returns 65508 == -28 print() maps on one write() call.
  Serial.println(df.print("it is full in here..."));

  Serial.print("WRITE:     ");
  //  returns 65508 == -28 print() maps on one write() call.
  Serial.println(df.write((const uint8_t *) "it is full in here...", 21));

  Serial.print("AVAILABLE: ");
  Serial.println(df.available());
  while (df.available() > 0)
  {
    Serial.print(df.peek());
    Serial.print('\t');
    Serial.println(df.read());
    delay(1000);
  }
}


void loop()
{
}


//  -- END OF FILE --
