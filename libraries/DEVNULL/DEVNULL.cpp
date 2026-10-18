//
//    FILE: DEVNULL.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2020-06-23
// PURPOSE: Arduino library for a /dev/null stream - useful for testing
//     URL: https://github.com/RobTillaart/DEVNULL


#include "DEVNULL.h"


DEVNULL::DEVNULL()
{
  setTimeout(0);        //  no timeout.
#ifdef DEVNULL_ENABLE_DEBUG
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
#ifdef DEVNULL_ENABLE_DEBUG
  _bottomLessPit = data;
#else
  (void) data;
#endif
  return 1;
}

size_t DEVNULL::write( const uint8_t *buffer, size_t size)
{
#ifdef DEVNULL_ENABLE_DEBUG
  if (size > 0) _bottomLessPit = buffer[size - 1];
#else
  (void) buffer[0];
#endif
  return size;
}

size_t DEVNULL::readBytes( const uint8_t *buffer, size_t size)
{
  (void) buffer[size];
  return 0;
}


#ifdef DEVNULL_ENABLE_DEBUG
int DEVNULL::lastByte()
{
  return _bottomLessPit;
}
#endif


//  -- END OF FILE --

