//
//    FILE: DAC8574.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-11
// VERSION: 0.1.1
// PURPOSE: Arduino library for DAC8574, I2C, 4 channel, 16 bit DAC.
//     URL: https://github.com/RobTillaart/DAC8574


#include "DAC8574.h"


//  INTERNAL USE ONLY
#define DAC8574_DAC_FLAG                0x40
#define DAC8574_INCR_FLAG               0x04


DAC8574::DAC8574(uint8_t address, TwoWire *wire)
{
  _address    = address;
  _wire       = wire;
  _error      = DAC8574_OK;
  _control    = 0x00;
  _maxChannel = 4;
  for (int channel = 0; channel < _maxChannel; channel++)
  {
    _dac[channel] = 0;
  }
  setWriteMode(DAC8574_MODE_NORMAL);
}


bool DAC8574::begin(uint16_t value)
{
  if ((_address < 0x4C) || (_address > 0x4F))
  {
    _error = DAC8574_ADDRESS_ERROR;
    return false;
  }
  if (!isConnected()) return false;

  for (int channel = 0; channel < _maxChannel; channel++)
  {
    write(channel, value);
  }
  return true;
}


bool DAC8574::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();  //  default == 0 ==> DAC8574_OK
  if (_error != 0)
  {
    _error = DAC8574_I2C_ERROR;
    return false;
  }
  return true;
}


uint8_t DAC8574::getAddress()
{
  return _address;
}


//////////////////////////////////////////////////////////
//
//  DAC PART
//
bool DAC8574::write(uint8_t channel, uint16_t value)
{
  if (channel >= _maxChannel)
  {
    _error = DAC8574_CHANNEL_ERROR;
    return false;
  }
  uint8_t lowByte = value & 0xFF;
  uint8_t highByte = value >> 8;
  _control &= 0xF0;  //  keep A2A3 + mode bits
  uint8_t control = _control | (channel << 1);

  _wire->beginTransmission(_address);
  _wire->write(control);
  _wire->write(highByte);
  _wire->write(lowByte);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = DAC8574_I2C_ERROR;
    return false;
  }

  _error = DAC8574_OK;
  _dac[channel] = value;
  return true;
}


uint16_t DAC8574::lastWrite(uint8_t channel)
{
  if (channel >= _maxChannel)
  {
    _error = DAC8574_CHANNEL_ERROR;
    return 0xFFFF;
  }
  return _dac[channel];
}


uint16_t DAC8574::read(uint8_t channel)
{
  if (channel >= _maxChannel)
  {
    _error = DAC8574_CHANNEL_ERROR;
    return 0;
  }

  _control &= 0xF0;  //  keep A2A3 + mode bits
  uint8_t control = _control | (channel << 1);
  _wire->beginTransmission(_address);
  _wire->write(control);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = DAC8574_I2C_ERROR;
    return 0;
  }
  uint8_t n = _wire->requestFrom(_address, uint8_t(2));
  if (n != 2)
  {
    _error = DAC8574_I2C_ERROR;
    return 0;
  }
  uint8_t highByte = _wire->read();
  uint8_t lowByte  = _wire->read();
  _error = DAC8574_OK;
  uint16_t value = highByte * 256 + lowByte;
  return value;
}


bool DAC8574::write(uint8_t channel, uint16_t * arr, uint8_t length)
{
  if (channel >= _maxChannel)
  {
    _error = DAC8574_CHANNEL_ERROR;
    return false;
  }
  if (length > 14)
  {
    _error = DAC8574_BUFFER_ERROR;
    return false;
  }

  _wire->beginTransmission(_address);

  _control &= 0xF0;  //  keep A2A3 + mode bits
  uint8_t control = _control | (channel << 1);
  _wire->write(control);
  for (int i = 0; i < length; i++)
  {
    uint8_t lowByte = arr[i] & 0xFF;
    uint8_t highByte = arr[i] >> 8;
    _wire->write(highByte);
    _wire->write(lowByte);
  }
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = DAC8574_I2C_ERROR;
    return false;
  }

  _error = DAC8574_OK;
  _dac[channel] = arr[length - 1];
  return true;
}


//////////////////////////////////////////////////////////
//
//  PERCENTAGE WRAPPER
//
bool DAC8574::setPercentage(uint8_t channel, float percentage)
{
  if (percentage < 0) percentage = 0;
  else if (percentage > 100) percentage = 100;
  return write(channel, percentage * 655.35);
}


float DAC8574::getPercentage(uint8_t channel)
{
  //  return read(channel) * 0.0015259022;  //  === / 655.35;
  //  faster from cache
  return _dac[channel] * 0.0015259022;  //  === / 655.35;
}


//////////////////////////////////////////////////////////
//
//  WRITE MODE PART
//
void DAC8574::setWriteMode(uint8_t mode)
{
  //  broadcast modi (3,4,5) not supported.
  if (mode > DAC8574_MODE_WRITE_CACHE)
  {
    mode = DAC8574_MODE_NORMAL;
  }
  _control &= 0xC0;  //  keep A2A3 bits
  _control |= (mode << 4);
}


uint8_t DAC8574::getWriteMode()
{
  uint8_t mode = (_control >> 4) & 0x03;
  return mode;
}


//////////////////////////////////////////////////////////
//
//  EXTENDED ADDRESS (A2 A3 pin) PART
//

bool DAC8574::setExtendedAddress(uint8_t A2A3)
{
  if (A2A3 > 3) return false;
  _control &= 0x30;  //  keep mode bits
  _control |= (A2A3 << 6);
  return true;
}


uint8_t DAC8574::getExtendedAddress()
{
  uint8_t A2A3 = (_control >> 6) & 0x03;
  return A2A3;
}


//////////////////////////////////////////////////////////
//
//  POWER DOWN PART
//
bool DAC8574::powerDown(uint8_t pdMode)
{
  uint16_t pdMask = 0x0000;
  //  table 6, page 22.
  switch(pdMode)
  {
    default:
    case DAC8574_PD_LOW_POWER:
      pdMask  = 0x0000;
      break;
    case DAC8574_PD_1_KOHM:
      pdMask  = 0x4000;
      break;
    case DAC8574_PD_100_KOHM:
      pdMask  = 0x8000;
      break;
    case DAC8574_PD_HI_Z:
      pdMask  = 0xC000;
      break;
  }
  //  DAC8574_MODE_NORMAL + power down bit 7
  _control &= 0xC0;  //  keep A2A3 bits
  _control |= (DAC8574_MODE_NORMAL << 4) + 0x01;
  return write(0, pdMask);
}


bool DAC8574::wakeUp(uint8_t channel, uint16_t value)
{
  setWriteMode(DAC8574_MODE_NORMAL);
  return write(channel, value);
}


//////////////////////////////////////////////////////////
//
//  ERROR HANDLING
//
int DAC8574::lastError()
{
  int e = _error;
  _error = DAC8574_OK;
  return e;
}


//  -- END OF FILE --

