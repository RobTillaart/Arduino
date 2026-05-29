
[![Arduino CI](https://github.com/RobTillaart/I2C_ABP2/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_ABP2/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_ABP2/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_ABP2/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_ABP2/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_ABP2.svg)](https://github.com/RobTillaart/I2C_ABP2/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_ABP2/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_ABP2.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_ABP2/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_ABP2.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_ABP2)


# I2C_ABP2

Arduino library for the Honeywell I2C ABP2 pressure sensors.


## Description

**Experimental**

This library is to use one of the pressure sensors of the I2C Honeywell
ABP2 series.
These sensors also exist with SPI interface but this library does not 
support the SPI interface.

The ABP2 sensor provides a pressure and a temperature measurement. 
Although technically one could read the pressure only, this optimization 
is not supported by the library. It could be added in the future.

As the sensor makes a measurement on request, which takes up to 10 milliseconds,
the library provides a separate request() and read() function. 
This to prevent a blocking call. See below.

The library is written based upon the datasheet and is not tested 
with hardware yet.

Feedback as always is welcome.


### Hardware

Check datasheet table 20.

```
        ABP2                MCU
    +----------+        +----------+
    |          |        |          |
    |       1 o|<------>|o GND     |
    |       2 o|<-------|o VCC     |
    |       3 o|------->|o EOC     |
    |       4 o|        |          |
    |       5 o|<------>|o SDA     |
    |       6 o|<-------|o SCL     |
    |          |        |          |
    +----------+        +----------+
```

|  pin  |   name   |  description        |  Notes  |
|:-----:|:--------:|:--------------------|:-------:|
|   1   |  GND     |  Ground             |
|   2   |  VCC     |  Power              |  TODO 3.3 or 5V.
|   3   |  EOC     |  End Of Conversion  |  not supported yet.
|   4   |  NC      |  not connected      |
|   5   |  SDA     |  I2C data           |
|   6   |  SCL     |  I2C clock          |   max 400 kHz.

The EOC pin is not supported in the library.


### Related

- https://github.com/RobTillaart/pressure - pressure conversions
- https://github.com/RobTillaart/Temperature - temperature conversions
- https://github.com/RobTillaart/I2C_ASDX - (I2C) pressure + conversions
- https://github.com/RobTillaart/I2C_ABP2 - this library
- https://github.com/RobTillaart/MS4525DO - (I2C) temperature pressure sensor
- https://github.com/RobTillaart/MS5837 - (I2C) temperature pressure sensor (incl pressure to altitude)
- https://github.com/RobTillaart/MS5611 - (I2C) temperature pressure sensor (incl pressure to altitude)
- https://github.com/RobTillaart/MSP300 - (I2C) industrial pressure transducer
- https://swharden.com/blog/2017-04-29-precision-pressure-meter-project/


### Tested

TODO:


## I2C

The sensor supports up to 400 kHz.

### I2C Address

Datasheet 6.3.
The address is hard coded in the sensor, so order the right type.

|  HEX  |  DEC  |
|:-----:|:-----:|
| 0x08  |    8  |
| 0x18  |   24  |
| 0x28  |   40  |
| 0x38  |   56  |
| 0x48  |   72  |
| 0x58  |   88  |
| 0x68  |  104  |
| 0x78  |  120  |


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

TODO: run performance sketch with hardware.

Only test **read()** as that is the main function.


|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 kHz  |             |  default 
|   200 kHz  |             |
|   300 kHz  |             |
|   400 kHz  |             |  max datasheet


## Interface

```cpp
#include "I2C_ABP2.h"
```

### Constructor

- **I2C_ABP2(uint8_t address, TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin(float minBar, float maxBar)** user must provide the range of 
the sensor in Bar (= 1000 mBar). 
A call to begin() allows the user to adjust the range runtime.
Returns true if the device is visible on the I2C bus, false otherwise.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the address set in constructor.


### Read

The interface of the sensor is made asynchronous as there is a delay needed
of around 10 milliseconds between a request for new data and the availability
of that new data. In this time the processor can do other tasks.

- **int request()** request a new measurement.
- **int read()** reads and converts the last measurement. 
Returns the status of the conversion.
- **uint32_t lastRead()** returns the time in milliseconds of last 
successful read() call. 


### Get data

These functions are used to retrieve the values from the last
**read()** action. Multiple calls will return the same value until new
data is read.

- **uint8_t getState()** idem
- **float getBar()** idem.
- **float getMilliBar()** wrapper for scaling.
- **float getKiloBar()** wrapper for scaling.
- **float getCelsius()** idem.


### Debug

- **int getLastError()** returns last error.


## Future

#### Must

- improve documentation
  - specs etc.
- test => get hardware

#### Should

- add examples
  - async demo
  - error handling
- improve error handling
- investigate support for EOC pin.

#### Could

- create unit tests if possible
- create a SPI_ADP2 library (on request only)
- support status only reading for performance
- support pressure only reading for performance
- improve error handling
- add getPSI() ? ==> pressure library.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


