
[![Arduino CI](https://github.com/RobTillaart/rotaryDecoderSwitch5/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/rotaryDecoderSwitch5/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/rotaryDecoderSwitch5/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/rotaryDecoderSwitch5/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/rotaryDecoderSwitch5/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/rotaryDecoderSwitch5.svg)](https://github.com/RobTillaart/rotaryDecoderSwitch5/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/rotaryDecoderSwitch5/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/rotaryDecoderSwitch5.svg?maxAge=3600)](https://github.com/RobTillaart/rotaryDecoderSwitch5/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/rotaryDecoderSwitch5.svg)](https://registry.platformio.org/libraries/robtillaart/rotaryDecoderSwitch5)


# rotaryDecoderSwitch5

Arduino library for a PCF8575 based rotary decoder - supports 5 rotary encoders with a switch.


## Description

This library uses a PCF8575 to read the pulses of a rotary encoder.
As a PCF8575 has 16 lines up to 5 decoders with a switch can be read over I2C.
The PCF interrupt line can be used to detect changes in the position of the encoders 
or if a switch is pressed.

If only 1 rotary encoders is connected one should use the lower bit lines as the 
library assumes these are used. Furthermore it is advised to connect the free PCF8575
pins to GND so you will not get unintended interrupts.

Strongly related to https://github.com/RobTillaart/rotaryDecoder

The interface is kept the same as much as possible.

```cpp
// connect up to 5 rotary encoders with a switch to 1 PCF8575.
//
//  RotaryEncoder    PCF8575      UNO
//  --------------------------------------
//   1 pin A          pin 0
//   1 pin B          pin 1
//   1 switch         pin 2
//   2 pin A          pin 3
//   2 pin B          pin 4
//   2 switch         pin 5
//   3 pin A          pin 6
//   3 pin B          pin 7
//   3 switch         pin 8
//   4 pin A          pin 9
//   4 pin B          pin 10
//   4 switch         pin 11
//   5 pin A          pin 12
//   5 pin B          pin 13
//   5 switch         pin 14
//   free to use      pin 15
//
//                    SDA         A4
//                    SCL         A5
```

Note: This library works (limited) with the PCF8574 (max 2 devices).

As always, feedback is welcome.


### Related

- https://github.com/RobTillaart/rotaryDecoder
- https://github.com/RobTillaart/rotaryDecoderSwitch
- https://github.com/RobTillaart/rotaryDecoder8
- https://github.com/RobTillaart/rotaryDecoderSwitch5
- https://github.com/RobTillaart/PCF8574
- https://github.com/RobTillaart/PCF8575


## Interface

```cpp
#include "rotaryDecoderSwitch5.h"
```

#### Constructor

- **rotaryDecoderSwitch5(const int8_t address, TwoWire \*wire = Wire)**
constructor to set the address and optional the Wire bus.
- **bool begin(uint8_t count = 5)** UNO ea. initializes the class. 
count is the number of rotary encoders connected.
Returns true if the PCF8575 is on the I2C bus.
- **bool isConnected()** returns true if the PCF8575 is on the I2C bus.
- **uint8_t getRECount()** returns number of RE's from begin(), 
convenience e.g. for for loops.
- **void reset()** reset all internal counters to 0.

### Core functions

- **uint8_t readInitialState()** read the initial state of the 5 rotary encoders. 
Typically called in setup only, or after a sleep e.g. in combination with **setValue()**.
This function returns the read state, saves an additional read8() call.
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
Typical use is for a RPM measurement.
Note that the **getValue()** can go 3x as fast if you turn in the other direction.
Returns false if there is no change since last read.


### Counters & keypresses

- **int32_t getValue(uint8_r re)** returns the RE counter. (re = 0..4).
If the parameter re > 4 then 0 is returned.
The max value is ± 2147483647.
- **bool setValue(uint8_r re, int32_t value = 0)** (re)set the internal counter to value, default 0.
If the parameter re > 4 then false is returned, true otherwise.
- **bool isKeyPressed(uint8_t re)** returns true if the switch is pressed of the RE selected (re = 0..4).
Note one needs to call **update()** first!


### Read1 - Write1

**Warning**

The **write1(pin, value)** might alter the state of the rotary encoder pins.
So this functionality should be tested thoroughly for your application.
Especially the **write1()** is **experimental**, feedback welcome.

**Read1()** and **write1()** are functions to access the pins of the PCF8574 that 
are not used for rotary encoders.
The user must guard that especially writing the pins do not interfere with the 
rotary encoder pins.

- **uint8_t read1(uint8_t pin)** reads a single pin (0..7).
Returns HIGH or LOW.
- **bool write1(uint8_t pin, uint8_t value)** writes a single pin (0..7).
Value should be LOW (0) or HIGH (other values).
As said before the user must guard not to interfere with the
rotary encoder pins.
- **uint16_t read16()** read all pins in one I2C IO action. When one need to access multiple 
input pins this is faster but need some bit masking.
- **bool write16(uint16_t bitMask)** writes to multiple pins at once, e.g. to control multiple
LEDs in one IO action. As said before the user must guard not to interfere with the
rotary encoder pins.


### Debugging

- **int8_t getLastPosition(uint8_r re)** Returns last position.
Returns 0 if re > 4.


## Performance

TODO get numbers right.

As the decoder is based upon a PCF8575, a I2C device, the performance is affected by the 
clock speed of the I2C bus.
All four core functions have one call to **read16()** which is the most expensive part.

Early tests gave the following indicative times (Arduino UNO) for the **update()** 
function. 
Note that above 500 KHz the gain becomes less while reliability of signal decreases.
(500 KHz is about 3x faster than 100 KHz in practice.)
As 400 KHz is a standard I2C clock speed it is the preferred one.


|  I2C speed  |  time (us)  |  delta  |  %%   |  Notes  |
|:-----------:|:-----------:|:-------:|:-----:|:--------|
|   100 KHz   |             |         |       |
|   200 KHz   |             |         |    %  |
|   300 KHz   |             |         |    %  |
|   400 KHz   |             |         |    %  |  preferred max
|   500 KHz   |             |         |    %  |
|   600 KHz   |             |         |    %  |
|   700 KHz   |             |         |    %  |

(test results differ slightly from the rotaryEncoder class)


At 400 KHz it can update 5 rotary encoders in less than XX  us. 
At a 50% update percentage this implies a max of about 
5000 **update()** calls per second in theory.
**to be tested in practice**

Note that a high speed drill goes up to 30000 RPM = 500 RPS = 2000 interrupts per second, 
assuming 4 pulses == 360°. (not tested)


## Future

#### Must

- update documentation
  - add schema
- keep in sync with rotaryDecoderSwitch library.

#### Should

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

