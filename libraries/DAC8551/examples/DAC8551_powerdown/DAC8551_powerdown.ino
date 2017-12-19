//
//    FILE: DAC8551_powerdown.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8551 library Arduino
// VERSION: 0.1.0
// HISTORY:
//     URL:
//
// Released to the public domain
//

#include <SPI.h>
#include "DAC8551.h"

// HW SPI
DAC8551 DAC;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(DAC8551_LIB_VERSION);
  DAC.begin();
}

void loop()
{
  Serial.println("Start sawtooth");
  for (uint16_t i = 0; i < 32000; i+= 100)
  {
    DAC.setValue(i);
  }

  Serial.println("Stop DAC for 5 seconds");
  DAC.setPowerDown(DAC8551_POWERDOWN_HIGH_IMP);
  uint32_t start = millis();
  while (millis() - start < 5000);
  DAC.setPowerDown(DAC8551_POWERDOWN_NORMAL);

  Serial.println("Continue sawtooth");
  for (uint16_t i = 32000; i < 64000; i+= 100)
  {
    DAC.setValue(i);
  }

  Serial.println("Stop DAC for 5 seconds");
  DAC.setPowerDown(DAC8551_POWERDOWN_HIGH_IMP);
  start = millis();
  while (millis() - start < 5000);
  DAC.setPowerDown(DAC8551_POWERDOWN_NORMAL);
}

// END OF FILE