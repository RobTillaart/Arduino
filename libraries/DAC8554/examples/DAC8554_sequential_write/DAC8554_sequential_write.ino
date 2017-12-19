//
//    FILE: DAC8554_sequential_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8554 library Arduino
// VERSION: 0.1.0
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/DAC8554
// HISTORY:
//   0.1.0: 2017-12-19 initial version
//
// Released to the public domain
//

#include <SPI.h>
#include "DAC8554.h"

// HW SPI
DAC8554 DAC;

uint32_t lastTime = 0;
uint16_t state = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(DAC8554_LIB_VERSION);
  DAC.begin();
}

void loop()
{
  uint8_t chanA = 0;
  uint8_t chanB = 1;
  uint8_t chanC = 2;
  uint8_t chanD = 3;


  // opposite square waves by setting A and B sequentially
  // first buffer one value and then set the other.
  // freq 10 Hz
  if (millis() - lastTime > 100)
  {
    lastTime = millis();
    if (state == 0)
    {
      state = 1;
      DAC.setValue(chanA, 0);
      DAC.setValue(chanB, 20000);
      DAC.setValue(chanC, 40000);
      DAC.setValue(chanD, 60000);
    }
    else
    {
      state = 0;
      DAC.setValue(chanD, 0);
      DAC.setValue(chanC, 20000);
      DAC.setValue(chanB, 40000);
      DAC.setValue(chanA, 60000);
    }
  }
}

// END OF FILE