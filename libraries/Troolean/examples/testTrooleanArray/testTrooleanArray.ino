//
//    FILE: testTrooleanArray.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test for troolean (tri state) math library for Arduino
//     URL: https://github.com/RobTillaart/Troolean


#include "Troolean.h"


// minimal array test
Troolean arr[10];
Troolean brr[5] = { true, false, unknown };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TROOLEAN_LIB_VERSION: ");
  Serial.println(TROOLEAN_LIB_VERSION);

  for (int i = 0; i < 10; i++) arr[i] = false;
  for (int i = 0; i < 10; i++)
  {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();

  for (int i = 0; i < 10; i++) arr[i] = true;
  for (int i = 0; i < 10; i++)
  {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();

  for (int i = 0; i < 10; i++) arr[i] = unknown;
  for (int i = 0; i < 10; i++)
  {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.println();
  for (int i = 0; i < 5; i++)
  {
    Serial.print(brr[i]);
    Serial.print(" ");
  }
  Serial.println(); 

  Serial.println("\ndone...");
}


void loop()
{
}


// -- END OF FILE --

