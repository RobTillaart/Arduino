
[![Arduino CI](https://github.com/RobTillaart/SWSPI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SWSPI/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SWSPI/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SWSPI/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SWSPI/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SWSPI.svg)](https://github.com/RobTillaart/SWSPI/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SWSPI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SWSPI.svg?maxAge=3600)](https://github.com/RobTillaart/SWSPI/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SWSPI.svg)](https://registry.platformio.org/libraries/robtillaart/SWSPI)


# SWSPI

Arduino library for SoftWare SPI.


## Description

**Experimental, use with care.**

The SPI protocol is a "standard" for serial communication, however there exists many variants.
This document only describe the four modi typical used in the Arduino context.

The SWSPI library implements a software implementation of SPI with 4 different modi.

The library is written for debugging purposes and might evolve to a real software SPI
implementation. It is shared as it might be useful for others.

- educational and debug purpose for now.
- very limited tested 
- master only
- no optimized performance
  - MSBFIRST is reversed LSBFIRST (reduces code size).
- does not implement SPIClass (yet),
  - goal is to follow the SPI API so it can be done in some future.

**Experimental, use with care.**


### SPI modes

There are 4 SPI MODES which encodes the clock polarity, phase and idle state.
The mode also defines at which edge data out should be present and when 
data in can be read.

The mode used is set in the **setTransaction()** call.

|  SPI MODE  |  polarity  |  phase  |  idle  |  data out  |  data in   |
|:----------:|:----------:|:-------:|:------:|:----------:|:----------:|
|     0      |      0     |    0    |    0   |   rising   |   falling  |
|     1      |      0     |    1    |    0   |   falling  |   rising   |
|     2      |      1     |    0    |    1   |   falling  |   rising   |
|     3      |      1     |    1    |    1   |   rising   |   falling  |


### Basic SPI transaction

```cpp
    //  set pins in "start position"
    myspi.beginTransaction(bitOrder, spiMode);

    //  select the device to communicate with
    //  must be done after beginTransaction() to prevent "false clock edges".
    digitalWrite(selectPin, LOW);
    //  do the IO
    data_in = myspi.transfer(data_out);
    //  unslect the device when ready.
    digitalWrite(selectPin, HIGH);

    //  close the transaction.
    myspi.endTransaction();
```


### Related

- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow
- https://github.com/RobTillaart/SWSPI
- https://docs.arduino.cc/learn/communication/spi/
- https://en.wikipedia.org/wiki/Serial_Peripheral_Interface


## Interface

```cpp
#include SWSPI.h
```


### Base

- **SWSPI(uint8_t dataIn, uint8_t dataOut, uint8_t clock))** constructor.
- **void begin()** 
- **void end()**
- **void setBitOrder(uint8_t bitOrder)** bitOrder must be MSBFIRST or LSBFIRST
- **void setDataMode(uint8_t dataMode)** dataMode must be in range 0..3

### Transfer

- **void beginTransaction(uint8_t bitOrder, uint8_t dataMode)**
  - bitOrder must be MSBFIRST or LSBFIRST
  - dataMode must be in range 0..3
- **void endTransaction()**
- **uint8_t transfer(uint8_t data)** send one byte.
- **void transfer(const void \*buf, size_t count)**
- **uint16_t transfer16(uint16_t data)** send two bytes.

//  TO BE TESTED
- **uint32_t transfer24(uint32_t data)** send three bytes.
- **uint32_t transfer32(uint32_t data)** send four bytes.


## Future

#### Must

- elaborate documentation
  - links to SPI explainers.
- test
- implement SPIclass interface

#### Should

- derived classes, read or write only.

#### Could

- add **void suppressInterrupts(bool flag = false)**
- code to .cpp file?
- add transfer24()
- unit test?


#### Won't (unless requested)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

