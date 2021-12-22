
[![Arduino CI](https://github.com/RobTillaart/MT8870/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MT8870/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MT8870/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MT8870/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MT8870/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MT8870/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MT8870.svg?maxAge=3600)](https://github.com/RobTillaart/MT8870/releases)


# MT8870

Arduino library for MT8870 DTMF decoder (breakout).


## Description

This library reads the signals of the MT8870 chip. 
If data is available one can read it raw or as text.

DTMF = Dual Tones Multiple Frequency, it are the tones you
hear when you press buttons on your phone. 

DTMF tones, uses one from A..D one from E..H.

| Name | Frequency |
|:----:|----------:|
|  A   |  697 Hz   |
|  B   |  770 Hz   |
|  C   |  852 Hz   |
|  D   |  941 Hz   |
|  E   |  1209 Hz  |
|  F   |  1336 Hz  |
|  G   |  1477 Hz  |
|  H   |  1633 Hz  |


## Interface

- **MT8870()** constructor
- **void begin(uint8_t STQ, uint8_t Q1, uint8_t Q2, uint8_t Q3, uint8_t Q4)** defines which pins to use. 
Technically it is possible to have readout multiple decoders
with one MT8870 object by calling **begin()** with other pins.
  - **STQ**    = data available signal
  - **Q1..Q4** = data pins.
  - Calling begin resets the **lastRead** char
- **bool available()** returns true if there is a DMTF signal 
- **char read()** reads the character available. returns 255 if no signal available.
- **uint8_t readRaw()** returns 0 .. 15 or 255 if no signal is available.
- **uint8_t lastRaw()** returns the last code read 0 .. 15 or 255 if no signal available.
Note this is a cached value from a readRaw / read call.
- **uint32_t lastTimeRead()** returns the timestamp of last **read()** or **readRaw()**. 


## Operations

See examples.


## Future / ideas / improvements

- improve documentation
- buffer like Serial? (how to fill? interrupt? example sketch?)
- test setup
- more examples
  - DMTF with a PCF8574
  - DMTF as secret key
  - DMTF with less keys (less pins)
  - DMTF over interrupt triggered by STQ line
- DMTF tone generation?  
  - MCP_DAC, 
  - PWM +HW?

