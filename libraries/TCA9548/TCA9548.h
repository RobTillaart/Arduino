#pragma once
//
//    FILE: TCA9548.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2021-03-16
// PURPOSE: Arduino Library for TCA9548 I2C multiplexer and compatibles.
//     URL: https://github.com/RobTillaart/TCA9548


#include "Arduino.h"
#include "Wire.h"


#define TCA9548_LIB_VERSION             (F("0.3.0"))


//  ERROR CODES (to be elaborated)
#define TCA9548_OK                      0
#define TCA9548_ERROR_I2C               -10  //  not used yet
#define TCA9548_ERROR_CHANNEL           -20  //  not used yet



class TCA9548
{
public:
  //  deviceAddress = 0x70 .. 0x77
  TCA9548(uint8_t deviceAddress, TwoWire *wire = &Wire);

  bool    begin(uint8_t mask = 0x00);         //  default no channels enabled
  bool    isConnected();                      //  find multiplexer on I2C bus
  bool    isConnected(uint8_t address);       //  find any address on I2C bus
  bool    isConnected(uint8_t address, uint8_t channel);  //  find address on selected channel

  uint8_t find(uint8_t address);  // returns a mask with channels
  
  //  channel = 0..channelCount()-1
  uint8_t channelCount();
  bool    enableChannel(uint8_t channel);     //  enable this channel non exclusive
  bool    disableChannel(uint8_t channel);
  bool    selectChannel(uint8_t channel);     //  enable only this channel
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
  uint8_t    _address;
  TwoWire *  _wire;
  uint8_t    _mask;             //  caching mask = status of channels
  uint8_t    _resetPin;         //  default not set == -1 (255)
  bool       _forced;
  int        _error;
  uint8_t    _channels;         //  PCA954x support.
};


/////////////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
//  see - https://github.com/RobTillaart/TCA9548/issues/15
//

//  SWITCH, 8 channel + reset
class PCA9548 : public TCA9548
{
public:
  PCA9548(uint8_t deviceAddress, TwoWire *wire = &Wire);
};


//  SWITCH, 4 channel + reset
class PCA9546 : public TCA9548
{
public:
  PCA9546(uint8_t deviceAddress, TwoWire *wire = &Wire);
  uint8_t getChannelMask();
};


//  DEVICES WITH INTERRUPT

//  SWITCH, 4 channel + reset + interrupt
class PCA9545 : public TCA9548
{
public:
  PCA9545(uint8_t deviceAddress, TwoWire *wire = &Wire);
  uint8_t getChannelMask();
  uint8_t getInterruptMask();
};


//  SWITCH, 2 channel + reset + interrupt
class PCA9543 : public TCA9548
{
public:
  PCA9543(uint8_t deviceAddress, TwoWire *wire = &Wire);
  uint8_t getChannelMask();
  uint8_t getInterruptMask();
};


//  -- END OF FILE --

