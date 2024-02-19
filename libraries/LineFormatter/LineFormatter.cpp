//
//    FILE: LineFormatter.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Simple positioning wrapper class for Serial
//    DATE: 2020-05-14
//     URL: https://github.com/RobTillaart/LineFormatter


#include "LineFormatter.h"


LineFormatter::LineFormatter(Print* stream)
{
  _stream      = stream;
  reset();
};


void LineFormatter::reset()
{
  _pos         = 0;
  _maxPos      = 0;
  _lineCount   = 0;
  _anl         = 0;
  _autoNewLine = 0;
  _tabCount    = 0;
}


///////////////////////////////////////////
//
//  WRITE - the core
//
size_t LineFormatter::write(uint8_t ch)
{
  //  handle tabs.
  if (_tabCount && (ch == '\t'))
  {
    write(' ');
    for (int i = 0; i < _tabCount; i++)
    {
      if (_tabStop[i] > _pos + 1)   //  assume sorted
      {
        gotoPos(_tabStop[i] - 1);
        break;
      }
    }
  }
  else
  {
    _stream->write(ch);
    _pos++;
  }

  //  handle return
  if (ch == '\n')
  {
    _pos = 0;
    _lineCount++;
    _anl++;
  }

  //  handle _maxPos if enabled (_maxPos > 0)
  if ((_maxPos > 0) && (_pos == _maxPos))
  {
    write('\n');  //  recursive call!
  }

  //  handle autoNewLine
  if (_autoNewLine && (_anl == _autoNewLine))
  {
    write('\n');  //  recursive call!
    _anl = 0;
  }
  return 1;
}


void LineFormatter::setMaxLength(uint8_t maxPos)
{
  _maxPos = maxPos;
}


uint8_t LineFormatter::getMaxLength()
{
  return _maxPos;
}


uint8_t LineFormatter::gotoPos(uint8_t position)
{
  while (_pos < position) write(' ');
  return _pos;
}


///////////////////////////////////////////
//
//  REPEAT
//
void LineFormatter::repeat(uint8_t n, char ch, uint8_t newLine)
{
  while (n--) print(ch);
  while (newLine--) write('\n');
}


void LineFormatter::repeat(uint8_t n, const char* str, uint8_t newLine)
{
  while (n--) print(str);
  while (newLine--) write('\n');
}


///////////////////////////////////////////
//
//  AUTONEWLINE
//
void LineFormatter::setAutoNewLine(uint8_t n)
{
  _autoNewLine = n;
  _anl = 0;
};


uint8_t LineFormatter::getAutoNewLine()
{
  return _autoNewLine;
}


///////////////////////////////////////////
//
//  TAB
//
bool LineFormatter::setTabs(uint8_t * positions, uint8_t size)
{
  if (size >= MAX_TAB_STOPS) return false;
  for (uint8_t i = 0; i < MAX_TAB_STOPS; i++)
  {
    if (i >= size) _tabStop[i] = 0;
    else _tabStop[i] = positions[i];
  }
  _tabCount = size;
  return true;
}


uint8_t LineFormatter::getTabs(uint8_t * positions)
{
  for (uint8_t i = 0; i < _tabCount; i++)
  {
    positions[i] = _tabStop[i];
  }
  return _tabCount;
}


bool LineFormatter::addTab(uint8_t position)
{
  if (position == 0) return false;
  //  full ?
  if (_tabCount >= MAX_TAB_STOPS) return false;
  //  prevent doubles.
  if (existTab(position)) return false;

  _tabStop[_tabCount] = position;
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


void LineFormatter::clearTabs()
{
  _tabCount = 0;
  for (uint8_t i = 0; i < MAX_TAB_STOPS; i++)
  {
    _tabStop[i] = 0;
  }
};


bool LineFormatter::removeTab(uint8_t position)
{
  for (uint8_t i = 0; i < _tabCount; i++)
  {
    if (_tabStop[i] == position)
    {
      _tabCount--;
      while(i < _tabCount)
      {
        _tabStop[i] = _tabStop[i + 1];
        i++;
      }
      return true;
    }
  }
  return false;
}


bool LineFormatter::existTab(uint8_t position)
{
  for (uint8_t i = 0; i < _tabCount; i++)
  {
    if (_tabStop[i] == position) return true;
  }
  return false;
}


void LineFormatter::tab(uint8_t n)
{
  while (n--) write('\t');
}


///////////////////////////////////////////
//
//  MISCELLANEOUS
//
uint8_t LineFormatter::getPos()
{
  return _pos;
}


void LineFormatter::resetLineCount()
{
  _lineCount = 0;
}


uint32_t LineFormatter::getLineCount()
{
  return _lineCount;
}


uint8_t LineFormatter::getTabCount()
{
  return _tabCount;
}


uint8_t LineFormatter::getTabStop(uint8_t n)
{
  return _tabStop[n];
}


void LineFormatter::printRuler(uint8_t length)
{
  //  DEBUG
  //  for (uint8_t i = 0; i < _tabCount; i++) _stream->println(_tabStop[i]);

  uint8_t t = 0;
  for (uint8_t i = 1; i <= length; i++)
  {
    char ch = '.';
    if (i == _tabStop[t])
    {
      ch = '#';
      t++;
    }
    else if ((i % 10) == 0) ch = '0';
    else if ((i % 5) == 0)  ch = '5';
    write(ch);
  }
  write('\n');
}


//  -- END OF FILE --

