
[![Arduino CI](https://github.com/RobTillaart/runningAngle/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/runningAngle/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/runningAngle/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/runningAngle/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/runningAngle/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/runningAngle.svg)](https://github.com/RobTillaart/runningAngle/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/runningAngle/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/runningAngle.svg?maxAge=3600)](https://github.com/RobTillaart/runningAngle/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/runningAngle.svg)](https://registry.platformio.org/libraries/robtillaart/runningAngle)


# runningAngle

Arduino library to calculate the running average of a series of angles.


## Description

This library provides a class, `runningAngle`, that computes an
exponentially weighted running average of a series of angles, such as
compass readings. It is aware of how angles wrap modulo 360°.

The [exponentially weighted running average][ewra] is a type of [running
average][ra] that averages all the past inputs with weights that
decrease exponentially as the inputs get older. It is a type of digital
filter very commonly used for smoothing noisy sensor readings. It is
more memory efficient than the simple running average, while providing
similar smoothing capability.

Computing an “average” of angular data, such as headings, is inherently
an ambiguous problem. For example, given the headings 350° and 10°,
there are two possible “averages” that lie halfway between them, namely
0° and 180°. This library assumes that the “correct” average is the one
that lies in the middle of the shorter arc joining the initial headings,
thus 0°. This is the right choice for smoothing noisy sensor readings,
assuming the peak-to-peak amplitude of the noise is not too large. Note
that the regular average of the numbers 350 and 10 is 180, which is not
the result we expect when averaging angles.

This library is a spin off of [AverageAngle][], based on [an issue][]
raised by Edgar Bonet.

[ewra]: https://en.wikipedia.org/wiki/Exponential_smoothing
[ra]: https://en.wikipedia.org/wiki/Moving_average
[AverageAngle]: https://github.com/RobTillaart/AverageAngle
[an issue]: https://github.com/RobTillaart/AverageAngle/issues/1


#### Related

- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/AngleConvertor
- https://github.com/RobTillaart/AverageAngle
- https://github.com/RobTillaart/RunningAngle
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian


## Smoothing coefficient

The output of the filter is efficiently computed as a weighted average
of the current input and the previous output:

output = α × current\_input + (1 − α) × previous\_output

The smoothing coefficient, α, is the weight of the current input in the average. 
It is called “weight” within the library, and should be set to a value between 
0.001 and 1. The larger the weight (closer to 1), the weaker the smoothing,
so noise will affect the average quite a bit.
Closer to zero, new values only affect the average minimal.
- A weight α = 1 provides no smoothing at all, as the
filter's output will be a copy of the input.
- A weight α = 0 will return only the first value added. 
Therefore the weight should be minimal 0.001.

The filter has a smoothing performance similar to a simple running
average over N = 2/α − 1 samples. For example, α = 0.2 is similar to
averaging over the last 9 samples.

It is important to do test runs to find the optimal coefficient (range)
for your application. One should be aware that the frequency of adding 
new angles will affect the time to stabilize the output.

Note also that it is possible to change the weight run-time. 
This can be needed e.g. if the accuracy of the input improves over time.


## Usage

First, create a filter as an instance of `runningAngle`:

```c++
runningAngle my_filter(runningAngle::DEGREES);
```

The parameter of the constructor should be
`runningAngle::DEGREES`, `runningAngle::RADIANS` or `runningAngle::GRADIANS`. 
This parameter is optional and defaults to degrees.

Then, set the “weight” smoothing coefficient:

```c++
my_filter.setWeight(0.2);
```
Note: the weight defaults to 0.80 so no need to set 

Finally, within the main sketch's loop, feed the raw angle readings to
the filter's `add()` method:

```c++
float heading = get_a_compass_reading_somehow();
float smoothed_heading = my_filter.add(heading);
```

The method returns the smoothed reading within ± 180° (i.e. ± π radians) by default.

The returned value is easily mapped upon 0..360 by adding 360 degrees ( 2π )
to the average if the average < 0.
Other mappings including scaling are of course possible.

Note: Degree character ° = ALT-0176 (windows)


## Interface

```cpp
#include "runningAngle.h"
```

#### AngleType

- **enum AngleType { DEGREES, RADIANS, GRADIANS }** used to get type math right.

A full circle is defined as:
- DEGREES = 360°
- RADIANS = 2 π = 6.283...
- GRADIANS = 400°

GRADIANS are sometimes called GON.

There also exists a type milli-radians which is effectively the 
same as RADIANS \* 1000. This won't be supported.
mRad and other angle-types can be converted here - https://github.com/RobTillaart/AngleConvertor


#### runningAngle

- **runningAngle(AngleType type = DEGREES)** constructor, default to DEGREES.
- **float add(float angle)** adds a new value using a defined weight. 
Except for the first value after a reset, which is used as initial value. 
The **add()** function returns the new average.
- **void reset()** resets the internal average to 0 and weight to start "clean" again. 
If needed one should call **setWeight()** again!
- **float getAverage()** returns the current average value.
- **void setWeight(float weight = RA_DEFAULT_WEIGHT)** sets the weight of the new added value. 
Value will be constrained between 0.001 and 1.0.
Default weight = RA_DEFAULT_WEIGHT == 0.80.
- **float getWeight()** returns the current / set weight.
- **AngleType type()** returns DEGREES, RADIANS or GRADIANS.
- **float wrap(float angle)** wraps an angle to \[-180..+180>  \[-PI..PI> 
or \[-200..200> depending on the type set.


#### Mode 

- **void setMode0()** average interval = \[-180..180>
- **void setMode1()** average interval = \[0..360>
- **uint8_t getMode()** returns current mode = 0 or 1.


## Performance add()

Being the most important worker function, doing float math.
(based on time-add.ino on UNO)

|  version  |  mode  |  CPU cycles  |  us per add  |  relative  |
|:---------:|:------:|-------------:|-------------:|-----------:|
|   0.1.5   |    0   |      681     |  42.5625 us  |   100%     |
|   0.2.0   |    0   |      681     |  42.5625 us  |   100%     |
|   0.2.0   |    1   |      681     |  42.5625 us  |   100%     |


## Future

#### Must

- improve documentation.

#### Should

- should **add()** return the average? (yes)
  - or make a **fastAdd()** that doesn't?

#### Could

- add examples.
  - compass HMC6352 lib or simulator.
  - AS5600 angle measurement sensor
- update unit tests.

#### Wont

- get statistics about the noise in the angles (stats on the delta?).
  - not the goal of this lib ==> use statistics library
- optimize **wrap()** to be generic => no loop per type.
  - needs variables for -180 / 180 / 360  (RAM vs PROGMEM)
- derived class for degrees only? (max optimization)
- runtime change of type 
  - no, too specific scenario.
  - conversion needed?
  - add mixed types.  45° + 3 radians = ??
  ==> user can do this. 


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

