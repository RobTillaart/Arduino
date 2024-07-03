#pragma once
//
//    FILE: ADG728.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-07-03
// PURPOSE: Arduino Library for I2C ADG728 matrix switch. 1x8 Multiplexer.
//     URL: https://github.com/RobTillaart/ADG728
//          https://www.adafruit.com/product/5899


#include "Arduino.h"
#include "Wire.h"


#define ADG728_LIB_VERSION             (F("0.1.0"))


//  ERROR CODES (to be elaborated)
#define ADG728_OK                      0
#define ADG728_ERROR_I2C               -10  //  not used yet
#define ADG728_ERROR_CHANNEL           -20  //  not used yet



class ADG728
{
public:
  //  deviceAddress = 0x4C .. 0x4F
  ADG728(uint8_t deviceAddress, TwoWire *wire = &Wire);

  bool    begin(uint8_t mask = 0x00);         //  default no channels enabled
  bool    isConnected();                      //  find address on I2C bus

  //  channel = 0..channelCount()-1
  uint8_t channelCount();
  bool    enableChannel(uint8_t channel);     //  enable channel NON exclusive
  bool    disableChannel(uint8_t channel);
  bool    selectChannel(uint8_t channel);     //  enable channel exclusive
  bool    isEnabled(uint8_t channel);
  bool    disableAllChannels();


  //  mask = 0x00 .. 0xFF - every bit is a channel.
  //         although not for derived types.
  //  note 1:  these are set simultaneously.
  //  note 2:  these may include interrupt bits (in derived classes)
  bool    setChannelMask(uint8_t mask);
  uint8_t getChannelMask();

  //  reset
  void    setResetPin(uint8_t resetPin);
  void    reset();     //  trigger reset pin

  //  set forced IO (default false)
  void    setForced(bool forced = false);
  bool    getForced();

  int     getError();


protected:
  uint8_t   _address;
  TwoWire*  _wire;
  uint8_t   _mask;             //  caching mask = status of channels
  uint8_t   _resetPin;         //  default not set == -1 (255)
  bool      _forced;
  int       _error;
  uint8_t   _channels;
};


//  -- END OF FILE --

