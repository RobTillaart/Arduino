//
//    FILE: float16_test_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16
//     URL: https://github.com/RobTillaart/float16


//  show storage needs (fixed in 0.3.0)

#include "float16.h"

float16 temperature[10];   //  pointers + object are stored.
uint16_t temp2[10];        //  only raw data is stored.


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FLOAT16_LIB_VERSION: ");
  Serial.println(FLOAT16_LIB_VERSION);
  Serial.println();


  //  simulate temperature sensor with random numbers
  for (uint32_t n = 0; n < 10; n++)
  {
    temperature[n] = (random(1000) - 300) * 0.01;
    temp2[n] = temperature[n].getBinary();
  }
  Serial.println();


  float average = 0;
  for (uint32_t n = 0; n < 10; n++)
  {
    Serial.print(n);
    Serial.print("\t");
    Serial.print(temperature[n].toDouble());
    Serial.println();
    average += temperature[n].toDouble();
  }
  Serial.print("\t");
  Serial.println(average * 0.01);
  Serial.println();


  average = 0;
  for (uint32_t n = 0; n < 10; n++)
  {
    float16 f16;
    f16.setBinary(temp2[n]);
    Serial.print(n);
    Serial.print("\t");
    Serial.print(f16.toDouble());
    Serial.println();
    average += f16.toDouble();
  }
  Serial.print("\t");
  Serial.println(average * 0.01);
  Serial.println();


  Serial.print("SIZE: ");
  Serial.println(sizeof(temperature));
  Serial.print("SIZE: ");
  Serial.println(sizeof(temp2));

  Serial.println("\ndone");
}


void loop()
{
}


//  -- END OF FILE --
