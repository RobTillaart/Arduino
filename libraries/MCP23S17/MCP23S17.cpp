//
//    FILE: MCP23S17.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for SPI MCP23S17 16 channel port expander
//    DATE: 2021-12-30
//     URL: https://github.com/RobTillaart/MCP23S17

//
//  HISTORY:
//  0.1.0   2021-12-30  initial version (a 2019 version did not make it)
//  0.1.1   2022-01-10  add 16 bit interface


#include "Arduino.h"
#include "MCP23S17.h"


//  Registers                         // description                 datasheet
#define MCP23S17_DDR_A        0x00    // Data Direction Register A   P18
#define MCP23S17_DDR_B        0x01    // Data Direction Register B   P18
#define MCP23S17_POL_A        0x02    // Input Polarity A            P18
#define MCP23S17_POL_B        0x03    // Input Polarity B            P18
#define MCP23S17_GPINTEN_A    0x04    // NOT USED interrupt enable   P19
#define MCP23S17_GPINTEN_B    0x05    // NOT USED
#define MCP23S17_DEFVAL_A     0x06    // NOT USED interrupt def      P19
#define MCP23S17_DEFVAL_B     0x07    // NOT USED
#define MCP23S17_INTCON_A     0x08    // NOT USED interrupt control  P20
#define MCP23S17_INTCON_B     0x09    // NOT USED
#define MCP23S17_IOCR         0x0A    // IO control register         P20
#define MCP23S17_IOCR2        0x0B    // NOT USED
#define MCP23S17_PUR_A        0x0C    // Pull Up Resistors A         P22
#define MCP23S17_PUR_B        0x0D    // Pull Up Resistors A         P22
#define MCP23S17_INTF_A       0x0E    // NOT USED interrupt flag     P22
#define MCP23S17_INTF_B       0x0F    // NOT USED
#define MCP23S17_INTCAP_A     0x10    // NOT USED interrupt capture  P23
#define MCP23S17_INTCAP_B     0x11    // NOT USED
#define MCP23S17_GPIO_A       0x12    // General Purpose IO A        P23
#define MCP23S17_GPIO_B       0x13    // General Purpose IO B        P23
#define MCP23S17_OLAT_A       0x14    // NOT USED output latch       P24
#define MCP23S17_OLAT_B       0x15    // NOT USED


// low level read / write masks
#define MCP23S17_WRITE_REG    0x40
#define MCP23S17_READ_REG     0x41

/*
MCP23S17::MCP23S17()
{
}
*/


MCP23S17::MCP23S17(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address)
{
  _address = address;
  _select  = select;
  _dataIn  = dataIn;
  _dataOut = dataOut;
  _clock   = clock;
  _error   = MCP23S17_OK;
  _hwSPI   = false;
}


MCP23S17::MCP23S17(uint8_t select, uint8_t address)
{
  _address = address;
  _select  = select;
  _error   = MCP23S17_OK;
  _hwSPI   = true;
}


bool MCP23S17::begin()
{
  ::pinMode(_select, OUTPUT);
  ::digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);//  8 MHz - datasheet page 8

  if (_hwSPI)
  {
    // TODO - ESP32 specific support - see MCP_ADC.
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

  // check connected
  if (! isConnected()) return false;

  // disable address increment (datasheet)
  if (! writeReg(MCP23S17_IOCR, 0b00100000)) return false;   // TODO MAGIC NR
  // Force INPUT_PULLUP
  if (! writeReg(MCP23S17_PUR_A, 0xFF)) return false;
  if (! writeReg(MCP23S17_PUR_B, 0xFF)) return false;
  return true;
}


bool MCP23S17::isConnected()
{
  _error = MCP23S17_OK;
  return true;
}


// single pin interface
// pin  = 0..15
// mode = INPUT, OUTPUT, INPUT_PULLUP (= same as INPUT)
bool MCP23S17::pinMode(uint8_t pin, uint8_t mode)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  if ((mode != INPUT) && (mode != INPUT_PULLUP) && (mode != OUTPUT))
  {
    _error = MCP23S17_VALUE_ERROR;
    return false;
  }

  uint8_t dataDirectionRegister = MCP23S17_DDR_A;
  if (pin > 7)
  {
    dataDirectionRegister = MCP23S17_DDR_B;
    pin -= 8;
  }
  uint8_t val = readReg(dataDirectionRegister);
  if (_error != MCP23S17_OK)
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
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


