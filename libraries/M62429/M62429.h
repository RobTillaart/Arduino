#pragma once
//
//    FILE: M62429.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for M62429 volume control IC
// VERSION: 0.3.7
//     URL: https://github.com/RobTillaart/M62429


#include "Arduino.h"


#define M62429_VERSION              (F("0.3.7"))


// minimum pulse width CLOCK = 1.6 us (datasheet);
// digitalWrite takes enough time on UNO / AVR so clock_delay == 0
// Note that if clock pulses are long enough the data pulses are too.
#ifndef M62429_CLOCK_DELAY
#ifdef __AVR__
#define M62429_CLOCK_DELAY          0
#else
#define M62429_CLOCK_DELAY          2
#endif
#endif


// ERROR CODES
#define M62429_OK                    0
#define M62429_MUTED                -1
#define M62429_CHANNEL_ERROR        -10

// CHANNELS
#define M62429_LEFT                  0
#define M62429_RIGHT                 1
#define M62429_BOTH                  2


class M62429
{
public:
  M62429();

  void     begin(uint8_t dataPin, uint8_t clockPin);

  //  channel = { 0, 1 }
  int     getVolume(uint8_t channel);
  //  channel = { 0, 1, 2 = both;
  //  volume  = {0 .. 255 }
  int     setVolume(uint8_t channel, uint8_t volume);
  //  increment / decrement until min/max = 0..255
  int     incr(uint8_t channel = 2);
  int     decr(uint8_t channel = 2);

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

