//
//    FILE: DS28CM00.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Library for the DS28CM00 unique identification chip.
// VERSION: 0.4.0
//     URL: https://github.com/RobTillaart/DS28CM00


#include "DS28CM00.h"


#define DS28CM00_DEVICE_ADDRESS      0x50
#define DS28CM00_UID_REGISTER        0x00
#define DS28CM00_CONTROL_REGISTER    0x08


DS28CM00::DS28CM00(TwoWire *wire)
{
  _wire = wire;
}


bool DS28CM00::begin()
{
  if (!isConnected()) return false;
  return setI2CMode();
}


bool DS28CM00::isConnected()
{
  _wire->beginTransmission(DS28CM00_DEVICE_ADDRESS);
  int rv = _wire->endTransmission();
  return rv == 0;
}


bool DS28CM00::getMode(uint8_t &mode)
{
  mode = DS28CM00_MODE_UNKNOWN;
  _wire->beginTransmission(DS28CM00_DEVICE_ADDRESS);
  _wire->write(DS28CM00_CONTROL_REGISTER);
  int rv = _wire->endTransmission();
  if (rv != 0) return false;

  uint8_t read = _wire->requestFrom(DS28CM00_DEVICE_ADDRESS, 1);
  if (read < 1) return false;

  mode = _wire->read();
  return true;
}


bool DS28CM00::getUID(uint8_t * buffer, uint8_t size)
{
  _wire->beginTransmission(DS28CM00_DEVICE_ADDRESS);
  _wire->write(DS28CM00_UID_REGISTER);
  int rv = _wire->endTransmission();
  if (rv != 0) return false;

  if (size == 0) return false;
  if (size > 8) size = 8;
  uint8_t read = _wire->requestFrom((uint8_t)DS28CM00_DEVICE_ADDRESS, size);
  if (read < size) return false;

  for (uint8_t i = 0; i < size; i++) 
  {
    buffer[i] = _wire->read();
  }

  return true;
}


////////////////////////////////////////////////////
//
//  PRIVATE
//
bool DS28CM00::setMode(uint8_t mode)
{
  _wire->beginTransmission(DS28CM00_DEVICE_ADDRESS);
  _wire->write(DS28CM00_CONTROL_REGISTER);
  _wire->write(mode);
  int rv = _wire->endTransmission();
  return rv == 0;
}



//  -- END OF FILE --

