
[![Arduino CI](https://github.com/RobTillaart/TinyKT0803/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TinyKT0803/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TinyKT0803/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TinyKT0803/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TinyKT0803/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TinyKT0803.svg)](https://github.com/RobTillaart/TinyKT0803/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TinyKT0803/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TinyKT0803.svg?maxAge=3600)](https://github.com/RobTillaart/TinyKT0803/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TinyKT0803.svg)](https://registry.platformio.org/libraries/robtillaart/TinyKT0803)



# TinyKT0803

Arduino Library for KT0803 and KT0803K FM transmitter. Tiny85 edition.


### Legal point of attention

In different countries there are different laws with respect to using transmitting devices 
and their range. 
Please inform yourself of the local rules and laws if and how you may or may not use a 
device like the KT0803 in your projects, either hobby, commercial or otherwise.


## Description

This is an **EXPERIMENTAL** port to the Tiny85/45/25 processor of - https://github.com/RobTillaart/KT0803

The library is verified to work - See issue #2  
There are two points of attention:

- ATTiny85 needs a 500 ms delay to initialize I2C to communicate properly (assuming 1 MHz clock)
- ATTiny85 needs a decoupling capacitor 100-300 nF between RESET and GND and a 10K resistor between VDC and RESET

Note: The KT0803 library will be leading in development and this one will follow.
The interface section below is identical except for the constructor.


## Interface

```cpp
#include "TinyKT0803.h"
```

#### Constructor

- **TinyKT0803()** constructor.
- **TinyKT0803K()** constructor.
- **bool begin(float freq = 90.0, bool mute = true)** initializes the library.
Furthermore it checks if the deviceAddress is available on the I2C bus.
Default it sets the frequency to 90 MHz and **mutes the signal**.
Returns true if deviceAddress is found on the bus, false otherwise.
- **bool isConnected()** test to see if deviceAddress is found on the I2C-bus.


#### Frequency

- **bool setFrequency(float MHz)** converts the frequency in MHz to 
call **setChannel(channel)**. The value of channel is rounded off depending 
on the resolution of the device.
Returns false if MHz is out of range or **setChannel()** fails.
- **float getFrequency()** returns the current frequency in MHz, can be slightly different
from the set value due to rounding math mentioned above.
The return value is derived from a call to **getChannel()**
- **bool setChannel(uint16_t channel)** writes the channel to broadcast on to the device.
This involves two or three writes to different device registers.
- **uint16_t getChannel()** reads the selected channel from the device and 
returns it.


#### PGA

Read Datasheet.

The KT0803K has a **PGA_LSB** (2 bits) setting, which allows setting the gain
with single (1) dB steps. This is not yet implemented in the library.

- **bool setPGA(uint8_t pga)** sets gain according to table below.
Returns false if pga is out of range (0..7).
- **uint8_t getPGA()** returns 0..7, default 0.


|  PGA  |  gain   |  notes  |
|:-----:|:-------:|:-------:|
|  111  |  12dB   |
|  110  |   8dB   |
|  101  |   4dB   |
|  100  |   0dB   |
|  000  |   0dB   |  default 
|  001  |  -4dB   |
|  010  |  -8dB   |
|  011  |  -12dB  |


#### RFGain

Read Datasheet.

Note: the RFGain value (4 bits) is distributed over three registers.
PA_BIAS (register 0x05) is only supported in the KT0803K device.
It is not yet supported in the library.

- **bool setRFGain(uint8_t rfgain)** sets rfgain according to table below.
Returns false if rfgain is out of range (0..15).
- **uint8_t getRFgain()** returns 0..15, default 15.


|  RFGAIN  |   RFout      |  PA_BIAS = 1 |  notes  |
|:--------:|:------------:|:------------:|:-------:|
|   0000   |   95.5 dBuV  |      -       |
|   0001   |   96.5 dBuV  |      -       |
|   0010   |   97.5 dBuV  |      -       |
|   0011   |   98.2 dBuV  |      -       |
|   0100   |   98.9 dBuV  |      -       |
|   0101   |  100.0 dBuV  |      -       |
|   0110   |  101.5 dBuV  |      -       |
|   0111   |  102.8 dBuV  |      -       |
|   1000   |  105.1 dBuV  |  107.2 dBuV  |
|   1001   |  105.6 dBuV  |  108.0 dBuV  |
|   1010   |  106.2 dBuV  |  108.7 dBuV  |
|   1011   |  106.5 dBuV  |  109.5 dBuV  |
|   1100   |  107.0 dBuV  |  110.3 dBuV  |
|   1101   |  107.4 dBuV  |  111.0 dBuV  |
|   1110   |  107.7 dBuV  |  111.7 dBuV  |
|   1111   |  108.0 dBuV  |  112.5 dBuV  |  default


#### Region selection

Read datasheet for details.

Note that not all frequencies are allowed in all regions / countries!

The first four are convenience wrappers for **setPHTCNST()**
If some region is missing please let me know the details and I can add 
a wrapper for it.

- **void setEurope()**
- **void setAustralia()**
- **void setUSA()**
- **void setJapan()**
- **bool setPHTCNST(bool on)** See table below.
- **bool getPHTCNST()** returns set value.

|  PHTCNST  |  time   |  Region  |
|:---------:|:-------:|:--------:|
|    0      |  75 μs  |  USA, Japan, (default)
|    1      |  50 μs  |  Europe, Australia


#### PilotToneAdjust

Read datasheet.

- **bool setPilotToneAdjust(uint8_t mode)**  HIGH = 1 LOW = 0
- **uint8_t getPilotToneAdjust()**


#### Mute

Default the device is not muted, but **begin()** will default mute it.
See interface section above.

- **bool setMute(bool mute)** enables or disables the transmitting
by muting the signal.
- **bool getMute()** returns the current state of muting.


## Preference channels

The device and library do not implement the persistant store of user 
selectable preferences (frequencies or channels).
This can be implemented by the user in EEPROM or another persistent medium.

Think of a class that holds an array of channels and optional descriptions.
A minimal hardcoded preset sketch is in the examples.


## Derived classes

A derived class TinyKT0803K class is created, with some extended
functions.

The KT0803L will work as it is backwards compatible with KT0803K. 
It has far more registers in use than the KT0803/K.

The KT0803M is identical to the KT0803K (no new registers), so
a derived class is straightforward.


## Interface KT0803K

(not tested), check datasheet.

#### Mono Stereo

- **bool setMono()** idem
- **bool setStereo()** idem
- **bool isStereo()** idem

#### Bass

- **bool setBass(uint8_t bass);  //  0..3 = 0, 5, 11, 17 dB
- **uint8_t getBass()** idem

#### Misc

- **bool powerOK()** idem
- **bool silenceDetected()** idem


## Future

See - https://github.com/RobTillaart/KT0803


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

