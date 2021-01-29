#pragma once
//
//    FILE: PAR27979.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library for Parallax 27979 _serial LCD display
//     URL: https://github.com/RobTillaart/PAR27979
//
//  HISTORY:
//  0.1.0   2010-03-06  initial version Macro's only
//  0.2.0   2020-06-23  complete redo as class
//                      also support for 27976, 27977 (not tested)
//  0.2.1   2021-01-03  Arduino-CI + unit test


#define PAR27929_VERSION      (F("0.2.1"))

#include "Arduino.h"

class PAR27979 : public Print
{
public:
  PAR27979(Stream * str) { _ser = str; };

  void on()           { _ser->write(22); };
  void off()          { _ser->write(21); };
  void clearHome()    { _ser->write(12); delay(5);  };

  void backlightOn()  { _ser->write(17); };
  void backlightOff() { _ser->write(18); };


  // MOVEMENT
  void left()         { _ser->write(8); };
  void right()        { _ser->write(9); };
  void down()         { _ser->write(10); };
  void gotoXY(uint8_t x, uint8_t y) { _ser->write(128 + y*20 + x); };


  // CUSTOM CHARS
  // array will need to be 8 bytes. - see datasheet.
  void defineCustomChar(uint8_t idx, uint8_t * arr)
  {
    _ser->write(248 + idx);
    for (int i = 0; i < 8; i++) _ser->write(arr[i]);
  }
  void customChar(uint8_t idx) { _ser->write(idx); };


  // PLAY MUSIC
  // octave = 3, 4, 5, 6, 7
  void octave(uint8_t octave) { _ser->write(212 + octave); };
  // duration is in 1/64 = 1, 2, 4, 8, 16, 32, 64
  void duration(uint8_t duration)
  {
    uint8_t ch = 207;
    while(duration) { duration /= 2; ch++; };
    _ser->write(ch);
  }
  // A = 0, A# = 1 etc, see datasheet
  void play(uint8_t note) { _ser->write(220 + note); };
  void noSound()          { _ser->write(232); };


  // PRINT interface
  size_t write(const uint8_t data) { return _ser->write(data); };

private:
  Stream *_ser;
};

// -- END OF FILE --
