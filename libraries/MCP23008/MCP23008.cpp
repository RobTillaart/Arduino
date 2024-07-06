//
//    FILE: MCP23008.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.4
// PURPOSE: Arduino library for I2C MCP23008 8 channel port expander
//    DATE: 2019-10-12
//     URL: https://github.com/RobTillaart/MCP23008


#include "MCP23008.h"


MCP23008::MCP23008(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
  _error   = MCP23008_OK;
}


bool MCP23008::begin(bool pullup)
{
  //  check connected
  if (! isConnected()) return false;

  //  disable address increment (datasheet P20
  //    SEQOP: Sequential Operation mode bit
  //    1 = Sequential operation disabled, address pointer does not increment.
  //    0 = Sequential operation enabled, address pointer increments.
  //  if (! writeReg(MCP23x08_IOCR, MCP23008_IOCR_SEQOP)) return false;

  if (pullup)
  {
    //  Force INPUT_PULLUP
    if (! writeReg(MCP23x08_PUR_A, 0xFF)) return false;   //  0xFF == all UP
  }
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


uint8_t MCP23008::getAddress()
{
  return _address;
}


///////////////////////////////////////////////////////////////////
//
//  single pin interface
//
//  pin  = 0..7
//  mode = INPUT, OUTPUT, INPUT_PULLUP (= same as INPUT)
//         do NOT use 0 or 1 for mode
bool MCP23008::pinMode1(uint8_t pin, uint8_t mode)
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

  uint8_t dataDirectionRegister = MCP23x08_DDR_A;
  uint8_t val = readReg(dataDirectionRegister);
  if (_error != MCP23008_OK)
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
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


//  pin   = 0..7
//  value = LOW, HIGH
bool MCP23008::write1(uint8_t pin, uint8_t value)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  uint8_t IOR = MCP23x08_GPIO_A;
  uint8_t val = readReg(IOR);
  uint8_t pre = val;
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
  //  only write when changed.
  if (pre != val)
  {
    writeReg(IOR, val);
    if (_error != MCP23008_OK)
    {
      return false;
    }
  }
  return true;
}


uint8_t MCP23008::read1(uint8_t pin)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return MCP23008_INVALID_READ;
  }
  uint8_t IOR = MCP23x08_GPIO_A;
  uint8_t val = readReg(IOR);
  if (_error != MCP23008_OK)
  {
    return MCP23008_INVALID_READ;
  }
  uint8_t mask = 1 << pin;
  if (val & mask) return HIGH;
  return LOW;
}


//  pin      = 0..7
//  reversed = true or false
bool MCP23008::setPolarity(uint8_t pin,  bool reversed)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23x08_POL_A;
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
  uint8_t inputPolarityRegister = MCP23x08_POL_A;
  uint8_t val = readReg(inputPolarityRegister);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  reversed = (val & mask) > 0;
  return true;
}


//  pin    = 0..7
//  pullup = true or false
bool MCP23008::setPullup(uint8_t pin,  bool pullup)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23x08_PUR_A;
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
  uint8_t inputPullupRegister = MCP23x08_PUR_A;
  uint8_t val = readReg(inputPullupRegister);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  pullup = (val & mask) > 0;
  return true;
}


///////////////////////////////////////////////////////////////////
//
//  8 pins interface
//
//  whole register at once
//  mask = 0x00..0xFF  bit pattern
//         bit 0 = output mode, bit 1 = input mode
bool MCP23008::pinMode8(uint8_t mask)
{
  writeReg(MCP23x08_DDR_A, mask);
  _error = MCP23008_OK;
  return true;
}


bool MCP23008::write8(uint8_t value)
{
  writeReg(MCP23x08_GPIO_A, value);
  _error = MCP23008_OK;
  return true;
}


int MCP23008::read8()
{
  _error = MCP23008_OK;
  return readReg(MCP23x08_GPIO_A);
}


