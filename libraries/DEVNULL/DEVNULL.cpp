//
//    FILE: DEVNULL.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: Arduino library for a /dev/null stream - useful for testing
//     URL: https://github.com/RobTillaart/DEVNULL
//
// HISTORY:
//  0.1.0   2020-06-23  initial version.
//  0.1.1   2020-12-18  add Arduino-CI.
//  0.1.2   2021-11-24  update build-CI, badges, etc.
//                      added write(data, length) + _timeOut.
//  0.1.3   2021-12-15  update library.json, license, minor edits
//  0.1.4   2022-09-21  split up .h in .cpp and .h
//                      add last() to check last byte written to.


#include "DEVNULL.h"

DEVNULL::DEVNULL()
{
  setTimeout(0);        //  no timeout.
  _bottomLessPit = -1;  //  nothing in the pit
}

int  DEVNULL::available() { return 0; };
int  DEVNULL::peek()      { return EOF; };
int  DEVNULL::read()      { return EOF; };
//  placeholder to keep CI happy
void DEVNULL::flush()     { return; };

size_t DEVNULL::write(const uint8_t data)
{
  _bottomLessPit = data;
  return 1;
}

size_t DEVNULL::write( const uint8_t *buffer, size_t size)
{
  if (size > 0) _bottomLessPit = buffer[size - 1];
  return size;
}

int DEVNULL::lastByte()
{
  return _bottomLessPit;
}


// -- END OF FILE --

