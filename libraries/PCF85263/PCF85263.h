#pragma once
//
//    FILE: PCF85263.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-17
// VERSION: 0.1.0
// PURPOSE: Arduino library for the PCF85263 RTC (I2C).
//     URL: https://github.com/RobTillaart/PCF85263


#include "Arduino.h"
#include "Wire.h"


#define PCF85263_LIB_VERSION         (F("0.1.0"))
#define PCF85263_DEFAULT_ADDRESS     0x51


///////////////////////////////////////////
//
//  ERROR CODES
//
//  values <> 0 are errors.
#define PCF85263_OK                   0
#define PCF85263_ERROR_ADDR           -10
#define PCF85263_ERROR_I2C            -11
#define PCF85263_ERROR_CONNECT        -12


///////////////////////////////////////////
//
//  REGISTERS  RTC MODE - page 7
//  note not all functionality is implemented.
//
//  DATE - TIME section 7.2
#define PCF85263_SECONDS_100TH        0x00
#define PCF85263_SECONDS              0x01
#define PCF85263_MINUTES              0x02
#define PCF85263_HOURS                0x03
#define PCF85263_DAYS                 0x04
#define PCF85263_WEEKDAYS             0x05
#define PCF85263_MONTHS               0x06
#define PCF85263_YEARS                0x07

//  ALARMS section 7.4
#define PCF85263_ALARM1               0x08
#define PCF85263_ALARM2               0x0D
#define PCF85263_ALARM_ENABLE         0x10

//  TIMESTAMPS section 7.7
#define PCF85263_TIMESTAMP1           0x11
#define PCF85263_TIMESTAMP2           0x17
#define PCF85263_TIMESTAMP3           0x1D
#define PCF85263_TIMESTAMP_MODE       0x23

//  CONTROL
#define PCF85263_OFFSET               0x24        //  page 29
#define PCF85263_OSCILLATOR           0x25        //  page 37
#define PCF85263_BATTERY              0x26        //  page 38
#define PCF85263_PINIO                0x27        //  page 44
#define PCF85263_FUNCTION             0x28        //  page 48
#define PCF85263_INTA_ENABLE          0x29        //  page 33
#define PCF85263_INTB_ENABLE          0x2A        //  page 33
#define PCF85263_FLAGS                0x2B        //  page 51
#define PCF85263_RAMBYTE              0x2C        //  page 24
#define PCF85263_WATCHDOG             0x2D        //  page 22
#define PCF85263_STOP_ENABLE          0x2E        //  page 54
#define PCF85263_RESETS               0x2F        //  page 52


///////////////////////////////////////////
//
//  REGISTERS  STOPWATCH MODE
//
//  STOPWATCH section 7.3
//
//  0x00-0x03 same register names
#define PCF85263_HOURS_100            0x04
#define PCF85263_HOURS_10000          0x05
//  0x06 en 0x07 not used
//  0x08-0x23 registers same names


class PCF85263
{
public:
  //  Constructor
  PCF85263(TwoWire *wire = &Wire);
  int      begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  BASE RTC
  int      readDateTime();
  int      writeDateTime();
  uint32_t lastRead();


  //  Getters
  uint8_t  seconds();
  uint8_t  minutes();
  uint8_t  hours();
  uint8_t  weekDay();
  uint8_t  day();
  uint8_t  month();
  uint8_t  year();


  //  Setters
  void     setSeconds(uint8_t value);
  void     setMinutes(uint8_t value);
  void     setHours(uint8_t value);
  void     setWeekDay(uint8_t value);
  void     setDay(uint8_t value);
  void     setMonth(uint8_t value);
  void     setYear(uint8_t value);


  //  FUNCTION register
  //  0 => RTC mode,  1 = Stopwatch mode,  other ignored.
  void     setRTCmode(uint8_t mode = 0);


  //  STOP_ENABLE register
  void     startRTC();
  void     stopRTC();


  //  LOW LEVEL
  //  access to all registers
  //  check datasheet for details of registers.
  //  return < 0 is error
  int      readRegister(uint8_t reg);
  int      writeRegister(uint8_t reg, uint8_t value);

  //  DEBUGGING
  //  get last low level return value, 0 == OK.
  int      getLastI2Cstate();

private:
  //  fixed address
  const uint8_t _address = PCF85263_DEFAULT_ADDRESS;
  TwoWire *     _wire;

  //  array holding the values
  uint8_t   _reg[7];
  uint32_t  _lastRead = 0;

  int       _rv;
  uint16_t  _error = PCF85263_OK;

  uint8_t   dec2bcd(uint8_t value);
  uint8_t   bcd2dec(uint8_t value);
};


