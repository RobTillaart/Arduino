#pragma once
//
//    FILE: rotaryDecoderSwitch.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2021-05-17
// PURPOSE: Arduino library for rotary decoder (with switch)
//     URL: https://github.com/RobTillaart/rotaryDecoderSwitch


#include "Arduino.h"
#include "Wire.h"

#define ROTARY_DECODER_SWITCH_LIB_VERSION         (F("0.3.1"))


class rotaryDecoderSwitch
{
public:
  explicit rotaryDecoderSwitch(const int8_t address, TwoWire *wire = &Wire);

  bool    begin(uint8_t count = 2);
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
  int32_t getValue(uint8_t re);
  bool    setValue(uint8_t re, int32_t value = 0);
  bool    isKeyPressed(uint8_t re);


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
  uint8_t   _lastPos[2] = { 0, 0 };
  int32_t   _encoder[2] = { 0, 0 };

  uint8_t   _address;
  TwoWire * _wire;
};


//  -- END OF FILE --

