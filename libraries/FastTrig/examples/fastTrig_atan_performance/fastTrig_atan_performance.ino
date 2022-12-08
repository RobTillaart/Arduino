//    FILE: fastTrig_atan_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-05
// PURPOSE: performance and accuracy measurement  
//     URL: https://github.com/RobTillaart/FastTrig


#include "Arduino.h"
#include "FastTrig.h"


uint32_t start, stop;
float x, y;
float angle, length;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  delay(10);

  x = random(100);
  y = x + random(100);
  
  start = micros();
  angle = atan(x / y);
  stop = micros();
  Serial.println("\natan");
  Serial.println(x / y, 4);
  Serial.println(angle, 4);
  Serial.println(stop - start);
  delay(10);

  start = micros();
  angle = atanFast(x / y);
  stop = micros();
  Serial.println("\natanFast");
  Serial.println(angle, 4);
  Serial.println(stop - start);
  delay(10);
  
  start = micros();
  angle = atan2(y, x);
  stop = micros();
  Serial.println("\natan2");
  Serial.println(angle, 4);
  Serial.println(stop - start);
  delay(10);

  start = micros();
  angle = atan2Fast(y, x);
  stop = micros();
  Serial.println("\natan2Fast");
  Serial.println(angle, 4);
  Serial.println(stop - start);
  delay(10);
  
  Serial.println("\natan2Fast comparison");
  for (float x = -100; x <= 100; x++)
  {
    for (float y = -100; y <= 100; y++)
    {
      if (abs(atan2(y, x) - atan2Fast(y, x)) > 0.001)  //  0.0007
      {
        Serial.print(x, 4);
        Serial.print('\t');
        Serial.print(y, 4);
        Serial.print('\t');
        Serial.print(atan2(y, x), 10);
        Serial.print('\t');
        Serial.print(atan2Fast(y, x), 10);
        Serial.print('\n');
      }
    }
  }

  Serial.println("done");

}

//  sin(radians);
//  isin(degrees)
//  zin(radians*2/PI)
float zin(float x)
{
  float x2 = x * x;
  // return ((((-0.004392476*x2 + 0.079487663) * x2) -0.645920978) * x2 + 1.570794852) * x;
  return (((0.0727102 * x2) - 0.6432292) * x2 + 1.5706268) * x;
}


float atanA(float x)
{
  float x2 = x * x;
  return (((0.079331 * x2) - 0.288679) * x2 + 0.995354) * x;
  // return ((((-0.0389929 * x2) + 0.1462766) * x2 - 0.3211819) * x2 + 0.9992150) * x;
}


float atan2A(float y, float x)
{
  if (x >= 0)
  {
    if (y >= 0)
    {
      if (abs(y) >= abs(x)) return PI / 2 - atanA(x / y);
      return atanA(y / x);
    }
    if (abs(y) >= abs(x)) return -PI / 2 - atanA(x / y);
    return atanA(y / x);
  }
  else
  {
    if (y >= 0)
    {
      if (abs(y) >= abs(x)) return PI / 2 - atanA(x / y);
      return PI + atanA(y / x);
    }
    if (abs(y) >= abs(x)) return -PI / 2 - atanA(x / y);
    return -PI + atanA(y / x);
  }
}

/*
  float atan2A(float y, float x)
  {
  float t;
  bool swap = abs(x) < abs(y);
  if (swap) t = x / y;
  else t = y / x;

  float res = atanA(t);
  if (swap)
  {
    if (t >= 0) res = PI / 2 - res;
    else res = -PI / 2 - res;
  }
  if (x < 0)
  {
    if (y >= 0) res += PI;
    else res -= PI;
  }
  return res;
  }
*/

void loop()
{
}

// -- END OF FILE --
