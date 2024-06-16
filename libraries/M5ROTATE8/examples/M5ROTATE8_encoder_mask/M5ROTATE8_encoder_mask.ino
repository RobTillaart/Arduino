//
//    FILE: M5ROTATE8_encoder_mask.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo firmware V2 function
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "m5rotate8.h"


M5ROTATE8 MM;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("M5ROTATE8_LIB_VERSION: ");
  Serial.println(M5ROTATE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();
}


void loop()
{
  uint8_t mask = MM.getEncoderChangeMask();
  if (mask != 0)
  {
    for (int encoder = 0; encoder < 8; encoder++)
    {
      if (mask & (1 << encoder))
      {
        Serial.print("Encoder ");
        Serial.print(encoder);
        Serial.print(" moved to ");

        //  read and process encoder.
        Serial.println(MM.getAbsCounter(encoder));
      }
    }
  }
}


//  -- END OF FILE --
