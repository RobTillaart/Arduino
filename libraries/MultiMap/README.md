
[![Arduino CI](https://github.com/RobTillaart/MultiMap/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MultiMap/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MultiMap/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MultiMap/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MultiMap/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MultiMap/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MultiMap.svg?maxAge=3600)](https://github.com/RobTillaart/MultiMap/releases)


# MultiMap

Arduino library for fast non-linear mapping or interpolation of values


## Description

In Arduino applications often the value of a sensor is mapped upon a more
usable value. E.g. the value of analogRead() is mapped onto 0 .. 5.0 Volt.
This is done by the map function which does a linear interpolation. 
This means in code:

```cpp
    output = C1 + input * C2
```

As C1 and C2 are to be calculated Arduino has the **map()** that calculates the 
two variables runtime from two given mappings.

```cpp
    output = map(input, I1, I2, O1, O2):
```

In many cases when there is no linear mapping possible, as the 'points' are not on a single straight line.
One needs non-linear math to calculate the output, **Multimap()** just simulates that.

**out = Multimap(value, input, output, size)** needs two equal sized arrays of reference 'points', 
**input\[\]** and **output\[\]**, it looks up the 
input value in the input\[\] array and if needed it linear interpolates between two
points of the output\[\] array. 

- The **input\[\]** array must have increasing values, 
there is no such restriction for the **output\[\]** array.
- **Multimap()** automatically constrains the output to the first and last value in the **output\[\]** array.


## Operation

See examples

Please note the fail example as this shows that in the intern math overflow can happen.


## Future

#### must
- improve documentation

#### should
- Investigate class implementation 
  - performance / footprint
  - less parameter passing
  
#### could
- flag if input value was "IN_MIN" <  input < "IN_MAX", 
  now it is constrained without user being informed.
- extend unit tests

#### wont
- should the lookup tables be merged into one array of pairs?
  - you cannot reuse e.g. the input array then. (memory footprint)

