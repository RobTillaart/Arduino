//
//    FILE: PCA9632.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-25
// VERSION: 0.1.1
// PURPOSE: Arduino library for PCA9632 and PCA9633 I2C 8 bit PWM LED driver, 4 channel.
//     URL: https://github.com/RobTillaart/PCA9632


#include "PCA9632.h"

#define PCA9632_NO_INCREMENT      0x00
#define PCA9632_AUTO_INCR_ALL     0x80
//  not used.
//  #define PCA963X_AUTO_INCR_xxx    0xA0
//  #define PCA963X_AUTO_INCR_xxx    0xC0
//  #define PCA963X_AUTO_INCR_xxx    0xE0



//////////////////////////////////////////////////////////////
//
//  Constructor
//
PCA9632::PCA9632(const uint8_t deviceAddress, TwoWire *wire)
{
  _address         = deviceAddress;
  _wire            = wire;
  _error           = PCA9632_OK;
}

bool PCA9632::begin(uint8_t mode1_mask, uint8_t mode2_mask)
{
  if (! isConnected()) return false;
  setMode1(mode1_mask);
  setMode2(mode2_mask);
  //  all LED can be controlled through its PWM register.
  setLedDriverModeAll(PCA9632_LEDPWM);
  return true;
}


bool PCA9632::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t PCA9632::getAddress()
{
  return _address;
}


uint8_t PCA9632::channelCount()
{
  return 4;
}


/////////////////////////////////////////////////////
//
//  WRITE
//
uint8_t PCA9632::writeR(uint8_t R)
{
  return writeRegister(PCA9632_PWM0, R);
}

uint8_t PCA9632::writeG(uint8_t G)
{
  return writeRegister(PCA9632_PWM1, G);
}

uint8_t PCA9632::writeB(uint8_t B)
{
  return writeRegister(PCA9632_PWM2, B);
}

uint8_t PCA9632::writeW(uint8_t W)
{
  return writeRegister(PCA9632_PWM3, W);
}

uint8_t PCA9632::write(uint8_t channel, uint8_t value)
{
  if (channel > 3)
  {
    _error = PCA9632_ERR_CHAN;
    return _error;
  }
  return writeRegister(PCA9632_PWM0 + channel, value);
}

uint8_t PCA9632::write(uint8_t R, uint8_t G, uint8_t B, uint8_t W)
{
  uint8_t arr[4] = { R, G, B, W};
  return write(arr);
}

//  array of at least 4 elements.
uint8_t PCA9632::write(uint8_t * arr)
{
  _wire->beginTransmission(_address);
  //  auto increment all  page 8 - table 5.
  _wire->write(PCA9632_AUTO_INCR_ALL + PCA9632_PWM0);
  for (uint8_t i = 0; i < 4; i++)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = PCA9632_ERR_I2C;
    return PCA9632_ERROR;
  }
  _error = PCA9632_OK;
  return _error;
}

uint8_t PCA9632::allOff()
{
  uint8_t arr[4] = {0, 0, 0, 0};
  return write(arr);
}


/////////////////////////////////////////////////////
//
//  WRITE MODE REGISTERS
//
uint8_t PCA9632::setMode1(uint8_t value)
{
  return writeRegister(PCA9632_MODE1, value);
}

uint8_t PCA9632::setMode2(uint8_t value)
{
  return writeRegister(PCA9632_MODE2, value);
}

uint8_t PCA9632::getMode1()
{
  return readRegister(PCA9632_MODE1);
}

uint8_t PCA9632::getMode2()
{
  return readRegister(PCA9632_MODE2);
}


/////////////////////////////////////////////////////
//
//  GROUP REGISTERS
//
uint8_t PCA9632::setGroupPWM(uint8_t value)
{
  return writeRegister(PCA9632_GRPPWM, value);
}

uint8_t PCA9632::getGroupPWM()
{
  return readRegister(PCA9632_GRPPWM);
}

uint8_t PCA9632::setGroupFREQ(uint8_t value)
{
  return writeRegister(PCA9632_GRPFREQ, value);
}

uint8_t PCA9632::getGroupFREQ()
{
  return readRegister(PCA9632_GRPFREQ);
}


/////////////////////////////////////////////////////
//
//  SUB CALL - to be tested
//
bool PCA9632::enableSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t prev = getMode1();
  uint8_t mask = prev;
  if (nr == 1)      mask |= PCA9632_MODE1_SUB1;
  else if (nr == 2) mask |= PCA9632_MODE1_SUB2;
  else              mask |= PCA9632_MODE1_SUB3;
  //  only update if changed.
  if (mask != prev)
  {
    setMode1(mask);
    //  TODO error handling ...
  }
  return true;
}


