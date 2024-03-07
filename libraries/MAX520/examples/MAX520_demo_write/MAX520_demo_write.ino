//
//    FILE: MAX520_demo_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MAX520 write(array)
//     URL: https://github.com/RobTillaart/MAX520


#include "MAX520.h"

//  adjust address if needed
//  MAX520 0x20..0x27
//  MAX521 0x20..0x23
MAX520 mx(0x20);

uint8_t values[4] = { 0, 85, 170, 255 };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX520_LIB_VERSION:\t");
  Serial.println(MAX520_LIB_VERSION);
  Serial.println();

  Wire.begin();

  mx.begin();

  mx.write(values);
  for (int ch = 0; ch < mx.getChannels(); ch++)
  {
    Serial.print(mx.read(ch));
    Serial.print("\t");
  }
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
