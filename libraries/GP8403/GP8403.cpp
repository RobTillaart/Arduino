//
//    FILE: GP8403.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-01-30
// PURPOSE: Arduino library for GP8403, I2C 12 bit two channel DAC.
//     URL: https://github.com/RobTillaart/GP8403


#include "GP8403.h"


//  REGISTER      DESCRIPTION            BITS     NOTES
//  0x00          GP8403_??                8
//  0x01          GP8403_CONFIGURATION     8
//  0x02          GP8403_DAC0_LOW          8      upper 4 bits!
//  0x03          GP8403_DAC0_HIGH         8
//  0x04          GP8403_DAC1_LOW          8      upper 4 bits!
//  0x05          GP8403_DAC1_HIGH         8


constexpr uint8_t GP8403_REG_CONFIG = 0x01;   //   8 bits
constexpr uint8_t GP8403_REG_DAC0 = 0x02;     //  16 bits
constexpr uint8_t GP8403_REG_DAC1 = 0x04;     //  16 bits



GP8403::GP8403(uint8_t address, TwoWire *wire)
{
  _address  = address;
  _wire     = wire;
  _maxValue = 0xFFF;
  _channels = 2;
  _value[0] = 0;
  _value[1] = 0;
  _range    = 0;
  _error    = GP8403_OK;
}

//  range as parameter?
bool GP8403::begin()
{
  if (! isConnected())
  {
    //  _error = ?
    return false;
  }
  // reset variables
  _error = GP8403_OK;
  setRange(5);
  return true;
}

bool GP8403::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t GP8403::getAddress()
{
  return _address;
}

bool GP8403::setRange(uint8_t range)
{
  uint8_t reg = GP8403_REG_CONFIG;
  //  default 5V.
  uint8_t value = 0x00;
  if (range == 10) value = 0x11;

  _error = _writeRegister8(reg, value);
  if (_error != GP8403_OK) return false;
  if (range == 10) _range = 10;
  else             _range = 5;
  return true;
}

uint8_t GP8403::getRange()
{
  return _range;
}

uint8_t GP8403::channels()
{
  return _channels;
}

uint16_t GP8403::maxValue()
{
  return 0x0FFF;
}


/////////////////////////////////////////////
//
//  CORE
//
bool GP8403::setValue(uint8_t channel, uint16_t value)
{
  if (channel >= _channels) return false;
  if (value   >= _maxValue) return false;

  uint8_t reg = GP8403_REG_DAC0;
  if (channel == 1) reg = GP8403_REG_DAC1;
  _error = _writeRegister16(reg, value << 4);
  if (_error != GP8403_OK) return false;

  _value[channel] = value;
  return true;
}

uint16_t GP8403::getValue(uint8_t channel)
{
  if (channel >= _channels) return 0;
  return _value[channel];
}

bool GP8403::increment(uint8_t channel)
{
  if (channel >= _channels) return false;
  if (_value[channel] >= _maxValue) return false;
  uint16_t val = _value[channel] + 1;
  return setValue(val, channel);
}

bool GP8403::decrement(uint8_t channel)
{
  if (channel >= _channels) return false;
  if (_value[channel] == 0) return false;
  uint16_t val = _value[channel] - 1;
  return setValue(val, channel);
}

bool GP8403::setPercentage(uint8_t channel, float percentage)
{
  if (percentage < 0.0f)   percentage =   0.0f;
  if (percentage > 100.0f) percentage = 100.0f;
  //  optimize if zero?
  return setValue(percentage * (_maxValue * 0.01f), channel);
}

float GP8403::getPercentage(uint8_t channel)
{
  if (channel >= _channels) return 0.0f;
  //  optimize if zero?
  return _value[channel] * (100.0f / _maxValue);
}


/////////////////////////////////////////////
//
//  DEBUG
//
int GP8403::getLastError()
{
  int e = _error;
  _error = GP8403_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PROTECTED
//
int GP8403::_writeRegister8(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  return _wire->endTransmission();
}


int GP8403::_writeRegister16(uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value & 0xFF);
  _wire->write(value >> 8);
  return _wire->endTransmission();
}


//  -- END OF FILE --

