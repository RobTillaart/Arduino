//
//    FILE: TM1637_float.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo TM1637 library
//    DATE: 2021-02-15
//     URL: https://github.com/RobTillaart/TM1637


#include "TM1637.h"

TM1637 TM;

uint32_t start, stop;
volatile float f = 3.14159265;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  TM.init(2, 3);
  TM.displayFloat(1.42425);
  delay(2000);
  TM.displayFloat(-1.42425);
  delay(2000);
  TM.displayClear();
  delay(2000);
}


void loop()
{
  test();
  delay(1000);
}


void test()
{
  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    TM.displayFloat(f);  // there is loop overhead etc
    f += 1;
  }
  stop = millis();
  Serial.print("TIME:\t");
  Serial.print(stop - start);
  Serial.println(" ms");
}


// -- END OF FILE --
