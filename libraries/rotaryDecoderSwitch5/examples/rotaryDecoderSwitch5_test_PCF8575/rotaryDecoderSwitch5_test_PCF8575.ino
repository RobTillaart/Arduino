//
//    FILE: rotaryDecoderSwitch_test_PCF8575.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-13
// PURPOSE: test program for the PCF8575
//     URL: https://github.com/RobTillaart/rotaryDecoderSwitch5
//
//  connect the PCF8575, no Rotary Encoders
//
//  connect PCF8575 pins alternately with 5V and GND
//  to see changes in the read8() return value.


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
  decoder.begin(0);
}


void loop()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(decoder.read16(), BIN);
}


//  -- END OF FILE --
