
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

The class is very straightforward, one can set the beats per minute (BPM)
and uses start / stop to have the ticks in the requested rhythm.

The Metronome has one or two output pins, typical connected to LEDs or a buzzer.
These are the nicknamed the tick and tock pin.
The Metronome will generate pulses with 50% duty cycle at the configured BPM.

If one output pin is defined all pulses will be send to this pin. 
If two output pins are defined the second pin will pulse once depending on the 
value set with **setMeasure()**. E.g. if the measure is set to 6, the first pin
will get 5 pulses and the second will get one.

The default BPM == 100 and default measure == 4.

Default the Metronoe is idle and needs an explicit start with **start()**.

The metronome can be used as a very simple square wave generator.
Be aware that to set a frequency, the BPM must be multiplied by 60.

Feedback as always is welcome.


### Related

- https://github.com/RobTillaart/Metronome
- https://github.com/RobTillaart/PulsePattern  (AVR only)


### Tested

Tested on Arduino UNO, with a red and green LED.


## Interface

```cpp
#include "Metronome.h"
```

### Constructor

- **Metronome(uint8_t tickPin, uint8_t tockPin = 255)** sets the output 
pin for ticks and optionally a separate pin for tock.
if the tock pin is not defined, the tick pin will be used instead.  
- **void begin()** initializes all pins and internal counters.

A separate pin for tick and tock allows e.g. a two colour LED to be used,
or two different sounds.

If tick and tock pins are the same it will behave as only the tick pin is defined.


### BPM

setMeasure(4) => tick tick tick TOCK
setMeasure(3) => tick tick TOCK

- **void setBeatsPerMinute(float bpm)** defines the tick interval. 
The BPM can be set as a floating point to correct minimal deviations.
The internal interval is measured in micros and if the BPM is very high it will be less accurate.
- **float getBeatsPerMinute()** returns the set BPM.
- **void setMeasure(uint8_t tock)** defines the TOCK rhythm, typical values are 2,3,4,5,6,8,12.
Will only work if tockpin is defined in the constructor.
- **uint8_t getMeasure()** returns the set measure.


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

Default the Metronome is idle and needs an explicit **start()**.

- **void start()** idem
- **void stop()** idem, and resets the internal tock count to zero.
- **void check()** workhorse, must be called as often as possible.


## Future

#### Must

- improve documentation

#### Should

- investigate range

#### Could

- void addMIDI(Stream \* ser)
  - baud rate 31250?
  - midi channel / note / duration etc.
- extend wave generator functions?
- inverted channel?
- duty cycle?
- Metronome macro language to change rhythm in a loop?
  - "R10 M4 B60 R2 M6 B120 R5 M4 B60" (R = repeat all till next R
  - interactive over serial?
- unit tests,
- ledstrip output?
- determine BPM tool with a button?
- debug() => probably complexer than the library :)

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


