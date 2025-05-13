
[![Arduino CI](https://github.com/RobTillaart/Metronome/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Metronome/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Metronome/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Metronome/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Metronome/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Metronome.svg)](https://github.com/RobTillaart/Metronome/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Metronome/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Metronome.svg?maxAge=3600)](https://github.com/RobTillaart/Metronome/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Metronome.svg)](https://registry.platformio.org/libraries/robtillaart/Metronome)


# Metronome

Arduino library for creating a Metronome.


## Description

**Experimental**

This library is to create a simple Metronome.

The class is very straightforward, one can set the beats per minute
and uses start / stop to have the ticks in the requested rhythm.




### Related

- https://github.com/RobTillaart/Metronome


### Tested

Tested on Arduino UNO


## Interface

```cpp
#include "Metronome.h"
```

### Constructor

- **Metronome(uint8_t tickPin, uint8_t tockPin = 255)** sets the output 
pin for ticks and optionally a separate for tock.
if the tock pin is not defined, the tick pin will be used instead.  
- **void begin()** initializes all pins

A separate pin for tick and tock allows e.g. a two colour LED to be used,
or two different sounds.


### BPM

setMeasure(4) = tick tick tick TOK
setMeasure(3) = tick tick TOK

- **void setBeatsPerMinute(float bpm)** defines the tick interval
- **float getBeatsPerMinute()** returns set BPM.
- **void setMeasure(uint8_t n)** defines the TOK, typical 2,3,4,5,6,8,12
- **uint8_t getMeasure()** returns set Measure.


Typical BPM's
```cpp
uint8_t BPM[47] =
{
   36,  38,  40,  42,  44,  46,  48,  50,  52,  54,
   56,  58,  60,  63,  66,  69,  72,  76,  80,  84,
   88,  92,  96, 100, 104, 108, 112, 116, 120, 126,
  132, 138, 144, 152, 160, 168, 176, 184, 192, 200,
  208, 216, 224, 232, 240, 248, 256
};
```

### Control

- **void start()** idem
- **void stop()** idem
- **void check()** workhorse


## Future

#### Must

- improve documentation


#### Should

- implement measure in check.

#### Could

- void addMIDI(Stream \* ser)
  - baud rate 32150?
  - midi channel / note / duration etc.
-

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


