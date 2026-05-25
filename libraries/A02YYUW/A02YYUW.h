#pragma once
//
//    FILE: A02YYUW.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-05-07
// VERSION: 0.1.1
// PURPOSE: Arduino library for A02YYUW serial distance sensor
//     URL: https://github.com/RobTillaart/A02YYUW


#include "Arduino.h"

#define A02YYUW_LIB_VERSION         (F("0.1.1"))

constexpr int A02YY_OK = 0;
constexpr int A02YY_ERR_CRC = -100;


class A02YYUW
{
public:
  A02YYUW(Stream * str, uint8_t TX);

  void     begin();

  //  needed for the UART AUTO only
  //  true  = processed mode
  //  false = real time mode (default)
  void     setProcessingMode(bool mode);
  bool     getProcessingMode();

  //  needed for the UART CONTROLLED only
  void     request();

  //  needed by all
  bool     newDistance();
  uint16_t getDistanceMM();
  float    getDistanceCM();
  float    getDistanceINCH();

  uint32_t lastRead();
  void     flush();

  int      getLastError();

protected:
  Stream * _stream;
  uint8_t  _TX;
  uint8_t  _byte;
  uint8_t  _high, _low;
  uint16_t _millimetres;
  uint32_t _lastRead;

  int      _error;
};


////////////////////////////////////////////
//
//  DERIVED CLASSES (experimental wrappers)
//
class A02YYU : public A02YYUW
{
  public:
  A02YYU(Stream * str, uint8_t TX) : A02YYUW(str, TX)
  {
  }
};

class A02YYT : public A02YYUW
{
  public:
  A02YYT(Stream * str, uint8_t TX) : A02YYUW(str, TX)
  {
  }
};

class A02YYTW : public A02YYUW
{
  public:
  A02YYTW(Stream * str, uint8_t TX) : A02YYUW(str, TX)
  {
  }
};


//  -- END OF FILE --





