
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

Experimental library for the AD9833 function (waveform) generator.
The library supports both hardware SPI and software SPI.

The AD9833 is a signal generator that has two channels for frequency and
two channels for the phase. These channels can be set separately to have
maximum flexibility.

The AD9833 can generate three waveforms: sine, square (2x) and triangle.
The frequency of the waves cover a range from 0 to 12.5 MHz.
The step size for frequency is ~0.1 Hz (using 25 MHz reference clock).

The library also can set the phase of each wave from 0° to 360°.
The step size for phase is ~0.1°.

|   type   |  freq max  |  freq step  |  phase   | phase step  |  Notes  |
|:--------:|:----------:|:-----------:|:--------:|:-----------:|:--------|
|  AD9833  |  12.5 MHz  |  0.1 Hz     |  0..360  |     0.1°    |

Note: With an external 1 MHz clock smaller frequency steps 0.004 Hz. can be made.
This is not tested yet.


#### Compatibles ??

List of (partially) compatibles in the series, that might work (partially) with this library.

TODO: Investigations needed, verify table below (hardware needed).

|   type   |  freq max  |  freq step  |  wave forms  |  Notes  |
|:--------:|:----------:|:-----------:|:------------:|:--------|
|  AD9832  |  12.5 MHz  |             |  SI          |
|  AD9833  |  12.5 MHz  |   0.1  Hz   |  SI  TR  SQ  |  for reference
|  AD9834  |  37.5 MHz  |   0.28 Hz   |  SI  TR      |  has extra HW lines.
|  AD9835  |  50.0 MHz  |   0.01 Hz   |      ??      |  looks not compatible
|  AD9837  |  16.0 MHz  |   0.06 Hz   |  SI  TR  SQ  |
|  AD9837  |   8.0 MHz  |   0.06 Hz   |  SI  TR      |

If you have experience with one of the above "compatibles" and this library, 
please let me know by opening an issue. 
Probably they need a dedicated library based on this one.


#### Related

- https://github.com/RobTillaart/AD985X
- https://github.com/RobTillaart/functionGenerator  software waveform generator
- https://pages.mtu.edu/~suits/notefreqs.html  frequency table for notes.


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
If the selectPin is set to 255, external FSYNC is used. 
See section below.
- **void begin(uint8_t selectPin, SPIClass \* spi)**
For hardware SPI only, to select a specific hardware SPI port e.g. SPI2.
If the selectPin is set to 255, external FSYNC is used. 
See section below.
- **void reset()** does a **hardwareReset()**, 
and sets the control register to B28 for the **setFrequency()**
- **void hardwareReset()** resets all registers to 0.
- **bool setPowerMode(uint8_t mode = 0)** set the powerMode.
Default is 0, wake up. So use ```setPowerMode(0)``` to wake up the device.
Returns false if mode is out of range.
Details see datasheet.

|  powerMode  |  meaning                      |
|:-----------:|:------------------------------|
|     0       |  no power saving              |
|     1       |  powers down the on-chip DAC  |
|     2       |  disable internal MCLK clock  |
|     3       |  combination of mode 1 & 2    |


#### Waveform

- **void setWave(uint8_t waveform)**
- **uint8_t getWave()**

|  waveform   |  define name      |  value  |  notes  |
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
- **void setFrequencyChannel(uint8_t channel)** select the active frequency of channel (0 or 1).

Note: the frequency depends on the internal reference clock which is default 25 MHz.
The library does not support other reference clocks yet.


#### Phase

Default channel is 0, which makes the function calls simpler 
when only using one channel.

- **float setPhase(float phase, uint8_t channel = 0)**
setPhase sets the phase and is limited to 0° - 360°.
Returns the phase set in degrees.
- **float getPhase(uint8_t channel = 0)** returns the phase set in degrees.
- **float getMaxPhase()** returns the maximum phase to set (convenience).
- **void setPhaseChannel(uint8_t channel)** select the active phase channel (0 or 1).

The library does not support get and set the phase in radians (yet).


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

#### Low level API

Use at your own risk, please read the datasheet carefully.

Since version 0.1.1 writing to the registers is made public.
By using the low level API to access the registers directly, one has maximum
control over the AD9833 device.
Especially frequency setting is improved as the float **setFrequency()** does 
not have the 28 bits precision of the register.

- **void writeControlRegister(uint16_t value)** see datasheet
- **void writeFreqRegister(uint8_t reg, uint32_t freq)** reg = 0 or 1, freq = 0 .. 134217728
- **void writePhaseRegister(uint8_t reg, uint16_t value)** reg = 0 or 1, freq = 0 .. 4095
  

## External FSYNC

Experimental => use with care!

If in the **begin()** function the selectPin is set to 255 external FSYNC is used. 
This allows to control e.g many AD9833 devices in parallel, with multi-IO chips.
Think of the SPI based **MCP23S08/17**, or the I2C based **PCF8574/75**.

The advantage is that one can control many (e.g. 16 devices) with a minimum of IO lines.

The disadvantage is that you need to add extra code lines to set / clear the FSYNC line(s).
Furthermore one should know that using this "external FSYNC" is slower than direct control 
with MCU pins from within the library.

Pin count wise this concept is only interesting for 3 or more AD9833 devices.

Code wise you need to "manual" control the FSYNC.

```cpp
  setFsyncLow(5);        //  select device 5
  AD.setFrequency(440);  //  set a new frequency
  setFsyncHigh(5);       //  update the setting.
```

As this implementation is experimental, the interface might change in the future.


## Future

#### Must

- update documentation
- get hardware to test


#### Should

- investigate HLB mode versus B28 mode
- investigate external clock
- investigate timing (response time)
  - change freq
  - change channels etc.
- test on ESP32 (3V3)


#### Could

- extend unit tests
- add examples
  - for ESP32 HWSPI interface
- move code to .cpp
- solve MAGIC numbers (defaults)
- setting half freq register for performance mode.
  - HLB mode
- extend performance measurements
- investigate compatibility AD9834 a.o.
- add **setPhaseRadians(float radians, uint8_t channel)** wrapper.
- add **getPhaseRadians(uint8_t channel)** wrapper.


#### Wont



## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

