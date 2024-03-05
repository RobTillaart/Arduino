//
//    FILE: MCP23017.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.6.2
// PURPOSE: Arduino library for I2C MCP23017 16 channel port expander
//    DATE: 2019-10-12
//     URL: https://github.com/RobTillaart/MCP23017_RT
//
// WARNING: please read REV D note in readme.md.


#include "MCP23017.h"


//  Registers                         //  DESCRIPTION                  DATASHEET
#define MCP23017_DDR_A        0x00    //  Data Direction Register A       P18
#define MCP23017_DDR_B        0x01    //  Data Direction Register B       P18
#define MCP23017_POL_A        0x02    //  Input Polarity A                P18
#define MCP23017_POL_B        0x03    //  Input Polarity B                P18
#define MCP23017_GPINTEN_A    0x04    //  NOT USED interrupt enable       P19
#define MCP23017_GPINTEN_B    0x05    //  NOT USED
#define MCP23017_DEFVAL_A     0x06    //  NOT USED interrupt def          P19
#define MCP23017_DEFVAL_B     0x07    //  NOT USED
#define MCP23017_INTCON_A     0x08    //  NOT USED interrupt control      P20
#define MCP23017_INTCON_B     0x09    //  NOT USED
#define MCP23017_IOCR         0x0A    //  IO control register             P20
#define MCP23017_IOCR2        0x0B    //  NOT USED
#define MCP23017_PUR_A        0x0C    //  Pull Up Resistors A             P22
#define MCP23017_PUR_B        0x0D    //  Pull Up Resistors A             P22
#define MCP23017_INTF_A       0x0E    //  NOT USED interrupt flag         P22
#define MCP23017_INTF_B       0x0F    //  NOT USED
#define MCP23017_INTCAP_A     0x10    //  NOT USED interrupt capture      P23
#define MCP23017_INTCAP_B     0x11    //  NOT USED
#define MCP23017_GPIO_A       0x12    //  General Purpose IO A            P23
#define MCP23017_GPIO_B       0x13    //  General Purpose IO B            P23
#define MCP23017_OLAT_A       0x14    //  NOT USED output latch           P24
#define MCP23017_OLAT_B       0x15    //  NOT USED


MCP23017::MCP23017(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
  _error   = MCP23017_OK;
}


bool MCP23017::begin(bool pullup)
{
  //  check connected
  if (! isConnected()) return false;
  //  disable address increment (datasheet)
  if (! writeReg(MCP23017_IOCR, 0b00100000)) return false;
  if (pullup)
  {
    //  Force INPUT_PULLUP
    if (! writeReg(MCP23017_PUR_A, 0xFF)) return false;
    if (! writeReg(MCP23017_PUR_B, 0xFF)) return false;
  }
  return true;
}


bool MCP23017::isConnected()
{
  _wire->beginTransmission(_address);
  if (_wire->endTransmission() != 0)
  {
    _error = MCP23017_I2C_ERROR;
    return false;
  }
  _error = MCP23017_OK;
  return true;
}


uint8_t MCP23017::getAddress()
{
  return _address;
}


//  single pin interface
//  pin  = 0..15
//  mode = INPUT, OUTPUT, INPUT_PULLUP (= same as INPUT)
bool MCP23017::pinMode1(uint8_t pin, uint8_t mode)
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return false;
  }
  if ((mode != INPUT) && (mode != INPUT_PULLUP) && (mode != OUTPUT))
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
  if (_error != MCP23017_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  //  only work with valid
  if ((mode == INPUT) || (mode == INPUT_PULLUP))
  {
    val |= mask;
  }
  else if (mode == OUTPUT)
  {
    val &= ~mask;
  }
  //  other values won't change val ....
  writeReg(dataDirectionRegister, val);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


//  pin   = 0..15
//  value = LOW, HIGH
bool MCP23017::write1(uint8_t pin, uint8_t value)
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return false;
  }
  uint8_t IOR = MCP23017_GPIO_A;
  if (pin > 7)
  {
    IOR = MCP23017_GPIO_B;
    pin -= 8;
  }

  uint8_t val = readReg(IOR);
  uint8_t pre = val;
  if (_error != MCP23017_OK)
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
  if (pre != val)
  {
    writeReg(IOR, val);
    if (_error != MCP23017_OK)
    {
      return false;
    }
  }
  return true;
}


uint8_t MCP23017::read1(uint8_t pin)
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return MCP23017_INVALID_READ;
  }
  uint8_t IOR = MCP23017_GPIO_A;
  if (pin > 7)
  {
    IOR = MCP23017_GPIO_B;
    pin -= 8;
  }

  uint8_t val = readReg(IOR);
  if (_error != MCP23017_OK)
  {
    return MCP23017_INVALID_READ;
  }
  uint8_t mask = 1 << pin;
  if (val & mask) return HIGH;
  return LOW;
}


//  pin  = 0..15
//  reverse = true or false
bool MCP23017::setPolarity(uint8_t pin,  bool reversed)
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23017_POL_A;
  if (pin > 7)
  {
    inputPolarityRegister = MCP23017_POL_B;
    pin -= 8;
  }
  uint8_t val = readReg(inputPolarityRegister);
  if (_error != MCP23017_OK)
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
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


bool MCP23017::getPolarity(uint8_t pin, bool &reversed)
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23017_POL_A;
  if (pin > 7)
  {
    inputPolarityRegister = MCP23017_POL_B;
    pin -= 8;
  }
  uint8_t val = readReg(inputPolarityRegister);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  reversed = (val & mask) > 0;
  return true;
}


