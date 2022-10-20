#pragma once
//
//    FILE: map2colour.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: Arduino library for mapping a float to colour spectrum
//     URL: https://github.com/RobTillaart/map2colour
//


#include "Arduino.h"

#define MAP2COLOUR_LIB_VERSION          (F("0.1.5"))


//  https://www.w3.org/wiki/CSS/Properties/color/keywords
#define M2C_BLACK                       0x00000000
#define M2C_SILVER                      0x00C0C0C0
#define M2C_GRAY                        0x00808080
#define M2C_WHITE                       0x00FFFFFF
#define M2C_MAROON                      0x00800000
#define M2C_RED                         0x00FF0000
#define M2C_PURPLE                      0x00800080
#define M2C_FUCHSIA                     0x00FF00FF
#define M2C_GREEN                       0x00008000
#define M2C_LIME                        0x000FF000
#define M2C_OLIVE                       0x00808000
#define M2C_YELLOW                      0x00FFFF00
#define M2C_NAVY                        0x00000080
#define M2C_BLUE                        0x000000FF
#define M2C_TEAL                        0x00008080
#define M2C_AQUA                        0x0000FFFF


class map2colour
{
  public:
    map2colour();

    //  values is an array of 7 values in ascending order
    bool begin(float * values, uint32_t * colourMap = NULL);
    uint32_t map2RGB(float value);
    uint16_t map2_565(float value);

  protected:
    uint8_t _size = 7;
    float * _values;

    //  default colours, split up per channel for performance.
    uint8_t _Red[7]   = { 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF };
    uint8_t _Green[7] = { 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF };
    uint8_t _Blue[7]  = { 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF };
};


/////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS
//
//  FASTER + MORE RAM
//
class map2colourFast : public map2colour
{
  public:
    map2colourFast();
    //  values is an array of 7 values in ascending order
    bool begin(float * values, uint32_t * colourMap = NULL);
    uint32_t map2RGB(float value);
    uint16_t map2_565(float value);

  private:
    float divFactor[6];
};

// -- END OF FILE --

