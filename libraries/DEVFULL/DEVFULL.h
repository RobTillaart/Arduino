#pragma once
//
//    FILE: DEVFULL.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for a /dev/full stream - useful for testing / debugging.
//     URL: https://github.com/RobTillaart/DEVFULL
//
// HISTORY:
//  0.1.0   2022-03-11  initial version.



#include "Arduino.h"

#define DEVFULL_LIB_VERSION     (F("0.1.0"))

#ifndef ENOSPC
#define ENOSPC        -28
#endif


class DEVFULL : public Stream
{
public:
  DEVFULL()
  {
    setTimeout(0);     // no timeout.
  };

  int  available() { return 32767; };
  int  peek()      { return 0; };
  int  read()      { return 0; };
  void flush()     { return; };   // placeholder to keep CI happy

  size_t write(const uint8_t data)
  {
    dummy = data;                 // keep compiler happy
    return -28;
  };
  size_t write( const uint8_t *buffer, size_t size) 
  {
    dummy = buffer[size-1];       // keep compiler happy
    return -28;
  };


private:
  uint8_t dummy;
};


// -- END OF FILE --