bool PCA9632::disableSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t prev = getMode1();
  uint8_t mask = prev;
  if (nr == 1)      mask &= ~PCA9632_MODE1_SUB1;
  else if (nr == 2) mask &= ~PCA9632_MODE1_SUB2;
  else              mask &= ~PCA9632_MODE1_SUB3;
  //  only update if changed.
  if (mask != prev)
  {
    setMode1(mask);
    //  TODO error handling ...
  }
  return true;
}


bool PCA9632::isEnabledSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t mask = getMode1();
  if (nr == 1) return (mask & PCA9632_MODE1_SUB1) > 0;
  if (nr == 2) return (mask & PCA9632_MODE1_SUB2) > 0;
  return (mask & PCA9632_MODE1_SUB3) > 0;
}


bool PCA9632::setSubCallAddress(uint8_t nr, uint8_t address)
{
  if ((nr == 0) || (nr > 3))
  {
    //  _error = ??  TODO
    return false;
  }
  writeRegister(PCA9632_SUBADR(nr), address);
  return true;
}


uint8_t PCA9632::getSubCallAddress(uint8_t nr)
{
  if ((nr == 0) || (nr > 3))
  {
    //  _error = ??  TODO
    return 0;
  }
  uint8_t address = readRegister(PCA9632_SUBADR(nr));
  return address;
}


/////////////////////////////////////////////////////
//
//  ALL CALL - to be tested
//
bool PCA9632::enableAllCall()
{
  uint8_t prev = getMode1();
  uint8_t mask = prev | PCA9632_MODE1_ALLCALL;
  //  only update if changed.
  if (mask != prev)
  {
    setMode1(mask);
    //  error handling TODO
  }
  return true;
}


bool PCA9632::disableAllCall()
{
  uint8_t prev = getMode1();
  uint8_t mask = prev & ~PCA9632_MODE1_ALLCALL;
  //  only update if changed.
  if (mask != prev)
  {
    setMode1(mask);
    //  error handling TODO
  }
  return true;
}


bool PCA9632::isEnabledAllCall()
{
  uint8_t mask = getMode1();
  return (mask & PCA9632_MODE1_ALLCALL) > 0;
}


bool PCA9632::setAllCallAddress(uint8_t address)
{
  writeRegister(PCA9632_ALLCALLADR, address);
  return true;
}


uint8_t PCA9632::getAllCallAddress()
{
  uint8_t address = readRegister(PCA9632_ALLCALLADR);
  return address;
}






















/////////////////////////////////////////////////////
//
//  LED DRIVER MODE
//
uint8_t PCA9632::setLedDriverModeAll(uint8_t mode)
{
  if (mode > 3)
  {
    _error  = PCA9632_ERR_MODE;
    return _error;
  }
  //  all 4 channels same mode.
  uint8_t mask = mode | mode << 2 | mode << 4 | mode << 6;
  return writeRegister(PCA9632_LEDOUT, mask);
}


uint8_t PCA9632::setLedDriverMode(uint8_t channel, uint8_t mode)
{
  if (channel >= 3)
  {
    _error  = PCA9632_ERR_CHAN;
    return _error;
  }
  if (mode > 3)
  {
    _error  = PCA9632_ERR_MODE;
    return _error;
  }

  //  some bit magic
  uint8_t shift = channel * 2;  // 0,2,4,6 places
  uint8_t setmask = mode << shift;
  uint8_t clrmask = ~(0x03 << shift);
  uint8_t value = (readRegister(PCA9632_LEDOUT) & clrmask) | setmask;
  return writeRegister(PCA9632_LEDOUT, value);
}


//  returns 0..3 if OK, other values indicate an error
uint8_t PCA9632::getLedDriverMode(uint8_t channel)
{
  if (channel >= 3)
  {
    _error  = PCA9632_ERR_CHAN;
    return _error;
  }

  uint8_t shift = channel * 2;  //  0, 2, 4, 6 places
  uint8_t value = (readRegister(PCA9632_LEDOUT) >> shift ) & 0x03;
  _error = PCA9632_OK;
  return value;
}


/////////////////////////////////////////////////////
//
//  ERROR
//
int PCA9632::lastError()
{
  int e = _error;
  _error = PCA9632_OK;
  return e;
}

/////////////////////////////////////////////////////
//
//  LOW LEVEL
//
uint8_t PCA9632::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  //  no Auto-Increment  page 8 - table 5.
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  if (_error == 0) _error = PCA9632_OK;
  else _error = PCA9632_ERR_I2C;
  return _error;
}


uint8_t PCA9632::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = PCA9632_ERR_I2C;
    return PCA9632_ERROR;
  }
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9632_ERR_I2C;
    return PCA9632_ERROR;
  }
  _error = PCA9632_OK;
  return _wire->read();
}

/////////////////////////////////////////////////////
//
//  DERIVED CLASS PCA9633
//
PCA9633::PCA9633(const uint8_t deviceAddress, TwoWire *wire)
        :PCA9632(deviceAddress, wire)
{
}

//  -- END OF FILE --

