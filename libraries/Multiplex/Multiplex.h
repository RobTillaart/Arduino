#pragma once
//
//    FILE: Multiplex.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.9
// PURPOSE: Arduino Library implementing a Print stream multiplexer.
//    DATE: 2021-01-09
//     URL: https://github.com/RobTillaart/Multiplex


#include "Arduino.h"


#define MULTIPLEX_LIB_VERSION         (F("0.2.9"))


//  MAX 254 (in theory) as 0xFF is a special value
#ifndef MAX_MULTIPLEX
#define MAX_MULTIPLEX                 4
#endif


class Multiplex: public Print
{
public:
  //  CONSTRUCTOR
  Multiplex();
  ~Multiplex();

  //  POPULATE
  void     reset();
  //  add new stream (cannot add a stream twice).
  //  returns true on success
  bool     add(Print * stream);
  //  remove
  //  use with care as it changes the indices.
  bool     remove(Print * stream);
  bool     remove(uint8_t index);
  //  find index or stream
  uint8_t  index(Print *stream);
  Print *  stream(uint8_t index);
  //  metrics
  uint8_t  count() { return _count; };
  uint8_t  size()  { return _size; };
  uint8_t  free()  { return _size - _count; };


  //  CORE
  virtual size_t write(uint8_t c) override;
  virtual size_t write(const uint8_t * buffer, size_t size) override;
  //  see issue #13
  virtual void flush() override;


  //  ENABLE
  //  returns true on success, false otherwise.
  bool     enable(uint8_t index);
  bool     disable(uint8_t index);
  bool     isEnabled(uint8_t index);
  bool     isEnabledAny();
  bool     enableStream(Print * stream);
  bool     disableStream(Print * stream);
  bool     isEnabledStream(Print * stream);


  //  DIAGNOSTIC
  void     resetOutputCount() { _outputCount = 0; };
  uint32_t getOutputCount()   { return _outputCount; };


private:
  Print *  _stream[MAX_MULTIPLEX];
  bool     _enabled[MAX_MULTIPLEX];
  //  bool    _free[MAX_MULTIPLEX];

  uint8_t  _count;
  uint8_t  _size;
  uint32_t _outputCount;
};


//  -- END OF FILE --

