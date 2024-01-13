
[![Arduino CI](https://github.com/RobTillaart/ADC081S/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADC081S/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADC081S/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADC081S/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADC081S/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADC081S.svg)](https://github.com/RobTillaart/ADC081S/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADC081S/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADC081S.svg?maxAge=3600)](https://github.com/RobTillaart/ADC081S/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADC081S.svg)](https://registry.platformio.org/libraries/robtillaart/ADC081S)


# ADC081S

Arduino library for ADC081S 8 bit, ADC101S 10 bit and ADC121S 12 bit ADC (SPI) single channel.


## Description

Experimental.

This library provides three classes, ADC081S, ADC101S and ADC121S.
These are respectively an 8 bit, a 10 bit and a 12 bit ADC convertor.
The library supports both hardware and software SPI.
The interface is straightforward as one only need a **read()** call
to get the data.

This library only supports the single channel versions.

The library can put the device in **lowPower()** and needs a call to
**wakeUp()** to wake up. Alternative way to wake up the device is to
do a dummy **read()**.

The library is not tested with hardware yet.

Feedback is as always welcome.


#### Performance

Although the ADC081S021 is rated at 200 KSPS, an Arduino UNO will not
be able to fetch that much samples from the device. 
The reason is that an UNO cannot fetch the bits fast enough from the device.
At maximum SPI speed of 8 MHz one will get at most 50 KSPS. 

For the faster ones, see below, at 1 MSPS one need a clock of at least 16 MHz
+ time to process the incoming data. 
A faster processor like an ESP32 or Teensy might do the job.

To be tested, feedback welcome.


#### Compatibles

Texas instruments has 9 devices in this series, which can be used with the
three classes of this library.

|  device name  |  bits  |  KSPS  |  Class    |  Notes  |
|:--------------|:------:|:------:|:---------:|:-------:|
|  ADC081S021   |   8    |   200  |  ADC081S  |
|  ADC081S051   |   8    |   500  |  ADC081S  |
|  ADC081S101   |   8    |  1000  |  ADC081S  |
|  ADC101S021   |   10   |   200  |  ADC101S  |
|  ADC101S051   |   10   |   500  |  ADC101S  |
|  ADC101S101   |   10   |  1000  |  ADC101S  |
|  ADC121S021   |   12   |   200  |  ADC121S  |
|  ADC121S051   |   12   |   500  |  ADC121S  |
|  ADC121S101   |   12   |  1000  |  ADC121S  |

Type = ADC(bits)(channel)S(speed)1 e.g ADC081S021 = 8 bits 1 channel 200000


#### Related

- https://gammon.com.au/adc  tutorial about ADC's (UNO specific)
- https://github.com/RobTillaart/MCP_ADC
- https://github.com/RobTillaart/ADS1x15  (12 & 16 bit ADC, I2C, slow)
- https://github.com/RobTillaart/PCF8591  (8 bit ADC + 1 bit DAC)
- https://github.com/RobTillaart/MCP_DAC


## Interface

```cpp
#include "ADC081S.h"
```

#### Constructors

The ADC101S and ADC121S have an identical interface as the ADC081S.

- **ADC081S(SPIClassRP2040 \* mySPI = &SPI)** hardware constructor RP2040
- **ADC081S(SPIClass \* mySPI = &SPI)** hardware constructor other
- **ADC081S(uint8_t dataOut, uint8_t clock)**
- **void begin(uint8_t select)** set select pin.
- **int16_t maxValue()** returns maxReading of ADC, => 255, 1023, 4095
depending on number of bits / class.

#### Base

- **uint16_t read()** reads the value of the device.
- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**, please read datasheet
of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** returns current speed in **Hz**.

#### Low power

- **void lowPower()** put device in low power mode.
- **void wakeUp()** put device in normal power mode.
- **isLowPower()** returns true if in low power mode, so wakeUp needed().

#### Debug

- **bool usesHWSPI()** returns true if hardware SPI is used.
- **uint32_t count()** returns number of reads since start.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should


#### Could

- unit tests possible?
- investigate multichannel series
  - ADC122S101  2 channel series
  - ADC124S101  4 channel series
  - need own (6) classes 
  - needs channel selection => so need dataout
  - need a control byte with channel select (bit 3,4,5)


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