//  mask  = 0..0xFF  bit pattern
bool MCP23008::setPolarity8(uint8_t mask)
{
  writeReg(MCP23x08_POL_A, mask);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


bool MCP23008::getPolarity8(uint8_t &mask)
{
  mask = readReg(MCP23x08_POL_A);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


//  mask  = 0..0xFF  bit pattern
bool MCP23008::setPullup8(uint8_t mask)
{
  writeReg(MCP23x08_PUR_A, mask);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


bool MCP23008::getPullup8(uint8_t &mask)
{
  mask = readReg(MCP23x08_PUR_A);
  if (_error != MCP23008_OK)
  {
    return false;
  }
  return true;
}


///////////////////////////////////////////////////
//
//  INTERRUPTS (experimental, see MCP23S17 - #40)
//
//  TODO, catch writeReg errors
//  TODO, MCP23x08_INT_MODE_ERROR?
//  TODO, if register not changed no need to update?
//  TODO, 8 bits optimize? more code vs speed?
//
//  pin = 0..7, mode = { RISING, FALLING, CHANGE }
bool MCP23008::enableInterrupt(uint8_t pin, uint8_t mode)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }

  //  right mode
  uint8_t intcon = readReg(MCP23x08_INTCON_A);
  if (mode == CHANGE)
  {
    //  compare to previous value.
    intcon &= ~(1 << pin);
  }
  else
  {
    uint8_t defval = readReg(MCP23x08_DEFVAL_A);
    if (mode == RISING)
    {
      intcon |= (1 << pin);
      defval &= ~(1 << pin);  //  RISING == compare to 0
    }
    else if (mode == FALLING)
    {
      intcon |= (1 << pin);
      defval |= ~(1 << pin);  //  FALLING == compare to 1
    }
    writeReg(MCP23x08_DEFVAL_A, defval);
  }
  writeReg(MCP23x08_INTCON_A, intcon);

  //  enable interrupt
  uint16_t value = readReg(MCP23x08_GPINTEN_A);
  value |= (1 << pin);
  return writeReg(MCP23x08_GPINTEN_A, value);
}


bool MCP23008::disableInterrupt(uint8_t pin)
{
  if (pin > 7)
  {
    _error = MCP23008_PIN_ERROR;
    return false;
  }
  //  disable interrupt
  uint16_t value = readReg(MCP23x08_GPINTEN_A);
  value &= ~(1 << pin);
  return writeReg(MCP23x08_GPINTEN_A, value);
}


//  which pins caused the INT?
uint8_t MCP23008::getInterruptFlagRegister()
{
  return readReg(MCP23x08_INTF_A);
}


uint8_t MCP23008::getInterruptCaptureRegister()
{
  return readReg(MCP23x08_INTCAP_A);
}


//       polarity: 0 = LOW, 1 = HIGH, 2 = NONE/ODR
bool MCP23008::setInterruptPolarity(uint8_t polarity)
{
  if (polarity > 2) return false;
  uint8_t reg = readReg(MCP23x08_IOCR);
  reg &= ~(MCP23x08_IOCR_ODR | MCP23x08_IOCR_INTPOL);
  //  LOW is default set.
  if (polarity == 2) reg |= MCP23x08_IOCR_ODR;
  if (polarity == 1) reg |= MCP23x08_IOCR_INTPOL;
  return writeReg(MCP23x08_IOCR, reg);
}


uint8_t MCP23008::getInterruptPolarity()
{
  uint8_t reg = readReg(MCP23x08_IOCR);
  if (reg & MCP23x08_IOCR_ODR) return 2;
  if (reg & MCP23x08_IOCR_INTPOL) return 1;
  return 0;
}


/////////////////////////////////////////////
//
//  MISC
//
int MCP23008::lastError()
{
  int e = _error;
  _error = MCP23008_OK;  //  reset error after read.
  return e;
}


bool MCP23008::enableControlRegister(uint8_t mask)
{
  uint8_t reg = readReg(MCP23x08_IOCR);
  reg |= mask;
  return writeReg(MCP23x08_IOCR, reg);
}


bool MCP23008::disableControlRegister(uint8_t mask)
{
  uint8_t reg = readReg(MCP23x08_IOCR);
  reg &= ~mask;
  return writeReg(MCP23x08_IOCR, reg);
}


////////////////////////////////////////////////////
//
//  DEBUG
//
uint8_t MCP23008::getPinMode8()
{
  return readReg(0);
}


////////////////////////////////////////////////////
//
//  PROTECTED
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
  uint8_t n = _wire->requestFrom(_address, (uint8_t)1);
  if (n != 1)
  {
    _error = MCP23008_I2C_ERROR;
    return 0;
  }
  _error = MCP23008_OK;
  return _wire->read();
}


//  -- END OF FILE --

