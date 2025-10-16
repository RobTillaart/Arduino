//    FILE: Logistic_find_period.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Logistic


#include "Logistic.h"

Logistic L;
float x = 0;
float p = 0;
uint32_t count = 0, lastCount = 0;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print("LOGISTIC_LIB_VERSION: ");
  //  Serial.println(LOGISTIC_LIB_VERSION);
  //  Serial.println();

  //  set initial rate
  L.setRate(0.5);  //  1 => 0
  //  L.setRate(2.0);  //  1
  //  L.setRate(2.9);  //  1
  //  L.setRate(3.1);  //  2
  //  L.setRate(3.5);  //  4
  //  L.setRate(3.560);  //  8
  //  L.setRate(3.565);  //  16
  //  L.setRate(3.570);  //  32
  //  L.setRate(3.57001);  //  704
  //  L.setRate(3.5701);  //  608
  //  L.setRate(3.571);  //  1360
  //  L.setRate(3.572);  //  3872
  //  L.setRate(3.573);  //  1032
  //  L.setRate(3.574);  //  872
  //  L.setRate(3.575);  //  3296
  //  L.setRate(3.576);  //  876
  //  L.setRate(3.577);  //  816
  //  L.setRate(3.578);  //  1144
  //  L.setRate(3.579);  //  1020
  //  L.setRate(3.580);  //  3176  (pretty large)
  //  L.setRate(3.581);  //  1848

  //  set initial value
  x = 0.1;
  p = 0;
  Serial.println(x, 7);  //  * 100 improves plotter range
  x = L.iterate(x);
  Serial.println(x, 7);
}


void loop()
{
  count++;
  x = L.iterate();
  //  Serial.println(x, 7);
  //  after X-1000 iterations we gonna search
  if (count == 4000)
  {
    p = x;
  }

  //  If we find the same number again,
  //  we have a found a repeating period.
  if (abs(p - x) < 0.000001)  //  works for float.
  //  if (p == x)  //  does flaw sometimes e.g. Rate == 2.9.
  {
    Serial.print(L.getRate(), 4);
    Serial.print(" stable at ");
    Serial.print(count);
    Serial.print(" size ");
    Serial.print(count - lastCount);
    Serial.print(" val ");
    Serial.println(x, 7);
    lastCount = count;
    delay(1000);
  }
}


//  -- END OF FILE --
