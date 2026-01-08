//
//    FILE: rotaryDecoder8_test_PCF8575.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test program for the PCF8575
//     URL: https://github.com/RobTillaart/rotaryDecoder8
//
//  connect the PCF8575, no Rotary Encoders
//
//  connect PCF8575 pins alternately with 5V and GND
//  to see changes in the read16() return value.


#include "rotaryDecoder8.h"

rotaryDecoder8 decoder(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER8_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER8_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(0);
}


void loop()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(decoder.read16(), HEX);
}


//  -- END OF FILE --
