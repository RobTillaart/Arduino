//    FILE: cascading_potentiometers.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-05
// PURPOSE: demo, calculates values for two cascaded potentiometers
//     URL: https://github.com/RobTillaart/AD524X/issues/26
//
//  experimental
//  precision is as good as the smallest potentiometer.
//  math needs actual LSB and include Rwiper (TODO).
//

#include "Arduino.h"


uint32_t start, stop;

float LSB_A = 1e6 / 255.0;  //  1 M Ohm
float LSB_B = 1e4 / 255.0;  //  10 K Ohm
float R = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  //  find settings for all R's in steps of pot LSB_B
  //  LSB_B iso 40 would be more exact but gives "no nice numbers"
  for (uint32_t r = 0; r <= 1000000; r += 40)
  {
    search(r);
  }

}


void loop()
{
}


//
//  searches optimal positions for pot A and pot B
//  simplified math, ignores Rwiper
//
void search(uint32_t value)
{
  uint32_t t = value;
  int a = t / LSB_A;
  t -= a * LSB_A;
  int b = round(t / LSB_B);
  R = a * LSB_A + b * LSB_B;

  Serial.print(value);           //  requested R
  Serial.print('\t');
  Serial.print(a);               //  position pot A
  Serial.print('\t');
  Serial.print(b);               //  position pot B
  Serial.print('\t');
  Serial.print(R);               //  effecive R
  Serial.print('\t');
  Serial.print(abs(R - value));  //  absolute error
  Serial.print('\t');
  Serial.print(100 * abs(R - value) / value);  //  percentage relative error
  Serial.println();
}


//
//  prints all possible values
//  simplified math, ignores Rwiper
//
void printTable()
{
  for (int a = 0; a < 256; a += 2)
  {
    R = a * LSB_A;
    for (int b = 0; b < 256; b++)
    {
      Serial.print(a);
      Serial.print('\t');
      Serial.print(b);
      Serial.print('\t');
      Serial.print(R);
      Serial.println();
      R += LSB_B;
    }
  }
}

//  -- END OF FILE --
