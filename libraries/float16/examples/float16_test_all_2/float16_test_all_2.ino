//
//    FILE: float16_test_all_2.ino
//  AUTHOR: alecelular, Rob Tillaart
// PURPOSE: test float16
//     URL: https://github.com/RobTillaart/float16
//     URL: https://github.com/RobTillaart/float16/issues/10


#include "float16.h"

//  issue 10 detected an Error -> 32760 / 32767

float16 f16;


void setup()
{
  delay(500);
  Serial.begin(115200);
  while (!Serial) delay(1);

  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FLOAT16_LIB_VERSION: ");
  Serial.println(FLOAT16_LIB_VERSION);

  test_all();

  Serial.println("\ndone");
}


void loop()
{
}


void test_all()
{
  Serial.println(__FUNCTION__);

  //  test all possible positive patterns
  //  test both the conversion to and from float.
  for (uint32_t x = 0x0000; x < 0x7C01; x++)
  {
    f16.setBinary(x);
    float16 f17 = f16.toDouble();

    //  internal format should be equal. Except for -0 and 0.
    if (x - f17.getBinary() != 0)
    {
      Serial.print(f16.toDouble(), 10);
      Serial.print("\t");
      Serial.print(f16.getBinary(), HEX);
      Serial.print("\t");
      Serial.print(f17.getBinary(), HEX);
      Serial.print("\t");
      Serial.print(x - f17.getBinary(), HEX);
      Serial.println();
    }
  }
  Serial.println();


  //  test all possible negative patterns
  for (uint32_t x = 0x8000; x < 0xFC01; x++)
  {
    f16.setBinary(x);
    float16 f17 = f16.toDouble();

    if (x - f17.getBinary() != 0)
    {
      Serial.print(f16.toDouble(), 10);
      Serial.print("\t");
      Serial.print(f16.getBinary(), HEX);
      Serial.print("\t");
      Serial.print(f17.getBinary(), HEX);
      Serial.print("\t");
      Serial.print(x - f17.getBinary(), HEX);
      Serial.println();
    }
  }
  Serial.println();

}


void test_0()
{
  Serial.println(__FUNCTION__);
  for (uint32_t x = 32750; x < 32770; x++)
    // for (uint32_t x = 8175; x < 8205; x++)
  {
    f16 = x;
    Serial.print(x);
    Serial.print("\t");
    Serial.print(f16.toString(2));
    Serial.print("\t");
    Serial.print(f16.toDouble(), 2);
    Serial.print("\t");
    Serial.println();
    yield();
  }

  f16.setBinary(0x7800);
  Serial.print(f16.toDouble(), 2);
  Serial.println();
}


//  -- END OF FILE --
