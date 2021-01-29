//
//    FILE: PCF8591.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-03-12
// VERSION: 0.1.1
// PURPOSE: I2C PCF8591 library for Arduino
//     URL: https://github.com/RobTillaart/PCF8591
//
//  HISTORY:
//  0.0.1  2020-03-12  initial version
//  0.0.2  2020-07-22  testing, refactor, documentation and examples 
//  0.1.0  2021-01-04  arduino-CI
//  0.1.1  2021-01-14  added WireN + improve error handling.


#include "PCF8591.h"


PCF8591::PCF8591(const uint8_t address, TwoWire *wire)
{
  if ((address < 0x48) || (address > 0x4F))
  {
    _error = PCF8591_ADDRESS_ERROR;
    return;
  }  
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


#if defined (ESP8266) || defined(ESP32)
bool PCF8591::begin(uint8_t sda, uint8_t scl, uint8_t val)
{
  _wire = &Wire;
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  } else {
    _wire->begin();
  }
  if (!isConnected()) return false;
  analogWrite(val);
  return true;
}
#endif

bool PCF8591::begin(uint8_t val)
{
  _wire->begin();
  if (!isConnected()) return false;
  analogWrite(val);
  return true;
}


bool PCF8591::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();  // default == 0 == PCF8591_OK
  return( _error == PCF8591_OK);
}

// ADC PART
uint8_t PCF8591::analogRead(uint8_t channel, uint8_t mode)
{
  if (mode > 3)
  {
    _error = PCF8591_MODE_ERROR;
    return 0;
  }
  _control &= 0b01000100;         // clear all except flags
  _control |= (mode << 4);

  _error = PCF8591_CHANNEL_ERROR;
  switch(mode)
  {
    case 0:
      if (channel > 3) return 0;
      _control |= channel;
      break;
    case 1:
      if (channel > 2) return 0;
      _control |= (channel << 4);
      break;
    case 2:
      if (channel > 2) return 0;
      _control |= (channel << 4);
      break;
    case 3:
      if (channel > 1) return 0;
      _control |= (channel << 4);
      break;
    default:
      return 0;
  }
  _error = PCF8591_OK;

  // NOTE: one must read two values to get an up to date value. 
  //       Page 8 datasheet.
  _wire->beginTransmission(_address);
  _wire->write(_control);
  _error = _wire->endTransmission();  // default == 0 == PCF8591_OK
  if (_error != 0) return PCF8591_I2C_ERROR;

  if (_wire->requestFrom(_address, (uint8_t)2) != 2)
  {
    _error = PCF8591_I2C_ERROR;
    return _adc[channel];          // known last value
  }
  _wire->read();
  _adc[channel] = _wire->read();
  return _adc[channel];
}


uint8_t PCF8591::analogRead4()
{
  _control &= 0b01000100;         // clear all except flags
  uint8_t channel = 0;
  _control |= channel;
  
  enableINCR();
  _wire->beginTransmission(_address);
  _wire->write(_control);
  _error = _wire->endTransmission();  // default == 0 == PCF8591_OK
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


// DAC PART
bool PCF8591::analogWrite(uint8_t value)
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

int PCF8591::lastError()
{
  int e = _error;
  _error = PCF8591_OK;
  return e;
}



// -- END OF FILE --
