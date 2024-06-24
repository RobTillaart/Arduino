#pragma once
//
//    FILE: rotaryDecoder.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2021-05-08
// PURPOSE: Arduino library for rotary decoder
//     URL: https://github.com/RobTillaart/rotaryDecoder


#include "Arduino.h"
#include "Wire.h"

#define ROTARY_DECODER_LIB_VERSION         (F("0.3.1"))


class rotaryDecoder
{
public:
  explicit rotaryDecoder(const int8_t address, TwoWire *wire = &Wire);

  bool    begin(uint8_t count = 4);
  bool    isConnected();

  uint8_t readInitialState();

  //  for polling version,
  //  checkChange is bit faster than a call to update
  //  so useful if there are only a few updates
  bool    checkChange();

  //  read and update the counters
  bool    update();         //  assumes two directions   => +1 and -1
  bool    updateSingle();   //  assumes single direction => + ++ +++

  //  re = rotary encoder
  //  returns 0, false if re > 3.
  int32_t getValue(uint8_t re);
  bool    setValue(uint8_t re, int32_t value = 0);


  //  READ - WRITE interface
  uint8_t read1(uint8_t pin);
  bool    write1(uint8_t pin, uint8_t value);
  uint8_t read8();
  bool    write8(uint8_t value);


  //  DEBUG
  uint8_t getLastPosition(uint8_t re);


protected:
  uint8_t   _count = 0;
  uint8_t   _lastValue = 0;
  uint8_t   _lastPos[4] = { 0, 0, 0, 0 };
  int32_t   _encoder[4] = { 0, 0, 0, 0 };

  uint8_t   _address;
  TwoWire * _wire;
};


//  -- END OF FILE --

