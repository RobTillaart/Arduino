//
//    FILE: AD8495_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD8495


#include "AD8495.h"

//  Arduino UNO analog port
AD8495 mySensor(A0, 1023, 5.0);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD8495_LIB_VERSION: ");
  Serial.println(AD8495_LIB_VERSION);

  Serial.println("\nPREC:\t");
  Serial.println(mySensor.getPrecision());
  Serial.println("VOLT:\t");
  Serial.println(mySensor.getVoltage());
  Serial.println();
}


void loop()
{
  float temp = mySensor.getTemperatureC(5);
  Serial.println("TEMP:\t");
  Serial.print(temp);
  Serial.println();
  delay(2000);
}


//  -- END OF FILE --
