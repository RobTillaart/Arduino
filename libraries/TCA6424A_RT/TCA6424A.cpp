//
//    FILE: TCA6424A.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-14
// VERSION: 0.1.0
// PURPOSE: Arduino library for TCA6424A I2C 16 bits IO expander.
//     URL: https://github.com/RobTillaart/TCA6424A_RT



#include "TCA6424A.h"

constexpr uint8_t TCA6424A_REG_INPUT    = 0x00;
constexpr uint8_t TCA6424A_REG_OUTPUT   = 0x04;
constexpr uint8_t TCA6424A_REG_POLARITY = 0x08;
constexpr uint8_t TCA6424A_REG_CONFIG   = 0x0C;


TCA6424A::TCA6424A(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _error = TCA6424A_OK;
}

bool TCA6424A::begin()
{
  //  reset variables
  _error = TCA6424A_OK;

  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool TCA6424A::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t TCA6424A::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  PINMODE
//
void TCA6424A::setPinMode24(uint32_t mask)
{
  writeRegister(TCA6424A_REG_CONFIG, mask);
  _IOMask = mask;
  //  TODO error propagation
  return;
}

uint32_t TCA6424A::getPinMode24()
{
  // return _IOMask; ???
  uint32_t mask = readRegister(TCA6424A_REG_CONFIG);
  return mask;
}

void TCA6424A::setPinMode1(uint8_t pin, uint8_t value)
{
  uint32_t data = readRegister(TCA6424A_REG_CONFIG);
  uint32_t prev = data;
  if (value == LOW) data &= ~(1 << pin);
  else              data |= (1 << pin);
  if (data != prev)
  {
    writeRegister(TCA6424A_REG_CONFIG, data);
    _IOMask = data;
    //  TODO error propagation
  }
  return;
}

uint8_t TCA6424A::getPinMode1(uint8_t pin)
{
  uint32_t data = readRegister(TCA6424A_REG_CONFIG);
  return (data & (1<< pin)) > 0;
}


/////////////////////////////////////////////
//
//  POLARITY
//
void TCA6424A::setPolarity24(uint32_t mask)
{
  writeRegister(TCA6424A_REG_POLARITY, mask);
  //  TODO error propagation
  return;
}

uint32_t TCA6424A::getPolarity24()
{
  uint32_t mask = readRegister(TCA6424A_REG_POLARITY);
  return mask;
}

void TCA6424A::setPolarity1(uint8_t pin, uint8_t value)
{
  uint32_t data = readRegister(TCA6424A_REG_POLARITY);
  uint32_t prev = data;
  if (value == LOW) data &= ~(1 << pin);
  else              data |= (1 << pin);
  if (data != prev)
  {
    writeRegister(TCA6424A_REG_POLARITY, data);
    //  TODO error propagation
  }
  return;
}

uint8_t TCA6424A::getPolarity1(uint8_t pin)
{
  uint32_t data = readRegister(TCA6424A_REG_POLARITY);
  return (data & (1<< pin)) > 0;
}


/////////////////////////////////////////////
//
//  READ-WRITE
//
void TCA6424A::digitalWrite24(uint32_t mask)
{
  writeRegister(TCA6424A_REG_OUTPUT, mask);
  //  TODO error propagation
  return;
}

uint32_t TCA6424A::digitalRead24()
{
  uint32_t mask = readRegister(TCA6424A_REG_INPUT) & _IOMask;
  return mask;
}

void TCA6424A::digitalWrite1(uint8_t pin, uint8_t value)
{
  uint32_t data = readRegister(TCA6424A_REG_OUTPUT);
  uint32_t prev = data;
  if (value == LOW) data &= ~(1 << pin);
  else              data |= (1 << pin);
  if (data != prev)
  {
    writeRegister(TCA6424A_REG_OUTPUT, data);
    //  TODO error propagation
  }
  return;
}

uint8_t TCA6424A::digitalRead1(uint8_t pin)
{
  uint32_t data = readRegister(TCA6424A_REG_INPUT) & _IOMask;
  return (data & (1<< pin)) > 0;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int TCA6424A::getLastError()
{
  int e = _error;
  _error = TCA6424A_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
int TCA6424A::writeRegister(uint8_t reg, uint32_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value & 0xFF);
  _wire->write(value >> 8);
  _wire->write(value >> 16);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    _error = n;
  }
  return n;
}

uint32_t TCA6424A::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int n = _wire->endTransmission(false);
  if (n != 0)
  {
    _error = n;
    return 0;
  }
  if (2 != _wire->requestFrom(_address, (uint8_t)2))
  {
    _error = TCA6424A_REQUEST_ERROR;
    return 0xFF;
  }
  uint32_t data = _wire->read();
  data |= ((uint32_t)_wire->read()) << 8;
  data |= ((uint32_t)_wire->read()) << 16;
  return data;
}


//  -- END OF FILE --

