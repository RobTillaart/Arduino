//
//    FILE: MTP40F_getCO2_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40F library
//     URL: https://github.com/RobTillaart/MTP40F
//
//  any board that support two or more hardware serial ports
//  Serial and Serial1, e.g. for MEGA, LEONARDO, MICRO, ESP32,ESP8266
//  Uno, Nano or Mini will fail to compile.
//
//  view e.g. with IDE plotter


#include "MTP40F.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(7, 6);

MTP40F mtp(&sws);       // use hardware Serial1 for MTP40C sensor


void setup()
{
  Serial.begin(115200);
  // Serial.println(__FILE__);
  // Serial.print("MTP40F_LIB_VERSION:\t");
  // Serial.println(MTP40F_LIB_VERSION);

  sws.begin(9600);
  mtp.begin();
}


void loop()
{
  if (millis() - mtp.lastRead() >= 5000)
  {
    Serial.print(mtp.getGasConcentration());
    Serial.println();
  }
}


//  -- END OF FILE --
