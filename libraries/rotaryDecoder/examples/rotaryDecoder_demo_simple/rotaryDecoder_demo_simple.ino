//
//    FILE: rotaryDecoder_demo_simple.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-08
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/rotaryDecoder
//
// connect up to 4 rotary encoders to 1 PCF8574.
//
//  RotaryEncoder    PCF8574      UNO
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
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(4);
  decoder.readInitialState();
}


void loop()
{
  //  if one of the counters is updated, print them.
  if (decoder.update())
  {
    for (uint8_t i = 0; i < 4; i++)
    {
      Serial.print("\t");
      Serial.print(decoder.getValue(i));
    }
    Serial.println();
  }

  //  other tasks...
}


//  -- END OF FILE --

