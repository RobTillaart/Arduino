//
//    FILE: PCA9549_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PCA9543 I2C multiplexer
//     URL: https://github.com/RobTillaart/PCA9549


#include "PCA9549.h"

PCA9549 PCA(0x70);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9549_LIB_VERSION: ");
  Serial.println(PCA9549_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (PCA.begin() == false)
  {
    Serial.println("COULD NOT CONNECT");
  }

  Serial.print("MASK:\t");
  Serial.println(PCA.getChannelMask(), HEX);
  for (int chan = 0; chan < 8; chan++)
  {
    Serial.print("PRE:\t");
    Serial.print(PCA.isEnabled(chan));
    PCA.enableChannel(chan);
    Serial.print("\t");
    Serial.println(PCA.isEnabled(chan));
    delay(100);
  }
  Serial.println();
  PCA.setChannelMask(0x00);

  Serial.print("MASK:\t");
  Serial.println(PCA.getChannelMask(), HEX);
  for (int chan = 0; chan < 8; chan++)
  {
    PCA.enableChannel(chan);

    Serial.print("MASK:\t");
    Serial.println(PCA.getChannelMask(), HEX);
    delay(100);
  }
  for (int chan = 0; chan < 8; chan++)
  {
    PCA.disableChannel(chan);
    Serial.print("MASK:\t");
    Serial.println(PCA.getChannelMask(), HEX);
    delay(100);
  }
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

