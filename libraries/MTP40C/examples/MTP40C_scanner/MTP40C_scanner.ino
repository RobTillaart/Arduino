//
//    FILE: MTP40C_scanner.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo of MTP40C library
//    DATE: 2021-08-21
//     URL: https://github.com/RobTillaart/MTP40C
//
// any board that support two or more hardware serial ports
// Serial and Serial1, e.g. for MEGA, LEONARDO, MICRO, ESP32,ESP8266
// Uno, Nano or Mini will fail to compile.


#include "MTP40C.h"

MTP40C mtp(&Serial1);


void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.println(__FILE__);

  Serial.print("MTP40C_LIB_VERSION:\t");
  Serial.println(MTP40C_LIB_VERSION);
  Serial.println();

  Serial.println("\tMTP40C ADDRESS SCANNER 0.1.0");

  Serial1.begin(19200);
  mtp.setTimeout(50);
  for (int addr = 0; addr < 248; addr += 16)
  {
    Serial.println();
    Serial.print("0x");
    if (addr < 0x10) Serial.print('0');
    Serial.print(addr, HEX);
    for (uint8_t i = 0; i < 16; i++)
    {
      Serial.print("\t");
      Serial.print(mtp.begin(addr + i));
    }
  }
  Serial.println();

  Serial.println("\ndone");
}


void loop()
{
}


// -- END OF FILE --
