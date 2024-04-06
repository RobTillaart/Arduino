
[![Arduino CI](https://github.com/RobTillaart/ADT7470/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ADT7470/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ADT7470/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ADT7470/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ADT7470/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ADT7470.svg)](https://github.com/RobTillaart/ADT7470/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADT7470/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADT7470.svg?maxAge=3600)](https://github.com/RobTillaart/ADT7470/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ADT7470.svg)](https://registry.platformio.org/libraries/robtillaart/ADT7470)


# ADT7470

Arduino library for I2C ADT7470 Fan Monitoring.


## Description

The ADT7470 Fan Monitoring library offers an I2C device that can
monitor and control up to four fans. Further this module can daisy 
chain up to 10 (specific TMP05/06) temperature sensors.

Please read datasheet carefully before working with the module.

**Experimental**  
This library was build in 2015 from datasheet (PDF) on request and
is never tested by me. So it is experimental at best and if you have the 
hardware and are able to try this library I would really appreciate it
as it is a quite unique module.

That said the library is supporting setting the fan speed and measure 
the RPM, so it should be usable e.g. for a climate controlled room or
cabinet.

**Warning**
Do not forget to put a diode over the Fan to prevent damage due to
inductive pulse when switched off. (see also datasheet).


## ADT7470 Address Select Mode

(from datasheet)

|  Pin 11                 | (ADDR) State |  Address                                      |
|:------------------------|:------------:|:---------------------------------------------:|
|  HIGH (10 kΩ to VCC)    |  010 1111    |  0x5E left-justified or 0x2F right-justified  | 
|  LOW  (10 kΩ to GND)    |  010 1100    |  0x58 left-justified or 0x2C right-justified  |
|  Floating (no pull-up)  |  010 1110    |  0x5C left-justified or 0x2E right-justified  |


## Interface

```cpp
#include "ADT7470.h"
```

Check datasheet for the details as this section needs to be elaborated.

- **ADT7470(uint8_t address, TwoWire \*wire = &Wire)** constructor, with default I2C bus.
- **void begin()** initialize the library
- **bool isConnected()** check if the module is connected to the I2C bus
- **void startMonitoring()** 
- **void stopMonitoring()**
- **void powerDown()** energy save mode
- **void powerUp()** active mode


#### Administrative

- **uint8_t getRevision()** returns version of the firmware.
- **uint8_t getDeviceID()** should return 0x70.
- **uint8_t getCompanyID()** should return 0x41.


#### Temperature

- **int8_t getTemperature(uint8_t index)** index = 0..9; if connected it returns the temperature 
of sensor index. Temperature sensors are daisy changed.
- **int8_t getMaxTemperature()** get max temperature of connected temperature sensors.
- **bool setTemperatureLimit(uint8_t index, int8_t low, int8_t high)** for ALARM function
- **int8_t getTemperatureLowLimit(uint8_t index)** return the set value. Default ?
- **int8_t getTemperatureHighLimit(uint8_t index)** return the set value. Default ?


#### PWM

- **bool setPWM(uint8_t index, uint8_t value)** set the speed of the fan at index
- **uint8_t getPWM(uint8_t index)** read back the speed set. 
- **bool setFanLowFreq(value = 0)** set PWM frequency.
- **bool setFanHighFreq(value = 0)** 
- **void setInvertPWM(uint8_t index)**
- **uint8_t getInvertPWM(uint8_t index)**


#### Tachio & RPM

- **bool setPulsesPerRevolution(uint8_t index, uint8_t value)** value should be 1..4 as a fan gives 1..4 pulses per revolution. 
This value is needed to calculate a correct tach and RPM.
- **uint8_t getPulsesPerRevolution(uint8_t index)** read back PulsePerRevolution. returns 1..4.
- **void setFastTach()** Tach register is updated 4x per second.
- **void setSlowTach()** Tach register is updated 1x per second. 
- **uint16_t getTach(uint8_t index)** get the raw pulses.
- **uint32_t getRPM(uint8_t index)** get Revolutions Per Minute, based upon **getTach()**
- **bool setTachLimits(uint8_t index, uint16_t low, uint16_t high)** 
- **uint16_t getTachLowLimits(uint8_t index)** 
- **uint16_t getTachHighLimits(uint8_t index)**


#### Interrupts

- **uint16_t getTemperatureIRQstatus()**
- **void setTemperatureIRQMask(uint8_t index)**
- **void clrTemperatureIRQMask(uint8_t index)**
- **uint8_t getTemperatureIRQMask(uint8_t index)**
- **uint8_t getFanIRQstatus()**
- **void setFanIRQMask(uint8_t index)**
- **void clrFanIRQMask(uint8_t index)**
- **uint8_t getFanIRQMask(uint8_t index)**


## Operation

See examples


## Future

This library will only be worked on on request as I have no hardware to test.

#### Must

#### Should

#### Could

- improve documentation, readme.md file.
  - The descriptions are short and need to be extended.
- implement async interface - getTemperature()
- fix TODO's in code
- get the hardware to test
- change pins from PWM to digital IO
- do we need default values for parameters e.g. index = 0 ?
- investigate temperature sensors    (functions are prepared)
- investigate how to connect temp sensors  (daisy chained)  
https://ez.analog.com/temperature_sensors/f/discussions/77540/adt7470-and-tmp05-daisy-chain-temeparure-sensing
- investigate the FULLSPEED pin, must it be in the library?  
  - software version ==> fullSpeed(uint8_t index)
- investigate auto mode (datasheet?)
- ...


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


