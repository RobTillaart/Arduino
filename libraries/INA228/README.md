
[![Arduino CI](https://github.com/RobTillaart/INA228/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA228/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA228/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA228/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA228/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA228.svg)](https://github.com/RobTillaart/INA228/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA228/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA228.svg?maxAge=3600)](https://github.com/RobTillaart/INA228/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA228.svg)](https://registry.platformio.org/libraries/robtillaart/INA228)


# INA228

Arduino library for the INA228 power sensor.


## Description

**Experimental** 

The library for the INA228 power sensor differs from the better 
known INA226 in that it has a 20 bit ADC.
This should result in higher precision however this is expected to only 
be visible with stable loads and low noise. 
Another important difference is that the INA228 works up to 85 Volts,
which is more than twice the 36 volt of the INA226.

The initial release 0.1.0 is **not** tested verified with hardware yet.
Furthermore not all functionality is implemented, especially the diagnose
alert, threshold and limits.

Feedback as always is welcome.

Read datasheet for details.

==> **USE WITH CARE**

The INA228 is a voltage, current and power measurement device. 
A few important maxima, see datasheet.

|  description  |  max  |  unit  | notes |
|:--------------|------:|-------:|:------|
| bus voltage   |  85   | Volt   |  unclear for how long.
| shunt voltage |  ??   | mVolt  |
| current       |  10   | Ampere |  DC only


#### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)


#### Related

- https://www.ti.com/product/INA228#tech-docs
- https://www.ti.com/product/INA228#params
- https://www.ti.com/document-viewer/INA228/datasheet
- https://github.com/RobTillaart/INA219
- https://github.com/RobTillaart/INA226
- https://github.com/RobTillaart/INA228
- https://github.com/RobTillaart/INA3221_RT


## I2C

#### Address

The sensor can have 16 different I2C addresses, 
which depends on how the A0 and A1 address lines 
are connected to the SCL, SDA, GND and VCC pins.

See table - from datasheet table 2, page18.

|  A1   |  A0   |  ADDRESS   |
|:-----:|:-----:|:----------:|
|  GND  |  GND  |  1000000   |
|  GND  |  VS   |  1000001   |
|  GND  |  SDA  |  1000010   |
|  GND  |  SCL  |  1000011   |
|  VS   |  GND  |  1000100   |
|  VS   |  VS   |  1000101   |
|  VS   |  SDA  |  1000110   |
|  VS   |  SCL  |  1000111   |
|  SDA  |  GND  |  1001000   |
|  SDA  |  VS   |  1001001   |
|  SDA  |  SDA  |  1001010   |
|  SDA  |  SCL  |  1001011   |
|  SCL  |  GND  |  1001100   |
|  SCL  |  VS   |  1001101   |
|  SCL  |  SDA  |  1001110   |
|  SCL  |  SCL  |  1001111   |


#### Performance

To be elaborated, 


## Interface

```cpp
#include "INA228.h"
```


#### Constructor

- **INA228(const uint8_t address, TwoWire \*wire = Wire)** Constructor to set 
the address and optional Wire interface.
- **bool begin()** initializes the class.
returns true if the INA228 address is on the I2C bus.
Note: one needs to set **Wire.begin()** before calling **begin()**.
- **bool isConnected()** returns true if the INA228 address is on the I2C bus.
- **uint8_t getAddress()** returns the address set in the constructor.


#### Core Functions

Note the power and the current are not meaningful without calibrating the sensor.
Also the value is not meaningful if there is no shunt connected.

- **float getShuntVoltage()** idem, in volts.
- **float getBusVoltage()** idem. in volts. Max 36 Volt.
- **float getCurrent()** is the current through the shunt in Ampere.
- **float getPower()** is the current x BusVoltage in Watt.
- **float getEnergy()** return Joule (elaborate).
- **float getCharge()** return Coulomb (elaborate).

The library has helper functions to convert above output to a more appropriate scale of units.

Helper functions for the milli scale.

- **float getBusVoltage_mV()** idem, in milliVolts.
- **float getShuntVoltage_mV()** idem, in milliVolts.
- **float getCurrent_mA()** idem, in milliAmpere.
- **float getPower_mW()** idem, in milliWatt.
- **float getEnergy_mJ()** idem, milliJoule.
- **float getCharge_mC()** idem, milliCoulomb.

Helper functions for the micro scale.

- **float getBusVoltage_uV()** idem, in microVolts.
- **float getShuntVoltage_uV()** idem, in microVolts.
- **float getCurrent_uA()** idem, in microAmpere.
- **float getPower_uW()** idem, in microWatt.
- **float getEnergy_uJ()** idem, microJoule.
- **float getCharge_uC()** idem, microCoulomb.


#### Configuration

to elaborate

- **void reset()**
- **bool setAccumulation(uint8_t val)** val: 0 == normal operation,  1 = clear registers
- **bool getAccumulation()** return set value.
- **void setConversionDelay(uint8_t steps)**  Conversion delay in 0..255 steps of 2 ms
- **uint8_t getConversionDelay()** return set value.
- **void setTemperatureCompensation(bool on)**
- **bool getTemperatureCompensation()** return set value.
- **void setADCRange(bool flag)** flag = false => 164 mV, true => 41 mV
- **bool getADCRange()** return set value.

#### Configuration ADC

to elaborate

- **bool setMode(uint8_t mode = INA228_MODE_CONT_TEMP_BUS_SHUNT)**
- **uint8_t getMode()** return set value.

|  MODE                           |  value  |  notes  |
|:-------------------------------:|:-------:|:--------|
| INA228_MODE_SHUTDOWN            |   0x00  |
| INA228_MODE_TRIG_BUS            |   0x01  |
| INA228_MODE_TRIG_SHUNT          |   0x02  |
| INA228_MODE_TRIG_BUS_SHUNT      |   0x03  |
| INA228_MODE_TRIG_TEMP           |   0x04  |
| INA228_MODE_TRIG_TEMP_BUS       |   0x05  |
| INA228_MODE_TRIG_TEMP_SHUNT     |   0x06  |
| INA228_MODE_TRIG_TEMP_BUS_SHUNT |   0x07  |
| INA228_MODE_SHUTDOWN2           |   0x08  |
| INA228_MODE_CONT_BUS            |   0x09  |
| INA228_MODE_CONT_SHUNT          |   0x0A  |
| INA228_MODE_CONT_BUS_SHUNT      |   0x0B  |
| INA228_MODE_CONT_TEMP           |   0x0C  |
| INA228_MODE_CONT_TEMP_BUS       |   0x0D  |
| INA228_MODE_CONT_TEMP_SHUNT     |   0x0E  |
| INA228_MODE_CONT_TEMP_BUS_SHUNT |   0x0F  |

- **bool setBusVoltageConversionTime(uint8_t bvct = INA226_1052_us)**
- **uint8_t getBusVoltageConversionTime()** return set value.
- **bool setShuntVoltageConversionTime(uint8_t svct = INA226_1052_us)**
- **uint8_t getShuntVoltageConversionTime()** return set value.
- **bool setTemperatureConversionTime(uint8_t tct = INA226_1052_us)**
- **uint8_t getTemperatureConversionTime()** return set value.

|  TIMING             |  value  |  notes  |
|:-------------------:|:-------:|:--------|
| INA228_50_us        |    0    |
| INA228_84_us        |    1    |
| INA228_150_us       |    2    |
| INA228_280_us       |    3    |
| INA228_540_us       |    4    |
| INA228_1052_us      |    5    |
| INA228_2074_us      |    6    |
| INA228_4120_us      |    7    |


- **bool setAverage(uint8_t avg = INA228_1_SAMPLE)**
- **uint8_t getAverage()** return set value.

|  AVERAGE            |  value  |  notes  |
|:-------------------:|:-------:|:--------|
| INA228_1_SAMPLE     |    0    |
| INA228_4_SAMPLES    |    1    |
| INA228_16_SAMPLES   |    2    |
| INA228_64_SAMPLES   |    3    |
| INA228_128_SAMPLES  |    4    |
| INA228_256_SAMPLES  |    5    |
| INA228_512_SAMPLES  |    6    |
| INA228_1024_SAMPLES |    7    |


#### Shunt Calibration

To elaborate

- **int setMaxCurrentShunt(float maxCurrent, float shunt)**
- **bool isCalibrated()** is valid calibration value.
- **float getMaxCurrent()** return set value
- **float getShunt()** return set value


#### Shunt temperature coefficient

To elaborate

- **bool setShuntTemperatureCoefficent(uint16_t ppm = 0)** ppm = 0..16383.
- **uint16_t getShuntTemperatureCoefficent()** return set value.


#### Diagnose alert

TODO


#### Threshold and Limits

TODO


#### Manufacturer and ID

- **bool getManufacturer()** Returns 0x5449, can be used to check right sensor.
- **uint16_t getDieID()** Returns 0x228, can be used to check right sensor.
- **uint16_t getRevision()** Returns revision, probably 0x01.


## Future


#### Must

- get hardware, test and verify.
- update documentation.
- update functionality.
  - diagnose, thresholds limits


#### Should

- write examples.
- keep in sync with INA226 where possible.


#### Could

- improve unit tests
- clean up magic numbers in the code

#### Won't

- cache registers for performance 
  - first get library working / tested.
  - reset should reread all cached values...


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

