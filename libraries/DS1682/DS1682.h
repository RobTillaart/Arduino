#pragma once
//
//    FILE: DS1682.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-09-11
// VERSION: 0.1.0
// PURPOSE: Arduino library for the I2C DS1682 elapsed time monitor.
//     URL: https://github.com/RobTillaart/DS1682
//


#include "Arduino.h"
#include "Wire.h"


#define DS1682_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
const uint8_t DS1682_OK            = 0x00;
const uint8_t DS1682_I2C_2         = 0x02;  //  not connected
const uint8_t DS1682_NOT_READY     = 0x10;
const uint8_t DS1682_REQUEST_ERROR = 0x11;
const uint8_t DS1682_EEPROM_ERROR  = 0x12;


class DS1682
{
public:
  DS1682(TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();

  //  CONFIGURATION - page 10 datasheet.
  //
  //  | BIT | NMEMONIC | DESCRIPTION |
  //  |:---:|:---------|:------------|
  //  |  0  | ECMSB    | Event Counter MSB
  //  |  1  | AP       | Alarm Polarity
  //  |  2  | RE       | Reset Enabled, enables reset() command.
  //  |  3  | AOS      | Alarm Output Select
  //  |  4  | WMDF     | Write Memory Disable Flag
  //  |  5  | WDF      | Write Disable Flag
  //  |  6  | AF       | Alarm Flag
  //  |  7  | not used | always 0
  int      setConfiguration(uint8_t mask);
  uint8_t  getConfiguration();

  //  ALARM
  int      setAlarm(uint32_t alarm);  //  alarm in seconds, max 1.073.741.823
  uint32_t getAlarm();                //  returns seconds.

  //  READ COUNTERS
  uint32_t getElapsedSeconds();       //  returns seconds
  uint32_t getElapsedQSEC();          //  returns quarter-seconds (internal counter)
  uint32_t getEventCounter();         //  returns event counter

  //  EEPROM
  int      setEEPROM(uint8_t ee, uint8_t value);
  uint8_t  getEEPROM(uint8_t ee);

  //  MISC - names might change
  //  these functions need to be called twice to be effective!!!
  int      reset(bool flag);
  int      writeDisable(bool flag);
  int      memoryDisable(bool flag);

  //       DEBUG
  int      getLastError();


private:
  uint8_t  _address = 0x2A;
  TwoWire* _wire;

  int      _command(uint8_t reg, uint8_t * arr, uint8_t size);
  int      _request(uint8_t reg, uint8_t * arr, uint8_t size);

  uint8_t  _error;
};


//  -- END OF FILE --





