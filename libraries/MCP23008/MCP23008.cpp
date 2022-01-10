//
//    FILE: MCP23008.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for I2C MCP23008 8 channel port expander
//    DATE: 2019-10-12
//     URL: https://github.com/RobTillaart/MCP23008
//
//  HISTORY:
//  0.1.0   2022-01-10  initial version



#include "MCP23008.h"


//  Registers                         // description                 datasheet
#define MCP23008_DDR_A        0x00    // Data Direction Register A   P
#define MCP23008_POL_A        0x01    // Input Polarity A            P
#define MCP23008_GPINTEN_A    0x02    // NOT USED interrupt enable   P
#define MCP23008_DEFVAL_A     0x03    // NOT USED interrupt def      P
#define MCP23008_INTCON_A     0x04    // NOT USED interrupt control  P
#define MCP23008_IOCR         0x05    // IO control register         P
#define MCP23008_PUR_A        0x06    // Pull Up Resistors A         P
#define MCP23008_INTF_A       0x07    // NOT USED interrupt flag     P
#define MCP23008_INTCAP_A     0x08    // NOT USED interrupt capture  P
#define MCP23008_GPIO_A       0x09    // General Purpose IO A        P
#define MCP23008_OLAT_A       0x0A    // NOT USED output latch       P


MCP23008::MCP23008(uint8_t address, TwoWire *wire)
{
  _address  = address;
  _wire     = wire;
  _error    = MCP23008_OK;
}


#if defined(ESP8266) || defined(ESP32)
bool MCP23008::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  _wire = &Wire;
  _wire->begin(dataPin, clockPin);
  // check connected
  if (! isConnected()) return false;
  // disable address increment (datasheet)
  if (! writeReg(MCP23008_IOCR, 0b00100000)) return false;
  // Force INPUT_PULLUP
  if (! writeReg(MCP23008_PUR_A, 0xFF)) return false;
  return true;
}
#endif


bool MCP23008::begin()
{
  _wire->begin();
  // check connected
  if (! isConnected()) return false;
  // disable address increment (datasheet)
  if (! writeReg(MCP23008_IOCR, 0b00100000)) return false;
  // Force INPUT_PULLUP
  if (! writeReg(MCP23008_PUR_A, 0xFF)) return false;
  return true;
}


bool MCP23008::isConnected()
{
  _wire->beginTransmission(_address);
  if (_wire->endTransmission() != 0)
  {
    _error = MCP23008_I2C_ERROR;
    return false;
  }
  _error = MCP23008_OK;
  return true;
}


// single pin interface
// pin  = 0..7
// mode = INPUT, OUTPUT, INPUT_PULLUP (= same as INPUT)
bool MCP23008::pinMode(uint8_t pin, uint8_t mode)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  if ((mode != INPUT) && (mode != INPUT_PULLUP) && (mode != OUTPUT))
  {
    _error = MCP23008_VALUE_ERROR;
    return false;
  }

  uint8_t dataDirectionRegister = MCP23008_DDR_A;
  uint8_t val = readReg(dataDirectionRegister);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  // only work with valid
  if ((mode == INPUT) || (mode == INPUT_PULLUP))
  {
    val |= mask;
  }
  else if (mode == OUTPUT)
  {
    val &= ~mask;
  }
  // other values won't change val ....
  writeReg(dataDirectionRegister, val);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


// pin   = 0..7
// value = LOW, HIGH
bool MCP23008::digitalWrite(uint8_t pin, uint8_t value)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  uint8_t IOR = MCP23008_GPIO_A;
  uint8_t val = readReg(IOR);
  if (_error != MCP23008_OK)
  {
    return false;
  }

  uint8_t mask = 1 << pin;
  if (value)
  {
    val |= mask;
  }
  else
  {
    val &= ~mask;
  }
  writeReg(IOR, val);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


uint8_t MCP23008::digitalRead(uint8_t pin)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return MCP23008_INVALID_READ;
  }
  uint8_t IOR = MCP23008_GPIO_A;
  uint8_t val = readReg(IOR);
  if (_error != MCP23008_OK)
  {
    return MCP23008_INVALID_READ;
  }
  uint8_t mask = 1 << pin;
  if (val & mask) return HIGH;
  return LOW;
}


// pin  = 0..7
// reverse = true or false
bool MCP23008::setPolarity(uint8_t pin,  bool reversed)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23008_POL_A;
  uint8_t val = readReg(inputPolarityRegister);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  if (reversed)
  {
    val |= mask;
  }
  else
  {
    val &= ~mask;
  }
  writeReg(inputPolarityRegister, val);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


bool MCP23008::getPolarity(uint8_t pin, bool &reversed)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23008_POL_A;
  uint8_t val = readReg(inputPolarityRegister);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  reversed = (val & mask) > 0;
  return true;
}


// pin  = 0..7
// reverse = true or false
bool MCP23008::setPullup(uint8_t pin,  bool pullup)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23008_PUR_A;
  uint8_t val = readReg(inputPullupRegister);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  if (pullup)
  {
    val |= mask;
  }
  else
  {
    val &= ~mask;
  }
  writeReg(inputPullupRegister, val);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


bool MCP23008::getPullup(uint8_t pin, bool &pullup)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23008_PUR_A;
  uint8_t val = readReg(inputPullupRegister);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  pullup = (val & mask) > 0;
  return true;
}


///////////////////////////////////////////////////////////////////////
// 8 pins interface
// whole register at once
// value = 0..0xFF  bit pattern
bool MCP23008::pinMode8(uint8_t value)
{
  writeReg(MCP23008_DDR_A, value);
  _error = MCP23008_OK;
  return true;
}


bool MCP23008::write8(uint8_t value)
{
  writeReg(MCP23008_GPIO_A, value);
  _error = MCP23008_OK;
  return true;
}


int MCP23008::read8()
{
  _error = MCP23008_OK;
  return readReg(MCP23008_GPIO_A);
}


// mask  = 0..0xFF  bit pattern
bool MCP23008::setPolarity8(uint8_t mask)
{
  writeReg(MCP23008_POL_A, mask);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


bool MCP23008::getPolarity8(uint8_t &mask)
{
  mask = readReg(MCP23008_POL_A);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


// mask  = 0..0xFF  bit pattern
bool MCP23008::setPullup8(uint8_t mask)
{
  writeReg(MCP23008_PUR_A, mask);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


bool MCP23008::getPullup8(uint8_t &mask)
{
  mask = readReg(MCP23008_PUR_A);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


int MCP23008::lastError()
{
  int e = _error;
  _error = MCP23008_OK;  // reset error after read.
  return e;
}


////////////////////////////////////////////////////
//
// PRIVATE
// 

bool MCP23008::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  if (_wire->endTransmission() != 0)
  {
    _error = MCP23008_I2C_ERROR;
    return false;
  }
  _error = MCP23008_OK;
  return true;
}


uint8_t MCP23008::readReg(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  if (_wire->endTransmission() != 0)
  {
    _error = MCP23008_I2C_ERROR;
    return 0;
  }
  else
  {
    _error = MCP23008_OK;
  }
  uint8_t n = _wire->requestFrom(_address, (uint8_t)1);
  if (n != 1)
  {
    _error = MCP23008_I2C_ERROR;
    return 0;
  }
  return _wire->read();
}


// -- END OF FILE --

