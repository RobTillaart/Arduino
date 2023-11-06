
[![Arduino CI](https://github.com/RobTillaart/map2colour/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/map2colour/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/map2colour/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/map2colour/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/map2colour/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/map2colour.svg)](https://github.com/RobTillaart/map2colour/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/map2colour/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/map2colour.svg?maxAge=3600)](https://github.com/RobTillaart/map2colour/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/map2colour.svg)](https://registry.platformio.org/libraries/robtillaart/map2colour)


# map2colour

Arduino library for mapping a float to a colour spectrum.


## Description

The map2colour library is used to map a float value to a colour in the RGB spectrum.
The float value can be the result of a calculation or read from a sensor, 
e.g. temperature, humidity, light, distance, direction or pressure. 

This function can be used to colour an element on a graphical display,
drive an RGB LED, or a LED string etc to indicate some sort of state visually.

The first releases used a fixed number of 7 floats values that describe the range being mapped.
With version 0.2.0 one can define the size as a parameter of the constructor.
There is no limit (except RAM) in theory, but in practice 16 or 32 entries is a lot.

A lookup array of float values is passed to the library with **begin()**.
These floats must be in **non-decreasing** order and are mapped default on the following colour array.

```cpp
uint32_t colours[] =
{
  // M2C_BLACK  M2C_RED   M2C_YELLOW   M2C_LIME   M2C_AQUA    M2C_BLUE    M2C_WHITE
  0x00000000, 0x00FF0000, 0x00FFFF00, 0x0000FF00, 0x0000FFFF, 0x000000FF, 0x00FFFFFF
}
```

New values will be linear interpolated between two points when needed.

Assume you initialize a float value array indicating temperature Celsius levels.

```cpp
float tempArray[] = { -20, -10, 5, 15, 30, 60, 125 };
```

A temperature of 0°C will be between the 2nd and 3rd value so it will be mapped 
between the 2nd and 3rd element colour so between M2C_RED and M2C_YELLOW.
Similarly any temperature between 60°C and 125°C will be mapped between M2C_BLUE and M2C_WHITE.

**begin()** allows one to overrule the values and the colours array with arrays of your choice.
Adjusting the colour array allows one to use a "full spectrum" like the default or only 
interpolate between two colours. 
Note the library has several colours predefined in **m2c_colours.h** as constants to make the 
colour table and therefore the code more readable. 
If colours are missing please make a PullRequest (preferred) or file an issue.

**begin()** returns true if the array of values is in non-decreasing order, false otherwise.
If returned false the code might behave in unexpected ways.

Please note that the colourMap can have duplicate entries even side by side.


#### Related

- https://github.com/RobTillaart/Kelvin2RGB
- https://github.com/RobTillaart/map2colour


## Interface

```cpp
#include "map2colour.h"
```

#### Functions

- **map2colour(uint8_t size = 7)** constructor, default size 7 to be backwards compatible.
- **~map2colour()** destructor.
- **map2colourFast(uint8_t size = 7)** constructor, (larger code base, more RAM and faster)
- **~map2colourFast()** destructor.
- **uint8_t size()** returns the size of the arrays needed (== parameter of constructor).
- **bool begin(float \* values, uint32_t \* colourMap = NULL)** load the array with **size** 
boundary values and the associated array of **size** colours packed in uint32_t **0x00RRGGBB**.
If the colour array is not given the last given (or the default) colour array is used.
**begin()** can be called multiple times to change the mapping.
The function returns false if the array of values is not in non-decreasing order.
- **uint32_t map2RGB(float value)** returns RGB colour packed in an uint32_t **0x00RRGGBB**.  
If the value is out of range of the original values array, the value is always mapped upon the 
first or last colour.
- **uint16_t map2_565(float value)** often used 16 bit colour format. 
Currently a wrapper around **map2RGB**.

Note: the arrays passed to **begin()** should both have **size** elements!

The colour array can be filled with decimal or HEX values or predefined colours can be used.
See below.


## Predefined colours

Colours are represented as 32 bit .RGB values and have the pattern **0x00RRGGBB**.

In the file **m2c_colours.h** a number of colours are predefined.


|  define       |  value       |  define      |  value       |
|:--------------|:------------:|:-------------|:------------:|
|  M2C_BLACK    |  0x00000000  |  M2C_GREEN   |  0x00008000  |
|  M2C_SILVER   |  0x00C0C0C0  |  M2C_LIME    |  0x000FF000  |
|  M2C_GRAY     |  0x00808080  |  M2C_OLIVE   |  0x00808000  |
|  M2C_WHITE    |  0x00FFFFFF  |  M2C_YELLOW  |  0x00FFFF00  |
|  M2C_MAROON   |  0x00800000  |  M2C_NAVY    |  0x00000080  |
|  M2C_RED      |  0x00FF0000  |  M2C_BLUE    |  0x000000FF  |
|  M2C_PURPLE   |  0x00800080  |  M2C_TEAL    |  0x00008080  |
|  M2C_FUCHSIA  |  0x00FF00FF  |  M2C_AQUA    |  0x0000FFFF  |


Besides these colours, the file contains also GRAY-scale VALUES M2C_GRAY_0 .. M2C_GRAY_16.

More colour definitions can be found on the internet 
e.g. https://www.w3.org/wiki/CSS/Properties/color/keywords

Note that only 3 bytes of 4 of the 32 bit colour patterns are used.
The 4th byte might be used in the future.


## Operation

See examples.

By changing the colour map one can get different effects. 
The minimum to implement is an intensity effect going e.g. from black towards a colour at max intensity. 
For this effect only two values are significant, however one must provide full size arrays.

```cpp
float values[7] =     { -200,      200,       200, 200, 200, 200, 200, };
uint32_t colours[7] = { M2C_BLACK, M2C_RED,   0, 0, 0, 0, 0};
```

Note that the above colour scheme maps all colokrs above 200 to BLACK (0).

Another interesting colour scheme could be a symmetric one.
This could indicate 25 as an optimal value (GREEN).

```cpp
float values[5] =     { -50,        -25,     0,          25,        50,        75,      100};
uint32_t colours[5] = { M2C_BLACK, M2C_RED, M2C_YELLOW, M2C_GREEN, M2C_YELLOW, M2C_RED, M2C_BLACK};
```

More complex colour schemes are possible, up to **size** different colours.


#### Non-decreasing array

(experimental in 0.1.5)
If you create a non-decreasing array of values one can create a break in the colour gradient. 
See example.

```cpp
float values[7] =     { -200,     -90,      0,        45,               45,     150,         180 };
uint32_t colours[7] = { M2C_BLUE, M2C_AQUA, M2C_LIME, M2C_YELLOW,       M2C_RED, M2C_YELLOW, M2C_BLUE};
```

With **45** occurring twice in the values array above there would be no interpolation or colour gradient 
between the **M2C_YELLOW** and **M2C_RED** effectively resulting in 2 continuous gradients.

A slightly less hard edge could be made by changing the second 45 to 46 or 47, 
so there is a small area with a very steep gradient. 

Note: Since 0.2.0 **begin()** will accept a non-decreasing value array and return true.
This was false in 0.1.5.


## Performance

Indicative performance figures measured with the performance example.
Performance depends on colours chosen, platform etc.

Note: time in microseconds
Note: UNO at 16 MHz, ESP32 at 240 MHz


#### version 0.1.2

|  function call           |  time UNO   |  time ESP32  |
|:-------------------------|------------:|-------------:|
|  begin(values)           |  4          |   4          |
|  begin(values, colours)  |  12         |   4          |
|  map2RGB(value)          |  124 - 152  |   2 - 4      |
|  map2_565(value)         |  124 - 168  |   2 - 4      |


#### version 0.1.3

|  function call           |  time UNO   |  time ESP32  |
|:-------------------------|------------:|-------------:|
|  begin(values)           |   4         |   4          |
|  begin(values, colours)  |   12        |   4          |
|  map2RGB(value)          |   64 - 132  |   2 - 3      |
|  map2_565(value)         |   68 - 140  |   2 - 3      |


#### version 0.1.4

map2colourFast.

|  function call           |  time UNO   |  time ESP32  |  notes                  |
|:-------------------------|------------:|-------------:|:------------------------|
|  begin(values)           |   284       |   15         |  unexpected peak ESP32  |
|  begin(values, colours)  |   304       |   6          |
|  map2RGB(value)          |   40 - 104  |   1 - 2      |
|  map2_565(value)         |   44 - 112  |   1 - 2      |


#### optimization 0.1.4

One performance optimization (trade memory for speed) is replacing the float division 
in map2RGB by a multiplication. 
This optimization is implemented as a derived class **map2colourFast** in version 0.1.4.

This requires (size x 4) bytes RAM to hold the \[size] factors and some ~100 bytes 
of PROGMEM for the calculation of the dividers in **begin()**.
The **map2RGB()** call is about 40 % faster compared to the original 0.1.2.
Although the **begin()** call is ~300 us longer, it only takes a dozen **map2RGB()** calls to break even.

Note: the gain for the ESP32 is less pronounced, but can still be interesting.


#### version 0.2.0

map2colourFast, slightly slower compared to 0.1.4.
Note that the larger the size the more time it takes to find the correct interval for the value.

|  function call           |  time UNO   |  time ESP32  |
|:-------------------------|------------:|-------------:|
|  begin(values)           |   316       |    22        |
|  begin(values, colours)  |   332       |    7         |
|  map2RGB(value)          |   48 - 116  |    1 - 2     |
|  map2_565(value)         |   52 - 120  |    1 - 2     |


## Future

#### Must

- update documentation

#### Should

- look for optimizations.
  - cache last value?

#### Could

- create a memory efficient version 
  - keep a pointer to the colour array.
  - split RGB channels for every mapping.
  - is this useful? only for smallest RAM devices.
- remove default array and break backwards compatibility.
- rename **map2_565()** to **map2RGB565()**
- add **map2CMYK()**


#### Wont

- **uint32_t dumpColourMap()** ==> not needed
- PROGMEM for default array? ==> slower, AVR specific.
- move up the test for non-increase in **begin()** ==> fail fast.
  - conflicts with begin of fast version.
  - user responsibility.
- could a 4th (alpha) channel be enabled?
  - not needed yet, would need new constants
- faster 16 bit 565 version?
  - only on request as a separate class map2colour565.
- map2HSL() as extra colour space.
  - not seen much HSL displays in "Arduino" world
  - separate converter solves this.
- add **reset()** for default array? 
  - takes too much RAM.
- improve the constructor
  - add **splitColorMap()**
  - only done once so too little gain.
- map2RGB variant that gives a colour as the delta with the previous value.
  - user can do that fairly easy => example
- add 3rd param size to **begin()** to allow smaller arrays?
  - suppose you allocate size = 20 and want to use only 5 entries.
  - create a new object.
- **bool adjustColour(uint8_t index, uint32_t RGB)**    
  - single colour adjustment
  - returns false if index out of range.
  - faster than calling **begin()**.
  - divfactors need to be calculated again?
  - see no real use case.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