//  pin  = 0..15
//  reverse = true or false
bool MCP23017::setPullup(uint8_t pin,  bool pullup)
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23017_PUR_A;
  if (pin > 7)
  {
    inputPullupRegister = MCP23017_PUR_B;
    pin -= 8;
  }
  uint8_t val = readReg(inputPullupRegister);
  if (_error != MCP23017_OK)
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
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


bool MCP23017::getPullup(uint8_t pin, bool &pullup)
{
  if (pin > 15)
  {
    _error = MCP23017_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23017_PUR_A;
  if (pin > 7)
  {
    inputPullupRegister = MCP23017_PUR_B;
    pin -= 8;
  }
  uint8_t val = readReg(inputPullupRegister);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  pullup = (val & mask) > 0;
  return true;
}


///////////////////////////////////////////////////////////////////////
//
//  8 pins interface
//  whole register at once
//  port  = 0..1
//  value = 0..0xFF  bit pattern
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
  if (port == 0) writeReg(MCP23017_GPIO_A, value);
  if (port == 1) writeReg(MCP23017_GPIO_B, value);
  _error = MCP23017_OK;
  return true;
}


int MCP23017::read8(uint8_t port)
{
  if (port > 1)
  {
    _error = MCP23017_PORT_ERROR;
    return MCP23017_INVALID_READ;
  }
  _error = MCP23017_OK;
  if (port == 0) return readReg(MCP23017_GPIO_A);
  return readReg(MCP23017_GPIO_B);  // port == 1
}


//  port  = 0..1
//  mask  = 0..0xFF  bit pattern
bool MCP23017::setPolarity8(uint8_t port,  uint8_t mask)
{
  if (port > 1)
  {
    _error = MCP23017_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23017_POL_A, mask);
  if (port == 1) writeReg(MCP23017_POL_B, mask);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


bool MCP23017::getPolarity8(uint8_t port, uint8_t &mask)
{
  if (port > 1)
  {
    _error = MCP23017_PORT_ERROR;
    return false;
  }
  if (port == 0) mask = readReg(MCP23017_POL_A);
  if (port == 1) mask = readReg(MCP23017_POL_B);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


//  port  = 0..1
//  mask  = 0..0xFF  bit pattern
bool MCP23017::setPullup8(uint8_t port, uint8_t mask)
{
  if (port > 1)
  {
    _error = MCP23017_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23017_PUR_A, mask);
  if (port == 1) writeReg(MCP23017_PUR_B, mask);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


bool MCP23017::getPullup8(uint8_t port, uint8_t &mask)
{
  if (port > 1)
  {
    _error = MCP23017_PORT_ERROR;
    return false;
  }
  if (port == 0) mask = readReg(MCP23017_PUR_A);
  if (port == 1) mask = readReg(MCP23017_PUR_B);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


///////////////////////////////////////////////////////////////////////
//
//  16 pins interface
//  two register at once
//  value = 0x0000..0xFFFF bit pattern
bool MCP23017::pinMode16(uint16_t value)
{
  writeReg(MCP23017_DDR_A, value >> 8);
  writeReg(MCP23017_DDR_B, value & 0xFF);
  _error = MCP23017_OK;
  return true;
}


//  value = 0x0000..0xFFFF   bit pattern
bool MCP23017::write16(uint16_t value)
{
  writeReg(MCP23017_GPIO_A, value >> 8);
  writeReg(MCP23017_GPIO_B, value & 0xFF);
  _error = MCP23017_OK;
  return true;
}


//  return = 0x0000..0xFFFF  bit pattern
uint16_t MCP23017::read16()
{
  _error = MCP23017_OK;
  uint16_t value = readReg(MCP23017_GPIO_A);
  value <<= 8;
  value += readReg(MCP23017_GPIO_B);
  return value;
}


//  mask = 0x0000..0xFFFF  bit pattern
bool MCP23017::setPolarity16(uint16_t mask)
{
  writeReg(MCP23017_POL_A, mask >> 8);
  writeReg(MCP23017_POL_B, mask & 0xFF);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


//  mask = 0x0000..0xFFFF  bit pattern
bool MCP23017::getPolarity16(uint16_t &mask)
{
  mask = readReg(MCP23017_POL_A);
  mask <<= 8;
  mask += readReg(MCP23017_POL_B);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


//  mask = 0x0000..0xFFFF  bit pattern
bool MCP23017::setPullup16(uint16_t mask)
{
  writeReg(MCP23017_PUR_A, mask >> 8);
  writeReg(MCP23017_PUR_B, mask & 0xFF);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


//  mask = 0x0000..0xFFFF  bit pattern
bool MCP23017::getPullup16(uint16_t &mask)
{
  mask = readReg(MCP23017_PUR_A);
  mask <<= 8;
  mask += readReg(MCP23017_PUR_B);
  if (_error != MCP23017_OK)
  {
    return false;
  }
  return true;
}


int MCP23017::lastError()
{
  int e = _error;
  _error = MCP23017_OK;     //  reset error after read.
  return e;
}


////////////////////////////////////////////////////
//
//  PRIVATE
//

bool MCP23017::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
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
  _wire->beginTransmission(_address);
  _wire->write(reg);
  if (_wire->endTransmission() != 0)
  {
    _error = MCP23017_I2C_ERROR;
    return 0;
  }
  else
  {
    _error = MCP23017_OK;
  }
  uint8_t n = _wire->requestFrom(_address, (uint8_t)1);
  if (n != 1)
  {
    _error = MCP23017_I2C_ERROR;
    return 0;
  }
  return _wire->read();
}


//  -- END OF FILE --

