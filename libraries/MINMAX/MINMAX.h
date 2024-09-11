#pragma once
//
//    FILE: MINMAX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2021-10-14
// PURPOSE: MINMAX library - simple peak finder
//     URL: https://github.com/RobTillaart/MINMAX


#include "Arduino.h"

#define MINMAX_LIB_VERSION                  (F("0.3.0"))

#define MINMAX_NO_CHANGE                    0X00
#define MINMAX_MIN_CHANGED                  0X01
#define MINMAX_MAX_CHANGED                  0X02
#define MINMAX_RESET_DONE                   0X80


class MINMAX
{
public:

  MINMAX();

  uint8_t  add(const float value);
  void     reset();
  //  the reset defaults are both zero.
  void     setResetDefaults(float minimum, float maximum);

  //  call back function when there is a change
  void     addCallBack( void (* func)(void) );

  //  set the auto reset at certain count
  //  count == 0 implies no auto reset.
  void     setAutoResetCount(uint32_t count);
  uint32_t getAutoResetCount();

  //  last value added
  float    lastValue();

  //  number of elements added.
  uint32_t count();

  //  peak values so far.
  float    minimum();
  float    maximum();

  //  timestamp of the last minimum and maximum change in milliseconds since start.
  uint32_t lastMin();
  uint32_t lastMax();

  //  in/decrease MIN and MAX - linear - with this value if possible.
  void     setDampening(const float value);
  float    getDampening();


private:
  float    _lastValue;

  float    _minimum;
  float    _maximum;
  float    _minimumDefault;
  float    _maximumDefault;
  float    _dampening;

  uint32_t _count;
  uint32_t _resetCount;
  void     (* _callback)(void);

  uint32_t _lastMin;
  uint32_t _lastMax;
};


//  -- END OF FILE --

