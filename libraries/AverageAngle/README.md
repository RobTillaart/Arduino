
[![Arduino CI](https://github.com/RobTillaart/AverageAngle/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AverageAngle/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AverageAngle/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AverageAngle/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AverageAngle/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AverageAngle.svg)](https://github.com/RobTillaart/AverageAngle/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AverageAngle/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AverageAngle.svg?maxAge=3600)](https://github.com/RobTillaart/AverageAngle/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AverageAngle.svg)](https://registry.platformio.org/libraries/robtillaart/AverageAngle)


# AverageAngle

Arduino library to calculate correctly the average of multiple angles.


## Description

AverageAngle is a class to calculate the average of angles.

This is especially useful when angles are around 0 degrees, 
e.g. from a compass sensor or the resultant of a track.
Example, the average angle of 359 and 1 is 0, not 179 (most of the time)

Furthermore the AverageAngle can also include the **length (weight)** of the angle as if it is a vector. 
Default this length is set to 1 so all angles are by default of equal weight.

Example: The average angle of 359 (length = 2) and 1 (length = 1) is 359.something not zero.

The average angle is calculated by converting the added angle (in DEGREES, etc) to polar coordinates.
These (x,y) are added to a (sumX, sumY) and divided by the number of angles added so far. 

As always, feedback is welcome.


### Related

- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/AngleConvertor
- https://github.com/RobTillaart/AverageAngle
- https://github.com/RobTillaart/runningAngle


### AngleType

- **enum AngleType { DEGREES, RADIANS, GRADIANS }** idem. 

|  value  |  name      |  range     |  notes  |
|:-------:|:-----------|:----------:|:--------|
|    0    |  DEGREES   |  0 .. 360  |
|    1    |  RADIANS   |  0 .. 2PI  |
|    2    |  GRADIANS  |  0 .. 400  |  100 GRADIANS == 90 DEGREES.


For lesser known angle-types, see - https://github.com/RobTillaart/AngleConvertor


## Interface

```cpp
#include "AverageAngle.h"
```

### Constructor

- **AverageAngle(AngleType type = DEGREES)** constructor, defaults to degrees.
- **AngleType type()** returns DEGREES, RADIANS or GRADIANS.
- **void setType(AngleType type)** changes type DEGREES, RADIANS or GRADIANS.
Type can be changed runtime and still continue to add.
- **void reset()** clears internal counters.


### Core

- **uint32_t add(float alpha, float length = 1.0)** add a new angle, 
optional with length other than 1. 
Returns the number of elements added so far (count).
If the internal sumX or sumY is >= 10000, the error **AVERAGE_ANGLE_OVERFLOW** is set. 
This indicates that the internal math is near or over its accuracy limits.
- **uint32_t count()** the number of angles added.
If count == 0, there is no average.
- **float getAverage()** returns the average, unless count == 0
or if the internal sums == (0,0) in which case we have a singularity ==> NAN (not a number)
If NAN the error **AVERAGE_ANGLE_SINGULARITY** is set. 
- **float getTotalLength()** the length of the resulting 'angle' when we see them as vectors.
If count == 0 the total length is set to 0.
- **float getAverageLength()** returns the average length of the angles added.
If count == 0 the average length is set to 0.
- **float getSumX()** get internal sumX counter. Rectangular coordinates.
- **float getSumY()** get internal sumY counter. Rectangular coordinates.


### Error handling

- **int lastError()**  return the last error detected.

|  name                       |  value  |
|:----------------------------|:-------:|
|  AVERAGE_ANGLE_OK           |   0     |
|  AVERAGE_ANGLE_OVERFLOW     |  -10    |
|  AVERAGE_ANGLE_SINGULARITY  |  -20    |


### Experimental Overflow

(since 0.2.0)

When the internal sumx or sumy is large (> 10000) the accuracy of the addition
becomes critical, leading to serious errors in the average and length functions.
To detect this the function **add()** sets the error **AVERAGE_ANGLE_OVERFLOW**.
This error can be checked with **lastError()**.
The function **add()** will add the new angle as good as possible.

Note this condition is independent of the **AngleType** as the internal math 
uses radians. The condition will be triggered faster when the length parameter 
is used. 

The overflow threshold of 10000 can be adjusted in the AverageAngle.cpp file if needed.

As this feature is **experimental**, the trigger condition for overflow will 
probably be redesigned in the future. See future section below.


## Gradians

Gradians a.k.a. **gon**, is a less often used unit for angles. 
There are 100 gradians in a right angle. A full circle = 400 gradians.

- https://en.wikipedia.org/wiki/Gradian

Other less used units for measuring angles:
- https://github.com/RobTillaart/AngleConvertor


## Operation

If you want to average 5 compass readings you can just add the angles and 
do not use the length parameter.
```cpp
  AA.reset();
  for (int i = 0; i < 5; i++)
  {
    AA.add(compass.readHeading());
    delay(100);    // e.g. compass read needs some time
  }
  Serial.println(AA.getAverage());
```


If you want to average a track, e.g. 5 steps North, 3 steps west etc, 
you need to include the length of each step.
```cpp
  AA.reset();
  AA.add(90, 5);     //  5 steps north  assuming east = 0
  AA.add(180, 3);    //  3 steps west
  Serial.println(AA.getAverage());
  Serial.println(AA.getTotalLength());
```


If you want to average an angle in DEGREES and an angle in RADIANS,
just change the type runtime.
```cpp
  AA.reset();
  AA.setType(DEGREES);
  AA.add(90);
  AA.setType(RADIANS);
  AA.add(PI/3);
  AA.setType(DEGREES);
  Serial.println(AA.getAverage());
```

## Future

#### Must

- investigate if and how the internal math can be made more robust against overflow.
  - use double instead of float (will work on certain platforms) (must) => 0.3.0
  - uint32_t?
  - accuracy threshold depends on float / double usage.  (sizeof(double) == 8)
  - threshold depends on the units of length. 
    if all add's are using 10000 as length they have equal weight.
    normalizing the weight? how? user responsibility?
  - get set threshold via API?
  - use of threshold versus error detection (sum - angle == previous or not)
  - split OVERFLOW error in X and Y


#### Should

- add overflow example
- add singularity example


#### Could

- **uint32_t addDegrees(float angle)** more explicit.
- **uint32_t addRadians(float angle)** idem.
- **uint32_t addGradians(float angle)** idem.


#### Wont

- add a USER AngleType, in which the user can map 0..360 degrees to any range.
  - float userFactor = 1.0;  (default)
  - can even be negative?
  - use cases? e.g 0..4 quadrant?
  - maybe better for the AngleConvertor class.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

