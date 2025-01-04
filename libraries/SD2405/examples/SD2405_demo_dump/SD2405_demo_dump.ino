//
//    FILE: SD2405_demo_dump.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic read function
//     URL: https://github.com/RobTillaart/SD2405


#include "SD2405.h"


SD2405 rtc;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SD2405_LIB_VERSION: ");
  Serial.println(SD2405_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (rtc.begin() != SD2405_OK)
  {
    Serial.println("could not connect, check wires etc");
    while (1);
  }

  for (int r = 0x00; r < 0x20; r++)
  {
    if (r < 0x10) Serial.print(0);
    Serial.print(r, HEX);
    Serial.print(' ');
  }
  Serial.println();
  for (int r = 0x00; r < 0x20; r++)
  {
    Serial.print("---");
  }
  Serial.println();

}


void loop()
{
  for (int r = 0x00; r < 0x20; r++)
  {
    int val = rtc.readRegister(r);
    if (val < 0x10) Serial.print(0);
    Serial.print(val, HEX);
    Serial.print(' ');
  }
  Serial.println();

  delay(2000);
}


//  --  END OF FILE  --
