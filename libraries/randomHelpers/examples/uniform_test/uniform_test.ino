//
//    FILE: uniform_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-11-15
//     URL: https://github.com/RobTillaart/randomHelpers


#include "randomHelpers.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  test_throwDice();

  Serial.println("\ndone...");
}


void loop()
{
}


void test_throwDice()
{
  Serial.println(__FUNCTION__);
  uint16_t ar[6];
  for (int i = 0; i < 6; i++) ar[i] = 0;

  for (uint32_t i = 0; i < 100000; i++)
  {
    uint8_t x = throwDice();
    ar[x - 1]++;
  }
  for (int i = 0; i < 6; i++)
  {
    Serial.print("\t");
    Serial.print(ar[i]);
  }
  Serial.println();
  for (int i = 0; i < 6; i++)
  {
    Serial.print("\t");
    Serial.print(ar[i] / 166.6666 - 100, 2);
    Serial.print("%");
  }
  Serial.println();
  delay(10);
}


// -- END OF FILE --

