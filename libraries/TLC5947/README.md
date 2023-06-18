
[![Arduino CI](https://github.com/RobTillaart/TLC5947/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TLC5947/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TLC5947/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TLC5947/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TLC5947/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TLC5947/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TLC5947.svg?maxAge=3600)](https://github.com/RobTillaart/TLC5947/releases)


# TLC5947

TLC5947 is an Arduino library for TLC5947 24 channel 12 bit PWM module.


## Description

This EXPERIMENTAL library allows easily control over a TLC5947 module.
To communicate it uses three (bit banging) serial lines. 
This module provides in total 24 channels of 12 bit PWM. 
So it allows 4096 greyscales or levels to be set, making the output pretty well tunable.
Main purpose is to drive LED's, see datasheet.

The library is EXPERIMENTAL and needs more testing.
(changes of the interface are definitely possible).


#### Daisy chaining
 
This library does **NOT** support daisy chaining yet. 
The current version can control only 1 module.
To control multiple modules by giving them their own CLOCK line.
The data and latch can be shared (to be tested).


#### Links

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
- **void setPWM(uint8_t channel, uint16_t PWM)**. Writes a PWM value to the buffer to
be written later.
channel = 0..23, PWM = 0..4095
- **void setAll(uint16_t PWM)** writes the same PWM value for all channels to the buffer. 
- **uint16_t getPWM(uint8_t channel)** get PWM value from the buffer, 
Note this value might differ from device when a new value is set after the last **write()**.
- **void write()** writes the buffer (24 x 12 bit) to the device.


#### Blank line

The blank pin (line) is used to set all channels on or off.
This allows to "preload" the registers with values and enable them all at once.

- **void enable()** all channels reflect last updated PWM value.
- **void disable()** all channels are off / 0.


## Performance

Writing 24 x 12 bit takes time, however is still pretty fast.
On a 16 MHz UNO writing all 24 channels takes less than 4 milliseconds.

Note that all channels must be written.

|  platform (MHz)  |  version  |  command  |  time (us)  |  notes       |
|:----------------:|:---------:|:----------|:------------|:-------------|
|  AVR/UNO  (16)   |   0.1.0   |  setPWM() |  16         |  24 channels |
|  AVR/UNO  (16)   |   0.1.0   |  write()  |  3808       |  24 channels |
|  ESP32    (240)  |   0.1.0   |  setPWM() |  6          |  24 channels |
|  ESP32    (240)  |   0.1.0   |  write()  |  128        |  24 channels |


Measured with **TLC5947_performance.ino**.


## Future

#### Must

- update documentation
  - links etc.
- buy hardware
  - test test test 


#### Should

- add examples
  - extend performance sketch
- test if partial write (e.g. first N channels) works.
- test "preloading" when module is disabled.
- AVR optimized bit banging, see **fastShiftOut**
  - factor 2 - 4 could be achievable 
- "dirty" flag for **bool writePending()**?
  - set by **setPWM()** if value changes.
  - would speed up unneeded **write()** too.


#### Could

- add unit-tests
- add **void setPercentage(float perc)** and **float getPercentage()** wrappers.
- investigate how to reduce memory usage (now 48 bytes)
  - could be 36 (12 bits / channel) or even 24 (8 bits/channel)
  - derived class?
- add **setRGB(LED, R, G, B)** wrapper (channel 0..7)
  24 channels == 3 x 8 RGB LEDs
- return value for **setPWM()** ? 


#### Won't


