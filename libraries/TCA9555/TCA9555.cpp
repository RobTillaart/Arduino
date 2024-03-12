//
//    FILE: TCA9555.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: Arduino library for I2C TCA9555 16 channel port expander
//    DATE: 2021-06-09
//     URL: https://github.com/RobTillaart/TCA9555


#include "TCA9555.h"


//  REGISTERS
#define TCA9555_INPUT_PORT_REGISTER_0     0x00    //  read()
#define TCA9555_INPUT_PORT_REGISTER_1     0x01
#define TCA9555_OUTPUT_PORT_REGISTER_0    0x02    //  write()
#define TCA9555_OUTPUT_PORT_REGISTER_1    0x03
#define TCA9555_POLARITY_REGISTER_0       0x04    //  get/setPolarity()
#define TCA9555_POLARITY_REGISTER_1       0x05
#define TCA9555_CONFIGURATION_PORT_0      0x06    //  pinMode()
#define TCA9555_CONFIGURATION_PORT_1      0x07


TCA9555::TCA9555(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
  _error   = TCA9555_OK;
  _type    = 55;
}


bool TCA9555::begin()
{
  if ((_address < 0x20) || (_address > 0x27)) return false;
  if (! isConnected()) return false;
  return true;
}


bool TCA9555::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t TCA9555::getAddress()
{
  return _address;
}


//////////////////////////////////////////////////////////
//
//  1 PIN INTERFACE
//
bool TCA9555::pinMode1(uint8_t pin, uint8_t mode)   //  pin = 0..15
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return false;
  }
  if ( (mode != INPUT) && (mode != OUTPUT) )
  {
    _error = TCA9555_VALUE_ERROR;
    return false;
  }
  uint8_t CONFREG = TCA9555_CONFIGURATION_PORT_0;
  if (pin > 7)
  {
    CONFREG = TCA9555_CONFIGURATION_PORT_1;
    pin -= 8;
  }
  uint8_t val = readRegister(CONFREG);
  uint8_t mask = 1 << pin;
  if (mode == INPUT)  val |= mask;
  if (mode == OUTPUT) val &= ~mask;
  writeRegister(CONFREG, val);
  _error = TCA9555_OK;
  return true;
}


bool TCA9555::write1(uint8_t pin, uint8_t value)   //  pin = 0..15
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return false;
  }
  uint8_t OPR = TCA9555_OUTPUT_PORT_REGISTER_0;
  if (pin > 7)
  {
    OPR = TCA9555_OUTPUT_PORT_REGISTER_1;
    pin -= 8;
  }
  uint8_t val = readRegister(OPR);
  uint8_t mask = 1 << pin;
  if (value) val |= mask;
  else val &= ~mask;
  writeRegister(OPR, val);
  _error = TCA9555_OK;
  return true;
}


uint8_t TCA9555::read1(uint8_t pin)   //  pin = 0..15
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return TCA9555_INVALID_READ;
  }
  uint8_t IPR = TCA9555_INPUT_PORT_REGISTER_0;
  if (pin > 7)
  {
    IPR = TCA9555_INPUT_PORT_REGISTER_1;
    pin -= 8;
  }
  uint8_t val = readRegister(IPR);
  uint8_t mask = 1 << pin;
  _error = TCA9555_OK;
  if (val & mask) return HIGH;
  return LOW;
}


bool TCA9555::setPolarity(uint8_t pin, uint8_t value)   //  pin = 0..15
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return false;
  }
  uint8_t POLREG = TCA9555_POLARITY_REGISTER_0;
  if (pin > 7)
  {
    POLREG = TCA9555_POLARITY_REGISTER_1;
    pin -= 8;
  }
  uint8_t val = readRegister(POLREG);
  uint8_t mask = 1 << pin;
  if (value == HIGH) val |= mask;
  if (value == LOW)  val &= ~mask;
  writeRegister(POLREG, val);
  _error = TCA9555_OK;
  return true;
}


uint8_t TCA9555::getPolarity(uint8_t pin)
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return false;
  }
  uint8_t POLREG = TCA9555_POLARITY_REGISTER_0;
  if (pin > 7) POLREG = TCA9555_POLARITY_REGISTER_1;
  _error = TCA9555_OK;
  uint8_t mask = readRegister(POLREG);
  return (mask >> pin) == 0x01;
}



