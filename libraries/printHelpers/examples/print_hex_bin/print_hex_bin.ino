//
//    FILE: print_hex_bin.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo hex(value, sep);
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"


volatile uint32_t n = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_VERSION: ");
  Serial.println(PRINTHELPERS_VERSION);
  Serial.println();

  Serial.println();
  uint8_t  a = 111;
  int8_t   b = 112;
  uint16_t c = 113;
  int16_t  d = 114;
  uint32_t e = 113;
  int32_t  f = 114;
  Serial.print(hex(a));
  Serial.print("\t");
  Serial.println(bin(a));

  Serial.print(hex((uint8_t)b));
  Serial.print("\t");
  Serial.println(bin((uint8_t)b));

  Serial.print(hex(c));
  Serial.print("\t");
  Serial.println(bin(c));

  Serial.print(hex((uint16_t)d));
  Serial.print("\t");
  Serial.println(bin((uint16_t)d));

  Serial.print(hex(e));
  Serial.print("\t");
  Serial.println(bin(e));

  Serial.print(hex((uint32_t)f));
  Serial.print("\t");
  Serial.println(bin((uint32_t)f));

  Serial.println(hex((uint64_t)a));
  Serial.println(bin((uint64_t)a));


  Serial.println();
  Serial.println("10 random() HEX values");
  for (uint8_t i = 0; i < 10; i++)
  {
    n = 2 * random(2000000000) + random(2);  //  0 .. 2^32-1
    Serial.print(n);
    Serial.print('\t');
    Serial.print(hex(n));
    Serial.print('\t');
    Serial.println(n, HEX);
  }
  Serial.println();

  Serial.println("10 random() BIN values");
  for (uint8_t i = 0; i < 10; i++)
  {
    n = 2 * random(2000000000) + random(2);  //  0 .. 2^32-1
    Serial.print(n);
    Serial.print('\t');
    Serial.print(bin(n));
    Serial.print('\t');
    Serial.println(n, BIN);
  }
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
