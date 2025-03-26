//    FILE: decibel_inverse.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/decibel


#include "decibel.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("DECIBEL_LIB_VERSION:\t");
  Serial.println(DECIBEL_LIB_VERSION);
  delay(100);

  float m = 0;
  float avg = 0;

  Serial.println("A\tO\tE\tMAX");
  for (float a = 0.001; a <= 1; a += 0.001)
  {
    float db = decibel(a);
    float org = inverseDecibel(db);
    //  find max error
    if (abs(org - a) > m) 
    {
      m = abs(org - a);
    }
    avg += abs(org - a);
    
    Serial.print(a, 6);
    Serial.print('\t');
    Serial.print(org, 6);
    Serial.print('\t');
    Serial.print(org - a, 6);
    Serial.print('\t');
    Serial.print(m, 6);
    Serial.println();
  }

  //  indication for average error.
  Serial.println(avg / 1000, 6);


}

void loop()
{


}

// -- END OF FILE --
