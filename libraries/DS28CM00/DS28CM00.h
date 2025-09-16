#pragma once
//
//    FILE: DS28CM00.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Library for the DS28CM00 unique identification chip.
// VERSION: 0.4.1
//    DATE: 2017-07-15
//     URL: https://github.com/RobTillaart/DS28CM00


#include "Arduino.h"
#include "Wire.h"


#define DS28CM00_LIB_VERSION            (F("0.4.1"))
#define DS28CM00_I2C_MODE               0x00
#define DS28CM00_SMBUS_MODE             0x01
#define DS28CM00_MODE_UNKNOWN           0xFF

//  uncomment to have a cache of 8 bytes
//  or use a command line define.
//  #define DS28CM00_CACHE                  0x01

class DS28CM00
{
public:
  explicit DS28CM00(TwoWire *wire = &Wire);

  bool     begin();       //  default DS28CM00_I2C_MODE
  bool     isConnected();

  bool     getUID(uint8_t * buffer, uint8_t size = 8);

  inline bool setI2CMode() { return setMode(DS28CM00_I2C_MODE); };
  inline bool setSMBusMode() { return setMode(DS28CM00_SMBUS_MODE); };
  bool     getMode(uint8_t &mode);

private:
  bool     setMode(uint8_t mode);
  TwoWire* _wire;

#ifdef DS28CM00_CACHE
  uint8_t  _cache[8];
  bool     _cacheRead = false;
#endif
};


//  -- END OF FILE --

