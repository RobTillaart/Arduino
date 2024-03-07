//
//    FILE: MAX520_demo_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MAX520
//     URL: https://github.com/RobTillaart/MAX520


#include "MAX520.h"

//  adjust address if needed
//  MAX520 0x20..0x27
//  MAX521 0x20..0x23
MAX520 mx(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX520_LIB_VERSION:\t");
  Serial.println(MAX520_LIB_VERSION);
  Serial.println();

  Wire.begin();

  mx.begin();

  //  all channels should read 0.
  for (int ch = 0; ch < mx.getChannels(); ch++)
  {
    Serial.print(ch);
    Serial.print("\t");
    Serial.println(mx.read(ch));
  }
}


void loop()
{
  for (int value = 0; value < 256; value++)
  {
    for (int ch = 0; ch < mx.getChannels(); ch++)
    {
      mx.write(ch, value);
      delay(250);
      Serial.print(mx.read(ch));
      Serial.print("\t");
    }
    Serial.println();
  }
}


//  -- END OF FILE --
