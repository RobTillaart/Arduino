//
//    FILE: multimap_NTC_int_FAIL.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of faulty optimizing 
//    DATE: 2020-04-09
//    (c) : MIT
//
//
//  NOTE:
//  use integers instead of floats to minimize RAM. uses ~320 bytes PROGMEM ~120 bytes RAM less on UNO than float version
//
//  this example is added to show how to reduce memory but also how it can FAIL due to math overflow
//  E.g. see around 196-200; 340-400
//  to prevent this one must have more values which increases the memory usage again.



#include "MultiMap.h"

uint32_t start;
uint32_t stop;

volatile float x, y, z;


int in[] = {
  0, 1, 3, 8, 13,  20, 25, 32, 50, 60,  72, 85, 100, 145, 200,  250, 300, 400, 500, 600,  650, 700, 753, 800, 830,  870, 900, 936, 964, 985,  1000, 1017, 1023
};

int out[] = {
  -27315, -7165, -6069, -4981, -4397,    -3850, -3554, -3216, -2572, -2295,    -2008, -1737, -1462, -790, -143,    357, 808, 1634, 2430, 3264, 
  3717, 4213, 4805, 5419, 5875,    6603, 7287, 8385, 9651, 11146,    12949, 18282, 30182
};

int sz = 33;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  delay(10);  //  make sure print has ended

  start = micros();
  x = val(z);
  stop = micros();
  Serial.println(stop - start);
  delay(10);  //  make sure print has ended

  start = micros();
  x = 0.01 * multiMap<int>(z, in, out, sz);
  stop = micros();
  Serial.println(stop - start);
  delay(10);  //  make sure print has ended

  for (int i = 0; i < 1024; i++)
  {
    x = val(i);
    y = 0.01 * multiMap<int>(i, in, out, sz);
    z = abs(x - y);

    Serial.print(i);
    Serial.print('\t');
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    Serial.println();
  }
}


void loop()
{
}


//  NTC formula
float val(int sensorValueA1)
{
  int   R10k_ntc = 9870;
  float U10k_ntc = sensorValueA1 * (5.0 / 1024.0);
  float Untc = 5.0 - U10k_ntc;
  float Rntc = (R10k_ntc * Untc) / U10k_ntc;
  float Temp = (298.15 / (1 - (298.15 / 4300.0) * log(10000.0 / Rntc))) - (273.15 + 0);

  return Temp;
}


//  -- END OF FILE --

