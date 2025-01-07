//
//    FILE: rotaryDecoder8_demo_single.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo single direction rotary decoder.
//     URL: https://github.com/RobTillaart/rotaryDecoder8
//
// note this is used for e.g. RPM counters that are unidirectional.
//      all moves are interpreted as same direction.
//
// connect up to 8 rotary encoders to 1 PCF8575.
//
//  RotaryEncoder    PCF8575      UNO
//  --------------------------------------
//    pin A           pin 0
//    pin B           pin 1
//    ....            ....     (up to 8 RE)
//
//                    SDA         A4
//                    SCL         A5
//


#include "rotaryDecoder8.h"

rotaryDecoder8 decoder(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER8_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER8_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(8);
  decoder.readInitialState();
}


void loop()
{
  //  if one of the counters is updated, print them.
  if (decoder.updateSingle())   //  note values will only go up!
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      Serial.print("\t");
      Serial.print(decoder.getValue(i));
    }
    Serial.println();
  }

  //  other tasks...
}


//  -- END OF FILE --
