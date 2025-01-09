//
//    FILE: PCA9698.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-06
// VERSION: 0.1.0
// PURPOSE: Arduino library for the PCA9698 - I2C, 40 channel IO expander.
//     URL: https://github.com/RobTillaart/PCA9698_RT


#include "PCA9698.h"


//  REGISTERS & FLAGS
#define PCA9698_AUTO_INCR      0x80
#define PCA9698_REG_INPUT      0x00
#define PCA9698_REG_OUTPUT     0x08
#define PCA9698_REG_POLARITY   0x10
#define PCA9698_REG_CONFIG     0x18
#define PCA9698_REG_INT_MASK   0x20

//  COMMANDS
#define PCA9698_DEVICEID            0xF9
//  ALL BANKS
#define PCA9698_OUTPUT_CONFIG       0x28   //  7.4.6,  fig 18 + 20  P28+30
#define PCA9698_ALL_BANK_CONTROL    0x29   //  7.4.7,  fig 18 + 20  P28+30
#define PCA9698_MODE_SELECTION      0x2A   //  7.4.8,  fig 18 + 20  P28+30



PCA9698::PCA9698(const uint8_t deviceAddress, TwoWire *wire)
: _address {deviceAddress}, _wire {wire}
{}


bool PCA9698::begin()
{
  if (! isConnected()) return false;
  return true;
}


bool PCA9698::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


//
//  DATA_IO
//
uint8_t PCA9698::read8(uint8_t bank, uint8_t & bitmask)
{
  if (bank > 5)
  {
    _error = PCA9698_BANK_ERROR;
    return _error;
  }
  uint8_t command = PCA9698_REG_INPUT | bank;
  _wire->beginTransmission(_address);
  _wire->write(command);
  if (_wire->endTransmission() != 0)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  bitmask = _wire->read();
  _error = PCA9698_OK;
  return _error;
}


uint8_t PCA9698::write8(uint8_t bank, uint8_t bitmask)
{
  if (bank > 5)
  {
    _error = PCA9698_BANK_ERROR;
    return _error;
  }
  uint8_t command = PCA9698_REG_OUTPUT | bank;
  _wire->beginTransmission(_address);
  _wire->write(command);
  _wire->write(bitmask);
  if (_wire->endTransmission() != 0)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  _error = PCA9698_OK;
  return _error;
}


uint8_t PCA9698::toggle8(uint8_t bank, uint8_t bitmask)
{
  uint8_t mask = 0;
  if (read8(bank, mask) != PCA9698_OK)
  {
    return _error;
  }
  mask ^= bitmask;
  if (write8(bank, mask) != PCA9698_OK)
  {
    return _error;
  }
  return _error;
}


uint8_t PCA9698::read1(uint8_t pin)
{
  if (pin > 39)
  {
    _error = PCA9698_PIN_ERROR;
    return _error;
  }
  uint8_t mask = 0;
  uint8_t bank = pin / 8;
  read8(bank, mask);
  uint8_t bit = 1 << (pin & 0x07);
  return (mask & bit) > 0;
}


uint8_t PCA9698::write1(uint8_t pin, uint8_t value)
{
  if (pin > 39)
  {
    _error = PCA9698_PIN_ERROR;
    return _error;
  }
  uint8_t mask = 0;
  uint8_t bank = pin / 8;
  read8(bank, mask);
  uint8_t bit = 1 << (pin & 0x07);
  if (value == LOW) mask &= ~bit;
  else              mask |= bit;
  return write8(bank, mask);
}


uint8_t PCA9698::toggle1(uint8_t pin)
{
  if (pin > 39)
  {
    _error = PCA9698_PIN_ERROR;
    return _error;
  }
  uint8_t mask = 0;
  uint8_t bank = pin / 8;
  uint8_t bit = 1 << (pin & 0x07);
  read8(bank, mask);
  mask ^= bit;
  return write8(bank, mask);
}


uint8_t PCA9698::read40(uint8_t * buf)
{
  uint8_t command = PCA9698_AUTO_INCR | PCA9698_REG_INPUT;
  return _read40(command, buf);
}


uint8_t PCA9698::write40(uint8_t * buf)
{
  uint8_t command = PCA9698_AUTO_INCR | PCA9698_REG_INPUT;
  return _write40(command, buf);
}


void PCA9698::select(uint8_t pin)
{
  uint8_t buf[5] = {0, 0, 0, 0, 0};
  buf[pin/8] = 1 << (pin & 0x07);
  write40(buf);
}


