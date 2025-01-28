
[![Arduino CI](https://github.com/RobTillaart/AD7367/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD7367/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD7367/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD7367/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD7367/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD7367.svg)](https://github.com/RobTillaart/AD7367/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD7367/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD7367.svg?maxAge=3600)](https://github.com/RobTillaart/AD7367/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD7367.svg)](https://registry.platformio.org/libraries/robtillaart/AD7367)


# AD7367

Arduino library for the AD7367, 2 channel simultaneous sampling 14 bit ADC.


## Description

**Experimental**

The AD7367 is a device with two ADC's which can sample 2 channels simultaneously 
at 14 bits with a theoretical speed of up to 1 MSPS. 
The AD7366 is a similar 12 bits device.
The two samples can be clocked out (SPI alike) simultaneous over two data pins.

This library implements the **basic** functionality to trigger a measurement and
read the bits of the two ADC's over two data pins.




Feedback, issues, improvements are welcome. 
Please file an issue on GitHub.



### Related

- https://github.com/RobTillaart/AD7367 simultaneous sampling 14 bit ADC.
- https://github.com/RobTillaart/ADC081S 10-12 bit, single channel ADC
- https://github.com/RobTillaart/ADC08XS 10-12 bit, 2 + 4 channel ADC
- https://gammon.com.au/adc tutorial about ADC's (UNO specific)
- https://github.com/RobTillaart/MCP_ADC 10-12 bit, 1,2,4,8 channel ADC
- https://github.com/RobTillaart/ADS1x15 12 & 16 bit ADC, I2C, slow
- https://github.com/RobTillaart/PCF8591 8 bit single ADC (+ 1 bit DAC)

Forum link where it all started

- https://forum.arduino.cc/t/request-for-ad7367-library-for-arduino/1340710


## Interface

```cpp
#include "AD7367.h"
```

### Constructor

- **AD7367(uint8_t select, uint8_t clock, uint8_t convert, uint8_t busy, uint8_t data0, uint8_t data1)**
- **AD7366(uint8_t select, uint8_t clock, uint8_t convert, uint8_t busy, uint8_t data0, uint8_t data1)**

|   pin     |   IO     |  description  |
|:----------|:---------|:--------------|
|  select   |  OUTPUT  |  Chip select 
|  clock    |  OUTPUT  |  Serial clock
|  convert  |  OUTPUT  |  start conversion
|  busy     |   INPUT  |  conversion busy
|  data0    |   INPUT  |  Serial data ADC A
|  data1    |   INPUT  |  Serial data ADC B


- **void begin()** initializes internal state.
- **uint8_t getType()** returns 67 or 66, depends on type (which constructor used)
- **int getBits()** returns resolution 12 or 14 bits, depends on type.


### Read

- **int read()** synchronous call to make a measurement from both channels.
Actually it is a wrapper around the next three calls.
- **void triggerConversion()** asynchronous call to start conversion.
- **bool conversionBusy()** returns true if a conversion is ongoing.
- **bool conversionReady()** returns true if a conversion is ready.
- **int readAsync()** clock in the data from the device.
Should be called only if the conversion is ready.
- **int getValue(uint8_t channel)** get the last measurement of channel 0 or 1.
Multiple calls to **getValue()** will result in the same value until new data 
is read, sync or async.

The device has an option to read both measurements using only one data pin
however this is not supported.

## Future

#### Must

- read the datasheet
- improve documentation
- get hardware to test the library

#### Should

- add examples
- support REFSEL reference select.
- support ADDR
- support RANGE1 RANGE0

#### Could

- optimize code.
  - digitalPulse(pin) LOW_HIGH 
- getMaxValue() 12 bit == 4096, 14 bit = 16383.
- flag in read() to read via data pin 1, 2 or both(3)?
  - or another constructor?
- optimize AVR with registers a la SW SPI.
- error handling?
- interrupt example?

#### Wont

- HW SPI won't work as there are 2 data channel.
  - one could sample both ADC over 1 channel with 2x clock pulses (fig 28)
- SPI 4 or QSPI might be an option?

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

