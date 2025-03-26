//    FILE: decibel_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: explore
//     URL: https://github.com/RobTillaart/decibel

#include "decibel.h"

uint32_t start, stop;


volatile float a = -5.0;
volatile float x, y;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = decibel(-a);
  }
  stop = micros();
  Serial.print("decibel(-a):\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(x, 6);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = decibel(0);
  }
  stop = micros();
  Serial.print("decibel(0):\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(x, 6);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = decibel(a);
  }
  stop = micros();
  Serial.print("decibel(a):\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(x, 6);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = decibelFast(a);
  }
  stop = micros();
  Serial.print("dBFast(a)\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(x, 6);
  delay(100);

  x = decibel(a);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    y = inverseDecibel(x);
  }
  stop = micros();
  Serial.print("inverse(x):\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(y, 6);
  Serial.println(x, 6);
  Serial.println(a, 6);
  delay(100);

}

void loop()
{


}

// -- END OF FILE --
