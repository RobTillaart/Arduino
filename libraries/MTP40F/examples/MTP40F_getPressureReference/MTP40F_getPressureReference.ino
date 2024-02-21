//
//    FILE: MTP40F_getPressureReference.ino
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

int lines = 10;
uint32_t lastRead = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MTP40F_LIB_VERSION:\t");
  Serial.println(MTP40F_LIB_VERSION);

  sws.begin(9600);
  mtp.begin();
}


void loop()
{
  if (lines == 10)
  {
    lines = 0;
    Serial.println("\nTIME\tPRESSURE (mbar)");
  }

  if (millis() - lastRead >= 1000)
  {
    lastRead = millis();
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(mtp.getAirPressureReference(), 1);
    Serial.println();
    lines++;
  }
}


//  -- END OF FILE --
