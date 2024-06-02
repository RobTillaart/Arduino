
[![Arduino CI](https://github.com/RobTillaart/ADC08XS/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADC08XS/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADC08XS/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADC08XS/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADC08XS/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADC08XS.svg)](https://github.com/RobTillaart/ADC08XS/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADC08XS/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADC08XS.svg?maxAge=3600)](https://github.com/RobTillaart/ADC08XS/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADC08XS.svg)](https://registry.platformio.org/libraries/robtillaart/ADC08XS)


# ADC08XS

Arduino library for ADC082S, ADC084S, ADC102S, ADC104S, ADC122S, ADC124S, 8, 10, 12 bits, 2 or 4 channel ADC (SPI).


## Description

**Experimental**

This library provides six classes,
- dual channel: ADC082S, ADC102S and ADC122S.
- quad channel: ADC084S, ADC104S and ADC124S.

These are respectively an 8 bit, a 10 bit and a 12 bit ADC convertor.
The library supports both hardware and software SPI.
The interface is straightforward as one only need a **read()** call
to get the data.

This library does not support the single channel versions.
- See https://github.com/RobTillaart/ADC081S

The library does not support the I2C versions of these devices.
These can be recognized from the C as ADCxxxC

The library can put the device in **lowPower()** and needs a call to
**wakeUp()** to wake up. Alternative way to wake up the device is to
do a dummy **read()**.

The library is not tested with hardware yet.

Feedback is as always welcome.


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **ADC.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### Performance

Although the ADC08XS is rated at 200 KSPS and higher, an Arduino UNO will not
be able to fetch that much samples from the device. 
The reason is that an UNO cannot fetch the bits fast enough from the device.
At maximum SPI speed of 8 MHz one will get at most 50 KSPS. 

For the faster ones, see below, at 1 MSPS one need a clock of at least 16 MHz
+ time to process the incoming data. 
A faster processor like an ESP32 or Teensy might do the job.

Investigations should be made for a sort of continuous mode.
This would have the CS line constantly LOW and be able to read from the same
address over and over.

To be tested, feedback welcome.


#### Compatibles

There are 18 (multi channel) device types in this series, which can be used
with the six classes of this library.

|  device name  |  channels  |  bits  |  KSPS  |  Class    |  Notes  |
|:--------------|:----------:|:------:|:------:|:---------:|:-------:|
|  ADC082S021   |     2      |   8    |   200  |  ADC082S  |
|  ADC082S051   |     2      |   8    |   500  |  ADC082S  |
|  ADC082S101   |     2      |   8    |  1000  |  ADC082S  |
|  ADC102S021   |     2      |   10   |   200  |  ADC102S  |
|  ADC102S051   |     2      |   10   |   500  |  ADC102S  |
|  ADC102S101   |     2      |   10   |  1000  |  ADC102S  |
|  ADC122S021   |     2      |   12   |   200  |  ADC122S  |
|  ADC122S051   |     2      |   12   |   500  |  ADC122S  |
|  ADC122S101   |     2      |   12   |  1000  |  ADC122S  |
|  ADC084S021   |     4      |   8    |   200  |  ADC084S  |
|  ADC084S051   |     4      |   8    |   500  |  ADC084S  |
|  ADC084S101   |     4      |   8    |  1000  |  ADC084S  |
|  ADC104S021   |     4      |   10   |   200  |  ADC104S  |
|  ADC104S051   |     4      |   10   |   500  |  ADC104S  |
|  ADC104S101   |     4      |   10   |  1000  |  ADC104S  |
|  ADC124S021   |     4      |   12   |   200  |  ADC124S  |
|  ADC124S051   |     4      |   12   |   500  |  ADC124S  |
|  ADC124S101   |     4      |   12   |  1000  |  ADC124S  |

Type = ADC(bits)(channel)(protocol)(speed)1 
e.g ADC082S021 = 8 bits 2 channel SPI 200000
S == SPI.C == I2C.


#### Related

- https://github.com/RobTillaart/ADC081S  single channel version of this series.
- https://gammon.com.au/adc  tutorial about ADC's (UNO specific)
- https://github.com/RobTillaart/MCP_ADC
- https://github.com/RobTillaart/ADS1x15  (12 & 16 bit ADC, I2C, slow)
- https://github.com/RobTillaart/PCF8591  (8 bit ADC + 1 bit DAC)
- https://github.com/RobTillaart/MCP_DAC


## Interface

```cpp
#include "ADC08XS_MC.h"
```

#### Constructors

All six classes have identical interfaces as the ADC082S.

- **ADC082S_MC(SPIClassRP2040 \* mySPI = &SPI)** hardware constructor RP2040
- **ADC082S_MC(SPIClass \* mySPI = &SPI)** hardware constructor other
- **ADC082S_MC(uint8_t dataIn, uint8_t dataOut, uint8_t clock)**
- **void begin(uint8_t select)** set SELECT or CS pin.
- **int16_t maxValue()** returns maxReading of ADC, => 255, 1023, 4095
depending on number of bits of the actual ADC.
- **uint8_t maxChannel()** returns 2 or 4 depending on the class.


#### Base

- **uint16_t read(uint8_t channel)** reads the value of the device.
The parameter channel must be 0,1,2,3, depending on device.
Invalid channels will always return zero 0.
- **int deltaRead(uint8_t chanA, uint8_t chanB)** read channel A and B 
and return the difference.
Note that the value can be negative if read(B) > read(A) or zero.
if chanA == chanB there will be two reads of the same channel just
a few microseconds apart, most often returning 0. 
The function does not check if both channels are the same.
- **void setSPIspeed(uint32_t speed)** sets SPI clock in **Hz**, 
please read datasheet of the ADC first to get optimal speed.
- **uint32_t getSPIspeed()** returns current speed in **Hz**.


#### Low power

- **void lowPower()** put device in low power mode.
- **void wakeUp()** put device in normal power mode.
- **bool isLowPower()** returns true if in low power mode, so wakeUp needed().

Alternative way to wake up the device is to
do a dummy **read()**.


#### Debug

- **bool usesHWSPI()** returns true if hardware SPI is used.
- **uint32_t count()** returns number of reads since start.


## Future

#### Must

- improve documentation
- get hardware to test / verify working
- align with ADC081S where possible

#### Should

- investigate continuous read 
  - set CS once (or hardwired)
  - use a prepared address
  - just transfer.
  - how much faster?

#### Could

- unit tests possible?


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

