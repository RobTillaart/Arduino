//
//    FILE: multimap_NTC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-04-09
//    (c) : MIT
//
//  example uses multiMap to calculate the temperature from an 10K NTC.


#include "MultiMap.h"

uint32_t start;
uint32_t stop;

volatile float x, y, z;

//  Note this is a bit an extreme example,
//  normally you only make a multimap of the working range


float in[] = {
  0, 1, 3, 8, 13,  20, 25, 32, 50, 60,  72, 85, 100, 145, 200,  250, 300, 400, 500, 600,  650, 700, 753, 800, 830,  870, 900, 936, 964, 985,  1000, 1017, 1023
};

float out[] = {
  -273.15, -71.65, -60.69, -49.81, -43.97, -38.50, -35.54, -32.16, -25.72, -22.95, -20.08, -17.37, -14.62, -7.90, -1.43, 3.57,
  8.08, 16.34, 24.30, 32.64, 37.17, 42.13, 48.05, 54.19, 58.75, 66.03, 72.87, 83.85, 96.51, 111.46, 129.49, 182.82, 301.82
};

int sz = 33;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();
  delay(100);

  start = micros();
  x = val(z);
  stop = micros();
  Serial.println(stop - start);
  delay(10);  //  make sure print has ended

  start = micros();
  x = multiMap<float>(z, in, out, sz);
  stop = micros();
  Serial.println(stop - start);
  delay(10);  //  make sure print has ended

  for (int i = 0; i < 1024; i++)
  {
    x = val(i);
    y = multiMap<float>(i, in, out, sz);
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

