#pragma once
//
//    FILE: DS3232.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DS3232 RTC (minimalistic)
// VERSION: 0.4.1
//    DATE: 2011-01-21
//     URL: https://github.com/RobTillaart/DS3232


#include "Arduino.h"
#include "Wire.h"


#define DS3232_LIB_VERSION         "0.4.1"


//  ERROR CODES
#define DS3232_OK                  0
#define DS3232_ERROR_ADDR          -10
#define DS3232_ERROR_I2C           -11
#define DS3232_ERROR_CONNECT       -12


//  REGISTERS DS3232 (maybe also for DS3231)
//  not all used yet
#define DS3232_SECONDS              0x00
#define DS3232_ALARM1               0x07
#define DS3232_ALARM2               0x0B
#define DS3232_CONTROL              0x0E
#define DS3232_AGING_OFFSET         0x10
#define DS3232_TEMPERATURE          0x11
#define DS3232_SRAM_BASE            0x14


class DS3231
{
public:
  //  Constructor
  DS3231(TwoWire *wire = &Wire);
  int      begin();
  bool     isConnected();
  uint8_t  getAddress();
  uint16_t getType();


  //  BASE RTC
  int      read();
  int      write();
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

  //  Temperature
  float    getTemperature();


  //  LOW LEVEL access to all registers
  //  check datasheet for details of registers.
  //  return < 0 is error
  int      readRegister(uint8_t reg);
  int      writeRegister(uint8_t reg, uint8_t value);

  //  Debug
  int      lastRv() { return _rv; };


protected:
  uint8_t   _address;
  TwoWire * _wire;

  //  array holding the values
  uint8_t   _reg[7];
  uint32_t  _lastRead = 0;

  int       _rv;
  uint16_t  _type = 3231;

  uint8_t   dec2bcd(uint8_t value);
  uint8_t   bcd2dec(uint8_t value);
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class DS3232 : public DS3231
{
public:
  DS3232(TwoWire *wire = &Wire);

  //  EXPERIMENTAL SRAM SUPPORT
  //
  //  SRAM 236 bytes, register 0x14-0xFF
  //  index = 0..235 == 0x00..0xEB
  //  236 bytes = 59 x uint32_t (e.g. time stamps)
  //  note: no boundary check
  //  TODO: optimize read/write multiple bytes at once.
  int      SRAMwrite8(uint8_t index, uint8_t value);
  int      SRAMwrite16(uint8_t index, uint16_t value);
  int      SRAMwrite32(uint8_t index, uint32_t value);
  uint8_t  SRAMread8(uint8_t index);
  uint16_t SRAMread16(uint8_t index);
  uint32_t SRAMread32(uint8_t index);

private:

};


//  -- END OF FILE --

