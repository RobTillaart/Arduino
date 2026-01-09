#pragma once
//
//    FILE: TLCBuffer.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-10-26
// VERSION: 0.2.0
// PURPOSE: Arduino library for a Time Length Compressed buffer.
//     URL: https://github.com/RobTillaart/TLCBuffer
//


#include "Arduino.h"


#define TLCBUFFER_LIB_VERSION         (F("0.2.0"))

//  ERROR CODES
//  values <> 0 are errors.
#define TLCBUFFER_OK                  (0x00)
#define TLCBUFFER_ERR_ALLOC           (0xFF)


//  TLCBuffer<uint8_t, uint8_t> TLCB(20);  //  minimize RAM usage
template<typename T_DATA = uint32_t, typename T_TIME = uint32_t>
class TLCBuffer
{
public:
  TLCBuffer(uint32_t size)
  {
    _size = size;
    if (_size < 4) _size = 4;
    //  allocate dynamic buffer
    _data = (T_DATA *) malloc(_size * sizeof(T_DATA));
    _time = (T_TIME *) malloc(_size * sizeof(T_TIME));
  }

  ~TLCBuffer()
  {
    free(_data);
    free(_time);
  }

  //  time units
  //  u = micros  m = Millis s = seconds
  //  t = Tenths of a second h = Hundreds of a second
  bool begin(char timeUnits = 'm')
  {
    if ((_data == NULL) || (_time == NULL))
    {
      //  _error = TLCBUFFER_ERR_ALLOC;
      free(_data);
      free(_time);
      return false;
    }

    _index = (_size - 1);
    _count = 0;
    _timeUnits = timeUnits;
    memset(&_lastTime, 0, sizeof(T_TIME));
    memset(&_lastData, 0, sizeof(T_DATA));
    memset(_time, 0, _size * sizeof(T_TIME));
    memset(_data, 0, _size * sizeof(T_DATA));
    return true;
  }


  //  READ WRITE
  void writeData(T_DATA data)
  {
    //  update duration of last data first.
    T_TIME now = getTime();
    _time[_index] += (T_TIME)(now - _lastTime);
    _lastTime = now;
    //  do we have a new data?
    if (memcmp(&_lastData, &data, sizeof(T_DATA)) == 0)
    {
      return;
    }
    memcpy(&_lastData, &data, sizeof(T_DATA));
    //  buffer the new data in next free slot.
    _index++;
    //  TODO handle circular here
    if (_index >= _size) _index = 0;
    memcpy(&_data[_index], &data, sizeof(T_DATA));
    _time[_index] = 0;
    if (_count < _size) _count++;
  }

  T_DATA readData(uint32_t index)
  {
    //  wrap index
    if (index >= _size) index %= _size;
    return _data[index];
  }

  T_TIME readDuration(uint32_t index)
  {
    //  wrap index
    if (index >= _size) index %= _size;
    return _time[index];
  }


  //  META INFO
  uint32_t size()      { return _size; }
  uint32_t count()     { return _count; }
  uint32_t index()     { return _index; }
  bool empty()         { return (_count == 0); }
  bool full()          { return (_count == _size); }
  uint32_t available() { return (_size - _count); }
  char getTimeUnit()   { return _timeUnits; }


private:
  //  dynamic memory to hold data & duration
  T_DATA * _data   = NULL;
  T_TIME * _time   = NULL;
  T_DATA _lastData;
  T_TIME _lastTime;

  uint32_t _size   = 0;
  uint32_t _index  = 0;
  uint32_t _count  = 0;
  char     _timeUnits = 'm';

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





