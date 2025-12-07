//
//    FILE: AnalogPin_volts.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: example sketch convert to volts
//     URL: https://github.com/RobTillaart/AnalogPin
//
//  view in plotter
//  change mode with 0, 1, 2
//  change noise level with + -
//  change smooth alpha with * /

#include "AnalogPin.h"

AnalogPin INA(A0);

//  adjust to your ADC (5 V 1023 steps == UNO R3)
const float VOLTS_PER_STEP = (5.0 / 1023);
float volts;

uint32_t lastTime = 0;
uint32_t interval = 10;

uint8_t mode = 0;
uint8_t noise = 3;
uint8_t alpha = 16;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ANALOGPIN_LIB_VERSION: ");
  Serial.println(ANALOGPIN_LIB_VERSION);
  Serial.println();

  //  configure the analog input
  INA.setNoiseThreshold(noise);
  INA.setSmoothWeight(alpha);

}


void loop()
{
  if (millis() - lastTime >= interval)
  {
    lastTime += interval;
    switch (mode)
    {
      default:
      case 0:
        volts = INA.readSmoothed();
        break;
      case 1:
        volts = INA.read();
        break;
      case 2:
        volts = INA.read(true);  //  twice
        break;
    }
    volts = INA.readSmoothed() * VOLTS_PER_STEP;
    Serial.println(volts, 3);
  }

  if (Serial.available())
  {
    char c = Serial.read();
    if (c == 'R') //  R = reset
    {
      mode = 0;
      noise = 3;
      alpha = 16;
    }
    if (c == '0') mode = 0;
    if (c == '1') mode = 1;
    if (c == '2') mode = 2;

    if (c == '+') if (noise < 15) noise++;
    if (c == '-') if (noise > 0)  noise--;

    if (c == '*') if (alpha < 31) alpha++;
    if (c == '/') if (alpha > 0)  alpha--;

    INA.setNoiseThreshold(noise);
    INA.setSmoothWeight(alpha);
  }
}


//  -- END OF FILE --
