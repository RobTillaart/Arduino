#pragma once
//
//    FILE: SD2405.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for I2C SD2405 RTC and compatibles.
// VERSION: 0.1.1
//    DATE: 2022-03-17
//     URL: https://github.com/RobTillaart/SD2405


#include "Arduino.h"
#include "Wire.h"


#define SD2405_LIB_VERSION           (F("0.1.1"))


//  ERROR CODES
#define SD2405_OK                  0
#define SD2405_ERROR_ADDR          -10
#define SD2405_ERROR_I2C           -11
#define SD2405_ERROR_CONNECT       -12


//  REGISTERS SD2405 (maybe also for SD2405)
//  not all used yet
#define SD2405_SECONDS              0x00
#define SD2405_ALARM1               0x07
#define SD2405_ALARM2               0x0B
#define SD2405_CONTROL              0x0E
#define SD2405_AGING_OFFSET         0x10
#define SD2405_TEMPERATURE          0x11
#define SD2405_SRAM_BASE            0x14



// SD2405AL

class SD2405
{
public:
  //  Constructor
  SD2405(TwoWire *wire = &Wire);
  int      begin();
  bool     isConnected();
  uint8_t  getAddress();


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


  //  EXPERIMENTAL SRAM SUPPORT
  //
  //  SRAM 12 bytes, register 0x14-0x1F
  //  index = 0..11 == 0x00..0x1B
  //  12 bytes = 3 x uint32_t (e.g. time stamps)
  //  note: no boundary check
  //  TODO: optimize read/write multiple bytes at once.
  int      SRAMwrite8(uint8_t index, uint8_t value);
  int      SRAMwrite16(uint8_t index, uint16_t value);
  int      SRAMwrite32(uint8_t index, uint32_t value);
  uint8_t  SRAMread8(uint8_t index);
  uint16_t SRAMread16(uint8_t index);
  uint32_t SRAMread32(uint8_t index);


  //  LOW LEVEL access to all registers
  //  check datasheet for details of registers.
  //  return < 0 is error
  int      readRegister(uint8_t reg);
  int      writeRegister(uint8_t reg, uint8_t value);


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



//  -- END OF FILE --

