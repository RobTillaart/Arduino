#pragma once
//
//    FILE: TCA9548.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
//    DATE: 2021-03-16
// PURPOSE: Library for TCA9548 I2C multiplexer
//     URL: https://github.com/RobTillaart/TCA9548


#include "Arduino.h"
#include "Wire.h"


#define TCA9548_LIB_VERSION             (F("0.1.5"))


//  ERROR CODES (to be elaborated)
#define TCA9548_OK                      0
#define TCA9548_ERROR_I2C               -10  //  not used yet
#define TCA9548_ERROR_CHANNEL           -20  //  not used yet



class TCA9548
{
public:
  //  deviceAddress = 0x70 .. 0x77
  TCA9548(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool    begin(uint8_t dataPin, uint8_t clockPin, uint8_t mask = 0x00);  //  default no channels enabled
#endif
  bool    begin(uint8_t mask = 0x00);         //  default no channels enabled
  bool    isConnected();                      //  find multiplexer on I2C bus
  bool    isConnected(uint8_t address);       //  find any address on I2C bus

  //  channel = 0.. 7
  bool    enableChannel(uint8_t channel);     //  enable this channel non exclusive
  bool    disableChannel(uint8_t channel);
  bool    selectChannel(uint8_t channel);     //  enable only this channel
  bool    isEnabled(uint8_t channel);
  bool    disableAllChannels();

  //  mask = 0x00 .. 0xFF - every bit is a channel.
  //  note these are set simultaneously.
  bool    setChannelMask(uint8_t mask);
  uint8_t getChannelMask();

  //  reset
  void    setResetPin(uint8_t resetPin);
  void    reset();     //  trigger reset pin

  //  set forced IO (default false)
  void    setForced(bool forced = false);
  bool    getForced();

  int     getError();


private:
  uint8_t   _address;
  TwoWire*  _wire;
  uint8_t   _mask;             //  caching mask = status of channels
  uint8_t   _resetPin;         //  default not set == -1 (255)
  bool      _forced;
  int       _error;
};


//  -- END OF FILE --

