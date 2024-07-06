//
//    FILE: MCP23S17.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.4
// PURPOSE: Arduino library for SPI MCP23S17 16 channel port expander
//    DATE: 2021-12-30
//     URL: https://github.com/RobTillaart/MCP23S17


#include "MCP23S17.h"


//  SOFTWARE SPI
MCP23S17::MCP23S17(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address)
{
  _address = (address << 1);
  _select  = select;
  _dataIn  = dataIn;
  _dataOut = dataOut;
  _clock   = clock;
  _error   = MCP23S17_OK;
  _hwSPI   = false;
}


//  HARDWARE SPI
MCP23S17::MCP23S17(int select, __SPI_CLASS__ * spi)
{
  MCP23S17(select, 0x00, spi);
}


MCP23S17::MCP23S17(int select, int address, __SPI_CLASS__ * spi)
{
  _address = (address << 1);
  _select  = select;
  _error   = MCP23S17_OK;
  _mySPI   = spi;
  _hwSPI   = true;
}


bool MCP23S17::begin(bool pullup)
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

  //  disable address increment - datasheet P20
  //  note that address increment must be enabled for readReg16() and writeReg16() to work.
  //    SEQOP: Sequential Operation mode bit
  //    1 = Sequential operation disabled, address pointer does not increment.
  //    0 = Sequential operation enabled, address pointer increments.
  uint8_t reg = readReg(MCP23x17_IOCR);
  if (reg & MCP23x17_IOCR_SEQOP)  //  check if already zero
  {
    reg &= ~MCP23x17_IOCR_SEQOP;  //  clear SEQOP bit for sequential read/write
    if (! writeReg(MCP23x17_IOCR, reg)) return false;
  }

  if (pullup)
  {
    //  Force INPUT_PULLUP
    if (! writeReg(MCP23x17_PUR_A, 0xFF)) return false;   //  0xFF == all UP
    if (! writeReg(MCP23x17_PUR_B, 0xFF)) return false;   //  0xFF == all UP
  }
  return true;
}


//  just to keep interface in sync with I2C MCP23017 library.
bool MCP23S17::isConnected()
{
  _error = MCP23S17_OK;
  return true;
}


uint8_t MCP23S17::getAddress()
{
  return (_address >> 1);
}


///////////////////////////////////////////////////////////////////
//
//  single pin interface
//
//  pin  = 0..15
//  mode = INPUT, OUTPUT, INPUT_PULLUP (= same as INPUT)
//         do NOT use 0 or 1 for mode.
bool MCP23S17::pinMode1(uint8_t pin, uint8_t mode)
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

  uint8_t dataDirectionRegister = MCP23x17_DDR_A;
  if (pin > 7)
  {
    dataDirectionRegister = MCP23x17_DDR_B;
    pin -= 8;
  }
  uint8_t val = readReg(dataDirectionRegister);
  if (_error != MCP23S17_OK)
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
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


//  pin   = 0..15
//  value = LOW, HIGH
bool MCP23S17::write1(uint8_t pin, uint8_t value)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  uint8_t IOR = MCP23x17_GPIO_A;
  if (pin > 7)
  {
    IOR = MCP23x17_GPIO_B;
    pin -= 8;
  }

  uint8_t val = readReg(IOR);
  uint8_t pre = val;
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
  //  only write when changed.
  if (pre != val)
  {
    writeReg(IOR, val);
    if (_error != MCP23S17_OK)
    {
      return false;
    }
  }
  return true;
}


