//
//    FILE: discomfortIndex_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Temperature


#include "temperature.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TEMPERATURE_LIB_VERSION: ");
  Serial.println(TEMPERATURE_LIB_VERSION);
  Serial.println();

/*
  for (int RH = 10; RH < 100; RH += 10)
  {
    for (int TC = 10; TC <= 50; TC += 5)
    {
      float DI = discomfortIndex(TC, RH);
      float TT = DI2Celsius(DI, RH);

      Serial.print(RH);
      Serial.print('\t');
      Serial.print(TC);
      Serial.print('\t');
      Serial.print(DI, 1);
      Serial.print('\t');
      Serial.print(TT - TC, 1);
      Serial.println();
    }
    Serial.println();
  }
*/

  //  print MATRIX
  Serial.print("    RH\t");
  for (int RH = 10; RH < 100; RH += 5)
  {
    Serial.print(RH);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println("TC");

  for (int TC = 10; TC <= 50; TC += 5)
  {
    Serial.print(TC);
    Serial.print('\t');
    for (int RH = 10; RH < 100; RH += 5)
    {
      float DI = discomfortIndex(TC, RH);
      Serial.print(DI, 1);
      Serial.print('\t');
    }
    Serial.println();
  }
  Serial.println();

  Serial.print("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
