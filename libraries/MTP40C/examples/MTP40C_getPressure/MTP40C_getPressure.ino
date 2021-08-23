//
//    FILE: MTP40C_getCO2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo of MTP40C library
//    DATE: 2021-08-21
//     URL: https://github.com/RobTillaart/MTP40C
//
// any board that support two or more hardware serial ports 
// Serial and Serial1, e.g. for MEGA, LEONARDO, MICRO, ESP32,ESP8266
// Uno, Nano or Mini will fail to compile.


#include "MTP40C.h"

MTP40C mtp(&Serial1);

int lines = 10;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MTP40C_LIB_VERSION:\t");
  Serial.println(MTP40C_LIB_VERSION);

  Serial1.begin(19200);
  if (mtp.begin() == false)
  {
    Serial.println("Could not connect!");
    while(1);
  }
}


void loop()
{
  if (lines == 10)
  {
    lines = 0;
    Serial.println("\nTIME\tPRESSURE (mbar)");
  }

  if (millis() - mtp.lastRead() >= 5000)
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(mtp.getAirPressure(), 1);
    Serial.println();
    lines++;
  }
}


// -- END OF FILE --
