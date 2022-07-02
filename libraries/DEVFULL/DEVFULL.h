#pragma once
//
//    FILE: DEVFULL.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for a /dev/full stream - useful for testing / debugging.
//     URL: https://github.com/RobTillaart/DEVFULL
//
// HISTORY:
//  0.1.0   2022-03-11  initial version.
//  0.1.1   2022-07-01  add limits.h INT_MAX to support 32 bit int.



#include "Arduino.h"
#include "limits.h"


#define DEVFULL_LIB_VERSION     (F("0.1.1"))


#ifndef ENOSPC
#define ENOSPC        -28
#endif


#ifndef INT_MAX
#define INT_MAX 32767
#endif


class DEVFULL : public Stream
{
public:
  DEVFULL()
  {
    setTimeout(0);     // no timeout.
  };

  int  available() { return INT_MAX; };
  int  peek()      { return 0; };
  int  read()      { return 0; };
  void flush()     { return; };   // placeholder to keep build CI happy

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

