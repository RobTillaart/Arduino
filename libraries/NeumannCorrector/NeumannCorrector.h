#pragma once
//
//    FILE: NeumannCorrector.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-11-23
// VERSION: 0.1.2
// PURPOSE: Arduino library for a NeumannCorrector. (randomizing streams of bits).
//     URL: https://github.com/RobTillaart/NeumannCorrector


//  Experimental code.


#include "Arduino.h"

#define NEUMANNCORRECTOR_LIB_VERSION         (F("0.1.2"))

#ifndef NEUMANNCORRECTOR_MAX_SIZE
#define NEUMANNCORRECTOR_MAX_SIZE            32
#endif


class NeumannCorrector
{
public:
  explicit NeumannCorrector()
  {
    clear();
  }

  void clear()
  {
    _count = 0;
    _bits = 0;
  }

  uint8_t available()
  {
    return _count;
  }

  uint8_t size()
  {
    return _size;
  }

  void add(uint8_t in)
  {
    static uint8_t buffer = 0;
    static uint8_t bufferSize = 0;
    int count = 0;
    //  process 8 bits.
    while (count < 8)
    {
      count++;
      //  add one bit to buffer
      buffer <<= 1;
      buffer |= (in & 0x01);
      buffer &= 0x03;
      in >>= 1;
      bufferSize++;

      //  if buffer contains 2 bits analyse them
      if (bufferSize == 2)
      {
        if (buffer == 0b01)
        {
          _bits <<= 1;
          // _bits add 0.
          bufferSize--;
          _count++;
        }
        else if (buffer == 0b10)
        {
          _bits <<= 1;
          _bits |= 1;
          bufferSize--;
          _count++;
        }
        else  //  ignore both;
        {
          bufferSize = 0;
        }
      }
    }
    if (_count > 32)
    {
      _count = 32;
    }
  }

  uint8_t get()
  {
    uint8_t value = _bits & 0xFF;
    _bits >>= 8;
    _count -= 8;
    if (_count < 0)
    {
      _count = 0;
    }
    return value;
  }

  uint16_t get16()
  {
    uint16_t value = _bits & 0xFFFF;
    _bits >>= 16;
    _count -= 16;
    if (_count < 0)
    {
      _count = 0;
    }
    return value;
  }

  uint32_t get32()
  {
    uint32_t value = _bits;
    _bits  = 0;
    _count = 0;
    return value;
  }


private:
  uint8_t  _size  = 32;
  int      _count = 0;
  uint32_t _bits  = 0;
};


//  -- END OF FILE --

