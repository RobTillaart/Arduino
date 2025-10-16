//    FILE: Logistic_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Logistic
//
//  best viewed with plotter


#include "Logistic.h"

Logistic L;
float x = 0;
uint32_t count = 0;

float p;  //  [32];
uint32_t idx = 0;
uint32_t lastIdx = 0;


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
  //  L.setRate(2.9);  //  1
  //  L.setRate(3.1);  //  2
  //  L.setRate(3.5);  //  4
  //  L.setRate(3.56);  //  8
  L.setRate(3.58);  //  8
  //  set initial value
  Serial.println(0.1 * 100, 6);  //  * 100 improves plotter range
  x = L.iterate(0.1);
  p = x;
  idx = 1;
  Serial.println(x * 100, 6);
}


void loop()
{
  count++;
  x = L.iterate();
  idx = (idx + 1) % 8192;
  //  Serial.println(x * 100, 6);
  if (idx == 0)
  {
    p = x;
  }
  if (abs(p - x) < 0.0000001)
  {
    Serial.print("stable at ");
    Serial.print(count);
    Serial.print(" size ");
    if (idx > lastIdx) Serial.print(idx - lastIdx);
    else Serial.print(lastIdx - idx);
    Serial.print(" val ");
    Serial.println(x, 10);
    lastIdx = idx;
    idx = 0;
    delay(1000);
  }
}

/*
  void loop_org()
  {
  count++;
  x = L.iterate();
  p[idx] = x;
  idx = (idx + 1) % 32;

  Serial.println(x * 100, 6);

  if (idx == 0)
  {
    for (int i = 1; i < 32; i++)
    {
      if (abs(p[i] - p[0] ) < 0.000001)
      {
        Serial.print("stable at ");
        Serial.print(count);
        Serial.print(" size ");
        Serial.println(i);
        for (int j = 0; j < i; j++)
        {
          Serial.print(p[j] * 100, 6);
          Serial.print(" ");
        }
        Serial.println();
        delay(1000);
        break;
      }
    }
  }
  }
*/

//  -- END OF FILE --
