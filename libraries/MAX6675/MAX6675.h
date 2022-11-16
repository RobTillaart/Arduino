#pragma once
//
//    FILE: MAX6675.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for MAX6675 chip for K type thermocouple
//    DATE: 2022-01-12
//     URL: https://github.com/RobTillaart/MAX6675


//  TODO Breakout board
//
//       +---------+
//   Vin | o       |
//   3V3 | o       |
//   GND | o     O | Thermocouple
//    D0 | o     O | Thermocouple
//    CS | o       |
//   CLK | o       |
//       +---------+

#include "Arduino.h"
#include "SPI.h"


#define MAX6675_LIB_VERSION               (F("0.1.2"))

#define MAX6675_NO_TEMPERATURE            -999

//  STATE constants returned by read()
//  TODO check
#define STATUS_OK                         0x00
#define STATUS_ERROR                      0x04
#define STATUS_NOREAD                     0x80
#define STATUS_NO_COMMUNICATION           0x81


//  Thermocouples working is based upon Seebeck effect.
//  Different TC have a different Seebeck Coefficient  (µV/°C)
//  See http://www.analog.com/library/analogDialogue/archives/44-10/thermocouple.html
//
//  K_TC == 41.276 µV/°C


class MAX6675
{
public:

  MAX6675();

  //  HW SPI
  void     begin(uint8_t select);
  //  SW SPI
  void     begin(uint8_t clock, uint8_t select, uint8_t miso);

  //       returns state - bit field: 0 = STATUS_OK
  uint8_t  read();
  float    getTemperature(void)  { return _temperature + _offset; };

  uint8_t  getStatus(void) const { return _status; };

  //       use offset to calibrate the TC.
  void     setOffset(const float  t)   { _offset = t; };
  float    getOffset() const           { return _offset; };

  uint32_t lastRead()    { return _lastTimeRead; };
  uint16_t getRawData()  { return _rawData;};

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };
  void     setSWSPIdelay(uint16_t del = 0)  { _swSPIdelay = del; };
  uint16_t getSWSPIdelay() { return _swSPIdelay; };


  //       ESP32 specific
  #if defined(ESP32)
  void     selectHSPI() { _useHSPI = true;  };
  void     selectVSPI() { _useHSPI = false; };
  bool     usesHSPI()   { return _useHSPI;  };
  bool     usesVSPI()   { return !_useHSPI; };

  //       to overrule ESP32 default hardware pins
  void     setGPIOpins(uint8_t clock, uint8_t miso, uint8_t mosi, uint8_t select);
  #endif


private:
  uint32_t _read();

  uint8_t  _status;
  float    _temperature;
  float    _offset;
  uint32_t _lastTimeRead;
  uint16_t _rawData;
  bool     _hwSPI;

  uint8_t  _clock;
  uint8_t  _miso;
  uint8_t  _select;

  uint16_t    _swSPIdelay = 0;
  uint32_t    _SPIspeed;
  SPIClass    * mySPI;
  SPISettings _spi_settings;
  #if defined(ESP32)
  bool        _useHSPI = true;
  #endif
};


// -- END OF FILE --

