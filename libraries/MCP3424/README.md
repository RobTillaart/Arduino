
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

This library is to be used to configure and read the 18 bit MCP4324 4 channel ADC et al.

The MCP3424 is not a fast ADC, however with 18 bit it has a very high resolution.
What the effects of the long sampling time means is to be investigated.
The high resolution combined with an optional gain of 8x means one could
measure voltage in steps of about 2 µV. The range is -2.048 ... +2.048 volt.

Library is limited tested with MCP3421 hardware (0.1.3).

The library cannot check yet if a conversion is ready.
Need hardware to check how this works in detail.

The library has three functions that return a reading in Volts, milliVolts or
microVolts to match the need of the user.

The user has to configure the ADC device (bits, gain) and can call
**read()** (et al) without parameters to keep usage straightforward.

Current implementation will probably change slightly in the future
when related devices will be supported. (See future section).

As always feedback is welcome.

### Special chars

Alt-230 = µ


### Resolution

SPS = Samples per second

Interval is the time between consecutive reads in milliseconds. 
This is also the time to wait after the switching of a channel.

|  Bits  |  LSB (gain=1)  |  SPS   |  Interval  |     Raw range       |  Notes  |
|:------:|---------------:|:------:|:----------:|:-------------------:|:-------:|
|   12   |          1 mV  |  240   |    4.2 ms  |    -2048 .. 2047    |
|   14   |        250 µV  |   60   |   16.7 ms  |    -8192 .. 8191    |
|   16   |       62.5 µV  |   15   |   66.7 ms  |   -32768 .. 32767   |
|   18   |     15.625 µV  |  3.75  |  266.7 ms  |  -131072 .. 131071  |  not for 3426/27/28.

The effective resolution also depends on the gain set.
In theory with a gain of 8 the LSB of the 18 bit resolution represents
1/8 of 15.625 µV == 1.95 µV.
If this is feasible in practice is to be verified.


### Hardware

More configurations see datasheet.

```
         +-------------+
         | O  MCP3428  |
   CH1+  | 1        14 |  CH4-
   CH1-  | 2        13 |  CH4+
   CH2+  | 3        12 |  CH3-
   CH2-  | 4        11 |  CH3+
   VSS   | 5        10 |  adr1
   VDD   | 6         9 |  adr0
   SDA   | 7         8 |  SCL
         |             |
         +-------------+
```


### I2C Address

The MCP3421 and MCP3426 have a fixed address 0x68, one can order different
addresses at the factory (see datasheet).

The other devices have two address pins to set 8 addresses. 
The trick used is to leave address pins floating. 
See datasheet table 5.3 for details.


### I2C Speed

The MCP342x devices support 100 KHz, 400 KHz and 3.4 MHz.
The latter is not (yet) supported by the library.
The sketch **MCP3424_performance.ino** can be used to get some insight
in the performance. It will check up to 800 kHz.

Test with Arduino UNO MCP3421, times in microseconds.

|  Clock   |  read (18)  |  read (16)  |  read (14)  |  read (12)  |  setRes  |
|:--------:|:-----------:|:-----------:|:-----------:|:-----------:|:--------:|
|  100000  |     432     |     340     |     340     |     336     |    244   |
|  200000  |     248     |     192     |     188     |     196     |    144   |
|  400000  |     148     |     120     |     120     |     124     |    100   |
|  600000  |     120     |     100     |      96     |      96     |     80   |
|  800000  |     112     |      88     |      88     |      88     |     72   |

Note 0: figures are without conversion interval.
Note 1: 12-16 bits use same time for all clock speeds.
Note 2: above 600 K there is little gain.
Note 3: the chip can do 3.4 MHz, but this is not possible with UNO.

If you have figures for 3.4 MHz, please let me know.


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

- **MCP3424(uint8_t address = 0x68, TwoWire \*wire = &Wire)**
- **bool begin()** initializes the device. POR?
- **bool isConnected()** checks if the device address can be seen on I2C bus.
- **uint8_t getAddress()** idem, convenience function.
- **uint8_t getMaxChannels()** idem, convenience function.

The MCP3421/2/3/6/7/8 constructors have the same parameters.


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

#### Channels

- **bool setChannel(uint8_t channel = 0)** not to be used for the MCP3421 as
it has only one channel. Default is channel 0, parameter should be less than the
value of **getMaxChannels()**.
After changing a channel one has to wait an interval depending on the resolution used.
See table above.
- **uint8_t getChannel()** returns chosen channel (default 0).

#### Gain

- **bool setGain(uint8_t gain = 1)** set gain to 1,2,4, or 8.
Other values will return false and not change the setting.
- **uint8_t getGain()** returns the set gain (default 1).

#### Resolution

- **bool setResolution(uint8_t bits = 12)** set the bit resolution 12,14,16 or 18.
Other values will return false and not change the setting.
- **uint8_t getResolution()** returns the set resolution (default 12).
- **uint16_t getConversionDelay()** returns the delay in ms one has to wait at the
current resolution between calls to **setChannel()** and /or **read()**.
See Resolution section above.

#### Mode

- **void setContinuousMode()** idem.
- **void setSingleShotMode()** idem.
- **uint8_t getMode()** returns 0 for singleShot and 1 for continuous.

The set function write their changes directly to the device. It might be better
to have one function to set all parameters in one call. To be investigated.

The library caches the last configuration, it is not read back from the device.
This might be added in the future.


## Future

#### Must

- investigate reading of ready flag
- get hardware to test.
  - redo interface for MCP3424 if needed.
- investigate continuous vs single shot mode.
- improve documentation
  - Table of addresses.

#### Should

- test on different boards.
- optimize performance if possible
  - dividing by ```_gain``` ==> multiplication (faster?).
- check performance I2C with HW.
- optimize setting all configuration in one function call.
  - **setConfig(channel, resolution, gain, mode)** ?
  - getter needed?
- implement PowerOnReset function for configuration


#### Could

- implement maxResolution (combine with maxChannels? in one "maxValue" byte)
  - check range in **setResolution()**.
- extract gain and resolution from the configuration byte to reduce storage.
  - like **getMode()**.
  - need to read 5 bytes... see par 5.3.3
- extend examples
  - array of ADC's
- add error handling
  - add error variable
  - check return value **writeConfig()**.
  - check read() process.


#### Wont

- cache last read value. (difficult for wrappers)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


