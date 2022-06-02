//
//    FILE: PCA9635.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 23-apr-2016
// VERSION: 0.4.0
// PURPOSE: Arduino library for PCA9635 I2C LED driver
//     URL: https://github.com/RobTillaart/PCA9635
//
//  HISTORY:
//
//
//  0.4.0   2022-05-29  breaking changes
//                      rename reset() to configure()
//                      add mode1 and mode2 parameter to configure.
//                      add SUB CALL and ALL CALL functions.
//                      update documentation.
//                      renamed PCA9634_MODE2_STOP to PCA9634_MODE2_ACK
//                      add mode parameters to begin()
//
//  0.3.4   2022-04-13  add constants and functions for mode registers.
//  0.3.3   2022-01-03  add channelCount()
//  0.3.2   2021-12-23  update library.json, readme, license, minor edits
//  0.3.1   2021-04-25  fix writeN by aspyra
//  0.3.0   2021-01-18  support Wire1..WireN
//
//  0.2.2   2021-01-13  refactor + fix register index error.
//  0.2.1   2021-01-05  Arduino-CI + unit test
//  0.2.0   2020-05-26  major refactor; ESP32 support
//  0.1.2   2020-05-07  fix for PCA9635_MODE1
//  0.1.1   2016-04-24  set autoincr in constructor
//  0.1.0   2016-04-23  initial BETA version



#include "PCA9635.h"


//////////////////////////////////////////////////////////////
//
// Constructor
//
PCA9635::PCA9635(const uint8_t deviceAddress, TwoWire *wire)
{
  _address      = deviceAddress;
  _wire         = wire;
  _channelCount = 16;
}


#if defined (ESP8266) || defined(ESP32)
bool PCA9635::begin(uint8_t sda, uint8_t scl, uint8_t mode1_mask, uint8_t mode2_mask)
{
  _wire = &Wire;
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  configure(mode1_mask, mode2_mask);
  return true;
}
#endif


bool PCA9635::begin(uint8_t mode1_mask, uint8_t mode2_mask)
{
  _wire->begin();
  if (! isConnected()) return false;
  configure(mode1_mask, mode2_mask);
  return true;
}


bool PCA9635::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


void PCA9635::configure(uint8_t mode1_mask, uint8_t mode2_mask)
{
  _data = 0;
  _error = 0;

  setMode1(mode1_mask);
  setMode2(mode2_mask);
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
// checks if [channel + count - 1 > 15]
uint8_t PCA9635::writeN(uint8_t channel, uint8_t* arr, uint8_t count)
{
  if (channel + count > _channelCount)
  {
    _error = PCA9635_ERR_WRITE;
    return PCA9635_ERROR;
  }
  uint8_t base = PCA9635_PWM(channel);
  _wire->beginTransmission(_address);
  _wire->write(base);
  for(uint8_t i = 0; i < count; i++)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
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


// Note 0xFF can also mean an error....  check error flag..
uint8_t PCA9635::readMode(uint8_t reg)
{
  if ((reg == PCA9635_MODE1) || (reg == PCA9635_MODE2))
  {
    _error = PCA9635_OK;
    uint8_t value = readReg(reg);
    return value;
  }
  _error = PCA9635_ERR_REG;
  return PCA9635_ERROR;
}


uint8_t PCA9635::setLedDriverMode(uint8_t channel, uint8_t mode)
{
  if (channel >= _channelCount)
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
  if (channel >= _channelCount)
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
// SUB CALL  -   ALL CALL
//
bool PCA9635::enableSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t prev = getMode1();
  uint8_t reg = prev;
  if (nr == 1)      reg |= PCA9635_MODE1_SUB1;
  else if (nr == 2) reg |= PCA9635_MODE1_SUB2;
  else              reg |= PCA9635_MODE1_SUB3;
  //  only update if changed.
  if (reg != prev) setMode1(reg);
  return true;
}


bool PCA9635::disableSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t prev = getMode1();
  uint8_t reg = prev;
  if (nr == 1)      reg &= ~PCA9635_MODE1_SUB1;
  else if (nr == 2) reg &= ~PCA9635_MODE1_SUB2;
  else              reg &= ~PCA9635_MODE1_SUB3;
  //  only update if changed.
  if (reg != prev) setMode1(reg);
  return true;
}


bool PCA9635::isEnabledSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t reg = getMode1();
  if (nr == 1) return (reg & PCA9635_MODE1_SUB1) > 0;
  if (nr == 2) return (reg & PCA9635_MODE1_SUB2) > 0;
  return (reg & PCA9635_MODE1_SUB3) > 0;
}


bool PCA9635::setSubCallAddress(uint8_t nr, uint8_t address)
{
  if ((nr == 0) || (nr > 3)) return false;
  writeReg(PCA9635_SUBADR(nr), address);
  return true;
}


uint8_t PCA9635::getSubCallAddress(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return 0;
  uint8_t address = readReg(PCA9635_SUBADR(nr));
  return address;
}


bool PCA9635::enableAllCall()
{
  uint8_t prev = getMode1();
  uint8_t reg = prev | PCA9635_MODE1_ALLCALL;
  //  only update if changed.
  if (reg != prev) setMode1(reg);
  return true;
}


bool PCA9635::disableAllCall()
{
  uint8_t prev = getMode1();
  uint8_t reg = prev & ~PCA9635_MODE1_ALLCALL;
  //  only update if changed.
  if (reg != prev) setMode1(reg);
  return true;
}


bool PCA9635::isEnabledAllCall()
{
  uint8_t reg = getMode1();
  return reg & PCA9635_MODE1_ALLCALL;
}


bool PCA9635::setAllCallAddress(uint8_t address)
{
  writeReg(PCA9635_ALLCALLADR, address);
  return true;
}


uint8_t PCA9635::getAllCallAddress()
{
  uint8_t address = readReg(PCA9635_ALLCALLADR);
  return address;
}



/////////////////////////////////////////////////////
//
// PRIVATE
//
uint8_t PCA9635::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  if (_error == 0) _error = PCA9635_OK;
  else _error = PCA9635_ERR_I2C;
  return _error;
}


uint8_t PCA9635::readReg(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9635_ERROR;
    return 0;
  }
  _error = PCA9635_OK;
  _data = _wire->read();
  return _data;
}


// -- END OF FILE --

