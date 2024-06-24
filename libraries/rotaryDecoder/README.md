
[![Arduino CI](https://github.com/RobTillaart/rotaryDecoder/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/rotaryDecoder/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/rotaryDecoder/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/rotaryDecoder/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/rotaryDecoder/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/rotaryDecoder.svg)](https://github.com/RobTillaart/rotaryDecoder/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/rotaryDecoder/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/rotaryDecoder.svg?maxAge=3600)](https://github.com/RobTillaart/rotaryDecoder/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/rotaryDecoder.svg)](https://registry.platformio.org/libraries/robtillaart/rotaryDecoder)


# rotaryDecoder

Arduino library for a PCF8574 based rotary decoder - supports 4 rotary encoders.


## Description

This experimental library uses a PCF8574 to read the pulses of a rotary encoder.
As a PCF8574 has 8 lines up to 4 decoders can be read over I2C.
The PCF interrupt line can be used to detect changes in the position of the encoders.

If less than 4 rotary encoders are connected one should use the lower bit lines as the 
library assumes these are used. Furthermore it is advised to connect the free PCF8574
pins to GND so you will not get unintended interrupts.


#### Related

- https://github.com/RobTillaart/rotaryDecoderSwitch
- https://github.com/RobTillaart/PCF8574


## Interface

```cpp
#include "rotaryEncoder.h"
```

#### Constructor

- **rotaryDecoder(const int8_t address, TwoWire \*wire = Wire)**
constructor to set the address and optional the Wire bus.
- **bool begin(uint8_t count = 4)** UNO ea. initializes the class. 
count is the number of rotary encoders connected. (Max 4 per PCF8574)
Returns true if the PCF8574 is on the I2C bus.
- **bool isConnected()** returns true if the PCF8574 is on the I2C bus.


#### Core functions

- **uint8_t readInitialState()** read the initial state of the 4 rotary encoders. 
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


#### Counters

- **int32_t getValue(uint8_r re)** returns the RE counter.
If the parameter re > 3 then 0 is returned.
- **bool setValue(uint8_r re, int32_t value = 0)** (re)set the internal counter to value, default 0.
If the parameter re > 3 then false is returned, true otherwise.


#### Read1 - Write1 - experimental

Warning the **write1(pin, value)** might alter the state of the rotary encoder pins.
So this functionality should be tested thoroughly for your application.
Especially the **write()** is **experimental**, see issue #10, feedback welcome.

See example **rotaryDecoder_demo_RE_IO.ino** (since 0.3.1).

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

- **int8_t getLastPosition(uint8_r re)** Returns last position.


## Performance

As the decoder is based upon a PCF8574, a I2C device, the performance is affected by the 
clock speed of the I2C bus.
All four core functions have one call to **read8()** which is the most expensive part.

Early tests gave the following indicative times (Arduino UNO) for the **update()** 
function (with no updates it is ~8 us faster). 
Note that above 500 KHz the gain becomes less while reliability of signal decreases.
(500 KHz is about 3x faster than 100 KHz in practice.)
As 400 KHz is a standard I2C clock speed it is the preferred one.


|  I2C speed  |  time (us)  |  delta  |  %%   |  Notes  |
|:-----------:|:-----------:|:-------:|:-----:|:--------|
|   100 KHz   |      247    |         |       |
|   200 KHz   |      146    |    99   |  40%  |
|   300 KHz   |      110    |    36   |  24%  |
|   400 KHz   |       95    |    15   |  14%  |  preferred max
|   500 KHz   |       84    |    11   |  12%  |
|   600 KHz   |       79    |     5   |   6%  |
|   700 KHz   |       73    |     6   |   8%  |


At 400 KHz it can update 4 rotary encoders in ~100us. 
At a 50% update percentage this implies a max of about 
5000 **update()** calls per second in theory.
**to be tested in practice**

Note that a high speed drill goes up to 30000 RPM = 500 RPS = 2000 interrupts per second, 
assuming 4 pulses == 360°. (not tested)


## Future

#### Must

- update documentation
- picture how to connect e.g two rotary encoders which pins to used

#### Should

- test with a high speed drill like a Dremel-tool.

#### Could

- invert flag to adjust to RE that give their pulse just the other way around?
  - setInvert(bool);  getInvert();
  - per channel / all?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

