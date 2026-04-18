//    FILE: Estimate_gravity.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: estimate gravity acceleration at certain latitude
//     URL: https://github.com/RobTillaart/FSR40X


#include "Arduino.h"


void setup() 
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  Serial.println("LAT\tG");
  for (int i = 0; i < 91; i++)
  {
    //  polar   = 9.8337;
    //  equator = 9.7806;
    
    float g = 9.7806 + sin(i * PI/180.0) * (9.8337 - 9.7806);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(g, 4);
  }
}

void loop()
{
}

// -- END OF FILE --
