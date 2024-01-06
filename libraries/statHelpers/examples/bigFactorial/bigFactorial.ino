//
//    FILE: bigFactorial.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-08-05
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"
#include "printHelpers.h"  //  to print large numbers ...


uint32_t start, duration1, duration2, duration3;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();

  uint32_t m    = 10000001;
  double   mant = 0;
  uint32_t expo = 0;

  for (uint32_t i = 1; i < m; i *= 10)
  {
    start = millis();
    bigFactorial(i, mant, expo);
    duration1 = millis() - start;
    Serial.print(i);
    Serial.print('\t');
    Serial.print(mant, 5);
    Serial.print('e');
    Serial.print(expo);
    Serial.print('\t');
    Serial.print(duration1);
    Serial.println();
  }
  Serial.println("-----");
  Serial.println();

  m    = 5;
  mant = 0;
  expo = 0;
  double f = 24;
  bool flag = false;
  while (flag == false)
  {
    f *= m++;
    while (f > 10)
    {
      f /= 10;
      expo++;
      if (expo > 0xFFFFFFF0)
      {
        flag = true;
      }
    }
  }
  mant = f;

  Serial.println();
  Serial.print(m);
  Serial.print('\t');
  Serial.print(mant, 15);
  Serial.print('e');
  Serial.print(expo);
  Serial.println();


  Serial.println("\n Done...");
}


void loop()
{
}


//  -- END OF FILE --

