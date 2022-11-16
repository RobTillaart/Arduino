#pragma once
//
//    FILE: MAX31855.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.2
// PURPOSE: Arduino library for MAX31855 chip for K type thermocouple
//    DATE: 2014-01-01
//     URL: https://github.com/RobTillaart/MAX31855_RT
//          http://forum.arduino.cc/index.php?topic=208061


//        Breakout board
//
//         +---------+
//     Vin | o       |
//     3V3 | o       |
//     GND | o     O |   Thermocouple
//      D0 | o     O |   Thermocouple
//      CS | o       |
//     CLK | o       |
//         +---------+


#include "Arduino.h"
#include "SPI.h"


#define MAX31855_VERSION              (F("0.4.2"))

#define MAX31855_NO_TEMPERATURE       -999

// STATE constants returned by read()
#define STATUS_OK                     0x00
#define STATUS_OPEN_CIRCUIT           0x01
#define STATUS_SHORT_TO_GND           0x02
#define STATUS_SHORT_TO_VCC           0x04
#define STATUS_ERROR                  0x07
#define STATUS_NOREAD                 0x80
#define STATUS_NO_COMMUNICATION       0x81


//  Thermocouples working is based upon Seebeck effect.
//  Different TC have a different Seebeck Coefficient  (µV/°C)
//  See http://www.analog.com/library/analogDialogue/archives/44-10/thermocouple.html
//
//  As the MAX31855 is designed for K type sensors, one can calculate
//  the factor needed to convert other sensors measurements.
//  NOTE: this is only a linear approximation.
//
//  Seebeck Coefficients (sensitivity) from the MAX31855 datasheet page 8
//  to be used in setSeebeckCoefficient()
//
//      TYPE    COEFFICIENT
#define E_TC    76.373
#define J_TC    57.953
#define K_TC    41.276
#define N_TC    36.256
#define R_TC    10.506
#define S_TC    9.587
#define T_TC    52.18


class MAX31855
{
public:

  MAX31855();

  //  HW SPI
  void     begin(uint8_t select);
  //  SW SPI
  void     begin(uint8_t clock, uint8_t select, uint8_t miso);

  //  returns state - bit field: 0 = STATUS_OK
  uint8_t  read();

  float    getInternal(void) const { return _internal; }
  float    getTemperature(void);

  uint8_t  getStatus(void) const  { return _status; };
  inline   bool openCircuit()     { return _status == STATUS_OPEN_CIRCUIT; };
  inline   bool shortToGND()      { return _status == STATUS_SHORT_TO_GND; };
  inline   bool shortToVCC()      { return _status == STATUS_SHORT_TO_VCC; };
  inline   bool genericError()    { return _status == STATUS_ERROR; };
  inline   bool noRead()          { return _status == STATUS_NOREAD; };
  inline   bool noCommunication() { return _status == STATUS_NO_COMMUNICATION; };

  //  use offset to calibrate the TC.
  void     setOffset(const float  t)   { _offset = t; };
  float    getOffset() const           { return _offset; };

  //  set the above E_TC or other Seebeck Coefficients
  //  one can also set your own optimized values.
  void     setSeebeckCoefficient(const float SC) { _SeebeckC = SC; };
  float    getSeebeckCoefficient() const         { return _SeebeckC; };

  uint32_t lastRead()    { return _lastTimeRead; };
  uint32_t getRawData()  { return _rawData;};

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

  //  to overrule ESP32 default hardware pins
  void     setGPIOpins(uint8_t clock, uint8_t miso, uint8_t mosi, uint8_t select);
  #endif


private:
  uint32_t _read();

  uint8_t  _status;
  float    _internal;
  float    _temperature;
  float    _offset;
  float    _SeebeckC;
  uint32_t _lastTimeRead;
  uint32_t _rawData;
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
