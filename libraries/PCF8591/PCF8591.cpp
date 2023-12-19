//
//    FILE: PCF8591.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-03-12
// VERSION: 0.4.0
// PURPOSE: Arduino Library for PCF8591 I2C 4 channel 8 bit ADC + 1 channel 8 bit DAC.
//     URL: https://github.com/RobTillaart/PCF8591


#include "PCF8591.h"


//  INTERNAL USE ONLY
#define PCF8591_DAC_FLAG                0x40
#define PCF8591_INCR_FLAG               0x04


PCF8591::PCF8591(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
  _control = 0;
  _dac     = 0;
  for (uint8_t i = 0; i < 4; i++)
  {
    _adc[i] = 0;
  }
  _error = PCF8591_OK;
}


bool PCF8591::begin(uint8_t val)
{
  if ((_address < 0x48) || (_address > 0x4F))
  {
    _error = PCF8591_ADDRESS_ERROR;
    return false;
  }
  if (!isConnected()) return false;
  write(val);
  return true;
}


bool PCF8591::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();  //  default == 0 == PCF8591_OK
  return (_error == PCF8591_OK);
}


uint8_t PCF8591::getAddress()
{
  return _address;
}


//////////////////////////////////////////////////////////
//
//  ADC PART
//
void PCF8591::enableINCR()
{
  _control |= PCF8591_INCR_FLAG;
}


void PCF8591::disableINCR()
{
  _control &= ~PCF8591_INCR_FLAG;
}


bool PCF8591::isINCREnabled()
{
  return ((_control & PCF8591_INCR_FLAG) > 0);
}


uint8_t PCF8591::read(uint8_t channel, uint8_t mode)
{
  if (mode > 3)
  {
    _error = PCF8591_MODE_ERROR;
    return 0;
  }
  _control &= 0b01000100;         //  clear all except flags
  _control |= (mode << 4);

  _error = PCF8591_CHANNEL_ERROR;
  switch(mode)
  {
    case PCF8591_FOUR_SINGLE_CHANNEL:
      if (channel > 3) return 0;
      break;
    case PCF8591_THREE_DIFFERENTIAL:
      if (channel > 2) return 0;
      break;
    case PCF8591_MIXED:
      if (channel > 2) return 0;
      break;
    case PCF8591_TWO_DIFFERENTIAL:
      if (channel > 1) return 0;
      break;
    default:
      return 0;
  }
  _control |= channel;
  _error = PCF8591_OK;

  //  NOTE: one must read two values to get an up to date value.
  //        Page 8 datasheet.
  _wire->beginTransmission(_address);
  _wire->write(_control);
  _error = _wire->endTransmission();  //  default == 0 == PCF8591_OK
  if (_error != 0) return PCF8591_I2C_ERROR;

  if (_wire->requestFrom(_address, (uint8_t)2) != 2)
  {
    _error = PCF8591_I2C_ERROR;
    return _adc[channel];          //  return last known value
  }
  _wire->read();
  _adc[channel] = _wire->read();
  return _adc[channel];
}


uint8_t PCF8591::read4()
{
  //  clear all except flags
  //  MODE == PCF8591_FOUR_SINGLE_CHANNEL.
  _control &= 0b01000100;
  uint8_t channel = 0;
  _control |= channel;

  enableINCR();
  _wire->beginTransmission(_address);
  _wire->write(_control);
  _error = _wire->endTransmission();  //  default == 0 == PCF8591_OK
  if (_error != 0)
  {
    _error = PCF8591_I2C_ERROR;
    disableINCR();
    return _error;
  }
  if (_wire->requestFrom(_address, (uint8_t)5) != 5)
  {
    _error = PCF8591_I2C_ERROR;
    disableINCR();
    return _error;
  }

  _wire->read();
  for (uint8_t i = 0; i < 4; i++)
  {
    _adc[i] = _wire->read();
  }
  _error = PCF8591_OK;
  disableINCR();
  return _error;
}


uint8_t PCF8591::lastRead(uint8_t channel)
{
  return _adc[channel];
};


//  comparator calls need testing.
int PCF8591::readComparator_01()
{
  int8_t v = read(0, 3);
  return v;
}


int PCF8591::readComparator_23()
{
  int8_t v = read(1, 3);
  return v;
}


int PCF8591::readComparator_03()
{
  int8_t v = read(0, 1);
  return v;
}


int PCF8591::readComparator_13()
{
  int8_t v = read(1, 1);
  return v;
}



//////////////////////////////////////////////////////////
//
//  DAC PART
//
void PCF8591::enableDAC()
{
  _control |= PCF8591_DAC_FLAG;
};


void PCF8591::disableDAC()
{
  _control &= ~PCF8591_DAC_FLAG;
};


bool PCF8591::isDACEnabled()
{
  return ((_control & PCF8591_DAC_FLAG) > 0);
};


bool PCF8591::write(uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(_control);
  _wire->write(value);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = PCF8591_I2C_ERROR;
    return false;
  }
  _dac = value;
  return true;
}


uint8_t PCF8591::lastWrite()
{
  return _dac;
};


//////////////////////////////////////////////////////////
//
//  ERROR HANDLING
//
int PCF8591::lastError()
{
  int e = _error;
  _error = PCF8591_OK;
  return e;
}


//  -- END OF FILE --

