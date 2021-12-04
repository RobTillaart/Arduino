#pragma once
//
//    FILE: map2colour.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for mapping a float to colour spectrum
//     URL: https://github.com/RobTillaart/map2colour
//


#include "Arduino.h"

#define MAP2COLOUR_LIB_VERSION         (F("0.1.0"))


class map2colour
{
  public:
    map2colour();

    // values is an array of 7 values
    bool begin(float * values);

    uint32_t map2RGB(float value);

  private:
    float * _values;
    uint8_t _Red[7]   = { 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF };
    uint8_t _Green[7] = { 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF };
    uint8_t _Blue[7]  = { 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF };

};


// -- END OF FILE --


