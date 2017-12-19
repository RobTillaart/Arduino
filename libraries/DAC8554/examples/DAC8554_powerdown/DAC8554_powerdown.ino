//
//    FILE: DAC8554_powerdown.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8554 library Arduino
// VERSION: 0.1.0
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/DAC8554
// HISTORY:
//   0.1.0: 2017-12-19 experimental version - NOT tested - from data sheet
//
// Released to the public domain
//

#include <SPI.h>
#include "DAC8554.h"

//  HW SPI
DAC8554 DAC;

uint8_t chanA = 0;
uint8_t chanB = 1;
uint8_t chanC = 2;
uint8_t chanD = 3;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(DAC8554_LIB_VERSION);
  DAC.begin();

  DAC.setValue(chanA, 0);
  DAC.setPowerDown(chanB, DAC8554_POWERDOWN_HIGH_IMP);
  DAC.setPowerDown(chanC, DAC8554_POWERDOWN_100K);
  DAC.setPowerDown(chanD, DAC8554_POWERDOWN_1K);
}

void loop()
{
  Serial.println("Start sawtooth");
  for (uint16_t i = 0; i < 32000; i+= 100)
  {
    DAC.setValue(chanA, i);
  }

  Serial.println("Stop DAC for 5 seconds");
  DAC.setPowerDown(chanA, DAC8554_POWERDOWN_HIGH_IMP);
  uint32_t start = millis();
  while (millis() - start < 5000);
  DAC.setPowerDown(chanA, DAC8554_POWERDOWN_NORMAL);

  Serial.println("Continue sawtooth");
  for (uint16_t i = 32000; i < 64000; i+= 100)
  {
    DAC.setValue(chanA, i);
  }

  Serial.println("Stop DAC for 5 seconds");
  DAC.setPowerDown(chanA, DAC8554_POWERDOWN_HIGH_IMP);
  start = millis();
  while (millis() - start < 5000);
  DAC.setPowerDown(chanA, DAC8554_POWERDOWN_NORMAL);
}

// END OF FILE