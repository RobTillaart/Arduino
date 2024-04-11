//
//    FILE: currency_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance test
//     URL: https://github.com/RobTillaart/currency


#include "Arduino.h"
#include "currency.h"

uint32_t start, stop;
char * p;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  delay(100);

  int x = 0x0020;
  Serial.println(__builtin_ctz(x) + 1);
  
  start = micros();
  p = currency(10000000, 0, '.', ',', '$');
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(p);
  Serial.println();
  delay(100);

  start = micros();
  p = currency64(-999999999999999, 2, '.', ',', '$');
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(p);
  Serial.println();
  delay(100);

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
