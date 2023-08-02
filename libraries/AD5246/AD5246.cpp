//
//    FILE: AD5246.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino Library for AD5246, I2C 128 step rheostat.
//    DATE: 2023-08-02
//     URL: https://github.com/RobTillaart/AD5246


#include "AD5246.h"


AD5246::AD5246(TwoWire *wire)
{
  //  fixed address 0x2E.
  _wire = wire;
  _lastValue = AD5246_MIDPOINT;   //  power on reset => mid position
}


#if defined (ESP8266) || defined(ESP32)
bool AD5246::begin(uint8_t dataPin, uint8_t clockPin)
{
  _wire = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  reset();
  return true;
}
#endif


bool AD5246::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  reset();
  return true;
}


bool AD5246::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t AD5246::reset()
{
  return write(AD5246_MIDPOINT);
}


uint8_t AD5246::write(uint8_t value)
{
  if (value > 127) value = 127;
  _lastValue = value;
  return send(value);
}


uint8_t AD5246::read()
{
  return _lastValue;
}


uint8_t AD5246::readDevice()
{
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


//////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t AD5246::send(const uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(value);
  return _wire->endTransmission();
}


//  -- END OF FILE --
