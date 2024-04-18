//
//    FILE: float16_test_special.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16
//     URL: https://github.com/RobTillaart/float16

//  test special values ...
//  https://github.com/RobTillaart/float16/issues/2


#include "float16.h"


uint16_t value[32] =
{
  0xFC00, 0xF400, 0xEC00, 0xE400, 0xDC00, 0xD400, 0xCC00, 0xC400,
  0xBC00, 0xB400, 0xAC00, 0xA400, 0x9C00, 0x9400, 0x8C00, 0x8400,
  0x0400, 0x0C00, 0x1400, 0x1C00, 0x2400, 0x2C00, 0x3400, 0x3C00,
  0x4400, 0x4C00, 0x5400, 0x5C00, 0x6400, 0x6C00, 0x7400, 0x7C00
};


float16 f16;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FLOAT16_LIB_VERSION: ");
  Serial.println(FLOAT16_LIB_VERSION);

  for (int i = 0; i < 32; i++)
  {
    f16.setBinary(value[i]);
    Serial.print(value[i], HEX);
    Serial.print("\t");
    Serial.print(f16.toString());
    Serial.print("\t");
    Serial.print(f16.toDouble(), 6);
    Serial.print("\t");
    Serial.println();
  }
  Serial.println();
  Serial.println();

  for (uint32_t x = 1; x < 65535; x *= 4)
  {
    f16 = x;
    Serial.print(f16.getBinary(), HEX);
    Serial.print("\t");
    Serial.print(f16.toString());
    Serial.print("\t");
    Serial.print(f16.toDouble(), 6);
    Serial.print("\t");
    Serial.println();
  }

  Serial.println("\ndone");
}


void loop()
{
}


//  -- END OF FILE --
