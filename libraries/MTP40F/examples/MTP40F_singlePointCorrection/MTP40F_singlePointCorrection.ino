//
//    FILE: MTP40F_singlePointCorrection.ino
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

  sws.begin(19200);
  mtp.begin();

  Serial.println("Set CO2 level to: 400-2000");
  Serial.setTimeout(10000);           //  default is 1000 which is rather small.
  float spc = Serial.parseFloat();    //  reads until carriage return
  Serial.println(spc, 1);

  bool valid = mtp.setSinglePointCorrection(spc);
  if (valid)
  {
    start = millis();
    uint8_t cnt = 0;
    while (mtp.getSinglePointCorrectionReady() == false)
    {
      delay(1000);
      Serial.print('.');
      cnt++;
      if (cnt == 50)
      {
        Serial.println();
        cnt = 0;
      }
      if (millis() - start > 600000UL)  //  600 seconds = 10 minutes
      {
        Serial.println();
        Serial.println("took > 10 minutes, something went wrong?");
        break;
      }
    }
  }
  else
  {
    Serial.println("could not set value");
  }
  Serial.println();
  Serial.print("TIME: \t");
  Serial.println(millis() - start);
  Serial.println("\ndone");
}


void loop()
{
}


//  -- END OF FILE --
