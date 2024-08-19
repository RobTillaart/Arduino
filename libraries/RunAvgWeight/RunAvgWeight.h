#pragma once
//
//    FILE: RunAvgWeight.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2024-06-30
// PURPOSE: Arduino library to calculate the running average with weights by means of a circular buffer
//     URL: https://github.com/RobTillaart/RunAvgWeight
//
//  based upon: https://github.com/RobTillaart/RunningAverage


#include "Arduino.h"


#define RUNAVGWEIGHT_LIB_VERSION          (F("0.2.0"))


class RunAvgWeight
{
public:
  explicit RunAvgWeight(const uint16_t size);
  ~RunAvgWeight();

  bool     clear();
  bool     addValue(const float value, const float weight = 1.0);
  float    getValue(const uint16_t position);
  float    getWeight(const uint16_t position);

  //  getAverage() iterates over all elements.
  float    getAverage();
  //  getFastAverage() reuses previous calculated values.
  float    getFastAverage();

  //  return statistical characteristics of the running average.
  //  TODO: investigate correctness of these two functions.
  //        weight == 1
  //        weight <> 1
  float    getStandardDeviation();
  float    getStandardError();
  float    getCoefficientOfVariation();

  //  returns min/max added to the data-set since last clear.
  //  values without weight!
  float    getMin() { return _min; };
  float    getMax() { return _max; };

  //  returns min/max from the values in the internal buffer.
  //  values without weight!
  float    getMinInBuffer();
  float    getMaxInBuffer();

  //  return true if buffer is full
  bool     bufferIsFull() { return _count == _size; };
  uint16_t getSize() { return _size; }
  uint16_t getCount() { return _count; }


  //  helper functions.
  float    getElementValue(const uint16_t index);
  float    getElementWeight(const uint16_t index);
  float    getSumValues()  { return _sumValues; };
  float    getSumWeights() { return _sumWeights; };


protected:
  uint16_t _size;
  uint16_t _count;
  uint16_t _index;

  float *  _values;
  float *  _weights;
  float    _sumValues;
  float    _sumWeights;
  float    _min;
  float    _max;
};


//  -- END OF FILE --

