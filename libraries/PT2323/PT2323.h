#pragma once
//
//    FILE: PT2323.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-07-23
// VERSION: 0.1.0
// PURPOSE: Arduino library for PT2323 I2C 6 channel audio processor / selector.
//     URL: https://github.com/RobTillaart/PT2323


#include "Arduino.h"
#include "Wire.h"


#define PT2323_LIB_VERSION                   (F("0.1.0"))


class PT2323
{
public:
  PT2323(TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();
  uint8_t getAddress();

  //  CHANNEL = 0..3 or 6  (fig 2, page 8)
  bool    setChannel(uint8_t channel = 0);
  uint8_t getChannel();

  //  (fig1, page 8)
  bool    muteFrontLeft(bool mute);
  bool    muteFrontRight(bool mute);
  bool    muteCenter(bool mute);
  bool    muteSubWoofer(bool mute);
  bool    muteRearLeft(bool mute);
  bool    muteRearRight(bool mute);
  bool    muteAll(bool mute);

  //  (fig 3, page 8)
  bool    setSurround(bool enable);
  bool    getSurround();

  //  (fig 3, page 8)
  bool    setMixedChannel(bool six_db);
  bool    getMixedChannel();

  int     getLastError();

private:
  int     write(const uint8_t value);

  TwoWire  *_wire;
  uint8_t  _address   = 0x94;

  uint8_t  _channel   = 0;
  bool     _surround  = false;
  bool     _mixedChannel = false;
  int      _error = 0;
};


//  -- END OF FILE --

