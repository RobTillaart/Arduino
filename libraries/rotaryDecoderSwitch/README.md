
[![Arduino CI](https://github.com/RobTillaart/rotaryDecoderSwitch/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/rotaryDecoderSwitch/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/rotaryDecoderSwitch/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/rotaryDecoderSwitch/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/rotaryDecoderSwitch/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/rotaryDecoderSwitch.svg)](https://github.com/RobTillaart/rotaryDecoderSwitch/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/rotaryDecoderSwitch/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/rotaryDecoderSwitch.svg?maxAge=3600)](https://github.com/RobTillaart/rotaryDecoderSwitch/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/rotaryDecoderSwitch.svg)](https://registry.platformio.org/libraries/robtillaart/rotaryDecoderSwitch)


# rotaryDecoderSwitch

Arduino library for a PCF8574 based rotary decoder - supports 2 rotary encoders with a switch.


## Description

This experimental library uses a PCF8574 to read the pulses of a rotary encoder.
As a PCF8574 has 8 lines up to 2 decoders with a switch can be read over I2C.
The PCF interrupt line can be used to detect changes in the position of the encoders or if a switch is pressed.

If only 1 rotary encoders is connected one should use the lower bit lines as the 
library assumes these are used. Furthermore it is advised to connect the free PCF8574
pins to GND so you will not get unintended interrupts.

Strongly related to https://github.com/RobTillaart/rotaryDecoder

The interface is kept the same as much as possible.

```cpp
// connect up to 2 rotary encoders with a switch to 1 PCF8574.
//
//  RotaryEncoder    PCF8574      UNO         REMARKS
//  -----------------------------------------------------------
//   1 pin A          pin 0
//   1 pin B          pin 1
//   1 switch         pin 2                   (switch to gnd)
//                    pin 3                   (reserved)
//   2 pin A          pin 4
//   2 pin B          pin 5
//   2 switch         pin 6                   (switch to gnd)
//                    pin 7                   (reserved)
//
//                    SDA         A4
//                    SCL         A5
//
```

Note the above mapping is sort of compatible to using the rotaryDecoder class and using device 0 and 2 only,


#### Related

- https://github.com/RobTillaart/rotaryDecoder
- https://github.com/RobTillaart/PCF8574


## Interface

```cpp
#include "rotaryDecoderSwitch.h"
```

#### Constructor

- **rotaryDecoderSwitch(const int8_t address, TwoWire \*wire = Wire)**
constructor to set the address and optional the Wire bus.
- **bool begin(uint8_t count = 2)** UNO ea. initializes the class. 
count is the number of rotary encoders connected.
returns true if the PCF8574 is on the I2C bus.
- **bool isConnected()** returns true if the PCF8574 is on the I2C bus.


#### Core functions

- **uint8_t readInitialState()** read the initial state of the 2 rotary encoders. 
Typically called in setup only, or after a sleep e.g. in combination with **setValue()**.
Since 0.3.1 this function returns the read state, saves an additional read8() call.
- **bool checkChange()** used for polling to see if one or more RE have changed.
This function does NOT update the internal counters.
- **bool update()** returns true if there is a change detected.
It updates the internal counters of the RE. 
The counters will add +1 or -1 depending on rotation direction. 
Need to be called before **getValue()** or before **getKeyPressed()**. 
Note that **update()** must be called as soon as possible after the interrupt occurs 
or as often as possible when polling.  
Returns false if there is no change since last read.
- **bool updateSingle()** returns true if there is a change detected.
It updates the internal counters of the RE. 
This will add +1, +2 or +3 as it assumes that the rotary encoder 
only goes into a single direction.  
Returns false if there is no change since last read.


#### Counters & keypresses

- **int32_t getValue(uint8_r re)** returns the RE counter. (re = 0 or 1).
If the parameter re > 1 then 0 is returned.
- **bool setValue(uint8_r re, int32_t value = 0)** (re)set the internal counter to value, default 0.
If the parameter re > 1 then false is returned, true otherwise.
- **bool isKeyPressed(uint8_t re)** returns true if the switch is pressed of the RE selected (re = 0 or 1).
Note one needs to call **update()** first!


#### Read1 - Write1 - experimental

Warning the **write1(pin, value)** might alter the state of the rotary encoder pins.
So this functionality should be tested thoroughly for your application.
Especially the **write()** is **experimental**, see issue #10, feedback welcome.


**Read1()** and **write1()** are functions to access the pins of the PCF8574 that 
are not used for rotary encoders.
The user must guard that especially writing the pins do not interfere with the rotary encoder pins.

- **uint8_t read1(uint8_t pin)** reads a single pin (0..7).
Returns HIGH or LOW.
- **bool write1(uint8_t pin, uint8_t value)** writes a single pin (0..7).
Value should be LOW (0) or HIGH (other values).
- **uint8_t read8()** read all pins in one I2C IO action. When one need to access multiple 
input pins this is faster but need some bit masking.
- **bool write8(uint8_t value)** writes to multiple pins at once, e.g. to control multiple
LEDs in one IO action. As said before the user must guard not to interfere with the
rotary encoder pins.


#### Debugging

- **int8_t getLastPosition(uint8_r re)** (re = 0 or 1). Returns last position.


## Performance

As the decoder is based upon a PCF8574, a I2C device, the performance is affected by the 
clock speed of the I2C bus.
All four core functions have one call to **read8()** which is the most expensive part.

Early tests gave the following indicative times (Arduino UNO) for the **update()** 
function. 
Note that above 500 KHz the gain becomes less while reliability of signal decreases.
(500 KHz is about 3x faster than 100 KHz in practice.)
As 400 KHz is a standard I2C clock speed it is the preferred one.


|  I2C speed  |  time (us)  |  delta  |  %%   |  Notes  |
|:-----------:|:-----------:|:-------:|:-----:|:--------|
|   100 KHz   |      234    |         |       |
|   200 KHz   |      136    |    98   |  42%  |
|   300 KHz   |      100    |    36   |  26%  |
|   400 KHz   |       85    |    15   |  15%  |  preferred max
|   500 KHz   |       78    |     7   |   8%  |
|   600 KHz   |       67    |    11   |  14%  |  (strange outlier)
|   700 KHz   |       63    |     4   |   6%  |

(test results differ slightly from the rotaryEncoder class)


At 400 KHz it can update 2 rotary encoders in less than 90 us. 
At a 50% update percentage this implies a max of about 
5000 **update()** calls per second in theory.
**to be tested in practice**

Note that a high speed drill goes up to 30000 RPM = 500 RPS = 2000 interrupts per second, 
assuming 4 pulses == 360°. (not tested)


## Future

#### Must

- update documentation
  - add schema
- keep in sync with rotaryDecoder library

#### Should

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

