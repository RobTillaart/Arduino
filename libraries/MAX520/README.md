
[![Arduino CI](https://github.com/RobTillaart/MAX520/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX520/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX520/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX520/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX520/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX520.svg)](https://github.com/RobTillaart/MAX520/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX520/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX520.svg?maxAge=3600)](https://github.com/RobTillaart/MAX520/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX520.svg)](https://registry.platformio.org/libraries/robtillaart/MAX520)


# MAX520

Arduino library for MAX520/521 4/8 channel 8 bit DAC.


## Description

**Experimental**

The MAX520 is a 4 channel 8 bit DAC. It has no output buffer amplifiers, 
giving it very low supply current.

The output range of the MAX520 4 DACs depends on the 4 VREF inputs.
You can have e.g. one from 0.0-5.0V  one from 0.0-3.3V and two from 0.0-2.5V.


The MAX521 is a 8 channel 8 bit DAC.  
The output range of the MAX521 8 DACs depends on the **FIVE** VREF inputs.
OUT0..OUT3 use VREF0..VREF3 and OUT4..OUT7 all use VREF4.


After calling **begin()** the user has to write the values per DAC or call **reset()**

#### Related

TODO other DAC libraries.



## I2C

#### I2C addresses

|  device  |  address pins  |   addresses    |
|:--------:|:--------------:|:--------------:|
|  MAX520  |     3          |  0x20 .. 0x27  |
|  MAX521  |     2          |  0x20 .. 0x23  |


#### I2C Performance

up to 400 KHz.


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


## Interface

```cpp
#include "MAX520.h"
```

**MAX520_INITIAL_VALUE** is a define 0xFF that can be set compile time or before
the include of "MAX520.h" to overrule the default value used with the **begin()** call.


#### Constructor

- **MAX520(uint8_t deviceAddress = 0x20, TwoWire \*wire = &Wire)** Constructor with optional address, default 0x20, 
and the optional Wire interface as parameter.
- **bool begin(uint8_t value = MAX520_INITIAL_VALUE)** set the initial value (default 0xFF) for the DACS.
- **bool isConnected()** checks if the address set in the constructor or by **setAddress()** is visible on the I2C bus.
- **bool setAddress(uint8_t deviceAddress)** sets the device address after construction. 
Can be used to switch between MAX520 modules runtime. Note this corrupts internal buffered values, 
so one might need to call **write()** again. Returns true if address can be found on I2C bus.
- **uint8_t getAddress()** Returns the device address.
- **uint8_t getChannels()** Returns the number of channels (4 or 8).


#### Read and Write

- **int write(uint8_t channel, uint8_t value)** writes value to chosen DAC.
- **int write(uint8_t \* values)** writes to all DACs. user must take care that array is large enough (4/8).
- **int read(uint8_t channel)** returns the last written value to chosen DAC. (from cache).


#### Reset and power down

- **int reset()**  TODO what values?
- **int powerDown()**
- **int wakeUp()**

TODO

#### Miscellaneous

- **int lastError()** returns the last error from the lib. (see .h file).


## Error codes

|  name                  |  value  |  description              |
|:-----------------------|:-------:|:--------------------------|
|  MAX520_OK             |  0x00   |  no error                 |
|  MAX520_CHANNEL_ERROR  |  0x81   |  channel nr out of range  |
|  MAX520_I2C_ERROR      |  0x82   |  I2C communication error  |



## Future

#### Must

- improve documentation.
- test with hardware
- stabilize.

#### Should

- error handling

#### Could



#### Wont

- add percentage API
- add vref array + add voltage interface


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


