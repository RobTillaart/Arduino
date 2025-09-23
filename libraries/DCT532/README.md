
[![Arduino CI](https://github.com/RobTillaart/DCT532/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DCT532/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DCT532/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DCT532/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DCT532/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DCT532.svg)](https://github.com/RobTillaart/DCT532/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DCT532/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DCT532.svg?maxAge=3600)](https://github.com/RobTillaart/DCT532/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DCT532.svg)](https://registry.platformio.org/libraries/robtillaart/DCT532)


# DCT532

Arduino library for the DCT532, an I2C industrial pressure and temperature sensor.


## Description

**Experimental**

This library is to use the I2C DCT532 industrial pressure and temperature sensor. 
The library does not support the RS485 / MODbus version.

The DCT532 is a range of industrial pressure sensors made by BD SENSORS GmbH, 
www.bdsensors.de. The pressure ranges vary from 0..100 mbar up to 0..60 bar.
These sensors have an accuracy (IEC 61298-2) ≤ ± 0.25 % FSO (Full Scale Output).

This library only support the I2C interface, there exists also an RS485 version 
of the sensor which has more functionality (TODO verify).

The library is not tested with hardware yet.

TODO: extend info here.

For details read the datasheet (www.bdsensors.de).

Feedback as always is welcome.


### Types and range

Pressure range from 100 mbar .. 60 bar.

|  type  |  bar   |  peak  |  type  |  bar   |  peak  |  type  |  bar   |  peak  |
|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|
|  1000  |  0.10  |        |  1001  |  1.00  |        |  1002  |  10.0  |        |
|  1600  |  0.16  |        |  1601  |  1.60  |        |  1602  |  16.0  |        |
|  2500  |  0.25  |        |  2501  |  2.50  |        |  2502  |  25.0  |        |
|  4000  |  0.40  |        |  4001  |  4.00  |        |  4002  |  40.0  |        |
|  6000  |  0.60  |        |  6001  |  6.00  |        |  6002  |  60.0  |        |

Note: absolute pressure possible from 0.4 bar

Note: type x102 = -1..0 bar, type 9999 = custom.

TODO add peak to table.


### Related

- https://github.com/RobTillaart/pressure pressure conversions
- https://github.com/RobTillaart/Temperature temperature conversions 
- https://github.com/RobTillaart/MS5611 temperature pressure sensor 
- https://github.com/RobTillaart/MS5837 temperature pressure sensor 
- https://github.com/RobTillaart/MSP300 industrial pressure transducer
- https://swharden.com/blog/2017-04-29-precision-pressure-meter-project/


## I2C

The device has a fixed I2C address 0x28 (40 dec).


### I2C multiplexing

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


### I2C Performance

Only test **readSensor()** as that is the main function.


|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  default 
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |  max speed according to datasheet
|   500 KHz  |             |
|   600 KHz  |             |


TODO: run performance sketch on hardware.


## Interface

```cpp
#include "DCT532.h"
```

### Constructor

- **DCT532(uint8_t address, TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin(float maxPressure, float minPressure = 0)** sets the range of the sensor,
the maximum pressure needs to be set explicit. Furthermore it resets the internal variables.
Returns true if device address is visible on the I2C bus.
- **bool isConnected()** returns true if device address is visible on the I2C bus.
- **uint8_t getAddress()** Returns the address set in the constructor (convenience).


### Read

- **int readSensor()** does the actual reading of the sensor, 
returns DCT532_OK (0) or an error code.
- **float getPressure()** returns the last pressure in BAR.
- **float getTemperature()** returns the last temperature in degrees Celsius.
- **uint32_t lastRead()** timestamp in millis of last read.
Can be used for schedule timed measurements.


### Debug

- **int getLastError()** returns last error of the low level communication.

TODO: insert table

DCT532_OK = 0


## Future

#### Must

- improve documentation
- get hardware to test proper working of the library 

#### Should

- improve error handling
- other registers accesible over I2C?
- do performance test
- remove P and T as private variables when library works.
- write examples


#### Could

- create unit tests if possible
- derived classes for specific P sensors?
- do we need minimum pressure?
- do we need offsets to calibrate?
- float getPmin(), float getPmax() for debugging?  
- setType() getType() function ?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


