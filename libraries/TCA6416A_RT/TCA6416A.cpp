//
//    FILE: TCA6416A.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-14
// VERSION: 0.1.1
// PURPOSE: Arduino library for TCA6416A I2C 16 bits IO expander.
//     URL: https://github.com/RobTillaart/TCA6416A_RT



#include "TCA6416A.h"

constexpr uint8_t TCA6416A_REG_INPUT    = 0x00;  //  R
constexpr uint8_t TCA6416A_REG_OUTPUT   = 0x02;  //  RW
constexpr uint8_t TCA6416A_REG_POLARITY = 0x04;  //  RW
constexpr uint8_t TCA6416A_REG_CONFIG   = 0x06;  //  RW


TCA6416A::TCA6416A(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
  _error   = TCA6416A_OK;
  _IOMask  = 0xFFFF;
}

bool TCA6416A::begin()
{
  //  reset variables
  _error = TCA6416A_OK;

  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool TCA6416A::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t TCA6416A::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  PINMODE
//
void TCA6416A::setPinMode16(uint16_t mask)
{
  writeRegister(TCA6416A_REG_CONFIG, mask);
  _IOMask = mask;
  //  TODO error propagation
  return;
}

uint16_t TCA6416A::getPinMode16()
{
  // return _IOMask; ???
  uint16_t mask = readRegister(TCA6416A_REG_CONFIG);
  return mask;
}

void TCA6416A::setPinMode1(uint8_t pin, uint8_t value)
{
  uint16_t data = readRegister(TCA6416A_REG_CONFIG);
  uint16_t prev = data;
  if (value == LOW) data &= ~(1 << pin);
  else              data |= (1 << pin);
  if (data != prev)
  {
    writeRegister(TCA6416A_REG_CONFIG, data);
    _IOMask = data;
    //  TODO error propagation
  }
  return;
}

uint8_t TCA6416A::getPinMode1(uint8_t pin)
{
  uint16_t data = readRegister(TCA6416A_REG_CONFIG);
  return (data & (1<< pin)) > 0;
}


/////////////////////////////////////////////
//
//  POLARITY
//
void TCA6416A::setPolarity16(uint16_t mask)
{
  writeRegister(TCA6416A_REG_POLARITY, mask);
  //  TODO error propagation
  return;
}

uint16_t TCA6416A::getPolarity16()
{
  uint16_t mask = readRegister(TCA6416A_REG_POLARITY);
  return mask;
}

void TCA6416A::setPolarity1(uint8_t pin, uint8_t value)
{
  uint16_t data = readRegister(TCA6416A_REG_POLARITY);
  uint16_t prev = data;
  if (value == LOW) data &= ~(1 << pin);
  else              data |= (1 << pin);
  if (data != prev)
  {
    writeRegister(TCA6416A_REG_POLARITY, data);
    //  TODO error propagation
  }
  return;
}

uint8_t TCA6416A::getPolarity1(uint8_t pin)
{
  uint16_t data = readRegister(TCA6416A_REG_POLARITY);
  return (data & (1<< pin)) > 0;
}


/////////////////////////////////////////////
//
//  READ-WRITE
//
void TCA6416A::digitalWrite16(uint16_t mask)
{
  writeRegister(TCA6416A_REG_OUTPUT, mask);
  //  TODO error propagation
  return;
}

void TCA6416A::digitalWrite1(uint8_t pin, uint8_t value)
{
  uint16_t data = readRegister(TCA6416A_REG_OUTPUT);
  uint16_t prev = data;
  if (value == LOW) data &= ~(1 << pin);
  else              data |= (1 << pin);
  if (data != prev)
  {
    writeRegister(TCA6416A_REG_OUTPUT, data);
    //  TODO error propagation
  }
  return;
}

uint16_t TCA6416A::digitalRead16()
{
  uint16_t mask = readRegister(TCA6416A_REG_INPUT) & _IOMask;
  return mask;
}

uint8_t TCA6416A::digitalRead1(uint8_t pin)
{
  uint16_t data = readRegister(TCA6416A_REG_INPUT) & _IOMask;
  return (data & (1<< pin)) > 0;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int TCA6416A::getLastError()
{
  int e = _error;
  _error = TCA6416A_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
int TCA6416A::writeRegister(uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value & 0xFF);
  _wire->write(value >> 8);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    _error = n;
  }
  return n;
}

uint16_t TCA6416A::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int n = _wire->endTransmission(false);
  if (n != 0)
  {
    _error = n;
    return 0xFFFF;
  }
  if (2 != _wire->requestFrom(_address, (uint8_t)2))
  {
    _error = TCA6416A_REQUEST_ERROR;
    return 0xFF;
  }
  uint16_t lo = _wire->read();
  uint16_t hi = _wire->read();
  return (hi << 8) | lo;
}


//  -- END OF FILE --

