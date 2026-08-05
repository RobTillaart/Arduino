//
//    FILE: DEVNULL.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.9
//    DATE: 2020-06-23
// PURPOSE: Arduino library for a /dev/null stream - useful for testing
//     URL: https://github.com/RobTillaart/DEVNULL


#include "DEVNULL.h"


DEVNULL::DEVNULL()
{
  setTimeout(0);        //  no timeout.
#if defined(DEVNULL_ENABLE_DEBUG) && DEVNULL_ENABLE_DEBUG
  _bottomLessPit = -1;  //  nothing in the pit
#endif
}

int  DEVNULL::available()
{
  return 0;
}

int  DEVNULL::peek()
{
  return EOF;
}

int  DEVNULL::read()
{
  return EOF;
}

//  placeholder to keep CI happy
void DEVNULL::flush()
{
  return;
}

size_t DEVNULL::write(const uint8_t data)
{
//  will generate warning
#if defined(DEVNULL_ENABLE_DEBUG) && DEVNULL_ENABLE_DEBUG
  _bottomLessPit = data;
#endif
  return 1;
}

size_t DEVNULL::write( const uint8_t *buffer, size_t size)
{
//  will generate warning
#if defined(DEVNULL_ENABLE_DEBUG) && DEVNULL_ENABLE_DEBUG
  if (size > 0) _bottomLessPit = buffer[size - 1];
#endif
  return size;
}

#if defined(DEVNULL_ENABLE_DEBUG) && DEVNULL_ENABLE_DEBUG
int DEVNULL::lastByte()
{
  return _bottomLessPit;
}
#endif


//  -- END OF FILE --

