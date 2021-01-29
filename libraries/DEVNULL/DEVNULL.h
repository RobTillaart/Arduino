#pragma once
//
//    FILE: DEVNULL.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for a /dev/null stream - usefull for testing
//     URL: https://github.com/RobTillaart/DEVNULL
//
// HISTORY:
// 0.1.0    2020-06-23  initial version
// 0.1.1    2020-12-18  add arduino-ci + 

#include "Arduino.h"

class DEVNULL : public Stream
{
public:
  DEVNULL() {};

  int    available() { return 0; };
  int    peek()      { return EOF; };
  int    read()      { return EOF; };
  void   flush()     { return; };  // placeholder to keep CI happy
  size_t write(const uint8_t data) { _bottomLessPit = data; return 1; };

private:
  uint8_t  _bottomLessPit;
};

// -- END OF FILE --
