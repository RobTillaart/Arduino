
[![Arduino CI](https://github.com/RobTillaart/MCP3424/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP3424/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP3424/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP3424/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP3424/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP3424.svg)](https://github.com/RobTillaart/MCP3424/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP3424/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP3424.svg?maxAge=3600)](https://github.com/RobTillaart/MCP3424/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP3424.svg)](https://registry.platformio.org/libraries/robtillaart/MCP3424)



# MCP3424

Arduino library for 18 bit ADC I2C MCP3424 and compatibles.

## Description

**Experimental**

Library not tested with hardware yet.

This library is to be used to configure and read the 18 bit MCP4324 4 channel ADC et al.

The MCP3424 is not a fast ADC, however with 18 bit it has at least a very high 
resolution. What the effects of the long sampling time means is to be investigated.
The high resolution combined with an optional gain of 8x means one could 
measure voltage in steps of about 2 µV

The library has three functions that return a reading in volts, millivolts or 
microvolts to match the need of the user.

The user has to configure the ADC device (bits, gain) and can call
**read()** (et al) without parameters to keep usage straightforward.

Current implementation will probably change slightly in the future 
when related devices will be supported. (See future section).


Alt-230 = µ


### Resolution

|  Bits  |  LSB (gain=1)  |  SPS   |     Raw range       |  Notes  |
|:------:|---------------:|:------:|:-------------------:|:-------:|
|   12   |          1 mV  |  240   |    -2048 .. 2047    |
|   14   |        250 µV  |   60   |    -8192 .. 8191    |
|   16   |       62.5 µV  |   15   |   -32768 .. 32767   |
|   18   |     15.625 µV  |  3.75  |  -131072 .. 131071  |  not for 3426/27/28.

The effective resolution also depends on the gain set.
In theory with a gain of 8 the LSB of the 18 bit resolution represents 
1/8 of 15.625 µV == 1.95 µV. 
If this is feasible in practice is to be seen. 


### I2C Address

The MCP3421 has a fixed address 0x68, one can order different addresses at factory (how?).

TODO Table of addresses?

Max speed ? 400 KHz.


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


### Related

- https://gammon.com.au/adc  tutorial about ADC's (UNO specific)
- https://github.com/RobTillaart/ADS1x15  (12 & 16 bit ADC, I2C, slow)
- https://github.com/RobTillaart/PCF8591  (8 bit ADC + 1 bit DAC)
- https://github.com/RobTillaart/MCP_DAC  SPI based ADC.
- https://github.com/RobTillaart/MCP3424  18 bit ADC, I2C


## Interface

```cpp
#include "MCP3424.h"
```

### Constructor

TODO other constructors.

- **MCP3424(uint8_t address = 0x68, TwoWire \*wire = &Wire)** 
- **bool begin()** initializes the device. POR?
- **bool isConnected()** checks if the device address can be seen on I2C bus.
- **uint8_t getAddress()** idem, convenience function.
- **uint8_t getMaxChannels()** idem, convenience function.


### Read

- **int32_t read()** returns the raw reading.
- **float readVolts()** converts the raw reading to volts value (wrapper).
- **float readMilliVolts()** converts the raw reading to millivolts value (wrapper).
This is useful for small ranges.
- **float readMicroVolts()** converts the raw reading to microvolts value (wrapper).
This is useful for very small ranges (especially with a gain of 8 one has a 
resolution of about 2 microvolts. 


### Configuration

The user has to configure the ADC device (bits, gain) and can call
**read()** (et al) without parameters to keep usage straightforward.

Correct settings will be written to the device immediately, but be aware of the fact
that it will take some time before the conversion with new settings is done.

- **bool setChannel(uint8_t channel = 0)** not to be used for the MCP3421 as
it has only one channel. Default is channel 0, parameter should be less than the 
value of **getMaxChannels()**.
- **uint8_t getChannel()** returns chosen channel, 0 based. e
- **bool setGain(uint8_t gain = 1)** set gain to 1,2,4, or 8. 
Other values will return false and not change the setting.
- **uint8_t getGain()** returns the set gain (default 1).
- **bool setResolution(uint8_t bits = 12)** set the bit resolution 12,14,16 or 18.
Other values will return false and not change the setting.
- **uint8_t getResolution()** returns the set resolution.
- **void setContinuousMode()** idem.
- **void setSingleShotMode()** idem.
- **uint8_t getMode()** idem.

The set function write their changes directly to the device. It might be better
to have one function to set all parameters in one call. To be investigated.

The library caches the last configuration, it is not read back from the device.


## Future

#### Must

- get hardware to test.
  - redo interface for MCP3424 if needed.
- investigate ready flag
- investigate continuous vs single shot.
- improve documentation


#### Should

- implement support for (separate classes ?)
  - 18 bit, MCP3421/MCP3422/MCP3423
  - 16 bit: MCP3426/MCP3427/MCP3428 (no 18 bit so not 100% compatible)
- test on different boards.
- optimize performance (a lot of same math in conversion to voltage)
- optimize setting all configuration in one function call.
- PowerOnReset function for configuration


#### Could



#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


