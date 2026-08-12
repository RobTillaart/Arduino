#pragma once
//
//    FILE: DS3501.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-08-12
// VERSION: 0.1.0
// PURPOSE: Arduino library for the DS3501, I2C, 7-bit, non-volatile, digital potentiometer. Temperature control.
//     URL: https://github.com/RobTillaart/DS3501
//


#include "Arduino.h"
#include "Wire.h"


#define DS3501_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
const uint8_t  DS3501_OK             = 0x00;
const uint8_t  DS3501_READ_ERROR     = 0x01;
const uint8_t  DS3501_REQUEST_ERROR  = 0x02;
const uint8_t  DS3501_CONNECT_ERROR  = 0x03;
const uint8_t  DS3501_VALUE_ERROR    = 0x04;
const uint8_t  DS3501_LUTINDEX_ERROR = 0x05;


//  value == 0..127
//  64 == 0x40 == default == middle value.
const uint8_t  DS3501_MIDDLE_VALUE   = 0x40;

//  maximum resistor value, adjust if needed.
//  default = 10 kΩ, value in Ohm Ω
const uint32_t DS3501_MAX_OHM = 10000;

//  MODE
//  datasheet page 7, table 1
const uint8_t  DS3501_DEFAULT_MODE   = 0x00;
const uint8_t  DS3501_LUT_MODE       = 0x01;
const uint8_t  DS3501_LUT_ADDER_MODE = 0x03;


class DS3501
{
public:
  DS3501(uint8_t address, TwoWire *wire = &Wire);

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

  //  Ohm wrappers, based on DS3501_MAX_OHM
  //  default max 10 kΩ, truncates values.
  bool     setOhm(uint16_t ohm);
  int16_t  getOhm();

  //  internal status
  int16_t  getTemperature();
  int16_t  getMilliVolt();  //  mV to keep integer math


  //  MODE
  void     setDefaultMode();
  void     setLUTMode();
  void     setLUTADDERMode();
  //  return 0, 1, 3 see MODE above.
  //  -1 indicates error.
  int      getMode();

  //  LUT-TABLE
  //  index = 0..35, value = 0..127
  bool     setLUTtable(uint8_t index, uint8_t value);
  //  return value -1 indicates error.
  int      getLUTtable(uint8_t index);

  //  only in LUT mode,
  //  should return 0..35, 0xFF => error.
  int      getLUTAR();
  int      getWIPER();

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





