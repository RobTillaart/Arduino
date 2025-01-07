//
//    FILE: rotaryDecoder8_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/rotaryDecoder8
//
// connect up to 8 rotary encoders to 1 PCF8575.
//
//  RotaryEncoder    PCF8578      UNO
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
    delay(100);
  }
}


void loop()
{
}


//  -- END OF FILE --
