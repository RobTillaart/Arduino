//
//    FILE: DAC8552.cpp 
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8552 SPI Digital Analog Convertor
// VERSION: 0.2.1
//     URL: https://github.com/RobTillaart/DAC8552
//
// HISTORY:
//  0.1.0: 2017-12-14  initial version
//  0.1.1: 2017-12-19  fix begin() bug
//  0.1.2  2020-04-06  minor refactor, readme.md
//  0.1.3  2020-06-07  fix library.json
//  0.2.0  2020-12-18  add arduino-ci + unit test
//                     add slave select pin for HW constructor
//  0.2.1  2021-06-02  compile ESP32 + fix for channel B


#include "DAC8552.h"


#define MAXVOLTAGE      5.0
#define MAXVALUE        0xFFFF

DAC8552::DAC8552(uint8_t slaveSelect)
{
  _hwSPI = true;
  _slaveSelect = slaveSelect;
}


DAC8552::DAC8552(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect)
{
  _hwSPI = false;
  _spiData = spiData;
  _spiClock = spiClock;
  _slaveSelect = slaveSelect;
}


// initializes the SPI
// and sets internal state
void DAC8552::begin()
{
  pinMode(_slaveSelect, OUTPUT);
  digitalWrite(_slaveSelect, HIGH);

  if(_hwSPI)
  {
    SPI.begin();
    delay(1);
  }
  else
  {
    pinMode(_spiData, OUTPUT);
    pinMode(_spiClock, OUTPUT);
    digitalWrite(_spiData, LOW);
    digitalWrite(_spiClock, LOW);
  }

  _value[0] = 0;
  _value[1] = 0;
  _register[0] = 0x00;
  _register[1] = 0x40;
}


// channel = 0, 1, 2, 3 depending on type
// value = 0..65535
void DAC8552::bufferValue(uint8_t channel, uint16_t value)
{
  _value[channel] = value;
  updateDevice(channel, false);
}


// channel = 0, 1, 2, 3 depending on type
// value = 0..65535
void DAC8552::setValue(uint8_t channel, uint16_t value)
{
  _value[channel] = value;
  updateDevice(channel, true);
}


// channel = 0, 1, 2, 3 depending on type
// returns 0..65535
uint16_t DAC8552::getValue(uint8_t channel)
{
  return _value[channel];
}


void DAC8552::bufferPowerDown(uint8_t channel, uint8_t powerDownMode)
{
  _register[channel] &= 0xFC;
  _register[channel] |= (powerDownMode & 0x03);
  updateDevice(channel, false);
}


void DAC8552::setPowerDown(uint8_t channel, uint8_t powerDownMode)
{
  _register[channel] &= 0xFC;
  _register[channel] |= (powerDownMode & 0x03);
  updateDevice(channel, true);
}


uint8_t DAC8552::getPowerDownMode(uint8_t channel)
{
  return _register[channel] & 0x03;
}


// channel = 0, 1, 2, 3 depending on type
// direct = true  ==> write buffers to both channel A and channel B
// direct = false ==> buffer value
void DAC8552::updateDevice(uint8_t channel, bool directWrite)
{
  uint8_t configRegister = _register[channel];
  if (directWrite) configRegister |= 0x30;

  if (_hwSPI)
  {
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1));
    digitalWrite(_slaveSelect, LOW);
    SPI.transfer(configRegister);
    SPI.transfer(_value[channel] >> 8);
    SPI.transfer(_value[channel] & 0xFF);
    digitalWrite(_slaveSelect, HIGH);
    SPI.endTransaction();
  }
  else // Software SPI
  {
    digitalWrite(_slaveSelect, LOW);
    swSPI_transfer(configRegister);
    swSPI_transfer(_value[channel] >> 8);
    swSPI_transfer(_value[channel] & 0xFF);
    digitalWrite(_slaveSelect, HIGH);
  }
}


// simple one mode version
void DAC8552::swSPI_transfer(uint8_t value)
{
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(_spiData,(value & mask) != 0);
    digitalWrite(_spiClock, HIGH);
    digitalWrite(_spiClock, LOW);
  }
}

// -- END OF FILE --
