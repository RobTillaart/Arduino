//
//    FILE: print_comma_separated_integers_MT.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo readability of (large) integers
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpersMT.h"

int64_t big = 123456789012345678;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_LIB_VERSION: ");
  Serial.println(PRINTHELPERS_LIB_VERSION);
  Serial.println();

  Serial.println((int32_t)123456789);
  Serial.println(csi((int32_t)123456789));
  Serial.println(csi((int32_t) - 123456789));
  Serial.println(csi((int32_t)12345678));
  Serial.println(csi((uint32_t)1234567));
  Serial.println(csi((int16_t) - 12345));
  Serial.println(csi((int16_t)1234));
  Serial.println(csi((uint8_t)123));
  Serial.println(csi((int8_t)12));
  Serial.println(csi((int32_t) - 1));

  Serial.println(csi(big));

  //  OTHER SPEARATOR
  Serial.println();
  Serial.println((int32_t)123456789);
  Serial.println(csi((int32_t)123456789, '_'));
  Serial.println(csi((int32_t) - 123456789, '_'));
  Serial.println(csi((int32_t)12345678, '_'));
  Serial.println(csi((uint32_t)1234567, '_'));
  Serial.println(csi((int16_t) - 12345, '_'));
  Serial.println(csi((int16_t)1234, '_'));
  Serial.println(csi((uint8_t)123, '_'));
  Serial.println(csi((int8_t)12, '_'));
  Serial.println(csi((int32_t) - 1, '_'));

  Serial.println(csi(big, '.'));
  Serial.println(csi(big, '/'));
  Serial.println(csi(big, '_'));
  Serial.println(csi(big, '-'));
  Serial.println(csi(big, '*'));
  Serial.println(csi(big, '#'));
  Serial.println(csi(big, ':'));
}

void loop()
{
  uint64_t large = 0;
  for (int i = 0; i < 64; i++)
  {
    large += random(2);
    large *= 2;
  }
}

//  -- END OF FILE --
