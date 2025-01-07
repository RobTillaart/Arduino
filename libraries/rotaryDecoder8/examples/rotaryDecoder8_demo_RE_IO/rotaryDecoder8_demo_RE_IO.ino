//
//    FILE: rotaryDecoder8_demo_RE_IO.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/rotaryDecoder8
//
//  example configuration
//    connect one rotary encoders
//    connect multiple switches
//    connect one line to the other end of the switches to enable them
//    connect a buzzer
//
//  RotaryEncoder     PCF8575      UNO
//  --------------------------------------
//   pin A            pin 0
//   pin B            pin 1
//   switch           pin 2
//   switch           pin 3
//   switch           pin 4
//   enable line      pin 5
//   buzzer           pin 6
//   switch           pin 7
//   etc
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
    Serial.print(decoder.getValue(0));  // uses pin 0, 1

    for (int n = 2; n < 16; n++)
    {
      Serial.print("\t");
      Serial.print(decoder.read1(n));
    }
    Serial.println();
  }

  //  other tasks...
}


//  -- END OF FILE --
