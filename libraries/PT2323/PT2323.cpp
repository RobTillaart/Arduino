//
//    FILE: PT2323.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-07-23
// VERSION: 0.1.0
// PURPOSE: Arduino library for PT2323 I2C 6 channel audio processor / selector.
//     URL: https://github.com/RobTillaart/PT2323


#include "PT2323.h"


PT2323::PT2323(TwoWire *wire)
{
  _wire = wire;
}


bool PT2323::begin()
{
  if (! isConnected()) return false;
  setChannel(0);
  //  TODO initialize defaults.
  return true;
}

uint8_t PT2323::getAddress()
{
  return _address;
}

bool PT2323::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}

//
//  CHANNEL
//
bool PT2323::setChannel(uint8_t channel)
{
  if (channel > 3 && channel != 6)
  {
    return false;
  }

  uint8_t cmd = 0;
  if      (channel == 6) cmd = 0xC7;
  else if (channel == 3) cmd = 0xC8;
  else if (channel == 2) cmd = 0xC9;
  else if (channel == 1) cmd = 0xCA;
  else if (channel == 0) cmd = 0xCB;

  if (write(cmd) == 0)
  {
    _channel = channel;
    return true;
  }
  return false;
}

uint8_t PT2323::getChannel()
{
  return _channel;
}


//
//  MUTE
//
bool PT2323::muteFrontLeft(bool mute)
{
  uint8_t cmd = 0xF0;
  if (mute) cmd |= 0x01;
  return write(cmd) == 0;
}

bool PT2323::muteFrontRight(bool mute)
{
  uint8_t cmd = 0xF2;
  if (mute) cmd |= 0x01;
  return write(cmd) == 0;
}

bool PT2323::muteCenter(bool mute)
{
  uint8_t cmd = 0xF4;
  if (mute) cmd |= 0x01;
  return write(cmd) == 0;
}

bool PT2323::muteSubWoofer(bool mute)
{
  uint8_t cmd = 0xF6;
  if (mute) cmd |= 0x01;
  return write(cmd) == 0;
}

bool PT2323::muteRearLeft(bool mute)
{
  uint8_t cmd = 0xF8;
  if (mute) cmd |= 0x01;
  return write(cmd) == 0;
}

bool PT2323::muteRearRight(bool mute)
{
  uint8_t cmd = 0xFA;
  if (mute) cmd |= 0x01;
  return write(cmd) == 0;
}

bool PT2323::muteAll(bool mute)
{
  uint8_t cmd = 0xFE;
  if (mute) cmd |= 0x01;
  return write(cmd) == 0;
}


//
//  SURROUND
//
bool PT2323::setSurround(bool enable)
{
  uint8_t cmd = 0xD0;
  if (enable) cmd |= 0x01;
  if (write(cmd) == 0)
  {
    _surround = enable;
    return true;
  }
  return false;
}

bool PT2323::getSurround()
{
  return _surround;
}


//
//  MIXED CHANNEL
//
bool PT2323::setMixedChannel(bool six_db)
{
  uint8_t cmd = 0xFE;
  if (six_db) cmd |= 0x01;
  if (write(cmd) == 0)
  {
    _mixedChannel = six_db;
    return true;
  }
  return false;
}

bool PT2323::getMixedChannel()
{
  return _mixedChannel;
}

int PT2323::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////////
//
//  PRIVATE
//
int PT2323::write(uint8_t cmd)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd);
  _error = _wire->endTransmission();
  return _error;
}


//  -- END OF FILE --

