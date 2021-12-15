#pragma once
//
//    FILE: DEVNULL.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library for a /dev/null stream - useful for testing
//     URL: https://github.com/RobTillaart/DEVNULL
//
// HISTORY:
//  0.1.0   2020-06-23  initial version.
//  0.1.1   2020-12-18  add Arduino-CI.
//  0.1.2   2021-11-24  update build-CI, badges, etc.
//                      added write(data, length) + _timeOut.
//  0.1.3   2021-12-15  update library.json, license, minor edits


#include "Arduino.h"

#define DEVNULL_LIB_VERSION     (F("0.1.3"))


class DEVNULL : public Stream
{
public:
  DEVNULL()
  {
    setTimeout(0);     // no timeout.
  };

  int    available() { return 0; };
  int    peek()      { return EOF; };
  int    read()      { return EOF; };
  void   flush()     { return; };  // placeholder to keep CI happy

  size_t write(const uint8_t data)
  {
    _bottomLessPit = data;
    return 1;
  };
  size_t write( const uint8_t *buffer, size_t size) 
  {
    if (size > 0) _bottomLessPit = buffer[size - 1];
    return size;
  };


private:
  uint8_t  _bottomLessPit;
};


// -- END OF FILE --

