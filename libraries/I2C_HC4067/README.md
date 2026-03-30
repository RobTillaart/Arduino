
[![Arduino CI](https://github.com/RobTillaart/I2C_HC4067/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_HC4067/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_HC4067/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_HC4067/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_HC4067/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_HC4067.svg)](https://github.com/RobTillaart/I2C_HC4067/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_HC4067/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_HC4067.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_HC4067/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_HC4067.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_HC4067)


# I2C_HC4067

Arduino library for HC4067 over I2C with a PCF8574.


## Description

**Experimental**

This library is to use an HC4067 multiplexer by means of a PCF8574 (I2C 8 channel IO).
The HC4067 allows e.g one analog port read up to 16 different analog channels,
or one digital port to read the state of 16 buttons.

Goal of this library is to reduce the number of pins to use for controlling an HC4067 multiplexer.
As there can be up to 16 PCF8574's on one I2C bus, this would allow to (in theory) 
control 16 HC4067 multiplexers over one I2C bus.
The price of less pins used is performance as an I2C write is much slower than
setting the IO pins directly.

The core API of the library is kept similar to my HC4067 library, (see related)
to allow easy transition. The constructor and I2C part is of course different.

The library is not tested with hardware yet (project pending).

The current version of this library has no error handling (in prep).

The current version of this library does not implement any function 
to control for the three remaining IO lines.

This library should work with a PCF8575 too although that would have 11 unused pins.
(see future section).


As always feedback is welcome.


### Related

- https://github.com/RobTillaart/HC4067 (1x16 mux)
- https://github.com/RobTillaart/MAX14661 (2x16 mux, I2C)
- https://github.com/RobTillaart/PCF8574 (I2C IO expander)


## Hardware connection

Connect the four **select pins** to pins 0..3 of your PCF8574.  
Connect the **enablePin E** to pin 4 of the PCF8574.  
Three pins of the PCF8574 are not connected.


```
        PCF8574                       HC4067
     +-------------+              +-------------+
     |             |              |             |
     |           0 |------------->| S0       Y0 |
     |           1 |------------->| S1       Y1 |
     |           2 |------------->| S2       Y2 |
     |           3 |------------->| S3       Y3 |
     |             |              |          Y4 |
     |           4 |------------->| Enable   Y5 |
     |           5 | NC           |          Y6 |
     |           6 | NC           |          Y7 |
     |           7 | NC           |          Y8 |
     | I2C         |              |          Y9 |
     +-------------+              |         Y10 |
       ||                         |         Y11 |
     +-------------+              |         Y12 |
     | I2C         |              |         Y13 |
     |        GND  |--------------| GND     Y14 |
     |        VCC  |--------------| VCC     Y15 |
     |             |              |             |
     |             |              |             |
     |        IOx  |<------------>| Z           |
     |             |              |             |
     +-------------+              +-------------+
       processor
       
       NC = Not Connected
```

Note: one could add a LED (+resistor) to the Enable line to have visual feedback.


### Tested

TODO.


## I2C

See - https://github.com/RobTillaart/PCF8574


### I2C Performance

The most expensive operation is **setChannel()** which needs to send 
three bytes to the device (+ 3x address = effectively 6 bytes).
Sending one byte (+ address) takes ~240 us (100 KHz) ==> 720 us in total.

Sending multiple bytes in one call (4 bytes) could be faster.
If the PCF8574 does not create ghost selections, writes can even be faster.
This not implemented in the current version, needs investigation.
(see future).


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
#include "I2C_HC4067.h"
```

### Constructor

- **I2C_HC4067(uint8_t address, TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the fixed address 0x2A (42).


### Channels

- **bool setChannel(uint8_t channel, bool disable = true)** set the current channel.
Valid values for channel are 0..15, returns false if channel out of range.  
If the channel is already selected it does not change it.
Note the four select lines may not change at the very same moment, 
possibly resulting in an invalid selection for a (very short) time.  
The disable flag can be set to false so the device is not disabled during channel switching.
Default the device is disabled during channel switching to prevent (very short) ghost channels.
Note that a call to **setChannel()** will always enable the device again.
Note the device cannot be disabled if there is no enable pin configured.
- **uint8_t getChannel()** returns the current channel 0..15.
The selected channel is also returned when the multiplexer is disabled.

The setChannel behavior needs investigation as the PCF8574 probably sets
all selection lines simultaneously.


### Enable

- **void enable()** enables the device to multiplex.
- **void disable()** disables the device, no channel is selected.
- **bool isEnabled()** returns the current status of the device (from cache).

Enabling / disabling does not change the channel.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- implement error handling.
  - mainly wire.transmission()
- investigate optimized **setChannel()**
- verify timing of the PCF8574 pins, are they simultaneous? (Ghost selection).
  - datasheet says update at ACK.
- investigate impact implement free IO pins?
  - readPin(n), writePin(n, HIGH/LOW);
  - need a variable to cache the write mask?
- is the SetChannel API intuitive?

#### Could

- investigate PCF8575 version to control 2 HC4067 devices (even 3).
  - API would need some "sub addressing"
- investigate MCP23S08 version as SPI is much faster
  - nr of lines reduced?
- investigate other multiplex libs
  - PCF8574 can control two HC4051 (3 select lines + Enable)
  - PCF8574 can control two HC4052 (2 select lines + Enable)
  - PCF8574 can control two HC4053 (2 select lines + Enable)

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


