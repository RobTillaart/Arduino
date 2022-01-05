//
//    FILE: M62429.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for M62429 volume control IC
// VERSION: 0.3.0
// HISTORY: See M62429.cpp2
//     URL: https://github.com/RobTillaart/M62429

//  HISTORY:
//  0.1.0   2019-01-17  initial version
//  0.2.0   2020-08-02  refactor
//  0.2.1   2020-12-30  add Arduino-CI + unit test
//  0.2.2   2021-05-27  fix library.properties
//  0.2.3   2021-12-21  update library.json, license, readme, minor edits
//  0.3.0   2021-12-30  fix #4 incomplete protocol


#include "M62429.h"


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

  uint8_t attn = volume/3 + 2;
  if (attn <= 2) attn = 0;
  _setVolume(channel, attn);

  // update cached values
  if (channel == 0) _vol[0] = volume;
  if (channel == 1) _vol[1] = volume;
  if (channel == 2) _vol[0] = _vol[1] = volume;
  return M62429_OK;
}


void M62429::incr()
{
  if (_vol[0] < 255) _vol[0]++;
  setVolume(0, _vol[0]);
  if (_vol[1] < 255) _vol[1]++;
  setVolume(1, _vol[1]);
}


void M62429::decr()
{
  if (_vol[0] > 0) _vol[0]--;
  setVolume(0, _vol[0]);
  if (_vol[1] > 0) _vol[1]--;
  setVolume(1, _vol[1]);
}


void M62429::average()
{
  uint8_t v = (((int)_vol[0]) + _vol[1]) / 2;
  setVolume(0, v);
  setVolume(1, v);
}


void M62429::muteOn()
{
  _muted = true;
  setVolume(2, 0);
}


void M62429::muteOff()
{
  _muted = false;
  setVolume(0, _vol[0]);
  setVolume(1, _vol[1]);
}


////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// attn = 0, 3..87
void M62429::_setVolume(uint8_t channel, uint8_t attn)
{
  uint16_t databits = 0xFE00;               //  D10 -  D9 latch bits
  databits |= ((attn & 0x03) << 7);         //  D8  -  D7
  databits |= (attn & 0x007C);              //  D6  -  D2
  // channel == 2 -> both 0x00 is default
  if (channel == 0) databits |= 0x03;       //  D0  -  D1
  if (channel == 1) databits |= 0x02;       //  D0  -  D1

  // write D0 - D9
  for (uint16_t mask = 1; mask < 0x0400; mask <<= 1)
  {
    digitalWrite(_data, databits & mask);
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

  // latch signal requires _clock low before _data
  // make _data dummy write to keep timing constant
  digitalWrite(_data, HIGH);
  digitalWrite(_clock, LOW);
  if (M62429_CLOCK_DELAY > 0) delayMicroseconds(M62429_CLOCK_DELAY);

  digitalWrite(_data, LOW);
  if (M62429_CLOCK_DELAY > 0) delayMicroseconds(M62429_CLOCK_DELAY);
}


// -- END OF FILE --

