//
//    FILE: MCP23S08.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library for SPI MCP23S08 8 channel port expander
//    DATE: 2022-01-10
//     URL: https://github.com/RobTillaart/MCP23S08


#include "Arduino.h"
#include "MCP23S08.h"


//  Registers                        //  description              datasheet P9
#define MCP23S08_DDR_A        0x00   //  Data Direction Register A   P 10
#define MCP23S08_POL_A        0x01   //  Input Polarity A            P 11
#define MCP23S08_GPINTEN_A    0x02   //  NOT USED interrupt enable   P 12
#define MCP23S08_DEFVAL_A     0x03   //  NOT USED interrupt def      P 13
#define MCP23S08_INTCON_A     0x04   //  NOT USED interrupt control  P 14
#define MCP23S08_IOCR         0x05   //  IO control register         P 15
#define MCP23S08_PUR_A        0x06   //  Pull Up Resistors A         P 16
#define MCP23S08_INTF_A       0x07   //  NOT USED interrupt flag     P 17
#define MCP23S08_INTCAP_A     0x08   //  NOT USED interrupt capture  P 18
#define MCP23S08_GPIO_A       0x09   //  General Purpose IO A        P 19
#define MCP23S08_OLAT_A       0x0A   //  NOT USED output latch       P 20


// low level read / write masks
#define MCP23S08_WRITE_REG    0x40
#define MCP23S08_READ_REG     0x41


MCP23S08::MCP23S08(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address)
{
  _address = address;
  _select  = select;
  _dataIn  = dataIn;
  _dataOut = dataOut;
  _clock   = clock;
  _error   = MCP23S08_OK;
  _hwSPI   = false;
}


MCP23S08::MCP23S08(uint8_t select, uint8_t address)
{
  _address = address;
  _select  = select;
  _error   = MCP23S08_OK;
  _hwSPI   = true;
}


bool MCP23S08::begin()
{
  ::pinMode(_select, OUTPUT);
  ::digitalWrite(_select, HIGH);

  //  8 MHz - datasheet page 8
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

  if (_hwSPI)
  {
    //  TODO - ESP32 specific support - see MCP_ADC.
    mySPI = &SPI;
    mySPI->end();
    mySPI->begin();
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

  //  disable address increment (datasheet)
  if (! writeReg(MCP23S08_IOCR, 0b00100000)) return false;   //  TODO MAGIC NR
  //  Force INPUT_PULLUP
  if (! writeReg(MCP23S08_PUR_A, 0xFF)) return false;
  return true;
}


bool MCP23S08::isConnected()
{
  _error = MCP23S08_OK;
  return true;
}


//  single pin interface
//  pin  = 0..7
//  mode = INPUT, OUTPUT, INPUT_PULLUP (= same as INPUT)
bool MCP23S08::pinMode(uint8_t pin, uint8_t mode)
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
bool MCP23S08::digitalWrite(uint8_t pin, uint8_t value)
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


uint8_t MCP23S08::digitalRead(uint8_t pin)
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



///////////////////////////////////////////////////////////////////////
//
//  8 pins interface
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


////////////////////////////////////////////////////
//
//  PRIVATE
//

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
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer(MCP23S08_WRITE_REG | (_address << 1) );
    mySPI->transfer(reg);
    mySPI->transfer(value);
    mySPI->endTransaction();
  }
  else
  {
    swSPI_transfer(MCP23S08_WRITE_REG | (_address << 1) );
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
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer(MCP23S08_READ_REG | (_address << 1) );  // TODO OPTIMIZE n times
    mySPI->transfer(reg);
    rv = mySPI->transfer(0xFF);
    mySPI->endTransaction();
  }
  else
  {
    swSPI_transfer(MCP23S08_READ_REG | (_address << 1) );
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

