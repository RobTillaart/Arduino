//
//    FILE: MCP23017.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for I2C MCP23017 16 channel port expander
//    DATE: 2019-10-12
//     URL: https://github.com/RobTillaart/MCP23017_RT
//
//  HISTORY:
//  0.1.0   2019-10-12  initial version
//  0.1.1   2020-06-19  refactor; #pragma once
//  0.1.2   2021-01-01  add arduino-ci + unit test
//  0.2.0   2021-01-11  Multiple Wire support Wire0 .. 5
//                      error handling
//  0.2.1   2021-02-17  fix #7 DDR is defined in ESP32

//    TODO: 
//  interrupts
//  caching for performance?
//  INPUT_PULLUP


#include "MCP23017.h"


#define MCP23017_DDR_A        0x00   // Data Direction Register
#define MCP23017_DDR_B        0x01
#define MCP23017_PUR_A        0x0C   // Pull Up Resistors
#define MCP23017_PUR_B        0x0D

#define MCP23017_IOCR         0x0A   // IO control register

#define MCP23017_GPIOA        0x12
#define MCP23017_GPIOB        0x13


MCP23017::MCP23017(uint8_t addr, TwoWire *wire)
{
  _addr  = addr;
  _wire  = wire;
  _error = MCP23017_OK;
}


#if defined(ESP8266) || defined(ESP32)
bool MCP23017::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  _wire = &Wire;
  _wire->begin(dataPin, clockPin);
    if (! isConnected()) return false;
  // Force INPUT_PULLUP
  writeReg(MCP23017_IOCR, 0b00100000); // disable addres increment (datasheet)
  writeReg(MCP23017_PUR_A, 0xFF);
  writeReg(MCP23017_PUR_B, 0xFF);
  return true;
}
#endif


bool MCP23017::begin()
{
  _wire->begin();
    if (! isConnected()) return false;
  // Force INPUT_PULLUP
  writeReg(MCP23017_IOCR, 0b00100000); // disable addres increment (datasheet)
  writeReg(MCP23017_PUR_A, 0xFF);
  writeReg(MCP23017_PUR_B, 0xFF);
  return true;
}


bool MCP23017::isConnected()
{
  _wire->beginTransmission(_addr);
  return (_wire->endTransmission() == 0);
}


// single pin interface
// pin 0..15
// value INPUT, OUTPUT, INPUT_PULLUP  
// TODO: split INPUT_PULLUP and INPUT, for now they are the same
bool MCP23017::pinMode(uint8_t pin, uint8_t value)
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return false;
  }
  if ((value != INPUT) && (value != INPUT_PULLUP) && (value != OUTPUT))
  {
    _error = MCP23017_VALUE_ERROR;
    return false;
  }
  
  uint8_t dataDirectionRegister = MCP23017_DDR_A;
  if (pin > 7)
  {
    dataDirectionRegister = MCP23017_DDR_B;
    pin -= 8;
  }
  uint8_t val = readReg(dataDirectionRegister);
  uint8_t mask = 1 << pin;
  // only work with valid
  if (value == INPUT || value == INPUT_PULLUP)
  {
    val |= mask;
  }
  else if (value == OUTPUT)
  {
    val &= ~mask;
  }
  // other values won't change val ....
  writeReg(dataDirectionRegister, val);
  _error = MCP23017_OK;
  return true;
}


bool MCP23017::digitalWrite(uint8_t pin, uint8_t value)   // pin = 0..15
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return false;
  }
  uint8_t IOR = MCP23017_GPIOA;
  if (pin > 7)
  {
    IOR = MCP23017_GPIOB;
    pin -= 8;
  }
  uint8_t val = readReg(IOR);
  uint8_t mask = 1 << pin;
  if (value) val |= mask;
  else val &= ~mask;
  writeReg(IOR, val);
  _error = MCP23017_OK;
  return true;
}


uint8_t MCP23017::digitalRead(uint8_t pin)
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return -100;    // TODO magic number
  }
  uint8_t IOR = MCP23017_GPIOA;
  if (pin > 7)
  {
    IOR = MCP23017_GPIOB;
    pin -= 8;
  }
  uint8_t val = readReg(IOR);
  uint8_t mask = 1 << pin;
  _error = MCP23017_OK;
  if (val & mask) return HIGH;
  return LOW;
}


// 8 pins interface
// whole register at once
bool MCP23017::pinMode8(uint8_t port, uint8_t value)
{
  if (port > 1)
  {
    _error = MCP23017_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23017_DDR_A, value);
  if (port == 1) writeReg(MCP23017_DDR_B, value);
  _error = MCP23017_OK;
  return true;
}


bool MCP23017::write8(uint8_t port, uint8_t value)   // port = 0..1
{
  if (port > 1)
  {
    _error = MCP23017_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23017_GPIOA, value);
  if (port == 1) writeReg(MCP23017_GPIOB, value);
  _error = MCP23017_OK;
  return true;
}


int MCP23017::read8(uint8_t port)
{
  if (port > 1)
  {
    _error = MCP23017_PORT_ERROR;
    return -100;  // TODO magic number;
  }
  _error = MCP23017_OK;
  if (port == 0) return readReg(MCP23017_GPIOA);
  return readReg(MCP23017_GPIOB);  // port == 1
}


int MCP23017::lastError()
{
  int e = _error;
  _error = MCP23017_OK;  // reset error after read.
  return e;
}


////////////////////////////////////////////////////
//
// PRIVATE
// 

bool MCP23017::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->write(value);
  if (_wire->endTransmission() != 0)
  {
    _error = MCP23017_I2C_ERROR;
    return false;
  }
  _error = MCP23017_OK;
  return true;
}


uint8_t MCP23017::readReg(uint8_t reg)
{
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  if (_wire->endTransmission() != 0)
  {
    _error = MCP23017_I2C_ERROR;
    // return 0; ???
  }
  else
  {
    _error = MCP23017_OK;
  }
  _wire->requestFrom(_addr, (uint8_t)1);
  return _wire->read();
}


// -- END OF FILE --
