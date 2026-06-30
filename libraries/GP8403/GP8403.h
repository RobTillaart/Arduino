#pragma once
//
//    FILE: GP8403.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-01-30
// PURPOSE: Arduino library for GP8403, I2C 12 bit two channel DAC.
//     URL: https://github.com/RobTillaart/GP8403
//

#include "Arduino.h"
#include "Wire.h"


#define GP8403_LIB_VERSION         (F("0.1.0"))


const int GP8403_DEFAULT_ADDRESS = 0x38;

//  ERROR CODES
//  values <> 0 are errors.
constexpr int GP8403_OK = 0x00;


class GP8403
{
public:
  GP8403(uint8_t address, TwoWire *wire = &Wire);

  //       CONFIGURATION
  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //  range = 5 or 10 V, 5 = default.
  bool     setRange(uint8_t range);
  uint8_t  getRange();  //  returns 0 if not initialized.

  uint8_t  channels();
  uint16_t maxValue();  //  0x0FFF

  //       CORE
  //       channel = 0, 1.
  bool     setValue(uint8_t channel, uint16_t value);
  uint16_t getValue(uint8_t channel);

  //       return false if at end of range.
  bool     increment(uint8_t channel);
  bool     decrement(uint8_t channel);

  //       convenience wrappers
  //       percentage = 0..100.0%
  bool     setPercentage(uint8_t channel, float percentage);
  float    getPercentage(uint8_t channel);

  //       DEBUG
  int      getLastError();


protected:
  uint8_t  _address;
  TwoWire* _wire;

  int      _writeRegister8(uint8_t reg, uint8_t value);
  int      _writeRegister16(uint8_t reg, uint16_t value);

  uint8_t  _channels;  //  Number of DAC-Channels of a given Chip
  uint16_t _maxValue;  //  Maximum value of a given Chip
  uint16_t _value[2];  //  Current value  (cache)
  uint8_t  _range;     //  Current range  (cache)

  uint8_t  _error;
};



///////////////////////////////////////////////////
//
//  DERIVED GP8413
//
//  class GP8413 : public GP8403
//  {
//    GP8413(uint8_t address, TwoWire *wire = &Wire);
//    bool     setValue(uint8_t channel, uint16_t value);  //  15 bit
//  };


//  -- END OF FILE --





