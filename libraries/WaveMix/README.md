
[![Arduino CI](https://github.com/RobTillaart/WaveMix/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/WaveMix/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/WaveMix/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/WaveMix/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/WaveMix/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/WaveMix/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/WaveMix.svg?maxAge=3600)](https://github.com/RobTillaart/WaveMix/releases)


# WaveMix

WaveMix is an Arduino library to mix two signals (A and B) with an adaptive weight.


## Description

WaveMix is a very simple library to mix two signals (A and B) with an adaptive weight.

Depending on the weights applied the output signal (O) looks more on signal A or on signal B.

Inspired by - https://www.codeproject.com/Articles/5323200/On-how-to-mix-two-signals-by-using-Spectral-Foreca

Differences
- simpler algorithm
- WaveMix works on streams of measurements too.



## Interface

The main functions of the WaveMix 


## Operation



## Future ideas

- make a N channel variant.
- modulator
  - 3rd signal? ==> adjust weight runtime.
  - separate modulator class?
- add gain()
- add (fixed) offset
- add increment() / decrement() ?
  - percentages


