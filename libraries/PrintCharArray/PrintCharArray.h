#pragma once
//
//    FILE: PrintCharArray.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Class that captures prints into a char array
//    DATE: 2017-12-07
//     URL: https://github.com/RobTillaart/PrintCharArray
//
// 0.1.0    2017-12-07 initial version
// 0.1.1    2020-04-28 minor optimization
// 0.2.0    2020-04-30 dynamic memory
// 0.2.1    2020-06-19 fix library.json

#include "Print.h"

#define PRINTCHARARRAY_VERSION "0.2.1"

class PrintCharArray: public Print
{
  public:
    PrintCharArray(uint8_t size = 100)
	{
      _bufSize = constrain(size, 20, 250);
	  _buffer = (char *) malloc(_bufSize);
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

    int free() { return (_bufSize - _index); }

    int size() { return _index; }

    char * getBuffer() 
	{
      _buffer[_index] = '\0';
	  return _buffer; 
	}

  private:
    char*   _buffer;
	uint8_t _bufSize = 0;
    uint8_t _index = 0;
};

// -- END OF FILE --
