
[![Arduino CI](https://github.com/RobTillaart/LTC2485/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LTC2485/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LTC2485/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LTC2485/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LTC2485/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LTC2485.svg)](https://github.com/RobTillaart/LTC2485/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LTC2485/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LTC2485.svg?maxAge=3600)](https://github.com/RobTillaart/LTC2485/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LTC2485.svg)](https://registry.platformio.org/libraries/robtillaart/LTC2485)


# LTC2485

Arduino library for LTC2485 I2C 24 bit ADC.


## Description

**Experimental**

LTC2485 is an library for the LTC2485 24 bit ADC which is typically used
to monitor a voltage.

With a reference voltage of 5.0 Volt, a 24 bit ADC can in theory measure
voltages in the sub-microvolt range (LSB  = ~0.3 µV).
In practice there will be noise and one need a very stable VREF and test
setup to get accurate readings on that level.

The LTC2485 has an internal voltage that is proportional to temperature.
The library allows to read that voltage and converts it to temperature Celsius.
The formula can be calibrated a bit at the top of the LTC2485.cpp file.


Read the datasheet for the details.

As always, feedback is welcome.


### Tested

Tested with hardware during development.
More tests are needed to see if and how it can be improved.

See - https://forum.arduino.cc/t/ltc2485-arduino-library/1356147

At the release 0.1.3 there are still unsolved / unexplained fluctuations 
visible in the measurements during tests, especially in temperature.


### Key code

ALT230 = µ  (windows).


### I2C Address

From datasheet - table 4

|  CA1       |  CA0       |  address  |
|:----------:|:----------:|:---------:|
|  low       |  high      |    0x14   |
|  low       |  floating  |    0x15   |
|  floating  |  high      |    0x17   |
|  floating  |  floating  |    0x24   |
|  high      |  high      |    0x26   |
|  high      |  floating  |    0x27   |


### Performance

No data available yet.
To be measured when hardware is available.

If you have hardware and performance figures, please share them in an issue.
Please report the output of example **LTC2485_performance.ino** and the board used.


### Compatibles

Unknown so far, there exists a whole range of LTCxxxx ADC's.


### Related

- https://gammon.com.au/adc  tutorial about ADC's (UNO specific)
- https://github.com/RobTillaart/LTC2485  this library
- https://github.com/RobTillaart/MCP_ADC  SPI based ADC
- https://github.com/RobTillaart/ADS1x15  (12 & 16 bit ADC, I2C, slow)
- https://github.com/RobTillaart/PCF8591  (8 bit ADC + 1 bit DAC)
- https://github.com/RobTillaart/temperature converters


## Interface

```cpp
#include "LTC2485.h"
```

### Constructor and setup

- **LTC2485(uint8_t address, TwoWire \*wire = Wire)**
The address is 0x48..0x4F depending on the address pins.
The library does not check the range.
- **bool begin(float VREF = 5.0)** UNO ea. initializes the class.
Allows to set the reference voltage to calibrate the measurement.
Returns true if the LTC2485 address is on the I2C bus.
Note: do call **Wire.begin()** before **begin()**
- **bool isConnected()** Returns true if the LTC2485 address is on the I2C bus.
- **uint8_t getAddress()** Returns the address set in the constructor.


### Configure

- **int configure(uint8_t value)** set flags for next conversion.
Returns status of I2C, 0 == success write, other values == error.

Configuration bit masks, should be OR-ed.

|  name                     |  value  |  notes  |
|:--------------------------|:-------:|:--------|
|  LTC2485_REJECT_50_60_HZ  |  0x00   |  default
|  LTC2485_SPEED_1X         |  0x00   |  default
|  LTC2485_SPEED_2X         |  0x01   |
|  LTC2485_REJECT_50HZ      |  0x02   |
|  LTC2485_REJECT_60HZ      |  0x04   |
|  LTC2485_INTERNAL_TEMP    |  0x08   |

Flags LTC2485_REJECT_50HZ and LTC2485_REJECT_60HZ may **NOT** be used simultaneously.
Use LTC2485_REJECT_50_60_HZ instead.

Example configure() call:

```cpp
LTC.configure(LTC2485_SPEED_2X | LTC2485_REJECT_60HZ);
```


### Read

Read returns the last conversion and triggers a new conversion at the end.
So it might be needed to discard a first read.

- **int32_t getADC()** returns ADC value. Will configure ADC mode automatically
if needed. 
Returned range == -16777215..+16777215  
+16777216 == overflow  
-16777216 == underflow
- **float getVolts()** converts ADC value to volts.
- **float getMilliVolts()** converts ADC value to millivolts.
- **float getMicroVolts()** converts ADC value to microvolts.
- **float getTemperature()** returns internal temperature.
Will configure temperature mode automatically.
During first hardware tests it was impossible to get the temperature
stable. 
This needs more investigation in the future.
- **uint32_t lastAccesed()** track time in milliseconds of last access.
used internally to determine maximum delay needed for conversion.


## Future

#### Must

- improve documentation
  - performance section
  - compatibles section
- get hardware to test library

#### Should

- improve error handling
  - overflow / underflow
  - time out handling?
- fix TODO's in code and documentation

#### Could

- check pin compatible devices as derived class?
  - LTC2481 (16 bits) and LTC2483 (16 bits)
- calibrate internal temperature, something like
  - **void calibrateTemperature(float A, float B)**  420.0  1.40
  - TC = 27 + (Voltage - A) x B;
- create a 16 bit API which only gets 2 bytes instead of 4?
  - looses the "noisy" bits.
- performance measurements
  - I2C bus speed?
  - check math for improvements
- refactor for performance

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

