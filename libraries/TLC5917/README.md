
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

The **TLC5917** library allows control over the 8 channels (outputs) of a TLC5917 device.
This library also support more than one device in a daisy chain (see below).

The library allows to set the channels (outputs) individually or a group in one call.
Furthermore it allows to set a current gain for all devices connected.

The **TLC5916** is a derived class that is functional identical to the TLC5917 (for now).
When implementation proceeds this might change, the difference is in support for fetching 
the status and error modi. This is not supported by the library

The library needs more testing with hardware.  
Please share your experiences.

(Changes of the interface are definitely possible).


#### Daisy chaining

This library supports daisy chaining of TLC5917 modules.
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
- **~TLC5917()** destructor. Frees the allocated memory.

#### Base

- **bool begin()** set the pinModes of the pins and their initial values.
The TLC is disabled by default, as the device has random values in its grey-scale register. 
One must call **enable()** explicitly.
- **int channelCount()** return the amount of channels == 8 x number of devices.


#### Set/Get channels

- **bool setChannel(uint8_t channel, bool on)** set a channel on or off in the 
internal buffer. The value is not written yet to the device(s).
- **bool setChannel(uint8_t \* array)** copy a preset of channel settings in one call.
The user has to take care the the size of array holds the right amount of bytes.
- **bool setAll(bool on)** set all channels on or off.
- **bool getChannel(uint8_t channel)** get current state of a channel in the cached buffer.
- **void write()** writes the whole buffer (deviceCount x 8 values) to the device(s).
- **void write(int n)** writes a part of the internal buffer (only **n** values) to the device.
Typical used to speed up if less than max number e.g. only 17 channels are used
and needs to be updated.  
**experimental, might have side effects**


**write()** must be called after setting all values one wants to change.
Updating per channel is possible but far less efficient if one has to update multiple 
channels as fast as possible.
See also **TLC5917_performance.ino** for an indication of time needed.


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

It might be possible to use a PWM pin on the OE line to dim the LEDS.
This is neither tested or supported by the library.


#### Configure gain

See datasheet page 23 for details.

- **void setNormalMode()**  to send the data for the LEDS.
- **void setSpecialMode()**  to configure the gain.


The special mode needs to be set for the following functions:

- **void writeConfiguration(uint8_t configuration)** See page 23 datasheet.
Writes same configuration to all devices. One must call setSpecialMode() first
and setNormalMode() after..
- **uint8_t getConfiguration()** returns last written configuration 
bit mask (from cache).
- **bool setGain(bool CM, bool HC, uint8_t CC)**  CC = {0..63}
returns false if CC >= 64
- **bool setCurrentGain(float n)** n = 0.250 - 3.000 (nicer range).  
Over the range 0.250 - 2.989 the max error is 0.0124  
Over the range 2.989 - 3.000 the max error goes up to 0.023  
So except for end of the range the error is (IMHO) small.
Returns false if out of range (n < 0.250 or n > 3.0).  
- **float getVoltageGain()** see below (from cache).
- **float getCurrentGain()** see below (from cache).


|      bit  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
|:---------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|  abbrev   |  CM |  HC | CC0 | CC1 | CC2 | CC3 | CC4 | CC5 |
|  default  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |  1  |

CM == Current Multiplier
- limits the output current range.  
- Low  (CM = 0):  3 mA to  40 mA.
- High (CM = 1): 10 mA to 120 mA.  == CM(0) x 3

VG (voltage gain) = (1 + HC) × (1 + D/64) / 4

where  D = CC0 × 32 + CC1 × 16 + CC2 × 8 + CC3 × 4 + CC4 × 2 + CC5  
       D = 0..63

CG (current gain) = VG x pow(3, CM - 1)    

```
Default 
VG = 2 x ( 1 + 63/64) / 4 = 127/128  
CG = VG x 3 = ~2.977
```

TODO: test with hardware to understand this in detail.  
Actual current depends on Rext == external resistor (see datasheet).


## Performance

See **TLC5917_performance.ino** for an indicative test.


## Future

#### Must

- update documentation
- buy hardware
  - test test test

#### Should

- investigate daisy chaining. (hardware needed).
  - max CLOCK speed when chained (50% DutyCycle)
  - what is clock in practice (e.g. an ESP32 240 MHz)
- now the CurrentGain is set to the same value for all devices.
  - needs array, one value (uint8_t or float) per device, investigate.

#### Could

- **index operator []** to get set channels, might be better?
- reading error codes from SDO

#### Wont (unless needed)

- **void getChannel(uint8_t array)** fill an array with current data.
- error handling in special mode
  - over-temperature, open-load, short to GND, short to VLED (5917 only).
- investigate if hardware SPI is possible
  - which mode?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


