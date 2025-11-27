
[![Arduino CI](https://github.com/RobTillaart/map2bits/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/map2bits/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/map2bits/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/map2bits/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/map2bits/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/map2bits.svg)](https://github.com/RobTillaart/map2bits/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/map2bits/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/map2bits.svg?maxAge=3600)](https://github.com/RobTillaart/map2bits/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/map2bits.svg)](https://registry.platformio.org/libraries/robtillaart/map2bits)


# map2bits

Arduino library for mapping a float to a number of bits.


## Description

**Experimental**

Map2bits is an experimental library which can be used to map a float 
value to a number of HIGH bits in an 32 bits integer.
The float value can be the result of a calculation or measurement from a 
sensor, e.g. temperature, humidity, light, distance, direction or pressure. 

**map2bits** is developed to drive a led bar like this one.
https://www.tinytronics.nl/shop/nl/displays/segmenten/led-bar-10x-rood
typical in combination with a PCF8575 or a MCP23017.
These are used for displaying e.g. audio volume, current level, temperature 
etc in a visual way.

Another application might be to control multiple pumps in a row to pump 
water from a pit. 
Depending on the level of the water more pumps need to be switched on.

In short many devices to drive or applications to think of.

As always, feedback is welcome.


### Related

Other mapping libraries

- https://github.com/RobTillaart/FastMap
- https://github.com/RobTillaart/Gamma
- https://github.com/RobTillaart/map2bits
- https://github.com/RobTillaart/map2colour
- https://github.com/RobTillaart/moduloMap
- https://github.com/RobTillaart/MultiMap


## Interface

```cpp
#include "map2bits.h"
```

### Constructor

- **map2bits()** Constructor, defines a default mapping of (0..100 => 10)
- **uint8_t init(float in_min, float in_max, uint32_t bits)** defines the mapping
input range and how many bits output should be generated.

### Mapping

The output of the **map()** functions is a bit mask and can be used to drive e.g. a led bar etc.

- **uint32_t map(float value)** maps value to an uint32_t with the appropriate 
number of bits set. These are constrained by the number of bits set in **init()**.
- **uint16_t map16(float value)** maps value to an uint16_t with the appropriate 
number of bits set. These are constrained by the number of bits set in **init()**.
Slightly faster (~2.5%).
- **uint32_t map32(float value)** equals map().
- **uint64_t map64(float value)** maps value to an uint64_t with the appropriate 
number of bits set. These are constrained by the number of bits set in **init()**.
Typical only used if one wants more than 32 bits.


## Operation

Suppose you have the following code 
```
mb.init(0, 100, 10);
                       //      (binary)
x = mb.map(64);        //  x =     111111 ==>  6 bits set, interpolated
x = mb.map(99);        //  x = 1111111111 ==> 10 bits set, interpolated
x = mb.map(4);         //  x =          0 ==>  0 bits set, interpolated
x = mb.map(-10);       //  x =          0 ==>  0 bits set, constrained
x = mb.map(1000);      //  x = 1111111111 ==> 10 bits set, constrained
```

See examples.


## Performance

Indicative performance measured with the **map2bits_performance.ino** example.
Performance depends on input chosen, platform support of float, and if
values are constrained (out range) or interpolated (in range).
Run tests on your own board to get the numbers.

Note: times in microseconds per call  
Note: UNO at 16 MHz, ESP32 at 240 MHz  
Note: out of range == 33% in range, 66% out range  
Note: map() == map32()

|  board   |  function  |  in range  |  out range  |  notes  |
|:--------:|:----------:|:----------:|:-----------:|:--------|
|  UNO R3  |    map16   |    45.22   |     22.08   |
|  UNO R3  |    map32   |    46.28   |     22.49   |
|  UNO R3  |    map64   |    49.00   |     23.60   |  for > 32 bits
|          |            |            |             |
|   ESP32  |    map16   |     0.42   |      0.24   |
|   ESP32  |    map32   |     0.41   |      0.23   |
|   ESP32  |    map64   |     0.52   |      0.33   |  for > 32 bits


## Polarity

The user can swap polarity by inverting with ~ 

```cpp
x = ~mb.map(42);            //   x = 0xFFFFFFF0  => 
x = ~mb.map(42) & 0xFFFF    //   x = 0x0000FFF0 optional mask.
```


## Future

#### Must

- update documentation
- test ESP32

#### Should

- add examples / applications
- investigate optimize
  - do we need map16() => optimizer does clean up.

#### Could

- map logarithmic  (map exponent)
- MSB/LSB   00000011 <> 0000110000 ?  (SIZE = 6)
  - reverse from CRC library

#### Wont

- map2DAC? 
  - maps a range to analogWrite()..
  - separate class. 
- polarity  0001 <> 1110 ?
  - ~operator
- map16(uint32_t) map32(uint32_t) map64(uint32_t) => accuracy float is sufficient
- map2bitsDouble(value), map2bitsDouble64(value) Double version (input range + precision)

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
