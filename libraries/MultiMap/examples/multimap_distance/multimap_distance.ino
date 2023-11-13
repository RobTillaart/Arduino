//
//    FILE: multimap_distance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-04-09
//
//  example simulates the lookup graph of a distance sensor 


#include "MultiMap.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();
  delay(100);

  for (int i = 80; i < 512; i++)
  {
    float distance = sharp2cm(i);
//    Serial.print('\t');
//    Serial.print(i);
//    Serial.print('\t');
    Serial.println(distance, 1);
  }
  Serial.println("Done...");
}


void loop()
{
}


//  for a sharp distance range finder
float sharp2cm(int val)
{
  //  out[] holds the distances in cm
  float out[] = {150, 140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20};

  //  in[] holds the measured analogRead() values for that distance
  float in[]  = { 90, 97, 105, 113, 124, 134, 147, 164, 185, 218, 255, 317, 408, 506};

  float dist = multiMap<float>(val, in, out, 14);
  return dist;
}


//  -- END OF FILE --

