//
//    FILE: AD8494_offset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD8495


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

  Serial.println("\nPREC:\t");
  Serial.println(mySensor.getPrecision());
  Serial.println("VOLT:\t");
  Serial.println(mySensor.getVoltage());
  Serial.println();
}


void loop()
{
  mySensor.setOffset(0);
  float temp = mySensor.getTemperatureC(5);
  Serial.println();
  Serial.print("TEMP:\t");
  Serial.print(temp);
  Serial.println();

  mySensor.setOffset(-0.8);
  temp = mySensor.getTemperatureC(5);
  Serial.print("OFFSET:\t");
  Serial.print(temp);
  Serial.println();
  delay(2000);
}


//  -- END OF FILE --
