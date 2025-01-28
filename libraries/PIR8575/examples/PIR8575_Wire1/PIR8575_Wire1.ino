//
//    FILE: PIR8575_Wire1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PIR8575


#include "PIR8575.h"

PIR8575 PIR(0x20, &Wire1);


void printHex(uint16_t x)
{
  if (x < 0x1000) Serial.print('0');
  if (x < 0x100)  Serial.print('0');
  if (x < 0x10)   Serial.print('0');
  Serial.println(x, HEX);
}


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PIR8575_LIB_VERSION:\t");
  Serial.println(PIR8575_LIB_VERSION);
  Serial.println();

  Wire.begin();
  PIR.begin();
}


void loop()
{
  uint16_t x = PIR.read16();
  Serial.print("Read ");
  printHex(x);
  delay(1000);
}


//  -- END OF FILE --
