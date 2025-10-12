
[![Arduino CI](https://github.com/RobTillaart/FastShiftInOut/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FastShiftInOut/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FastShiftInOut/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FastShiftInOut/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FastShiftInOut/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/FastShiftInOut.svg)](https://github.com/RobTillaart/FastShiftInOut/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FastShiftInOut/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FastShiftInOut.svg?maxAge=3600)](https://github.com/RobTillaart/FastShiftInOut/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/FastShiftInOut.svg)](https://registry.platformio.org/libraries/robtillaart/FastShiftInOut)


# FastShiftInOut

Arduino library for **AVR** optimized shiftInOut (simultaneously).

## Description

**Experimental**

FastShiftInOut is a class that has optimized code (**AVR** only) to send and receive 
bytes simultaneously. In that sense it mimics a SPI bus.
It speeds up the shift using low level ports and masks. These are predetermined
in the constructor of the FastShiftOut object.

If not an **ARDUINO_ARCH_AVR** or **ARDUINO_ARCH_MEGAAVR** the class falls back 
to a default non optimized implementation. 

The library allows to set (and get) the bitOrder and apply this to multiple write()
calls. It also provide access to **writeLSBFIRST()** and **writeMSBFIRST()** which 
are the low level workers and most optimized code (so far).

Note: the bitOrder of the byte read and the byte written are the same.


### 0.2.0 breaking changes

The 0.2.0 version has a flag to unroll the inner loop in **writeLSBFIRST()**
and **writeMSBFIRST()**. The unrolled loop blocks the interrupts per byte.

Note: this optimization is new and thus experimental.
Feedback, including improvements, is welcome.


### Performance


#### Measurements (pre 0.2.0)

Performance of **write()**

|  version  |  UNO (us)  |  ESP32 (us)  |
|:---------:|-----------:|-------------:|
|   0.1.0   |   181.08   |     4.32     |
|   0.1.1   |    26.84   |     4.32     |
|   0.1.2   |    26.84   |    no data   |
|   0.1.3   |    25.52   |     4.32     |


#### Measurements

(0.2.1)  
Indicative time in microseconds, Arduino UNO, IDE 1.8.19, measured over 1000 calls.  
(delta between 2 calls and 1 call to eliminate overhead)

|  function                |   0.1.3  |   0.2.0  |   0.2.0L  |   0.2.1  |   0.2.1L  |
|:-------------------------|---------:|---------:|----------:|---------:|----------:|
|  write() (reference)     | no data  |  158.24  |  no data  |  158.24  |  no data  |
|  write()                 |   25.52  |   17.61  |    12.26  |   16.72  |    11.00  |
|  writeLSBFIRST()         |   25.52  |   17.61  |    12.26  |   16.72  |    11.00  |
|  writeMSBFIRST()         |   25.52  |   17.60  |    12.20  |   16.72  |    10.94  |


- Note: 0.1.3 added from old table.
- Note: reference run on AVR by commenting all optimizations.
- Note: 0.2.0 measured with loop unroll flag disabled.
- Note: 0.2.0L measured with loop unrolled flag enabled.
- Note: 0.2.1 / 0.2.1L idem.


### Related

- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow
- https://github.com/RobTillaart/SWSPI (experimental)


## Interface

```cpp
#include "FastShiftInOut.h"
```

### Constructor

bitOrder = { LSBFIRST, MSBFIRST };

- **FastShiftInOut(uint8_t dataIn, uint8_t dataOut, uint8_t clockPin, uint8_t bitOrder = LSBFIRST)** Constructor.

### Functions

- **uint8_t write(uint8_t data)** reads and writes simultaneously.
- **uint8_t lastWritten(void)** returns last byte written.
- **uint8_t lastRead(void)** returns last byte read.
- **uint8_t writeLSBFIRST(uint8_t data)** lowest level function, optimized for LSB.
- **uint8_t writeMSBFIRST(uint8_t data)** lowest level function, optimized for MSB.

### BitOrder

- **bool setBitOrder(uint8_t bitOrder)** bitOrder must be LSBFIRST or MSBFIRST.
- **uint8_t getBitOrder(void)** idem.

## Future

#### Must

- Update documentation
- Follow FastShiftIn and FastShiftOut

#### Should


#### Could


#### Wont

- **void ignoreRead()** => would in effect be FastShiftIn()
- add Print interface?
  - meaning of the return value is not defined.

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


