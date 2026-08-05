#pragma once
//
//    FILE: DEVNULL.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.9
//    DATE: 2020-06-23
// PURPOSE: Arduino library for a /dev/null stream - useful for testing
//     URL: https://github.com/RobTillaart/DEVNULL


#include "Arduino.h"

#define DEVNULL_LIB_VERSION     (F("0.1.9"))

//  allows command line overrule
//  or comment or set to zero
#ifndef DEVNULL_ENABLE_DEBUG
#define DEVNULL_ENABLE_DEBUG    1
#endif


class DEVNULL : public Stream
{
public:
  DEVNULL();

  int    available();
  int    peek();
  int    read();
  void   flush();  //  placeholder to keep CI happy

  size_t write(const uint8_t data);
  size_t write( const uint8_t *buffer, size_t size);

#if defined(DEVNULL_ENABLE_DEBUG) && DEVNULL_ENABLE_DEBUG
  int    lastByte();
#endif

private:
#if defined(DEVNULL_ENABLE_DEBUG) && DEVNULL_ENABLE_DEBUG
  uint8_t  _bottomLessPit;
#endif
};


//  -- END OF FILE --

