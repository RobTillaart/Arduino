#pragma once
//
//    FILE: PrintSize.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: Class that determines printSize
//    DATE: 2017-12-09
//     URL: https://github.com/RobTillaart/PrintSize
//
//  HISTORY:
//  0.1.0   2017-12-09  initial version
//  0.2.0   2020-04-30  add total counter to sum multiple print statements
//  0.2.1   2020-05-26  fix #1 - URLS + centering example
//  0.2.2   2020-06-19  fix library.json
//  0.3.0   2021-01-06  Arduino-CI + unit test
//  0.3.1   2021-11-13  update Arduino-CI, readme.md, badges
//                      add write(str, length) for Print interface.
//


#include "Print.h"

#define PRINTSIZE_VERSION     (F("0.3.1"))


class PrintSize: public Print
{
public:
  PrintSize()
  {
    reset();
  };



  size_t write(uint8_t c)  // note: warning unused parameter
  {
    _total++;
    return 1;
  }


  size_t write(uint8_t * str, uint8_t length)  // note: warning unused parameter
  {
    _total += length;
    return length;
  }


  void     reset() { _total = 0; }


  uint32_t total() { return _total; };


private:
  uint32_t _total = 0;

};

// -- END OF FILE --
