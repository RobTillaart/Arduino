#pragma once
//
//    FILE: DS1683.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-09-13
// VERSION: 0.1.0
// PURPOSE: Arduino library for the I2C DS1683 elapsed time monitor
//     URL: https://github.com/RobTillaart/DS1683
//


#include "Arduino.h"
#include "Wire.h"


#define DS1683_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
const uint8_t DS1683_OK            = 0x00;
const uint8_t DS1683_I2C_2         = 0x02;  //  not connected
const uint8_t DS1683_NOT_READY     = 0x10;
const uint8_t DS1683_REQUEST_ERROR = 0x11;
const uint8_t DS1683_EEPROM_ERROR  = 0x12;


class DS1683
{
public:
  //  Fixed address 0x6B (107)
  DS1683(TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  CONFIGURATION - page 14 datasheet.
  //
  //  | BIT | NMEMONIC | DESCRIPTION |
  //  |:---:|:---------|:------------|
  //  |  0  | ALRM POL | Alarm Polarity
  //  |  1  | EC ENAB  | Event Counter Alarm Enable
  //  |  2  | ETC ENAB | Event Timer Alarm Enable
  //  | 3-7 | not used | always 0
  int      setConfiguration(uint8_t mask);
  uint8_t  getConfiguration();


  //  COMMAND - page 11 datasheet.
  //
  //  | BIT | NMEMONIC | DESCRIPTION |
  //  |:---:|:---------|:------------|
  //  |  0  | CLR-ALM  | Clear Alarm
  //  | 1-7 | not used |
  int      setCommand(uint8_t command);
  uint8_t  getCommand();


  //  STATUS - page 11 datasheet.
  //
  //  | BIT | NMEMONIC | DESCRIPTION |
  //  |:---:|:---------|:------------|
  //  |  0  | ETC AF   | Event Timer Flag
  //  |  1  | EC AV    | Event Counter Flag
  //  |  2  | EVENT    | status EVENT pin
  //  | 3-7 | not used |
  uint8_t  getStatus();


  //  ALARM - page 13,14 datasheet.
  int      setEventTimeAlarm(uint32_t alarm);  //  alarm in seconds, max 1.073.741.823
  uint32_t getEventTimeAlarm();
  int      setEventCountAlarm(uint16_t alarm);  //  alarm in counts.
  uint16_t getEventCountAlarm();


  //  READ COUNTERS - page 12-13 datasheet.
  uint32_t getElapsedSeconds();  //  returns seconds
  uint32_t getElapsedQSEC();     //  returns quarter-seconds (internal counter)
  uint32_t getEventCounter();    //  returns event counter


  //  RESET COUNTERS - page 7 datasheet
  int      resetEventTime();
  int      resetEventCounter();


  //  EEPROM - page 15 datasheet.
  //  address = 0..15
  int      setEEPROM(uint8_t address, uint8_t value);
  uint8_t  getEEPROM(uint8_t address);


  //  PASSWORD - page 12,15 datasheet.
  //  default password = 0xFFFFFFFF
  int      setPasswordEntry(uint32_t value);
  int      setPasswordValue(uint32_t value);

  //       DEBUG
  int      getLastError();


private:
  uint8_t  _address = 0x6B;
  TwoWire* _wire;

  int      _command(uint8_t reg, uint8_t * arr, uint8_t size);
  int      _request(uint8_t reg, uint8_t * arr, uint8_t size);

  uint8_t  _error;
};


//  -- END OF FILE --





