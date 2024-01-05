//
//    FILE: PCA9552.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-17
// VERSION: 0.3.1
// PURPOSE: Arduino library for for I2C PCA9552 16 channel PWM
//     URL: https://github.com/RobTillaart/PCA9552


#include "PCA9552.h"


//////////////////////////////////////////////////////////////
//
//  Constructor
//
PCA9552::PCA9552(const uint8_t deviceAddress, TwoWire *wire)
{
  _address = deviceAddress;
  _wire    = wire;
  _outputCount = 16;
  _error = PCA9552_OK;
}


bool PCA9552::begin()
{
  if (! isConnected()) return false;
  return true;
}


bool PCA9552::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t PCA9552::reset()
{
  //  not most efficient
  setPrescaler(0, 0);   //  44 Hz
  setPrescaler(1, 0);   //  44 Hz
  setPWM(0, 128);       //  50%
  setPWM(1, 128);       //  50%
  for (int pin = 0; pin < _outputCount; pin++)
  {
    setOutputMode(pin, 0);  //  LOW
  }
  return PCA9552_OK;
}


uint8_t PCA9552::getAddress()
{
  return _address;
}


uint8_t PCA9552::outputCount()
{
  return _outputCount;
}


/////////////////////////////////////////////////////
//
//  GPIO
//
uint16_t PCA9552::getInput()
{
  uint16_t reg = readReg(PCA9552_INPUT1);
  reg <<= 8;
  reg += readReg(PCA9552_INPUT0);
  return reg;
}


void PCA9552::pinMode1(uint8_t pin, uint8_t mode)
{
  if (mode != OUTPUT) setOutputMode(pin, PCA9552_MODE_HIGH);
}


void PCA9552::write1(uint8_t pin, uint8_t val)
{
  if (val == LOW) setOutputMode(pin, PCA9552_MODE_LOW);
  else            setOutputMode(pin, PCA9552_MODE_HIGH);
}


uint8_t PCA9552::read1(uint8_t pin)
{
  uint8_t reg = PCA9552_INPUT0;
  if (pin > 7)
  {
    reg += 1;
    pin -= 8;
  }
  uint8_t value = readReg(reg);
  if ((value >> pin) & 0x01) return HIGH;
  return LOW;
}


/////////////////////////////////////////////////////
//
//  PRESCALERS
//
void PCA9552::setPrescaler(uint8_t gen, uint8_t psc)
{
  if (gen == 0) writeReg(PCA9552_PSC0, psc);
  else          writeReg(PCA9552_PSC1, psc);
}


uint8_t PCA9552::getPrescaler(uint8_t gen)
{
  if (gen == 0) return readReg(PCA9552_PSC0);
  else          return readReg(PCA9552_PSC1);
}


/////////////////////////////////////////////////////
//
//  PWM
//
void PCA9552::setPWM(uint8_t gen, uint8_t pwm)
{
  if (gen == 0) writeReg(PCA9552_PWM0, pwm);
  else          writeReg(PCA9552_PWM1, pwm);
}


uint8_t PCA9552::getPWM(uint8_t gen)
{
  if (gen == 0) return readReg(PCA9552_PWM0);
  else          return readReg(PCA9552_PWM1);
}


/////////////////////////////////////////////////////
//
//  OUTPUT MODE - MUX SELECTION
//
uint8_t PCA9552::setOutputMode(uint8_t pin, uint8_t mode)
{
  if (pin >= _outputCount)
  {
    _error = PCA9552_ERR_CHAN;
    return _error;
  }
  if (mode > 3)
  {
    _error = PCA9552_ERR_MODE;
    return _error;
  }

  uint8_t reg = PCA9552_LS0;
  while (pin > 3)
  {
    reg += 1;
    pin -= 4;
  }
  uint8_t ledSelect = readReg(reg);
  ledSelect &= ~(0x03 << (pin * 2));
  ledSelect |= (mode << (pin * 2));

  return writeReg(reg, ledSelect);
}


uint8_t PCA9552::getOutputMode(uint8_t pin)
{
  if (pin >= _outputCount)
  {
    _error = PCA9552_ERR_CHAN;
    return _error;
  }

  uint8_t reg = PCA9552_LS0;
  while (pin > 3)
  {
    reg += 1;
    pin -= 4;
  }
  uint8_t ledSelect = readReg(reg);
  uint8_t mode = (ledSelect >> (pin * 2)) & 0x03;
  return mode;
}


uint8_t PCA9552::getLastError()
{
  uint8_t e = _error;
  _error = PCA9552_OK;
  return e;
}



/////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t PCA9552::writeReg(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();

  if (_error == 0) _error = PCA9552_OK;
  else _error = PCA9552_ERROR;
  return _error;
}


uint8_t PCA9552::readReg(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error == 0) _error = PCA9552_OK;
  else
  {
    _error = PCA9552_ERR_I2C;
    return 0;
  }
  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9552_ERROR;
    return 0;
  }
  _error = PCA9552_OK;
  return _wire->read();
}


//  -- END OF FILE --

