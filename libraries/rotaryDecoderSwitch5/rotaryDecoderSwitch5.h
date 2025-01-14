#pragma once
//
//    FILE: rotaryDecoderSwitch5.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-01-13
// PURPOSE: Arduino library for a PCF8575 based rotary decoder (with switch)
//     URL: https://github.com/RobTillaart/rotaryDecoderSwitch5


#include "Arduino.h"
#include "Wire.h"

#define ROTARY_DECODER_SWITCH5_LIB_VERSION         (F("0.1.0"))

const uint8_t ROTDEC_MAX_COUNT = 5;

class rotaryDecoderSwitch5
{
public:
  explicit rotaryDecoderSwitch5(const int8_t address, TwoWire *wire = &Wire);

  bool     begin(uint8_t count = ROTDEC_MAX_COUNT);
  bool     isConnected();

  uint8_t  getRECount();
  void     reset();

  uint16_t readInitialState();

  //  for polling version,
  //  checkChange is bit faster than a call to update
  //  so useful if there are only a few updates
  bool     checkChange();

  //  read and update the counters
  bool     update();         //  assumes two directions   => +1 and -1
  bool     updateSingle();   //  assumes single direction => + ++ +++

  //  re = rotary encoder 0..4
  //  returns 0, false if re > 4.
  int32_t  getValue(uint8_t re);
  bool     setValue(uint8_t re, int32_t value = 0);
  bool     isKeyPressed(uint8_t re);


  //  READ - WRITE interface
  uint8_t  read1(uint8_t pin);
  bool     write1(uint8_t pin, uint8_t value);
  uint16_t read16();
  bool     write16(uint16_t bitMask);


  //  DEBUG
  //  re = rotary encoder 0..4
  uint8_t  getLastPosition(uint8_t re);


protected:
  uint8_t   _count = 0;
  uint16_t  _lastValue = 0;
  uint8_t   _lastPos[ROTDEC_MAX_COUNT] = { 0, 0, 0, 0, 0 };
  int32_t   _encoder[ROTDEC_MAX_COUNT] = { 0, 0, 0, 0, 0 };

  uint8_t   _address;
  TwoWire * _wire;
};


//  -- END OF FILE --

