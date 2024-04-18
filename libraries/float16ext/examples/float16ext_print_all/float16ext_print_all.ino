//
//    FILE: float16ext_print_all.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16ext
//     URL: https://github.com/RobTillaart/float16ext


#include "float16ext.h"


float16ext f16;

void setup()
{
  delay(500);
  Serial.begin(115200);
  while (!Serial) delay(1);

  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FLOAT16EXT_LIB_VERSION: ");
  Serial.println(FLOAT16EXT_LIB_VERSION);

  print_all();

  Serial.println("\ndone");
}


void loop()
{
}


void print_all()
{
  Serial.println(__FUNCTION__);

  //  test all positive patterns
  //  test both the conversion to and from float.
  for (uint32_t x = 0x0000; x <= 0x7FFF; x++)
  {
    f16.setBinary(x);
    Serial.print(x);
    Serial.print("\t");
    Serial.print(f16.toDouble(), 10);
    Serial.print("\t");
    Serial.print(f16.toString(10));
    Serial.println();
  }

  //  test all negative patterns
  for (uint32_t x = 0x8000; x <= 0xFFFF; x++)
  {
    f16.setBinary(x);
    Serial.print(x);
    Serial.print("\t");
    Serial.print(f16.toDouble(), 10);
    Serial.print("\t");
    Serial.print(f16.toString(10));
    Serial.println();
  }
}

//  -- END OF FILE --
