//
//    FILE: PrintSize1.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo printSize
//     URL: https://github.com/RobTillaart/PrintSize
//
// HISTORY:
// 0.1.0   2017-12-09 initial version
// 0.1.1   2020-02-19 refactored, simpler printSpaces()
//

#include "PrintSize.h"

PrintSize ps;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println("Determine length of 10 random numbers and right ");
  Serial.println("align the numbers in a table with their sum.");
  Serial.println();
}

void loop()
{
  uint32_t sum = 0;

  for (int i = 0; i < 10; i++)
  {
    uint32_t rn = random(100000000);
    int length = ps.println(rn);
    printSpaces(15 - length);
    sum += rn;
    Serial.println(rn);
  }

  Serial.print("================ +\n");
  int length = ps.println(sum);
  printSpaces(15 - length);
  Serial.println(sum);
  Serial.println();
}

void printSpaces(uint8_t n)
{
  while (n--) Serial.print(' ');
}

// -- END OF FILE -- 
