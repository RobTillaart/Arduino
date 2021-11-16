#pragma once
//
//    FILE: rotaryDecoderSwitch.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2021-05-17
// PURPOSE: rotary decoder library for Arduino
//     URL: https://github.com/RobTillaart/rotaryDecoderSwitch


#include "Arduino.h"
#include "Wire.h"

#define ROTARY_DECODER_SWITCH_LIB_VERSION         (F("0.1.1"))


class rotaryDecoderSwitch
{
public:
  explicit rotaryDecoderSwitch(const int8_t address, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool    begin(uint8_t sda, uint8_t scl, uint8_t count = 2);
#endif

  bool    begin(uint8_t count = 2);
  bool    isConnected();

  void    readInitialState();

  // for polling version, 
  // checkChange is bit faster than a call to update
  // so useful if there are only a few updates 
  bool    checkChange();

  // read and update the counters
  bool    update();         // assumes two directions   => +1 and -1
  bool    updateSingle();   // assumes single direction => + ++ +++ 

  int32_t getValue(uint8_t re) { return _encoder[re]; };
  void    setValue(uint8_t re, int32_t val = 0) { _encoder[re] = val; };
  bool    isKeyPressed(uint8_t re);

  // DEBUG
  uint8_t getLastPosition(uint8_t re) { return _lastPos[re]; };
  uint8_t getRaw() { return _read8(); };

private:
  uint8_t   _count = 0;
  uint8_t   _lastValue = 0;
  uint8_t   _lastPos[2] = { 0,0 };
  int32_t   _encoder[2] = { 0,0 };

  uint8_t   _read8();
  uint8_t   _address;
  TwoWire * _wire;
};


// -- END OF FILE --

