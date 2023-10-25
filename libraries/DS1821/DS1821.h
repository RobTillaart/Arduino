#pragma once
//
//    FILE: DS1821.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.6
//    DATE: 2014-10-05
// PURPOSE: Arduino library for DS1821 temperature sensor
//     URL: https://github.com/RobTillaart/DS1821
//
//
//      BOTTOM VIEW
//
//                  PIN     MEANING
//       /---+
//      /  o |      1       GND
//      |  o |      2       DATA
//      \  o |      3       VCC
//       \---+


#include "Arduino.h"
#include "OneWire.h"


#define DS1821_H_LIB_VERSION     (F("0.3.6"))

#define DS1821_RESET_OK          0
#define DS1821_RESET_ERROR       -999


class DS1821
{
public:
  DS1821(OneWire* ow);

  //  THERMOMETER MODE
  int        requestTemperature();
  int        requestContinuous();
  int        stopContinuous();

  int        conversionReady();
  float      readTemperature();
  int        error()  { int e = _error; _error = 0; return e; };

  //  High and low temperature 'alarm' flags.
  int        setLow(int8_t lo);
  int        getLow();
  int        setHigh(int8_t hi);
  int        getHigh();
  //  flags in configuration register => 1 = triggered since clear
  int        getHighFlag();
  int        clrHighFlag();
  int        getLowFlag();
  int        clrLowFlag();

  //  THERMOSTAT CONFIG
  //  - be sure to  read datasheet first!
  //  - check the example
  //  - DQ pin must be same the oneWire pin!
  int        setOneWireMode(uint8_t VDD, uint8_t DQ);
  int        setPolarity(int activeState);  //  HIGH or LOW
  int        getPolarity();
  int        setThermostatMode();

private:
  OneWire * _oneWire;
  int       _error;

  int       _reset()                { _error = _oneWire->reset(); return _error; };
  void      _command(uint8_t cmd)   { _oneWire->write(cmd); };
  uint8_t   _readByte()             { return _oneWire->read(); };
  uint8_t   _waitForNVB();
  int       _getConfigFlag(uint8_t flag);
  int       _setConfigFlag(uint8_t flag);
  int       _clrConfigFlag(uint8_t flag);
  int       _readConfig();
  int       _writeConfig(uint8_t val);

  uint8_t   _VDD;
  uint8_t   _DQ;
};


//  -- END OF FILE --

