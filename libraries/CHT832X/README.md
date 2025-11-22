
[![Arduino CI](https://github.com/RobTillaart/CHT832X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CHT832X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CHT832X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CHT832X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CHT832X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/CHT832X.svg)](https://github.com/RobTillaart/CHT832X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CHT832X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CHT832X.svg?maxAge=3600)](https://github.com/RobTillaart/CHT832X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/CHT832X.svg)](https://registry.platformio.org/libraries/robtillaart/CHT832X)


# CHT832X

Arduino library for CHT832X temperature and humidity sensor.


## Description

**Experimental**

The CHT8320 and CHT8325 are temperature and relative humidity sensors. 
They both have the same interface, the CHT8325 is slightly more accurate.
The CHT832X are factory calibrated and have an unique NIST number 
(48 bit) to be globally trackable.

This library implements the most important functionality of the sensor.
This includes reading the temperature and humidity and the manufacturer-ID register.
Furthermore one can set an offset for temperature and humidity.

The API of the library is based upon https://github.com/RobTillaart/CHT8310
The sensors use a different protocol to communicate.

The library is tested to work with hardware, see issue 3.

Feedback as always is welcome, please share your experiences.


### Breaking change 0.3.0

Fixed temperature above 40 degrees Celsius - see #5


### Breaking change 0.2.0

The 0.1.0 version was not working, it is now obsolete.

The 0.2.0 version implements an asynchronous interface as one has to
wait 60 ms before one can read temperature and humidity.
This included a refactor of the low level (private) parts.


### Related

- https://github.com/RobTillaart/Temperature (e.g. heatIndex)
- https://github.com/RobTillaart/CHT8305
- https://github.com/RobTillaart/CHT8310
- https://github.com/RobTillaart/CHT832X
- https://github.com/RobTillaart/SHT31 - sort of command compatible!


## Hardware

Always check datasheet for connections.

```cpp
//
//             +---------------+
//     VCC ----| VCC           |
//     SDA ----| SDA  CHT832X  |
//     GND ----| GND           |
//     SCL ----| SCL           |
//             +---------------+
//
```

Pull ups are needed on SDA, SCL.


## I2C 

### Performance

I2C bus speeds is supported up to 1000 KHz (datasheet P4).

An indicative table of times in micros on an UNO R3 for various I2C clock speeds.
Note that the performance gain of higher clock speeds become less and less.
At the same time the robustness of the signal decreases (not visible in the table).

TODO: fill table

|  Version  |  Speed   |   Read   | getManufacturer  |
|:---------:|:--------:|:--------:|:----------------:|
|   0.3.0   |   50000  |          |                  |
|   0.3.0   |  100000  |          |                  |
|   0.3.0   |  200000  |          |                  |
|   0.3.0   |  300000  |          |                  |
|   0.3.0   |  400000  |          |                  |
|   0.3.0   |  600000  |          |                  |
|   0.3.0   |  800000  |          |                  |


### Addresses

The CHT8320 supports one fixed address, however one can order different 
versions with different addresses. Max 4 sensors per bus.

CHT8320-A-DNR .. CHT8320-D-DNR == 0x44 ..0x47  
CHT8325-A-DNR .. CHT8325-D-DNR == 0x44 ..0x47

Pull ups are needed on SDA and SCL.


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


## Interface

```cpp
#include "CHT832X.h"
```

### Constructor

- **CHT832X(const uint8_t address = CHT832X_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** Constructor 
with default address (0x44) and I2C bus.
- **int begin()** initializes internals.
Returns error status.
- **bool isConnected()** checks if address (default 0x40) can be seen on the I2C bus.
- **uint8_t getAddress()** returns address set in constructor.


### Asynchronous interface

- **int requestData()** triggers a new single shot conversion.
- **bool dataReady()** checks if 60 milliseconds have passed
since last request, indicating conversion ready.
- **int readData()** read the raw data, convert to T & H and
store them in cache until next readData() call.

The ASYNC interface will be extended when other acquisition modi
are supported. There are continuous modes that work differently.


### Synchronous interface

Note: the read() call wraps the ASYNC interface in a **blocking** call
which lasts for **60 milliseconds**.

- **int read()** reads both the temperature and humidity from the sensor.
Can be called at most once per second, otherwise it will return **CHT832X_ERROR_LASTREAD**
Return value should be tested and be **CHT832X_OK**.
- **uint32_t lastRead()** returns lastRead in milliSeconds since start sketch.
Useful to check when it is time to call **read()** again, or for logging.
LastRead is updated only when **read()** is successful.


### Get Temperature and Humidity

- **float getTemperature()** returns last temperature read.
Will return the same value until **read()** is called again.
- **float getHumidity()** returns last humidity read.
Will return the same value until **read()** is called again.


### Offset

Adding offsets works well in the "normal range" but might introduce 
under- or overflow at the ends of the sensor range.
These are not handled for temperature by the library, humidity is constrained.
  
- **void setHumidityOffset(float offset)** idem.
- **void setTemperatureOffset(float offset)** idem.
This function can be used to set return temperature in Kelvin, with offset = 273.15
- **float getHumidityOffset()** idem.
- **float getTemperatureOffset()** idem.

If the offset is not the same over the operational range, 
consider a mapping function for temperature and/or humidity.
e.g. https://github.com/RobTillaart/MultiMap


### Heater

Check datasheet for details.

The heater can be used to remove condense from the sensor - think humidity.
It is unclear how long the sensor may be heated. (feedback welcome).

The heater must be disabled when making measurements as the heating 
affects both the temperature and humidity. 
Note it might take some time to stabilize to "environment temperature" again.

- **void enableHeater()** switch on.
- **void enableHeaterFull()** set to full power level.
- **void enableHeaterHalf()** set to half power level.
- **void enableHeaterQuarter()** set to quarter power level.
- **void disableHeater()** switch off.

The status of the heater can be fetched with **getStatusRegister()**.
see below.


### Status register

Check datasheet for details.

- **uint16_t getStatusRegister()** See the table below.
- **void clearStatusRegister()** idem.

|  bit  |  name            |  description  |
|:-----:|:----------------:|:--------------|
|   13  |  heater status   |  0 = Heater disabled, 1 = heater enabled
|    4  |  reset detected  |  0 = no reset, 1 reset since last clearStatus
|    1  |  command status  |  0 = executed, 1 = not executed 
|    0  |  checksum        |  0 = pass, 1 = fail
| other |  reserved        |


### SoftwareReset

Check datasheet for details.

- **void softwareReset()** idem.


### Meta data

In issue https://github.com/RobTillaart/CHT832X/issues/7 it is reported that 
the CHT8320 does not have an unique NIST identifier (any more).
At the moment it is unknown if this is for one manufacturer or for all.
Feedback on this topic is welcome.

In short, the getNIST() function is probably not usable to identify your product.

- **uint16_t getNIST(uint8_t id)** id = 0, 1, 2; returns 2 x 3 = 6 bytes of 
the device ID. As said above, not guaranteed unique.
- **uint16_t getManufacturer()** Returns 0x5959 according to the datasheet.
Other manufacturers may return different number.


## Error codes

- **getError()** returns the last error status.
Resets internal error to CHT832X_OK.


|  value  |  define                  |  notes  |
|:-------:|:-------------------------|:--------|
|     0   |  CHT832X_OK              |  default
|   -10   |  CHT832X_ERROR_ADDR      |
|   -11   |  CHT832X_ERROR_I2C       |
|   -12   |  CHT832X_ERROR_CONNECT   |
|   -20   |  CHT832X_ERROR_LASTREAD  |
|   -21   |  CHT832X_ERROR_CRC       |


## Future

#### Must

- elaborate documentation.
- test with hardware if all works.

#### Should

- make read-delay of 60 ms configurable uint8_t (0.4.0 ?)
- test heater functions.
- test softwareReset().
- operational modi
  - single shot (supported)
  - continuous (#samples per second)
  - sleep?
- investigate missing functions.

#### Could

- test different platforms
  - AVR, ESP32, ESP8266, STM32, RP2040, ...
- add examples (which functions?)

### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


