#pragma once
//
//    FILE: rotaryDecoder.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2021-05-08
// PURPOSE: rotary decoder library for Arduino
//     URL: https://github.com/RobTillaart/rotaryDecoder


#include "Arduino.h"
#include "Wire.h"

#define ROTARY_DECODER_LIB_VERSION         (F("0.1.1"))


class rotaryDecoder
{
public:
  explicit rotaryDecoder(const int8_t address, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool    begin(uint8_t sda, uint8_t scl, uint8_t count = 4);
#endif

  bool    begin(uint8_t count = 4);
  bool    isConnected();

  void    readInitialState();

  // for polling version, 
  // checkChange is bit faster than a call to update
  // so useful if there are only a few updates 
  bool    checkChange();

  // read and update the counters
  bool    update();         // assumes two directions   => +1 and -1
  bool    updateSingle();   // assumes single direction => + ++ +++ 

  // re = rotary encoder
  int32_t getValue(uint8_t re) { return _encoder[re]; };
  void    setValue(uint8_t re, int32_t value = 0) { _encoder[re] = value; };

  // DEBUG
  uint8_t getLastPosition(uint8_t re) { return _lastPos[re]; };

private:
  uint8_t   _count = 0;
  uint8_t   _lastValue = 0;
  uint8_t   _lastPos[4] = { 0,0,0,0 };
  int32_t   _encoder[4] = { 0,0,0,0 };

  uint8_t   _read8();
  uint8_t   _address;
  TwoWire * _wire;
};

// -- END OF FILE --
