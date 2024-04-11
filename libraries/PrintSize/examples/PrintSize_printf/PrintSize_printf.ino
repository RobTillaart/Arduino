//
//    FILE: PrintSize_printf.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo printSize printf
//
//    NOTE: - UNO does not support printf, - ESP32 does


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
    int length = ps.printf("%u\n", rn);
    printSpaces(15 - length);
    sum += rn;
    Serial.printf("%u\n", rn);
  }

  Serial.print("================ +\n");
  int length = ps.printf("%u\n", sum);
  printSpaces(15 - length);
  Serial.printf("%u\n\n", sum);
  delay(1000);
}


void printSpaces(uint8_t n)
{
  while (n--) Serial.print(' ');
}


// -- END OF FILE --

