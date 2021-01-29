#pragma once
//
//    FILE: DAC8554.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8554 SPI Digital Analog Convertor  
// VERSION: 0.2.1
// HISTORY: See DAC8554.cpp
//     URL: https://github.com/RobTillaart/DAC8554
//

#include "SPI.h"

#define DAC8554_LIB_VERSION           (F("0.2.1"))


#define DAC8554_POWERDOWN_NORMAL     0x00
#define DAC8554_POWERDOWN_1K         0x40
#define DAC8554_POWERDOWN_100K       0x80
#define DAC8554_POWERDOWN_HIGH_IMP   0xC0


class DAC8554
{
public:
  // hardware SPI constructor
  DAC8554(uint8_t slaveSelect, uint8_t address = 0);  // address is 0,1,2,3

  // software SPI constructor
  DAC8554(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect, uint8_t address = 0);

  void     begin();

  void     bufferValue(uint8_t channel, uint16_t value);
  void     setValue(uint8_t channel, uint16_t value);
  uint16_t getValue(uint8_t channel);
  //writes the value to the channel but does not affect buffered ones
  void     setSingleValue(uint8_t channel, uint16_t value);

  void     bufferPowerDown(uint8_t channel, uint8_t powerDownMode);
  void     setPowerDown(uint8_t channel, uint8_t powerDownMode);
  uint8_t  getPowerDownMode(uint8_t channel);
  void     setSinglePowerDown(uint8_t channel, uint8_t powerDownMode);

  // write all buffers to all(up to 4) 8554's channel's
  void     broadcastBuffer();
  // write value to all(up to 4) 8554's channel's
  void     broadcastValue(uint16_t value);
  // write powerDownMode to all 8554's channel's
  void     broadcastPowerDown(uint8_t powerDownMode);

private:
  uint8_t  _spiData;
  uint8_t  _spiClock;
  uint8_t  _slaveSelect;
  bool     _hwSPI;
  uint8_t  _address;

  uint16_t _value[4];     // holdes last written / buffered value per channel
  uint8_t  _register[4];  // holds powerDownMode per channel

  void     writeDevice(uint8_t configRegister, uint16_t value);
  void     swSPI_transfer(uint8_t value);
};

// -- END OF FILE --
