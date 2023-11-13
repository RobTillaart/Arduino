#pragma once
//
//    FILE: Multiplex.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.7
// PURPOSE: Arduino library to multiplex streams
//    DATE: 2021-01-09
//     URL: https://github.com/RobTillaart/Multiplex


#include "Arduino.h"


#define MULTIPLEX_LIB_VERSION         (F("0.2.7"))


//  MAX 254 (in theory) as 0xFF is a special value
#ifndef MAX_MULTIPLEX
#define MAX_MULTIPLEX                 4
#endif


class Multiplex: public Print
{
public:
  Multiplex();
  ~Multiplex();


  //  CORE
  virtual size_t write(uint8_t c) override;
  virtual size_t write(const uint8_t * buffer, size_t size) override;

  bool     add(Print * stream);  //  returns true on success
  void     reset();

  //  remove
  //  use with care as it changes the indices.
  bool     remove(Print * stream);
  bool     remove(uint8_t index);

  //  see issue #13
  virtual void flush() override;

  //  CONTROL
  uint8_t  count() { return _count; };
  uint8_t  size()  { return _size; };
  uint8_t  free()  { return _size - _count; };

  //  returns true on success, false otherwise.
  bool     enable(uint8_t index);
  bool     enableStream(Print * stream);
  bool     disable(uint8_t index);
  bool     disableStream(Print * stream);

  bool     isEnabled(uint8_t index);
  bool     isEnabledStream(Print * stream);

  uint8_t  index(Print *stream);
  Print *  stream(uint8_t index);

  bool     isEnabledAny();


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

