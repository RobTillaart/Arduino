//
//    FILE: printCharArray2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: demo right alignment
//     URL: https://github.com/RobTillaart/PrintCharArray
//
//  HISTORY:
//  0.1.0  2017-12-09  initial version
//  0.3.0  2021-01-06  free() -> available()

#include "PrintCharArray.h"

PrintCharArray ps;

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
    ps.clear();
    ps.println(rn);
    printSpaces(15 - ps.size());
    sum += rn;
    Serial.print(ps.getBuffer());
  }
  Serial.print("================ +\n");
  ps.clear();
  ps.println(sum);
  printSpaces(15 - ps.size());
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

// -- END OF FILE --
