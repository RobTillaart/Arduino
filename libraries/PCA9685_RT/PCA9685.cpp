//
//    FILE: PCA9685.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 24-apr-2016
// VERSION: 0.7.3
// PURPOSE: Arduino library for PCA9685 I2C LED driver, 16 channel PWM, 12 bit.
//     URL: https://github.com/RobTillaart/PCA9685_RT


#include "PCA9685.h"


//////////////////////////////////////////////////////////////
//
//  Constructor
//
PCA9685::PCA9685(const uint8_t deviceAddress, TwoWire *wire)
{
  _address         = deviceAddress;
  _wire            = wire;
  _channelCount    = 16;
  _error           = PCA9685_OK;
  _OutputEnablePin = 255;
}


bool PCA9685::begin(uint8_t mode1_mask, uint8_t mode2_mask)
{
  if (! isConnected()) return false;
  configure(mode1_mask, mode2_mask);
  return true;
}


bool PCA9685::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t PCA9685::getAddress()
{
  return _address;
}


/////////////////////////////////////////////////////
//
//  CONFIGURATION
//
uint8_t PCA9685::configure(uint8_t mode1_mask, uint8_t mode2_mask)
{
  _error = PCA9685_OK;

  uint8_t r1 = setMode1(mode1_mask);
  uint8_t r2 = setMode2(mode2_mask);

  if ((r1 != PCA9685_OK) || (r2 != PCA9685_OK))
  {
    return PCA9685_ERROR;
  }
  return _error;
}


uint8_t PCA9685::channelCount()
{
  return _channelCount;
}


/////////////////////////////////////////////////////
//
//  WRITE MODE
//
uint8_t PCA9685::writeMode(uint8_t reg, uint8_t value)
{
  if ((reg == PCA9685_MODE1) || (reg == PCA9685_MODE2))
  {
    writeRegister(reg, value);
    return PCA9685_OK;
  }
  _error = PCA9685_ERR_MODE;
  return PCA9685_ERROR;
}


uint8_t PCA9685::readMode(uint8_t reg)
{
  if ((reg == PCA9685_MODE1) || (reg == PCA9685_MODE2))
  {
    _error = PCA9685_OK;
    uint8_t value = readRegister(reg);
    return value;
  }
  _error = PCA9685_ERR_MODE;
  return PCA9685_ERROR;
}


uint8_t PCA9685::setMode1(uint8_t value)
{
  writeRegister(PCA9685_MODE1, value);
  return PCA9685_OK;
}


uint8_t PCA9685::setMode2(uint8_t value)
{
  writeRegister(PCA9685_MODE2, value);
  return PCA9685_OK;
}


uint8_t PCA9685::getMode1()
{
  return readRegister(PCA9685_MODE1);
}


uint8_t PCA9685::getMode2()
{
  return readRegister(PCA9685_MODE2);
}


/////////////////////////////////////////////////////
//
//  PWM  FREQUENCY
//
//  write value to single PWM channel
uint8_t PCA9685::setPWM(uint8_t channel, uint16_t onTime, uint16_t offTime)
{
  _error = PCA9685_OK;
  if (channel >= _channelCount)
  {
    _error = PCA9685_ERR_CHANNEL;
    return _error;
  }
  uint8_t reg = PCA9685_CHANNEL(channel);
  //  mask both onTime and offTime to be in range 0..4095
  //  allows to set the FULL_ON / FULL OFF bits.
  return writeRegister2(reg, onTime & 0x1FFF, offTime & 0x1FFF);
}


//  write value to single PWM channel
uint8_t PCA9685::setPWM(uint8_t channel, uint16_t offTime)
{
  return setPWM(channel, 0, offTime);
}


//  read value from single PWM channel
//  may include FULL_ON or FULL_OFF bit.
uint8_t PCA9685::getPWM(uint8_t channel, uint16_t* onTime, uint16_t* offTime)
{
  _error = PCA9685_OK;
  if (channel >= _channelCount)
  {
    _error = PCA9685_ERR_CHANNEL;
    return _error;
  }
  uint8_t reg = PCA9685_CHANNEL(channel);
  return readRegister2(reg, onTime, offTime);
}


