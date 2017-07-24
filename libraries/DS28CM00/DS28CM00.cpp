//
//    FILE: DS28CM00.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Library for the DS28CM00 unique identification chip.
// VERSION: 0.1.0
//     URL:
//
// HISTORY:
// 0.1.0  2017-07-15 initial version
//
// Released to the public domain
//

#include "DS28CM00.h"

#define DS28CM00_DEVICEADDRESS    0x50
#define DS28CM00_UIDREGISTER      0x00
#define DS28CM00_CONTROLREGISTER  0x08


DS28CM00::DS28CM00()
{
}

void DS28CM00::begin()
{
  Wire.begin();
  setI2CMode();
}

bool DS28CM00::setMode(uint8_t mode)
{
  Wire.beginTransmission(DS28CM00_DEVICEADDRESS);
  Wire.write(DS28CM00_CONTROLREGISTER);
  Wire.write(mode);
  int rv = Wire.endTransmission();
  return rv == 0;
}

bool DS28CM00::getMode(uint8_t &mode)
{
  Wire.beginTransmission(DS28CM00_DEVICEADDRESS);
  Wire.write(DS28CM00_CONTROLREGISTER);
  int rv = Wire.endTransmission();
  if (rv != 0) return false;

  uint8_t read = Wire.requestFrom(DS28CM00_DEVICEADDRESS, 1);
  if (read < 1) return false;

  mode = Wire.read();

  return true;
}

bool DS28CM00::getUID(uint8_t *buffer)
{
  Wire.beginTransmission(DS28CM00_DEVICEADDRESS);
  Wire.write(DS28CM00_UIDREGISTER);
  int rv = Wire.endTransmission();
  if (rv != 0) return false;

  uint8_t read = Wire.requestFrom(DS28CM00_DEVICEADDRESS, 8);
  if (read < 8) return false;

  for (uint8_t i = 0; i < 8; i++) buffer[i] = Wire.read();
  // if (buffer[0] != 0x70) return false

  return true;
}

// END OF FILE