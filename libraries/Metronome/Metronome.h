#pragma once
//
//    FILE: Metronome.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for creating a Metronome.
//    DATE: 2013-09-16  (initial sketch)
//     URL: https://github.com/RobTillaart/Metronome


#include "Arduino.h"


#define METRONOME_LIB_VERSION   (F("0.1.0"))


class Metronome
{
  public:
  Metronome(uint8_t tickPin, uint8_t tockPin = 255)
  {
    _tickPin = tickPin;
    _tockPin = tockPin;
    if (_tockPin == 255) _tockPin = _tickPin;
    //  defaults
    _bpm = 100;
    _measure = 4;
    _run = false;
    _tick = LOW;
    _count = 0;
  };

  void begin()
  {
    pinMode(_tickPin, OUTPUT);
    pinMode(_tockPin, OUTPUT);
    _tick = LOW;
    digitalWrite(_tickPin, _tick);
    digitalWrite(_tockPin, _tick);
  };

  //  bpm >= 30 ?
  void setBeatsPerMinute(float bpm)
  {
    _bpm = bpm;
    _interval = round(30000000 / _bpm);
  };

  float getBeatsPerMinute()
  {
    return _bpm;
  };

  //  e.g. 3 = Waltz  3/8 or 3/4
  void setMeasure(uint8_t m)
  {
    _measure = m;
  };

  uint8_t getMeasure()
  {
    return _measure;
  };

  void start()
  {
    _run = true;
    _last = micros();
  };

  void stop()
  {
    _run = false;
    _tick = LOW;
    _count = 0;
  };

  //  check must be called every millisecond for timing.
  void check()
  {
    if (_run)
    {
      uint32_t now = micros();
      if (now - _last >= _interval)
      {
         _last = now;
         _count++;
         _tick = (_tick == LOW) ? HIGH : LOW;
         if (_count < (2 * _measure - 1))
         {
           digitalWrite(_tickPin, _tick);
         }
         else
         {
           digitalWrite(_tockPin, _tick);
         }
         if (_count == (2 * _measure))
         {
           _count = 0;
         }
      }
    }
    else
    {
      _tick = LOW;
      digitalWrite(_tickPin, _tick);
      digitalWrite(_tockPin, _tick);
    }
  };


private:
  uint8_t  _tickPin;
  uint8_t  _tockPin;
  float    _bpm;
  uint8_t  _measure;
  uint8_t  _count;  //  for measure
  bool     _run;
  uint32_t _last;
  uint32_t _interval;
  uint8_t  _tick;
};


//  -- END OF FILE --

