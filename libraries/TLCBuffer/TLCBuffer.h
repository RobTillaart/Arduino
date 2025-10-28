#pragma once
//
//    FILE: TLCBuffer.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-10-26
// VERSION: 0.1.0
// PURPOSE: Arduino library for a Time Length Compressed buffer.
//     URL: https://github.com/RobTillaart/TLCBuffer
//


#include "Arduino.h"


#define TLCBUFFER_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
#define TLCBUFFER_OK                  (0x00)
//  TODO
#define TLCBUFFER_ERR_ALLOC           (0xFF)
#define TLCBUFFER_ERR_TIMEUNIT        (0xFE)


class TLCBuffer
{
public:
  TLCBuffer(uint32_t size)
  {
    _size = size;
    if (_size < 4) _size = 4;
    //  allocate dynamic buffer
    _data = (uint32_t *) malloc(_size * 4);
    _time = (uint32_t *) malloc(_size * 4);
  }

  ~TLCBuffer()
  {
    if (_data != NULL) free(_data);
    if (_time != NULL) free(_time);
  }

  //  time units
  //  u = micros  m = Millis s = seconds
  //  t = Tenths of a second h = Hundreds of a second
  bool begin(char timeUnits = 'm')
  {
    if ((_data == NULL) || (_time == NULL))
    {
      free(_data);
      free(_time);
      return false;
    }

    _index = 0;
    _count = 0;
    _timeUnits = timeUnits;
    _lastTime = 0;
    _lastData = 0;
    memset(_time, 0, _size * 4);
    memset(_data, 0, _size * 4);
    return true;
  }

  void writeData(uint32_t data)
  {
    //  update duration of last data first.
    uint32_t now = getTime();
    _time[_index] += (now - _lastTime);
    _lastTime = now;
    //  do we have a new data?
    if (data == _lastData)
    {
      return;
    }
    _lastData = data;
    //  buffer the new data in next free slot.
    //  TODO handle circular here
    _index++;
    if (_index >= _size) _index = 0;
    _data[_index] = data;
    _time[_index] = 0;
    if (_count < _size) _count++;
  }

  uint32_t readData(uint32_t index)
  {
    //  no check on index
    return _data[index];
  }

  uint32_t readDuration(uint32_t index)
  {
    //  no check on index
    return _time[index];
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

  char getTimeUnit()
  {
    return _timeUnits;
  }


private:
  uint32_t * _data  = NULL;
  uint32_t * _time  = NULL;
  uint32_t _size    = 0;
  uint32_t _index   = 0;
  uint32_t _count   = 0;
  char     _timeUnits = 'm';
  uint32_t _lastTime  = 0;
  uint32_t _lastData  = 0;
  //  int      _error = TLCBUFFER_OK;

  uint32_t getTime()
  {
    if (_timeUnits == 'm') return millis();
    if (_timeUnits == 'u') return micros();
    if (_timeUnits == 's') return millis() / 1000;
    if (_timeUnits == 'h') return millis() / 10;
    if (_timeUnits == 't') return millis() / 100;
    //  default.
    return millis();
  }
};



//  -- END OF FILE --





