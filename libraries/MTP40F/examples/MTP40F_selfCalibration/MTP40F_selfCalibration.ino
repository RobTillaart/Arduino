//
//    FILE: MTP40F_selfCalibration.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40F library
//     URL: https://github.com/RobTillaart/MTP40F
//
//  any board that support two or more hardware serial ports
//  Serial and Serial1, e.g. for MEGA, LEONARDO, MICRO, ESP32, ESP8266
//  Uno, Nano or Mini will fail to compile.
//
//  SCHEMA example SoftwareSerial sws(7, 6);
//              UNO                     MTP40F
//        +---------------+        +---------------+
//        |               |        |               |
//        |          +5V  |--------| 1 VIN         |
//        |          GND  |--------| 2 GND         |
//        |               |        | 3             |
//        |               |        | 4             |
//        |               |        |               |
//        |               |        | 5             |
//        |         RX 6  |<-------| 6 TX          |
//        |         TX 7  |------->| 7 RX          |
//        |               |        | 8             |
//        |               |        | 9             |
//        |               |        |               |
//        +---------------+        +---------------+
//


#include "MTP40F.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(7, 6);
MTP40F mtp(&sws);
// MTP40F mtp(&Serial1);

uint32_t start;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.print("MTP40F_LIB_VERSION:\t");
  Serial.println(MTP40F_LIB_VERSION);

  sws.begin(9600);
  mtp.begin();

  Serial.print("STAT:\t");
  Serial.println(mtp.getSelfCalibrationStatus());
  delay(100);
//  Serial.print("OPEN:\t");
//  Serial.println(mtp.openSelfCalibration());
//  delay(100);
//  Serial.print("STAT:\t");
//  Serial.println(mtp.getSelfCalibrationStatus());
//  delay(100);
//  Serial.print("CLOSE:\t");
//  Serial.println(mtp.closeSelfCalibration());
//  delay(100);
//  Serial.print("STAT:\t");
//  Serial.println(mtp.getSelfCalibrationStatus());
//  delay(100);
//  Serial.print("OPEN:\t");
//  Serial.println(mtp.openSelfCalibration());
//  delay(100);
//  Serial.print("STAT:\t");
//  Serial.println(mtp.getSelfCalibrationStatus());
//  delay(100);
//
//  Serial.println();
//
//  Serial.print("GET_HRS:\t");
//  uint16_t hrs = mtp.getSelfCalibrationHours();
//  Serial.println(hrs);
//  delay(100);
//
//  if (hrs > 720) hrs = 23;
//  Serial.print("SET_HRS:\t");
//  Serial.println(mtp.setSelfCalibrationHours(hrs + 1));
//  delay(100);
  Serial.print("GET_HRS:\t");
  Serial.println(mtp.getSelfCalibrationHours());
  delay(100);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
