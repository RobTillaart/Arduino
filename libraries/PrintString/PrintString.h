#pragma once
//
//    FILE: PrintString.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Class that captures prints into a String 
//    DATE: 2017-12-09
//     URL: https://github.com/RobTillaart/PrintString
//
//  0.1.0   2017-12-09  initial version
//  0.1.1   2020-04-26  added size
//  0.1.2   2020-06-19  fix library.json
//  0.2.0   2021-01-06  add Arduino-CI + unit test


#include "Arduino.h"
#include "Print.h"


#define PRINTSTRING_VERSION       (F("0.2.0"))


class PrintString: public Print
{
public:
  PrintString() {};
  
  size_t write(uint8_t c)
  {
    buffer.concat(char(c));
    return 1;
  }
  
  size_t size()
  {
    return buffer.length();
  }
  
  void clear()
  {
    buffer = "";
  }
 
  String getString() { return buffer; }

private:
  String buffer;
};

// -- END OF FILE --
