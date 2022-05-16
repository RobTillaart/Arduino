//
//    FILE: PCA9634.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 03-01-2022
// VERSION: 0.1.2
// PURPOSE: Arduino library for PCA9634 I2C LED driver
//     URL: https://github.com/RobTillaart/PCA9634
//
//  HISTORY:
//  0.1.0   2022-01-03  initial version -- based upon 0.3.2 PCA9635
//  0.1.1   2022-01-04  minor fixes 
//  0.1.2   2022-04-13  issue #7 add constants and functions for mode registers.


#include "PCA9634.h"


//////////////////////////////////////////////////////////////
//
// Constructor
//
PCA9634::PCA9634(const uint8_t deviceAddress, TwoWire *wire)
{
  _address      = deviceAddress;
  _wire         = wire;
  _channelCount = 8;
}


#if defined (ESP8266) || defined(ESP32)
bool PCA9634::begin(uint8_t sda, uint8_t scl)
{
  _wire = &Wire;
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  reset();
  return true;
}
#endif


bool PCA9634::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  reset();
  return true;
}


bool PCA9634::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


void PCA9634::reset()
{
  _data = 0;
  _error = 0;

  uint8_t mode1_mask = PCA9634_MODE1_AUTOINCR2 | PCA9634_MODE1_ALLCALL;
  writeReg(PCA9634_MODE1, mode1_mask);  //  AUTOINCR | NOSLEEP | ALLADRR  0x81
}


// write value to single PWM registers
uint8_t PCA9634::write1(uint8_t channel, uint8_t value)
{
  return writeN(channel, &value, 1);
}


// write three values in consecutive PWM registers
// typically for RGB values
uint8_t PCA9634::write3(uint8_t channel, uint8_t R, uint8_t G, uint8_t B)
{
  uint8_t arr[3] = { R, G, B };
  return writeN(channel, arr, 3);
}


// write count values in consecutive PWM registers
// checks if [channel + count - 1 > 8]
uint8_t PCA9634::writeN(uint8_t channel, uint8_t* arr, uint8_t count)
{
  if (channel + count > _channelCount)
  {
    _error = PCA9634_ERR_WRITE;
    return PCA9634_ERROR;
  }
  uint8_t base = PCA9634_PWM(channel);
  _wire->beginTransmission(_address);
  _wire->write(base);
  for(uint8_t i = 0; i < count; i++)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = PCA9634_ERR_I2C;
    return PCA9634_ERROR;
  }
  return PCA9634_OK;
}


uint8_t PCA9634::writeMode(uint8_t reg, uint8_t value)
{
  if ((reg == PCA9634_MODE1) || (reg == PCA9634_MODE2))
  {
    writeReg(reg, value);
    return PCA9634_OK;
  }
  _error = PCA9634_ERR_REG;
  return PCA9634_ERROR;
}


// Note 0xFF can also mean an error....  check error flag..
uint8_t PCA9634::readMode(uint8_t reg)
{
  if ((reg == PCA9634_MODE1) || (reg == PCA9634_MODE2))
  {
    _error = PCA9634_OK;
    uint8_t value = readReg(reg);
    return value;
  }
  _error = PCA9634_ERR_REG;
  return PCA9634_ERROR;
}


uint8_t PCA9634::setLedDriverMode(uint8_t channel, uint8_t mode)
{
  if (channel >= _channelCount)
  {
    _error  = PCA9634_ERR_CHAN;
    return PCA9634_ERROR;
  }
  if (mode > 3)
  {
    _error  = PCA9634_ERR_MODE;
    return PCA9634_ERROR;
  }

  uint8_t reg = PCA9634_LEDOUT_BASE + (channel >> 2);
  // some bit magic
  uint8_t shift = (channel & 0x03) * 2;  // 0,2,4,6 places
  uint8_t setmask = mode << shift;
  uint8_t clrmask = ~(0x03 << shift);
  uint8_t value = (readReg(reg) & clrmask) | setmask;
  writeReg(reg, value);
  return PCA9634_OK;
}


// returns 0..3 if OK, other values indicate an error
uint8_t PCA9634::getLedDriverMode(uint8_t channel)
{
  if (channel >= _channelCount)
  {
    _error  = PCA9634_ERR_CHAN;
    return PCA9634_ERROR;
  }

  uint8_t reg = PCA9634_LEDOUT_BASE + (channel >> 2);
  uint8_t shift = (channel & 0x03) * 2;  // 0,2,4,6 places
  uint8_t value = (readReg(reg) >> shift ) & 0x03;
  return value;
}


// note error flag is reset after read!
int PCA9634::lastError()
{
  int e = _error;
  _error = 0;
  return e;
}


/////////////////////////////////////////////////////
//
// PRIVATE
//
uint8_t PCA9634::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  if (_error == 0) _error = PCA9634_OK;
  else _error = PCA9634_ERR_I2C;
  return _error;
}


uint8_t PCA9634::readReg(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9634_ERROR;
    return 0;
  }
  _error = PCA9634_OK;
  _data = _wire->read();
  return _data;
}


// -- END OF FILE --

