//
//    FILE: SPIKeyPad.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-04-09
// PURPOSE: Arduino library for 4x4 KeyPad connected to an SPI MCP23S08
//     URL: https://github.com/RobTillaart/SPIKeyPad


#include "SPIKeyPad.h"

//                MCP23S08 Registers       //  description              datasheet P9
constexpr uint8_t MCP23x08_DDR_A  = 0x00;  //  Data Direction Register A   P 10
constexpr uint8_t MCP23x08_POL_A  = 0x01;  //  Input Polarity A            P 11
constexpr uint8_t MCP23x08_PUR_A  = 0x06;  //  Pull Up Resistors A         P 16
constexpr uint8_t MCP23x08_GPIO_A = 0x09;  //  General Purpose IO A        P 19


//  SOFTWARE SPI
SPIKeyPad::SPIKeyPad(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address)
{
  _address = (address << 1);
  _select  = select;
  _dataIn  = dataIn;
  _dataOut = dataOut;
  _clock   = clock;
  _hwSPI   = false;

  _lastKey = SPI_KEYPAD_NOKEY;
  _mode    = SPI_KEYPAD_4x4;
  _debounceThreshold = 0;
  _lastTimeRead      = 0;
}


//  HARDWARE SPI
SPIKeyPad::SPIKeyPad(int select, __SPI_CLASS__ * spi)
{
  _address = 0x00;
  _select  = select;
  _mySPI   = spi;
  _hwSPI   = true;

  _lastKey = SPI_KEYPAD_NOKEY;
  _mode    = SPI_KEYPAD_4x4;
  _debounceThreshold = 0;
  _lastTimeRead      = 0;
}


//  HARDWARE SPI
SPIKeyPad::SPIKeyPad(int select, int address, __SPI_CLASS__ * spi)
{
  _address = (address << 1);
  _select  = select;
  _mySPI   = spi;
  _hwSPI   = true;

  _lastKey = SPI_KEYPAD_NOKEY;
  _mode    = SPI_KEYPAD_4x4;
  _debounceThreshold = 0;
  _lastTimeRead      = 0;
}


bool SPIKeyPad::begin()
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

  //  Force INPUT_PULLUP
  if (! writeReg(MCP23x08_PUR_A, 0xFF)) return false;   //  0xFF == all UP
  //  Force POLARITY
  if (! writeReg(MCP23x08_POL_A, 0xFF)) return false;   //  0xFF == all inverted
  //  set all pins LOW
  if (! writeReg(MCP23x08_GPIO_A, 0x00))return false;

  return true;
}


uint8_t SPIKeyPad::getAddress()
{
  return (_address >> 1);
}


uint8_t SPIKeyPad::getKey()
{
  uint32_t now = millis();
  if (_debounceThreshold > 0)
  {
    if (now - _debounceThreshold < _lastTimeRead)
    {
      return SPI_KEYPAD_THRESHOLD;
    }
  }

  uint8_t key = 0;
  if      (_mode == SPI_KEYPAD_5x3) key = _getKey5x3();
  else if (_mode == SPI_KEYPAD_6x2) key = _getKey6x2();
  else if (_mode == SPI_KEYPAD_8x1) key = _getKey8x1();
  else                              key = _getKey4x4();  //  default.

  if (key == SPI_KEYPAD_FAIL) return key;  //  propagate error.
  //  valid keys + NOKEY
  _lastKey = key;
  _lastTimeRead = now;
  return key;
}


uint8_t SPIKeyPad::getLastKey()
{
  return _lastKey;
}


//  to check "press any key"
bool SPIKeyPad::isPressed()
{
  uint8_t a = readReg(MCP23x08_GPIO_A);
  if (a == 0xFF) return false;
  return (a != 0x00);
}


uint8_t SPIKeyPad::getChar()
{
  //  handle no keyMap loaded.
  if (_keyMap == NULL) return 0;
  uint8_t key = getKey();
  if (key != SPI_KEYPAD_THRESHOLD)
  {
    return _keyMap[key];
  }
  return SPI_KEYPAD_THRESHOLD;
}


uint8_t SPIKeyPad::getLastChar()
{
  //  handle no keyMap loaded.
  if (_keyMap == NULL) return 0;
  return _keyMap[_lastKey];
}


void SPIKeyPad::loadKeyMap(char * keyMap)
{
  _keyMap = keyMap;
}


void SPIKeyPad::setKeyPadMode(uint8_t mode)
{
  if ((mode == SPI_KEYPAD_5x3) ||
      (mode == SPI_KEYPAD_6x2) ||
      (mode == SPI_KEYPAD_8x1))
  {
    _mode = mode;
    return;
  }
  _mode = SPI_KEYPAD_4x4;
}


uint8_t SPIKeyPad::getKeyPadMode()
{
  return _mode;
}


void SPIKeyPad::setDebounceThreshold(uint16_t value)
{
  _debounceThreshold = value;
}


