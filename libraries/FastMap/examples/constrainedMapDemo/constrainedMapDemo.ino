//
//    FILE: constrainedMap.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: demo of FastMap class ==> merge map and constrain functions
//    DATE: 2014-11-02
//     URL: 
//
// Released to the public domain
//

#include "FastMap.h"

FastMap mapper;

void setup() 
{
  Serial.begin(115200);
  Serial.print("Start constrainedMap demo\nlib version: ");
  Serial.println(FASTMAP_LIB_VERSION);
  Serial.println();

  mapper.init(0, 10, 0, 300);

  Serial.println("I\tMAP\tLCM\tUCM\tCM");
  for (int i = -5; i < 20; i++)
  {
    float a = map(i, 0, 10, 0, 300);
    float b = mapper.lowerConstrainedMap(i);
    float c = mapper.upperConstrainedMap(i);
    float d = mapper.constrainedMap(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(a);
    Serial.print("\t");
    Serial.print(b);
    Serial.print("\t");
    Serial.print(c);
    Serial.print("\t");
    Serial.println(d);
  }
  Serial.println("\ndone...");
}

void loop() 
{
}


