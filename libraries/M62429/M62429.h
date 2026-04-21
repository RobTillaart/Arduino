#pragma once
//
//    FILE: M62429.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for M62429 volume control IC
// VERSION: 0.4.0
//    DATE: 2019-01-17
//     URL: https://github.com/RobTillaart/M62429


#include "Arduino.h"


#define M62429_LIB_VERSION              (F("0.4.0"))
//  obsolete in future
#define M62429_VERSION                  (M62429_LIB_VERSION)


//  minimum pulse width CLOCK = 1.6 us (datasheet);
//  digitalWrite takes enough time on UNO / AVR so clock_delay == 0
//  Note that if clock pulses are long enough the data pulses are too.
#ifndef M62429_CLOCK_DELAY
#ifdef __AVR__
#define M62429_CLOCK_DELAY          0
#else
#define M62429_CLOCK_DELAY          2
#endif
#endif


//  ERROR CODES
constexpr int M62429_OK            =  0;
constexpr int M62429_MUTED         = -1;
constexpr int M62429_CHANNEL_ERROR = -10;


//  CHANNELS
constexpr uint8_t M62429_LEFT  = 0;
constexpr uint8_t M62429_RIGHT = 1;
constexpr uint8_t M62429_BOTH  = 2;


class M62429
{
public:
  M62429();

  void     begin(uint8_t dataPin, uint8_t clockPin);

  //  channel = 0, 1, 2
  //      2 = both returns maximum of both channels
  int     getVolume(uint8_t channel);
  //  channel = 0, 1, 2 = both
  //  volume  = 0..255
  int     setVolume(uint8_t channel, uint8_t volume);
  //  increment / decrement until minimum/maximum = 0..255
  int     increment(uint8_t channel = 2);
  int     decrement(uint8_t channel = 2);

  int     average();

  void    muteOn();
  void    muteOff();
  bool    isMuted();


private:
  uint8_t _vol[2] = { 0, 0 };
  uint8_t _data   = 0;
  uint8_t _clock  = 0;
  bool    _muted  = false;

  void    _setAttn(uint8_t channel, uint8_t attn);
};


//////////////////////////////////////////

//  M62429_RAW class only
constexpr uint16_t M62429_MAX_ATTN = 87;  //  decibel

class M62429_RAW
{
public:

  void begin(uint8_t dataPin, uint8_t clockPin);

  //  channel = { 0, 1 }
  int     getAttn(uint8_t channel);
  //  channel = { 0, 1, 2 = both;
  //  attn    = {0 .. 87 }
  void    setAttn(uint8_t channel, uint8_t attn);

private:
  uint8_t _attn[2] = { 0, 0 };
  uint8_t _data   = 0;
  uint8_t _clock  = 0;
};


//  -- END OF FILE --

