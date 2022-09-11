//
//    FILE: PCA9634.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 03-01-2022
// VERSION: 0.2.3
// PURPOSE: Arduino library for PCA9634 I2C LED driver
//     URL: https://github.com/RobTillaart/PCA9634
//
//  HISTORY:
//  0.1.0   2022-01-03  initial version -- based upon 0.3.2 PCA9635
//  0.1.1   2022-01-04  minor fixes 
//  0.1.2   2022-04-13  issue #7 add constants and functions for mode registers.
//
//  0.2.0   2022-05-29  breaking changes
//                      rename reset() to configure()
//                      add mode1 and mode2 parameter to configure.
//                      add SUB CALL and ALL CALL functions.
//                      update documentation.
//                      renamed PCA9634_MODE2_STOP to PCA9634_MODE2_ACK
//  0.2.1   2022-05-30  add mode parameters to begin()
//  0.2.2   2022-09-02  add static I2C_SoftwareReset()
//  0.2.3   2022-09-11  update documentation
//                      fix begin() for ESP32 ambiguity - See PCA9635 #17


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
bool PCA9634::begin(int sda, int scl, uint8_t mode1_mask, uint8_t mode2_mask)
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


bool PCA9634::begin(uint8_t mode1_mask, uint8_t mode2_mask)
{
  _wire->begin();
  if (! isConnected()) return false;
  configure(mode1_mask, mode2_mask);
  return true;
}


bool PCA9634::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


void PCA9634::configure(uint8_t mode1_mask, uint8_t mode2_mask)
{
  _data = 0;
  _error = 0;

  setMode1(mode1_mask);
  setMode2(mode2_mask);
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


// note error flag is set to PCA9634_OK after read!
int PCA9634::lastError()
{
  int e = _error;
  _error = PCA9634_OK;
  return e;
}



/////////////////////////////////////////////////////
//
// SUB CALL  -   ALL CALL
//
bool PCA9634::enableSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t prev = getMode1();
  uint8_t reg = prev;
  if (nr == 1)      reg |= PCA9634_MODE1_SUB1;
  else if (nr == 2) reg |= PCA9634_MODE1_SUB2;
  else              reg |= PCA9634_MODE1_SUB3;
  //  only update if changed.
  if (reg != prev) setMode1(reg);
  return true;
}


bool PCA9634::disableSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t prev = getMode1();
  uint8_t reg = prev;
  if (nr == 1)      reg &= ~PCA9634_MODE1_SUB1;
  else if (nr == 2) reg &= ~PCA9634_MODE1_SUB2;
  else              reg &= ~PCA9634_MODE1_SUB3;
  //  only update if changed.
  if (reg != prev) setMode1(reg);
  return true;
}


bool PCA9634::isEnabledSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t reg = getMode1();
  if (nr == 1) return (reg & PCA9634_MODE1_SUB1) > 0;
  if (nr == 2) return (reg & PCA9634_MODE1_SUB2) > 0;
  return (reg & PCA9634_MODE1_SUB3) > 0;
}


bool PCA9634::setSubCallAddress(uint8_t nr, uint8_t address)
{
  if ((nr == 0) || (nr > 3)) return false;
  writeReg(PCA9634_SUBADR(nr), address);
  return true;
}


uint8_t PCA9634::getSubCallAddress(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return 0;
  uint8_t address = readReg(PCA9634_SUBADR(nr));
  return address;
}


bool PCA9634::enableAllCall()
{
  uint8_t prev = getMode1();
  uint8_t reg = prev | PCA9634_MODE1_ALLCALL;
  //  only update if changed.
  if (reg != prev) setMode1(reg);
  return true;
}


bool PCA9634::disableAllCall()
{
  uint8_t prev = getMode1();
  uint8_t reg = prev & ~PCA9634_MODE1_ALLCALL;
  //  only update if changed.
  if (reg != prev) setMode1(reg);
  return true;
}


bool PCA9634::isEnabledAllCall()
{
  uint8_t reg = getMode1();
  return reg & PCA9634_MODE1_ALLCALL;
}


bool PCA9634::setAllCallAddress(uint8_t address)
{
  writeReg(PCA9634_ALLCALLADR, address);
  return true;
}


uint8_t PCA9634::getAllCallAddress()
{
  uint8_t address = readReg(PCA9634_ALLCALLADR);
  return address;
}


//////////////////////////////////////////////////////
//
//  EXPERIMENTAL
//
int PCA9634::I2C_SoftwareReset(uint8_t method)
{
  //  only support 0 and 1
  if (method > 1) return -999;
  if (method == 1)
  {
    //  from https://github.com/RobTillaart/PCA9634/issues/10#issuecomment-1206326417
   const uint8_t SW_RESET = 0x03;
   _wire->beginTransmission(SW_RESET);
   _wire->write(0xA5);
   _wire->write(0x5A);
   return _wire->endTransmission(true);
  }

  //  default - based upon NXP specification - UM10204.pdf - page 16
  _wire->beginTransmission(0x00);
  _wire->write(0x06);
  return _wire->endTransmission(true);
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

