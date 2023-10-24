#pragma once
//
//    FILE: DEVNULL.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
// PURPOSE: Arduino library for a /dev/null stream - useful for testing
//     URL: https://github.com/RobTillaart/DEVNULL


#include "Arduino.h"

#define DEVNULL_LIB_VERSION     (F("0.1.6"))


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

  int    lastByte();

private:
  uint8_t  _bottomLessPit;
};


//  -- END OF FILE --

