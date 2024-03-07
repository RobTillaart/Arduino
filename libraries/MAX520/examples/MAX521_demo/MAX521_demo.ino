//
//    FILE: MAX521_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MAX521
//     URL: https://github.com/RobTillaart/MAX520


#include "MAX520.h"

//  adjust address if needed
//  MAX520 0x20..0x27
//  MAX521 0x20..0x23
MAX521 mx;  //  uses default address


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX520_LIB_VERSION:\t");
  Serial.println(MAX520_LIB_VERSION);
  Serial.println();

  Wire.begin();

  mx.begin();

}


void loop()
{
  for (int ch = 0; ch < mx.getChannels(); ch++)
  {
    for (int value = 0; value < 256; value++)
    {
      mx.write(ch, value);
      delay(100);
      Serial.println(mx.read(ch));
    }
  }
}


//  -- END OF FILE --

