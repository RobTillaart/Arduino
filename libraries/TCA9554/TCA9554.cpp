//
//    FILE: TCA9554.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for I2C TCA9554 8 channel port expander.
//    DATE: 2025-01-09
//     URL: https://github.com/RobTillaart/TCA9554


#include "TCA9554.h"


//  REGISTERS
#define TCA9554_INPUT_PORT_REGISTER     0x00    //  read()
#define TCA9554_OUTPUT_PORT_REGISTER    0x01    //  write()
#define TCA9554_POLARITY_REGISTER       0x02    //  get/setPolarity()
#define TCA9554_CONFIGURATION_PORT      0x03    //  pinMode()


TCA9554::TCA9554(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
  _error   = TCA9554_OK;
  _type    = 54;
}


bool TCA9554::begin(uint8_t mode, uint8_t mask)
{
  if ((_address < 0x20) || (_address > 0x27)) return false;
  if (! isConnected()) return false;

  if (mode == OUTPUT)
  {
    pinMode8(0x00);
    write8(mask);
  } else {
    pinMode8(0xFF);
  }
  return true;
}


bool TCA9554::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t TCA9554::getAddress()
{
  return _address;
}


//////////////////////////////////////////////////////////
//
//  1 PIN INTERFACE
//
bool TCA9554::pinMode1(uint8_t pin, uint8_t mode)
{
  if (pin > 7)
  {
    _error = TCA9554_PIN_ERROR;
    return false;
  }
  if ( (mode != INPUT) && (mode != OUTPUT) )
  {
    _error = TCA9554_VALUE_ERROR;
    return false;
  }
  uint8_t val = readRegister(TCA9554_CONFIGURATION_PORT);
  uint8_t prevVal = val;
  uint8_t mask = 1 << pin;
  if (mode == INPUT)  val |= mask;
  else                val &= ~mask;
  if (val != prevVal)
  {
    return writeRegister(TCA9554_CONFIGURATION_PORT, val);
  }
  _error = TCA9554_OK;
  return true;
}


bool TCA9554::write1(uint8_t pin, uint8_t value)
{
  if (pin > 7)
  {
    _error = TCA9554_PIN_ERROR;
    return false;
  }
  uint8_t val = readRegister(TCA9554_OUTPUT_PORT_REGISTER);
  uint8_t prevVal = val;
  uint8_t mask = 1 << pin;
  if (value) val |= mask;  //  all values are HIGH.
  else       val &= ~mask;
  if (val != prevVal)
  {
    return writeRegister(TCA9554_OUTPUT_PORT_REGISTER, val);
  }
  _error = TCA9554_OK;
  return true;
}


uint8_t TCA9554::read1(uint8_t pin)
{
  if (pin > 7)
  {
    _error = TCA9554_PIN_ERROR;
    return TCA9554_INVALID_READ;
  }
  uint8_t val = readRegister(TCA9554_INPUT_PORT_REGISTER);
  uint8_t mask = 1 << pin;
  _error = TCA9554_OK;
  if (val & mask) return HIGH;
  return LOW;
}


bool TCA9554::setPolarity(uint8_t pin, uint8_t value)
{
  if (pin > 7)
  {
    _error = TCA9554_PIN_ERROR;
    return false;
  }
  if ((value != LOW) && (value != HIGH))
  {
    _error = TCA9554_VALUE_ERROR;
    return false;
  }
  uint8_t val = readRegister(TCA9554_POLARITY_REGISTER);
  uint8_t prevVal = val;
  uint8_t mask = 1 << pin;
  if (value == HIGH) val |= mask;
  else               val &= ~mask;
  if (val != prevVal)
  {
    return writeRegister(TCA9554_POLARITY_REGISTER, val);
  }
  _error = TCA9554_OK;
  return true;
}


uint8_t TCA9554::getPolarity(uint8_t pin)
{
  if (pin > 7)
  {
    _error = TCA9554_PIN_ERROR;
    return false;
  }
  _error = TCA9554_OK;
  uint8_t mask = readRegister(TCA9554_POLARITY_REGISTER);
  return (mask >> pin) == 0x01;
}


//////////////////////////////////////////////////////////
//
//  8 PIN INTERFACE
//
bool TCA9554::pinMode8(uint8_t mask)
{
  _error = TCA9554_OK;
  return writeRegister(TCA9554_CONFIGURATION_PORT, mask);
}


bool TCA9554::write8(uint8_t mask)
{
  _error = TCA9554_OK;
  return writeRegister(TCA9554_OUTPUT_PORT_REGISTER, mask);
}


int TCA9554::read8()
{
  _error = TCA9554_OK;
  return readRegister(TCA9554_INPUT_PORT_REGISTER);
}


bool TCA9554::setPolarity8(uint8_t mask)
{
  _error = TCA9554_OK;
  return writeRegister(TCA9554_POLARITY_REGISTER, mask);
}


uint8_t TCA9554::getPolarity8()
{
  _error = TCA9554_OK;
  return readRegister(TCA9554_POLARITY_REGISTER);
}


//////////////////////////////////////////////////////////
//
//  OTHER
//
int TCA9554::lastError()
{
  int error = _error;
  _error = TCA9554_OK;  //  reset error after read.
  return error;
}


uint8_t TCA9554::getType()
{
  return _type;
}


////////////////////////////////////////////////////
//
//  PROTECTED
//
bool TCA9554::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  if (_wire->endTransmission() != 0)
  {
    _error = TCA9554_I2C_ERROR;
    return false;
  }
  _error = TCA9554_OK;
  return true;
}


uint8_t TCA9554::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int rv = _wire->endTransmission();
  if (rv != 0)
  {
    _error = TCA9554_I2C_ERROR;
    return rv;
  }
  else
  {
    _error = TCA9554_OK;
  }
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES TCA9534 PCA9554 PCA9534 CAT9554 CAT9534
//
TCA9534::TCA9534(uint8_t address, TwoWire *wire)
        :TCA9554(address, wire)
{
  _type = 34;
}

PCA9554::PCA9554(uint8_t address, TwoWire *wire)
        :TCA9554(address, wire)
{
  _type = 54;
}

PCA9534::PCA9534(uint8_t address, TwoWire *wire)
        :TCA9554(address, wire)
{
  _type = 34;
}

CAT9554::CAT9554(uint8_t address, TwoWire *wire)
        :TCA9554(address, wire)
{
  _type = 54;
}

CAT9534::CAT9534(uint8_t address, TwoWire *wire)
        :TCA9554(address, wire)
{
  _type = 34;
}


//  -- END OF FILE --

