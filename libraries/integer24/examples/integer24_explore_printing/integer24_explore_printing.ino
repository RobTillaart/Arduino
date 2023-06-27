//    FILE: integer24_explore_printing.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: investigate printing uint24_t and int24_t
//     URL: https://github.com/RobTillaart/integer24
//
//  this is work in progress

#include "Arduino.h"
#include "integer24.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("INTEGER24_LIB_VERSION: ");
  Serial.println(INTEGER24_LIB_VERSION);

  //  PRINT TEST
  //  exploring options
  Serial.println();

  uint24_t x = 8000000;
  Serial.println(uint32_t(x));
  Serial.println(uint32_t(x), HEX);
  Serial.println(convert24(x));
  Serial.println(convert24(x, HEX));
  Serial.println();

  x = -1;
  Serial.println(uint32_t(x));
  Serial.println(uint32_t(x), HEX);
  Serial.println(convert24(x));
  Serial.println(convert24(x, HEX));
  Serial.println();

  int24_t y = -100000;
  Serial.println(int32_t(y));
  Serial.println(int32_t(y), HEX);  //  note prints leading FF
  Serial.println(int32_t(y) & 0xFFFFFF, HEX);  //  remove leading FF (not nice)
  Serial.println(convert24(y));
  Serial.println(convert24(y, HEX));
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}

//  use like this:
//    uint24 x = 100000;
//    Serial.print(convert24(x));
//
char * convert24(uint24_t value)
{
  return convert24(value, 10);
}

char * convert24(uint24_t value, uint8_t base)
{
  static char buf[9];
  return ltoa(value, buf, base);
}


char * convert24(int24_t value)
{
  return convert24(value, 10);
}

char * convert24(int24_t value, uint8_t base)
{
  static char buf[9];
  return ltoa(value, buf, base);
}


// -- END OF FILE --
