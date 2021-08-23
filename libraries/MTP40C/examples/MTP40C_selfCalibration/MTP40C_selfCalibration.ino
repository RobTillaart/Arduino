//
//    FILE: MTP40C_selfCalibration.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo of MTP40C library
//    DATE: 2021-08-23
//     URL: https://github.com/RobTillaart/MTP40C
//
// any board that support two or more hardware serial ports
// Serial and Serial1, e.g. for MEGA, LEONARDO, MICRO, ESP32,ESP8266
// Uno, Nano or Mini will fail to compile.


#include "MTP40C.h"

MTP40C mtp(&Serial1);

uint32_t start;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.print("MTP40C_LIB_VERSION:\t");
  Serial.println(MTP40C_LIB_VERSION);

  Serial1.begin(19200);
  mtp.begin(MTP40C_DEFAULT_ADDRESS);

  Serial.print("STAT:\t");
  Serial.println(mtp.getSelfCalibrationStatus());
  Serial.print("OPEN:\t");
  Serial.println(mtp.openSelfCalibration());
  Serial.print("STAT:\t");
  Serial.println(mtp.getSelfCalibrationStatus());
  Serial.print("CLOSE:\t");
  Serial.println(mtp.closeSelfCalibration());
  Serial.print("STAT:\t");
  Serial.println(mtp.getSelfCalibrationStatus());
  Serial.print("OPEN:\t");
  Serial.println(mtp.openSelfCalibration());
  Serial.println();

  Serial.print("GET_HRS:\t");
  uint16_t hrs = mtp.getSelfCalibrationHours();
  Serial.println(hrs);

  if (hrs > 720) hrs = 23;
  Serial.print("SET_HRS:\t");
  Serial.println(mtp.setSelfCalibrationHours(hrs + 1));
  Serial.print("GET_HRS:\t");
  Serial.println(mtp.getSelfCalibrationHours());

  Serial.println("\ndone...");
}


void loop()
{
}


// -- END OF FILE --
