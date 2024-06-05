
[![Arduino CI](https://github.com/RobTillaart/MCP_DAC/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP_DAC/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP_DAC/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP_DAC/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP_DAC/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP_DAC.svg)](https://github.com/RobTillaart/MCP_DAC/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP_DAC/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP_DAC.svg?maxAge=3600)](https://github.com/RobTillaart/MCP_DAC/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP_DAC.svg)](https://registry.platformio.org/libraries/robtillaart/MCP_DAC)


# MCP_DAC

Arduino library for Microchip SPI DAC's:  8, 10, 12 bits, 1, 2 channel.


## Description

The MCP_DAC is a library for DAC's from Microchip in the MCP48xx en MCP49xx series.
The library is not tested with all different devices however stable.

Please post an issue if there are problems with a specific device.


|  Type   | Channels | Bits | MaxValue | Voltage reference |
|:--------|:--------:|:----:|:--------:|:-----------------:|
| MCP4801 |  1       |  8   |   255    | internal 2.048 V  |
| MCP4802 |  2       |  8   |   255    | internal 2.048 V  |
| MCP4811 |  1       |  10  |   1023   | internal 2.048 V  |
| MCP4812 |  2       |  10  |   1023   | internal 2.048 V  |
| MCP4821 |  1       |  12  |   4095   | internal 2.048 V  |
| MCP4822 |  2       |  12  |   4095   | internal 2.048 V  |
| MCP4901 |  1       |  8   |   255    | external          |
| MCP4902 |  2       |  8   |   255    | external          |
| MCP4911 |  1       |  10  |   1023   | external          |
| MCP4912 |  2       |  10  |   1023   | external          |
| MCP4921 |  1       |  12  |   4095   | external          |
| MCP4922 |  2       |  12  |   4095   | external          |


The output voltage of the MCP_DAC depends on the voltage supplied,
which is in the range of 2.7V .. 5.5V. Check datasheet for the details.


#### 0.5.0 Breaking change

Version 0.5.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **MCP.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.4.0 Breaking change

The version 0.4.0 has breaking changes in the interface. 
The rationale is that the programming environment of the **Arduino ESP32 S3** 
board uses a remapping by means of the include file **io_pin_remap.h**.
This file remaps the pins of several core Arduino functions. 
The remapping is implemented by #define macros and these implement "hard" text 
replacements without considering context. 
The effect is that methods from this class (and several others) which have the same 
name as those Arduino core functions will be remapped into something not working.

The following library functions have been renamed:

|  old name        |  new name    |  notes  |
|:-----------------|:-------------|:--------|
|  analogRead()    |  read()      |
|  analogWrite()   |  write()     |
|  pinMode()       |  pinMode1()  |
|  digitalRead()   |  read1()     |
|  digitalWrite()  |  write1()    |



#### 0.3.0 breaking change

The version 0.3.0 has breaking changes in the interface. The essence is that the
dependency of Wire (ESP32 / RP2040) is removed from the library.
This makes it possible to support the **ESP32-S3** and other processors in the future.
Also it makes the library a bit simpler to maintain.


#### Related

- https://github.com/RobTillaart/MCP_ADC
- https://github.com/RobTillaart/MAX520
- https://github.com/RobTillaart/MCP_DAC
- https://github.com/RobTillaart/MCP4725
- https://github.com/RobTillaart/DAC8550
- https://github.com/RobTillaart/DAC8551
- https://github.com/RobTillaart/DAC8552
- https://github.com/RobTillaart/DAC8554


## Interface

```cpp
#include "MCP_DAC.h"
```

#### Constructor

- **MCP_DAC(SPIClassRP2040 \*mySPI = &SPI)** Constructor base class for RP2040, hardware SPI.
- **MCP_DAC(SPIClass \*mySPI = &SPI)** Constructor base class other platforms, hardware SPI.
- **MCP_DAC(uint8_t dataOut = 255, uint8_t clock = 255)** Constructor base class, software SPI.
Other devices just use their name as class object e.g. **MCP4801()** with same parameters.
- **begin(uint8_t select)** defines the select pin.
The select pin is used for device selection in case of multiple SPI devices.
- **uint8_t channels()** returns the number of channels, 1 or 2.
(note channel numbers are 0 or 1).
- **uint16_t maxValue()** returns the maximum value that can be set.
This relates to the number of bits, see table above.


#### Gain

- **bool setGain(uint8_t gain = 1)** gain is 1 (default) or 2.
- **uint8_t getGain()** returns gain set, default 1.

The analog output cannot go beyond the supply voltage.  
So if Vref is connected to 5V, gain = 2 will not output 10 Volts.


#### Write

- **bool write(uint16_t value, uint8_t channel = 0)** writes value to channel.
Default for channel 0 as that works for the single DAC devices.
The value is limited to maxValue.
Returns false in case of an invalid channel.
- **uint16_t lastValue(uint8_t channel = 0)** returns last written value. 
Default for channel 0 as that works for the single DAC devices.
- **void setPercentage(float percentage, uint8_t channel = 0)** percentage = 0..100.0%.  
Wrapper around **write()**.
- **float getPercentage(uint8_t channel = 0)** returns percentage. 
Reads from cache.
- **void fastWriteA(uint16_t value)** faster version to write to channel 0. 
Does not check flags and does not update **lastValue()**
- **void fastWriteB(uint16_t value)** faster version to write to channel 1. 
Does not check flags and does not update **lastValue()**
- **bool increment(uint8_t channel = 0)** returns true if channel is incremented, false otherwise.
- **bool decrement(uint8_t channel = 0)** returns true if channel is decremented, false otherwise.

For fastest speed there is an example added **MCP4921_standalone.ino**.
That squeezes the most performance out of it for now.
Code for the other MCP4xxx can be written in same way.


#### Shutdown

- **void shutDown()** shuts down the device, optional one might need to **triggerLatch()**.
- **bool isActive()** returns false if device is in shutdown mode.
Note: any **write()** operation will set active to true again.


#### Hardware SPI

To be used only if one needs a specific speed.
Check datasheet for details.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.


#### LDAC

- **void setLatchPin(uint8_t latchPin)** defines the latchPin, this is optional. 
The latchPin is used for simultaneous setting a value in both DAC registers.
It can also be used to synchronize the setting of multiple devices.
Note the latchPin must be the same for all instances that need to be triggered together.
- **triggerLatch()** toggles the defined latchPin, and all devices that are connected to it.

Note: pre 0.2.0 versions have the LDAC signal incorrectly inverted.


#### Buffered

**MCP49xxx series only**, see page 20 ==> not functional for MCP48xx series.

- **void setBufferedMode(bool mode = false)** set buffered mode on/off. 
The default mode == false == unbuffered.
- **bool getBufferedMode()** returns set value.


#### Debug

- **void reset()** resets internal variables to initial value. (use with care!).
- **bool usesHWSPI()** returns true if HW SPI is used.


## ESP32 specific

Several functions removed in 0.3.0 as they were too processor specific,
and prevented support for the ESP32-S3.


#### ESP32 connections to MCP4922 (example)

ESP32 (first series) has **four** SPI peripherals from which two can be used.

SPI0 and SPI1 are used to access flash memory. 
SPI2 and SPI3 are "user" SPI controllers a.k.a. HSPI and VSPI.


|   MCP4922  |  HSPI = SPI2  |  VSPI = SPI3  |
|:----------:|:-------------:|:-------------:|
|    CS      |  SELECT = 15  |  SELECT = 5   |
|    SCK     |  SCLK   = 14  |  SCLK   = 18  |
|    SDI     |  MOSI   = 13  |  MOSI   = 23  |
|  not used  |  MISO   = 12  |  MISO   = 19  |

By using different **SELECT** pins multiple DAC's can be controlled over one SPI bus.


The ESP32-S3 introduces user access to FSPI (which is reused from flash memory).
Depending on ESP32 series e.g. HSPI is different, see code snippet below.

```cpp
#if CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32S3
#define FSPI  0
#define HSPI  1  
#else  
#define FSPI  1 //SPI bus attached to the flash (can use the same data lines but different SS)  
#define HSPI  2 //SPI bus normally mapped to pins 12 - 15, but can be matrixed to any pins  
#if CONFIG_IDF_TARGET_ESP32  
#define VSPI  3 //SPI bus normally attached to pins 5, 18, 19 and 23, but can be matrixed to any pins  
#endif  
#endif
```

## RP2040 specific

#### SPI port selection

The SPI Port selections happens in the hardware constructor with e.g. &SPI, &SPI1 etc.
In pre-0.3.0 an experimental feature **void setGPIOpins** was supported to adjust the
hardware pins however this should now be handled by the user outside the library.


#### Pico connections to MCP4922 (example)

The RP2040 has **two** SPI peripherals from which two can be used.

SPI (SPI0) and SPI1 can both be used to connect devices.


| MCP4922  |   SPI / SPI0  |      SPI1     |
|:--------:|:-------------:|:-------------:|
|  CS      |  SELECT = 17  |  SELECT = 13  |
|  SCK     |  SCLK   = 18  |  SCLK   = 14  |
|  SDI     |  MOSI   = 19  |  MOSI   = 15  |
| not used |  MISO   = 16  |  MISO   = 12  |

By using different **SELECT** pins multiple DAC's can be controlled over one SPI bus.


## Operation

See examples


## Future

#### Must

- test test test and ....
- improve documentation.

#### Should


#### Could

- functional names for magic masks.
- refactor the API (how).

#### Wont

- **useSPI1** and **useHSPI** are functional identical indicators.
  - how to refactor to a generic model? Should work for all libraries.
  - int8_t HWSPIport = 0, 1, 2, 3, 4, ....  (-1 == SW SPI ?).
    - numbers are not self-documenting.
    - **selectSPIport(int)** ?
  - would reduce conditional code.
  - does not improve library


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

