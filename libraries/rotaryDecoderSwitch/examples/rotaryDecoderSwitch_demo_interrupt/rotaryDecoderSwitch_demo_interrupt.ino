//
//    FILE: rotaryDecoderSwitch_demo_interrupt.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-17
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/rotaryDecoderSwitch
//
// connect up to 2 rotary encoders with a switch to 1 PCF8574.
//
//  RotaryEncoder    PCF8574      UNO
//  --------------------------------------
//   1 pin A          pin 0
//   1 pin B          pin 1
//   1 switch         pin 2
//                    pin 3   (reserved)
//   2 pin A          pin 4
//   2 pin B          pin 5
//   2 switch         pin 6
//                    pin 7   (reserved)
//
//                    SDA         A4
//                    SCL         A5
//


#include "rotaryDecoderSwitch.h"

rotaryDecoderSwitch decoder(0x20);

volatile bool flag = false;


void moved()
{
  flag = true;
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER_SWITCH_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER_SWITCH_LIB_VERSION);

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, moved, FALLING);
  flag = false;

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(2);
  decoder.readInitialState();
}


void loop()
{
  if (flag)
  {
    decoder.update();
    flag = false;
    for (uint8_t i = 0; i < 2; i++)
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

