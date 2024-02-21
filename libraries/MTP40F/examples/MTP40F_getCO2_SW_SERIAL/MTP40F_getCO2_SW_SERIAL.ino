//
//    FILE: MTP40F_getCO2_SW_SERIAL.ino
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

int lines = 10;


void setup()
{
  // DEBUG SERIAL
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MTP40F_LIB_VERSION:\t");
  Serial.println(MTP40F_LIB_VERSION);

  // SERIAL OF MTP40F SENSOR
  sws.begin(9600);
  if ( mtp.begin() == false)
  {
    Serial.println("could not connect!");
    while (1);
  }
}


void loop()
{
  if (lines == 10)
  {
    lines = 0;
    Serial.println("\nTIME\tCO2 LEVEL");
  }

  if (millis() - mtp.lastRead() >= 2500)
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(mtp.getGasConcentration());
    Serial.println();
    lines++;
  }
}


//  -- END OF FILE --
