//
//    FILE: PrintSize1.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo printSize
//
// HISTORY:
// 0.1.0   2017-12-09 initial version
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
}

void loop()
{

}

void printSpaces(int n)
{
  if (n <= 0) return;
  while (n)
  {
    Serial.print(' ');
    n--;
  }
}