//  set update frequency for all channels
uint8_t PCA9685::setFrequency(uint16_t freq, int offset)
{
  _error = PCA9685_OK;
  _freq = freq;
  //  limits frequency see page 25 datasheet
  if (_freq < PCA9685_MIN_FREQ) _freq = PCA9685_MIN_FREQ;
  if (_freq > PCA9685_MAX_FREQ) _freq = PCA9685_MAX_FREQ;
  //  removed float operation for speed
  //  faster and equal accurate
  //  uint8_t scaler = round(25e6 / (_freq * 4096)) - 1;
  uint8_t scaler = 48828 / (_freq * 8) - 1;

  uint8_t mode1 = getMode1();
  setMode1(mode1 | PCA9685_MODE1_SLEEP);
  scaler += offset;
  writeRegister(PCA9685_PRE_SCALER, scaler);
  return setMode1(mode1);
}


//  cache == false returns the actual used frequency.
//  cache == true returns the frequency without pre-scaler (offset).
uint16_t PCA9685::getFrequency(bool cache)
{
  _error = PCA9685_OK;
  if (cache) return _freq;
  uint8_t scaler = readRegister(PCA9685_PRE_SCALER);
  scaler++;
  _freq = 48828 / scaler;
  _freq /= 8;
  return _freq;
}


//  datasheet P.18 - fig. 9:
//  Note: bit[11-0] ON should NOT equal timer OFF in ON mode
//  in OFF mode it doesn't matter.
uint8_t PCA9685::write1(uint8_t channel, uint8_t mode)
{
  _error = PCA9685_OK;
  if (channel >= _channelCount)
  {
    _error = PCA9685_ERR_CHANNEL;
    return _error;
  }
  uint8_t reg = PCA9685_CHANNEL(channel);
  if (mode != LOW) return writeRegister2(reg, 0x1000, 0x0000);
  return writeRegister2(reg, 0x0000, 0x0000);
}


//  See #29 for discussion.
uint8_t PCA9685::read1(uint8_t channel)
{
  _error = PCA9685_OK;
  if (channel >= _channelCount)
  {
    _error = PCA9685_ERR_CHANNEL;
    return _error;
  }

  uint8_t reg = PCA9685_CHANNEL(channel);

  uint16_t on, off;
  if (readRegister2(reg, &on, &off) != PCA9685_OK) return 2;
  if (on  & 0x1000) return HIGH;  //  FULL_ON
  if (off & 0x1000) return LOW;   //  FULL_OFF

  uint16_t duty = (off - on) & 0x0FFF;
  if (duty == 4095) return HIGH;  //  PWM = 100%
  if (duty == 0)    return LOW;   //  PWM = 0%

  return 2;  //  not HIGH not LOW => use getPWM() to get PWM value.
}


uint8_t PCA9685::allOFF()
{
  _error = PCA9685_OK;
  return writeRegister(PCA9685_ALL_OFF_H, 0x10);
}


/////////////////////////////////////////////////////
//
//  ERROR
//
int PCA9685::lastError()
{
  int e = _error;
  _error = PCA9685_OK;
  return e;
}


/////////////////////////////////////////////////////
//
//  SUB CALL
//
bool PCA9685::enableSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t prev = getMode1();
  uint8_t mask = prev;
  if (nr == 1)      mask |= PCA9685_MODE1_SUB1;
  else if (nr == 2) mask |= PCA9685_MODE1_SUB2;
  else              mask |= PCA9685_MODE1_SUB3;
  //  only update if changed.
  if (mask != prev)
  {
    setMode1(mask);
    //  TODO error handling ...
  }
  return true;
}


bool PCA9685::disableSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t prev = getMode1();
  uint8_t mask = prev;
  if (nr == 1)      mask &= ~PCA9685_MODE1_SUB1;
  else if (nr == 2) mask &= ~PCA9685_MODE1_SUB2;
  else              mask &= ~PCA9685_MODE1_SUB3;
  //  only update if changed.
  if (mask != prev)
  {
    setMode1(mask);
    //  TODO error handling ...
  }
  return true;
}


bool PCA9685::isEnabledSubCall(uint8_t nr)
{
  if ((nr == 0) || (nr > 3)) return false;
  uint8_t mask = getMode1();
  if (nr == 1) return (mask & PCA9685_MODE1_SUB1) > 0;
  if (nr == 2) return (mask & PCA9685_MODE1_SUB2) > 0;
  return (mask & PCA9685_MODE1_SUB3) > 0;
}


