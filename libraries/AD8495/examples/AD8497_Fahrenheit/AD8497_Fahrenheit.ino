//
//    FILE: AD8497_Fahrenheit.ino
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

  Serial.println("TC(5)\tTF(5)");
}


void loop()
{
  float tempC = mySensor.getTemperatureC(5);
  float tempF = mySensor.getTemperatureF(5);
  Serial.print(tempC);
  Serial.print("\t");
  Serial.print(tempF);
  Serial.println();
  delay(50);
}


//  -- END OF FILE --
