
[![Arduino CI](https://github.com/RobTillaart/MCP4725/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MCP4725/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MCP4725/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MCP4725/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MCP4725/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MCP4725.svg)](https://github.com/RobTillaart/MCP4725/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP4725/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP4725.svg?maxAge=3600)](https://github.com/RobTillaart/MCP4725/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MCP4725.svg)](https://registry.platformio.org/libraries/robtillaart/MCP4725)


# MCP4725

Arduino library for 12 bit I2C DAC - MCP4725.


## Description

The MCP4725 is an I2C single channel 12 bit Digital to Analog Converter (DAC). 
It is possible to have up to 8 MCP4725 on one I2C bus. 
The MCP4725 supports 100 KHz 400 KHz and 3.4 MHz bus speeds.

The output of the MCP4725 depends on the voltage supplied, which is in the range 
of 2.7V .. 5.5V. Check datasheet for the details.


#### 0.4.0 Breaking change

Version 0.4.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/AD56x8 (multi channel)
- https://github.com/RobTillaart/AD568X (single channel lower resolution)
- https://github.com/RobTillaart/MCP_DAC (SPI interface)


## Interface

```cpp
#include "MCP4725.h"
```

### Constructor

- **MCP4725(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor, needs I2C address, optional set Wire bus
- **bool begin()** initializes internals.
Returns false if address out of range.
Returns true if deviceAddress can be found on the I2C bus.
- **bool isConnected()** returns true if device (address) can be seen on the I2C bus.
- **uint8_t getAddress())** returns address set in constructor.

### Base

- **int setValue(uint16_t value = 0)** value = 0 .. 4095.  
Uses writeFastMode and does not write to EEPROM.
Therefore it does not update the lastWriteEEPROM timestamp.
The default value is 0.  
Returns 0 on success
- **uint16_t getValue()** returns last value set from cache, this is much faster than readDAC().  
This latter gives the real value from the MCP4725. 
Note: a difference can be caused by power outage a reset etc.
- **int setPercentage(float percentage)** percentage = 0..100.0%.
Convenience wrapper around setValue().
- **float getPercentage()** returns percentage. Wrapper around getValue().
- **int writeDAC(value, bool EEPROM = false)** Writes to DAC and conditionally to EEPROM.  
This latter is for startup / reset behaviour. Check datasheet for the detail behaviour.
- **bool ready()** returns true if a new value can be written to the MCP4725.  
Return false if recently was written to EEPROM.
- **uint16_t readDAC()** reads the current value set in the MCP4725.
- **uint16_t readEEPROM()** reads the current value in the EEPROM of the MCP4725.
- **uint32_t getLastWriteEEPROM()** returns time in millis() when last value was written to EEPROM.

Page 3 of datasheet states it takes **25 - 50 ms** before values are written to EEPROM. 
So the exact timing of a sensor can differ quite a lot. 
When writing to EEPROM with **writeDAC()** one should check it is at least 50 ms ago.
If one know the specific timing of a sensor one can tune this or even make it adaptive.  


### Voltage interface

(Since 0.3.8) 
Assumes linear behaviour over 12 bit from 0..4095 == 0 .. maxVoltage.
The default value is 5.0 volt.
Allows sort of calibration e.g. setting maxVoltage to 4.952 Volt.
Furthermore it can be a preferred interface over percentage and raw values.

- **void setMaxVoltage(float v = 5.0)** configures maximum voltage of Vout.
- **float getMaxVoltage()** return set maximum.
- **void setVoltage(float v)** set the DAC to voltage v.
This maps the voltage to 0..4095 and calls **setValue()**
- **float getVoltage()** get the current setting as a voltage

If this behaviour is not precise enough or should be more "complex" the user can 
always define its own set of wrapper functions around **getValue()** and **setValue()**.


## Experimental

Check datasheet for these functions, (not tested enough yet).

- **int writePowerDownMode(uint8_t PDM, bool EEPROM = false)**
- **uint8_t readPowerDownModeEEPROM()**
- **uint8_t readPowerDownModeDAC()**
- **int powerOnReset()**
- **int powerOnWakeUp()**

More investigations needed for:
- Writing to EEPROM, **ready()** and **getLastWriteEEPROM()**  
checking when and how long the sensor blocks needs to be verified in detail in practice. 


## Address Notes

The address of the MCP4725 in the demo sketches is set to 0x62 as that 
was the address of the sensor I had during writing. 
According to the datasheet the address has the following bit pattern: 

address  011000FFU   (so 0x6?)

         F = Factory set bit
         U = User configurable bit

This means you can have at most 8 MCP4725 in one I2C bus (without multiplexing).
You have to specify the factory bits in your order, but not all shops might
provide all versions of the MCP4725.

```
MCP4725A0T-E/CH:  0110 000U   0x60 - 0x61
MCP4725A1T-E/CH:  0110 001U   0x62 - 0x63
MCP4725A2T-E/CH:  0110 010U   0x64 - 0x65
MCP4725A3T-E/CH:  0110 011U   0x66 - 0x67
```

If one need more DAC's one might have a look at the MCP4728
It has 4 channels per chip (no experience / library yet)


#### RP2040 specific

There are different RP2040 board files.
This library works with RP2040 pico - https://github.com/earlephilhower/arduino-pico
Will give an error on setSDA() and setSCL() with the "Arduino MBED OS" version.

See remark PR #21.

- **bool begin(int sda, int scl)** begin communication with the DAC. 
It has the parameter for selecting on which pins the communication should happen. 
Check RP2040 Pinout for compatible pins. 
When Wire1 is used, it needs to be specified in the constructor with "&Wire1"


## Multi devices on one I2C bus

Normal one can have 1 to 8 MCP4725 on a I2C bus. This depends on the right
choice of devices as 2 address bits are hard coded in the device. 
See paragraph 7.2 datasheet + address notes section above.

But one cannot always order the right devices.
Especially breakout boards often have the same address-range.


#### TCA9548 I2C multiplexer

Use an I2C multiplexer to create multiple "I2C channels" which allows then 
up to 8 devices per channel. Selecting the right devices includes setting 
the I2C multiplexer to the right channel to address the right device. 
This implies access is a bit slower and uses more code.

One (TCA9548) multiplexer allows one to control up to 64 MCP4725's.

- https://github.com/RobTillaart/TCA9548

Note that other multiplexers do exist.


#### Use A0 address pin as a SELECT pin

(Experimental)  
Need to do more tests to see how this solution behaves in practice.  
Verified to work - see https://forum.arduino.cc/t/using-digital-pins-to-control-two-mcp4725-modules/1161482/7.

The assumption here is that the devices are all from the same address range (factory bits).

You can control multiple MCP4725 over the hardware I2C bus with an extra IO pin per device.
- Connect the address pin of every MCP4725 to an IO pin which will work as a **SELECT** pin.
- Keep all IO pins **LOW** so the all have effectively the same address == 0x60.
- To select a specific MCP4725 you set the related IO pin to **HIGH** and that one will have address == 0x61.
- Now you can access and control the associated MCP4725 with address 0x61.
- See **mcp4725_multiple.ino** and **mcp4725_multiple_minimal.ino**


## Future

#### Must

- update documentation

#### Should

- test the powerDown modes / functions.
- test A0 (address bit) as SELECT pin.
- optimize
  - voltage interface uses float divisions => store reciprocate?
  - takes 2 extra floats.

#### Could

- extend unit tests

#### Wont

- MCP4725_VERSION ==> MCP4725_LIB_VERSION


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

