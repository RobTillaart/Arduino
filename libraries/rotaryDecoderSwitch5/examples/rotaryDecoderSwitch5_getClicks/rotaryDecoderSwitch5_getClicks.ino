//
//    FILE: rotaryDecoderSwitch5_getClicks.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/rotaryDecoderSwitch5
//
// connect up to 5 rotary encoders with a switch to 1 PCF8575.
//
//  RotaryEncoder    PCF8575      UNO R3     ESP32
//  -------------------------------------------------
//   1 pin A          IO 0
//   1 pin B          IO 1
//   1 switch         IO 2
//   2 pin A          IO 3
//   2 pin B          IO 4
//   2 switch         IO 5
//   3 pin A          IO 6
//   3 pin B          IO 7
//   3 switch         IO 8
//                    etc
//                    IO 15  free
//
//                    SDA         A4         22
//                    SCL         A5         23


#include "rotaryDecoderSwitch5.h"

rotaryDecoderSwitch5 decoder(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER_SWITCH5_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER_SWITCH5_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(5);
  decoder.readInitialState();

  //  different values for demo purpose
  for (uint8_t re = 0; re < 5; re++)
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
    for (uint8_t re = 0; re < 5; re++)
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
