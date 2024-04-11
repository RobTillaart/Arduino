#pragma once
//
//    FILE: PrintString.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.5
// PURPOSE: Class that captures prints into a String
//    DATE: 2017-12-09
//     URL: https://github.com/RobTillaart/PrintString


#include "Arduino.h"
#include "Print.h"


#define PRINTSTRING_VERSION       (F("0.2.5"))


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


  String getString()
  {
    return buffer;
  }


private:
  String buffer;
};


//  -- END OF FILE --

