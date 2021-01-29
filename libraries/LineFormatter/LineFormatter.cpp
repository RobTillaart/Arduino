//
//    FILE: LineFormatter.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Simpe positioning wrapper class for Serial
//    DATE: 2020-05-14
//     URL: https://github.com/RobTillaart/LineFormatter
//
//  HISTORY:
//  0.1.0   2020-05-14  initial version
//  0.1.1   2020-06-19  fix library.json
//  0.1.2   2020-12-30  Arduino-ci + unit tests


#include "LineFormatter.h"

LineFormatter::LineFormatter(Print* stream)
{
  _stream      = stream;
  // reset
  _pos         = 0;
  _maxPos      = 0;
  _lineCount   = 0;
  _anl         = 0;
  _autoNewLine = 0;
  _tabCount    = 0;
};


///////////////////////////////////////////
//
// WRITE - the core
//
size_t LineFormatter::write(uint8_t c)
{
  // handle tabs.
  if (_tabCount && c == '\t')
  {
    write(' ');
    for (int i = 0; i < _tabCount; i++)
    {
      if (_tabStop[i] > _pos + 1)   // assume sorted
      {
        gotoPos(_tabStop[i] - 1);
        break;
      }
    }
  }
  else
  {
    _stream->write(c);
    _pos++;
  }

  // handle return
  if (c == '\n')
  {
    _pos = 0;
    _lineCount++;
    _anl++;
  }

  // handle maxpos
  if (_maxPos && _pos == _maxPos)
  {
    write('\n');
  }

  // handle autoNewLine
  if (_autoNewLine && (_anl == _autoNewLine))
  {
    write('\n');
    _anl = 0;
  }
  return 1;
}

///////////////////////////////////////////
//
// REPEAT
//
void LineFormatter::repeat(uint8_t n, char c, uint8_t newLine)
{
  while (n--) print(c);
  while (newLine--) write('\n');
}

void LineFormatter::repeat(uint8_t n, const char* str, uint8_t newLine)
{
  while (n--) print(str);
  while (newLine--) write('\n');
}

///////////////////////////////////////////
//
// AUTONEWLINE
//
void LineFormatter::setAutoNewLine(uint8_t n)
{
  _autoNewLine = n;
  _anl = 0;
};

///////////////////////////////////////////
//
// TAB
//
void LineFormatter::clearTabs()
{
  _tabCount = 0;
  for (uint8_t i = 0; i < MAX_TAB_STOPS; i++)
  {
    _tabStop[i] = 0;
  }
};

bool LineFormatter::addTab(uint8_t n)
{
  if (_tabCount >= MAX_TAB_STOPS) return false;
  _tabStop[_tabCount] = n;
  _tabCount++;
  return true;
}

bool LineFormatter::addRelTab(uint8_t n)
{
  if (_tabCount >= MAX_TAB_STOPS) return false;
  uint8_t newPos = n;
  if (_tabCount != 0) newPos += _tabStop[_tabCount - 1];
  addTab(newPos);
  return true;
}

///////////////////////////////////////////
//
// DEBUGGING
//
void LineFormatter::printRuler(uint8_t n)
{
  // for (int i = 0; i < _tabCount; i++) _stream->println(_tabStop[i]);
  // return;

  uint8_t t = 0;
  for (int i = 1; i <= n; i++)
  {
    char c = '.';
    if (i && i % 5 == 0) c = '5';
    if (i && i % 10 == 0) c = '0';
    if (_tabCount && (t < _tabCount) && (i == _tabStop[t]))
    {
      c = '#';
      t++;
    }
    write(c);
  }
  write('\n');
}

// -- END OF FILE --
