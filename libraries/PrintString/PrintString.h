#pragma once
//
//    FILE: PrintString.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: Class that captures prints into a String 
//    DATE: 2017-12-09
//     URL: https://github.com/RobTillaart/PrintString
//
//  0.1.0   2017-12-09  initial version
//  0.1.1   2020-04-26  added size
//  0.1.2   2020-06-19  fix library.json
//  0.2.0   2021-01-06  add Arduino-CI + unit test
//  0.2.1   2021-11-14  update Arduino-CI, readme.md
//                      add write(char * str, uint8_t length) Print interface.
//  0.2.2   2021-12-24  update library.json, license, minor edits


#include "Arduino.h"
#include "Print.h"


#define PRINTSTRING_VERSION       (F("0.2.2"))


class PrintString: public Print
{
public:
  PrintString() {};


  size_t write(uint8_t c)
  {
    buffer.concat(char(c));
    return 1;
  }


  size_t write(uint8_t * str, uint8_t length)
  {
    buffer.concat((char*)str);
    return length;
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

