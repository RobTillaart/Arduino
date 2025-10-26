#pragma once
//
//    FILE: logicAnalyzer.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-10-20
// VERSION: 0.1.0
// PURPOSE: Arduino library for building a logicAnalyzer. (non performant).
//     URL: https://github.com/RobTillaart/logicAnalyzer
//
//  UNO R3 (16 MHz) can do max 10Khz
//

#include "Arduino.h"


#define LOGICANALYZER_LIB_VERSION         (F("0.1.0"))

//  board dependent but 32 seems OK for now.
#define LA_MAX_CHANNEL                    (32)


//  ERROR CODES
//  values <> 0 are errors.
#define LOGICANALYZER_OK                  (0x00)


class logicAnalyzer
{
public:
  ///////////////////////////////////////
  //
  //  CONFIG
  //
  logicAnalyzer(Stream * str = &Serial);

  bool configPins(uint8_t pins[], uint8_t channels);
  bool configClock(uint8_t clockPin);
  bool setChannels(uint8_t channels);  //  for inject.
  uint8_t getChannels();


  ///////////////////////////////////////
  //
  //  SAMPLE and PLOT
  //
  uint32_t sample();
  void inject(uint32_t data);
  void plot();
  void plotRaw();


  ///////////////////////////////////////
  //
  //  CLOCK
  //
  bool clockChanged();
  bool clockFalling();
  bool clockRising();
  bool clockHIGH();
  bool clockLOW();


  ///////////////////////////////////////
  //
  //  COUNT
  //
  //  if user measures time, the SPS can be calculated.
  void setCount(uint32_t count = 0);
  uint32_t getCount();


private:
  Stream * _stream;
  uint8_t  _size = 0;
  uint8_t  _channels = 0;
  uint8_t  _dataPins[LA_MAX_CHANNEL];
  uint8_t  _clockPin = 255;
  uint32_t _data;
  uint32_t _count;
  uint8_t  _lastClock = LOW;

  inline int _read(uint8_t pin)
  {
    //  optimized versions here
    return digitalRead(pin);
  }

};


//  -- END OF FILE --





