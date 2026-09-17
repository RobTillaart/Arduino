//
//    FILE: rotaryDecoder_getClicks.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/rotaryDecoder
//
// connect up to 4 rotary encoders to 1 PCF8574.
//
//  RotaryEncoder    PCF8574      UNO R3
//  --------------------------------------
//    pin A           pin 0
//    pin B           pin 1
//    ....            ....     (up to 4 RE)
//
//                    SDA         A4
//                    SCL         A5
//


#include "rotaryDecoder.h"

rotaryDecoder decoder(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(4);
  decoder.readInitialState();

  //  different values for demo purpose
  for (uint8_t re = 0; re < 4; re++)
  {
    decoder.setStepsPerClick(re, re + 1);
  }
  Serial.println("/setup()");
}


void loop()
{
  if (decoder.checkChange())
  {
    decoder.update();
    for (uint8_t re = 0; re < 4; re++)
    {
      Serial.print(re);
      Serial.print("\t");
      Serial.print(decoder.getValue(re));
      Serial.print("\t");
      Serial.print(decoder.getClicks(re));
      Serial.println();
    }
    Serial.println();
  }

  //  other tasks...
}


//  -- END OF FILE --
