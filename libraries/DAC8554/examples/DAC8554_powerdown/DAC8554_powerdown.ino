//
//    FILE: DAC8554_powerdown.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8554 library Arduino
//     URL: https://github.com/RobTillaart/Arduino/DAC8554


#include "DAC8554.h"


//  HW SPI
DAC8554 mydac(10);

uint8_t chanA = 0;
uint8_t chanB = 1;
uint8_t chanC = 2;
uint8_t chanD = 3;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8554_LIB_VERSION: ");
  Serial.println(DAC8554_LIB_VERSION);

  SPI.begin();

  mydac.begin();

  mydac.setValue(chanA, 0);
  mydac.setPowerDown(chanB, DAC8554_POWERDOWN_HIGH_IMP);
  mydac.setPowerDown(chanC, DAC8554_POWERDOWN_100K);
  mydac.setPowerDown(chanD, DAC8554_POWERDOWN_1K);
}


void loop()
{
  Serial.println("Start sawtooth");
  for (uint16_t i = 0; i < 32000; i+= 100)
  {
    mydac.setValue(chanA, i);
  }

  Serial.println("Stop DAC for 5 seconds");
  mydac.setPowerDown(chanA, DAC8554_POWERDOWN_HIGH_IMP);
  uint32_t start = millis();
  while (millis() - start < 5000);
  mydac.setPowerDown(chanA, DAC8554_POWERDOWN_NORMAL);

  Serial.println("Continue sawtooth");
  for (uint16_t i = 32000; i < 64000; i+= 100)
  {
    mydac.setValue(chanA, i);
  }

  Serial.println("Stop DAC for 5 seconds");
  mydac.setPowerDown(chanA, DAC8554_POWERDOWN_HIGH_IMP);
  start = millis();
  while (millis() - start < 5000);
  mydac.setPowerDown(chanA, DAC8554_POWERDOWN_NORMAL);
}


//  -- END OF FILE --

