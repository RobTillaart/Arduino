//
//    FILE: printCharArray4.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo it takes less time to send data out.
//     URL: https://github.com/RobTillaart/PrintCharArray
//
// HISTORY:
// 0.1.0   2017-12-09 initial version
// 0.1.1   2020-04-30 minor refactor
//

#include "PrintCharArray.h"

PrintCharArray ps(200);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println("Using direct print");
  start = micros();
  for (int i = 0; i < 10; i++)
  {
    Serial.println(1000 + i);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  Serial.println("Using printCharArray");
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

  Serial.println("print PrintCharArray again");
  start = micros();
  Serial.println(ps.getBuffer());
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  Serial.print("FREE: ");
  Serial.println(ps.free());
}

void loop()
{

}

// -- END OF FILE --
