
[![Arduino CI](https://github.com/RobTillaart/AD9833/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD9833/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD9833/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD9833/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD9833/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD9833.svg)](https://github.com/RobTillaart/AD9833/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD9833/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD9833.svg?maxAge=3600)](https://github.com/RobTillaart/AD9833/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD9833.svg)](https://registry.platformio.org/libraries/robtillaart/AD9833)


# AD9833

Arduino library for AD9833 function generator. 


## Description

Experimental library for the AD9833 function generator.
The library supports both hardware SPI and software SPI.

TODO: test with hardware.

The AD9833 is a signal generator that has two channels for frequency and
two channels for the phase. These channels can be set separately to give
maximum flexibility.

The AD9833 can generate three types of wave: sine, square (2x) and triangle.
The frequency of the waves cover a range from 0 to 12.5 MHz.
The step size for frequency is ~0.1 Hz (using 25 MHz reference clock).

The library also can set the phase of each wave from 0° to 360°.
The step size for phase is ~0.1°.

|   type   |  freq max  |  freq step  |  phase   | phase step  |
|:--------:|:----------:|:-----------:|:--------:|:-----------:|
|  AD9833  |  12.5 MHz  |  0.1 Hz     |  0..360  |     0.1°    |


#### Related

- https://github.com/RobTillaart/AD985X
- https://github.com/RobTillaart/functionGenerator


## Connection

Schema AD9833 chip, breakout will have different pins.

```
                  TOP VIEW
                +-----------+
   COMP         | 1      10 |  VOUT
   VDD          | 2       9 |  A-GND
   CAP / 2.5 V  | 3       8 |  FSYNC (select)
   D-GND        | 4       7 |  SCLK
   MCLK         | 5       6 |  SDATA
                +-----------+

```

|  PIN          |  Description         |
|:--------------|:---------------------|
|  COMP         |  DAC Bias Pin        |
|  VDD          |  Power supply        |
|  CAP / 2.5 V  |  (datasheet)         |
|  D-GND        |  Digital Ground      |
|  MCLK         |  Digital Clock Input |
|  SDATA        |  Serial Data In      |
|  SCLK         |  Serial Clock In     |
|  FSYNC        |  Select              |
|  A-GND        |  Analog Ground       |
|  VOUT         |  Analog Out          |

Read datasheet for detailed description of the pins.


## Interface

```cpp
#include "AD9833.h"
```

#### Constructor

- **AD9833()** 12.5 MHz signal generator
- **void begin(uint8_t selectPin, uint8_t dataPin = 0, uint8_t clockPin = 0)**
For hardware SPI only use the first two parameters, 
for SW SPI you need to define the data and clock pin too.
  - selectPin = chip select.
- **void begin(uint8_t selectPin, SPIClass \* spi)**
For hardware SPI only, to select a specific hardware SPI port e.g. SPI2.
- **void reset()** resets the function generator.


#### Wave

- **void setWave(uint8_t wave)**
- **uint8_t getWave()**

|  wave type  |  define name      |  value  |  notes  |
|:-----------:|:-----------------:|:-------:|:--------|
|  No output  |  AD9833_OFF       |    0    |
|  Sine       |  AD9833_SINE      |    1    |
|  Square     |  AD9833_SQUARE1   |    2    |
|  Square2    |  AD9833_SQUARE2   |    3    |  half frequency
|  Triangle   |  AD9833_TRIANGLE  |    4    |


#### Frequency

Default channel is 0, which makes the function calls simpler 
when only using one channel.

- **float setFrequency(float freq, uint8_t channel = 0)**
SetFrequency sets the frequency and is limited by the MaxFrequency of 12.5 MHz.
Returns the frequency set.
- **float getFrequency(uint8_t channel = 0)** returns the frequency set.
- **float getMaxFrequency()** returns the maximum frequency to set (convenience).
- **void selectFreqChannel(uint8_t channel)** select the active frequency channel (0 or 1).


#### Phase

Default channel is 0, which makes the function calls simpler 
when only using one channel.

- **float setPhase(float phase, uint8_t channel = 0)**
setPhase sets the phase and is limited to 0° - 360°.
Returns the phase set.
- **float getPhase(uint8_t channel = 0)** returns the phase set.
- **float getMaxPhase()** returns the maximum phase to set (convenience).
- **void selectPhaseChannel(uint8_t channel)** select the active phase channel (0 or 1).


#### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true if HW SPI is used.


#### ESP32 specific

- **void selectHSPI()** in case hardware SPI, the ESP32 has two options HSPI and VSPI.
- **void selectVSPI()** see above.
- **bool usesHSPI()** returns true if HSPI is used.
- **bool usesVSPI()** returns true if VSPI is used.

The **selectVSPI()** or the **selectHSPI()** needs to be called 
BEFORE the **begin()** function.

- **void setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select)**
to overrule ESP32 default hardware pins (to be tested).
Needs to be called AFTER the **begin()** function.

In code, something like this (TODO write example)
```cpp
void setup()
{
  freqGen.selectVSPI();
  freqGen.begin(15);
  freqGen.setGPIOpins(CLK, MISO, MOSI, SELECT);  // SELECT should match the parameter of begin()
  ...
}
```


## Future

#### Must

- test with hardware
- update documentation


#### Should

- examples 
  - for ESP32 HWSPI interface
  - use of channels (freq & phase)
- do tests on ESP32
- performance measurements


#### Could

- extend unit tests
- move code to .cpp
- solve MAGIC numbers (defaults)
- setting half freq register for performance mode.
- investigate different power down / sleep modi (page 16)
- investigate hardware reset (page 16)


#### Wont



## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

