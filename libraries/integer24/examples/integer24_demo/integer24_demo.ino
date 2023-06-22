//    FILE: integer24_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/integer24


#include "Arduino.h"
#include "integer24.h"

uint32_t start, stop;


uint24_t u = 12345;
uint24_t uar[100];

int24_t s = -4321;
int24_t sar[3] = { -1, 1, 0 };


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("INTEGER24_LIB_VERSION: ");
  Serial.println(INTEGER24_LIB_VERSION);

  uar[99] = random(100);
  Serial.println((uint32_t)u);
  Serial.println(sizeof(u));
  Serial.println((uint32_t)uar[99]);
  Serial.println(sizeof(uar));

  Serial.println((int32_t)s);
  Serial.println(sizeof(s));
  Serial.println((uint32_t)sar[2]);
  Serial.println(sizeof(sar));
}


void loop()
{
}


// -- END OF FILE --
