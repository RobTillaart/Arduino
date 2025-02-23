
[![Arduino CI](https://github.com/RobTillaart/AD7367_SPI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD7367_SPI/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD7367_SPI/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD7367_SPI/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD7367_SPI/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD7367_SPI.svg)](https://github.com/RobTillaart/AD7367_SPI/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD7367_SPI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD7367_SPI.svg?maxAge=3600)](https://github.com/RobTillaart/AD7367_SPI/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD7367_SPI.svg)](https://registry.platformio.org/libraries/robtillaart/AD7367_SPI)


# AD7367_SPI

Arduino library for the AD7367_SPI, 2 channel consecutive sampling 14 bit ADC.


## Description

**Experimental**

The AD7367 is a device with two ADC's which can be sampled simultaneously
at 14 bits with a theoretical speed of up to 1 MSPS.
The AD7366 is a similar 12 bits device.

This library uses a single channel to clock out both ADC values.
Therefore the theoretical speed is max 500KSPS.

One need to connect the **SPI.MISO** to one of the two dataOut channels of the device.
The library reads both ADC's over one channel and splits the data in an appropriate way.

See - https://github.com/RobTillaart/AD7367

**Warning** The library is not tested with hardware yet.

Feedback, issues, improvements are welcome.
Please file an issue on GitHub.

### Related

- https://github.com/RobTillaart/AD7367 simultaneous sampling 14 bit ADC.
- https://github.com/RobTillaart/AD7367_SPI consecutive sampling 14 bit ADC.
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
#include "AD7367_SPI.h"
```

### Constructor

- **AD7367_SPI(uint8_t select, uint8_t convert, uint8_t busy, __SPI_CLASS__ \* mySPI = &SPI)**
- **AD7366_SPI(uint8_t select, uint8_t convert, uint8_t busy, __SPI_CLASS__ \* mySPI = &SPI)**

|   pin     |   IO        |  description  |
|:----------|:------------|:--------------|
|  select   |  OUTPUT     |  Chip select
|  convert  |  OUTPUT     |  start conversion
|  busy     |   INPUT     |  conversion busy
|  mySPI    |  IN/OUTPUT  |  standard hardware SPI.


- **void begin()** initializes internal state.
- **uint8_t getType()** returns 67 or 66, depends on type (which constructor used)
- **int getBits()** returns resolution 12 or 14 bits, depends on type.


### Read

- **int read()** synchronous call to make a measurement from both ADC-A and ADC-B.
These values are stored in an internal buffer to be fetched with **getLastADCA()**
and **getLastADCB()**.
Note the **ADDR** line below determines which lines are read (a1, b1) or (a2, b2).
Actually it is a wrapper around the next three calls.
- **void triggerConversion()** asynchronous call to start ADC measurements.
- **bool conversionBusy()** returns true when the measurement are ongoing.
- **bool conversionReady()** returns true when the measurement are  ready.
- **int readAsync()** clocks in the data from the two ADC's of the device.
Should be called only when the measurements are ready.
- **int getLastADCA()** returns the last measurement of ADC-A
Multiple calls to **getLastADCA()** will result in the same value until new data
is read, either synchronous or asynchronous.
- **int getLastADCB()** returns the last measurement of ADC-A
Multiple calls to **getLastADCB()** will result in the same value until new data
is read, either synchronous or asynchronous.

The device has an option to read both measurements using only one data pin
however this is not supported. See SPI - single line section at the top.


### FastRead

- **int fastRead(int &a, int &b)** reads and returns two measurements by reference.
This function is more ideal e.g. to fill an array. See example.
Note the **ADDR** line below determines which lines are read (a1, b1) or (a2, b2).


### RANGE

Datasheet page 16, 17, table 8

- **void setRangePin(uint8_t range0, uint8_t range1)** define the two range pins.
- **int setRange(uint8_t range)** set range to 0, 1 or 2 see table below.
One should not set a range outside these values and one cannot change the range
when conversion is busy.
- **uint8_t getRange()** returns the set range or 255 if pins are not set.


|  range  |  RANGE1  |  RANGE0  |  selection     |  notes  |
|:-------:|:--------:|:--------:|:--------------:|:-------:|
|    0    |    LOW   |    LOW   |  ±10 Volt      |
|    1    |    LOW   |   HIGH   |   ±5 Volt      |
|    2    |   HIGH   |    LOW   |  0 to 10 V     |
|  other  |      -   |      -   |  NOT ALLOWED!  |  setRange() returns -1

Instead of setting the RANGE pins, one can hardwire these pins.

**DATASHEET WARNING** do not set both range pins to HIGH.  
(not clear what will happen, expect broken device)

**DATASHEET WARNING** do not change the range when conversion is busy.
**setRange()** returns -2 when busy.
(not clear what will happen)


### ADDR

Datasheet page 17

- **void setADDRpin(uint8_t pin)** define the ADDR pin, default LOW = (Va1, Vb1).
- **void ADDRwrite(uint8_t mode)** LOW = (Va1, Vb1) or HIGH = (Va2, Vb2)
input pins in the **read()** or **fastRead()** function.

Instead of setting the ADDR pin, one can hardwire this pin.


### REFSEL

Datasheet page 19

- **void setREFSELpin(uint8_t pin)** define the REFSEL pin, default HIGH = internal.
- **void REFSELwrite(uint8_t mode)** LOW = external voltage or LOW = internal 2.5 Volt.

Instead of setting the REFSEL pin, one can hardwire this pin.


### SPI

- **void setSPIspeed(uint32_t speed)** adjust SPI speed.
- **uint32_t getSPIspeed()** returns current SPI speed.


### Obsolete

- int getValue(channel) replaced by **int getLastADCA()** and **int getLastADCB()**.


## Future

#### Must

- keep in sync with AD7367
- improve documentation
- get hardware to test the library

#### Should

#### Could

- add SW SPI single data pin?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

