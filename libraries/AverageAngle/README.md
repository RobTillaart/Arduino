
[![Arduino CI](https://github.com/RobTillaart/AverageAngle/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AverageAngle/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AverageAngle/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AverageAngle/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AverageAngle/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AverageAngle/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AverageAngle.svg?maxAge=3600)](https://github.com/RobTillaart/AverageAngle/releases)


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


#### Related to
- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/AngleConvertor
- https://github.com/RobTillaart/runningAngle


#### AngleType

- **enum AngleType { DEGREES, RADIANS, GRADIANS }** idem. 

|  value  |  name      |  range     |
|:-------:|:-----------|:-----------|
|   0     |  DEGREES   |  0 .. 360  |
|   1     |  RADIANS   |  0 .. 2PI  |
|   2     |  GRADIANS  |  0 .. 400  |  100 GRADIANS == 90 DEGREES.


## Interface

- **AverageAngle(AngleType type = DEGREES)** constructor defaults to degrees.
- **uint32_t add(float alpha, float length = 1.0)** add a new angle, 
optional with length other than 1. 
Returns the number of elements (count).
- **void reset()** clears internal counters.
- **uint32_t count()** the amount of angles added.
If count == 0, there is no average.
- **float getAverage()** returns the average, unless count == 0 
or the internal sums == (0,0) in which case we have a singularity ==> NAN (not a number)
- **float getTotalLength()** the length of the resulting 'angle' when we see them as vectors.
If count == 0 ==> total length = 0.
- **float getAverageLength()** returns the average length of the angles added.
If count == 0 ==> average length = 0.
- **AngleType type()** returns DEGREES, RADIANS or GRADIANS.
- **void setType(AngleType type)** changes type DEGREES, RADIANS or GRADIANS.
Type can be changed run time and still continue to add. 


## Gradians

Gradians a.k.a. **gon**, is a less often used unit for angles. 
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

#### Warning

As the internal representation has a limited resolution (float) it can occur that when
the internal values are large, one cannot add a very small angle any more.
Did not encounter it yet myself. 


## Future

#### Must

#### Should

#### Could
- add a USER AngleType, in which the user can map 0..360 degrees to any range.
  - float userFactor = 1.0;  (default)
  - can even be negative?
  - use cases? e.g 0..4 quadrant?

