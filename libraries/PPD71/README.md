
[![Arduino CI](https://github.com/RobTillaart/PPD71/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PPD71/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PPD71/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PPD71/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PPD71/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PPD71.svg)](https://github.com/RobTillaart/PPD71/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PPD71/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PPD71.svg?maxAge=3600)](https://github.com/RobTillaart/PPD71/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PPD71.svg)](https://registry.platformio.org/libraries/robtillaart/PPD71)


# PPD71

Arduino library for the PPD71 Particle Sensor Unit.


## Description

**Experimental**

This library is to use the PPD71 Particle Sensor Unit with an Arduino.

The device provides its measurements through a Serial interface.

Not tested with hardware yet.

Feedback as always is welcome.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment, 
and any other applications that may cause personal injury due to the product's failure._


### Related

- https://www.shinyei.co.jp/stc/eng/products/optical/ppd71.html

Other environment related

- https://www.co2.earth/ - current outdoor CO2 level can be used for calibrating.
- https://keelingcurve.ucsd.edu/ - historical outdoor CO2 level.
- https://github.com/RobTillaart/MTP40C - CO2
- https://github.com/RobTillaart/MTP40F - CO2
- https://github.com/RobTillaart/Cozir - CO2


## Interface

```cpp
#include "PPD71.h"
```

### Constructor

- **PPD71(Stream \* stream = &Serial)** set the stream to use. 
Typical this is a hardware Serial like Serial or Serial1 or 
optionally one can use a SoftwareSerial.

The communication parameters are 9600 Baud, 8 bit, no parity,
1 stop bit and no flow control (CTS/RTS or XON/XOFF)


### Data

- **bool dataAvailable()** returns true if there are 29 bytes in the buffer.
This is the packet size the device communicates.
- **void dataFlush()** flushes the input buffer of the stream used.
- **bool getData()** returns false if not enough data is available.
Extracts the data from the stream.

Data packet info

|  byte  |  meaning  |
|:------:|:----------|
|   0    |  STX == 0x02
|   1    |  Number of bytes to expect till EOT
|   2    |  Command == 0x10  (data info identifier?)
|  3-4   |  Average10  - 0..1000 µg/m³
|  5-6   |  Average30  - 0..1000 µg/m³
|  7-8   |  Average60  - 0..1000 µg/m³
|  9-10  |  Average180 - 0..1000 µg/m³
|  11-12 |  Pulse Ratio Output 0.5 µm
|  13-14 |  Pulse Ratio Output 0.7 µm
|  15-16 |  Pulse Ratio Output 1.0 µm
|  17-18 |  Pulse Ratio Output 2.5 µm
|  19-20 |  Status - unknown values.
|   21   |  Software version
|  22-25 |  Production number
|   26   |  ETX == 0x03
|   27   |  checkSum (sum % 256)
|   28   |  EOT == 0x04


ALT-0179 = cubed == ³
ALT-0181 = micro == µ

### Average

- **uint16_t getAverage10()** average number of particles over 10 seconds, 0..1000 µg/m³
- **uint16_t getAverage30()** average number of particles over 30 seconds. 0..1000 µg/m³
- **uint16_t getAverage60()** average number of particles over 60 seconds. 0..1000 µg/m³
- **uint16_t getAverage180()** average number of particles over 180 seconds. 0..1000 µg/m³


### Pulse Ratio 

Pulse Ratio: possible meaning (to verify).

The pulse ratio is the percentage (x100) of time that the sensor is detecting particles.

- **uint16_t getPulseRatio05()** 0..1000, 0.5 µm
- **uint16_t getPulseRatio07()** 0..1000, 0.7 µm
- **uint16_t getPulseRatio10()** 0..1000, 1.0 µm
- **uint16_t getPulseRatio25()** 0..1000, 2.5 µm


### Status

TODO unknown meaning

- **uint16_t getStatus()**


### Meta info

- **uint16_t getSWVersion()** idem.
- **uint16_t getProductNumber()** idem.


## Start up packet

Note this is **NOT** implemented.

The product info is sent at the startup of the device, 
within the first 2 seconds only (AFAIK).

Product info

|  byte  |  meaning  |
|:------:|:----------|
|   0    |  STX == 0x02
|   1    |  number of bytes to expect till EOT
|   2    |  command == 0x12  (product info identifier?)
|   3    |  software version
|   4    |  year
|   5    |  month
|   6    |  day
|  7-10  |  product number
|   11   |  ETX == 0x03
|   12   |  checkSum (sum % 256)
|   13   |  EOT == 0x04


## Future

#### Must

- improve documentation
- test with hardware


#### Should

- compatibles?
- add dump-example


#### Could

- add CRC check
- add error handling
- implement product info packet
- add unit tests


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


