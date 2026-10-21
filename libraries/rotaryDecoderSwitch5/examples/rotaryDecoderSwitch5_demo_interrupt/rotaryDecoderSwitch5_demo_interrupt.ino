//
//    FILE: rotaryDecoderSwitch5_demo_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo using interrupts to handle pulses per tick.
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
//
//                    INT          2          2
//



#include "rotaryDecoderSwitch5.h"

rotaryDecoderSwitch5 decoder(0x20);

volatile bool newTickFlag = false;


void moved()
{
  //  one should not read the PCF8575 in the interrupt routine.
  //  adjust if mechanical rotary encoder gives e.g. 4 pulses per tick
  //  see interrupt section readme.md
  //  see issue #5
  const int IRQ_PULSES_PER_TICK = 1;
  static int count = 0;
  count++;
  if (count == IRQ_PULSES_PER_TICK)
  {
    count = 0;
    newTickFlag = true;
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER_SWITCH5_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER_SWITCH5_LIB_VERSION);
  Serial.println();

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, moved, FALLING);
  newTickFlag = false;

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(5);
  decoder.readInitialState();
}


void loop()
{
  if (newTickFlag)
  {
    decoder.update();
    newTickFlag = false;
    Serial.print(millis());
    for (uint8_t i = 0; i < 8; i++)
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

