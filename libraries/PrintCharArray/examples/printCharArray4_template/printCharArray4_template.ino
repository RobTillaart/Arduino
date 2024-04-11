//
//    FILE: printCharArray4_template.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo it takes less time to send data out.
//     URL: https://github.com/RobTillaart/PrintCharArray


#include "PrintCharArray.h"

PrintCharArrayT<200> ps;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTCHARARRAY_VERSION: ");
  Serial.println(PRINTCHARARRAY_VERSION);
  Serial.println();

  Serial.println("Using direct print");
  delay(100);
  start = micros();
  for (int i = 0; i < 10; i++)
  {
    Serial.println(1000 + i);
  }
  stop = micros();
  Serial.println();
  Serial.println(stop - start);
  Serial.println();

  Serial.println("Using printCharArray");
  delay(100);

  start = micros();
  ps.clear();
  for (int i = 0; i < 10; i++)
  {
    ps.println(1000 + i);
  }
  Serial.println(ps.getBuffer());
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  Serial.println("print PrintCharArray buffer again");
  delay(100);

  start = micros();
  Serial.println(ps.getBuffer());
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  Serial.print("FREE: ");
  Serial.println(ps.available());
}


void loop()
{
}


//  -- END OF FILE --
