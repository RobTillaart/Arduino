//
//    FILE: TCA6408A.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-13
// VERSION: 0.1.1
// PURPOSE: Arduino library for TCA6408A I2C 8 bits IO expander.
//     URL: https://github.com/RobTillaart/TCA6408A_RT



#include "TCA6408A.h"

constexpr uint8_t TCA6408A_REG_INPUT    = 0x00;  //  R
constexpr uint8_t TCA6408A_REG_OUTPUT   = 0x01;  //  RW
constexpr uint8_t TCA6408A_REG_POLARITY = 0x02;  //  RW
constexpr uint8_t TCA6408A_REG_CONFIG   = 0x03;  //  RW


TCA6408A::TCA6408A(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
  _error   = TCA6408A_OK;
  _IOMask  = 0xFF;
}

bool TCA6408A::begin()
{
  //  reset variables
  _error = TCA6408A_OK;

  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool TCA6408A::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t TCA6408A::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  PINMODE
//
void TCA6408A::setPinMode8(uint8_t mask)
{
  writeRegister(TCA6408A_REG_CONFIG, mask);
  _IOMask = mask;
  //  TODO error propagation
  return;
}

uint8_t TCA6408A::getPinMode8()
{
  // return _IOMask; ???
  uint8_t mask = readRegister(TCA6408A_REG_CONFIG);
  return mask;
}

void TCA6408A::setPinMode1(uint8_t pin, uint8_t value)
{
  uint8_t data = readRegister(TCA6408A_REG_CONFIG);
  uint8_t prev = data;
  if (value == LOW) data &= ~(1 << pin);
  else              data |= (1 << pin);
  if (data != prev)
  {
    writeRegister(TCA6408A_REG_CONFIG, data);
    _IOMask = data;
    //  TODO error propagation
  }
  return;
}

uint8_t TCA6408A::getPinMode1(uint8_t pin)
{
  uint8_t data = readRegister(TCA6408A_REG_CONFIG);
  return (data & (1<< pin)) > 0;
}


/////////////////////////////////////////////
//
//  POLARITY
//
void TCA6408A::setPolarity8(uint8_t mask)
{
  writeRegister(TCA6408A_REG_POLARITY, mask);
  //  TODO error propagation
  return;
}

uint8_t TCA6408A::getPolarity8()
{
  uint8_t mask = readRegister(TCA6408A_REG_POLARITY);
  return mask;
}

void TCA6408A::setPolarity1(uint8_t pin, uint8_t value)
{
  uint8_t data = readRegister(TCA6408A_REG_POLARITY);
  uint8_t prev = data;
  if (value == LOW) data &= ~(1 << pin);
  else              data |= (1 << pin);
  if (data != prev)
  {
    writeRegister(TCA6408A_REG_POLARITY, data);
    //  TODO error propagation
  }
  return;
}

uint8_t TCA6408A::getPolarity1(uint8_t pin)
{
  uint8_t data = readRegister(TCA6408A_REG_POLARITY);
  return (data & (1<< pin)) > 0;
}


/////////////////////////////////////////////
//
//  READ-WRITE
//
void TCA6408A::digitalWrite8(uint8_t mask)
{
  writeRegister(TCA6408A_REG_OUTPUT, mask);
  //  TODO error propagation
  return;
}

void TCA6408A::digitalWrite1(uint8_t pin, uint8_t value)
{
  uint8_t data = readRegister(TCA6408A_REG_OUTPUT);
  uint8_t prev = data;
  if (value == LOW) data &= ~(1 << pin);
  else              data |= (1 << pin);
  if (data != prev)
  {
    writeRegister(TCA6408A_REG_OUTPUT, data);
    //  TODO error propagation
  }
  return;
}


uint8_t TCA6408A::digitalRead8()
{
  uint8_t mask = readRegister(TCA6408A_REG_INPUT) & _IOMask;
  return mask;
}

uint8_t TCA6408A::digitalRead1(uint8_t pin)
{
  uint8_t data = readRegister(TCA6408A_REG_INPUT) & _IOMask;
  return (data & (1<< pin)) > 0;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int TCA6408A::getLastError()
{
  int e = _error;
  _error = TCA6408A_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
int TCA6408A::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    _error = n;
  }
  return n;
}

uint8_t TCA6408A::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int n = _wire->endTransmission(false);
  if (n != 0)
  {
    _error = n;
    return 0xFF;
  }
  if (1 != _wire->requestFrom(_address, (uint8_t)1))
  {
    _error = TCA6408A_REQUEST_ERROR;
    return 0xFF;
  }
  return _wire->read();
}


//  -- END OF FILE --

