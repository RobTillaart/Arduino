//
//    FILE: DAC8554_same_time_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8554 library Arduino with hardware SPI
//     URL: https://github.com/RobTillaart/Arduino/DAC8554


#include "DAC8554.h"


//  HW SPI
DAC8554 mydac(10);

uint32_t lastTime = 0;
uint16_t state = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8554_LIB_VERSION: ");
  Serial.println(DAC8554_LIB_VERSION);

  SPI.begin();

  mydac.begin();
}


void loop()
{
  uint8_t chanA = 0;
  uint8_t chanB = 1;
  uint8_t chanC = 2;
  uint8_t chanD = 3;

  //  opposite square waves by setting 4 channels simultaneous
  //  first buffer three values and then set the last.
  //  freq 10 Hz
  if (millis() - lastTime > 100)
  {
    lastTime = millis();
    if (state == 0)
    {
      state = 1;
      mydac.bufferValue(chanA, 0);
      mydac.bufferValue(chanB, 20000);
      mydac.bufferValue(chanC, 40000);
      mydac.setValue(chanD, 60000);
    }
    else
    {
      state = 0;
      mydac.bufferValue(chanD, 0);
      mydac.bufferValue(chanC, 20000);
      mydac.bufferValue(chanB, 40000);
      mydac.setValue(chanA, 60000);
    }
  }
}


//  -- END OF FILE --

