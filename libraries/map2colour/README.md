
[![Arduino CI](https://github.com/RobTillaart/map2colour/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/map2colour/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/map2colour/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/map2colour/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/map2colour/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/map2colour/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/map2colour.svg?maxAge=3600)](https://github.com/RobTillaart/map2colour/releases)


# map2colour

Arduino library for mapping a float to colour spectrum


## Description

The map2colour library is used to make map a reading from a sensor, e.g. temperature or pressure, 
to a colour in the RGB spectrum. This can be used to colour an element on a graphical display, drive an RGB LED etc.

The initial release uses 7 floats values that describe the range being mapped. 
These are passed to the library with **begin()**. 
These 7 floats must be in ascending order and are mapped default on the following colour array.

```cpp
uint32_t colours[] = 
{
  // BLACK        RED         YELLOW      GREEN      AQUA        BLUE       WHITE
  0x00000000, 0x00FF0000, 0x00FFFF00, 0x0000FF00, 0x0000FFFF, 0x000000FF, 0x00FFFFFF
}
```

New values will be linear interpolated between two points when needed.

Assume you initialize a float array 
```cpp
float tempArray[] = { -10, -10, 5, 15, 30, 60, 125 };  // note the double -10
```
A temperature of 0°C will be mapped between the 2nd and 3rd element so 
between RED and YELLOW.  
A temperature between 60°C and 125°C will be mapped between BLUE and WHITE.


## Interface

- **map2colour()** constructor.
- **bool begin(float \* values, uint32_t \* colourMap = NULL)** load the array with **7** boundary values and
the associated array of **7** colours packed in uint32_t **0x00RRGGBB**. 
If the colour array is not given the last used (default) colour array is used.
**begin()** can be called multiple times to change the mapping.
- **uint32_t map2RGB(float value)** returns RGB colour packed in an uint32_t **0x00RRGGBB**.

Note: the arrays passed to **begin()** should both have at least 7 elements!

The colour array can be filled with decimal or HEX values or predefined colours can be used. See below.


## Predefined colours

Colours have the pattern **0x00RRGGBB**.


| define      | value      |
|:------------|:----------:|
| M2C_BLACK   | 0x00000000 |
| M2C_SILVER  | 0x00C0C0C0 |
| M2C_GRAY    | 0x00808080 |
| M2C_WHITE   | 0x00FFFFFF |
| M2C_MAROON  | 0x00800000 |
| M2C_RED     | 0x00FF0000 |
| M2C_PURPLE  | 0x00800080 |
| M2C_FUCHSIA | 0x00FF00FF |
| M2C_GREEN   | 0x00008000 |
| M2C_LIME    | 0x000FF000 |
| M2C_OLIVE   | 0x00808000 |
| M2C_YELLOW  | 0x00FFFF00 |
| M2C_NAVY    | 0x00000080 |
| M2C_BLUE    | 0x000000FF |
| M2C_TEAL    | 0x00008080 |
| M2C_AQUA    | 0x0000FFFF |


More colour definitions can be found e.g. https://www.w3.org/wiki/CSS/Properties/color/keywords


## Operation

See examples.


## Future

- update documentation
- investigate performance
- **uint16_t map2_565(float value)** 
  - wrapper around RGB uses less memory and is expected slower)
- add examples
- seven "fixed" points is that flex enough?
- PROGMEM for default array

