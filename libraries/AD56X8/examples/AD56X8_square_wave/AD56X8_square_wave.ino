//
//    FILE: AD56X8_square_wave.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD56X8


#include "AD56X8.h"


AD56X8 AD16_SW(9, 10, 11);  //  SW SPI

uint32_t start, stop;

int value = 0;

//  1000 == 1 kHz.
float freq = 1000;
uint32_t duration = round(1000000.0 / freq);  //  micros
uint32_t lastTime = 0;
uint32_t maxAmplitude = 32767;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD56X8_LIB_VERSION: ");
  Serial.println(AD56X8_LIB_VERSION);
  Serial.println();

  AD16_SW.begin();

  value = AD16_SW.getValue(0);
}


void loop()
{
  uint32_t now = micros();
  if (now - lastTime >= duration)
  {
    lastTime = now;
    if (value == 0) value = maxAmplitude;
    else value = 0;
    AD16_SW.setValue(0, value);
  }

}


//  -- END OF FILE --
