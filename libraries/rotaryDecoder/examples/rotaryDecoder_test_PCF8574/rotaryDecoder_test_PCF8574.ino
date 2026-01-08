//
//    FILE: rotaryDecoder_test_PCF8574.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test program for the PCF8574
//     URL: https://github.com/RobTillaart/rotaryDecoder
//
//  connect the PCF8574, no Rotary Encoders
//
//  connect PCF8574 pins alternately with 5V and GND
//  to see changes in the read8() return value.


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
  decoder.begin(0);
}


void loop()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(decoder.read8(), BIN);
}


//  -- END OF FILE --

