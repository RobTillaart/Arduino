
[![Arduino CI](https://github.com/RobTillaart/74HC590/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/74HC590/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/74HC590/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/74HC590/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/74HC590/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/74HC590.svg)](https://github.com/RobTillaart/74HC590/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/74HC590/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/74HC590.svg?maxAge=3600)](https://github.com/RobTillaart/74HC590/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/74HC590.svg)](https://registry.platformio.org/libraries/robtillaart/74HC590)


# 74HC590

Arduino library for the 74HC590 8 bit binary counter.


## Description

**Experimental**

This library is to control the 74HC590 (and 54HC590) binary counter.

The library was written to get a better understanding of the possibilities 
the device has to offer. It has not been tested with hardware yet.

The 74HC590 is an 8 bit binary counter, with 8 output lines QA .. QH which
can represent the values 0 .. 255.
The internal counter can only count up, or can be reset to zero.
Furthermore the device can control, by means of RCLK, when the internal counter 
is copied to the 8 output lines.
This selective copying of the internal counter allows to skip through the 
binary numbers e.g. with step 5.

The 74HC590 has an RCO line which triggers a (LOW) pulse when the internal
counter is going from 255 to 0. 
This can be used for cascading multiple devices (to investigate).

Read datasheet for details.

As always feedback is welcome. 


### Related

only slightly related
- https://github.com/RobTillaart/FastShiftIn
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow


## Interface

```cpp
#include "74HC590.h"
```

### Constructor

- **74HC590(uint8_t OE, uint8_t CCLR, uint8_t CCKEN, uint8_t CCLK, uint8_t RCLK = 255, uint8_t RCO = 255)**
  - OE    = output enable
  - CCLR  = counter clear
  - CCKEN = counter clock enable
  - CCLK  = counter clock
  - RCLK  = register clock (if 255 ==> RCLK == CCLK)
  - RCO   = register clock OUT (if 255 ==>  no RCO)

### Control

- **void enableOutput()** idem.
- **void disableOutput()** idem.
- **void clearCounter()** set the internal counter to zero.
- **void enableCounter()** enable the increment the internal counter on the RISING edge of CCLK.
- **void disableCounter()** disable the increment the internal counter on the RISING edge of CCLK.


### Pulse

- **void pulseCounter()** increment the internal counter.
- **void pulseRegister()** copy internal counter to output register.
If RCLK is not set, pulseRegister() does nothing.
The user can e.g. connect the CCLK and RCLK so they update in sync,
or uses another way to trigger the RCLK line.


### Cascading

- **uint8_t readRCO()** read back the value of the RCO pin.
Could be connected to an interrupt pin to know when 256 pulses arrived.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- derived class 54HC590?
- CCLK optional / external?

#### Could

- investigate applications (examples / separate classes)
  - counter for external pulses?  RPM? - no CCLK connected.
  - pulse divider by 2,4,8,16,32,64,128 with reset to zero control.
  - control a DAC / R2R network?
  - PIR sensor pulse counter
  - use the output as fast timer 
    - 1MHz input counts micros().
    - 1kHz input counts millis().
- optimize pulseCounter() for AVR (most used). See fastShiftOut class.
- optimize pulseRegister() for AVR (most used).

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