bool PCA9685::setSubCallAddress(uint8_t nr, uint8_t address)
{
  if ((nr == 0) || (nr > 3))
  {
    //  _error = ??  TODO
    return false;
  }
  writeRegister(PCA9685_SUBADR(nr), address);
  return true;
}


uint8_t PCA9685::getSubCallAddress(uint8_t nr)
{
  if ((nr == 0) || (nr > 3))
  {
    //  _error = ??  TODO
    return 0;
  }
  uint8_t address = readRegister(PCA9685_SUBADR(nr));
  return address;
}


/////////////////////////////////////////////////////
//
//  ALL CALL
//
bool PCA9685::enableAllCall()
{
  uint8_t prev = getMode1();
  uint8_t mask = prev | PCA9685_MODE1_ALLCALL;
  //  only update if changed.
  if (mask != prev)
  {
    setMode1(mask);
    //  error handling TODO
  }
  return true;
}


bool PCA9685::disableAllCall()
{
  uint8_t prev = getMode1();
  uint8_t mask = prev & ~PCA9685_MODE1_ALLCALL;
  //  only update if changed.
  if (mask != prev)
  {
    setMode1(mask);
    //  error handling TODO
  }
  return true;
}


bool PCA9685::isEnabledAllCall()
{
  uint8_t mask = getMode1();
  return (mask & PCA9685_MODE1_ALLCALL) > 0;
}


bool PCA9685::setAllCallAddress(uint8_t address)
{
  writeRegister(PCA9685_ALLCALLADR, address);
  return true;
}


uint8_t PCA9685::getAllCallAddress()
{
  uint8_t address = readRegister(PCA9685_ALLCALLADR);
  return address;
}


/////////////////////////////////////////////////////
//
//  OUTPUT ENABLE (OE) control
//
//  active LOW see datasheet
//
bool PCA9685::setOutputEnablePin(uint8_t pin)
{
  _OutputEnablePin = pin;
  if (_OutputEnablePin != 255)
  {
    pinMode(_OutputEnablePin, OUTPUT);
    digitalWrite(_OutputEnablePin, HIGH);
    return true;
  }
  //  must it be set to HIGH now?
  return false;
}


bool PCA9685::setOutputEnable(bool on)
{
  if (_OutputEnablePin != 255)
  {
    digitalWrite(_OutputEnablePin, on ? LOW : HIGH);
    return true;
  }
  return false;
}


uint8_t PCA9685::getOutputEnable()
{
  if (_OutputEnablePin != 255)
  {
    return digitalRead(_OutputEnablePin);
  }
  return HIGH;
}


//////////////////////////////////////////////////////
//
//  EXPERIMENTAL
//
int PCA9685::I2C_SoftwareReset(uint8_t method)
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
//  PRIVATE
//
uint8_t PCA9685::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();

  if (_error == 0) _error = PCA9685_OK;
  else _error = PCA9685_ERR_I2C;
  return _error;
}


uint8_t PCA9685::writeRegister2(uint8_t reg, uint16_t a, uint16_t b)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(a & 0xFF);
  _wire->write((a >> 8) & 0x1F);
  _wire->write(b & 0xFF);
  _wire->write((b >> 8) & 0x1F);
  _error = _wire->endTransmission();
  if (_error == 0) _error = PCA9685_OK;
  else _error = PCA9685_ERR_I2C;
  return _error;
}


uint8_t PCA9685::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != PCA9685_OK) return 0;

  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    _error = PCA9685_ERR_I2C;
    return 0;
  }
  _error = PCA9685_OK;
  return _wire->read();
}


int PCA9685::readRegister2(uint8_t reg, uint16_t * v1, uint16_t * v2)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != PCA9685_OK) return _error;

  if (_wire->requestFrom(_address, (uint8_t)4) != 4)
  {
    _error = PCA9685_ERR_I2C;
    return _error;
  }
  uint16_t data = _wire->read();
  *v1 = (_wire->read() * 256) + data;
  data = _wire->read();
  *v2 = (_wire->read() * 256) + data;
  _error = PCA9685_OK;
  return _error;
}


//  -- END OF FILE --