uint8_t MCP23S17::read1(uint8_t pin)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return MCP23S17_INVALID_READ;
  }
  uint8_t IOR = MCP23x17_GPIO_A;
  if (pin > 7)
  {
    IOR = MCP23x17_GPIO_B;
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


//  pin  = 0..15
//  reversed = true or false
bool MCP23S17::setPolarity(uint8_t pin,  bool reversed)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  uint8_t inputPolarityRegister = MCP23x17_POL_A;
  if (pin > 7)
  {
    inputPolarityRegister = MCP23x17_POL_B;
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
  uint8_t inputPolarityRegister = MCP23x17_POL_A;
  if (pin > 7)
  {
    inputPolarityRegister = MCP23x17_POL_B;
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


//  pin  = 0..15
//  pullup = true or false
bool MCP23S17::setPullup(uint8_t pin,  bool pullup)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  uint8_t inputPullupRegister = MCP23x17_PUR_A;
  if (pin > 7)
  {
    inputPullupRegister = MCP23x17_PUR_B;
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
  uint8_t inputPullupRegister = MCP23x17_PUR_A;
  if (pin > 7)
  {
    inputPullupRegister = MCP23x17_PUR_B;
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


///////////////////////////////////////////////////////////////////
//
//  8 pins interface
//
//  whole register at once
//  port = 0..1
//  mask = 0x00..0xFF  bit pattern
//         bit 0 = output mode, bit 1 = input mode
bool MCP23S17::pinMode8(uint8_t port, uint8_t mask)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23x17_DDR_A, mask);
  if (port == 1) writeReg(MCP23x17_DDR_B, mask);
  _error = MCP23S17_OK;
  return true;
}


//  port = 0..1
bool MCP23S17::write8(uint8_t port, uint8_t value)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23x17_GPIO_A, value);
  if (port == 1) writeReg(MCP23x17_GPIO_B, value);
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
  if (port == 0) return readReg(MCP23x17_GPIO_A);
  return readReg(MCP23x17_GPIO_B);  //  port == 1
}


//  port  = 0..1
//  mask  = 0..0xFF  bit pattern
bool MCP23S17::setPolarity8(uint8_t port,  uint8_t mask)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23x17_POL_A, mask);
  if (port == 1) writeReg(MCP23x17_POL_B, mask);
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
  if (port == 0) mask = readReg(MCP23x17_POL_A);
  if (port == 1) mask = readReg(MCP23x17_POL_B);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


