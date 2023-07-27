//
//    FILE: MTP40F_setPressureReference.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MTP40F library
//     URL: https://github.com/RobTillaart/MTP40F
//
//  any board that support two or more hardware serial ports
//  Serial and Serial1, e.g. for MEGA, LEONARDO, MICRO, ESP32,ESP8266
//  Uno, Nano or Mini will fail to compile.


#include "MTP40F.h"
#include "SoftwareSerial.h"

SoftwareSerial sws(7, 6);
MTP40F mtp(&sws);
// MTP40F mtp(&Serial1);

int lines = 10;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MTP40F_LIB_VERSION:\t");
  Serial.println(MTP40F_LIB_VERSION);

  sws.begin(9600);
  mtp.begin();

  Serial.print("990:\t");
  Serial.print(mtp.setAirPressureReference(990));
  Serial.print("\t");
  delay(5000);
  Serial.println(mtp.getAirPressureReference());
  delay(5000);


  Serial.print("1013:\t");
  Serial.print(mtp.setAirPressureReference(1013));
  Serial.print("\t");
  delay(5000);
  Serial.println(mtp.getAirPressureReference());
  delay(5000);
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
    Serial.print(mtp.getAirPressureReference());
    Serial.println();
    lines++;
  }
}


//  -- END OF FILE --
