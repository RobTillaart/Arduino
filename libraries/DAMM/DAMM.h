#pragma once
//
//    FILE: DAMM.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-00-00
// VERSION: 0.2.0
// PURPOSE: Arduino library for calculating DAMM checksum.
//     URL: https://github.com/RobTillaart/DAMM
//     URL: https://en.wikipedia.org/wiki/Damm_algorithm
//


#include "Arduino.h"


#define DAMM_LIB_VERSION         (F("0.1.0"))

class DAMM
{
public:
  DAMM()
  {
    _value = 0;
    _count = 0;
  }


  //////////////////////////////////////////////////////////////
  //
  //  NORMAL INTERFACE
  //
  bool isValid(const char * buffer)
  {
    return isValid((char*)buffer);
  }

  bool isValid(char * buffer)
  {
    _value = 0;
    int len = strlen(buffer);
    for (int i = 0; i < len; i++)
    {
      add(buffer[i] - '0');
    }
    return (_value == 0);
  }

  char generateChecksum(const char * buffer)
  {
    return generateChecksum((char *) buffer);
  }

  char generateChecksum(char * buffer)
  {
    _value = 0;
    uint32_t len = strlen(buffer);
    for (uint32_t i = 0; i < len; i++)
    {
      add(buffer[i] - '0');
    }
    return (_value + '0');
  }


  //////////////////////////////////////////////////////////////
  //
  //  STREAM INTERFACE
  //
  char reset()
  {
    int val = _value;
    _value = 0;
    _count = 0;
    return val + '0';
  }

  //  for digits
  char add(int x)
  {
    _count++;
    _value = _dammMatrix[_value][x];
    return _value + '0';
  }

  //  for digits as char '0'..'9'
  char add(char c)
  {
    return add(c - '0');
  }

  uint32_t count()
  {
    return _count;
  }


protected:
  int       _value = 0;
  uint32_t  _count = 0;

  //  FAST MATRIX
  uint8_t _dammMatrix[10][10] =
  {
    {0, 3, 1, 7, 5, 9, 8, 6, 4, 2},
    {7, 0, 9, 2, 1, 5, 4, 8, 6, 3},
    {4, 2, 0, 6, 8, 7, 1, 3, 5, 9},
    {1, 7, 5, 0, 9, 8, 3, 4, 2, 6},
    {6, 1, 2, 3, 0, 4, 5, 9, 7, 8},
    {3, 6, 7, 4, 2, 0, 9, 5, 8, 1},
    {5, 8, 6, 9, 7, 2, 0, 1, 3, 4},
    {8, 9, 4, 5, 3, 6, 2, 0, 1, 7},
    {9, 4, 3, 8, 6, 1, 7, 2, 0, 5},
    {2, 5, 8, 1, 4, 3, 6, 7, 9, 0}
  };

};


//////////////////////////////////////////
//
//  ALTERNATIVE CLASS (experimental)
//
//  less RAM version - slower
//
class DAMM_small
{
public:
  DAMM_small()
  {
    _value = 0;
    _count = 0;
  }

  //////////////////////////////////////////////////////////////
  //
  //  NORMAL INTERFACE
  //
  bool isValid(const char * buffer)
  {
    return isValid((char*)buffer);
  }

  bool isValid(char * buffer)
  {
    _value = 0;
    int len = strlen(buffer);
    for (int i = 0; i < len; i++)
    {
      add(buffer[i] - '0');
    }
    return (_value == 0);
  }

  char generateChecksum(const char * buffer)
  {
    return generateChecksum((char *) buffer);
  }

  char generateChecksum(char * buffer)
  {
    _value = 0;
    uint32_t len = strlen(buffer);
    for (uint32_t i = 0; i < len; i++)
    {
      add(buffer[i] - '0');
    }
    return (_value + '0');
  }


  //////////////////////////////////////////////////////////////
  //
  //  STREAM INTERFACE
  //
  char reset()
  {
    int val = _value;
    _value = 0;
    _count = 0;
    return val + '0';
  }

  //  for digits
  char add(int x)
  {
    _count++;
    _value = _dammMatrix_small[_value][x/2];
    _value = (x & 1) ? _value & 0x0F : _value >> 4;
    return _value + '0';
  }

  //  for digits as char '0'..'9'
  char add(char c)
  {
    return add(c - '0');
  }

  uint32_t count()
  {
    return _count;
  }


protected:
  int       _value = 0;
  uint32_t  _count = 0;


  //  SMALL MATRIX
  uint8_t _dammMatrix_small[10][5] =
  {
    {0x03, 0x17, 0x59, 0x86, 0x42},
    {0x70, 0x92, 0x15, 0x48, 0x63},
    {0x42, 0x06, 0x87, 0x13, 0x59},
    {0x17, 0x50, 0x98, 0x34, 0x26},
    {0x61, 0x23, 0x04, 0x59, 0x78},
    {0x36, 0x74, 0x20, 0x95, 0x81},
    {0x58, 0x69, 0x72, 0x01, 0x34},
    {0x89, 0x45, 0x36, 0x20, 0x17},
    {0x94, 0x38, 0x61, 0x72, 0x05},
    {0x25, 0x81, 0x43, 0x67, 0x90}
  };
};


//  -- END OF FILE --

