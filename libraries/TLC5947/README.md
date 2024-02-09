
[![Arduino CI](https://github.com/RobTillaart/TLC5947/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TLC5947/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TLC5947/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TLC5947/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TLC5947/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TLC5947.svg)](https://github.com/RobTillaart/TLC5947/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TLC5947/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TLC5947.svg?maxAge=3600)](https://github.com/RobTillaart/TLC5947/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TLC5947.svg)](https://registry.platformio.org/libraries/robtillaart/TLC5947)


# TLC5947

TLC5947 is an Arduino library for the TLC5947, 24 channel 12 bit, PWM module.


## Description

This experimental library allows easy control over a TLC5947 module.
To communicate this module uses three (bit banging) serial lines.

The TLC5947 module provides in total 24 outputs of 12 bit PWM. 
So it allows 4096 greyscales or levels to be set, making the output pretty well tunable.
Main purpose is to drive LED's, see datasheet.

The library is experimental and needs more testing, so please share your experiences.
(changes of the interface are definitely possible).


#### Daisy chaining
 
This library does **NOT** support daisy chaining (yet). 
The current version can control only 1 module.
To control multiple modules, you need to give them their own **clock** line, 
and preferable their own latch line.
The data can be shared (to be tested) as data won't be clocked in if
the **clock** line is not shared.


#### Related

- https://www.adafruit.com/product/1429
- https://github.com/RobTillaart/TLC5947
- https://github.com/RobTillaart/PCA9634  (I2C)
- https://github.com/RobTillaart/PCA9635  (I2C)
- https://github.com/RobTillaart/PCA9685  (I2C)


## Interface

```cpp
#include TLC5947.h
```

- **TLC5947(uint8_t clock, uint8_t data, uint8_t latch, uint8_t blank)** constructor.
Defines the pins used for uploading / writing the PWM data to the module.
The blank pin is explained in more detail below. 
- **~TLC5947()** destructor
- **bool begin()** set the pinModes of the pins and their initial values.
- **int setPWM(uint8_t channel, uint16_t PWM)**. set a PWM value to 
the buffer to be written later.  
channel = 0..23, PWM = 0..4095  
Returns TLC5947_OK or TLC5947_CHANNEL_ERROR.
- **void setAll(uint16_t PWM)** set the same PWM value for all channels to the buffer, and writes them to device.
- **uint16_t getPWM(uint8_t channel)** get PWM value from the buffer, 
Note this value might differ from device when a new value is set after the last **write()**.
May return TLC5947_CHANNEL_ERROR.
- **void write()** writes the buffer (24 x 12 bit) to the device.


**write()** must be called after setting all PWM values one wants to change as doing that 
per channel is less efficient if one wants to update multiple channels as fast as possible.


#### Percentage wrappers

Wrapper functions to set the device in percentages. 
The accuracy of these functions is about 1/4095 = ~0.025%.

Note: the percentages will be rounded to the nearest integer PWM value.

- **int setPercentage(uint8_t channel, float percentage)** wrapper setPWM().  
channel = 0..23, percentage = 0.0 .. 100.0 (will be constrained)  
Returns TLC5947_OK or TLC5947_CHANNEL_ERROR.
- **void setPercentageAll(float percentage)** wrapper setAll().  
percentage = 0.0 .. 100.0 (will be constrained)
- **float getPercentage(uint8_t channel)** wrapper getPWM().  
Note: the error code TLC5947_CHANNEL_ERROR = 0xFFFF will return as 1600%.


#### Blank line

The blank pin (line) is used to set all channels on or off.
This allows to "preload" the registers with values and enable them all at once.

- **void enable()** all channels reflect last PWM values written.
- **void disable()** all channels are off / 0.
- **bool isEnabled()** returns status of blank line.


#### RGB interface

(since 0.2.0)

The 24 PWM channels of the TLC5947 are ideal to control 8 RGB LEDS.
The supported mapping of LED to channel is straightforward.

LED n uses channel 3n, 3n+1, 3n+2

|  LED  |  channels  |  |  LED  |  channels  |
|:-----:|:----------:|--|:-----:|:----------:|
|   0   |    0,1,2   |  |   4   |  12,13,14  |
|   1   |    3,4,5   |  |   5   |  15,16,17  |
|   2   |    6,7,8   |  |   6   |  18,19,20  |
|   3   |   9,10,11  |  |   7   |  21,22,23  |

- **int setRGB(uint8_t led, uint16_t R,  uint16_t G,  uint16_t B)**
Set RGB values.  
Returns TLC5947_CHANNEL_ERROR if led > 7, TLC5947_OK otherwise.
- **int getRGB(uint8_t led, uint16_t &R,  uint16_t &G,  uint16_t &B)**
idem.  
Returns TLC5947_CHANNEL_ERROR if led > 7, TLC5947_OK otherwise.

If you need an other mapping you have to use the **setPWM(channel, pwm)** 
call with the channels of your choice.


## Performance

Writing 24 x 12 bit takes time, however is still pretty fast.
On a 16 MHz UNO writing all 24 channels takes 740 microseconds.

Note that all channels must be written. (time in microseconds)
Pre 0.2.0 versions are obsolete.

|  platform (MHz)  |  version  |  command  |  time  |  notes       |
|:----------------:|:---------:|:----------|:-------|:-------------|
|  AVR/UNO  (16)   |   0.1.0   |  setPWM() |    16  |  24 channels, obsolete version
|  AVR/UNO  (16)   |   0.1.0   |  write()  |  3808  |  24 channels, obsolete version
|  AVR/UNO  (16)   |   0.1.1   |  setPWM() |    16  |  24 channels, obsolete version
|  AVR/UNO  (16)   |   0.1.1   |  write()  |   804  |  24 channels, obsolete version
|  ESP32    (240)  |   0.1.0   |  setPWM() |     6  |  24 channels, obsolete version
|  ESP32    (240)  |   0.1.0   |  write()  |   128  |  24 channels, obsolete version
|                  |           |           |        |
|  AVR/UNO  (16)   |   0.2.0   |  setPWM() |    16  |  24 channels
|  AVR/UNO  (16)   |   0.2.0   |  setRGB() |    16  |  24 channels = 8 leds
|  AVR/UNO  (16)   |   0.2.0   |  write()  |   740  |  24 channels
|  ESP32    (240)  |   0.2.0   |  setPWM() |     6  |  24 channels
|  ESP32    (240)  |   0.2.0   |  setRGB() |     8  |  24 channels = 8 leds
|  ESP32    (240)  |   0.2.0   |  write()  |   117  |  24 channels


Measured with **TLC5947_performance.ino**.


## Future

#### Must

- update documentation
  - links etc.
  - schema for multiple devices
- buy hardware
  - test test test 

#### Should

- investigate daisy chaining. (hardware needed).


#### Could

- add examples
- "dirty" flag for **bool writePending()**?
  - set by **setPWM()** if value changes.
  - would speed up unneeded **write()** too.
- test if partial write (e.g. first N channels) works.
- test "preloading" when module is disabled.
- investigate how to reduce memory usage (now 48 bytes)
  - parameter in constructor # channels? e.g 0..15  (admin overhead).
  - could be 36 (12 bits / channel)
  - or even 24 (8 bits/channel) = derived class?
  - performance penalty unpacking!


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