// pin   = 0..15
// value = LOW, HIGH
bool MCP23S17::digitalWrite(uint8_t pin, uint8_t value)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  uint8_t IOR = MCP23S17_GPIO_A;
  if (pin > 7)
  {
    IOR = MCP23S17_GPIO_B;
    pin -= 8;
  }

  uint8_t val = readReg(IOR);
  if (_error != MCP23S17_OK)
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
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


uint8_t MCP23S17::digitalRead(uint8_t pin)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return MCP23S17_INVALID_READ;
  }
  uint8_t IOR = MCP23S17_GPIO_A;
  if (pin > 7)
  {
    IOR = MCP23S17_GPIO_B;
    pin -= 8;
  }

  uint8_t val = readReg(IOR);
  if (_error != MCP23S17_OK)
  {
    return MCP23S17_INVALID_READ;
  }
  uint8_t mask = 1 << pin;
  if (val & mask) return HIGH;
  return LOW;
}


// pin  = 0..15
// reversed = true or false
bool MCP23S17::setPolarity(uint8_t pin,  bool reversed)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23S17_POL_A;
  if (pin > 7)
  {
    inputPolarityRegister = MCP23S17_POL_B;
    pin -= 8;
  }
  uint8_t val = readReg(inputPolarityRegister);
  if (_error != MCP23S17_OK)
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
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


bool MCP23S17::getPolarity(uint8_t pin, bool &reversed)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23S17_POL_A;
  if (pin > 7)
  {
    inputPolarityRegister = MCP23S17_POL_B;
    pin -= 8;
  }
  uint8_t val = readReg(inputPolarityRegister);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  reversed = (val & mask) > 0;
  return true;
}


// pin  = 0..15
// pullup = true or false
bool MCP23S17::setPullup(uint8_t pin,  bool pullup)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23S17_PUR_A;
  if (pin > 7)
  {
    inputPullupRegister = MCP23S17_PUR_B;
    pin -= 8;
  }
  uint8_t val = readReg(inputPullupRegister);
  if (_error != MCP23S17_OK)
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
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


bool MCP23S17::getPullup(uint8_t pin, bool &pullup)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23S17_PUR_A;
  if (pin > 7)
  {
    inputPullupRegister = MCP23S17_PUR_B;
    pin -= 8;
  }
  uint8_t val = readReg(inputPullupRegister);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  uint8_t mask = 1 << pin;
  pullup = (val & mask) > 0;
  return true;
}


void MCP23S17::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};



///////////////////////////////////////////////////////////////////////
// 8 pins interface
// whole register at once
// port  = 0..1
// value = 0..0xFF  bit pattern
bool MCP23S17::pinMode8(uint8_t port, uint8_t value)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23S17_DDR_A, value);
  if (port == 1) writeReg(MCP23S17_DDR_B, value);
  _error = MCP23S17_OK;
  return true;
}


bool MCP23S17::write8(uint8_t port, uint8_t value)   // port = 0..1
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23S17_GPIO_A, value);
  if (port == 1) writeReg(MCP23S17_GPIO_B, value);
  _error = MCP23S17_OK;
  return true;
}


int MCP23S17::read8(uint8_t port)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return MCP23S17_INVALID_READ;
  }
  _error = MCP23S17_OK;
  if (port == 0) return readReg(MCP23S17_GPIO_A);
  return readReg(MCP23S17_GPIO_B);  // port == 1
}


// port  = 0..1
// mask  = 0..0xFF  bit pattern
bool MCP23S17::setPolarity8(uint8_t port,  uint8_t mask)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23S17_POL_A, mask);
  if (port == 1) writeReg(MCP23S17_POL_B, mask);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


bool MCP23S17::getPolarity8(uint8_t port, uint8_t &mask)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) mask = readReg(MCP23S17_POL_A);
  if (port == 1) mask = readReg(MCP23S17_POL_B);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


// port  = 0..1
// mask  = 0..0xFF  bit pattern
bool MCP23S17::setPullup8(uint8_t port, uint8_t mask)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23S17_PUR_A, mask);
  if (port == 1) writeReg(MCP23S17_PUR_B, mask);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


