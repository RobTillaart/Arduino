#pragma once
//
//    FILE: Student.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for Student or T-distribution math.
//    DATE: 2024-07-22


#include "Arduino.h"
#include "StudentTable.h"

#define STUDENT_LIB_VERSION       (F("0.1.0"))


class Student
{
public:
  Student()
  {
    _size = STUDENT_MAX_SIZE;
    _count = 0;
  }

  uint8_t getSize()
  {
    return _size;
  }

  uint8_t getCount()
  {
    return _count;
  }

  void reset()
  {
    _count = 0;
  }

  //
  //  ADD
  //
  bool add(float value)
  {
    if (_count >= _size) return false;
    _value[_count++] = value;
    return true;
  }

  bool add(float *array, uint8_t size)
  {
    if (_count + size > _size) return false;
    for (int i = 0; i < size; i++)
    {
      add(array[i]);
    }
    return true;
  }

  //
  //  MATH
  //
  float mean()
  {
    float sum = 0;
    for (int i = 0; i < _count; i++)
    {
      sum += _value[i];
    }
    return sum / _count;
  }

  float variance()
  {
    if (_count < 2) return NAN;
    float m = mean();
    float var = 0;
    for (int i = 0; i < _count; i++)
    {
      var += (_value[i] - m)*(_value[i] - m);
    }
    var /= (_count - 1);
    return var;
  }

  float deviation()
  {
    if (_count < 2) return NAN;
    float var = variance();
    return sqrt(var);
  }

  float estimatedDeviation()
  {
    if (_count < 2) return NAN;
    float dev = deviation();
    return dev / sqrt(_count);
  }

  //
  //  INTERVAL
  //

  float intervalDelta(int confidence)
  {
    if (_count < 2) return NAN;
    //  degrees freedom
    int df = _count - 1;
    int idx = 2;  //  95% default
    if (confidence == 80) idx = 0;
    if (confidence == 90) idx = 1;
    if (confidence == 98) idx = 3;
    if (confidence == 99) idx = 4;

    //  interpolation possible
    float t = StudentLUT[df][idx] * 0.001;
    return estimatedDeviation() * t;
  }

  float meanLower(int confidence)
  {
    return mean() - intervalDelta(confidence);
  }

  float meanUpper(int confidence)
  {
    return mean() + intervalDelta(confidence);
  }


private:

  uint8_t _size;
  uint8_t _count;
  float   _mean = 0;
  float   _value[STUDENT_MAX_SIZE];

};


//  -- END OF FILE --

