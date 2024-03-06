//
//    FILE: float16ext_print_all_sci.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16ext
//     URL: https://github.com/RobTillaart/float16ext


#include "float16ext.h"
#include "printHelpers.h"  //  for scientific notation


float16ext f16, f17;

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
    Serial.print(sci(f16.toDouble(), 4));
    Serial.println();
  }

  //  test all negative patterns
  for (uint32_t x = 0x8000; x <= 0xFFFF; x++)
  {
    f16.setBinary(x);
    Serial.print(x);
    Serial.print("\t");
    Serial.print(sci(f16.toDouble(), 4));
    Serial.println();
  }
}

//  -- END OF FILE --
