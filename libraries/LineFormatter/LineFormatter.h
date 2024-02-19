#pragma once
//
//    FILE: LineFormatter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Simple positioning wrapper class for Serial / Stream
//    DATE: 2020-05-14
//     URL: https://github.com/RobTillaart/LineFormatter


#include "Arduino.h"
#include "Print.h"

#ifndef MAX_TAB_STOPS
#define MAX_TAB_STOPS                       12
#endif

#define LINEFORMATTER_LIB_VERSION           (F("0.3.0"))


class LineFormatter: public Print
{
public:
  LineFormatter(Print* stream = &Serial);

  void      reset();

  size_t    write(uint8_t ch);


  //  set the maximum line length - bold cut off
  void      setMaxLength(uint8_t maxPos);
  uint8_t   getMaxLength();


  //  if position is smaller than n, move to the right
  uint8_t   gotoPos(uint8_t position);


  //  repeat a char or a "string" n times
  //  followed by 0 or more newlines.
  void      repeat(uint8_t n, char ch, uint8_t newLine = 0);
  void      repeat(uint8_t n, const char* str, uint8_t newLine = 0);


  //  n = 0 switches autoNewLine off
  void      setAutoNewLine(uint8_t n = 1);
  uint8_t   getAutoNewLine();


  //  Set the internal array of tabs at once, easy bulk config, 
  //  positions is an increasing array.
  bool      setTabs(uint8_t * positions, uint8_t size);
  //  get array with positions.
  uint8_t   getTabs(uint8_t * positions);

  //  Add one tab at (absolute or relative) position
  //  returns true on success
  bool      addTab(uint8_t position);
  bool      addRelTab(uint8_t n);
  //  remove all the tabs,
  void      clearTabs();
  //  remove tab at position position
  //  returns false if it does not exist.
  bool      removeTab(uint8_t position);
  bool      existTab(uint8_t position);

  //  print zero or more tabs, similar as e.g. "\t\t\t"
  //  optimized repeat
  void      tab(uint8_t n = 1);


  //  MISCELLANEOUS
  uint8_t   getPos();
  void      resetLineCount();
  uint32_t  getLineCount();
  uint8_t   getTabCount();
  uint8_t   getTabStop(uint8_t n);
  void      printRuler(uint8_t length);


private:
  Print *   _stream;

  uint8_t   _pos         = 0;
  uint8_t   _maxPos      = 0;
  uint32_t  _lineCount   = 0;
  uint8_t   _anl         = 0;  //  counter
  uint8_t   _autoNewLine = 0;  //  position for the newline.

  uint8_t   _tabStop[MAX_TAB_STOPS];
  uint8_t   _tabCount = 0;
};


//  -- END OF FILE --

