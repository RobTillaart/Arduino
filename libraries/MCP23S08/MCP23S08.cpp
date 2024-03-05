//
//    FILE: MCP23S08.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.1
// PURPOSE: Arduino library for SPI MCP23S08 8 channel port expander
//    DATE: 2022-01-10
//     URL: https://github.com/RobTillaart/MCP23S08


#include "MCP23S08.h"


//  SOFTWARE SPI
MCP23S08::MCP23S08(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address)
{
  _address = (address << 1);
  _select  = select;
  _dataIn  = dataIn;
  _dataOut = dataOut;
  _clock   = clock;
  _error   = MCP23S08_OK;
  _hwSPI   = false;
}


//  HARDWARE SPI
MCP23S08::MCP23S08(int select, __SPI_CLASS__ * spi)
{
  MCP23S08(select, 0x00, spi);
}


//  HARDWARE SPI
MCP23S08::MCP23S08(int select, int address, __SPI_CLASS__ * spi)
{
  _address = (address << 1);
  _select  = select;
  _error   = MCP23S08_OK;
  _mySPI   = spi;
  _hwSPI   = true;
}


bool MCP23S08::begin(bool pullup)
{
  ::pinMode(_select, OUTPUT);
  ::digitalWrite(_select, HIGH);

  //  8 MHz - datasheet page 8
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

  if (_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
  }
  else
  {
    ::pinMode(_dataIn,  INPUT);
    ::pinMode(_dataOut, OUTPUT);
    ::pinMode(_clock,   OUTPUT);
    ::digitalWrite(_dataOut, LOW);
    ::digitalWrite(_clock,   LOW);
  }

  //  check connected
  if (! isConnected()) return false;

  //  disable address increment (datasheet P20
  //    SEQOP: Sequential Operation mode bit
  //    1 = Sequential operation disabled, address pointer does not increment.
  //    0 = Sequential operation enabled, address pointer increments.
  if (! writeReg(MCP23S08_IOCR, MCP23S08_IOCR_SEQOP)) return false;

  if (pullup)
  {
    //  Force INPUT_PULLUP
    if (! writeReg(MCP23S08_PUR_A, 0xFF)) return false;   //  0xFF == all UP
  }
  return true;
}


bool MCP23S08::isConnected()
{
  _error = MCP23S08_OK;
  return true;
}


uint8_t MCP23S08::getAddress()
{
  return (_address >> 1);
}


///////////////////////////////////////////////////////////////////
//
//  single pin interface
//
//  pin  = 0..7
//  mode = INPUT, OUTPUT, INPUT_PULLUP (= same as INPUT)
bool MCP23S08::pinMode1(uint8_t pin, uint8_t mode)
{
  if (pin > 7)
  {
    _error = MCP23S08_PIN_ERROR;
    return false;
  }
  if ((mode != INPUT) && (mode != INPUT_PULLUP) && (mode != OUTPUT))
  {
    _error = MCP23S08_VALUE_ERROR;
    return false;
  }

  uint8_t dataDirectionRegister = MCP23S08_DDR_A;
  uint8_t val = readReg(dataDirectionRegister);
  if (_error != MCP23S08_OK)
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
  if (_error != MCP23S08_OK)
  {
    return false;
  }
  return true;
}


//  pin   = 0..7
//  value = LOW, HIGH
bool MCP23S08::write1(uint8_t pin, uint8_t value)
{
  if (pin > 7)
  {
    _error = MCP23S08_PIN_ERROR;
    return false;
  }
  uint8_t IOR = MCP23S08_GPIO_A;
  uint8_t val = readReg(IOR);
  uint8_t pre = val;
  if (_error != MCP23S08_OK)
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
    if (_error != MCP23S08_OK)
    {
      return false;
    }
  }
  return true;
}


uint8_t MCP23S08::read1(uint8_t pin)
{
  if (pin > 7)
  {
    _error = MCP23S08_PIN_ERROR;
    return MCP23S08_INVALID_READ;
  }
  uint8_t IOR = MCP23S08_GPIO_A;
  uint8_t val = readReg(IOR);
  if (_error != MCP23S08_OK)
  {
    return MCP23S08_INVALID_READ;
  }
  uint8_t mask = 1 << pin;
  if (val & mask) return HIGH;
  return LOW;
}


