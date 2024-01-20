//
//    FILE: DAC8552_sequential_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8552 library Arduino
//     URL: https://github.com/RobTillaart/DAC8552


#include "DAC8552.h"


//  HW SPI
DAC8532 mydac(10);

uint32_t lastTime = 0;
uint16_t state = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8552_LIB_VERSION: ");
  Serial.println(DAC8552_LIB_VERSION);

  SPI.begin();

  mydac.begin();
}


void loop()
{
  uint8_t chanA = 0;
  uint8_t chanB = 1;

  //  opposite square waves by setting A and B simultaneous
  //  first buffer one value and then set the other.
  //  freq 10 Hz
  if (millis() - lastTime > 100)
  {
    lastTime = millis();
    if (state == 0)
    {
      state = 1;
      mydac.setValue(chanA, 0);
      mydac.setValue(chanB, 65535);
    }
    else
    {
      state = 0;
      mydac.setValue(chanB, 0);
      mydac.setValue(chanA, 65535);
    }
  }
}


//  -- END OF FILE --

