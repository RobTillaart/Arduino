//
//    FILE: DAC8552_powerdown.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8552 library Arduino
//     URL: https://github.com/RobTillaart/DAC8552


#include "DAC8552.h"


//  HW SPI
DAC8552 mydac(10);

uint8_t chanA = 0;
uint8_t chanB = 1;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8552_LIB_VERSION: ");
  Serial.println(DAC8552_LIB_VERSION);

  SPI.begin();

  mydac.begin();

  mydac.setValue(chanA, 0);
  mydac.setPowerDown(chanB, DAC8552_POWERDOWN_HIGH_IMP);
}


void loop()
{
  Serial.println("Start sawtooth");
  for (uint16_t i = 0; i < 32000; i+= 100)
  {
    mydac.setValue(chanA, i);
  }

  Serial.println("Stop both DAC's for 5 seconds");
  mydac.setPowerDown(chanA, DAC8552_POWERDOWN_HIGH_IMP);
  uint32_t start = millis();
  while (millis() - start < 5000);
  mydac.setPowerDown(chanA, DAC8552_POWERDOWN_NORMAL);

  Serial.println("Continue sawtooth");
  for (uint16_t i = 32000; i < 64000; i+= 100)
  {
    mydac.setValue(chanA, i);
  }

  Serial.println("Stop both DAC's for 5 seconds");
  mydac.setPowerDown(chanA, DAC8552_POWERDOWN_HIGH_IMP);
  start = millis();
  while (millis() - start < 5000);
  mydac.setPowerDown(chanA, DAC8552_POWERDOWN_NORMAL);
}


//  -- END OF FILE --

