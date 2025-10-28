#pragma once
//
//    FILE: RLCBuffer.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-10-26
// VERSION: 0.1.0
// PURPOSE: Arduino library for a Run Length Compressed circular buffer.
//     URL: https://github.com/RobTillaart/RLCBuffer
//


#include "Arduino.h"


#define RLCBUFFER_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
#define RLCBUFFER_OK                  (0x00)
//  TODO
#define RLCBUFFER_ERR_ALLOC           (0xFF)



class RLCBuffer
{
public:
  RLCBuffer(uint32_t size)
  {
    _size = size;
    if (_size < 4) _size = 4;
    //  allocate dynamic buffer
    _data = (uint32_t *) malloc(_size * 4);
    _cnt  = (uint32_t *) malloc(_size * 4);
  }

  ~RLCBuffer()
  {
    if (_data != NULL) free(_data);
    if (_cnt != NULL) free(_cnt);
  }

  bool begin()
  {
    if ((_data == NULL) || (_cnt == NULL))
    {
      free(_data);
      free(_cnt);
      return false;
    }

    _index = 0;
    _count = 0;
    _lastData = 0;
    memset(_cnt, 0, _size * 4);
    memset(_data, 0, _size * 4);
    return true;
  }

  void writeData(uint32_t data)
  {
    //  do we have same data?
    if (data == _lastData)
    {
      _cnt[_index]++;
      return;
    }
    _lastData = data;
    //  buffer the new data in next free slot.
    //  TODO handle circular here
    _index++;
    if (_index >= _size) _index = 0;
    _data[_index] = data;
    _cnt[_index] = 1;
    if (_count < _size) _count++;
  }

  uint32_t readData(uint32_t index)
  {
    //  no check on index
    return _data[index];
  }

  uint32_t readCount(uint32_t index)
  {
    //  no check on index
    return _cnt[index];
  }


  //  META INFO
  uint32_t size() 
  {
    return _size;
  }

  uint32_t count()
  {
    return _count;
  }

  uint32_t index()
  {
    return _index;
  }

  bool empty()
  {
    return (_count == 0);
  }

  bool full()
  {
    return (_count == _size);
  }

  uint32_t available()
  {
    return (_size - _count);
  }


private:
  uint32_t * _data  = NULL;
  uint32_t * _cnt   = NULL;
  uint32_t _size    = 0;
  uint32_t _index   = 0;
  uint32_t _count   = 0;
  uint32_t _lastData  = 0;
  //  int      _error = RLCBUFFER_OK;
};



//  -- END OF FILE --





