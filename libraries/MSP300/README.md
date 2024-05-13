
[![Arduino CI](https://github.com/RobTillaart/MSP300/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MSP300/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MSP300/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MSP300/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MSP300/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MSP300.svg)](https://github.com/RobTillaart/MSP300/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MSP300/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MSP300.svg?maxAge=3600)](https://github.com/RobTillaart/MSP300/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MSP300.svg)](https://registry.platformio.org/libraries/robtillaart/MSP300)


# MSP300

Arduino library for I2C MSP300 pressure transducer.


## Description

**Experimental**

The MSP300 is an industrial digital pressure transducer. 
This library implements the I2C version (J) of the sensor.
The code is written based upon the datasheet, 
it is not actually tested by me yet.

The library does not implement the SPI or analog version.

Note: be aware to buy the right sensor: PSI/BAR, SPI/I2C/analog and I2C address as these are hardcoded.
OK, The pressure value can be converted with **Pressure** library, see below.

```
PSI = 1.45037737738e-5 * BAR;
BAR = 6.89475729318e+4 * PSI;
```

As the sensor is industrial quality, many applications can be realized with it.

Issues, remarks, experience and improvements are welcome, 
please open an issue on https://github.com/RobTillaart/MSP300.


#### 0.3.0 Bug fix

A read bug has been fixed and this makes all previous versions obsolete.

#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Available pressure ranges

Again: be aware to buy the right sensor: PSI/BAR, SPI/I2C/analog and I2C address as these are hardcoded.
(OK pressure output can be converted)

- PSI := 100, 200, 300, 500, 1K, 3K, 5K, 10K, 15K
- BAR := 7, 10, 20, 35, 70, 200, 350, 700, 1000


#### I2C connection

|  colour  |  description  |
|:--------:|:-------------:|
|  RED     |  2.7 – 5.0V   |
|  BLACK   |  GND          |
|  GREEN   |  SCL          |
|  WHITE   |  SDA          |
|  YELLOW  |  NC           |


#### Analog version

For Arduino analog output version 3 is also interesting.
It provide 0.5-4.5 volt output which matches many ADC ranges.

White wire is the output (page 4 datasheet).

The analog version is not supported in the library.


#### Related libraries

This library is related to:
- https://github.com/RobTillaart/I2C_ASDX Honeywell pressure sensors
- https://github.com/RobTillaart/MS5611 (I2C) air pressure & temperature sensor
- https://github.com/RobTillaart/MS5611_SPI air pressure & temperature sensor
- https://github.com/RobTillaart/Pressure to convert PSI to BAR and back.
 

## I2C

#### I2C Address

The MSP300 has a fixed address, however there a five different supported.
So without a multiplexer you can have up to 5 transducers on one I2C bus.
The address is in the product number of the sensor you buy. (check datasheet Page 7).

|  code  |  address  | decimal |
|:------:|:---------:|:-------:|
|    0   |   0x28    |   24    |
|    1   |   0x36    |   54    |
|    2   |   0x46    |   70    |
|    3   |   0x48    |   72    |
|    4   |   0x51    |   81    |


#### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up
to eight channels (think of it as I2C subnets) which can use the complete
address range of the device.

Drawback of using a multiplexer is that it takes more administration in
your code e.g. which device is on which channel.
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


#### I2C Speed

The sensor is specified to work at 100 - 400 KHz I2C.
An example performance sketch can be used to see the duration of
the most important **readPT()** call.

As I have no hardware yet, the performance figures are not available.
It is also not known yet if and how well the sensor operates above
and below the specified range.

To elaborate table with measurements.

|  I2C clock  |  readPT()  |  Notes  |
|:-----------:|:----------:|:-------:|
|     50000   |            |
|    100000   |            |
|    200000   |            |
|    300000   |            |
|    400000   |            |  max advised speed
|    500000   |            |
|    600000   |            |

Operating the sensor outside the specified range may cause incorrect 
readings and/or shorten lifetime. This is unknown territory.


## Interface

```cpp
#include "MSP300.h"
```

#### Constructor

The library has a number of functions which are all quite straightforward.

- **MSP300(uint8_t address = 0x20, TwoWire \*wire = &Wire)** constructor, 
default address and I2C bus.
- **bool begin(int maxValue)** initialize internals.
maxValue is the maximum pressure the sensor can read.
- **bool isConnected()** See if address set in constructor is on the bus.
- **bool setAddress(const uint8_t deviceAddress)** set address runtime 
e.g. when the address is unknown at compile time.
- **uint8_t getAddress()** returns address set.


#### Read

- **uint32_t readP()** read status and pressure.
Does not update the temperature.
Returns the raw value which is useful for debugging.
- **uint32_t readPT()** reads status, pressure and temperature.
Returns the raw value which is useful for debugging.
- **uint8_t getStatus()** returns status. Should be 0 after read.
- **float getPressure()** returns the pressure in PSI or BAR (whatever sensor you have).
For converting PSI to BAR or other pressure unit one can use the **Pressure** library.
See above.
Multiple calls will return the same (cached) value. 
Call readP() or readPT() to update.
- **float getTemperature()** returns the temperature in degrees Celsius. 
Compensated range 0..55° Celsius.
Multiple calls will return the same (cached) temperature. 
Call readPT() to update.


#### Calibration

Pressure calibration

- **void setPressureCounts(int Pmin = 1000, int Pmax = 15000)** set the count rates.
Use with care. Check datasheet for details.
- **int getPmin()** return current value.
- **int getPmax()** return current value.


#### Error handling

- **int lastError()** returns the last error set. Note: will reset the error!


## Error and Status codes

|  define                |  value  |
|:-----------------------|:-------:|
|  MSP300_OK             |    0    |
|  MSP300_RESERVED       |    1    |
|  MSP300_STALE_DATA     |    2    |
|  MSP300_READ_ERROR     |    3    |
|  MSP300_REQUEST_ERROR  |  100    |


## Operation

The examples show the basic working of the functions.


## Future

#### Must

- improve documentation
- get hardware
- test performance

#### Should

- add examples
- test accuracy?
- improve status / errorhandling

#### Could

- add Temperature calibration.
- unit tests
- add simple class for the analog version
  - MSP300A


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

