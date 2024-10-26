//
//    FILE: DAC8560_powerdown.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8560 library Arduino
//     URL: https://github.com/RobTillaart/DAC8560


#include "DAC8560.h"


//  select, address HW SPI
DAC8560 mydac(10);  //  uses default


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8560_LIB_VERSION: ");
  Serial.println(DAC8560_LIB_VERSION);

  SPI.begin();

  mydac.begin();
}


void loop()
{
  Serial.println("Start sawtooth");
  for (uint16_t i = 0; i < 32000; i+= 100)
  {
    mydac.setValue(i);
  }

  Serial.println("Stop DAC for 5 seconds");
  mydac.setPowerDownMode(DAC8560_POWERDOWN_HIGH_IMP);
  uint32_t start = millis();
  while (millis() - start < 5000);
  mydac.setPowerDownMode(DAC8560_POWERDOWN_NORMAL);

  Serial.println("Continue sawtooth");
  for (uint16_t i = 32000; i < 64000; i+= 100)
  {
    mydac.setValue(i);
  }

  Serial.println("Stop DAC for 5 seconds");
  mydac.setPowerDownMode(DAC8560_POWERDOWN_HIGH_IMP);
  start = millis();
  while (millis() - start < 5000);
  mydac.setPowerDownMode(DAC8560_POWERDOWN_NORMAL);
}


//  -- END OF FILE --

