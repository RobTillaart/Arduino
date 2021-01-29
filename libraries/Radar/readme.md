
[![Arduino CI](https://github.com/RobTillaart/Radar/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Radar/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Radar.svg?maxAge=3600)](https://github.com/RobTillaart/Radar/releases)

# Radar

Arduino library for a pan tilt radar based upon 2 servo's.


## Warning

**WARNING: not extensively tested**
There are stil a lot of things to be tested. 
The example code is now working to show the concept.


## Description

radar is a concept library not elaborated yet that implements a Ping))) based Radar
with the use of two pan/tilt servo's. It was written after a question on the forum but 
never finished or tested it. Still, it has some interesting concepts wrt determine 
the position of pan/tilt while in progress. 

The idea is that one knows how fast the pan and tilt servos are working in degrees per second.
From that number and the start moment one can determine approximately its position. 

Given its position while moving is interesting for radar purposes as one can determine e.g.
in which direction a ping is given and which distance belongs to which pair of angles.


## Interface

TODO elaborate

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


### memory positions - store / recall?

- **uint8_t getMaxPositions()**
- **bool setPosition(const uint8_t idx, const int16_t pan, const int16_t tilt)**
- **bool getPosition(const uint8_t idx, int16_t & pan, int16_t & tilt)**
- **bool gotoPosition(const uint8_t idx)**
- **void setHomePosition(const int16_t pan, const int16_t tilt)**
- **void gotoHomePosition()**


### feedback on positions.

- **bool isMoving()**
- **bool isPanMoving()**
- **bool isTiltMoving()**


## Operation

See examples


