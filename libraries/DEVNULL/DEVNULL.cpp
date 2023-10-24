//
//    FILE: DEVNULL.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
// PURPOSE: Arduino library for a /dev/null stream - useful for testing
//     URL: https://github.com/RobTillaart/DEVNULL


#include "DEVNULL.h"


DEVNULL::DEVNULL()
{
  setTimeout(0);        //  no timeout.
  _bottomLessPit = -1;  //  nothing in the pit
}

int  DEVNULL::available()
{
  return 0;
};

int  DEVNULL::peek()
{
  return EOF;
};

int  DEVNULL::read()
{
  return EOF;
};

//  placeholder to keep CI happy
void DEVNULL::flush()
{
  return;
};

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


//  -- END OF FILE --

