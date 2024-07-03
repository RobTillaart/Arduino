#pragma once
//
//    FILE: ADG729.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-07-03
// PURPOSE: Arduino Library for I2C ADG729 matrix switch. 2x4 Multiplexer.
//     URL: https://github.com/RobTillaart/ADG729
//          https://www.adafruit.com/product/5932


#include "Arduino.h"
#include "Wire.h"


#define ADG729_LIB_VERSION             (F("0.1.0"))


//  ERROR CODES (to be elaborated)
#define ADG729_OK                      0
#define ADG729_ERROR_I2C               -10  //  not used yet
#define ADG729_ERROR_CHANNEL           -20  //  not used yet



class ADG729
{
public:
  //  deviceAddress = 0x4C .. 0x4F
  ADG729(uint8_t deviceAddress, TwoWire *wire = &Wire);

  bool    begin(uint8_t mask = 0x00);         //  default no channels enabled
  bool    isConnected();                      //  find address on I2C bus

  //  channel = 0..7
  uint8_t channelCount();
  bool    enableChannel(uint8_t channel);     //  enable channel NON exclusive
  bool    disableChannel(uint8_t channel);
  bool    selectChannel(uint8_t channel);     //  enable channel exclusive
  bool    isEnabled(uint8_t channel);
  bool    disableAllChannels();

  //  channel = 0..3
  //  sets both A and B with the same value.
  bool    enableAB(uint8_t channel);
  bool    disableAB(uint8_t channel);
  bool    selectAB(uint8_t channel);
  bool    isEnabledAB(uint8_t channel);
  //  A, B = 0..3
  //  sets A and B separately and uniquely.
  bool    select(uint8_t A, uint8_t B);


  //  mask = 0x00 .. 0xFF - every bit is a channel.
  //         although not for derived types.
  //  note 1:  these are set simultaneously.
  //  note 2:  these may include interrupt bits (in derived classes)
  bool    setChannelMask(uint8_t mask);
  uint8_t getChannelMask();


  //  set forced IO (default false)
  void    setForced(bool forced = false);
  bool    getForced();

  int     getError();


protected:
  uint8_t   _address;
  TwoWire*  _wire;
  uint8_t   _mask;    //  caching mask = status of channels
  bool      _forced;
  int       _error;
  uint8_t   _channels;
};


//  -- END OF FILE --

