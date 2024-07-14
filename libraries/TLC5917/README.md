
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

The library allows to set the channels (outputs) on/off individually or as a group in one call.
Furthermore it allows to set a current gain for all devices connected.

The **TLC5916** is a derived class that is functional identical to the TLC5917.
When implementation proceeds this might change, the difference is in support for fetching 
the status and error modi. This functionality is not supported by the library yet, 
so there is no difference between the **TLC5916** and **TLC5917** for now. 

The library needs more testing with hardware.  
Please share your experiences.

(Changes of the interface are definitely possible).


### Breaking changes

The 0.2.0 version fixed an internal storage bug which allocated way to much memory
in version 0.1.x. So these versions can be considered obsolete.
The performance of the library **write()** call improved a lot.


### Daisy chaining

This library supports daisy chaining of multiple **TLC5917** modules.
A constructor takes the number of devices as parameter and 
an internal buffer is allocated (8 channels per device).
This internal buffer is clocked into the devices with the **write()** call.
So **setChannel()** calls can be changed until last moment.


### Related

- https://www.adafruit.com/product/1429
- https://github.com/RobTillaart/TLC5917
- https://github.com/RobTillaart/TLC5947
- https://github.com/RobTillaart/PCA9634  (I2C, PWM)
- https://github.com/RobTillaart/PCA9635  (I2C, PWM)
- https://github.com/RobTillaart/PCA9685  (I2C, PWM)


## Interface

```cpp
#include TLC5917.h
```

### Constructor

- **TLC5917(uint8_t clock, uint8_t data, uint8_t latch, uint8_t outputEnable)** constructor.
Single device constructor.
Defines the pins used for uploading / writing the data to the device.
The outputEnable pin is explained in more detail below. 
- **TLC5917(int deviceCount, uint8_t clock, uint8_t data, uint8_t latch, uint8_t outputEnable)** constructor.
To be used for multiple devices, typical 2 or more.
Defines the pins used for uploading / writing the data to the device.
The outputEnable pin is explained in more detail below. 
- **~TLC5917()** destructor. Frees the allocated memory.

### Base

- **bool begin()** set the pinMode of the pins used and their initial values.
The TLC5917 is disabled by default, as the device has random values in its register. 
Therefore one must call **enable()** explicitly.
- **int channelCount()** return the amount of channels == 8 x number of devices.


### Set/Get channels

- **bool setChannel(uint8_t channel, bool on)** set a channel on or off in the 
internal buffer. The value is not written immediately to the device(s).
One has to call **write()** for that.
- **bool setChannel(uint8_t \* array)** copy a preset of channel settings in one call.
The user has to take care that the size of array holds the right amount of bytes.
Typical amount is deviceCount (or more).
- **bool setAll(bool on)** set all channels on or off.
- **bool getChannel(uint8_t channel)** get current state of a channel from the cached buffer.
- **void write()** writes the whole buffer (deviceCount x 8 values) to the device(s).
- **void write(int channels)** writes a part of the internal buffer (only **channels** values) to the device.
Typical used to speed up if less than max number e.g. only 17 channels are used
and needs to be updated.  
**experimental, might have side effects**


**write()** must be called after setting all values one wants to change.
Updating per channel is possible but far less efficient if one has to update multiple 
channels as fast as possible.
See also **TLC5917_performance.ino** for an indication of time needed.


### OutputEnable line
 
The **outputEnable** pin (OE or blank) is used to set all channels on or off.
This allows to "preload" the registers with values and enable them all at once
with very precise timing.

Default a TLC device is disabled, by **begin()**, so one should enable it "manually".  
(P13 datasheet)

- **void enable()** all channels reflect last values written.
- **void disable()** all channels are off / 0.
- **bool isEnabled()** returns status of outputEnable line.

The library only supports one **enable() line**. 
If you want a separate **enable()** per device you might need to connect the devices
"in parallel" instead of "in series" (daisy chained).
The outputEnable parameter in the constructor should be set to -1 (out of range value).

#### PWM

It might be possible to use a PWM pin on the **outputEnable** line to dim the LEDS.
This is neither tested nor supported by the library.
Note that writing to the TLC5917 needs a HIGH **outputEnable** so the PWM value needs 
to be set again.


### Configure gain

See datasheet page 23 for details.

- **void setNormalMode()** switch to normal mode (default) to send the data for the IO pins.
- **void setSpecialMode()** switch to special mode to configure the gain.

Note that calling **setSpecialMode()** and **setNormalMode()** disables the output.
So one should enable it again if one wants to.


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

Based upon **TLC5917_performance.ino** for an indicative test.  
and issue #9 for the LGT8F328 data

Timing in microseconds, 800 channels = 100 devices.

| Version | Function         | UNO 1.8.19 | LGT8F328 |   other  |
|:-------:|:-----------------|:----------:|:--------:|:--------:|
|  0.2.0  | SETCHANNEL TRUE  |    2572    |   1152   |
|  0.2.0  | SETCHANNEL FALSE |    2840    |   1296   |
|  0.2.0  | SETALL TRUE      |     236    |    108   |
|  0.2.0  | SETALL FALSE     |     232    |      -   |
|  0.2.0  | WRITE optimized  |    1772    |      -   |
|  0.2.0  | WRITE normal     |    9420    |      -   |

_The "WRITE optimized" is AVR only._

So setting and writing 8 channels (e.g. a single 7 segment display) takes 
28.40 + 17.72 = 46.12 < 50 microseconds. 
So in theory an UNO could update it roughly 20K times per second. 


## Hardware SPI

First investigations show that **write()** could be a hardware SPI transaction.
However the **setNormalMode()**, **setSpecialMode()** and especially the 
**writeConfiguration()** function are no standard 8 bit SPI transactions.
This of course includes the **gain** functions that use these.
To solve this one still has to provide the CLOCK, LATCH and OUTPUT ENABLE pins.
Especially the CLOCK pin is part of the SPI pins, and it would depend on the 
board and optional number of HW SPI ports of the board.
To prevent this complexity the library does not have a hardware SPI constructor. 

It looks like it is possible to create a simplified class (stripped version) 
without the gain control that might work well with HW SPI for many application. 
The added value is however limited as the (optimized) SW is pretty fast already.


## Future

#### Must

- update documentation
- do hardware test test test ...

#### Should

- investigate daisy chaining. (extra hardware needed).
  - max CLOCK speed when chained (50% DutyCycle)
  - what is clock in practice (e.g. an ESP32 240 MHz)
- now the CurrentGain is set to the same value for all devices.
  - needs array, one value (uint8_t) per device, investigate.

#### Could

- **index operator []** to get set channels, might be better?
- reading error codes from SDO
- do brightness test with analogWrite(OE, value);
  - it would be mandatory to have OE be a PWM pin.

#### Wont (unless needed)

- redo constructor, 
  - move deviceCount to last place with default = 1 (one constructor less).
- **void getChannel(uint8_t \* array)** fill an array with current data.
- error handling in special mode
  - over-temperature, open-load, short to GND, short to VLED (TLC5917 only).
- implement hardware SPI, see above.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


