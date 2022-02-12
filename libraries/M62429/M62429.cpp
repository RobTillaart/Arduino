//
//    FILE: M62429.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for M62429 volume control IC
// VERSION: 0.3.2
// HISTORY: See M62429.cpp2
//     URL: https://github.com/RobTillaart/M62429

//  HISTORY:
//  0.1.0   2019-01-17  initial version
//  0.2.0   2020-08-02  refactor
//  0.2.1   2020-12-30  add Arduino-CI + unit test
//  0.2.2   2021-05-27  fix library.properties
//  0.2.3   2021-12-21  update library.json, license, readme, minor edits
//  0.3.0   2021-12-30  fix #4 incomplete protocol
//                      add examples, refactor
//  0.3.1   2022-02-12  performance updates
//                      average(), increment() and decrement()
//  0.3.2   2022-02-12  fix #6 mute behavior


#include "M62429.h"

#define M62429_MAX_ATTN           87 // decibel


void M62429::begin(uint8_t dataPin, uint8_t clockPin)
{
  _data = dataPin;
  _clock = clockPin;
  pinMode(_data, OUTPUT);
  pinMode(_clock, OUTPUT);
  digitalWrite(_data, LOW);
  digitalWrite(_clock, LOW);

  _muted = false;
  setVolume(2, 0);
}


int M62429::getVolume(uint8_t channel)
{
  if (channel > 2) return M62429_CHANNEL_ERROR;
  return _vol[channel & 1];
}


int M62429::setVolume(uint8_t channel, uint8_t volume)
{
  if (channel > 2) return M62429_CHANNEL_ERROR;
  if (_muted)      return M62429_MUTED;

  uint16_t attn = (M62429_MAX_ATTN * volume)/255;
  _setAttn(channel, attn);

  // update cached values
  if (channel == 0)      _vol[0] = volume;
  else if (channel == 1) _vol[1] = volume;
  else                   _vol[0] = _vol[1] = volume;
  return M62429_OK;
}


int M62429::incr()
{
  if (_muted) return M62429_MUTED;
  if (_vol[0] < 255)
  {
    _vol[0]++;
    setVolume(0, _vol[0]);
  }
  if (_vol[1] < 255)
  {
    _vol[1]++;
    setVolume(1, _vol[1]);
  }
  return M62429_OK;
}


int M62429::decr()
{
  if (_muted) return M62429_MUTED;
  if (_vol[0] > 0)
  {
    _vol[0]--;
    setVolume(0, _vol[0]);
  }
  if (_vol[1] > 0)
  {
    _vol[1]--;
    setVolume(1, _vol[1]);
  }
  return M62429_OK;
}


int M62429::average()
{
  if (_muted) return M62429_MUTED;
  uint8_t v = (((int)_vol[0]) + _vol[1]) / 2;
  setVolume(2, v);
  return M62429_OK;
}


void M62429::muteOn()
{
  if (_muted) return;
  _muted = true;
  _setAttn(2, 0);
}


void M62429::muteOff()
{
  if (_muted == false) return;
  _muted = false;
  setVolume(0, _vol[0]);
  setVolume(1, _vol[1]);
}


////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// attn = 0..M62429_MAX_ATTN
void M62429::_setAttn(uint8_t channel, uint8_t attn)
{
  uint16_t databits = 0x0200;               //         D9 latch bit
  databits |= ((attn & 0x03) << 7);         //  D8  -  D7
  databits |= (attn & 0x7C);                //  D6  -  D2
  // channel == 2 -> both 0x00 is default
  if (channel == 0) databits |= 0x03;       //  D0  -  D1
  if (channel == 1) databits |= 0x02;       //  D0  -  D1

  // write D0 - D9
  for (uint8_t i = 0; i < 10; i++)
  {
    digitalWrite(_data, databits & 0x01);
    databits >>= 1;
    digitalWrite(_clock, HIGH);
    // Note if _clock pulses are long enough, _data pulses are too.
    if (M62429_CLOCK_DELAY > 0) delayMicroseconds(M62429_CLOCK_DELAY);

    digitalWrite(_data, LOW);
    digitalWrite(_clock, LOW);
    if (M62429_CLOCK_DELAY > 0) delayMicroseconds(M62429_CLOCK_DELAY);
  }

  // Send D10 HIGH bit (Latch signal)
  digitalWrite(_data, HIGH);
  digitalWrite(_clock, HIGH);
  if (M62429_CLOCK_DELAY > 0) delayMicroseconds(M62429_CLOCK_DELAY);

  // latch D10  signal requires _clock low before _data
  // make _data dummy write to keep timing constant
  digitalWrite(_data, HIGH);
  digitalWrite(_clock, LOW);
  if (M62429_CLOCK_DELAY > 0) delayMicroseconds(M62429_CLOCK_DELAY);

  digitalWrite(_data, LOW);
  if (M62429_CLOCK_DELAY > 0) delayMicroseconds(M62429_CLOCK_DELAY);
}


// -- END OF FILE --

