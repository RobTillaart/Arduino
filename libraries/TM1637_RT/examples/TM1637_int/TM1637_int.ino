//
//    FILE: TM1637_int.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TM1637 library
//     URL: https://github.com/RobTillaart/TM1637_RT


#include "TM1637.h"


TM1637 TM;

uint32_t start, stop;
volatile uint32_t val  = 0;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TM1637_LIB_VERSION: ");
  Serial.println(TM1637_LIB_VERSION);
  Serial.println();

  TM.begin(2, 3);       //  clock pin, data pin

  TM.displayClear();
  delay(1000);

  TM.displayInt(123456);
  delay(1000);
  TM.displayInt(-98675);
  delay(1000);
  TM.displayInt(-1, true);  //  test no leading zero's
  delay(1000);
  TM.displayInt(-1);        //  default leading zero's
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
    TM.displayInt(++val, false);  //  leading zeros
    TM.dumpCache();
  }
  stop = millis();
  Serial.print("TIME1:\t");
  Serial.print(stop - start);
  Serial.println(" ms");
  delay(100);

  start = millis();
  for (int i = 0; i < 1000; i++)
  {
    TM.displayInt(++val, true);  //  hide leading zeros
    TM.dumpCache();
  }
  stop = millis();
  Serial.print("TIME2:\t");
  Serial.print(stop - start);
  Serial.println(" ms");
  delay(100);
}


//  -- END OF FILE --
