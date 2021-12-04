
[![Arduino CI](https://github.com/RobTillaart/map2colour/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/map2colour/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/map2colour/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/map2colour/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/map2colour/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/map2colour/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/map2colour.svg?maxAge=3600)](https://github.com/RobTillaart/map2colour/releases)


# map2colour

Arduino library for mapping a float to colour spectrum


## Description

The map2colour library is used to make map a reading from a sensor, e.g. temperature or pressure, 
to a colour in the RGB spectrum. 

The initial release uses 7 floats values that describe the range being mapped. 
These are passed to the library with **begin()**. 
These 7 floats must be in ascending order and are mapped upon the following colour array.

```cpp
uint32_t colours[] = 
{
  // BLACK        RED         YELLOW      GREEN       ??         BLUE       WHITE
  0x00000000, 0x00FF0000, 0x00FFFF00, 0x0000FF00, 0x0000FFFF, 0x000000FF, 0x00FFFFFF
}
```

New values will be linear interpolated between the two points when needed.

Assume you initialize a float array 
```cpp
float tempArray[] = { -10, -10, 5, 15, 30, 60, 125 };  // note the double -10
```
A temperature of 0°C will be mapped between the 2nd and 3rd element so somewhere 
between RED and YELLOW. 
A temperature between 60°C and 125°C will be mapped between BLUE and WHITE.

This first version is to get hands on experience, a later version should 
support user defined colour maps. 


## Interface

- **map2colour()** constructor.
- **bool begin(float \* ar)** load the array with 7 boundaries.
- **uint32_t map2RGB(float value)** returns RGB colour packed in an uint32_t. **0x00RRGGBB**


## Operation

See examples.


## Future

- update documentation

**0.2.0** thoughts
- make the colour map user defined - like multi-map
  - between BLACK and a single colour. - intensity
  - between a number of colours e.g. RED YELLOW GREEN or GREEN YELLOW RED 
  - fixed number of points is flex enough
- example with double entries
  - temp -10,    5,     10,     30,    35,    60,  120
  -       Red  yellow  black   black  yellow  red  red 
  - middle area 10..30 has no colour.
