
[![Arduino CI](https://github.com/RobTillaart/INA219/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA219/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA219/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA219/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA219/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA219.svg)](https://github.com/RobTillaart/INA219/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA219/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA219.svg?maxAge=3600)](https://github.com/RobTillaart/INA219/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA219.svg)](https://registry.platformio.org/libraries/robtillaart/INA219)


# INA219

Arduino library for INA219 voltage, current and power sensor.


## Description

**Experimental** library for the INA219 power sensor.
Minimal tested, so usage remarks and comments are welcome.

Read datasheet for details.

**USE WITH CARE**

The INA219 is a voltage, current and power measurement device. 
A few important maxima, see datasheet, chapter 7, esp 7.5

|   description   |  max  |   unit  |  notes  |
|:----------------|------:|--------:|:--------|
|  bus voltage    |  32   |  Volt   |  depends on BRNG setting
|  shunt voltage  |  320  |  mVolt  |  depends on PGA setting



#### 0.4.0 Breaking change

Version 0.4.0 fixed negative values for **getShuntVoltage()**.
Older versions are obsolete now.


#### 0.2.0 Breaking change

Version 0.2.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)


#### Related

- https://www.ti.com/product/INA219#tech-docs
- https://www.ti.com/product/INA219#params
- https://www.ti.com/document-viewer/INA219/datasheet
- https://github.com/RobTillaart/INA219
- https://github.com/RobTillaart/INA226


## I2C

#### Address

The sensor can be configured to use 1 of 16 I2C addresses between 0x40 and 0x4F.
The address depends on how the A0 and A1 address lines are connected to the SCL, SDA, GND and VCC pins.
(datasheet chapter 8.5.5.1 Serial Bus Address)


#### Performance

Datasheet states it supports 1 KHz .. 2.56 MHz.
Note: higher speeds and longer wires need smaller pull up resistors.

Some timings in micros for **INA.getMode()** on an Arduino UNO.
This is just one readRegister call, similar to most functions.

Above 600 KHz there is little performance gain.

|  speed  |  time  |  speed  |  time  |  speed  |  time  |  speed  |  time  |
|:-------:|:------:|:-------:|:------:|:-------:|:------:|:-------:|:------:|
|  100000 |   560  |  150000 |   396  |  200000 |   320  |  250000 |   272  |
|  300000 |   232  |  350000 |   208  |  400000 |   196  |  450000 |   176  |
|  500000 |   172  |  550000 |   164  |  600000 |   152  |  650000 |   152  |
|  700000 |   144  |  750000 |   144  |  800000 |   140  |         |        |

use **INA219_test_I2C.ino**


## Interface

```cpp
#include "INA219.h"
```


#### Constructor

- **INA219(const uint8_t address, TwoWire \*wire = Wire)** Constructor to set
the address and optional Wire interface.
- **bool begin()** initializes the class.
Returns true if the INA219 address (set in the constructor) is on the I2C bus.
- **bool isConnected()** Returns true if the INA219 address (set in the constructor) is on the I2C bus.
- **uint8_t getAddress()** Returns the INA219 address set in the constructor.


#### Core Functions

Note the power and the current are not meaningful without calibrating the sensor. 
Also the value is not meaningful if there is no shunt connected.

- **float getShuntVoltage()** idem, in volts.
- **float getBusVoltage()** idem. in volts. Max 32 Volt.
- **float getCurrent()** returns the current through the shunt in Ampere.
- **float getPower()** returns the current x BusVoltage in Watt.

The library has helper functions to convert above output to a more appropriate scale of units.

Helper functions for the milli scale.

- **float getBusVoltage_mV()** idem, in milliVolts.
Note: returns -100 if the math overflow bit is set.
- **float getShuntVoltage_mV()** idem, in milliVolts.
- **float getCurrent_mA()** idem, in milliAmpere.
- **float getPower_mW()** idem, in milliWatt.

Helper functions for the micro scale.

- **float getBusVoltage_uV()** idem, in microVolts.
- **float getShuntVoltage_uV()** idem, in microVolts.
- **float getCurrent_uA()** idem, in microAmpere.
- **float getPower_uW()** idem, in microWatt.


##### Indicator flags

- **bool getMathOverflowFlag()** internal math overflow.
- **bool getConversionFlag()** conversion is ready.
Especially useful in non-continuous modi.


#### Configuration

- **bool reset()** software power on reset. 
This implies that calibration with **setMaxCurrentShunt()** needs to be redone.
See section below.
Returns false if it could not write settings to device.
- **bool setBusVoltageRange(uint8_t voltage = 16)** set to 16 or 32.
Values <= 16 map to 16 and values between 16 and 32 map to 32.
Returns false if voltage is above 32.
Returns false if it could not write settings to device.
- **uint8_t getBusVoltageRange()** returns 16 or 32. (Volts)
- **bool setGain(uint8_t factor)** factor = 1, 2, 4, 8 (default).
Determines the shunt voltage range. 40, 80, 160 or 320 mV. 
Returns false if factor is not a valid value.
Returns false if it could not write settings to device.
- **uint8_t getGain()** returns set factor.
- **int getMaxShuntVoltage()** returns 40, 80, 160 or 320 (mV).
320 is the sensors default.


#### Configuration BUS and SHUNT

**Note:**
The internal conversions runs in the background in the device.
If a conversion is finished the measured value is stored in the appropriate register. 
The last obtained values can always be read from the registers, so they will not block.
Result can be that you get the very same value if no new data is available yet.
This is especially true if you increase the number of samples.
(See also discussion in INA219 issue 11).

Using more samples reduces the noise level, but one will miss the faster 
changes in voltage or current.
Depending on your project needs you can choose one over the other.

As a rule of thumb one could take the time between two I2C reads of 
a register as an upper limit.
This would result in a fresh measurement every time one reads the register. 
NB it is always possible to average readings fetched from the device
in your own code.

Use one of these three so set **bus** resolution and sampling.

- **bool setBusResolution(uint8_t bits)** bits = 9..12, always 1 sample.
Returns false if parameter out of range.
Returns false if it could not write settings to device.
- **bool setBusSamples(uint8_t value)** value = 0..7 => maps to 2^value samples.
Always 12 bits.
Returns false if parameter out of range.
Returns false if it could not write settings to device.
- **bool setBusADC(uint8_t mask = 0x03)** see table below. 
Check datasheet for all details.
Returns false if parameter out of range (mask > 0x0F).
Returns false if it could not write settings to device.
- **uint8_t getBusADC()** returns mask, see table below.


Use one of these three so set **shunt** resolution and sampling.

- **bool setShuntResolution(uint8_t bits)** bits = 9..12, always 1 sample.
Returns false if parameter out of range.
Returns false if it could not write settings to device.
- **bool setShuntSamples(uint8_t value)** value = 0..7 => maps to 2^value samples.
Always 12 bits.
Returns false if parameter out of range.
Returns false if it could not write settings to device.
- **bool setShuntADC(uint8_t mask = 0x03)** see table below. 
Check datasheet for all details.
Returns false if parameter out of range (mask > 0x0F).
Returns false if it could not write settings to device.
- **uint8_t getShuntADC()** returns mask, see table below.


#### Resolution samples table

mask = both resolution + averaging multiple samples.
minus - == don't care


|  bit mask  |  value  |  resolution  |  samples      | conversion time |
|:----------:|:-------:|:-------------|:--------------|:---------------:|
|    0-00    |  0 / 4  |     9 bit    |    1 sample   |      84 μs      |
|    0-01    |  1 / 5  |    10 bit    |    1 sample   |     148 μs      |
|    0-10    |  2 / 6  |    11 bit    |    1 sample   |     276 μs      |
|    0-11    |  3 / 7  |    12 bit    |    1 sample   |     532 μs      |
|            |         |              |               |                 |
|    1000    |    8    |    12 bit    |    1 sample   |     532 μs      |
|    1001    |    9    |    12 bit    |    2 samples  |    1.06 ms      |
|    1010    |   10    |    12 bit    |    4 samples  |    2.13 ms      |
|    1011    |   11    |    12 bit    |    8 samples  |    4.26 ms      |
|    1100    |   12    |    12 bit    |   16 samples  |    8.51 ms      |
|    1101    |   13    |    12 bit    |   32 samples  |   17.02 ms      |
|    1110    |   14    |    12 bit    |   64 samples  |   34.05 ms      |
|    1111    |   15    |    12 bit    |  128 samples  |   68.10 ms      |

- note that a new value set can substantially increase the conversion time.
- note that you cannot set e.g. 9 bits and 16 samples.
- note that there are 3 ways to set 12 bits 1 sample.


#### Operating mode

See details datasheet,

- **bool setMode(uint8_t mode = 7)** mode = 0..7.
The default value 7 == ShuntBusContinuous mode.
Returns false if parameter out of range (mode > 7).
Returns false if it could not write settings to device.
- **uint8_t getMode()** returns the mode (0..7) set.

Descriptive mode functions (convenience wrappers around **setMode()**).

- **bool shutDown()** mode 0
- **bool setModeShuntTrigger()** mode 1 - how to trigger to be investigated.
- **bool setModeBusTrigger()** mode 2
- **bool setModeShuntBusTrigger()** mode 3
- **bool setModeADCOff()** mode 4
- **bool setModeShuntContinuous()** mode 5
- **bool setModeBusContinuous()** mode 6
- **bool setModeShuntBusContinuous()** mode 7 - default


#### Calibration

See datasheet.

Calibration is mandatory to get **getCurrent()** and **getPower()** to work.

- **bool setMaxCurrentShunt(float ampere = 20.0, float ohm = 0.002)** 
set the calibration register based upon the shunt and the max ampere. 
From this the LSB is derived. 
Note the function will round up the LSB to nearest round value by default. 
This may cause loss of precision. The function may force normalization if underflow detected.
The user **must** check the return value == true, otherwise the calibration register is **not** set.
Returns false if parameter out of range.
Returns false if it could not write settings to device.
- **bool isCalibrated()** returns true if CurrentLSB has been calculated by **setMaxCurrentShunt()**. 
- **float getCurrentLSB()** returns the LSB in Ampere == precision of the calibration.
- **float getCurrentLSB_mA()** returns the LSB in milliAmpere.
- **float getCurrentLSB_uA()** returns the LSB in microAmpere.
- **float getShunt()** returns the value set for the shunt in Ohm.
- **float getMaxCurrent()** returns the value for the maxCurrent which can be corrected.

To print these values one might use https://github.com/RobTillaart/printHelpers 
to get the values in scientific notation like "3.5e-6"


#### Debugging

- **uint16_t getRegister(uint8_t reg)** fetch values from registers directly.
Meant for debugging only, reg = 0..5. Check datasheet for the details.

|  reg  |  description    |  RW  |
|:-----:|:----------------|:----:|
|   0   |  configuration  |  RW  |
|   1   |  shunt voltage  |  R   |
|   2   |  bus voltage    |  R   |
|   3   |  power          |  R   |
|   4   |  current        |  R   |
|   5   |  calibration    |  RW  |


## Future

#### Must

- find time to test more
  - test different loads
  - all functions.
- update documentation


#### Should

- sync INA226 where meaningful
- improve error handling
  - low level I2C, readRegister() +  writeRegister()
  - other? parameters
- create unit tests
- test performance
  - verify conversion time
- write and verify examples
- add a **setCurrentLSB(uint16_t mA)** function ?
  - maxAmpere as derived value
- disconnected load.
  - can it be recognized? => current drop?

#### Could

- clean up magic numbers in the code
- calibration
  - autocorrect \_current_LSB  round number
  - maxCurrent? how much?
  - can the calibration math be optimized
    - integer only?
    - less iterations?
    - local var for current_lsb?
    - does this matter as it is often a one time action?

- cache configuration ? ==> 2 bytes
  - what is gained? both getting and setting is faster.
    a few milliseconds per call?
  - about a dozen times used,
  - flag for forced read in functions **setMode(uint8_t mode, bool forced = false)**
- create defines for several masks / magic numbers


#### Wont

- initial current 20A and shunt 0.002 Ω in **begin()**
  - can't be sure so user is responsible


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

