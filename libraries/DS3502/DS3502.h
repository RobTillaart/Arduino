#pragma once
//
//    FILE: DS3502.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-08-10
// VERSION: 0.1.1
// PURPOSE: Arduino library for the DS3502, I2C, 7-bit, non-volatile, digital potentiometer.
//     URL: https://github.com/RobTillaart/DS3502
//


#include "Arduino.h"
#include "Wire.h"


#define DS3502_LIB_VERSION         (F("0.1.1"))

//  ERROR CODES
//  values <> 0 are errors.
const uint8_t DS3502_OK             = 0x00;
const uint8_t DS3502_READ_ERROR     = 0x01;
const uint8_t DS3502_REQUEST_ERROR  = 0x02;
const uint8_t DS3502_CONNECT_ERROR  = 0x03;
const uint8_t DS3502_VALUE_ERROR    = 0x04;
const uint8_t DS3502_LUTINDEX_ERROR = 0x05;


//  value == 0..127
//  64 == 0x40 == default == middle value.
const uint8_t  DS3502_MIDDLE_VALUE = 0x40;

//  maximum resistor value, adjust if needed.
//  default = 10 kΩ
const uint32_t DS3502_MAX_OHM = 10000;  //  in Ohm Ω


class DS3502
{
public:
  DS3502(uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //       MODE
  //       enables write to NVRAM with next write.
  bool     enableNVRAM(bool nvram);
  bool     isEnabledNVRAM();

  //       set value potmeter 0..127
  void     enableCache(bool cache);
  bool     isEnabledCache();

  //       set value potmeter 0..127
  bool     setValue(uint8_t value);
  int      getValue();

  //  Ohm wrappers, based on DS3502_MAX_OHM
  //  default max 10 kΩ, truncates values.
  bool     setOhm(uint16_t ohm);
  int16_t  getOhm();

  //       DEBUG
  int      getLastError();


private:
  uint8_t  _address = 0x2A;
  TwoWire* _wire;

  int      _write(uint8_t reg, uint8_t value);
  uint8_t  _read(uint8_t reg);
  uint8_t  _lastValue = 255;  //  cached value.
  bool     _useNVRAM = false;
  bool     _useCache = false;

  int      _error;
};


//  -- END OF FILE --