bool MCP23S17::getPullup8(uint8_t port, uint8_t &mask)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) mask = readReg(MCP23S17_PUR_A);
  if (port == 1) mask = readReg(MCP23S17_PUR_B);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


///////////////////////////////////////////////////////////////////////
// 16 pins interface
// two register at once
// value = 0..0xFFFF bit pattern
bool MCP23S17::pinMode16(uint16_t value)
{
  writeReg(MCP23S17_DDR_A, value >> 8);
  writeReg(MCP23S17_DDR_B, value & 8);
  _error = MCP23S17_OK;
  return true;
}


// value = 0..0xFFFF   bit pattern
bool MCP23S17::write16(uint16_t value)
{
  writeReg(MCP23S17_GPIO_A, value >> 8);
  writeReg(MCP23S17_GPIO_B, value & 8);
  _error = MCP23S17_OK;
  return true;
}


// return = 0..0xFFFF  bit pattern
uint16_t MCP23S17::read16()
{
  _error = MCP23S17_OK;
  uint16_t value = readReg(MCP23S17_GPIO_A);
  value <<= 8;
  value += readReg(MCP23S17_GPIO_B);
  return value;
}


// mask = 0..0xFFFF  bit pattern
bool MCP23S17::setPolarity16(uint16_t mask)
{
  writeReg(MCP23S17_POL_A, mask >> 8);
  writeReg(MCP23S17_POL_B, mask & 8);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


// mask = 0..0xFFFF  bit pattern
bool MCP23S17::getPolarity16(uint16_t &mask)
{
  mask = readReg(MCP23S17_POL_A);
  mask <<= 8;
  mask += readReg(MCP23S17_POL_B);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


// mask = 0..0xFFFF  bit pattern
bool MCP23S17::setPullup16(uint16_t mask)
{
  writeReg(MCP23S17_PUR_A, mask >> 8);
  writeReg(MCP23S17_PUR_B, mask & 8);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


// mask = 0..0xFFFF  bit pattern
bool MCP23S17::getPullup16(uint16_t &mask)
{
  mask = readReg(MCP23S17_PUR_A);
  mask <<= 8;
  mask += readReg(MCP23S17_PUR_B);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


int MCP23S17::lastError()
{
  int e = _error;
  _error = MCP23S17_OK;  // reset error after read.
  return e;
}


////////////////////////////////////////////////////
//
// PRIVATE
//

bool MCP23S17::writeReg(uint8_t reg, uint8_t value)
{
  _error = MCP23S17_OK;

  if (reg > MCP23S17_OLAT_B)
  {
    _error = 0xFF;   // TODO MAGIC NR
    return false;
  }
  ::digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer(MCP23S17_WRITE_REG | (_address << 1) );
    mySPI->transfer(reg);
    mySPI->transfer(value);
    mySPI->endTransaction();
  }
  else
  {
    swSPI_transfer(MCP23S17_WRITE_REG | (_address << 1) );
    swSPI_transfer(reg);
    swSPI_transfer(value);
  }
  ::digitalWrite(_select, HIGH);
  return true;
}


uint8_t MCP23S17::readReg(uint8_t reg)
{
  uint8_t rv = 0;

  _error = MCP23S17_OK;

  if (reg > MCP23S17_OLAT_B)
  {
    _error = 0xFF;   // TODO MAGIC NR
    return false;
  }

  ::digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    mySPI->transfer(MCP23S17_READ_REG | (_address << 1) );  // TODO OPTIMIZE n times
    mySPI->transfer(reg);
    rv = mySPI->transfer(0xFF);
    mySPI->endTransaction();
  }
  else
  {
    swSPI_transfer(MCP23S17_READ_REG | (_address << 1) );
    swSPI_transfer(reg);
    rv = swSPI_transfer(0xFF);
  }
  ::digitalWrite(_select, HIGH);
  return rv;
}


uint8_t  MCP23S17::swSPI_transfer(uint8_t val)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  uint8_t dai = _dataIn;

  uint8_t rv = 0;
  for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
  {
    ::digitalWrite(dao, (val & mask));
    ::digitalWrite(clk, HIGH);
    if (::digitalRead(dai) == HIGH) rv |= mask;
    ::digitalWrite(clk, LOW);
  }
  return rv;
}


// -- END OF FILE --

