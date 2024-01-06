//
//    FILE: rotaryDecoderSwitch_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-17
// PURPOSE: measure I2C performance
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


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ROTARY_DECODER_SWITCH_LIB_VERSION:\t");
  Serial.println(ROTARY_DECODER_SWITCH_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  decoder.begin(2);
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

