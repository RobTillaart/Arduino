//
//    FILE: AD8495_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD8495
//
//  show the effect of averaging 7 readings in plotter.

#include "AD8495.h"

//  Arduino UNO analog port
AD8494 mySensor(A0, 1023, 5.0);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD8495_LIB_VERSION: ");
  Serial.println(AD8495_LIB_VERSION);

  Serial.println("TC(1)\tTC(7)");
}


void loop()
{
  float temp1 = mySensor.getTemperatureC(1);
  float temp7 = mySensor.getTemperatureC(7);
  Serial.print(temp1);
  Serial.print("\t");
  Serial.print(temp7);
  Serial.println();
  delay(50);
}


//  -- END OF FILE --