//////////////////////////////////////////////////////////
//
//  8 PIN INTERFACE
//
bool TCA9555::pinMode8(uint8_t port, uint8_t mask)
{
  if (port > 1)
  {
    _error = TCA9555_PORT_ERROR;
    return false;
  }
  _error = TCA9555_OK;
  if (port == 0) return writeRegister(TCA9555_CONFIGURATION_PORT_0, mask);
  if (port == 1) return writeRegister(TCA9555_CONFIGURATION_PORT_1, mask);
  return false;
}


bool TCA9555::write8(uint8_t port, uint8_t mask)   //  port = 0..1
{
  if (port > 1)
  {
    _error = TCA9555_PORT_ERROR;
    return false;
  }
  _error = TCA9555_OK;
  if (port == 0) return writeRegister(TCA9555_OUTPUT_PORT_REGISTER_0, mask);
  if (port == 1) return writeRegister(TCA9555_OUTPUT_PORT_REGISTER_1, mask);
  return false;
}


int TCA9555::read8(uint8_t port)
{
  if (port > 1)
  {
    _error = TCA9555_PORT_ERROR;
    return TCA9555_INVALID_READ;
  }
  _error = TCA9555_OK;
  if (port == 0) return readRegister(TCA9555_INPUT_PORT_REGISTER_0);
  if (port == 1) return readRegister(TCA9555_INPUT_PORT_REGISTER_1);
  return 0; // keeps compiler happy
}


bool TCA9555::setPolarity8(uint8_t port, uint8_t mask)
{
  if (port > 1)
  {
    _error = TCA9555_PORT_ERROR;
    return false;
  }
  _error = TCA9555_OK;
  if (port == 0) return writeRegister(TCA9555_POLARITY_REGISTER_0, mask);
  if (port == 1) return writeRegister(TCA9555_POLARITY_REGISTER_1, mask);
  return false;
}


uint8_t TCA9555::getPolarity8(uint8_t port)
{
  if (port > 1)
  {
    _error = TCA9555_PORT_ERROR;
    return 0;
  }
  _error = TCA9555_OK;
  if (port == 0) return readRegister(TCA9555_POLARITY_REGISTER_0);
  if (port == 1) return readRegister(TCA9555_POLARITY_REGISTER_1);
  return 0;  //  keeps compiler happy
}


//////////////////////////////////////////////////////////
//
// 16 PIN INTERFACE
//
bool TCA9555::pinMode16(uint16_t mask)
{
  bool b = true;
  b &= pinMode8(0, mask & 0xFF);
  b &= pinMode8(1, mask >> 8);
  return b;
}


bool TCA9555::write16(uint16_t mask)
{
  bool b = true;
  b &= write8(0, mask & 0xFF);
  b &= write8(1, mask >> 8);
  return b;
}


uint16_t TCA9555::read16()
{
  uint16_t rv = 0;
  rv |= (read8(1) << 8);
  rv |= read8(0);
  return rv;
}


bool TCA9555::setPolarity16(uint16_t mask)
{
  bool b = true;
  b &= setPolarity8(0, mask & 0xFF);
  b &= setPolarity8(1, mask >> 8);
  return b;
}


uint8_t TCA9555::getPolarity16()
{
  uint16_t rv = 0;
  rv |= (getPolarity8(1) << 8);
  rv |= getPolarity8(0);
  return rv;
}


int TCA9555::lastError()
{
  int error = _error;
  _error = TCA9555_OK;  //  reset error after read.
  return error;
}


uint8_t TCA9555::getType()
{
  return _type;
}


////////////////////////////////////////////////////
//
//  PROTECTED
//
bool TCA9555::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  if (_wire->endTransmission() != 0)
  {
    _error = TCA9555_I2C_ERROR;
    return false;
  }
  _error = TCA9555_OK;
  return true;
}


uint8_t TCA9555::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int rv = _wire->endTransmission();
  if (rv != 0)
  {
    _error = TCA9555_I2C_ERROR;
    return rv;
  }
  else
  {
    _error = TCA9555_OK;
  }
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


/////////////////////////////////////////////////////////////////////////////
//
//  TCA9535
//
TCA9535::TCA9535(uint8_t address, TwoWire *wire)
        :TCA9555(address, wire)
{
  _type = 35;
}


//  -- END OF FILE --

