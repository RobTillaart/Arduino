
[![Arduino CI](https://github.com/RobTillaart/AverageAngle/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AverageAngle/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AverageAngle/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AverageAngle/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AverageAngle/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AverageAngle/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AverageAngle.svg?maxAge=3600)](https://github.com/RobTillaart/AverageAngle/releases)


# AverageAngle

Arduino library to calculate correctly the average of multiple angles.


## Description

AverageAngle is an class to calculate the average of angles.

This is especially useful when angles are around 0 degrees, 
e.g. from a compass sensor or the resultant of a track.
Example, the average angle of 359 and 1 is 0, not 179 (most of the time)

Furthermore the AverageAngle can also include the **length (weight)** of the angle as if it is a vector. 
Default this length is set to 1 so all angles are by default of equal weight.

Example: The average angle of 359 (length = 2) and 1 (length = 1) is 359.something not zero.

See also **runningAngle** class.


## Interface

- **enum AngleType { DEGREES, RADIANS, GRADIANS } ** idem. 100 GRADIANS == 90 DEGREES.
- **AverageAngle(AngleType type = DEGREES)** constructor defaults to degrees.
- **uint32_t add(float alpha, float length = 1.0)** add a new angle, optional with length. 
**add()** returns the number of elements (count).
- **void reset()** clears internal buffers.
- **uint32_t count()** the amount of angles added.
- **float getAverage() ** returns the average.
- **float getTotalLength() ** the length of the resulting 'angle' when we see them as vectors.
- **float getAverageLength()** returns the average length of the angles added.
- **AngleType type()** returns DEGREES = 0, RADIANS = 1 or GRADIANS = 2.
- **void setType(AngleType type)** changes type DEGREES, RADIANS or GRADIANS.


## Gradians

Gradians a.k.a. gon, is a less often used unit for angles. 
There are 100 gradians in a right angle. A full circle = 400 gradians.

https://en.wikipedia.org/wiki/Gradian


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
  AA.add(90, 5);     // 5 steps north
  AA.add(180, 3);    // 3 steps west
  Serial.println(AA.getAverage());
  Serial.println(AA.getTotalLength());
```


## Future

- Improve documentation. 
- check if other units exist to support.


