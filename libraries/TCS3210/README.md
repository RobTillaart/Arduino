
[![Arduino CI](https://github.com/RobTillaart/TCS3210/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TCS3210/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TCS3210/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TCS3210/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TCS3210/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TCS3210.svg)](https://github.com/RobTillaart/TCS3210/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TCS3210/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TCS3210.svg?maxAge=3600)](https://github.com/RobTillaart/TCS3210/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TCS3210.svg)](https://registry.platformio.org/libraries/robtillaart/TCS3210)


# TCS3210

Arduino library for TCS3210 colour light to frequency convertor.


## Description

**Experimental**

This library gives basic control over the TCS3200 and TCS3210 device.

The TCS32x0 are light to frequency converters, that allows the
colour to be selected and the frequency to be scaled.

The TCS3200 uses an 8x8 array of photo diodes and the TCS3210
uses a 4x6 array of photodiodes.
These photodiodes are divided in 4 groups, with a red, green, blue
or no filter to measure light intensity.

The output frequency of the TCS3210 is 2.6667x lower than the output
frequency of the TCS3200. This is exactly the ratio of the sizes of
their internal array of photodiodes.
This makes the TCS3210 more suitable for bright light. 
(See page 4, saturation irradiance).

The library implements support for basic settings and reading the
duration of the pulse or the corresponding frequency.

The library does not support conversion to uW / cm2 etc.

A far more elaborated library - https://github.com/nthnn/TCS3200
which supports calibration, normalization, various colour spaces
and more.

As always, feedback is welcome.


### Related

- https://github.com/nthnn/TCS3200 more elaborated library.


## Hardware

### Pin layout

```
          +-----------+
          |  TCS32x0  |
          |           |
      S0  | 1       8 |  S3
      S1  | 2       7 |  S2
      OE  | 3       6 |  OUT
     GND  | 4       5 |  VCC
          |           |
          +-----------+
```

|  pin  |  description  |
|:-----:|:--------------|
|   1   |  frequency scaling
|   2   |  frequency scaling
|   3   |  Output Enable
|   4   |  Ground
|   5   |  +5V
|   6   |  frequency out
|   7   |  colour filter selection
|   8   |  colour filter selection


## Interface

Check the datasheet for details

```cpp
#include "TCS3210.h"
```

### Constructor

- **TCS3210(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t OE, uint8_t data)**
- **TCS3200(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t OE, uint8_t data)**
- **bool begin()** initializes library.
Default no filter at 100%.
- **getType()** returns 00 or 10.

### Output Enable

Using **powerDown()** saves more energy than enable/disable.
Note it takes 100 us to recover from power down versus 100 ns from **disable()**.
(datasheet page 7)

- **void enable()** set OutputEnable line LOW.
- **void disable()** set OutputEnable line HIGH.

### Select colour filter

Select the colour filter for the next measurement.

- **void selectRed()**
- **void selectGreen()**
- **void selectBlue()**
- **void selectNone()**

### Select Output

Scale the output of the output, or switch the sensor to low power mode.

- **void powerDown()**
- **void set2Percent()**
- **void set20Percent()**
- **void set100Percent()**

### Read

- **uint32_t getDuration(uint16_t ms = 100)** returns micros.
Default max blocking time 100 milliseconds.
- **float getFrequency(uint16_t ms = 100)** returns frequency in Hz.
Default max blocking time 100 milliseconds.
So lowest frequency to measure is about 10 Hz (pretty dark).


## Future

#### Must

- improve documentation
- buy TCS3210 / TCS3200
- test functionality

#### Should

- investigate extended functionality
  - Angular Displacement - fig 2

#### Could

- easy constructor **TCS3210(S0)** //  all pins are sequence.
- select defaults in begin()?
- extend unit test.
- investigate extended functionality
  - conversion to uW etc?


#### Wont (unless)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

