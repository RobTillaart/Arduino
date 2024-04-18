//
//    FILE: float16_test_all.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16
//     URL: https://github.com/RobTillaart/float16

//  test all values except the NAN
//  test_1 takes ~ 2 minutes on UNO @ 115200baud
//  https://github.com/RobTillaart/float16/issues/2
//
//  test_3 is related to issue #10


#include "float16.h"

float16 f16;

uint32_t start, stop;
uint32_t errors = 0;
float prev;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FLOAT16_LIB_VERSION: ");
  Serial.println(FLOAT16_LIB_VERSION);
  Serial.println("\nStart ");

  test_1();
  test_2();
  test_3();
}


void loop()
{
}


//  test for issue #10
void test_3()
{
  Serial.println(__FUNCTION__);
  uint16_t y = 0;
  uint16_t last = 0;

  start = millis();
  for (int32_t x = 1; x < 65535; x++)  //  test positive integers.
  //  for (int32_t x = -1; x > -65535; x--)   //  test negative integers.
  {
    last = y;
    f16 = x;
    y = f16.getBinary();
    if (y < last)
    {
      Serial.print("|  ");
      Serial.print(x);
      Serial.print("  |  ");
      Serial.print(y, HEX);
      Serial.print("  |  ");
      Serial.print(last, HEX);
      Serial.println("  |");
    }
  }
  stop = millis();
  Serial.println();
  Serial.print("  TIME: ");
  Serial.println(stop - start);
}


void test_2()
{
  Serial.println(__FUNCTION__);
  start = millis();
  for (uint32_t x = 0x0001; x < 0x7C01; x++)
  {
    if (x % 16 == 0) Serial.println();
    f16.setBinary(x);
    float16 f17 = f16.toDouble();
    Serial.print(x, HEX);
    Serial.print("\t");
    Serial.print(f17.toDouble() - f16.toDouble(), 5);
    Serial.println();
  }
  stop = millis();
  Serial.println();
  Serial.print("  TIME: ");
  Serial.println(stop - start);
}


void test_1()
{
  Serial.println(__FUNCTION__);
  //  POSITIVE NUMBERS
  prev = 0;
  errors = 0;
  start = millis();
  for (uint32_t x = 0x0000; x < 0x7C01; x++)
  {
    if (x % 16 == 0) Serial.println();
    f16.setBinary(x);
    Serial.print(x, HEX);
    Serial.print('\t');
    float current = f16.toDouble();
    Serial.print(current, 8);
    if (prev > current)           //  numbers should be increasing.
    {
      Serial.print("\t\tERROR");
      errors++;
    }
    prev = current;
    Serial.println();
  }
  stop = millis();
  Serial.println();
  Serial.print("  TIME: ");
  Serial.println(stop - start);
  Serial.print("ERRORS: ");
  Serial.println(errors);
  Serial.println();
  Serial.println();


  //  NEGATIVE NUMBERS
  prev = 0;
  errors = 0;
  start = millis();
  for (uint32_t x = 0x8000; x < 0xFC01; x++)
  {
    if (x % 16 == 0) Serial.println();
    f16.setBinary(x);
    Serial.print(x, HEX);
    Serial.print('\t');
    float current = f16.toDouble();
    Serial.print(current, 8);
    if (prev < current)           //  negative numbers should be decreasing.
    {
      Serial.print("\t\tERROR");
      errors++;
    }
    prev = current;
    Serial.println();
  }
  stop = millis();
  Serial.println();
  Serial.print("  TIME: ");
  Serial.println(stop - start);
  Serial.print("ERRORS: ");
  Serial.println(errors);
  Serial.println();
  Serial.println();


  Serial.println("\ndone");
}



//  -- END OF FILE --
