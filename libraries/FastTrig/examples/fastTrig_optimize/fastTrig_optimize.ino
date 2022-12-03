//
//    FILE: fastTrig_optimize.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: sketch to optimize the table for interpolation
//    DATE: 2020-09-06

// WARNING TAKES A LOT OF TIME ON 16 MHz

// TODO    make a python script for this ?


#include "FastTrig.h"


float getError(int i)
{
  float error = 0;
  for (float f = i - 1; f < i + 1; f += 0.0001)   // get error due to interpolation around point i .
  {
    error += abs(sin(f / 180 * PI) - isin(f));    // sum up the error (all errors are traded equal
  }
  return error;
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // print the table
  for (int i = 0; i <= 90; i++)
  {
    Serial.print(sinTable16[i]);
    Serial.print(", ");
    if (i % 10 == 0) Serial.println();
  }
  Serial.println();
  Serial.println();
  test_isin_error_1(false);
  Serial.println();

  while(optimize());  // prints a new table as long as it is better.

  Serial.println("\n\ndone...");
}


int optimize()
{
  int rv = 0;
  for (int i = 1; i < 90; i++)   // for every angle
  {
    int t = sinTable16[i];
    int idx = 0;
    float minError = getError(i);  // what is the current error
    bool flag = false;
    for (int j = -2; j <= 2; j++)   // try if adjacent numbers in table give less error.
    {
      if (j == 0) continue;
      sinTable16[i] = t + j;
      float e = getError(i);
      if (e < minError)            // if less than we can update the table.
      {
        idx = j;
        minError = e;
        rv++;
        flag = true;
      }
    }
    if (flag) Serial.print('*');    // comment if you do not want see changes.
    sinTable16[i] = t + idx;
    Serial.print(sinTable16[i]);
    Serial.print(", ");
    if (i % 10 == 0) Serial.println();
  }
  Serial.println();
  Serial.println();
  test_isin_error_1(false);

  return rv;
}


void test_isin_error_1(bool show)
{
  Serial.println(__FUNCTION__);
  Serial.println("ISIN 0-3600 calls: \t");
  Serial.flush();

  float mx = 0;
  float z = 0;
  for (int i = 0; i < 3600; i++)
  {
    float a = sin(i * 0.1 * PI / 180);
    float b = isin(i * 0.1);
    float y = abs(a - b);
    z += y;
    if (mx < y)
    {
      mx = y;
      if (show)
      {
        Serial.print(i);
        Serial.print("\t");
        Serial.print(a, 6);
        Serial.print("\t");
        Serial.print(b, 6);
        Serial.print("\t");
        Serial.println(a - b, 6);
      }
    }
  }
  Serial.print("max error: ");
  Serial.println(mx, 8);
  Serial.print("avg error: ");
  Serial.println(z / 3600, 8);
  Serial.println();
  Serial.flush();
}


void loop()
{
}


// -- END OF FILE --

