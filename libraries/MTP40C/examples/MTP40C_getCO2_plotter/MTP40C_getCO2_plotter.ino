//
//    FILE: MTP40C_getCO2_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40C library
//    DATE: 2021-08-23
//     URL: https://github.com/RobTillaart/MTP40C
//
// any board that support two or more hardware serial ports
// Serial and Serial1, e.g. for MEGA, LEONARDO, MICRO, ESP32,ESP8266
// Uno, Nano or Mini will fail to compile.
//
// view e.g. with IDE plotter


#include "MTP40C.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(6, 7);

MTP40C mtp(&sws);       // use hardware Serial1 for MTP40C sensor


void setup()
{
  Serial.begin(115200);
  // Serial.println(__FILE__);
  // Serial.print("MTP40_LIB_VERSION:\t");
  // Serial.println(MTP40_LIB_VERSION);

  sws.begin(19200);
  mtp.begin(MTP40_DEFAULT_ADDRESS);            // default 0x64

  // if (mtp.begin() == false)
  // {
  //   Serial.println("could not connect!");
  //   while(1);
  // }

}


void loop()
{
  if (millis() - mtp.lastRead() >= 5000)
  {
    Serial.print(mtp.getGasConcentration());
    Serial.println();
  }
}


// -- END OF FILE --

