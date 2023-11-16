
[![Arduino CI](https://github.com/RobTillaart/Radar/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Radar/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Radar/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Radar/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Radar/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Radar.svg)](https://github.com/RobTillaart/Radar/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Radar/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Radar.svg?maxAge=3600)](https://github.com/RobTillaart/Radar/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Radar.svg)](https://registry.platformio.org/libraries/robtillaart/Radar)


# Radar

Arduino library for a pan tilt radar based upon 2 servo's.


## Warning

**WARNING: not extensively tested**
There are still a lot of things to be tested.  
The example code is now working to show the concept.


## Description

Radar is a concept library (not elaborated) that implements a Ping))) based Radar
with the use of two pan and tilt servo's. 
It was written after a question on the Arduino forum but never finished or tested it. 
Still, it has some interesting concepts with respect to how to determine the position 
of pan/tilt while the movements are in progress. 

The idea is that one knows how fast the pan and tilt servos are working in degrees per second.
From that number and the start moment one can determine approximately its position. 

Given its position while moving is interesting for radar purposes as one can determine e.g.
in which direction a ping is given and therefore which distance belongs to which pair of angles.

Note: no active development.


## Interface

```cpp
#include "radar.h"
```

### Constructor and config

- **RADAR(pan, tilt)** define pan / tilt pins of the radar. These should be PWM pins.

Note: no valid range checking or negative value check.
- **void setPanPerSecond(float pps)**
- **float getPanPerSecond()**
- **void setTiltPerSecond(float tps)**
- **float getTiltPerSecond()**


### basic moves

- **void gotoPan(const int16_t pan)**
- **int16_t getPan()**
- **void  gotoTilt(const int16_t tilt)**
- **int16_t getTilt()**
- **void gotoPanTilt(const int16_t pan, const int16_t tilt)**


### memory positions - store / recall

- **uint8_t getMaxPositions()**
- **bool setPosition(const uint8_t index, const int16_t pan, const int16_t tilt)**
- **bool getPosition(const uint8_t index, int16_t & pan, int16_t & tilt)**
- **bool gotoPosition(const uint8_t index)**
- **void setHomePosition(const int16_t pan, const int16_t tilt)**
- **void gotoHomePosition()**


### feedback on position

- **bool isMoving()**
- **bool isPanMoving()**
- **bool isTiltMoving()**


## Operation

See examples


## Future

#### Must

- build the thing when time permits!
- improve documentation.

#### Should

- test more (e.g. continuous servo versus 180 servo).
- add sketches.
- remember lastPing (angle pan tilt).
- check TODO's in code.
- move code from .h to .cpp

#### Could

- single servo radar (Pan only) as derived class.
- dynamic allocation of position arrays.
- store positions in EEPROM/FRAM for reboot?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
