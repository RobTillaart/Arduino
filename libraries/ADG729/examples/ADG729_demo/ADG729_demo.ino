//
//    FILE: ADG729_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo ADG729 I2C multiplexer
//     URL: https://github.com/RobTillaart/ADG729


#include "ADG729.h"


ADG729 MP(0x4C);  //  0x4C..0x4F
uint8_t channels = 0;
uint8_t selected = 0;


uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADG729_LIB_VERSION: ");
  Serial.println(ADG729_LIB_VERSION);
  Serial.println();

  Wire.begin();
  //  initialize multiplexer
  if (MP.begin() == false)
  {
    Serial.println("Multiplexer error");
  }
  channels = MP.channelCount();

  selected = 0;
}


void loop()
{
  if ((millis() - lastTime) >= 5000)
  {
    lastTime = millis();

    selected++;
    if (selected >= MP.channelCount()) selected = 0;

    MP.selectChannel(selected);
    Serial.println(selected);
  }
}


//  -- END OF FILE --
