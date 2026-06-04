
[![Arduino CI](https://github.com/RobTillaart/A02YYUW/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/A02YYUW/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/A02YYUW/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/A02YYUW/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/A02YYUW/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/A02YYUW.svg)](https://github.com/RobTillaart/A02YYUW/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/A02YYUW/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/A02YYUW.svg?maxAge=3600)](https://github.com/RobTillaart/A02YYUW/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/A02YYUW.svg)](https://registry.platformio.org/libraries/robtillaart/A02YYUW)


# A02YYUW

Arduino library for A02YYUW Serial distance sensor.


## Description

**Experimental**

This library is to use the DFRobotics **A02YYU** and **A02YYUW** Serial distance sensor.

The A02YYU(W) has a range of max 3.0 to 4.5 meter (10 to 15 feet).
The UW version has an IP67 coating so it can be used outdoors in most 
weather conditions.

The library is confirmed to work, see tested section below.

Furthermore the library has (derived) classes for the **UART CONTROLLED**
types devices (A02YYT, A02YYTW).
These devices need a trigger pulse on the RX line.
This is not tested yet, but is expected to work.

These devices work with a hardware Serial only.

Feedback as always is welcome.


### Hardware

The connector of the A02YYU(W) is a 4-pin JST-PH (2.0mm pitch)
with the following pins.

|  colour  |  name  |  description      |  Notes  |
|:---------|:------:|:------------------|:-------:|
|  RED     |  VCC   |  power 3.3 - 5V   |
|  BLACK   |  GND   |  ground           |
|  YELLOW  |  RX    |  receive 3.3V     |
|  WHITE   |  TX    |  transmit 3.3V    |  use voltage divider if needed.

The device draws 8 mA average (see DFRobotic website).


### Compatible or not

The A02YYUW is one from a series, these are not all compatible.
From a datasheet.

|  Model            |  Output interface  |  Supported  |
|:-----------------:|:-------------------|:------------|
| DYP-A02YYU-V2.0   |  UART Auto         |  yes, confirmed
| DYP-A02YYUW-V2.0  |  UART Auto         |  yes, confirmed
|                   |                    |
| DYP-A02YYT-V2.0   |  UART Controlled   |  trigger with request()
| DYP-A02YYTW-V2.0  |  UART Controlled   |  trigger with request()
|                   |                    |
| DYP-A02YYM-V2.0   |  PWM Output        |  no, example might work
| DYP-A02YYMW-V2.0  |  PWM Output        |  no, example might work
|                   |                    |
| DYP-A02YYGD-V2.0  |  Switch output     |  no
| DYP-A02YYGDW-V2.0 |  Switch output     |  no
|                   |                    |
| DYP-A02YY4W-V2.0  |  RS485 output      |  no


Details see - https://www.dypcn.com/uploads/A02-Output-Interfaces.pdf

Missing (compatible) devices? Other remarks? Please open an issue on GitHub.


### Related

- https://github.com/RobTillaart/SRF05 - distance sensor
- https://github.com/RobTillaart/US500 - US500 + US4000 underwater distance sensor.
- https://github.com/RobTillaart/lengthConverter
- https://github.com/RobTillaart/printHelpers - printing.
- https://wiki.dfrobot.com/sen0311/docs/21654


### Tested

The library is confirmed to work.
- https://forum.arduino.cc/t/a02yyuws-measurement-results-are-unstable/1442997/16

More feedback is welcome, please open an issue on GitHub.


## Interface

```cpp
#include "A02YYUW.h"
```

### Constructor

- **A02YYU(Stream \* str, uint8_t TX)** Set the hardware serial port to use,
and the TX pin of MCU == RX of device.
Note one has to call Serial.begin() before using the A02YYU object.
- **A02YYUW(Stream \* str, uint8_t TX)** idem A02YYU.
- **A02YYT(Stream \* str)** Set the hardware serial port to use.
Note one has to call Serial.begin() before using the A02YYT object.
- **A02YYTW(Stream \* str, uint8_t TX)** idem A02YYT.
- **void begin()** reset internals.


### UART auto specific

The A02YYU and A02YYUW send a constant stream of data.
The RX pin is used to set mode.

|   RX   |  mode   |  description  |  time(ms)  |  notes  |
|:------:|:-------:|:--------------|:-----------|:--------|
|  HIGH  |  true   |  processed    |  100-500   |  more stable
|  LOW   |  false  |  real time    |  100       |

- **void setProcessingMode(bool mode)** see table above.
- **bool getProcessingMode()** see table above.


### UART controlled specific

The A02YYT and A02YYTW need a trigger before they will send data.
This is done by sending a pulse on the RX pin.

- **void request()** triggers a measurement for UART CONTROLLED
type devices.


### Distance

- **bool newDistance()** the workhorse, checks for new byte arrivals.
Syncs with the header byte so it knows which following bytes to
convert to a distance in millimetres.
Returns true if a new distance is available.
Returns false if not all bytes have arrived.
The user should **always** check the error flag with **getLastError** as this can be set. See below.
- **uint16_t getDistanceMM()** returns the last read distance in millimetres.
- **float getDistanceCM()** returns the last read distance in centimetres.
- **float getDistanceINCH()** returns the last read distance in inches.
Uses decimal inches e.g. 4.2, does not use 1/8th or 1/16th.

Note: the printHelpers class can help formatting the print e.g. in inches.


### Control

- **uint32_t lastRead()** time in millis of last successful read.
Can be used to read new distances at regular intervals.
- **void flush()** empties the input buffer of the Stream so next
value is a recent one.
Can be used after a restart or if communication is out of sync
(although it should auto recover).


### Error

- **int getLastError()** returns error flag.

|  error state        |  value  |
|:--------------------|--------:|
|  A02YY_OK           |      0  |
|  A02YY_ERR_CRC      |   -100  |
|  A02YY_ERR_TIMEOUT  |   -101  |

- **A02YY_OK** => no action required.
- **A02YY_ERR_CRC** => CRC error in a new measurement, however
the read distance can still be valid as the CRC does not indicate
which byte(s) failed. A comparison with the last returned distance
should be done.
- **A02YY_ERR_TIMEOUT** => communication failure.
Too few bytes arrived since the last header byte was detected,
or since start of program.
This error will occur too if bytes arrive and there is no header detected.



## Future

#### Must

- improve documentation
- get hardware to test (see tested section).

#### Should

- clean up class hierarchy.
  - not all need the TX pin
- add sanity checks (improve error handling?)
  - add checksum check => error flag or just false?
  - add high check < 0x12 (max for 4500 mm; 0x1F ~8191 mm)

#### Could

- create unit tests if possible
- create a library for the PWM devices A02YYM, A02YYMW
- create a library for the SWITCH devices A02YYGD, A02YYGD

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


