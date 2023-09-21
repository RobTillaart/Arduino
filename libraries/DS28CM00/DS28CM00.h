#pragma once
//
//    FILE: DS28CM00.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Library for the DS28CM00 unique identification chip.
// VERSION: 0.3.0
// HISTORY: See DS28CM00.cpp
//     URL: https://github.com/RobTillaart/DS28CM00


#include "Arduino.h"
#include "Wire.h"


#define DS28CM00_LIB_VERSION            (F("0.3.0"))
#define DS28CM00_I2C_MODE               0x00
#define DS28CM00_SMBUS_MODE             0x01
#define DS28CM00_MODE_UNKNOWN           0xFF


class DS28CM00
{
public:
  explicit DS28CM00(TwoWire *wire = &Wire);

#if defined(ESP8266) || defined(ESP32)
  bool     begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  bool     begin();                //  default DS28CM00_I2C_MODE
  bool     isConnected();

  bool     getUID(uint8_t * buffer, uint8_t size = 8);

  bool     setI2CMode()           { return setMode(DS28CM00_I2C_MODE); };
  bool     setSMBusMode()         { return setMode(DS28CM00_SMBUS_MODE); };
  bool     getMode(uint8_t &mode);

private:
  bool     setMode(uint8_t mode);
  TwoWire* _wire;
};


//  -- END OF FILE --