void PCA9698::selectN(uint8_t n)
{
  uint8_t buf[5] = {0, 0, 0, 0, 0};
  uint8_t bank = n / 8;
  for (int i = 0; i < bank; i++)
  {
    buf[i] = 0xFF;
  }
  uint8_t pos = n & 0x07;
  for (int i = 0; i < pos; i++)
  {
    buf[bank] <<= 1;
    buf[bank] |= 0x01;
  }
  write40(buf);
}


uint8_t PCA9698::setPolarity40(uint8_t * buf)
{
  uint8_t command = PCA9698_AUTO_INCR | PCA9698_REG_POLARITY;
  return _write40(command, buf);
}

uint8_t PCA9698::getPolarity40(uint8_t * buf)
{
  uint8_t command = PCA9698_AUTO_INCR | PCA9698_REG_POLARITY;
  return _read40(command, buf);
}


uint8_t PCA9698::setPinMode40(uint8_t * buf)
{
  uint8_t command = PCA9698_AUTO_INCR | PCA9698_REG_CONFIG;
  return _write40(command, buf);
}

uint8_t PCA9698::getPinMode40(uint8_t * buf)
{
  uint8_t command = PCA9698_AUTO_INCR | PCA9698_REG_CONFIG;
  return _read40(command, buf);
}


uint8_t PCA9698::setInterrupt40(uint8_t * buf)
{
  uint8_t command = PCA9698_AUTO_INCR | PCA9698_REG_INT_MASK;
  return _write40(command, buf);
}

uint8_t PCA9698::getInterrupt40(uint8_t * buf)
{
  uint8_t command = PCA9698_AUTO_INCR | PCA9698_REG_INT_MASK;
  return _read40(command, buf);
}


uint8_t PCA9698::setOutputConfig(uint8_t mask)
{
  return _write(PCA9698_OUTPUT_CONFIG, mask);
}


uint8_t PCA9698::getOutputConfig()
{
  uint8_t mask = 0;
  _read(PCA9698_OUTPUT_CONFIG, mask);
  return mask;
}


uint8_t PCA9698::setAllBank(uint8_t mask)
{
  return _write(PCA9698_ALL_BANK_CONTROL, mask);
}


uint8_t PCA9698::getAllBank()
{
  uint8_t mask = 0;
  _read(PCA9698_ALL_BANK_CONTROL, mask);
  return mask;
}


uint8_t PCA9698::setMode(uint8_t mask)
{
  return _write(PCA9698_MODE_SELECTION, mask);
}

uint8_t PCA9698::getMode()
{
  uint8_t mask = 0;
  _read(PCA9698_MODE_SELECTION, mask);
  return mask;
}


uint32_t PCA9698::getDeviceID()
{
  //  7.5
  uint32_t devid = 0;
  _wire->beginTransmission(0xF8);
  _wire->write(_address);
  if (_wire->endTransmission(false) != 0)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  if (_wire->requestFrom((uint8_t)0xF9, (uint8_t)3) != 3)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  for (int i = 0; i < 3; i++)
  {
    devid <<= 8;
    devid += _wire->read();
  }
  _error = PCA9698_OK;
  return _error;
}


int PCA9698::lastError()
{
  int e = _error;
  _error = PCA9698_OK;
  return e;
}


/////////////////////////////////////////////////////////////////
//
//  PROTECTED
//

uint8_t PCA9698::_read(uint8_t reg, uint8_t & value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  if (_wire->endTransmission() != 0)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  value = _wire->read();
  _error = PCA9698_OK;
  return _error;
}


uint8_t PCA9698::_write(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  if (_wire->endTransmission() != 0)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  _error = PCA9698_OK;
  return _error;
}


uint8_t PCA9698::_read40(uint8_t command, uint8_t * buf)
{
  _wire->beginTransmission(_address);
  _wire->write(command);
  if (_wire->endTransmission() != 0)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  if (_wire->requestFrom(_address, (uint8_t)5) != 5)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  for (int i = 0; i < 5; i++)
  {
    buf[i] = _wire->read();
  }
  _error = PCA9698_OK;
  return _error;
}


uint8_t PCA9698::_write40(uint8_t command, uint8_t * buf)
{
  _wire->beginTransmission(_address);
  _wire->write(command);
  for (int i = 0; i < 5; i++)
  {
    _wire->write(buf[i]);
  }
  if (_wire->endTransmission() != 0)
  {
    _error = PCA9698_I2C_ERROR;
    return _error;
  }
  _error = PCA9698_OK;
  return _error;
}


//  -- END OF FILE --

