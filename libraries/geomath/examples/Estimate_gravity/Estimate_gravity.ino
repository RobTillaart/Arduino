//    FILE: Estimate_gravity.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: estimate gravity acceleration at certain latitude
//     URL: https://github.com/RobTillaart/FSR40X


#include "Arduino.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  Serial.println("LAT\tG\tGbest\tABS\tREL");
  for (int i = 0; i < 91; i++)
  {
    //  polar   = 9.8337;
    //  equator = 9.7806;
    //    float gc = 9.832185 - cos(i * PI / 180.0) * (9.832185 - 9.780327);
    //    float gs = 9.780327 + sin(i * PI / 180.0) * (9.832185 - 9.780327);
    //    float gbest = (gc + gs) / 2;

    const float Gpoles   = 9.832185;
    const float Gequator = 9.780327;
    const float Gaverage = (Gpoles + Gequator) / 2;
    const float Gdelta   = (Gpoles - Gequator) / 2;
    float phi2 = i * (PI / 180.0);
    float gbest = Gaverage + Gdelta * (sin(phi2) - cos(phi2));

    //  https://en.wikipedia.org/wiki/Gravity_of_Earth
    //  Geodetic Reference System 1980
    float equator = 9.780327;
    float phi = i * PI / 180;
    float s1 = sin(phi) * sin(phi);
    float s2 = sin(2 * phi) * sin(2 * phi);
    float g = equator * (1.0 + 0.0053024 * s1 - 0.0000058 * s2);

    Serial.print(i);
    Serial.print("\t");
    //    Serial.print(gc, 6);
    //    Serial.print("\t");
    //    Serial.print(gs, 6);
    //    Serial.print("\t");
    Serial.print(g, 6);
    Serial.print("\t");
    Serial.print(gbest, 6);
    Serial.print("\t");
    //    Serial.print(abs(g - gc), 6);
    //    Serial.print("\t");
    //    Serial.print(abs(g - gs), 6);
    //    Serial.print("\t");
    Serial.print(abs(g - gbest), 6);  //  abs error
    Serial.print("\t");
    Serial.println(abs(100 - 100 * abs(gbest / g)), 6);  //  rel error
  }
}

void loop()
{
}

// -- END OF FILE --
