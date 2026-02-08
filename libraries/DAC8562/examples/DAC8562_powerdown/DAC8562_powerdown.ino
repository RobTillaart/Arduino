//
//    FILE: DAC8562_powerdown.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8562 library Arduino
//     URL: https://github.com/RobTillaart/DAC8562


#include "DAC8562.h"


//  select, address HW SPI
DAC8562 mydac(10);  //  uses default


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DAC8562_LIB_VERSION: ");
  Serial.println(DAC8562_LIB_VERSION);
  Serial.println();

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
  mydac.setPowerDownMode(DAC8562_POWERDOWN_HIGH_IMP);
  uint32_t start = millis();
  while (millis() - start < 5000);
  mydac.setPowerDownMode(DAC8562_POWERDOWN_NORMAL);

  Serial.println("Continue sawtooth");
  for (uint16_t i = 32000; i < 64000; i+= 100)
  {
    mydac.setValue(i);
  }

  Serial.println("Stop DAC for 5 seconds");
  mydac.setPowerDownMode(DAC8562_POWERDOWN_HIGH_IMP);
  start = millis();
  while (millis() - start < 5000);
  mydac.setPowerDownMode(DAC8562_POWERDOWN_NORMAL);
}


//  -- END OF FILE --

