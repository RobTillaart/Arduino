//
//    FILE: PCA9632.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-25
// VERSION: 0.1.0
// PURPOSE: Arduino library for PCA9632 and PCA9633 4 channel, I2C LED driver.
//     URL: https://github.com/RobTillaart/PCA9632


#include "PCA9632.h"


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


/////////////////////////////////////////////////////
//
//  WRITE
//
uint8_t PCA9632::writeR(uint8_t R)
{
  return writeReg(PCA9632_PWM0, R);
}

uint8_t PCA9632::writeG(uint8_t G)
{
  return writeReg(PCA9632_PWM1, G);
}

uint8_t PCA9632::writeB(uint8_t B)
{
  return writeReg(PCA9632_PWM2, B);
}

uint8_t PCA9632::writeW(uint8_t W)
{
  return writeReg(PCA9632_PWM3, W);
}

uint8_t PCA9632::write(uint8_t channel, uint8_t value)
{
  if (channel > 3)
  {
    _error = PCA9632_ERR_CHAN;
    return _error;
  }
  return writeReg(PCA9632_PWM0 + channel, value);
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
  _wire->write(PCA9632_PWM0);
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


/////////////////////////////////////////////////////
//
//  WRITE MODE REGISTERS
//
uint8_t PCA9632::setMode1(uint8_t value)
{
  return writeReg(PCA9632_MODE1, value);
}


uint8_t PCA9632::setMode2(uint8_t value)
{
  return writeReg(PCA9632_MODE2, value);
}


uint8_t PCA9632::getMode1()
{
  return readReg(PCA9632_MODE1);
}


uint8_t PCA9632::getMode2()
{
  return readReg(PCA9632_MODE2);
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
  return writeReg(PCA9632_LEDOUT, mask);
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
  uint8_t value = (readReg(PCA9632_LEDOUT) & clrmask) | setmask;
  return writeReg(PCA9632_LEDOUT, value);
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
  uint8_t value = (readReg(PCA9632_LEDOUT) >> shift ) & 0x03;
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
uint8_t PCA9632::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  if (_error == 0) _error = PCA9632_OK;
  else _error = PCA9632_ERR_I2C;
  return _error;
}


uint8_t PCA9632::readReg(uint8_t reg)
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

