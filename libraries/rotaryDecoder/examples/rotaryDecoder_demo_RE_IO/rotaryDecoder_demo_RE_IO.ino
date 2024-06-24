//
//    FILE: rotaryDecoder_demo_RE_IO.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-02-13
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/rotaryDecoder
//
//  example configuration
//    connect one rotary encoders
//    connect multiple switches
//    connect one line to the other end of the switches to enable them 
//    connect a buzzer
//
//  RotaryEncoder     PCF8574      UNO
//  --------------------------------------
//   pin A            pin 0
//   pin B            pin 1
//   switch           pin 2
//   switch           pin 3
//   switch           pin 4
//   enable line      pin 5
//   buzzer           pin 6
//   switch           pin 7
//
//                    SDA         A4
//                    SCL         A5
//


#include "rotaryDecoder.h"

rotaryDecoder decoder(0x39);  //  0x39 = 57


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);

  //  only one rotary encoder
  decoder.begin(1);
  decoder.readInitialState();

  //  other lines are switches (INPUT)
  decoder.write1(2, LOW);
  decoder.write1(3, LOW);
  decoder.write1(4, LOW);
  decoder.write1(7, LOW);

  //  enable/disable switches
  //  HIGH == switches enabled
  decoder.write1(5, HIGH);

  //  line 6 == buzzer
  decoder.write1(6, LOW);
}


void loop()
{
  //  if one of the lines is updated, print them.
  if (decoder.update())
  {
    Serial.print("\t");
    Serial.print(decoder.getValue(0));
    Serial.print("\t");
    Serial.print(decoder.read1(2));
    Serial.print("\t");
    Serial.print(decoder.read1(3));
    Serial.print("\t");
    Serial.print(decoder.read1(4));
    Serial.print("\t");
    Serial.print(decoder.read1(5));
    Serial.print("\t");
    Serial.print(decoder.read1(6));
    Serial.print("\t");
    Serial.print(decoder.read1(7));
    Serial.println();
  }

  //  other tasks...
}


//  -- END OF FILE --
