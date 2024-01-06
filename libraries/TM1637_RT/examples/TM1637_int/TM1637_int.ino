//
//    FILE: TM1637_int.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TM1637 library
//     URL: https://github.com/RobTillaart/TM1637


#include "TM1637.h"


TM1637 TM;

uint32_t start, stop;
volatile uint32_t val  = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  TM.begin(2, 3);       //  clock pin, data pin

  TM.displayClear();
  delay(1000);

  TM.displayInt(123456);
  delay(1000);
  TM.displayInt(-98675);
  delay(1000);
}


void loop()
{
  test();
  delay(1000);
  TM.displayClear();
  delay(1000);
}


void test()
{
  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    TM.displayInt(val);  // there is loop overhead etc.
    val++;
  }
  stop = millis();
  Serial.print("TIME:\t");
  Serial.print(stop - start);
  Serial.println(" ms");
}


//  -- END OF FILE --

