
[![Arduino CI](https://github.com/RobTillaart/TLC5917/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TLC5917/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TLC5917/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TLC5917/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TLC5917/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TLC5917.svg)](https://github.com/RobTillaart/TLC5917/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TLC5917/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TLC5917.svg?maxAge=3600)](https://github.com/RobTillaart/TLC5917/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TLC5917.svg)](https://registry.platformio.org/libraries/robtillaart/TLC5917)


# TLC5917

TLC5917 is an Arduino library for TLC5917 8-Channel Constant-Current LED Sink Drivers.


## Description

**Experimental**

This library allows control over the 8 channels of a TLC5917 device.


TODO: Elaborate.

The TLC5916 is a derived class that is functional identical to the TLC5917 (for now).
When implementation proceeds this might change.

The library is **experimental** and needs testing with Hardware.  
Please share your experiences.


(Changes of the interface are definitely possible).


#### Daisy chaining

This library supports daisy chaining.
A constructor takes the number of devices as parameter and 
an internal buffer is allocated (8 elements per device).
This internal buffer is clocked into the devices with **write()**.


#### Related

- https://www.adafruit.com/product/1429
- https://github.com/RobTillaart/TLC5917
- https://github.com/RobTillaart/TLC5947
- https://github.com/RobTillaart/PCA9634  (I2C)
- https://github.com/RobTillaart/PCA9635  (I2C)
- https://github.com/RobTillaart/PCA9685  (I2C)


## Interface

```cpp
#include TLC5917.h
```

#### Constructor

- **TLC5917(uint8_t clock, uint8_t data, uint8_t latch, uint8_t blank)** constructor.
Single device constructor.
Defines the pins used for uploading / writing the PWM data to the module.
The blank pin is explained in more detail below. 
- **TLC5917(int deviceCount, uint8_t clock, uint8_t data, uint8_t latch, uint8_t blank)** constructor.
To be used for multiple devices, typical 2 or more.
Defines the pins used for uploading / writing the PWM data to the module.
The blank pin is explained in more detail below. 
- **~TLC5917()** destructor

#### Base

- **bool begin()** set the pinModes of the pins and their initial values.
The TLC is disabled by default, as the device has random values in its grey-scale register. 
One must call **enable()** explicitly.
- **int getChannels()** return the amount of channels == 8 x number of devices.
- **bool setChannel(uint8_t channel, bool on)** set a channel on or off in the buffer.
- **bool setChannel(uint8_t \* array)** copy a preset of channel settings in one call.
- **bool setAll(bool on)** set all channels on or off.
- **bool getChannel(uint8_t channel)** get current state of a channel in the cached buffer.
- **void write()** writes the whole buffer (deviceCount x 8 values) to the device(s).
- **void write(int n)** writes a part of the buffer (only **n** values) to the device.
Typical used to speed up if less than max number e.g. only 17 channels are used
and needs to be updated.  
**experimental, might have side effects**


**write()** must be called after setting all values one wants to change.
Doing that per channel is far less efficient if one wants to update multiple 
channels as fast as possible.
See also **TLC5917_performance.ino** for an indication of time.


#### Blank line  TODO CHECK
 
The blank pin (OE line) is used to set all channels on or off.
This allows to "preload" the registers with values and enable them all at once
with very precise timing.

Default a TLC device is disabled (by begin), so one should enable it "manually".  
(P13 datasheet)

- **void enable()** all channels reflect last PWM values written.
- **void disable()** all channels are off / 0.
- **bool isEnabled()** returns status of blank line.

The library only supports one **enable() / blank line**. If you want
a separate **enable()** per device you might need to connect the devices
"in parallel" instead of "in series" (daisy chained).
The blank parameter in the constructor should be set to -1 (out of range value).


#### Configure gain

See datasheet page 23 for details.

- **void setCurrentAdjustMode()**
- **void setNormalMode()**
- **void writeConfiguration(uint8_t config)** See page 23 datasheet

|      bit  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
|:---------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|  meaning  |  CM |  HC | CC0 | CC1 | CC2 | CC3 | CC4 | CC5 |
|  default  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |

CM limits the output current range.  
- High Current Multiplier (CM = 1): 10 mA to 120 mA.
- Low Current Multiplier  (CM = 0):  3 mA to  40 mA.

VG (voltage gain) = (1 + HC) × (1 + D/64) / 4
where  D = CC0 × 32 + CC1 × 16 + CC2 × 8 + CC3 × 4 + CC4 × 2 + CC5

CG (current gain) = VG x pow(3, CM - 1)    

```
Default 
CG = VG x 3;  
VG = 2 x ( 1 + 63/64) / 4 = 127/128
```

TODO test with hardware to understand this in detail.  
Actual current depends on Rext (see datasheet).


## Performance

See **TLC5917_performance.ino** for an indicative test.


## Future

#### Must

- update documentation
- buy hardware
  - test test test 
- get basic functionality running

#### Should

- get basic functionality running
- investigate daisy chaining. (hardware needed).
  - max CLOCK speed when chained (50% DutyCycle)
  - what is clock in practice (e.g. an ESP32 240 MHz)

#### Could

- add examples

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


