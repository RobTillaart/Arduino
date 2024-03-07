
[![Arduino CI](https://github.com/RobTillaart/MAX520/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX520/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX520/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX520/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX520/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX520.svg)](https://github.com/RobTillaart/MAX520/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX520/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX520.svg?maxAge=3600)](https://github.com/RobTillaart/MAX520/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX520.svg)](https://registry.platformio.org/libraries/robtillaart/MAX520)


# MAX520

Arduino library for MAX520 and MAX521 4/8 channel 8 bit DAC.


## Description

**Experimental**

The MAX520 is a 4 channel 8 bit DAC. The 520 has no output buffer amplifiers, 
giving it low supply current. See datasheet for details.

The output range of the MAX520 4 DACs depends on the **FOUR** VREF inputs.
You can have e.g. one from 0.0-5.0V, one from 0.0-3.3V and two from 0.0-2.5V.
This provides a flexibility, many other DAC's do not have.

The MAX520 is a write only device, so the library provides a cache of the last 
written values per DAC. These cached values are set to 0 when **begin()** is called. 
At startup and after **reset()** the outputs of the 4 DAC's are 0V.

The MAX521 is an 8 channel 8 bit DAC. The 521 has output amplifiers to they can
provide more current. See datasheet for details.

The output range of the MAX521 8 DACs depends on the **FIVE** VREF inputs.
OUT0..OUT3 use VREF0..VREF3 and OUT4..OUT7 all use VREF4.

After calling **begin()** the user has to write the values per DAC.

|  Device  |  Output   |   VREF   |  buffered  |  time  |  Notes  |
|:--------:|:---------:|:--------:|:----------:|:------:|:-------:|
|  MAX520  |  OUT_0    |  VREF_0  |     N      |   2    |
|  MAX520  |  OUT_1    |  VREF_1  |     N      |   2    |
|  MAX520  |  OUT_2    |  VREF_2  |     N      |   2    |
|  MAX520  |  OUT_3    |  VREF_3  |     N      |   2    |
|          |           |          |            |        |
|  MAX521  |  OUT_0    |  VREF_0  |     Y      |   6    |
|  MAX521  |  OUT_1    |  VREF_1  |     Y      |   6    |
|  MAX521  |  OUT_2    |  VREF_2  |     Y      |   6    |
|  MAX521  |  OUT_3    |  VREF_3  |     Y      |   6    |
|  MAX521  |  OUT_4..7 |  VREF_4  |     Y      |   6    |  shared VREF4  |

_time = time to settle a value in microseconds_

The MAX52x comes in various types with different working ranges (e.g. temperature).
See datasheet for details.

As always feedback about the library or device behaviour is welcome.


#### Related

- https://github.com/RobTillaart/MAX520
- https://github.com/RobTillaart/MCP_DAC
- https://github.com/RobTillaart/MCP4725
- https://github.com/RobTillaart/DAC8550
- https://github.com/RobTillaart/DAC8551
- https://github.com/RobTillaart/DAC8552
- https://github.com/RobTillaart/DAC8554



## I2C

#### I2C addresses

|  Device  |  Address pins  |  Address range   |
|:--------:|:--------------:|:----------------:|
|  MAX520  |     3          |    0x20..0x27    |
|  MAX521  |     2          |    0x20..0x23    |


#### I2C Performance

The devices are rated up to 400 KHz. Given that setting a DAC takes 3 bytes
and some ACK bits a maximum update speed is theoretical in the order of 
10 KHz for one channel (or 2.5 KHz for 4 channels). 
As it is possible to **write(array)** multiple channels in one transaction
the actual numbers might be slightly higher.

The settling time of a new value the MAX520 is 2 us and the MAX521 uses up 
to 6 us. This faster than I2C can provide new values.


TODO: No hardware test is done yet to measure performance.

|  speed   |  write  (us)  |  Notes  |
|:--------:|:-------------:|:-------:|
|   50000  |               |
|  100000  |               |
|  200000  |               |
|  300000  |               |
|  400000  |               |  max datasheet


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


#### Constructor

- **MAX520(uint8_t deviceAddress = 0x20, TwoWire \*wire = &Wire)** Constructor with optional address, default 0x20, 
and the optional Wire interface as parameter.
- **MAX521(uint8_t deviceAddress = 0x20, TwoWire \*wire = &Wire)** Constructor with optional address, default 0x20, 
and the optional Wire interface as parameter.
- **bool begin()** initializes all DAC's to 0V by calling **reset()**.
Returns false if the device cannot be seen on the I2C bus.
- **bool isConnected()** checks if the address set in the constructor or by **setAddress()** is visible on the I2C bus.
- **bool setAddress(uint8_t deviceAddress)** sets the device address after construction. 
Can be used to switch between MAX520 modules runtime. Note this corrupts internal cached last written values, 
so one might need to call **write()** again. Returns true if address can be found on I2C bus.
- **uint8_t getAddress()** Returns the device address.
- **uint8_t getChannels()** Returns the number of channels (4 or 8).


#### Read and Write

- **int write(uint8_t channel, uint8_t value)** writes a value 0..255 to the chosen DAC.
- **int write(uint8_t \* values)** writes to all DACs. 
The user must take care that the array is large enough to hold 4 or 8 values.
- **int read(uint8_t channel)** returns the last written value to chosen DAC. (from cache).


#### Reset and power down

- **int reset()** resets the values to 0V. Also clears the cache.
- **int powerDown()** sets device in a low current mode.
- **int wakeUp()** wakes up the device.

TODO: investigate the actual behaviour of the devices in PD mode.  
What effect does it have and are the cached values still actual / correct?

Feedback welcome.

#### Miscellaneous

- **int lastError()** returns the last error from the lib. (see .h file).


## Error codes

|  Name                  |  Value  |  Description              |
|:-----------------------|:-------:|:--------------------------|
|  MAX520_OK             |  0x00   |  no error                 |
|  MAX520_CHANNEL_ERROR  |  0x81   |  channel nr out of range  |
|  MAX520_I2C_ERROR      |  0x82   |  I2C communication error  |


## Future

#### Must

- improve documentation.
- test with hardware
  - verify behaviour of powerDown() / wakeup()


#### Should

- measure actual performance (I2C)


#### Could

- add **wakeUp(values)** ?  
- add **powerDown(values)** ?
- error handling
- add **writeAll(value)** ?


#### Wont

- add percentage API
- add vref array + add voltage interface


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


