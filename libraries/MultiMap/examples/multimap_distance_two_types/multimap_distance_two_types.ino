//
//    FILE: multimap_distance_two_types.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2023-11-12
//
//  example simulates the lookup graph of a distance sensor


#include "MultiMap.h"

uint32_t start, stop;

volatile float dist;

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
    float distance1 = sharp2cm1(i);
    float distance2 = sharp2cm2(i);
    float distance3 = sharp2cm3(i);
    Serial.print(i);
    Serial.print('\t');
    Serial.print(distance1, 2);
    Serial.print('\t');
    Serial.print(distance2, 2);
    Serial.print('\t');
    Serial.println(distance3, 2);
  }
  Serial.println();
  delay(1000);


  start = micros();
  for (int i = 100; i < 500; i++)
  {
    dist = sharp2cm1(i);
  }
  stop = micros();
  Serial.print("TIME1: ");
  Serial.println((stop - start) / 400.0, 2);
  delay(100);


  start = micros();
  for (int i = 100; i < 500; i++)
  {
    dist = sharp2cm2(i);
  }
  stop = micros();
  Serial.print("TIME2: ");
  Serial.println((stop - start) / 400.0, 2);
  delay(100);


  start = micros();
  for (int i = 100; i < 500; i++)
  {
    dist = sharp2cm3(i);
  }
  stop = micros();
  Serial.print("TIME3: ");
  Serial.println((stop - start) / 400.0, 2);
  delay(100);

  Serial.println("\nDone...");
}


void loop()
{
}


// for a sharp distance range finder
float sharp2cm1(int val)
{
  // out[] holds the distances in cm
  float out[] = {150, 140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20};

  // in[] holds the measured analogRead() values for that distance
  float in[]  = { 90, 97, 105, 113, 124, 134, 147, 164, 185, 218, 255, 317, 408, 506};

  float dist = multiMap<float>(val, in, out, 14);
  return dist;
}


// for a sharp distance range finder
float sharp2cm2(int val)
{
  // out[] holds the distances in cm
  float out[] = {150, 140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20};

  // in[] holds the measured analogRead() values for that distance
  int in[]  = { 90, 97, 105, 113, 124, 134, 147, 164, 185, 218, 255, 317, 408, 506};

  float dist = multiMap<int, float>(val, in, out, 14);
  return dist;
}


// for a sharp distance range finder
float sharp2cm3(int val)
{
  // out[] holds the distances in cm
  float out[] = {150, 140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20};

  // in[] holds the measured analogRead() values for that distance
  int in[]  = { 90, 97, 105, 113, 124, 134, 147, 164, 185, 218, 255, 317, 408, 506};

  float dist = multiMapBS<int, float>(val, in, out, 14);
  return dist;
}


// -- END OF FILE --
