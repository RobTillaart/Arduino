#pragma once
//
//    FILE: wordCount.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-01-23
// PURPOSE: Arduino library for creating a wordCounter
//     URL: https://github.com/RobTillaart/wordCount


#include "Arduino.h"

#define WORDCOUNT_LIB_VERSION     (F("0.1.0"))



class wordCount : public Print
{
public:
  wordCount(Print* stream = &Serial)
  {
    _stream = stream;
    reset();
  };

  uint32_t lines()  { return _lines; };
  uint32_t words()  { return _words; };
  uint32_t chars()  { return _chars; };
  uint32_t digits() { return _digits; };

  //  THROUGHPUT
  float    bytesPerSecond()
  {
    return (1000.0 * _chars) / (millis() - _startTime);
  }
  float    Bps()  { return bytesPerSecond(); };
  float    kBps() { return bytesPerSecond() / 1024.0f; };
  float    MBps() { return bytesPerSecond() / (1024.0f * 1024.0f); };

  float    wordsPerSecond()
  {
    return (1000.0 * _words) / (millis() - _startTime);
  }

  float    linesPerSecond()
  {
    return (1000.0 * _lines) / (millis() - _startTime);
  }

  //  STATISTICS
  float    averageCharsPerLine()
  {
    if (_lines <= 0) return -1;
    return (1.0 * _chars) / _lines;
  }

  void reset()
  {
    _lines  = 0;
    _words  = 0;
    _chars  = 0;
    _inWord = false;
    _startTime = millis();
  };


private:
  Print*   _stream;

  //  too simplistic minimal version,
  //  needs state for words and lines.
  size_t   write(uint8_t c)
  {
    //  CHARS
    _chars++;

    //  DIGITS
    if (isDigit(c))
    {
      _digits++;
    }
    
    //  WORDS
    //  accept a..zA..Z0..9 + _
    if ((isAlphaNumeric(c) == true) || (c == '_'))
    {
      if (_inWord == false)
      {
        _inWord = true;
        _words++;
      }
    }
    else
    {
      _inWord = false;
    }

    //  LINES
    if (c == '\n')
    {
      _lines++;
    }
    _stream->write(c);
    return 1;
  }

  uint32_t _lines = 0;
  uint32_t _words = 0;
  uint32_t _chars = 0;
  uint32_t _digits = 0;

  bool     _inWord = false;
  uint32_t _startTime = 0;
};


//  -- END OF FILE --

