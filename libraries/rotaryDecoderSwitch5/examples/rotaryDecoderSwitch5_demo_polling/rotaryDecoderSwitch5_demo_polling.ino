//
//    FILE: rotaryDecoderSwitch5_demo_polling.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-13
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/rotaryDecoderSwitch5
//
// connect up to 5 rotary encoders with a switch to 1 PCF8575.
//
//  RotaryEncoder    PCF8575      UNO
//  --------------------------------------
//   1 pin A          pin 0
//   1 pin B          pin 1
//   1 switch         pin 2
//   2 pin A          pin 3
//   2 pin B          pin 4
//   2 switch         pin 5
//   3 pin A          pin 6
//   3 pin B          pin 7
//   3 switch         pin 8
//                    etc
//                    pin 15  free
//
//                    SDA         A4
//                    SCL         A5
//


#include "rotaryDecoderSwitch5.h"

rotaryDecoderSwitch5 decoder(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER_SWITCH5_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER_SWITCH5_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(5);
  decoder.readInitialState();
}


void loop()
{
  if (decoder.checkChange())
  {
    decoder.update();
    for (uint8_t i = 0; i < 5; i++)
    {
      Serial.print("\t");
      Serial.print(decoder.getValue(i));
      Serial.print("\t");
      Serial.print(decoder.isKeyPressed(i));
    }
    Serial.println();
  }

  //  other tasks...
}


//  -- END OF FILE --

