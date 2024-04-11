#pragma once
//
//    FILE: PrintSize.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.5
// PURPOSE: Library to determine size of a printed variable.
//    DATE: 2017-12-09
//     URL: https://github.com/RobTillaart/PrintSize


#include "Arduino.h"
#include "Print.h"

#define PRINTSIZE_VERSION     (F("0.3.5"))


class PrintSize: public Print
{
public:
  PrintSize()
  {
    reset();
  };


  size_t write(uint8_t c)                     //  note: warning unused parameter
  {
    _total++;
    return sizeof(c);
  }


  size_t write(uint8_t * str, uint8_t length)  //  note: warning unused parameter
  {
    _total += length;
    return length;
  }


  void reset()
  {
    _total = 0;
  }


  uint32_t total()
  {
    return _total;
  }


private:
  uint32_t _total = 0;

};


//  -- END OF FILE --

