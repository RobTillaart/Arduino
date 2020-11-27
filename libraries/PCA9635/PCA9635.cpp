//
//    FILE: PCA9635.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 23-apr-2016
// VERSION: 0.2.0
// PURPOSE: Arduino library for PCA9635 I2C LED driver
//     URL: https://github.com/RobTillaart/PCA9635
//
// HISTORY:
// 0.2.0    2020-05-26 major refactor; ESP32 support
// 0.1.2    2020-05-07 fix for PCA9635_MODE1
// 0.1.1    2016-04-24 set autoincr in constructor
// 0.1.0    2016-04-23 initial BETA version
//

#include "PCA9635.h"

#include <Wire.h>


PCA9635::PCA9635(const uint8_t deviceAddress)
{
  _address = deviceAddress;
}

#if defined (ESP8266) || defined(ESP32)
void PCA9635::begin(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);
  reset();
}
#endif

void PCA9635::begin()
{
  Wire.begin();
  reset();
}

void PCA9635::reset()
{
  _data = 0;
  _error = 0;
  writeReg(PCA9635_MODE1, 0x81);  //  AUTOINCR | NOSLEEP | ALLADRR
}

// write value to single PWM registers
uint8_t PCA9635::write1(uint8_t channel, uint8_t value)
{
  return writeN(channel, &value, 1);
}

// write three values in consecutive PWM registers
// typically for RGB values
uint8_t PCA9635::write3(uint8_t channel, uint8_t R, uint8_t G, uint8_t B)
{
  uint8_t arr[3] = { R, G, B };
  return writeN(channel, arr, 3);
}

// write count values in consecutive PWM registers
// does not check if [channel + count > 16]
uint8_t PCA9635::writeN(uint8_t channel, uint8_t* arr, uint8_t count)
{
  if (channel + count > 16)
  {
    _error = PCA9635_ERR_WRITE;
    return PCA9635_ERROR;
  }
  uint8_t base = PCA9635_PWM(channel);
  Wire.beginTransmission(_address);
  Wire.write(base);
  for(uint8_t i = 0; i < count; i++)
  {
    Wire.write(arr[i]);
  }
  _error = Wire.endTransmission();
  if (_error != 0)
  {
    _error = PCA9635_ERR_I2C;
    return PCA9635_ERROR;
  }
  return PCA9635_OK;
}

uint8_t PCA9635::writeMode(uint8_t reg, uint8_t value)
{
  if ((reg == PCA9635_MODE1) || (reg == PCA9635_MODE2))
  {
    writeReg(reg, value);
	return PCA9635_OK;
  }
  _error = PCA9635_ERR_REG;
  return PCA9635_ERROR;
}

// Note 0xFF can also mean an error....  
uint8_t PCA9635::readMode(uint8_t reg)
{
  if ((reg == PCA9635_MODE1) || (reg == PCA9635_MODE2))
  {
    uint8_t value = readReg(reg);
    return value;
  }
  _error = PCA9635_ERR_REG;
  return PCA9635_ERROR;
}

uint8_t PCA9635::setLedDriverMode(uint8_t channel, uint8_t mode)
{
  if (channel > 15)
  {
    _error  = PCA9635_ERR_CHAN;
    return PCA9635_ERROR;
  }
  if (mode > 3) 
  {
    _error  = PCA9635_ERR_MODE;
    return PCA9635_ERROR;
  }

  uint8_t reg = PCA9635_LEDOUT_BASE + (channel >> 2);
  // some bit magic
  uint8_t shift = (channel & 0x03) * 2;  // 0,2,4,6 places
  uint8_t setmask = mode << shift;
  uint8_t clrmask = ~(0x03 << shift);
  uint8_t value = (readReg(reg) & clrmask) | setmask;
  writeReg(reg, value);
  return PCA9635_OK;
}

// returns 0..3 if OK, other values indicate an error
uint8_t PCA9635::getLedDriverMode(uint8_t channel)
{
  if (channel > 15)
  {
    _error  = PCA9635_ERR_CHAN;
    return PCA9635_ERROR;
  }

  uint8_t reg = PCA9635_LEDOUT_BASE + (channel >> 2);
  uint8_t shift = (channel & 0x03) * 2;  // 0,2,4,6 places
  uint8_t value = (readReg(reg) >> shift ) & 0x03;
  return value;
}

// note error flag is reset after read!
int PCA9635::lastError()
{
  int e = _error;
  _error = 0;
  return e;
}


/////////////////////////////////////////////////////
//
// PRIVATE
//
void PCA9635::writeReg(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write(value);
  _error = Wire.endTransmission();
}


uint8_t PCA9635::readReg(uint8_t reg)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  _error = Wire.endTransmission();
  if (Wire.requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9635_ERROR;
    return 0;
  }
  _data = Wire.read();
  return _data;
}

// -- END OF FILE --
