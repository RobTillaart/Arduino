#pragma once
//
//    FILE: Multiplex.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library to multiplex streams 
//    DATE: 2021-01-09
//     URL: https://github.com/RobTillaart/Multiplex


#include "Arduino.h"
#include "Print.h"


#define MULTIPLEX_LIB_VERSION      (F("0.1.0"))


const uint8_t MAX_MULTIPLEX = 4;


class Multiplex: public Print
{
public:
  Multiplex();
  
  // CORE
  size_t  write(uint8_t c);
  bool    add(Print * stream);  // returns true on success
  void    reset();

  // CONTROL
  uint8_t count()       { return _count; };
  uint8_t size()        { return _size; };
  void    enable(uint8_t index);
  void    disable(uint8_t index);
  bool    isEnabled(uint8_t index);

private:
  Print * _stream[MAX_MULTIPLEX];
  bool    _enabled[MAX_MULTIPLEX];  // bitmask max 4 ...
  uint8_t _count;
  uint8_t _size;
};

// -- END OF FILE --
