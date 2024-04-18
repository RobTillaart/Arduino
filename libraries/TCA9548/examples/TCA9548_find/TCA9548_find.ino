//
//    FILE: TCA9548_find.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TCA9548 I2C multiplexer
//     URL: https://github.com/RobTillaart/TCA9548


#include "TCA9548.h"

TCA9548 MP(0x70);

uint8_t channels = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9548_LIB_VERSION: ");
  Serial.println(TCA9548_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (MP.begin() == false)
  {
    Serial.println("COULD NOT CONNECT TO MULTIPLEXER");
  }

  channels = MP.channelCount();
  Serial.print("CHAN:\t");
  Serial.println(MP.channelCount());

  //  adjust address range to your needs.
  for (uint8_t addr = 60; addr < 70; addr++)
  {
    if (addr % 10 == 0) Serial.println();
    Serial.print(addr);
    Serial.print("\t");
    Serial.print(MP.find(addr), BIN);
    Serial.println();
  }

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
