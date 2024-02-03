//
//    FILE: constrainedMap.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of FastMap class ==> merge map and constrain functions
//     URL: https://github.com/RobTillaart/FastMap


#include "FastMap.h"

FastMap mapper;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FASTMAP_LIB_VERSION: ");
  Serial.println(FASTMAP_LIB_VERSION);
  Serial.println();

  mapper.init(0, 10, 0, 300);

  Serial.println("I\t\tMAP\t\tLCM\t\tUCM\t\tCM");
  for (int i = -5; i < 20; i++)
  {
    float a = map(i, 0, 10, 0, 300);
    float b = mapper.lowerConstrainedMap(i);
    float c = mapper.upperConstrainedMap(i);
    float d = mapper.constrainedMap(i);
    Serial.print(i);
    Serial.print("\t\t");
    Serial.print(a);
    Serial.print("\t\t");
    Serial.print(b);
    Serial.print("\t\t");
    Serial.print(c);
    Serial.print("\t\t");
    Serial.println(d);
  }
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
