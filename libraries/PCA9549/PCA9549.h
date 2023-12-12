#pragma once
//
//    FILE: PCA9549.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-12-12
// PURPOSE: Arduino Library for PCA9549 I2C octal bus switch.
//     URL: https://github.com/RobTillaart/PCA9549


#include "Arduino.h"
#include "Wire.h"


#define PCA9549_LIB_VERSION             (F("0.1.0"))

#define PCA9549_OK                       0x00


class PCA9549
{
public:
  //  deviceAddress = 0x70 .. 0x77
  PCA9549(uint8_t deviceAddress, TwoWire *wire = &Wire);

  bool    begin(uint8_t mask = 0x00);         //  default no channels enabled
  bool    isConnected();                      //  find multiplexer on I2C bus


  //  channel = 0..channelCount()-1
  bool    enableChannel(uint8_t channel);     //  enable this channel non exclusive
  bool    disableChannel(uint8_t channel);
  bool    selectChannel(uint8_t channel);     //  enable only this channel
  bool    isEnabled(uint8_t channel);
  bool    disableAllChannels();


  //  mask = 0x00 .. 0xFF - every bit is a channel.
  //  note 1:  these are set simultaneously.
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
};


//  -- END OF FILE --

