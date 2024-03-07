//
//    FILE: MAX520.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-03-06
// VERSION: 0.1.1
// PURPOSE: Arduino library for MAX520 and MAX521 4/8 channel 8 bit DAC.
//     URL: https://github.com/RobTillaart/MAX520


#include "MAX520.h"

#define MAX520_RESET          0x10
#define MAX520_POWERDOWN      0x08
#define MAX520_WAKEUP         0x00


///////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
MAX520::MAX520(const uint8_t deviceAddress, TwoWire *wire)
{
  _address    = deviceAddress;
  _wire       = wire;
  _channels   = 4;
  _error      = MAX520_OK;
}


bool MAX520::begin()
{
  if (! isConnected()) return false;
  reset();
  return true;
}


bool MAX520::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


bool MAX520::setAddress(const uint8_t deviceAddress)
{
  _address = deviceAddress;
  return isConnected();
}


uint8_t MAX520::getAddress()
{
  return _address;
}


uint8_t MAX520::getChannels()
{
  return _channels;
}


///////////////////////////////////////////////////////////
//
//  READ WRITE
//
int MAX520::write(uint8_t channel, uint8_t value)
{
  if (channel >= _channels) return MAX520_CHANNEL_ERROR;

  _values[channel] = value;

  uint8_t command = channel;
  _wire->beginTransmission(_address);
  _wire->write(command);
  _wire->write(value);
  return _wire->endTransmission();
}


//  Can be optimized with one I2C transaction.
//  page 11 figure 7
int MAX520::write(uint8_t * values)
{
  for (int i = 0; i < _channels; i++)
  {
    uint8_t rv = write(i, values[i]);
    if (rv != MAX520_OK)
    {
      return rv;
    }
  }
  return MAX520_OK;
}


int MAX520::read(uint8_t channel)
{
  if (channel >= _channels)
  {
    _error = MAX520_CHANNEL_ERROR;
    return 255;  //  buggy
  }
  _error = MAX520_OK;
  return _values[channel];
}


///////////////////////////////////////////////////////////
//
//  RESET (page 11) and POWER DOWN (page12)
//
int MAX520::reset()
{
  for (int i = 0; i < _channels; i++)
  {
    _values[i] = 0;
  }
  _wire->beginTransmission(_address);
  _wire->write(MAX520_RESET);
  _wire->write(0x00);  //  needs a value to ignore
  return _wire->endTransmission();
}


int MAX520::powerDown()
{
  _wire->beginTransmission(_address);
  _wire->write(MAX520_POWERDOWN);
  return _wire->endTransmission();
}


int MAX520::wakeUp()
{
  _wire->beginTransmission(_address);
  _wire->write(MAX520_WAKEUP);
  return _wire->endTransmission();
}


///////////////////////////////////////////////////////////
//
//  DEBUG
//
int MAX520::lastError()
{
  int e = _error;
  _error = MAX520_OK;  //  reset error after read, is this wise?
  return e;
}


///////////////////////////////////////////////////////////
//
//  DERIVED CLASS MAX521
//
MAX521::MAX521(uint8_t deviceAddress, TwoWire *wire) : MAX520(deviceAddress, wire)
{
  _channels = 8;
}


//  -- END OF FILE --