//  port  = 0..1
//  mask  = 0..0xFF  bit pattern
bool MCP23S17::setPullup8(uint8_t port, uint8_t mask)
{
  if (port > 1)
  {
    _error = MCP23S17_PORT_ERROR;
    return false;
  }
  if (port == 0) writeReg(MCP23x17_PUR_A, mask);
  if (port == 1) writeReg(MCP23x17_PUR_B, mask);
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
  if (port == 0) mask = readReg(MCP23x17_PUR_A);
  if (port == 1) mask = readReg(MCP23x17_PUR_B);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


///////////////////////////////////////////////////////////////////
//
//  16 pins interface
//
//  two registers at once
//  mask = 0x0000..0xFFFF bit pattern
//         bit 0 = output mode, bit 1 = input mode
bool MCP23S17::pinMode16(uint16_t mask)
{
  writeReg16(MCP23x17_DDR_A, mask);
  _error = MCP23S17_OK;
  return true;
}


//  value = 0x0000..0xFFFF   bit pattern
bool MCP23S17::write16(uint16_t value)
{
  writeReg16(MCP23x17_GPIO_A, value);
  _error = MCP23S17_OK;
  return true;
}


//  return = 0x0000..0xFFFF  bit pattern
uint16_t MCP23S17::read16()
{
  _error = MCP23S17_OK;
  uint16_t value = readReg16(MCP23x17_GPIO_A);
  return value;
}


//  mask = 0x0000..0xFFFF  bit pattern
bool MCP23S17::setPolarity16(uint16_t mask)
{
  writeReg16(MCP23x17_POL_A, mask);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


//  mask = 0x0000..0xFFFF  bit pattern
bool MCP23S17::getPolarity16(uint16_t &mask)
{
  mask = readReg16(MCP23x17_POL_A);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


//  mask = 0x0000..0xFFFF  bit pattern
bool MCP23S17::setPullup16(uint16_t mask)
{
  writeReg16(MCP23x17_PUR_A, mask);
  if (_error != MCP23S17_OK)
  {
    return false;
  }
  return true;
}


//  mask = 0x0000..0xFFFF  bit pattern
bool MCP23S17::getPullup16(uint16_t &mask)
{
  mask = readReg16(MCP23x17_PUR_A);
  if (_error != MCP23S17_OK)
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
//  TODO, MCP23x17_INT_MODE_ERROR?
//  TODO, if register not changed no need to update?
//  TODO, 8 bits optimize? more code vs speed?
//
//  pin = 0..15, mode = { RISING, FALLING, CHANGE }
bool MCP23S17::enableInterrupt(uint8_t pin, uint8_t mode)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }

  //  right mode
  uint16_t intcon = readReg16(MCP23x17_INTCON_A);
  if (mode == CHANGE)
  {
    //  compare to previous value.
    intcon &= ~(1 << pin);
  }
  else
  {
    uint16_t defval = readReg16(MCP23x17_DEFVAL_A);
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
    writeReg16(MCP23x17_DEFVAL_A, defval);
  }
  writeReg16(MCP23x17_INTCON_A, intcon);

  //  enable interrupt
  uint16_t value = readReg16(MCP23x17_GPINTEN_A);
  value |= (1 << pin);
  return writeReg16(MCP23x17_GPINTEN_A, value);
}


bool MCP23S17::disableInterrupt(uint8_t pin)
{
  if (pin > 15)
  {
    _error = MCP23S17_PIN_ERROR;
    return false;
  }
  //  disable interrupt
  uint16_t value = readReg16(MCP23x17_GPINTEN_A);
  value &= ~(1 << pin);
  return writeReg16(MCP23x17_GPINTEN_A, value);
}


bool MCP23S17::enableInterrupt16(uint16_t mask, uint8_t mode)
{
  uint16_t intcon = 0, defval = 0;
  //  right mode
  if (mode == CHANGE)
  {
    //  compare to previous value.
    intcon = ~mask;
  }
  else
  {
    if (mode == RISING)
    {
      intcon = mask;
      defval = ~mask;  //  RISING == compare to 0
    }
    else if (mode == FALLING)
    {
      intcon = mask;
      defval = mask;  //  FALLING == compare to 1
    }
    writeReg16(MCP23x17_DEFVAL_A, defval);
  }
  writeReg16(MCP23x17_INTCON_A, intcon);

  //  enable the mask
  writeReg16(MCP23x17_GPINTEN_A, mask);
  return true;
}


bool MCP23S17::disableInterrupt16(uint16_t mask)
{
  return writeReg16(MCP23x17_GPINTEN_A, ~mask);
}


//  which pins caused the INT?
uint16_t MCP23S17::getInterruptFlagRegister()
{
  return readReg16(MCP23x17_INTF_A);
}


uint16_t MCP23S17::getInterruptCaptureRegister()
{
  return readReg16(MCP23x17_INTCAP_A);
}

  //       polarity: 0 = LOW, 1 = HIGH, 2 = NONE/ODR
bool MCP23S17::setInterruptPolarity(uint8_t polarity)
{
  if (polarity > 2) return false;
  uint8_t reg = readReg(MCP23x17_IOCR);
  reg &= ~(MCP23x17_IOCR_ODR | MCP23x17_IOCR_INTPOL);
  //  LOW is default set.
  if (polarity == 2) reg |= MCP23x17_IOCR_ODR;
  if (polarity == 1) reg |= MCP23x17_IOCR_INTPOL;
  return writeReg(MCP23x17_IOCR, reg);
}


uint8_t MCP23S17::getInterruptPolarity()
{
  uint8_t reg = readReg(MCP23x17_IOCR);
  if (reg & MCP23x17_IOCR_ODR) return 2;
  if (reg & MCP23x17_IOCR_INTPOL) return 1;
  return 0;
}


bool MCP23S17::mirrorInterrupts(bool on)
{
  if (on) return enableControlRegister(MCP23x17_IOCR_MIRROR);
  return disableControlRegister(MCP23x17_IOCR_MIRROR);
}


bool MCP23S17::isMirroredInterrupts()
{
  return (readReg(MCP23x17_IOCR) & MCP23x17_IOCR_MIRROR) > 0;
}


/////////////////////////////////////////////
//
//  MISC
//
int MCP23S17::lastError()
{
  int e = _error;
  _error = MCP23S17_OK;  //  reset error after read.
  return e;
}


bool MCP23S17::enableControlRegister(uint8_t mask)
{
  uint8_t reg = readReg(MCP23x17_IOCR);
  reg |= mask;
  return writeReg(MCP23x17_IOCR, reg);
}


bool MCP23S17::disableControlRegister(uint8_t mask)
{
  uint8_t reg = readReg(MCP23x17_IOCR);
  reg &= ~mask;
  return writeReg(MCP23x17_IOCR, reg);
}


bool MCP23S17::enableHardwareAddress()
{
  return enableControlRegister(MCP23x17_IOCR_HAEN);
}


bool MCP23S17::disableHardwareAddress()
{
  return disableControlRegister(MCP23x17_IOCR_HAEN);
}


////////////////////////////////////////////////////
//
//  PROTECTED
//


//  low level read / write masks
#define MCP23S17_WRITE_REG    0x40
#define MCP23S17_READ_REG     0x41


bool MCP23S17::writeReg(uint8_t reg, uint8_t value)
{
  _error = MCP23S17_OK;

  if (reg > MCP23x17_OLAT_B)
  {
    _error = MCP23S17_REGISTER_ERROR;
    return false;
  }

//  start write
  ::digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    //  _address already shifted
    _mySPI->transfer(MCP23S17_WRITE_REG | _address );
    _mySPI->transfer(reg);
    _mySPI->transfer(value);
    _mySPI->endTransaction();
  }
  else
  {
    //  _address already shifted
    swSPI_transfer(MCP23S17_WRITE_REG | _address );
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

  if (reg > MCP23x17_OLAT_B)
  {
    _error = MCP23S17_REGISTER_ERROR;
    return 0;
  }

//  start read
  ::digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    //  _address already shifted
    _mySPI->transfer(MCP23S17_READ_REG | _address );
    _mySPI->transfer(reg);
    rv = _mySPI->transfer(0xFF);
    _mySPI->endTransaction();
  }
  else
  {
    //  _address already shifted
    swSPI_transfer(MCP23S17_READ_REG | _address );
    swSPI_transfer(reg);
    rv = swSPI_transfer(0xFF);
  }
  ::digitalWrite(_select, HIGH);
  return rv;
}


//  writes HIGH byte first, LOW byte last
bool MCP23S17::writeReg16(uint8_t reg, uint16_t value)
{
  _error = MCP23S17_OK;

  if (reg > MCP23x17_OLAT_B)
  {
    _error = MCP23S17_REGISTER_ERROR;
    return false;
  }

//  start write
  ::digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    //  _address already shifted
    _mySPI->transfer(MCP23S17_WRITE_REG | _address );
    _mySPI->transfer(reg);
    _mySPI->transfer(value >> 8);
    _mySPI->transfer(value & 0xFF);
    _mySPI->endTransaction();
  }
  else
  {
    //  _address already shifted
    swSPI_transfer(MCP23S17_WRITE_REG | _address );
    swSPI_transfer(reg);
    swSPI_transfer(value >> 8);
    swSPI_transfer(value & 0xFF);
  }
  ::digitalWrite(_select, HIGH);
  return true;
}


uint16_t MCP23S17::readReg16(uint8_t reg)
{
  uint16_t rv = 0;

  _error = MCP23S17_OK;

  if (reg > MCP23x17_OLAT_B)
  {
    _error = MCP23S17_REGISTER_ERROR;
    return 0;
  }

//  start read
  ::digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    //  _address already shifted
    _mySPI->transfer(MCP23S17_READ_REG | _address );
    _mySPI->transfer(reg);
    rv = _mySPI->transfer(0xFF) << 8;
    rv += _mySPI->transfer(0xFF);
    _mySPI->endTransaction();
  }
  else
  {
    //  _address already shifted
    swSPI_transfer(MCP23S17_READ_REG | _address );
    swSPI_transfer(reg);
    rv = swSPI_transfer(0xFF) << 8;
    rv += swSPI_transfer(0xFF);
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
    ::digitalWrite(dao, (val & mask) ? HIGH : LOW);
    ::digitalWrite(clk, HIGH);
    if (::digitalRead(dai) == HIGH) rv |= mask;
    ::digitalWrite(clk, LOW);
  }
  return rv;
}


//  -- END OF FILE --

