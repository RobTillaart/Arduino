//
//    FILE: perm1.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2010-11-23
// PURPOSE: demo permutations
//     URL: https://github.com/RobTillaart/statHelpers
//
//
//  WARNING TAKES LONG
//  ========================================================================
//  ESP32 @ 240 MHz string length 8  ==> ~8100 milliseconds  => printing!!
//  UNO no printing string length 8  ==> ~431 milliseconds
//  UNO no printing string length 10 ==> ~38763 milliseconds


#include "statHelpers.h"

char permstring[12] = "0123456789";    //  can be made slightly longer

uint32_t start, stop;


void permutate(char * array, uint8_t n)
{
  if (n == 0)  //  end reached print the string
  {
    // Serial.println(array);      //  process permutation
    return;
  }

  for (int i = 0; i < n; i++)
  {
    // swap
    char t = array[i];
    array[i] = array[n - 1];
    array[n - 1] = t;

    // permutate substrings
    permutate(array, n - 1);

    // swap back
    t = array[i];
    array[i] = array[n - 1];
    array[n - 1] = t;
  }
}


void setup()
{
  Serial.begin(500000);
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();


  Serial.println("Will take some time..");
  Serial.print("perm1 strlen: ");
  Serial.println(strlen(permstring));

  start = millis();
  permutate(permstring, strlen(permstring));
  stop = millis();
  
  Serial.print("TIME: ");
  Serial.println(stop - start);
}


void loop()
{
}


//  -- END OF FILE --
