#ifndef DS28CM00_H
#define DS28CM00_H
//
//    FILE: DS28CM00.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Library for the DS28CM00 unique identification chip.
// VERSION: 0.1.0
// HISTORY: See DS28CM00.cpp
//     URL:
//
// Released to the public domain
//

#include <Wire.h>

#include "Arduino.h"

#define DS28CM00_LIB_VERSION      "0.1.0"
#define DS28CM00_I2C_MODE         0x00
#define DS28CM00_SMBUS_MODE       0x01

class DS28CM00
{
public:
  explicit DS28CM00();

  void begin();
  bool getUID(uint8_t *);

  bool setI2CMode()           { return setMode(DS28CM00_I2C_MODE); };
  bool setSMBusMode()         { return setMode(DS28CM00_SMBUS_MODE); };
  bool getMode(uint8_t &mode);

private:
  bool setMode(uint8_t m);
};

#endif

// END OF FILE