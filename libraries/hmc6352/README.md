
[![Arduino CI](https://github.com/RobTillaart/HMC6352/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HMC6352/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HMC6352.svg?maxAge=3600)](https://github.com/RobTillaart/HMC6352/releases)

# HMC6352

Arduino library for HMC6352 compass sensor

## Description

**BETA: WARNING: BETA: WARNING: BETA: WARNING: BETA:** 

This library is BETA, only tested partially and not thoroughly
No guarantees, use at own risk, all disclaimers apply 
The example sketch can be used to config the compass.
For switching operational mode one must reboot the system.

**WARNING: BETA: WARNING: BETA: WARNING: BETA: WARNING:**

## Interface

TO elaborate

Check datasheet

### Constructor

- **hmc6352(uint8_t device)**
- **void begin(uint8_t sda, uint8_t scl)** for ESP32 ea
- **void begin()** for UNO

### Base calls standby mode

- **int getHeading(void)**
- **int askHeading(void)**
- **int readHeading(void)**
- **int wakeUp(void)**
- **int sleep(void)**

### Expert calls

- **int factoryReset()**
- **int setOperationalModus(hmcMode m, uint8_t freq, bool periodicReset)**
- **int getOperationalModus()**
- **int setOutputModus(uint8_t om)**
- **int getOutputModus()**
- **int callibrationOn(void)**
- **int callibrationOff(void)**
- **int setI2CAddress(uint8_t address)**
- **int getI2CAddress()**
- **int writeEEPROM(uint8_t address, uint8_t data)**
- **int readEEPROM(uint8_t address)**
- **int writeRAM(uint8_t address, uint8_t data)**
- **int readRAM(uint8_t address)**
- **int saveOpMode(byte OpMode)** allow power users to set operational mode flags

### NOT TESTED / unknown

Check datasheet

- **int setTimeDelay(uint8_t msec)**
- **int getTimeDelay()**
- **int setMeasurementSumming(uint8_t ms)**
- **int getMeasurementSumming()**
- **int updateOffsets(void)**


## Operation

See examples
