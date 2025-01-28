#pragma once
//
//    FILE: AD7367.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-01-10
// PURPOSE: Arduino library for the AD7367, 2 channel simultaneous sampling 14 bit ADC.
//          Also AD7366 == 12 bits.


#include "Arduino.h"

#define AD7367_LIB_VERSION        (F("0.1.0"))


class AD7367
{
public:
  //  CONSTRUCTOR
  //  pins to set.
  AD7367(uint8_t select, uint8_t clock, uint8_t convert, uint8_t busy, uint8_t data0, uint8_t data1);

  void     begin();
  uint8_t  getType();  //  returns 66 or 67
  int      getBits();  //  returns 12 or 14

  //  READ
  int      read();
  //  READ ASYNC
  void     triggerConversion();
  bool     conversionBusy();
  bool     conversionReady();
  int      readAsync();
  //  GET VALUE
  int      getValue(uint8_t channel);  //  channel = 0 or 1


protected:
  uint8_t  _type;
  uint8_t  _bits;
  uint8_t  _select;
  uint8_t  _clock;
  uint8_t  _convert;
  uint8_t  _busy;
  uint8_t  _data0;
  uint8_t  _data1;
  int16_t  _value[2] = {0, 0};
};



/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS AD7366
//
class AD7366 : public AD7367
{
public:
  AD7366(uint8_t select, uint8_t clock, uint8_t convert, uint8_t busy, uint8_t data0, uint8_t data1);
};


//  -- END OF FILE --

