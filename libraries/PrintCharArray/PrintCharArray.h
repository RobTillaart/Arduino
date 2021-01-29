#pragma once
//
//    FILE: PrintCharArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Class that captures prints into a char array
//    DATE: 2017-12-07
//     URL: https://github.com/RobTillaart/PrintCharArray
//
//  0.1.0   2017-12-07  initial version
//  0.1.1   2020-04-28  minor optimization
//  0.2.0   2020-04-30  dynamic memory
//  0.2.1   2020-06-19  fix library.json
//  0.3.0   2021-01-06  Arduino-CI + unit test, free -> available()


#include "Print.h"


#define PRINTCHARARRAY_VERSION            (F("0.3.0"))

#define PRINTCHARARRAY_MAX_BUFFER_SIZE    250


class PrintCharArray: public Print
{
public:
  PrintCharArray(uint8_t size = 100)
  {
    _bufSize = constrain(size, 20, PRINTCHARARRAY_MAX_BUFFER_SIZE);
    _buffer = (char *) malloc(_bufSize);
  };

  ~PrintCharArray()
  {
    if (_buffer) free(_buffer);
  };

  size_t write(uint8_t c)
  {
    if (_index < _bufSize - 1)
    {
      _buffer[_index++] = c;
      return 1;
    }
    return 0;
  }

  void clear()
  {
    _index = 0;
  }

  int available()
  { 
    return (_bufSize - _index);
  }

  // int length() { return _index; };   // better as size()?
  int size()
  { 
    return _index;
  }

  int bufSize()
  {
    return _bufSize;
  }

  char * getBuffer() 
  {
    _buffer[_index] = '\0';
    return _buffer; 
  }

private:
  char*   _buffer;
  uint8_t _bufSize = 0;
  uint8_t _index   = 0;
};

// -- END OF FILE --
