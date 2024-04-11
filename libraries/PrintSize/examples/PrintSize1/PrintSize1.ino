//
//    FILE: PrintSize1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo printSize
//     URL: https://github.com/RobTillaart/PrintSize


#include "PrintSize.h"

PrintSize ps;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTSIZE_VERSION: ");
  Serial.println(PRINTSIZE_VERSION);
  Serial.println();

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

  delay(1000);
}


void printSpaces(uint8_t n)
{
  while (n--) Serial.print(' ');
}


//  -- END OF FILE --
