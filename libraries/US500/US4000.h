#pragma once
//
//    FILE: US4000.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-29
// VERSION: see US500.h
// PURPOSE: Arduino library for US500 and US4000 underwater distance sensor.
//     URL: https://github.com/RobTillaart/US500


#include "US500.h"

#define US4000_LIB_VERSION         (US500_LIB_VERSION)


//  ERROR CODES US4000
//  values < 0 are errors.
constexpr int US4000_CMD_ERROR = -1;
constexpr int US4000_CRC_ERROR = -2;
constexpr int US4000_TIMEOUT_ERROR = -3;

class US4000 : public US500
{
public:
  US4000(Stream * str) : US500(str)
  {
    _address = 0x000A;
  }

  // int setMaxDistance(uint16_t distance) { return (distance > 0); };  //  not supported => stub...
};


//  -- END OF FILE --





