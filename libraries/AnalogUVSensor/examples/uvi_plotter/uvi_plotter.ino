//
//    FILE: uvi_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo UV sensor
//     URL: https://github.com/RobTillaart/AnalogUVSensor

//  Use the Arduino IDE -> Tools -> Serial plotter 
//  to get a graph.


#include "AnalogUVSensor.h"

AnalogUVSensor AUV;
float lastRead = 0;


void setup()
{
  Serial.begin(115200);
  //  Serial.println(__FILE__);
  //  Serial.print("ANALOG_UVSENSOR_LIB_VERSION: ");
  //  Serial.println(ANALOG_UVSENSOR_LIB_VERSION);

  AUV.begin(A0, 5.0, 1023);
  lastRead = AUV.read(5);      //  average 5 readings

  //  print the header for the plotter.
  Serial.println("UVI \tLAST \tDELTA");
}


void loop()
{
  float uvi = AUV.read(5);      //  average 5 readings
  float delta = uvi - lastRead;

  Serial.print(uvi, 1);
  Serial.print('\t');
  Serial.print(lastRead, 1);
  Serial.print('\t');
  Serial.print(delta, 1);
  Serial.print('\n');

  lastRead = uvi;
  delay(1000);
}


//  -- END OF FILE --

