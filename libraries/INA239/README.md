
[![Arduino CI](https://github.com/RobTillaart/INA239/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA239/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA239/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA239/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA239/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA239.svg)](https://github.com/RobTillaart/INA239/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA239/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA239.svg?maxAge=3600)](https://github.com/RobTillaart/INA239/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA239.svg)](https://registry.platformio.org/libraries/robtillaart/INA239)


# INA239

Arduino library for the INA239, SPI, 16 bit, voltage, current and power sensor.


## Description

**Experimental**

This library controls the INA239, a device that measures voltage,
current, power, and temperature.

The library is not tested with hardware yet, feedback welcome.

The library is written to be able to use the faster SPI interface which
might be needed (faster than I2C which is used by many other INA devices.).

The INA239 sensor uses a 16 bit ADC.

An important difference with the well known INA226 is that the INA239
works up to 85 Volts, which is more than twice the 36 volt of the INA226.
The INA239 has a build in temperature sensor (±1°C) to be used for
monitoring and temperature compensation.

The INA239 also provides an ALERT line, to generate an interrupt
in case a predefined threshold has been met.
This can be an under- or over-voltage, temperature or power limit.
The library does not handle these interrupts.

The code is based upon my INA228 library which uses the same registers
(plus 3 more) and has a I2C interface.
The 239 uses 16 bit where the 228 uses a 20 bit ADC.
This means most constants in the formulas are slightly different.

==> **USE WITH CARE**

Feedback as always is welcome.


### Update 0.4.0

In 0.4.0 bugs were fixed in getBusVoltage() and in getTemperature();
All float constants now have f-suffix added to prevent interpreting 
them as double.
Added is direct register access.
Added **INA.setBusVoltageLSB(lsb)** and **INA.setVoltageRatio(ratio)**
to adjust VBUS and POWER when using a voltage divider.

All pre 0.4.0 versions are obsolete.


### Update 0.2.0

In 0.2.0 a bug was fixed in software SPI, so all 0.1.x versions
are now obsolete (although HW SPI did work).


### Details

The INA239 is a voltage, current and power measurement device.
A few important data, Read the datasheet for the details,
Section 7, Page 12++.


|  description   |  value      |  notes  |
|:---------------|:-----------:|:--------|
|  bus voltage   |  85 Volt    |  unclear for how long.
|  ADC           |  16 bit     |
|  alert timing  |  75 µs.     |


No breakout boards are known.


### Calibrating

Note the power and the current are not meaningful without calibrating the sensor.
Also the values are not meaningful if there is no shunt connected.


### Schema LOW SIDE


```
         GND                         Voltage
          |                             |
          |                             |
          +--[SHUNT]---+----[ LOAD ]----+
          |            |                |
          |            |                |
      /-------------------------------------\
      |  VIN-         VIN+             VBUS |
      |                                     |
      |                                     |
      |          INA239 BREAKOUT            |
      |                                     |
      |                                     |
      \-------------------------------------/

```

Verified to work in #13, more feedback welcome.


### Schema HIGH SIDE


```
         GND                         Voltage
          |                             |
          |                             |
          +--[ LOAD ]--+--[SHUNT]--+----+
                       |           |    |
                       |           |    |
      /-------------------------------------\
      |               VIN-       VIN+  VBUS |
      |                                     |
      |                                     |
      |          INA239 BREAKOUT            |
      |                                     |
      |                                     |
      \-------------------------------------/

```

Verified to work in #13, more feedback welcome.


### Schema voltage divider

Since 0.4.0 - experimental, use carefully, feedback welcome.

To measure a bus voltage higher than the 85 Volt maximum limit, 
use a voltage divider connected to the VBUS pin.
A voltage divider can also be used when measuring around the limit and 
one wants a safety margin for (un)expected spikes.
Make sure that the voltage divider drops the maximum voltage enough
under the 85 Volt limit so the INA239 can handle it.

Note a voltage divider also affects the power reported.

One must use the **LOW SIDE mode**, as one does not want to have
the high voltage (e.g. 120 Volt) to the VIN+ and VIN- pins.


```
         GND                            Voltage
          |                                |
          |                                |
          +---[SHUNT]---+-----[ LOAD ]-----+
          |             |                  |
          |             |                  |
          |             |        +---[R1---+
          |             |        |
          |             |        |
          |             |        +---[R2]-------GND
          |             |        |
          |             |        |
      /-------------------------------------\
      |  VIN-          VIN+     VBUS        |
      |                                     |
      |                                     |
      |          INA239 BREAKOUT            |
      |                                     |
      |                                     |
      \-------------------------------------/

```

The ratio becomes (R1 + R2) / R2.

Example, the high voltage is maximum 120 Volt.
This must be mapped upon e.g. 80 Volts so the INA239 still has a 5 Volt margin.
So the ratio needed is 120 / 80 ==> 1.5.

By choosing R1 = 100 kΩ and R2 200 kΩ, the factor = (100+200)/200 = 1.5.
The new BusVoltageLSB becomes 1.5 x 3.125e-3f = 4.6875e-3f.
Calling **INA.setBusVoltageLSB(4.6875e-3f)** or **INA.setVoltageRatio(1.5)** 
will now return the corrected getBusVoltage() and getPower() for the given
voltage divider.

Use precision resistors and verify them with a DMM to get the best results. 
E.g. if the resistors were 201 kΩ and 99 kΩ, the ratio would become 300 / 201
= 1.49254 and the LSB would be 1.49254 x 3.125e-3f = 4.6642e-3f.

To reset to factory defaults, call **INA.setBusVoltageLSB()** or **INA.setVoltageRatio()**.

Note that measuring the voltage between GND and VBUS with a DMM will
give the uncorrected voltage


### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)
- ° == degree = ALT-0176 (Windows)
- ± == plus minus = ALT-0177 (Windows)


### Related

- https://www.ti.com/product/INA239#tech-docs
- https://www.ti.com/product/INA239#params
- https://www.ti.com/document-viewer/INA239/datasheet
- https://github.com/RobTillaart/INA219  26 Volt, I2C, 12 bit
- https://github.com/RobTillaart/INA226  36 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA228  85 Volt, I2C, 20 bit
- https://github.com/RobTillaart/INA229  85 Volt, SPI, 20 bit
- https://github.com/RobTillaart/INA236  48 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA238  85 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA239  85 Volt, SPI, 16 bit
- https://github.com/RobTillaart/INA260  36 Volt, SPI, 16 bit
- https://github.com/RobTillaart/INA3221_RT  26 Volt, I2C, 13 bits (3 channel)
- https://www.adafruit.com/product/5832
- https://www.mateksys.com/?portfolio=i2c-ina-bm
- https://github.com/RobTillaart/printHelpers  (for scientific notation)


### Performance

Run **INA239_performance.ino** sketch to get a first indication.
Numbers below are based upon tests with no board.

Time in micros, SPI speed in MHz.

|  SPI  |  function         |  time  |  notes  |
|:-----:|:------------------|:------:|:-------:|
|  1.0  |  getBusVoltage    |   56   |  100%
|  1.0  |  getShuntVoltage  |  100   |
|  1.0  |  getCurrent       |   52   |
|  1.0  |  getPower         |   68   |
|  1.0  |  getTemperature   |   52   |
|       |                   |        |  other functions similar gain.
|  2.0  |  getBusVoltage    |   44   |
|  4.0  |  getBusVoltage    |   40   |
|  8.0  |  getBusVoltage    |   32   |


Most non core functions are as fast as **getTemperature()**


## Interface

```cpp
#include "INA239.h"
```

### Constructor

- **INA239(uint8_t select, __SPI_CLASS__ \* mySPI = &SPI)** Constructor HARDWARE SPI
- **INA239(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)**
Constructor SOFTWARE SPI
- **bool begin()** initializes the class.

### BUS VOLTAGE

Main function + wrappers.

- **float getBusVoltage()** idem. Returns value in volts. Max 85 Volt.
This value is always positive.
- **float getBusVolt()**
- **float getBusMilliVolt()**
- **float getBusMicroVolt()**

### SHUNT VOLTAGE

- **float getShuntVoltage()** idem, Returns value in volts.
Note the value can be positive or negative as the INA239 is bidirectional.
- **float getShuntVolt()**
- **float getShuntMilliVolt()**
- **float getShuntMicroVolt()**

### SHUNT CURRENT

- **float getCurrent()** returns the current through the shunt in Ampere.
Note this value can be positive or negative as the INA239 is bidirectional.
- **float getAmpere()** idem
- **float getMilliAmpere()** idem
- **float getMicroAmpere()** idem

### TEMPERATURE

- **float getTemperature()** returns the temperature in Celsius.

### POWER

- **float getPower()** returns the current x BusVoltage in Watt.
- **float getWatt()** idem
- **float getMilliWatt()** idem
- **float getMicroWatt()** idem
- **float getKiloWatt()** idem


### Configuration busVoltageLSB

New since 0.4.0, use with care.

This configuration is only needed if one wants to monitor a voltage above the
85 Volt limit of the INA239. See "Schema voltage divider" section above.

There are two ways to define the busVoltageLSB, one is direct, the other is 
based upon the scaling needed from Vmax to 85 Volt, or a bit lower to be safe.
You need to call only one of these two in setup() to adjust for the voltage divider.

- **void setBusVoltageLSB(float LSB = 3.125e-3f)** set a different LSB to calculate 
the VBUS voltage. The default 3.125e-3f is the factory default;
- **float getBusVoltageLSB()** returns current voltage LSB. For convenience.
- **void setVoltageRatio(float ratio = 1.0f)** set the voltage ratio to calculate 
the VBUS voltage. 
Default is 1.0f, indicating no adjustment / correction on the factory default.
- **float getVoltageRatio()** - return set ratio.

Note: these functions could also be used to adjust the LSB, 
e.g. to match voltages reported your DMM. 
E.g. call **INA.setBusVoltageLSB(3.128e-3f)** or **INA.setVoltageRatio(0.998f)**

Note: the BUS over- and underVoltage functions do not use the BUS LSB yet.
The user has to do the math here e.g. by using **getVoltageLSB()**.


### Configuration

Read datasheet for details, section 7.6.1.1, page 20

- **void reset()** Resets the device, be aware that you need to calibrate the sensor
(shunt register) again ==> call **setMaxCurrentShunt()** and more.
- **void setConversionDelay(uint8_t steps)**  Conversion delay in 0..255 steps of 2 ms
- **uint8_t getConversionDelay()** return set value.
- **bool setADCRange(bool flag)** flag = false => 164 mV, true => 41 mV
Since 0.2.1 setADCRange() calls setMaxCurrentShunt() to update the internal LSB values.
Returns false on failure of setMaxCurrentShunt().
- **bool getADCRange()** return set value.


### ADC mode

Read datasheet for details, section 7.6.1.2, page 20++

- **bool setMode(uint8_t mode = INA239_MODE_CONT_TEMP_BUS_SHUNT)** default all on.
- **uint8_t getMode()** return set value.

|  MODE                           |  value  |  notes  |
|:--------------------------------|:-------:|:--------|
| INA239_MODE_SHUTDOWN            |   0x00  |  See 0x08.
| INA239_MODE_TRIG_BUS            |   0x01  |
| INA239_MODE_TRIG_SHUNT          |   0x02  |
| INA239_MODE_TRIG_BUS_SHUNT      |   0x03  |
| INA239_MODE_TRIG_TEMP           |   0x04  |
| INA239_MODE_TRIG_TEMP_BUS       |   0x05  |
| INA239_MODE_TRIG_TEMP_SHUNT     |   0x06  |
| INA239_MODE_TRIG_TEMP_BUS_SHUNT |   0x07  |
| INA239_MODE_SHUTDOWN2           |   0x08  |  There are two shutdowns.
| INA239_MODE_CONT_BUS            |   0x09  |
| INA239_MODE_CONT_SHUNT          |   0x0A  |
| INA239_MODE_CONT_BUS_SHUNT      |   0x0B  |
| INA239_MODE_CONT_TEMP           |   0x0C  |
| INA239_MODE_CONT_TEMP_BUS       |   0x0D  |
| INA239_MODE_CONT_TEMP_SHUNT     |   0x0E  |
| INA239_MODE_CONT_TEMP_BUS_SHUNT |   0x0F  |


### ADC conversion time

- **bool setBusVoltageConversionTime(uint8_t bvct = INA239_1052_us)**
- **uint8_t getBusVoltageConversionTime()** return set value.
- **bool setShuntVoltageConversionTime(uint8_t svct = INA239_1052_us)**
- **uint8_t getShuntVoltageConversionTime()** return set value.
- **bool setTemperatureConversionTime(uint8_t tct = INA239_1052_us)**
- **uint8_t getTemperatureConversionTime()** return set value.

|  TIMING             |  value  |  notes  |
|:--------------------|:-------:|:--------|
| INA239_50_us        |    0    |
| INA239_84_us        |    1    |
| INA239_150_us       |    2    |
| INA239_280_us       |    3    |
| INA239_540_us       |    4    |
| INA239_1052_us      |    5    |
| INA239_2074_us      |    6    |
| INA239_4120_us      |    7    |


- **bool setAverage(uint8_t avg = INA239_1_SAMPLE)**
- **uint8_t getAverage()** return set value.

|  AVERAGE            |  value  |  notes  |
|:--------------------|:-------:|:--------|
| INA239_1_SAMPLE     |    0    |
| INA239_4_SAMPLES    |    1    |
| INA239_16_SAMPLES   |    2    |
| INA239_64_SAMPLES   |    3    |
| INA239_128_SAMPLES  |    4    |
| INA239_256_SAMPLES  |    5    |
| INA239_512_SAMPLES  |    6    |
| INA239_1024_SAMPLES |    7    |


### Shunt Calibration

To elaborate, read datasheet for details.

Note: **setMaxCurrentShunt()** must be called to calibrate your sensor.
Otherwise several functions will return zero or incorrect data.

- **int setMaxCurrentShunt(float maxCurrent, float shunt)** The maxCurrent
depends on breakout used, See section above.
The shunt should be 0.0001 Ω and up.
  - returns 0 if OK.
  - returns -2 if shunt < 0.0001 Ohm.
- **bool isCalibrated()** is valid calibration value. The currentLSB > 0.
- **float getMaxCurrent()** return set value.
- **float getShunt()** return set value.
- **float getCurrentLSB()** return actual currenLSB. 0.0 means not calibrated.
- **float getCurrentLSB_mA()** returns the LSB in milliAmpere.
- **float getCurrentLSB_uA()** returns the LSB in microAmpere.

### Diagnose alert

Read datasheet for details, section 7.6.1.9, page 23++.

- **void setDiagnoseAlert(uint16_t flags)** set all flags as bit mask.
- **uint16_t getDiagnoseAlert()** return all flags as bit mask.

INA239.h has an enum for the bit fields.

- **void setDiagnoseAlertBit(uint8_t bit)** set individual bit.
- **void clearDiagnoseAlertBit(uint8_t bit)** clear individual bit.
- **uint16_t getDiagnoseAlertBit(uint8_t bit)** return individual bit.


### Threshold and Limits

Read datasheet for details, section 7.6.1.10-15, page 23++

Note: the implementation of this part is rather minimalistic and
might be changed / extended in the future.
Currently it are just wrappers around the registers.

#### Shunt

- **void setShuntOvervoltageTH(uint16_t threshold)**
- **uint16_t getShuntOvervoltageTH()**
- **void setShuntUndervoltageTH(uint16_t threshold)**
- **uint16_t getShuntUndervoltageTH()**

#### Bus

- **void setBusOvervoltageTH(uint16_t threshold)**
- **uint16_t getBusOvervoltageTH()**
- **void setBusUndervoltageTH(uint16_t threshold)**
- **uint16_t getBusUndervoltageTH()**

#### Temperature

- **void setTemperatureOverLimitTH(uint16_t threshold)**
- **uint16_t getTemperatureOverLimitTH()**

#### Power

- **void setPowerOverLimitTH(uint16_t threshold)**
- **uint16_t getPowerOverLimitTH()**


### Manufacturer and ID

- **bool getManufacturer()** Returns 0x5449, can be used to check right sensor.
- **uint16_t getDieID()** Returns 0x228, can be used to check right sensor.
- **uint16_t getRevision()** Returns revision, probably 0x01.


## Future


#### Must

- update documentation.
  - remove INA228 sections,

#### Should

- Fix TODO's in code and docs.
- redo API threshold and limit registers 12-17 (check verify)
- add error handling.
  - codes
- keep in sync with INA228 / INA229 where possible
- add examples
  - to show the effect of the ADC configuration.

#### Could

- getBusVoltageLSB() for completeness?
- getVoltageRatio() for completeness?

#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

