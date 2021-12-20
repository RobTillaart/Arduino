#pragma once
//
//    FILE: LineFormatter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: Simple positioning wrapper class for Serial / Stream
//    DATE: 2020-05-14
//     URL: https://github.com/RobTillaart/LineFormatter
//

#include "Arduino.h"
#include "Print.h"

#ifndef MAX_TAB_STOPS
#define MAX_TAB_STOPS       12
#endif

#define LINEFORMATTER_LIB_VERSION           (F("0.1.4"))


class LineFormatter: public Print
{
public:
  LineFormatter(Print* stream = &Serial);

  void      reset();

  size_t    write(uint8_t c);


  // set the maximum line length - bold cut off
  void      setMaxLength(uint8_t maxPos) { _maxPos = maxPos; };
  uint8_t   getMaxLength()  { return _maxPos; };


  // if position is smaller than n, move to the right
  uint8_t   gotoPos(uint8_t pos) { while (_pos < pos) write(' '); return _pos; };


  // repeat a char or a "string" n times
  // followed by 0 or more newlines.
  void      repeat(uint8_t n, char c, uint8_t newLine = 0);
  void      repeat(uint8_t n, const char* str, uint8_t newLine = 0);


  // n = 0 switches autoNewLine off
  void      setAutoNewLine(uint8_t n);
  uint8_t   getAutoNewLine() { return _autoNewLine; };


  // Add a tab at (absolute/relative) position
  // returns true on success
  bool      addTab(uint8_t n);
  bool      addRelTab(uint8_t n);
  // remove all the tabs,
  void      clearTabs();
  // print zero or more tabs, similar as e.g. "\t\t\t"
  void      tab(uint8_t n = 1) { while (n--) write('\t'); };

  // DEBUGGING
  uint8_t   getPos()              { return _pos; };
  void      resetLineCount()      { _lineCount = 0; };
  uint16_t  getLineCount()        { return _lineCount; };
  uint8_t   getTabCount()         { return _tabCount; };
  uint8_t   getTabStop(uint8_t n) { return _tabStop[n]; };
  void      printRuler(uint8_t n);


private:
  Print *   _stream;

  uint8_t   _pos         = 0;
  uint8_t   _maxPos      = 0;
  uint16_t  _lineCount   = 0;
  uint8_t   _anl         = 0;
  uint8_t   _autoNewLine = 0;

  uint8_t   _tabStop[MAX_TAB_STOPS];
  uint8_t   _tabCount = 0;
};


// -- END OF FILE --

