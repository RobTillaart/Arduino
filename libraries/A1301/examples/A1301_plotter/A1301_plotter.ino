//
//    FILE: A1301_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo A1301 A1302 magnetometer.
//     URL: https://github.com/RobTillaart/A1301
//
//  to be used with Arduino Serial plotter


#include "A1301.h"


A1301 mm(A0);

uint32_t lastTime = 0;

float raw, current, prev = 0;

void setup()
{
  Serial.begin(115200);
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print("A1301_LIB_VERSION: ");
  //  Serial.println(A1301_LIB_VERSION);

  mm.begin(5000, 1023);

  Serial.println("RAW\tGAUSS\tDELTA");
}


void loop()
{
  if (millis() - lastTime >= 50)  //  == 20 SAMPLES PER SECOND
  {
    lastTime = millis();
    raw      = mm.raw();
    current  = mm.read();
    prev     = mm.prevGauss();

    Serial.print(raw);
    Serial.print("\t");
    Serial.print(current);
    Serial.print("\t");
    Serial.print(current - prev);
    Serial.print("\n");
  }
}


//  -- END OF FILE --
