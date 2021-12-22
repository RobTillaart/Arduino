//
//    FILE: MTP40C_getCO2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40C library
//    DATE: 2021-08-21
//     URL: https://github.com/RobTillaart/MTP40C
//
// any board that support two or more hardware serial ports
// Serial and Serial1, e.g. for MEGA, LEONARDO, MICRO, ESP32,ESP8266
// Uno, Nano or Mini will fail to compile.


#include "MTP40C.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(6, 7);

MTP40C mtp(&sws);
// MTP40C mtp(&Serial1);

int lines = 10;


void setup()
{
  Serial.begin(115200);
  // Serial.println(__FILE__);
  // Serial.print("MTP40_LIB_VERSION:\t");
  // Serial.println(MTP40_LIB_VERSION);

  sws.begin(19200);
  mtp.begin();  // default 0x64

  // if (mtp.begin() == false)
  // {
  //   Serial.println("could not connect!");
  //   while(1);
  // }

}


void loop()
{
  if (lines == 10)
  {
    lines = 0;
    Serial.println("\nTIME\tCO2 LEVEL");
  }

  if (millis() - mtp.lastRead() >= 5000)
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(mtp.getGasConcentration());
    Serial.println();
    lines++;
  }
}


// -- END OF FILE --

