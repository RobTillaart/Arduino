//
//    FILE: MTP40_scanner.ino
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

MTP40C mtp(&sws);       // optional use hardware Serial1 for MTP40C sensor


void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println(__FILE__);

  Serial.print("\tMTP40_LIB_VERSION:\t");
  Serial.println(MTP40_LIB_VERSION);
  Serial.println();

  Serial.println("\tMTP40 ADDRESS SCANNER 0.1.1");

  sws.begin(19200);
  mtp.setTimeout(50);

  uint32_t start = millis();
  full_scan();
  Serial.print("Time ms:\t");
  Serial.println(millis() - start);

  start = millis();
  detect_scan();
  Serial.print("Time ms:\t");
  Serial.println(millis() - start);

  Serial.println("\ndone");
}


void loop()
{
}


void full_scan()
{
  Serial.println();
  uint8_t found = 0;

  for (int addr = 0; addr < 248; addr += 16)
  {
    Serial.println();
    Serial.print("0x");
    if (addr < 0x10) Serial.print('0');
    Serial.print(addr, HEX);
    for (uint8_t i = 0; i < 16; i++)
    {
      Serial.print("\t");
      bool b = mtp.begin(addr + i);
      Serial.print(b);
      if (b) found++;
    }
  }
  Serial.println();
  Serial.println();
  Serial.print("Devices:\t");
  Serial.println(found);
}


void detect_scan()
{
  Serial.println();
  uint8_t found = 0;
  for (int addr = 0; addr < 248; addr++)
  {
    bool b = mtp.begin(addr);
    if (b)
    {
      Serial.print("Address:\t0x");
      if (addr < 0x10) Serial.print('0');
      Serial.print(addr, HEX);
      Serial.print("\t");
      found++;
    }
  }
  Serial.println();
  Serial.print("Devices:\t");
  Serial.println(found);
}


// -- END OF FILE --

