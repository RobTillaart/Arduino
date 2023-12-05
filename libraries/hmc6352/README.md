
[![Arduino CI](https://github.com/RobTillaart/HMC6352/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HMC6352/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HMC6352/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HMC6352/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HMC6352/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HMC6352.svg)](https://github.com/RobTillaart/HMC6352/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HMC6352/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HMC6352.svg?maxAge=3600)](https://github.com/RobTillaart/HMC6352/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HMC6352.svg)](https://registry.platformio.org/libraries/robtillaart/HMC6352)


# HMC6352

Arduino library for HMC6352 compass sensor


## Description

**BETA: WARNING: BETA: WARNING: BETA: WARNING: BETA:** 

This library is BETA, only tested partially and not thoroughly
No guarantees, use at own risk, all disclaimers apply 
The example sketch can be used to configuration the compass.
For switching operational mode one must reboot the device.

**WARNING: BETA: WARNING: BETA: WARNING: BETA: WARNING:**


#### 0.4.0 Breaking change

Version 0.4.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/Angle
- https://github.com/RobTillaart/AngleConvertor
- https://github.com/RobTillaart/AverageAngle
- https://github.com/RobTillaart/AS5600


## Interface

```cpp
#include "hmc6352.h"
```

### Constructor

- **hmc6352(uint8_t address, TwoWire \*wire = &Wire)** set the I2C address and optional the Wire interface.
- **bool begin()** initializes library.
Returns true if address can be seen on the I2C bus.
- **bool isConnected()** Returns true if address can be seen on the I2C bus. 
Can be used as first order diagnostics.


### Base calls standby mode

- **int getHeading()** is a combination of **askHeading()** and **readHeading()**
- **int askHeading()** requests a new read of the heading (compass direction).
- **int readHeading()** reads the new value from the device.
- **int wakeUp()** if the device is in sleep mode, wake it up.
- **int sleep()** puts the device in sleep mode.


### Expert calls

Warning: use with care: read the datasheet for the details

- **int factoryReset()** idem
- **int setOperationalModus(hmcMode mode, uint8_t frequency, bool periodicReset)**
- **int getOperationalModus()**
- **int setOutputModus(uint8_t outputModus)**
- **int getOutputModus()**
- **int callibrationOn()**
- **int callibrationOff()**
- **int setI2CAddress(uint8_t address)** writes the I2C address in EEPROM to use after the next reboot.
- **int getI2CAddress()** reads the I2C address stored in EEPROM.


### Helper functions

Warning: use with care: read the datasheet for the details

- **int writeEEPROM(uint8_t address, uint8_t data)** EEPROM IO function
- **int readEEPROM(uint8_t address)** EEPROM IO function
- **int writeRAM(uint8_t address, uint8_t data)** RAM IO function
- **int readRAM(uint8_t address)** RAM IO function
- **int saveOpMode(byte OpMode)** allow power users to set operational mode flags


### NOT TESTED

Warning: use with care: read the datasheet for the details

- **int setTimeDelay(uint8_t milliSeconds)**
- **int getTimeDelay()**
- **int setMeasurementSumming(uint8_t NrOfMeasurements)** 1..16 
- **int getMeasurementSumming()** returns 1..16
- **int updateOffsets(void)**


## Operation

See examples


## Future

#### Must

- update documentation

#### Should

- testing AVR
- testing ESP32
- test examples => more specific?

#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


