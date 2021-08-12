//
//    FILE: MAX31855.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library for MAX31855 chip for K type thermocouple
//    DATE: 2014-01-01
//     URL: https://github.com/RobTillaart/MAX31855_RT
//
//  HISTORY:
//  0.3.0   2021-08-11  VSPI / HSPI support for ESP32
//                      add setGIOpins - ESP32 specific
//                      add get/setSPIspeed() - all
//  0.2.5   2021-07-04  fix #14 CS for STM32
//  0.2.4   2020-12-30  arduinoCI, unit test
//  0.2.3   2020-08-30  fix #8 support hardware SPI + example
//  0.2.2   2020-08-30  fix#9 + fix failing examples + minor refactor
//  0.2.1   2020-08-26  read rawData and STATUS_NO_COMMUNICATION recognition (thanks to FabioBrondo)
//  0.2.0   2020-06-20  #pragma once; major refactor; removed pre 1.0 support; fix offset
//  0.1.10  2019-07-31  add 3 inline functions to test errors + demo sketch
//  0.1.9   2017-07-27  reverted double -> float (issue33)
//  0.1.08  2015-12-06  replaced all temperature calls with one TCfactor + update demos.
//  0.1.07  2015-12-06  updated TC factors from the MAX31855 datasheet
//  0.1.06  2015-12-05  added support for other types of TC's (experimental)
//  0.1.05  2015-07-12  refactor robust constructor
//  0.1.04  2015-03-09  replaced float -> double (ARM support)
//  0.1.03  2014-01-24  fixed negative temperature
//  0.1.02  2014-01-03  added offset
//  0.1.01  2014-01-02  refactored speed/performance
//  0.1.00  2014-01-02  initial version.
//


#include "MAX31855.h"


MAX31855::MAX31855(const uint8_t select)
{
  MAX31855(255, select, 255);
}


MAX31855::MAX31855(const uint8_t clock, const uint8_t select, const uint8_t miso)
{
  _clock       = clock;
  _select      = select;
  _miso        = miso;
  _hwSPI       = (clock == 255);

  _lastTimeRead = 0;
  _offset       = 0;
  _SeebeckC     = K_TC;
  _status       = STATUS_NOREAD;
  _temperature  = MAX31855_NO_TEMPERATURE;
  _internal     = MAX31855_NO_TEMPERATURE;
  _rawData      = 0;
}


void MAX31855::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);

  if (_hwSPI)
  {
    #if defined(ESP32)
    if (_useHSPI)      // HSPI
    {
      mySPI = new SPIClass(HSPI);
      mySPI->end();
      mySPI->begin(14, 12, 13, _select);   // CLK=14 MISO=12 MOSI=13
    }
    else               // VSPI
    {
      mySPI = new SPIClass(VSPI);
      mySPI->end();
      mySPI->begin(18, 19, 23, _select);   // CLK=18 MISO=19 MOSI=23
    }
    #else              // generic hardware SPI
    mySPI = &SPI;
    mySPI->end();
    mySPI->begin();
    #endif
    delay(1);
  }
  else
  {
    pinMode(_clock, OUTPUT);
    digitalWrite(_clock, LOW);
    pinMode(_miso, INPUT);
  }
}


void MAX31855::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
};


#if defined(ESP32)
void MAX31855::setGPIOpins(uint8_t clock, uint8_t miso, uint8_t mosi, uint8_t select)
{
  _clock   = clock;
  _miso    = miso;
  _select  = select;
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  mySPI->end();  // disable SPI
  mySPI->begin(clock, miso, mosi, select);
}
#endif


uint8_t MAX31855::read()
{
  // return value of _read()
  // BITS     DESCRIPTION
  // ----------------------
  // 00 - 02  STATUS
  //      03  RESERVED
  // 04 - 15  INTERNAL
  //      16  FAULT-BIT
  //      17  RESERVED
  // 18 - 30  TEMPERATURE (RAW)
  //      31  SIGN
  uint32_t value = _read();

  if (value == 0xFFFFFFFF)  // needs a pull up on miso pin to work properly!
  {
    // bit 3 and bit 17 should always be 0 - P10 datasheet
    _status = STATUS_NO_COMMUNICATION;
    return _status;
  }

  _lastTimeRead = millis();

  // process status bit 0-2
  _status = value & 0x0007;
  if (_status != STATUS_OK)
  {
    return _status;
  }

  value >>= 3;

  // reserved bit 3, always 0
  value >>= 1;

  // process internal bit 4-15
  _internal = (value & 0x07FF) * 0.0625;
  // negative flag set ?
  if (value & 0x0800)
  {
    _internal = -128 + _internal;
  }
  value >>= 12;

  // Fault bit ignored as we have the 3 status bits
  // _fault = value & 0x01;
  value >>= 1;

  // reserved bit 17, always 0
  value >>= 1;

  // process temperature bit 18-30 + sign bit = 31
  _temperature = (value & 0x1FFF) * 0.25;
  // negative flag set ?
  if (value & 0x2000)
  {
    _temperature = -2048 + _temperature;
  }
  return _status;
}


uint32_t MAX31855::_read(void)
{
  _rawData = 0;
  // DATA TRANSFER
  if (_hwSPI)
  {
    mySPI->beginTransaction(_spi_settings);
    digitalWrite(_select, LOW);         // must be after mySPI->beginTransaction() - see #14 STM32
    for (uint8_t i = 0; i < 4; i++)
    {
      _rawData <<= 8;
      _rawData += mySPI->transfer(0);
    }
    digitalWrite(_select, HIGH);
    mySPI->endTransaction();
  }
  else  // Software SPI
  {
    digitalWrite(_select, LOW);
    for (int8_t i = 31; i >= 0; i--)
    {
      _rawData <<= 1;
      digitalWrite(_clock, LOW);
      // delayMicroseconds(1);  // DUE
      if ( digitalRead(_miso) ) _rawData++;
      digitalWrite(_clock, HIGH);
      // delayMicroseconds(1);  // DUE
    }
    digitalWrite(_select, HIGH);
  }

  return _rawData;
}


float MAX31855::getTemperature()
{
  // offset needs to be added after multiplication TCfactor
  // not before otherwise offset will be larger / smaller
  // default behaviour
  if (_SeebeckC == K_TC) return _temperature + _offset;

  // EXPERIMENTAL OTHER THERMOCOUPLES
  // to be tested
  // in practice this works also for K_TC but is way slower..
  // 1: reverse calculate the Voltage measured  (is this correct?)
  float Vout = K_TC * (_temperature - _internal);  // PAGE 8 datasheet

  // 2: from Voltage to corrected temperature using the Seebeck Coefficient
  float _temp = Vout / _SeebeckC + _internal + _offset;
  return _temp;
}


// -- END OF FILE --
