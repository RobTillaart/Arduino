//
//    FILE: PCA9553.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-16
// VERSION: 0.1.0
// PURPOSE: Arduino library for for I2C PCA9553 4 channel PWM
//     URL: https://github.com/RobTillaart/PCA9553


#include "PCA9553.h"


//////////////////////////////////////////////////////////////
//
//  Constructor
//
PCA9553::PCA9553(const uint8_t deviceAddress, TwoWire *wire)
{
  _address = deviceAddress;
  _wire    = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool PCA9553::begin(int sda, int scl)
{
  _wire = &Wire;
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  return true;
}
#endif


bool PCA9553::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  return true;
}


bool PCA9553::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t PCA9553::channelCount()
{
  return 4;
}


/////////////////////////////////////////////////////
//
//  GPIO
//
uint8_t PCA9553::getInput()
{
  return readReg(PCA9553_INPUT);
}


/////////////////////////////////////////////////////
//
//  PRESCALERS
//
void PCA9553::setPrescaler0(uint8_t psc)
{
  writeReg(PCA9553_PSC0, psc);
}


uint8_t PCA9553::getPrescaler0()
{
  return readReg(PCA9553_PSC0);
}


void PCA9553::setPrescaler1(uint8_t psc)
{
  writeReg(PCA9553_PSC1, psc);
}


uint8_t PCA9553::getPrescaler1()
{
  return readReg(PCA9553_PSC1);
}


/////////////////////////////////////////////////////
//
//  PWM
//
void PCA9553::setPWM0(uint8_t pwm)
{
  writeReg(PCA9553_PWM0, pwm);
}


uint8_t PCA9553::getPWM0()
{
  return readReg(PCA9553_PWM0);
}


void PCA9553::setPWM1(uint8_t pwm)
{
  writeReg(PCA9553_PWM1, pwm);
}


uint8_t PCA9553::getPWM1()
{
  return readReg(PCA9553_PWM1);
}


/////////////////////////////////////////////////////
//
//  LED SOURCE SELECTOR
//
bool PCA9553::setLEDSource(uint8_t led, uint8_t source)
{
  if (led > 3) return false;
  if (source > 3) return false;

  uint8_t val = source << (led * 2);
  uint8_t ledSelect = readReg(PCA9553_LS0);
  ledSelect &= ~(0x03 << (led * 2));
  ledSelect |= val;

  writeReg(PCA9553_LS0, ledSelect);
  return true;
}


uint8_t PCA9553::getLEDSource(uint8_t led)
{
  if (led > 3) return PCA9553_ERROR;

  uint8_t ledSelect = readReg(PCA9553_LS0);
  uint8_t source = (ledSelect >> (led * 2)) & 0x03;
  return source;
}


/////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t PCA9553::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();

  if (_error == 0) _error = PCA9553_OK;
  else _error = PCA9553_ERROR;
  return _error;
}


uint8_t PCA9553::readReg(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();

  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9553_ERROR;
    return 0;
  }
  _error = PCA9553_OK;
  return _wire->read();
}


//  -- END OF FILE --

