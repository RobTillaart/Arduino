
[![Arduino CI](https://github.com/RobTillaart/runningAngle/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/runningAngle/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/runningAngle/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/runningAngle/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/runningAngle/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/runningAngle/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/runningAngle.svg?maxAge=3600)](https://github.com/RobTillaart/runningAngle/releases)


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


## Smoothing coefficient

The output of the filter is efficiently computed as a weighted average
of the current input and the previous output:

output = α × current\_input + (1 − α) × previous\_output

The smoothing coefficient, α, is the weight of the current input in the
average. It is called “weight” within the library, and should be set to
a value between 0.001 and 1. The larger the weight, the weaker the
smoothing. A weight α&nbsp;=&nbsp;1 provides no smoothing at all, as the
filter's output is a just a copy of its input.

The filter has a smoothing performance similar to a simple running
average over N = 2/α − 1 samples. For example, α = 0.2 is similar to
averaging over the last 9 samples.


## Usage

First, create a filter as an instance of `runningAngle`:

```c++
runningAngle my_filter(runningAngle::DEGREES);
```

The parameter of the constructor should be either
`runningAngle::DEGREES` or `runningAngle::RADIANS`. It is optional and
defaults to degrees.

Then, set the “weight” smoothing coefficient:

```c++
my_filter.setWeight(0.2);
```

Finally, within the main sketch's loop, feed the raw angle readings to
the filter's `add()` method:

```c++
float heading = get_a_compass_reading_somehow();
float smoothed_heading = my_filter.add(heading);
```

The method returns the smoothed reading within ± 180° (i.e. ± π rad).

See the “examples” folder for a more complete example.

Degree character = ALT-0176


## Interface

### AngleType

- **enum AngleType { DEGREES, RADIANS, GRADIANS }** used to get type math right.

A full circle is defined as:
- DEGREES = 360°
- RADIANS = 2 π = 6.283...
- GRADIANS = 400°

GRADIANS are sometimes called GON. 
There also exists a type milli-radians which is effectively the 
same as RADIANS \* 1000. It won't be supported. 


### runningAngle

- **runningAngle(AngleType type = DEGREES)** constructor, default to DEGREES
- **float add(float angle)** adds value using a certain weight, 
except the first value after a reset is used as initial value. 
The **add()** function returns the new average.
- **void reset()** resets the internal average and weight to start clean again. 
If needed one should call **setWeight()** again!
- **float getAverage()** returns the current average value.
- **void setWeight(float weight)** sets the weight of the new added value. 
Value will be constrained between 0.001 and 1.00
- **float getWeight()** returns the current set weight.
- **AngleType type()** returns DEGREES, RADIANS or GRADIANS.
- **float wrap(float angle)** wraps an angle to <-180..+180>  <-PI..PI> <-200..200> depending on the type set.


## Operation

See examples


## Future

- get some numbers about the noise in the angles (stats on the delta?)
- runtime change of type
  - conversion 
  - add mixed types.  45° + 3 radians = ??



