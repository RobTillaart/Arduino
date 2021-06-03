//
//    FILE: MAX14661.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-29
// VERSION: 0.1.0
// PURPOSE: Arduino library for MAX14661 16 channel I2C multiplexer
//     URL: https://github.com/RobTillaart/MAX14661
//
//  HISTORY:
//  0.1.00  2021-01-29  initial version
//

#include "MAX14661.h"


// registers
#define MAX14661_DIR0       0x00
#define MAX14661_DIR1       0x01
#define MAX14661_DIR2       0x02
#define MAX14661_DIR3       0x03
#define MAX14661_SHDW0      0x10
#define MAX14661_SHDw1      0x11
#define MAX14661_SHDw2      0x12
#define MAX14661_SHDw3      0x13
#define MAX14661_CMD_A      0x14
#define MAX14661_CMD_B      0x15


MAX14661::MAX14661(const uint8_t deviceAddress, TwoWire *wire)
{
  _address = deviceAddress;
  _wire    = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool MAX14661::begin(uint8_t dataPin, uint8_t clockPin)
{
  _wire = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  _error = 0;
  if (! isConnected()) return false;
  return true;
}
#endif


bool MAX14661::begin()
{
  _wire->begin();
  _error = 0;

  if (! isConnected()) return false;
  return true;
}


bool MAX14661::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


/////////////////////////////////////////////////////////
//
// PAIR INTERFACE
//
bool MAX14661::openChannel(uint8_t channel)
{
  if (channel > 15) return false;
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR0;
  if (ch > 7)
  {
    reg = MAX14661_DIR1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask |= (1 << ch);
  writeRegister(reg, mask);
  reg += 2;
  mask = readRegister(reg);
  mask |= (1 << ch);
  writeRegister(reg, mask);
  return true;
}


bool MAX14661::closeChannel(uint8_t channel)
{
  if (channel > 15) return false;
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR0;
  if (ch > 7)
  {
    reg = MAX14661_DIR1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask &= ~(1 << ch);
  writeRegister(reg, mask);
  reg += 2;
  mask = readRegister(reg);
  mask &= ~(1 << ch);
  writeRegister(reg, mask);
  return true;
}


// assumption both A and B are in same state
bool MAX14661::isOpenChannel(uint8_t channel)
{
  if (channel > 15) return false;
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR0;
  if (ch > 7)
  {
    reg = MAX14661_DIR1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  return (mask & (1 << ch)) > 0;
}


void MAX14661::openAllChannels()
{
  setChannels(0xFFFF);
}


void MAX14661::closeAllChannels()
{
  setChannels(0);
}

void MAX14661::setChannels(uint16_t mask)
{
  writeRegister(MAX14661_DIR0, mask & 0x00FF);
  writeRegister(MAX14661_DIR1, (mask & 0xFF00) >> 8);
  writeRegister(MAX14661_DIR2, mask & 0x00FF);
  writeRegister(MAX14661_DIR3, (mask & 0xFF00) >> 8);
}


// assumption both A and B are in same state
uint16_t MAX14661::getChannels()
{
  uint16_t channels = readRegister(MAX14661_DIR1) << 8;
  channels |= readRegister(MAX14661_DIR0);
  return channels;
}


/////////////////////////////////////////////////////////
//
// MUX INTERFACE
//

void MAX14661::MUXA(uint8_t channel)
{
  uint8_t ch = channel;
  if (channel > 15) ch = 0x10;
  writeRegister(MAX14661_CMD_A, ch);
}


uint8_t MAX14661::getMUXA()
{
  uint8_t ch = readRegister(MAX14661_CMD_A);
  if ((ch & 0x10) == 0) return (ch & 0x0F);
  return 255;
}


void MAX14661::MUXB(uint8_t channel)
{
  uint8_t ch = channel;
  if (channel > 15) ch = 0x10;
  writeRegister(MAX14661_CMD_B, ch);
}


uint8_t MAX14661::getMUXB()
{
  uint8_t ch = readRegister(MAX14661_CMD_B);
  if ((ch & 0x10) == 0) return (ch & 0x0F);
  return 255;
}


/////////////////////////////////////////////////////////
//
// FULL CONTROL
//
bool MAX14661::openA(uint8_t channel)
{
  if (channel > 15) return false;
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR0;
  if (ch > 7)
  {
    reg = MAX14661_DIR1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask |= (1 << ch);
  writeRegister(reg, mask);
  return true;
}


bool MAX14661::openB(uint8_t channel)
{
  if (channel > 15) return false;
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR2;
  if (ch > 7)
  {
    reg = MAX14661_DIR3;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask |= (1 << ch);
  writeRegister(reg, mask);
  return true;
}


bool MAX14661::closeA(uint8_t channel)
{
  if (channel > 15) return false;
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR0;
  if (ch > 7)
  {
    reg = MAX14661_DIR1;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask &= ~(1 << ch);
  writeRegister(reg, mask);
  return true;
}


bool MAX14661::closeB(uint8_t channel)
{
  if (channel > 15) return false;
  uint8_t ch = channel;
  uint8_t reg = MAX14661_DIR2;
  if (ch > 7)
  {
    reg = MAX14661_DIR3;
    ch -= 8;
  }
  uint8_t mask = readRegister(reg);
  mask &= ~(1 << ch);
  writeRegister(reg, mask);
  return true;
}


/////////////////////////////////////////////////////////
//
// LOW LEVEL CONTROL
//
uint8_t MAX14661::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != 0) return 0;
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = -1;
    return 0;
  }
  return _wire->read();
}


int MAX14661::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return _error;
}


int MAX14661::lastError()
{
  int e = _error;
  _error = 0;
  return e;
}




// -- END OF FILE -- 