uint16_t SPIKeyPad::getDebounceThreshold()
{
  return _debounceThreshold;
}


uint32_t SPIKeyPad::getLastTimeRead()
{
  return _lastTimeRead;
}


//////////////////////////////////////////////////////
//
//  PROTECTED
//

//  low level read / write masks
constexpr uint8_t MCP23S08_WRITE_REG = 0x40;
constexpr uint8_t MCP23S08_READ_REG  = 0x41;


bool SPIKeyPad::writeReg(uint8_t reg, uint8_t value)
{
//  start write
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


uint8_t SPIKeyPad::readReg(uint8_t reg)
{
  uint8_t rv = 0;

//  start read
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


uint8_t  SPIKeyPad::swSPI_transfer(uint8_t value)
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



uint8_t SPIKeyPad::_read(uint8_t mask)
{
  writeReg(MCP23x08_DDR_A, mask);
  return readReg(MCP23x08_GPIO_A);
}


uint8_t SPIKeyPad::_getKey4x4()
{
  //  key = row + 4 x column
  uint8_t key = 0;

  //  mask = 4 rows as input pull up, 4 columns as output
  uint8_t rows = _read(0x0F);
  //  check if single line has gone low.
  if      (rows == 0x00) return SPI_KEYPAD_NOKEY;
  else if (rows == 0x01) key = 0;
  else if (rows == 0x02) key = 1;
  else if (rows == 0x04) key = 2;
  else if (rows == 0x08) key = 3;
  else return SPI_KEYPAD_FAIL;

  //  4 columns as input pull up, 4 rows as output
  uint8_t cols = _read(0xF0);
  //  check if single line has gone low.
  if      (cols == 0x00) return SPI_KEYPAD_NOKEY;
  else if (cols == 0x10) key += 0;
  else if (cols == 0x20) key += 4;
  else if (cols == 0x40) key += 8;
  else if (cols == 0x80) key += 12;
  else return SPI_KEYPAD_FAIL;

  return key;   //  0..15
}


//  not tested
uint8_t SPIKeyPad::_getKey5x3()
{
  //  key = row + 5 x column
  uint8_t key = 0;

  //  mask = 5 rows as input pull up, 3 columns as output
  uint8_t rows = _read(0x1F);
  //  check if single line has gone low.
  if      (rows == 0x00) return SPI_KEYPAD_NOKEY;
  else if (rows == 0x01) key = 0;
  else if (rows == 0x02) key = 1;
  else if (rows == 0x04) key = 2;
  else if (rows == 0x08) key = 3;
  else if (rows == 0x10) key = 4;
  else return SPI_KEYPAD_FAIL;

  // 3 columns as input pull up, 5 rows as output
  uint8_t cols = _read(0xE0);
  // check if single line has gone low.
  if      (cols == 0x00) return SPI_KEYPAD_NOKEY;
  else if (cols == 0x20) key += 0;
  else if (cols == 0x40) key += 5;
  else if (cols == 0x80) key += 10;
  else return SPI_KEYPAD_FAIL;

  return key;   //  0..14
}


//  not tested
uint8_t SPIKeyPad::_getKey6x2()
{
  //  key = row + 6 x column
  uint8_t key = 0;

  //  mask = 6 rows as input pull up, 2 columns as output
  uint8_t rows = _read(0x3F);
  //  check if single line has gone low.
  if      (rows == 0x00)  return SPI_KEYPAD_NOKEY;
  else if (rows == 0x01) key = 0;
  else if (rows == 0x02) key = 1;
  else if (rows == 0x04) key = 2;
  else if (rows == 0x08) key = 3;
  else if (rows == 0x10) key = 4;
  else if (rows == 0x20) key = 5;
  else return SPI_KEYPAD_FAIL;

  //  2 columns as input pull up, 6 rows as output
  uint8_t cols = _read(0xC0);
  //  check if single line has gone low.
  if      (cols == 0x00) return SPI_KEYPAD_NOKEY;
  else if (cols == 0x40) key += 0;
  else if (cols == 0x80) key += 6;
  else return SPI_KEYPAD_FAIL;

  return key;   //  0..11
}


uint8_t SPIKeyPad::_getKey8x1()
{
  //  key = row
  uint8_t key = 0;

  //  mask = 8 rows as input pull up, 0 columns as output
  uint8_t rows = _read(0xFF);
  //  check if single line has gone low.
  if      (rows == 0x00) return SPI_KEYPAD_NOKEY;
  else if (rows == 0x01) key = 0;
  else if (rows == 0x02) key = 1;
  else if (rows == 0x04) key = 2;
  else if (rows == 0x08) key = 3;
  else if (rows == 0x10) key = 4;
  else if (rows == 0x20) key = 5;
  else if (rows == 0x40) key = 6;
  else if (rows == 0x80) key = 7;
  else return SPI_KEYPAD_FAIL;

  return key;   //  0..7
}


//  -- END OF FILE --

