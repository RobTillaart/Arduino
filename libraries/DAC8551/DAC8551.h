#pragma once
//
//    FILE: DAC8551.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8551 SPI Digital Analog Convertor  
//          could work with DAC8550, not tested
// VERSION: 0.1.3
// HISTORY: See DAC8551.cpp
//     URL: https://github.com/RobTillaart/DAC8551
//

#include <SPI.h>

#define DAC8551_POWERDOWN_NORMAL   0
#define DAC8551_POWERDOWN_1K       1
#define DAC8551_POWERDOWN_100K     2
#define DAC8551_POWERDOWN_HIGH_IMP 3

#define DAC8551_LIB_VERSION "0.1.3"

class DAC8551
{
public:
  DAC8551();
  DAC8551(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);

  void begin();

  void setValue(uint16_t value);
  uint16_t getValue();

  void setPowerDown(uint8_t powerDownMode);
  uint8_t getPowerDownMode();

private:
  uint8_t _spiData;
  uint8_t _spiClock;
  uint8_t _slaveSelect;
  bool    _hwSPI;
  uint8_t _value;
  uint8_t _register;

  void updateDevice();
  void swSPI_transfer(uint8_t value);
};

// -- END OF FILE --
