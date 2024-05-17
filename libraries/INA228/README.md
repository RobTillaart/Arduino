
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

This library controls the INA228, a device that measures voltage,
current, power, temperature and more.

The INA228 sensor differs from the better known INA226.
Most important difference is that the INA228 has a 20 bit ADC.
This should result in higher precision however this is expected to only
be visible with stable loads and low noise.
Another important difference is that the INA228 works up to 85 Volts,
which is more than twice the 36 volt of the INA226.
The INA228 has a build in temperature sensor (±1°C) to be used for
monitoring and temperature compensation.
Finally the INA228 has an **energy** and **charge** register.
These are values accumulated over time, and only work in continuous mode.
(to be investigated what those mean ).

The INA provides also provides an alert line, to generate an interrupt
in case a predefined threshold has been met.
This can be an under- or over-voltage, temperature or power limit.

The library is **not** tested and verified with hardware yet.

==> **USE WITH CARE**

Feedback as always is welcome.

The INA228 is a voltage, current and power measurement device.
A few important data, see datasheet.

|  description   |  value      |  notes  |
|:---------------|:-----------:|:--------|
|  bus voltage   |  85 Volt    |  unclear for how long.
|  shunt voltage |  ?? mVolt   |
|  current       |  10 Ampere  |  DC only
|  ADC           |  20 bit     |
|  alert timing  |  75 µs.     |

Read the datasheet for the details, Section 7, Page 12++.


#### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)
- ° == degree = ALT-0176 (Windows)
- ± == plus minus = ALT-177 (Windows)


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

See table - from datasheet table 7-2, page 19.

|  A1   |  A0   |  Addr  |  HEX   |
|:-----:|:-----:|:------:|:------:|
|  GND  |  GND  |   64   |  0x40  |
|  GND  |  VS   |   65   |  0x41  |
|  GND  |  SDA  |   66   |  0x42  |
|  GND  |  SCL  |   67   |  0x43  |
|  VS   |  GND  |   68   |  0x44  |
|  VS   |  VS   |   69   |  0x45  |
|  VS   |  SDA  |   70   |  0x46  |
|  VS   |  SCL  |   71   |  0x47  |
|  SDA  |  GND  |   72   |  0x48  |
|  SDA  |  VS   |   73   |  0x49  |
|  SDA  |  SDA  |   74   |  0x4A  |
|  SDA  |  SCL  |   75   |  0x4B  |
|  SCL  |  GND  |   76   |  0x4C  |
|  SCL  |  VS   |   77   |  0x4D  |
|  SCL  |  SDA  |   78   |  0x4E  |
|  SCL  |  SCL  |   79   |  0x4F  |


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

The **getEnergy()** and **getCharge()** only have meaning in continuous
mode. See page 13++.

The library has helper functions to convert above output to a more
appropriate scale of units.

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

Read datasheet for details, section 7.6.1.1, page 22

- **void reset()**
- **bool setAccumulation(uint8_t value)** value: 0 == normal operation,  1 = clear registers
- **bool getAccumulation()** return set value.
- **void setConversionDelay(uint8_t steps)**  Conversion delay in 0..255 steps of 2 ms
- **uint8_t getConversionDelay()** return set value.
- **void setTemperatureCompensation(bool on)**
- **bool getTemperatureCompensation()** return set value.
- **void setADCRange(bool flag)** flag = false => 164 mV, true => 41 mV
- **bool getADCRange()** return set value.

#### Configuration ADC

Read datasheet for details, section 7.6.1.2, page 22++

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

To elaborate, read datasheet for details.

- **int setMaxCurrentShunt(float maxCurrent, float shunt)**
- **bool isCalibrated()** is valid calibration value.
- **float getMaxCurrent()** return set value.
- **float getShunt()** return set value.


#### Shunt temperature coefficient

Read datasheet for details, page 16.

The INA228 can compensate for shunt temperature variance to increase accuracy.
The reference temperature is 25°C.
- Enter the coefficient with **setShuntTemperatureCoefficent(uint16_t ppm)**.
- Enable the function with **setTemperatureCompensation(true)**.

In formula:
```
Radjusted = Rnominal + (Rnominal x (temperature - 25) x PPM) * 10e-6;
```

- **bool setShuntTemperatureCoefficent(uint16_t ppm = 0)** ppm = 0..16383 ppm/°C.
Default 0 for easy reset.
- **uint16_t getShuntTemperatureCoefficent()** return set value.


#### Diagnose alert

Read datasheet for details, section 7.6.1.12, page 26++.

- **void setDiagnoseAlert(uint16_t flags)** set all flags as bit mask.
- **uint16_t getDiagnoseAlert()** return all flags as bit mask.

INA228.h has an enum for the bit fields.

- **void setDiagnoseAlertBit(uint8_t bit)** set individual bit.
- **void clrDiagnoseAlertBit(uint8_t bit)** clear individual bit.
- **uint16_t getDiagnoseAlertBit(uint8_t bit)** return individual bit.


#### Threshold and Limits

Read datasheet for details, section 7.3.7, page 16++

- **void setShuntOvervoltageTH(uint16_t threshold)**
- **uint16_t getShuntOvervoltageTH()**
- **void setShuntUndervoltageTH(uint16_t threshold)**
- **uint16_t getShuntUndervoltageTH()**
- **void setBusOvervoltageTH(uint16_t threshold)**
- **uint16_t getBusOvervoltageTH()**
- **void setBusUndervoltageTH(uint16_t threshold)**
- **uint16_t getBusUndervoltageTH()**
- **void setTemperatureOverLimitTH(uint16_t threshold)**
- **uint16_t getTemperatureOverLimitTH()**
- **void setPowerOverLimitTH(uint16_t threshold)**
- **uint16_t getPowerOverLimitTH()**


#### Manufacturer and ID

- **bool getManufacturer()** Returns 0x5449, can be used to check right sensor.
- **uint16_t getDieID()** Returns 0x228, can be used to check right sensor.
- **uint16_t getRevision()** Returns revision, probably 0x01.


## Future


#### Must

- get hardware.
- test and verify.


#### Should

- update documentation.
- write examples, (please share yours).
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