//  pin  = 0..7
//  reversed = true or false
bool MCP23S08::setPolarity(uint8_t pin,  bool reversed)
{
  if (pin > 7)
  {
    _error = MCP23S08_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23S08_POL_A;
  uint8_t val = readReg(inputPolarityRegister);
  if (_error != MCP23S08_OK)
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
  if (_error != MCP23S08_OK)
  {
    return false;
  }
  return true;
}


bool MCP23S08::getPolarity(uint8_t pin, bool &reversed)
{
  if (pin > 7)
  {
    _error = MCP23S08_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23S08_POL_A;
  uint8_t val = readReg(inputPolarityRegister);
  if (_error != MCP23S08_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  reversed = (val & mask) > 0;
  return true;
}


//  pin  = 0..7
//  pullup = true or false
bool MCP23S08::setPullup(uint8_t pin,  bool pullup)
{
  if (pin > 7)
  {
    _error = MCP23S08_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23S08_PUR_A;
  uint8_t val = readReg(inputPullupRegister);
  if (_error != MCP23S08_OK)
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
  if (_error != MCP23S08_OK)
  {
    return false;
  }
  return true;
}


bool MCP23S08::getPullup(uint8_t pin, bool &pullup)
{
  if (pin > 7)
  {
    _error = MCP23S08_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23S08_PUR_A;
  uint8_t val = readReg(inputPullupRegister);
  if (_error != MCP23S08_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  pullup = (val & mask) > 0;
  return true;
}


void MCP23S08::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};


///////////////////////////////////////////////////////////////////
//
//  8 pins interface
//
//  whole register at once
//  value = 0..0xFF  bit pattern
bool MCP23S08::pinMode8(uint8_t value)
{
  writeReg(MCP23S08_DDR_A, value);
  _error = MCP23S08_OK;
  return true;
}


bool MCP23S08::write8(uint8_t value)
{
  writeReg(MCP23S08_GPIO_A, value);
  _error = MCP23S08_OK;
  return true;
}


int MCP23S08::read8()
{
  _error = MCP23S08_OK;
  return readReg(MCP23S08_GPIO_A);
}


//  mask  = 0..0xFF  bit pattern
bool MCP23S08::setPolarity8(uint8_t mask)
{
  writeReg(MCP23S08_POL_A, mask);
  if (_error != MCP23S08_OK)
  {
    return false;
  }
  return true;
}


bool MCP23S08::getPolarity8(uint8_t &mask)
{
  mask = readReg(MCP23S08_POL_A);
  if (_error != MCP23S08_OK)
  {
    return false;
  }
  return true;
}


//  mask  = 0..0xFF  bit pattern
bool MCP23S08::setPullup8(uint8_t mask)
{
  writeReg(MCP23S08_PUR_A, mask);
  if (_error != MCP23S08_OK)
  {
    return false;
  }
  return true;
}


bool MCP23S08::getPullup8(uint8_t &mask)
{
  mask = readReg(MCP23S08_PUR_A);
  if (_error != MCP23S08_OK)
  {
    return false;
  }
  return true;
}


int MCP23S08::lastError()
{
  int e = _error;
  _error = MCP23S08_OK;  //  reset error after read.
  return e;
}


void MCP23S08::enableControlRegister(uint8_t mask)
{
  uint8_t reg = readReg(MCP23S08_IOCR);
  reg |= mask;
  writeReg(MCP23S08_IOCR, reg);
}


void MCP23S08::disableControlRegister(uint8_t mask)
{
  uint8_t reg = readReg(MCP23S08_IOCR);
  reg &= ~mask;
  writeReg(MCP23S08_IOCR, reg);
}


void MCP23S08::enableHardwareAddress()
{
  enableControlRegister(MCP23S08_IOCR_HAEN);
}


void MCP23S08::disableHardwareAddress()
{
  disableControlRegister(MCP23S08_IOCR_HAEN);
}


////////////////////////////////////////////////////
//
//  PRIVATE
//


//  low level read / write masks
#define MCP23S08_WRITE_REG    0x40
#define MCP23S08_READ_REG     0x41


bool MCP23S08::writeReg(uint8_t reg, uint8_t value)
{
  _error = MCP23S08_OK;

  if (reg > MCP23S08_OLAT_A)
  {
    _error = MCP23S08_REGISTER_ERROR;
    return false;
  }
  ::digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    //  _address already shifted
    _mySPI->transfer(MCP23S08_WRITE_REG | _address );
    _mySPI->transfer(reg);
    _mySPI->transfer(value);
    _mySPI->endTransaction();
  }
  else
  {
    //  _address already shifted
    swSPI_transfer(MCP23S08_WRITE_REG | _address );
    swSPI_transfer(reg);
    swSPI_transfer(value);
  }
  ::digitalWrite(_select, HIGH);
  return true;
}


uint8_t MCP23S08::readReg(uint8_t reg)
{
  uint8_t rv = 0;

  _error = MCP23S08_OK;

  if (reg > MCP23S08_OLAT_A)
  {
    _error = MCP23S08_REGISTER_ERROR;
    return false;
  }

  ::digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    //  _address already shifted
    _mySPI->transfer(MCP23S08_READ_REG | _address );  // TODO OPTIMIZE n times
    _mySPI->transfer(reg);
    rv = _mySPI->transfer(0xFF);
    _mySPI->endTransaction();
  }
  else
  {
    //  _address already shifted
    swSPI_transfer(MCP23S08_READ_REG | _address );
    swSPI_transfer(reg);
    rv = swSPI_transfer(0xFF);
  }
  ::digitalWrite(_select, HIGH);
  return rv;
}


uint8_t  MCP23S08::swSPI_transfer(uint8_t value)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  uint8_t dai = _dataIn;

  uint8_t rv = 0;
  for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
  {
    ::digitalWrite(dao, (value & mask) ? HIGH : LOW);
    ::digitalWrite(clk, HIGH);
    if (::digitalRead(dai) == HIGH) rv |= mask;
    ::digitalWrite(clk, LOW);
  }
  return rv;
}


//  -- END OF FILE --

