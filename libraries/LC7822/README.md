
[![Arduino CI](https://github.com/RobTillaart/LC7822/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LC7822/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LC7822/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LC7822/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LC7822/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LC7822.svg)](https://github.com/RobTillaart/LC7822/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LC7822/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LC7822.svg?maxAge=3600)](https://github.com/RobTillaart/LC7822/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LC7822.svg)](https://registry.platformio.org/libraries/robtillaart/LC7822)


# LC7822

Arduino library for the LC7822 8 channel analogue switch.


## Description

**Experimental**

This library is to use the LC7821/22/23 with an Arduino.

The LC782X series are typical used in audio applications as every
switch is implemented twice a.k.a. stereo. 
However other applications that uses two synchronized channels are
very well possible.

The library allows to set the switches individually or set all 
switches in one call.
Furthermore the library caches the current state of the switches. 
This allows to read back the state of the switches either as a
bit mask or read them individually (from cache).

The library has a base class LC782X and three derived classes for 
the LC7821, LC7822 and LC7823 as these are controlled in a similar way. 
The difference is the address used, and the internal setup of the switches. 
Check the datasheet for the details.

The library is not tested with hardware yet.

Note the LC782x devices are relative old and may seem obsolete,
however they are still available online.

Feedback, as always, is welcome.


### Breaking change 0.2.0

Many changes, so pre 0.2.0 versions are obsolete.


### Mode operandi

The library has two modi operandi. 

The first mode operandi is if the **sPin** has a hardwired connection, 
meaning the device has a hard coded / wired address. 
Then the sPin does not need to be set in the constructor (or set to 255).
The user must set the address in the **begin(address)** call so
the library uses the correct address to communicate.
This mode is used if the library needs to control only one device,
or two devices that share the data, clock and ce pins.
See example **LC7822_two_device.ino**.

The second mode operandi is used when there are more than two
devices that share the data, clock and ce pins. Every device needs 
to have an unique **sPin** which works as a select pin as it changes
the active address of the device. See section about address below.
By setting all **sPins** to LOW and only one to HIGH, one of the devices 
is selected. 
In this scenario the **begin()** function must be called **without** 
an address. The library takes care of the addressing.
See example **LC7822_multi.ino**.


### Notes about hardware

The LC7822 et al, can work with relative high voltages, up to ~20 Volts.
They can be controlled directly with an Arduino as 5V is within specification.
It is adviced to add an appropriate optocoupler and optional invertor
when voltages above the 5 Volt are used with this device.

Be sure to read the datasheet.


### Compatibles

There are newer devices with type numbers LC78211, LC78212 and LC78213 
that are compatible with resp. LC7821, LC7822 and LC7823.
(although these seem to be obsolete too).


### Addresses

|   Type   |  S  |  A3  |  A2  |  A1  |  A0  |  DEC  |   HEX  |
|:--------:|:---:|:----:|:----:|:----:|:----:|:-----:|:------:|
|  LC7821  |  L  |  1   |  0   |  1   |  0   |   10  |  0x0A  |
|  LC7821  |  H  |  1   |  0   |  1   |  1   |   11  |  0x0B  |
|  LC7822  |  L  |  1   |  1   |  0   |  0   |   12  |  0x0C  |
|  LC7822  |  H  |  1   |  1   |  0   |  1   |   13  |  0x0D  |
|  LC7823  |  L  |  1   |  1   |  1   |  0   |   14  |  0x0E  |
|  LC7823  |  H  |  1   |  1   |  1   |  1   |   15  |  0x0F  |

Note the address bits are shown in MSB order, while the device
need them in LSB order (see datasheet).


### Details switches LC7821

The LC7821 has three Left Commons (LCOMx) and three Right Commons (RCOMx).
These are symmetrical and are switched simultaneously.

LCOM1 can be connected to L1, L2, L3 and L4.  
LCOM2 can be connected to L5 and L6.  
LCOM3 can be connected to L7 and L8.  

|  COMMON  |  L1  |  L2  |  L3  |  L4  |  L5  |  L6  |  L7  |  L8  |
|:--------:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|  LCOM1   |   X  |   X  |   X  |   X  |      |      |      |      |
|  LCOM2   |      |      |      |      |   X  |   X  |      |      |
|  LCOM3   |      |      |      |      |      |      |   X  |   X  |

Note the library does not check if e.g. LCOM1 is connected to more 
than one output as the library does not know the logic needed in a 
specific application.


### Details switches LC7822

The LC7822 has three Left Commons (LCOMx) and three Right Commons (RCOMx).
These are symmetrical and are switched simultaneously.

LCOM1 can be connected to L1, L2 and L3.  
LCOM2 can be connected to L4, L5 and L6.  
LCOM3 can be connected to L7 and L8.  

|  COMMON  |  L1  |  L2  |  L3  |  L4  |  L5  |  L6  |  L7  |  L8  |
|:--------:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|  LCOM1   |   X  |   X  |   X  |      |      |      |      |      |
|  LCOM2   |      |      |      |   X  |   X  |   X  |      |      |
|  LCOM3   |      |      |      |      |      |      |   X  |   X  |

Note the library does not check if e.g. LCOM1 is connected to more 
than one output as the library does not know the logic needed in a 
specific application.


### Details switches LC7823

The LC7823 has four Left Commons (LCOMx) and four Right Commons (RCOMx).
These are symmetrical and are switched simultaneously.
Note: it has only 7 switches.

LCOM1 can be connected to L1 and L2.  
LCOM2 can be connected to L3 and L4.  
LCOM3 can be connected to L5 and L6.  
LCOM4 can be connected to L7.  
Note: L8 is not used.  

|  COMMON  |  L1  |  L2  |  L3  |  L4  |  L5  |  L6  |  L7  |  L8  |
|:--------:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|  LCOM1   |   X  |   X  |      |      |      |      |      |      |
|  LCOM2   |      |      |   X  |   X  |      |      |      |      |
|  LCOM3   |      |      |      |      |   X  |   X  |      |      |
|  LCOM4   |      |      |      |      |      |      |   X  |      |

Note the library does not check if e.g. LCOM1 is connected to more 
than one output as the library does not know the logic needed in a 
specific application.


### Related

#### Trigger for the development of the library.

- https://forum.arduino.cc/t/legacy-analogue-switch-controll-serial-commands/1419824/125

#### Datasheet

- https://www.haje.nl/pub/pdf/electronica/halfgeleiders/lc7821_lc7822_lc7823.pdf
- https://www.haje.nl/product_info.php/products_id/22222  (LC7821)

#### Multiplexers

- https://github.com/RobTillaart/HC4051  (1x8 mux)
- https://github.com/RobTillaart/HC4052  (2x4 mux)
- https://github.com/RobTillaart/HC4053  (3x2 mux)
- https://github.com/RobTillaart/HC4067  (1x16 mux)
- https://github.com/RobTillaart/MAX14661 (2x16 mux, I2C)
- https://tronixstuff.com/2013/08/05/part-review-74hc4067-16-channel-analog-multiplexerdemultiplexer/
- https://www.gammon.com.au/forum/?id=11976


## Interface LC7822

```cpp
#include "LC7822.h"
```

Note LC782X is the base class.


### Constructor

- **LC7822(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin = 255, uint8_t resetPin = 255)** Constructor, set pins needed.
- **bool begin(uint8_t address = 0x0D)** Initializes the IO pins, 
sets the address, only 0x0C and 0x0D are valid.
- **bool reset()** resets the device, returns false if reset Pin is not defined.
- **uint8_t getAddress()** returns cached address (debugging).


### Switches

- **bool setAll(uint8_t value)** mask to set all switches in one call.
- **uint8_t getAll()** get bit mask of all switches.
- **bool setSwitch(uint8_t switch, bool val)** set one switch.
The parameter switch must be in the range 0..7. 
Returns false if switch is out of range.
- **bool getSwitch(uint8_t switch)** get state of single switch.
The parameter switch must be in the range 0..7. 
Returns false if switch is out of range.

Note: Switch 0 ==> L1 + R1,  Switch 1 ==> L2 + R2 etc.


### Tune timing

- **void setMicroDelay(uint8_t udel)** set pulse delay.
- **uint8_t getMicroDelay()** return set value

The datasheet specifies a delay of 1 us, however depending on the length
of the wires etc. a longer delay might be needed. 


## Interface LC7821

- **LC7821(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin = 255, uint8_t resetPin = 255)** Constructor, set pins needed.
- **bool begin(uint8_t address = 0x0B)** Initializes the IO pins, 
sets the address, only 0x0A and 0x0B are valid.


## Interface LC7823

- **LC7823(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin = 255, uint8_t resetPin = 255)** Constructor, set pins needed.
- **bool begin(uint8_t address = 0x0F)** Initializes the IO pins, 
sets the address, only 0x0E and 0x0F are valid.


## Reset

To elaborate (need HW test).


## Future

#### Must

- improve documentation
- get hardware to test
- test reset() polarity (need hardware)

#### Should


#### Could

- add examples (or document them).
  - array sketch
  - use device as input selector
    - audio sources + mute
    - MIDI devices
  - use device as output selector
    - fast I2C switch? => connect all LCOMx together as SDA and RCOMX as SCL
    - use to multiplex (hardware) Serial TX RX (RS485 etc).
  - use for symmetrical light in a car (left/right front/rear)
  - use as double pole switch, (disconnect an device 100%)
    - right 12 V motor, left feedback channel to uProc (use PCF8574 to read 8 pin states).
    - right 12 V motor, left feedback via LED to user
  - synchronized motor control e.g. LC7823, 3x {direction, enable} pairs
- add defaults for some parameters?
- add #define LC78XX_NO_PIN 255


#### Wont

- add error handling
- add derived classes for compatibles LC78211/2/3 (unless)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


