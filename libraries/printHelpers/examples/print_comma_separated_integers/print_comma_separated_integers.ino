//
//    FILE: print_comma_separated_integers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo readability
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_VERSION: ");
  Serial.println(PRINTHELPERS_VERSION);

  Serial.println((int32_t)123456789);
  Serial.println(csi((int32_t)123456789));
  Serial.println(csi((int32_t)-123456789));
  Serial.println(csi((int32_t)12345678));
  Serial.println(csi((uint32_t)1234567));
  Serial.println(csi((int16_t)-12345));
  Serial.println(csi((int16_t)1234));
  Serial.println(csi((uint8_t)123));
  Serial.println(csi((int8_t)12));
  Serial.println(csi((int32_t)-1));

  int64_t big = 123456789012345678;
  Serial.println(csi(big));
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

// -- END OF FILE --
