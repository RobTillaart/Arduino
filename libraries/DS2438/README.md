
[![Arduino CI](https://github.com/RobTillaart/DS2438/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DS2438/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DS2438/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DS2438/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DS2438/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DS2438.svg)](https://github.com/RobTillaart/DS2438/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS2438/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS2438.svg?maxAge=3600)](https://github.com/RobTillaart/DS2438/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DS2438.svg)](https://registry.platformio.org/libraries/robtillaart/DS2438)


# DS2438

Arduino Library for the DS2438 1-wire battery monitor.


#### Note

Started with this library, however I could not find these sensors for sale.
It is shared for future reference.


## Description

The DS2438 is a **very experimental** library for the DS2438 battery management sensor.

The library is not tested yet as I have no hardware (hard to get).
So for the moment the library is written based upon the datasheet 
and provided as is.

The device supports the following functionality.
- voltage measurement
- temperature measurement
- current measurement.
- 40 bytes non-volatile EEPROM memory
- Elapsed time meter in binary format

This library supports only one DS2438 per Arduino / MCU pin.

As always, feedback is welcome.


#### Hardware pins

Need to find a breakout.

See datasheet for details

```
                   DS2438
              +------------------+
              | 1  GND           |
              | 2  Vsense+       |
              | 3  Vsense-       |
              | 4  Vad           |
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
                                                                |

#### Related

- https://github.com/RobTillaart/DS2438
- https://github.com/RobTillaart/Temperature  (conversions)


## Interface

```cpp
#include "DS2438.h"
```

#### Constructor

- **DS2438(OneWire \* ow)** constructor needs a reference to OneWire object.
- **bool begin(uint8_t retries = 3)** resets oneWire.
Returns true if address / device is found and all is OK. 
There will be a number of retries to connect, default 3.
- **bool isConnected(uint8_t retries = 3)** Returns true if address / device is found.
There will be a number of retries to connect, default 3.


#### Temperature and voltage

- **float readTemperature()** read temperature from device. Degrees Celsius.
- **float getTemperature()** get the last read temperature.
- **bool readVoltage(uint8_t channel)** read voltage from device. Volts.
- **float getVoltage(uint8_t channel)** get the last read voltage.


#### Current

- **void setResistor(float resistor = 0.01)** set the shunt resistor in OHM.
This allows a sort of tuning/calibration.
- **void enableCurrentMeasurement()** set IAD bit, see datasheet.
Starts the background measurement of the current.
Takes ~28 milliseconds for a measurement.
Must be called before readCurrent will work.
- **void disableCurrentMeasurement()** clear IAD bit, see datasheet.
Stops the background measurement of the current.
- **float readCurrent()** read current from device.
- **float getCurrent()** get last read current.


#### Current Offset

See datasheet for details.
units not clear yet.

- **void writeCurrentOffset(int value)** 
- **int readCurrentOffset()**

#### Threshold

See datasheet for details.

- **void writeThreshold(uint8_t value)**
- **uint8_t readThreshold()**

only 4 values possible.

|  value  |  THRESHOLD       |
|:-------:|:----------------:|
|  0x00   |  None (default)  |
|  0x40   |  ±2 LSB          |
|  0x80   |  ±4 LSB          |
|  0xC0   |  ±8 LSB          |


#### Time

From datasheet:

The elapsed time meter (ETM) is a 4-byte binary counter with 1-second resolution. 
The ETM can accumulate 136 years of seconds before rolling over. 
Time/date is represented by the number of seconds since a reference point, which is determined by the user. 
For example, 12:00 A.M., January 1, 1970 could be used as a reference point.

- **void writeElapsedTimeMeter(uint32_t value)** value in seconds.
- **uint32_t readElapsedTimeMeter()** returns current time in seconds.


#### EEPROM

Valid addresses are 0..39.

- **bool writeEEPROM(uint8_t address, uint8_t value)** write a byte to EEPROM address.
- **uint8_t readEEPROM(uint8_t address)** read the byte from EEPROM address.


#### Configuration register

See datasheet for details.

- **void setConfigBit(uint8_t bit)**
- **void clearConfigBit(uint8_t bit)**
- **uint8_t getConfigByte()**


## Operation

This library supports only one DS2438 per Arduino / MCU pin.


## Future

#### Must

- Improve documentation (a lot).
- test with hardware or simulator?.
- examples for testing.


#### Should

only after testing and 0.1.0 code works.

- implement Disconnect timestamp
- implement End of charge timestamp
- implement Integrated Current Accumulator (ICA).
- implement Charging Current Accumulator (CCA).
- implement Discharging Current Accumulator (DCA).


#### Could

only after testing and 0.1.0 code works.

- unit tests?
  - possible?
- async interface for both T and V.
- optimize the code.
  - cache registers?
- improve magic masks and numbers
- performance test.
- getAddress() ?
- debug and error handling.
- copy snapshot to EEPROM(page)
  - copies page 0 to EEPROM page 0..4


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

