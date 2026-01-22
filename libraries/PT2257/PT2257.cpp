//
//    FILE: PT2257.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-01-20
// VERSION: 0.1.1
// PURPOSE: Arduino library for the PT2257 two channel volume controller.
//     URL: https://github.com/RobTillaart/PT2257


#include "PT2257.h"


PT2257::PT2257(TwoWire *wire)
{
  _address = 0x44;
  _wire = wire;
  _error = 0;
}


bool PT2257::begin()
{
  //  reset variables
  _error = 0;

  if (! isConnected())
  {
    return false;
  }
  return true;
}


bool PT2257::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t PT2257::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  Functions
//
//  TODO - fix magic numbers
//
void PT2257::allOff()
{
  _write(0xFF);
}

void PT2257::mute()
{
  _muted = true;
  _write(0x79);
}

void PT2257::muteOff()
{
  _muted = false;
  _write(0x78);
}

bool PT2257::isMuted()
{
  return _muted;
}

bool PT2257::stereo(int dB)
{
  dB = abs(dB);
  if (dB > 79) return false;
  _left = _right = dB;
  uint8_t v1 = 0xD0 + dB % 10;
  uint8_t v2 = 0xE0 + dB / 10;
  _write2(v1, v2);
  return true;
}

bool PT2257::left(int dB)
{
  dB = abs(dB);
  if (dB > 79) return false;
  _left = dB;
  uint8_t v1 = 0xA0 + dB % 10;
  uint8_t v2 = 0xB0 + dB / 10;
  _write2(v1, v2);
  return true;
}

bool PT2257::right(int dB)
{
  dB = abs(dB);
  if (dB > 79) return false;
  _right = dB;
  uint8_t v1 = 0x20 + dB % 10;
  uint8_t v2 = 0x30 + dB / 10;
  _write2(v1, v2);
  return true;
}

int PT2257::getLeft()
{
  return -_left;
}

int PT2257::getRight()
{
  return -_right;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int PT2257::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////
//
//  PROTECTED
//
int PT2257::_write(uint8_t command)
{
  _wire->beginTransmission(_address);
  _wire->write(command);
  _error = _wire->endTransmission();
  return _error;
}

int PT2257::_write2(uint8_t val1, uint8_t val2)
{
  _wire->beginTransmission(_address);
  _wire->write(val1);
  _wire->write(val2);
  _error = _wire->endTransmission();
  return _error;
}


///////////////////////////////////////////////
//
//  DERIVED
//
PT2259::PT2259(TwoWire *wire) : PT2257(wire)
{
}

void PT2259::allOff()
{
  stereo(-79);  //  work around
}

void PT2259::mute()
{
  _muted = true;
  _write(0x77);
}

void PT2259::muteOff()
{
  _muted = false;
  _write(0x74);
}

void PT2259::muteLeft()
{
  _muted = false;
  _write(0x76);
}

void PT2259::muteRight()
{
  _muted = false;
  _write(0x75);
}


void PT2259::clearRegister()
{
  _write(0xF0);
}

//  -- END OF FILE --

