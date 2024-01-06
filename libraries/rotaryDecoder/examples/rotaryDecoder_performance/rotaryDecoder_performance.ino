//
//    FILE: rotaryDecoder_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-08
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/rotaryDecoder
//
// connect up to 4 rotary encoders to 1 PCF8574.
//
//  RotaryEncoder    PCF8574      UNO
//  --------------------------------------
//    pin A           pin 0
//    pin B           pin 1
//    ....            ....     (up to 4 RE)
//
//                    SDA         A4
//                    SCL         A5
//


#include "rotaryDecoder.h"

rotaryDecoder decoder(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(4);
  decoder.readInitialState();

  for (uint32_t clock = 100000; clock <= 800000; clock += 100000)
  {
    Wire.setClock(clock);
    uint32_t start = micros();
    for (int i = 0; i < 10; i++)
    {
      decoder.update();
    }
    uint32_t stop = micros();
    Serial.print(clock);
    Serial.print("\t");
    Serial.print((stop - start) * 0.1);
    Serial.print("\n");
  }
}


void loop()
{
}


//  -- END OF FILE --

