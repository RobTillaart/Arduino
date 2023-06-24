
[![Arduino CI](https://github.com/RobTillaart/MultiMap/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MultiMap/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MultiMap/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MultiMap/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MultiMap/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MultiMap/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MultiMap.svg?maxAge=3600)](https://github.com/RobTillaart/MultiMap/releases)


# MultiMap

Arduino library for fast non-linear mapping or interpolation of values.


## Description

In Arduino applications often the 'raw' value of a sensor is mapped upon a more
usable value. E.g. the value of analogRead() 0 .. 1023 is mapped onto 0 .. 5.0 Volt.
This is often done by the map function which does a linear interpolation.

This means in code:

```cpp
    output = C1 + input * C2
```

As C1 and C2 are to be determined, Arduino has the **map()** function that calculates the 
two variables runtime from two given mapping points (I1, O1) and (I2, O2).

```cpp
    output = map(input, I1, I2, O1, O2):
```

In many cases when there is no linear mapping possible as the 'points' are not on a single straight line.
To solve this one needs non-linear math to calculate the output.

The **multiMap()** function simulates this math by approximating the non-linear function with multiple
linear line segments. 
Of course this approximation introduces an error. 
By increasing the number of points and choose their position strategically the average error will be reduced.

Note: some functions are hard to approximate with multiMap as they go to infinity or have a singularity.
Think of **tan(x)** around x = PI/2 (90°) or **sin(1/x)** around zero.


#### Usage

The basic call for **multiMap()** is:

```cpp
output = Multimap<datatype>(input, inputArray, outputArray, size);
```

**multiMap()** needs two equally sized arrays representing the reference 'points' named 
**inputArray\[\]** and **outputArray\[\]** both of the **datatype**.

**multiMap()** will do a lookup of the input value in the inputArray\[\].
If it cannot find the index of an exact point it will determine a weighted position between two points.
This optional weighted point is used to interpolate a value from data in the output\[\] array.

- The **inputArray\[\]** must have increasing values, 
there is no such restriction for the **output\[\]** array.
- The values of the **inputArray\[\]** do not need to have the same distance (non-equidistant).
E.g an array like { 1, 10, 100, 1000 } is valid.
- **multiMap()** automatically constrains the output to the first and last value in the **output\[\]** array.
This is a explicit difference with the **map()** function.
Therefore it is important to extend the range of the arrays to cover all possible values.


#### Performance

**multiMap()** does a linear search for the inputValue in the inputArray.
This implies that usage of larger and more precise arrays will take more time.
Furthermore "low" input values will be found faster than "high" values.

As every usage of multiMap() is unique one should always do a performance check to see
if there is a substantial gain in the case at hand. In my experience there often is.


#### MultiMapBS

Experimental 0.1.7 => use with care.

**multiMapBS()** MMBS for short, is a very similar function as **multiMap()**.
The main difference is that MMBS uses binary search instead of linear search.

First performance tests indicate that for array sizes about 10 MMBS is on par
with **multiMap()**. This is expected as both need on average about 5 steps 
to find the right interval.

Be sure to do your own tests to see if MMBS improves your performance.


#### MultiMapCache

Experimental 0.1.7 => use with care.

**multiMapCache()** MMC for short, is a very similar function as **multiMap()**.
The main difference is that MMC caches the last input and output value.
The goal is to improve the performance by preventing 

If the input sequence has a lot of repeating values e.g. 2 2 2 2 2 2 5 5 5 5 5 4 4 4 4 2 2 2 2 2 2
MMC will be able to return the value from cache often. 
Otherwise keeping cache is overhead.

Be sure to do your own tests to see if MMC improves your performance.


#### Related

Other mapping libraries 

- https://github.com/RobTillaart/FastMap
- https://github.com/RobTillaart/Gamma
- https://github.com/RobTillaart/map2colour
- https://github.com/RobTillaart/moduloMap
- https://github.com/RobTillaart/MultiMap


## Operation

See examples

Please note the fail example as this shows that in the intern math overflow can happen.


## Future

#### Must

- improve documentation


#### Should

- investigate multiMapCache behaviour
  - determine overhead.
- investigate binary search multiMapBS behaviour
  - expect a constant time
  - where is the tipping point between linear and binary search.
    (expect around size = 8)
- extend unit tests


#### Could

- Investigate class implementation
  - basic call out = mm.map(value);
  - runtime adjusting input and output array **begin(in[], out[])**
  - performance / footprint
  - less parameter passing
  - **isInRange(value)**?
  - caching last value / position / index (does that help?)
  - flag if input value was "IN_MIN" <  input < "IN_MAX", 
    now it is constrained without user being informed.
- Investigate a 2D multiMap e.g. for complex numbers?
  - is it possible / feasible?
- data type input array does not need to be equal to the output array.
  - template<typename T1, typename T2>
    ```T2 multiMapBS(T1 value, T1* _in, T2* _out, uint16_t size)```


#### Wont

- should the lookup tables be merged into one array of pairs?
  - you cannot reuse e.g. the input array or the output array then. 
    this would not improve the memory footprint.

