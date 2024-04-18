//
//    FILE: TCA9548_demo.ino
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
    Serial.println("COULD NOT CONNECT");
  }

  channels = MP.channelCount();
  Serial.print("CHAN:\t");
  Serial.println(MP.channelCount());

  Serial.print("MASK:\t");
  Serial.println(MP.getChannelMask(), HEX);
  for (int chan = 0; chan < channels; chan++)
  {
    Serial.print("PRE:\t");
    Serial.print(MP.isEnabled(chan));
    MP.enableChannel(chan);
    Serial.print("\t");
    Serial.println(MP.isEnabled(chan));
    delay(100);
  }
  Serial.println();
  MP.setChannelMask(0x00);

  Serial.print("MASK:\t");
  Serial.println(MP.getChannelMask(), HEX);
  for (int chan = 0; chan < channels; chan++)
  {
    MP.enableChannel(chan);

    Serial.print("MASK:\t");
    Serial.println(MP.getChannelMask(), HEX);
    delay(100);
  }
  for (int chan = 0; chan < channels; chan++)
  {
    MP.disableChannel(chan);
    Serial.print("MASK:\t");
    Serial.println(MP.getChannelMask(), HEX);
    delay(100);
  }
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

