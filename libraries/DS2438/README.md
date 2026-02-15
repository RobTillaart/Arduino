
[![Arduino CI](https://github.com/RobTillaart/DS2438/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS2438/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS2438/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS2438/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS2438/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS2438.svg)](https://github.com/RobTillaart/DS2438/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS2438/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS2438.svg?maxAge=3600)](https://github.com/RobTillaart/DS2438/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS2438.svg)](https://registry.platformio.org/libraries/robtillaart/DS2438)


# DS2438

Arduino Library for the DS2438 1-wire battery monitor.


## Description

**Experimental**

The DS2438 is a experimental library for the DS2438 battery management sensor.

The library is not tested by me in detail as I have no hardware (breakout board).
So for the moment the library is written based upon the datasheet and provided as is.
That said, the library is working (see e.g. #5) but use it with care as it is still
work in progress.

The device supports the following functionality.
- voltage measurement
- temperature measurement
- current measurement.
- 40 bytes non-volatile EEPROM memory
- Elapsed time meter in binary format

This library supports only one DS2438 per Arduino / MCU pin.

As always, feedback is welcome.


### 0.2.0 Breaking Change

The 0.2.0 version fixes a bug in the EEPROM that affects the proper working
of the device. (See issue 5).

Versions before 0.2.0 are therefore obsolete.


### Hardware pins

Need to find a breakout.

See datasheet for details for a measurement schema.

```
                   DS2438
              +------------------+
              | 1  GND           |
              | 2  Vsense+       |
              | 3  Vsense-       |
              | 4  VAD           |
              | 5  VDD           |
              | 6  NC            |
              | 7  NC            |
              | 8  DQ            |
              +------------------+
```

|  Pin     |  Description                        |  Connect to  |
|:--------:|:------------------------------------|:-------------|
|  DQ      |  Data In/Out                        |  processor   |
|  VAD     |  General A/D input                  |              |
|  VSENS+  |  Battery current monitor input (+)  |  Battery     |
|  VSENS-  |  Battery current monitor input (-)  |  Battery     |
|  VDD     |  Power Supply (2.4V to 10.0V)       |  +5V         |
|  GND     |  Ground                             |  processor   |
|  NC      |  No connect                         |  -           |


### Related

- https://github.com/RobTillaart/DS2438 - this library.
- https://github.com/RobTillaart/INA226 - current, voltage, power sensor
- https://github.com/RobTillaart/Temperature  (conversions)


### Special chars

ALT234 = Ω (Ohm)

## Interface

```cpp
#include "DS2438.h"
```

### Constructor

- **DS2438(OneWire \* ow)** constructor needs a reference to OneWire object.
- **bool begin(uint8_t retries = 3)** resets oneWire.
Returns true if address / device is found and all is OK. 
There will be a number of retries to connect, default 3.
- **bool isConnected(uint8_t retries = 3)** Returns true if address / device is found.
There will be a number of retries to connect, default 3.

### Temperature

- **float readTemperature()** read temperature from device. Units = Celsius.
- **float getTemperature()** get the last read temperature.

### Voltage

- **float readVDD()** read voltage VDD from device. Units = Volts.
- **float getVDD()** get the last read voltage VDD.
- **float readVAD()** read voltage VAD.  Units = Volts.
- **float getVAD()** get the last read voltage VAD.

### Current

See datasheet for details. 
Choice of the resistor determines the working range / accuracy.

- **void setResistor(float resistor = 0.01)** set the shunt resistor in Ohm.
This allows a sort of tuning/calibration.
- **void enableCurrentMeasurement()** set IAD bit, see datasheet.
Starts the background measurement of the current.
Takes ~28 milliseconds for a measurement.
Must be called before readCurrent will work.
- **void disableCurrentMeasurement()** clear IAD bit, see datasheet.
Stops the background measurement of the current.
- **float readCurrent()** read current from device.
- **float getCurrent()** get last read current.

Datasheet page 6, 
When writing to the Offset Register, current measurement MUST be disabled.
Read datasheet for calibration routine.

- **void writeCurrentOffset(int value)** 
- **int readCurrentOffset()**


### ICA 

See datasheet for details.

- ICA = Integrated Current Accumulator.

- **float readRemaining()**
- **void writeThreshold(uint8_t value)**
- **uint8_t readThreshold()**

Only 4 values possible.

|  value  |  Threshold       |
|:-------:|:----------------:|
|  0x00   |  None (default)  |
|  0x40   |  ±2 LSB          |
|  0x80   |  ±4 LSB          |
|  0xC0   |  ±8 LSB          |


### Time

From datasheet:

The elapsed time meter (ETM) is a 4-byte binary counter with 1-second resolution. 
The ETM can accumulate 136 years of seconds before rolling over. 
Time/date is represented by the number of seconds since a reference point, which is determined by the user. 
For example, 12:00 A.M., January 1, 1970 could be used as a reference point.

- **void writeElapsedTimeMeter(uint32_t value)** value in seconds.
- **uint32_t readElapsedTimeMeter()** returns current time in seconds.
- **uint32_t readDisconnectTime()** returns last disconnect timestamp.
- **uint32_t readEndOfChargeTime()** returns last end of charging timestamp.


### EEPROM

Valid addresses are 0..35 if CCA/DCA is enabled, 0..39 otherwise.

- **bool writeEEPROM(uint8_t address, uint8_t value)** write a byte to EEPROM address.
- **uint8_t readEEPROM(uint8_t address)** read the byte from EEPROM address.


### CCA DCA

See datasheet page 8 + 16 for details.

- CCA = Charging Current Accumulator
- DCA = Discharge Current Accumulator

The delta CCA - DCA should be actual load. 

- **void enableCCA()** also enables DCA.
- **void disableCCA()**

To enable shadowing in EEPROM
- **void enableCCAShadow()** => EEPROM reduced to address 0..35
- **void disableCCAShadow()**

Note the setters below block for 10+ milliseconds
- **bool setCCA(float CCA)** returns true on success, negative values not allowed,
no upper limit check.
- **bool setDCA(float DCA)** returns true on success, negative values not allowed,
no upper limit check.
- **void resetAccumulators()** sets both CCA and DCA to zero.

Read back the values.
- **float readCCA()** Does not check if enabled.
- **float readDCA()** Does not check if enabled.


### Configuration + status register

See datasheet page 15 for details.

- **void setConfigBit(uint8_t bit)**  bit = 0..3
- **void clearConfigBit(uint8_t bit)** bit = 0..3
- **uint8_t getConfigRegister()** returns configuration and status bits.

|  bit  |  name  |  default  |  description  |
|:-----:|:------:|:---------:|:--------------|
|   0   |  IAD   |     1     |  Current A/D Control bit.
|   1   |   CA   |     1     |  Current Accumulator Configuration bit.
|   2   |   EE   |     1     |  Current Accumulator Shadow Selector bit.
|   3   |   AD   |     1     |  Voltage A/D Input Select bit. 1 = VDD,  0 = VAD.
|   4   |   TB   |     0     |  Temperature Busy Flag.
|   5   |  NVB   |     0     |  Non Volatile Memory Busy Flag.
|   6   |  ADB   |     0     |  A/D Converter Busy Flag.
|   7   |   x    |     x     |  don't care.

### Status

Reads status bits from configuration register above.

- **bool busy()** any busy flag set
- **bool busyTemperature()** temperature conversion busy
- **bool busyNVRAM()** NOn volatile memory busy
- **bool busyADC()** A/D conversion busy.


## Operation

This library supports only one DS2438 per Arduino / MCU pin.


## Future

#### Must

- Improve documentation (a lot).
- test with hardware or simulator?.
- examples for testing.

#### Should

- implement CRC
- add device type check

#### Could

only after testing and code works.
- renaming: getVDD() vs getLastVDD? et al.
- getters,
  - remove? == user responsibility?
- unit tests?
  - possible?
- async interface for both T and V.
  - performance gain ?!
- optimize the code.
  - cache registers?
- improve magic masks and numbers
- performance test.
- getAddress() ?
- debugging
- error handling.
- copy snapshot to EEPROM(page) -> datasheet p.8 EE bit.
  - copies page 0 to EEPROM page 0..4


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

