
[![Arduino CI](https://github.com/RobTillaart/MT8870/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MT8870/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MT8870.svg?maxAge=3600)](https://github.com/RobTillaart/MT8870/releases)

# MT8870

Arduino library for MT8870 DTMF decoder (breakout)

## Description

This library reads the signals of the MT8870 chip. 
If data is available one can read it raw or as text.

DTMF = Dual Tones Multiple Frequency, it are the tones you
hear when you press buttons on your phone. 

A=697 Hz
B=770 Hz
C=852 Hz
D=941 Hz
E=1209 Hz
F=1336 Hz
G=1477 Hz
H=1633 Hz

## Interface

- **MT8870()** constructor
- **void begin(STQ, Q1, Q2, Q3, Q4)** defines which pins to use. 
Technically it is possible to have readout multiple decoders
with one MT8870 object by calling **begin()** with other pins.
  - **STQ**    = data available signal
  - **Q1..Q4** = datapins
  - Calling begin resets the **lastRead** char
- **bool available()** returns true if there is a DMTF signal 
- **char read()** reads the character available. returns 255 if no signal available.
- **uint8_t readRaw()** returns 0 .. 15 or 255 if no signal is available.
- **uint8_t lastRaw()** returns the last code read 0 .. 15 or 255.  
Note this is a cached value from a readRaw / read call.


## Future / ideas / improvements

- buffer like Serial? (how to fill? interrupt? example sketch?)
- DMTF tone generation?
- more examples!

DTMF tones, uses one from A..D one from E..H.

| Name | Frequency |
|:----:|----:|
| A | 697 Hz  |
| B | 770 Hz  |
| C | 852 Hz  |
| D | 941 Hz  |
| E | 1209 Hz |
| F | 1336 Hz |
| G | 1477 Hz |
| H | 1633 Hz |

## Operations

See examples.
