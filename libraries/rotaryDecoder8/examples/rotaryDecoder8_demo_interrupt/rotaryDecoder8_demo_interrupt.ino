//
//    FILE: rotaryDecoder8_demo_interrupt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo interrupt controlled rotary decoder
//     URL: https://github.com/RobTillaart/rotaryDecoder8
//
// connect up to 8 rotary encoders to 1 PCF8575.
//
//  RotaryEncoder    PCF8575      UNO R3
//  --------------------------------------
//    pin A           pin 0
//    pin B           pin 1
//    ....            ....     (up to 8 RE)
//
//                    SDA         A4
//                    SCL         A5
//
//                    INT         2
//


#include "rotaryDecoder8.h"


rotaryDecoder8 decoder(0x20);

volatile bool newTickFlag = false;


void moved()
{
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
  Serial.print("ROTARY_DECODER8_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER8_LIB_VERSION);
  Serial.println();

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, moved, FALLING);
  newTickFlag = false;

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(8);
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
    }
    Serial.println();
  }

  //  other tasks...
}


//  -- END OF FILE --
