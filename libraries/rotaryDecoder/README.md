
[![Arduino CI](https://github.com/RobTillaart/rotaryDecoder/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/rotaryDecoder/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/rotaryDecoder/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/rotaryDecoder/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/rotaryDecoder/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/rotaryDecoder/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/rotaryDecoder.svg?maxAge=3600)](https://github.com/RobTillaart/rotaryDecoder/releases)


# rotaryDecoder

Arduino library for a PCF8574 based rotary decoder - supports 4 RE.


## Description

This experimental library uses a PCF8574 to read the pulses of a rotary encoder.
As a PCF8574 has 8 lines up to 4 decoders can be read over I2C.
The PCF interrupt line can be used to detect changes in the position of the encoders.

If less than 4 rotary encoders are connected one should use the lower bit lines as the 
library assumes these are used. Furthermore it is advised to connect the free PCF8574
pins to GND so you will not get unintended interrupts.


## Interface

- **rotaryDecoder(const int8_t address, TwoWire \*wire = Wire);**
- **bool begin(uint8_t sda, uint8_t scl, uint8_t count = 4)** ESP32 ea initializes the class
by setting the I2C sda and scl pins.
count is the number of rotary encoders connected. (Max 4 per PCF8574)
Returns true if the PCF8574 is on the I2C bus.
- **bool begin(uint8_t count = 4)** UNO ea. initializes the class. 
count is the number of rotary encoders connected. (Max 4 per PCF8574)
Returns true if the PCF8574 is on the I2C bus.
- **bool isConnected()** returns true if the PCF8574 is on the I2C bus.


## Core functions

- **void readInitialState()** read the initial state of the 4 rotary encoders. 
Typically called in setup only, or after a sleep e.g. in combination with **setValue()**
- **bool checkChange()** polling to see if one or more RE have changed, without updating the counters.
- **void update()** update the internal counters of the RE. These will add +1 or -1 depending on direction. 
- **void updateSingle()** update the internal counters of the RE. This will add +1 +2 or +3
 as it assumes that the rotary encoder only goes into a single direction. 


## Counters

- **uint32_t getValue(uint8_r re)** returns the RE counter.
- **void setValue(uint8_r re, uint32_t value = 0)** (re)set the internal counter to value, default 0


## Debugging

- **int8_t getLastPosition(uint8_r re)** returns last position.


## Performance

As the decoder is based upon a PCF8574, a I2C device, the performance is affected by the 
clock speed of the I2C bus. All four core functions have one call to **\_read8()** which 
is the most expensive part.

Early tests gave the following indicative times (Arduino UNO) for the **update()** 
function (with no updates it is ~8 us faster). Note that above 500KHz the gain becomes less
while reliability of signal decreases. (500KHz is about ~3x faster than 100 KHz)
As 400 KHz is a standard I2C clock speed it is the preferred one.


| I2C speed | time (us) | delta |  %%   |
|:---------:|:---------:|:-----:|:-----:|
| 100 KHz   |    247    |       |       |
| 200 KHz   |    146    |  99   | 40%   |
| 300 KHz   |    110    |  36   | 24%   |
| 400 KHz   |     95    |  15   | 14%   | preferred max
| 500 KHz   |     84    |  11   | 12%   |
| 600 KHz   |     79    |   5   |  6%   |
| 700 KHz   |     73    |   6   |  8%   |


At @400KHz it can update 4 rotary encoders in ~100us. 
At a 50% update percentage this implies a max of about 
5000 **update()** calls per second in theory 
**to be tested in practice**

Note that a high speed drill goes up to 30000 RPM = 500 RPS = 2000 interrupts per second, 
assuming 4 pulses == 360°. (not tested)


## Operational

See examples..


## Future

- test with a high speed drill like a Dremel-tool.
- update documentation
- picture how to connect e.g 2 RE's  which pins to used

