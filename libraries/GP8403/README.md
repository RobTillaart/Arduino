
[![Arduino CI](https://github.com/RobTillaart/GP8403/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/GP8403/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/GP8403/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/GP8403/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/GP8403/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/GP8403.svg)](https://github.com/RobTillaart/GP8403/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/GP8403/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/GP8403.svg?maxAge=3600)](https://github.com/RobTillaart/GP8403/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/GP8403.svg)](https://registry.platformio.org/libraries/robtillaart/GP8403)


# GP8403

Arduino library for GP8403, I2C 12 bit two channel DAC.


## Description

**Experimental**

This library is for the I2C GP8403 12 bit two channel DAC.

The GP8403 accepts values from 0 to 4095.

Besides the core **setValue(channel, value)** the library provides
convenience functions **setPercentage(channel, perc)**, **increment()**
 and **decrement()**.
Furthermore is allows to read back (from cache) the current value
per channel.

What makes the GP8403 different from other DAC's it that it has the
option to switch its output range from 5V to 10V. 
Please note this is done for both channels, so one cannot set the 
voltage per channel. So use with care!


|              |  GP8403     |  Notes  |
|:-------------|------------:|:--------|
|  Range       |  5 or 10 V  |
|  Resolution  |  12 bit     |
|  Channels    |   2         |
|  Max error   |   0.5 %     |
|  Max I2C     |  400 kHz    | to be verified

Feedback as always is welcome.


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._


### Hardware

```
             TOPVIEW GP8403
         +--------------------+
         |                    |
    SCL  | o 1          10  o |  5V
    SDA  | o 2           9  o |  A2
     A0  | o 3           8  o |  VOUT0
     A1  | o 4           7  o |  VOUT1
    VCC  | o 5           6  o |  GND
         |                    |
         +--------------------+
```

|  pin  |  name   |  description  |  Notes  |
|:-----:|:--------|:--------------|:-------:|
|   1   |  SCL    |  I2C clock    |
|   2   |  SDA    |  I2C data     |
|   3   |   A0    |  address pi   |
|   4   |   A1    |  address pi   |
|   5   |  VCC    |  Voltage      |  ??
|   6   |  GND    |  ground       |
|   7   |  VOUT0  |  channel 0    |
|   8   |  VOUT1  |  channel 1    |
|   9   |   A2    |  address pin  |
|  10   |  5 V    |  power        |



### Related

- https://github.com/robtillaart/AD5370 40 channel 16 bit DAC SPI
- https://github.com/RobTillaart/AD5680 1 channel 18 bit DAC SPI
- https://github.com/RobTillaart/AD7390 1 channel 12/10 bit SPI
- https://github.com/RobTillaart/DAC8550 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8551 1 channel, 16 bit
- https://github.com/RobTillaart/DAC8552 2 channel, 16 bit
- https://github.com/RobTillaart/DAC8554 4 channel, 16 bit
- https://github.com/RobTillaart/GP8403 I2C, 2 channel, 12 bit
- https://github.com/RobTillaart/MAX520 I2C, 4, 8 channel, 8 bit
- https://github.com/RobTillaart/MCP4725 I2C, 1 channel, 12 bit
- https://github.com/RobTillaart/MCP_DAC SPI based DACs


## I2C

### I2C Address

The device has a configurable address from 0x38..0x3F (== 56..63).
The address is configured by hardware with the A0, A1 and A2 pins.

Do not forget appropriate pull up resistors on the I2C SDA and SCL lines.

If one needs more DAC's there are some options.
- One could use an I2C multiplexer (see below)
- One could use an MCU with multiple I2C buses.
- One could use a (Two-Wire compatible) SW I2C.
(outside scope of this library).
- one could use one address pin (e.g. A2) as a select line.
(outside scope of this library).


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

Only test **setValue()** as that is the main function.


|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  default
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |
|   500 KHz  |             |
|   600 KHz  |             |


TODO: run performance sketch on hardware.


## Interface

```cpp
#include "GP8403.h"
```

### Constructor

- **GP8403(uint8_t address, TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
Sets default range to 5 Volt.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the address set in constructor.
- **bool setRange(uint8_t range)** Range can be 5 or 10 volt.
All other values map to 5 Volt.
- **uint8_t getRange()** idem, returns 0 if not initialized.

**Warning**: the range is set for both channels at the same time.
Changing the range will bump both outputs by a factor 2 up or down.
This can result in unexpected behaviour including damage to connected 
devices. So use with care.

- **uint8_t channels()** returns 2
- **uint16_t maxValue()** returns 0x0FFF = 4095


### Core

- **bool setValue(uint8_t channel, uint16_t value)** returns false
if parameter out of range, or if setting fails.
- **uint16_t getValue(uint8_t channel)** returns last set value from cache.
- **bool increment(uint8_t channel)** step interface, convenience.
- **bool decrement(uint8_t channel)** step interface, convenience.
- **bool setPercentage(uint8_t channel, float percentage)** percentage = 0.0 .. 100.0
- **float getPercentage(uint8_t channel)** returns set value as percentage.


### Debug

- **uint8_t getLastError()** returns last error of low level communication.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- writing both channels in one call?
  - same latching time! (assumption)
  - writing both DAC's e.g. zero.
- investigate compatibles
  - GP8413 - 15 bit 2 channel
- can values be read back from DAC?
  - slower but more accurate.
- improve error handling
- investigate storage settings for startup
  - non standard I2C commands.
- investigate performance
  - writing e.g. lower 4 bits only works?
  - 8 bit API by writing only higher 8 bits?

#### Could

- extend unit tests if possible.
- auto adjust range **set- getVoltage()**?
- is it possible to write 0x10 or 0x01 to register 1
  and set output voltage per channel?
  - not documented.


#### Wont

- related but not derived => own libs
  - GP8302, GP8211, GP8503, GP8512

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


