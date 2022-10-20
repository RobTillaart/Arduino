
[![Arduino CI](https://github.com/RobTillaart/map2colour/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/map2colour/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/map2colour/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/map2colour/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/map2colour/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/map2colour/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/map2colour.svg?maxAge=3600)](https://github.com/RobTillaart/map2colour/releases)


# map2colour

Arduino library for mapping a float to colour spectrum.


## Description

The map2colour library is used to make map a reading from a sensor, e.g. temperature or pressure,
to a colour in the RGB spectrum. This can be used to colour an element on a graphical display, drive an RGB LED, or even a LED string etc.

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
float tempArray[] = { -20, -10, 5, 15, 30, 60, 125 };
```
A temperature of 0°C will be mapped between the 2nd and 3rd element so
between RED and YELLOW.
A temperature between 60°C and 125°C will be mapped between BLUE and WHITE.

**begin()** also allows one to overrule the colours array with a colour array of your choice.
Adjusting the colour array allows one to use a "full spectrum" like the default or only 
interpolate between two colours. Note the library has several colours predefined as constant
to make the colour table (and the code) more readable. If colours are missing please make a 
PullRequest (preferred) or file an issue.

**begin()** returns false if the array of values is not in increasing order, true otherwise.
If returned false the code might behave in unexpected ways.


## Interface

- **map2colour()** constructor.
- **map2colourFast()** constructor, (larger code base, more RAM and faster)
- **bool begin(float \* values, uint32_t \* colourMap = NULL)** load the array with **7** 
boundary values and the associated array of **7** colours packed in uint32_t **0x00RRGGBB**.
If the colour array is not given the last given (or the default) colour array is used.
**begin()** can be called multiple times to change the mapping.
The function returns false if the array of values is not in increasing order.
- **uint32_t map2RGB(float value)** returns RGB colour packed in an uint32_t **0x00RRGGBB**.  
If the value is out of range of the original values array, the value is always mapped upon the first colour.
- **uint16_t map2_565(float value)** often used 16 bit colour format. Currently a wrapper around **map2RGB**.

Note: the arrays passed to **begin()** should both have at least 7 elements!

The colour array can be filled with decimal or HEX values or predefined colours can be used. See below.


## Predefined colours

Colours are represented as 24 bit RGB values and have the pattern **0x00RRGGBB**.


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


More colour definitions can be found on the internet 
e.g. https://www.w3.org/wiki/CSS/Properties/color/keywords


## Operation

See examples.

By changing the colour map one can get different effects. 
The minimum to implement is an intensity effect going from black towards a colour at max intensity. 
More complex colour schemes are possible, up to 7 different colours. 
This number 7 is hardcoded (for now) and that might change in the future.

#### Experimental in 0.1.5

(was planned for 0.2.0)
If you create a non-decreasing array of values one can create a break in the gradient. See example.

```cpp
float values[7] = { -200, -90, 0, 45,                                   45, 150, 180 };
uint32_t colours[7] = { M2C_BLUE, M2C_AQUA, M2C_LIME, M2C_YELLOW,       M2C_RED, M2C_YELLOW, M2C_BLUE};
```

with the double 45 in the values array there would be no gradient between the **M2C_YELLOW** and **M2C_RED**
effectively having 2 continuous gradients.

Note: **begin()** will report such array as false.


## Performance

Indicative performance figures measured with performance example.
Performance depends on colours chosen, platform etc.


#### version 0.1.2

| function call          | time us UNO | time us ESP32 |
|:-----------------------|------------:|--------------:|
| begin(values)          | 4           | 4             |
| begin(values, colours) | 12          | 4             |
| map2RGB(value)         | 124 - 152   | 2 - 4         |
| map2_565(value)        | 124 - 168   | 2 - 4         |


#### version 0.1.3

| function call          | time us UNO | time us ESP32 |
|:-----------------------|------------:|--------------:|
| begin(values)          | 4           | 4             |
| begin(values, colours) | 12          | 4             |
| map2RGB(value)         | 64 - 132    | 2 - 3         |
| map2_565(value)        | 68 - 140    | 2 - 3         |


#### version 0.1.4

| function call          | time us UNO | time us ESP32 | notes                 |
|:-----------------------|------------:|--------------:|:----------------------|
| begin(values)          | 284         | 15            | unexpected peak ESP32 |
| begin(values, colours) | 304         | 6             |
| map2RGB(value)         | 40 - 104    | 1 - 2         |
| map2_565(value)        | 44 - 112    | 1 - 2         |


Note: UNO at 16 MHz, ESP32 at 240 MHz


#### optimization 0.1.4

One performance optimization (trade memory for speed) is replacing the float division 
in map2RGB by a multiplication. 
This requires 24 bytes RAM to hold the 6 factors and ~100 bytes of PROGMEM for the 
calculation of the dividers in begin(). 
This optimization is implemented as a derived class **map2colourFast** in version 0.1.4.
The **map2RGB()** call is about 40 % faster compared to the original 0.1.2.
Although the **begin()** call is ~300 us longer, it only takes a dozen **map2RGB()** calls to break even.

Note: the gain for the ESP32 is less pronounced, but can still be interesting.


## Future

#### must
- update documentation

#### should
- redo **begin()** of map2colour to allow all values. (0.2.0)
  - non-decreasing array (already experimental in 0.1.5, will still return false! )
  - any array of numbers.  (return value will always be true then)
- look for optimizations.
  - cache last value?

#### could
- make size configurable ?
- **void adjustColour(uint8_t index, uint32_t RGB)**    
  - single colour adjust
  - faster than calling begin() again
- map2RGB variant that gives a colour to the delta with previous value
  - user can do that fairly easy => example
- map2HSL() as extra colour space.
- add **reset()** for default array? (RAM)

#### wont
- **uint32_t dumpColourMap()** ==> not needed
- PROGMEM for default array? ==> slower, AVR specific.
- move up the test for non-increase in **begin()** ==> fail fast.
  - conflicts with begin of fast version.


