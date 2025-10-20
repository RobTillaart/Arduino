
[![Arduino CI](https://github.com/RobTillaart/INA229/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA229/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA229/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA229/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA229/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA229.svg)](https://github.com/RobTillaart/INA229/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA229/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA229.svg?maxAge=3600)](https://github.com/RobTillaart/INA229/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA229.svg)](https://registry.platformio.org/libraries/robtillaart/INA229)


# INA229

Arduino library for the INA229, SPI, 20 bit, voltage, current and power sensor.


## Description

**Experimental**

This library controls the INA229, a device that measures voltage,
current, power, temperature and more.

The library is confirmed to work, still feedback is welcome.

The library is written to be able to use the faster SPI interface which
might be needed (faster than I2C which is used by many other INA devices.).

The INA229 sensor uses a 20 bit ADC.

An important difference with the well known INA226 is that the INA229
works up to 85 Volts, which is more than twice the 36 volt of the INA226.
The INA229 has a build in temperature sensor (±1°C) to be used for
monitoring and temperature compensation.

The INA229 also provides an ALERT line, to generate an interrupt
in case a predefined threshold has been met.
This can be an under- or over-voltage, temperature or power limit.
The library does not handle these interrupts.

The code is based upon my INA228 (functional equivalent 20 bit but I2C) 
and my INA239 (SPI interface) libraries. So there might be some loose
ends in the code, please report them.


==> **USE WITH CARE**

Feedback as always is welcome.


### Breaking change 0.4.0

The function **getCharge()** is updated as the value can be negative too.
The previous versions assumed it could only be positive. See #8.
0.4.0 fixed the **getEnergy()** which only can have positive values
and was broken in 0.3.0. Versions before 0.4.0 are obsolete now.


### Update 0.2.0

In 0.2.0 a bug was fixed in software SPI, so all 0.1.x versions
are now obsolete (although HW SPI did work).


### Details

The INA229 is a voltage, current and power measurement device.
A few important data, Read the datasheet for the details,
Section 7, Page 12++.


|  description   |  value      |  notes  |
|:---------------|:-----------:|:--------|
|  bus voltage   |  85 Volt    |  unclear for how long.
|  ADC           |  20 bit     |
|  alert timing  |  75 µs.     |


No breakout boards are known.


### Calibrating

Note the power and the current are not meaningful without calibrating the sensor.
Also the values are not meaningful if there is no shunt connected.


### Schema LOW SIDE


```
         GND                           VCC
          |                             |
          |                             |
          |            +----[ LOAD ]----+
          |            |                |
          |            |                |
      /-------------------------------------\
      |  VIN-         VIN+             VBUS |
      |                                     |
      |                                     |
      |          INA229 BREAKOUT            |
      |                                     |
      |                                     |
      \-------------------------------------/

```

Not tested with hardware, feedback welcome.


### Schema HIGH SIDE


```
         GND                          VCC
          |                            |
          |                            |
          +---[ LOAD ]---+        +----+
                         |        |    |
                         |        |    |
      /-------------------------------------\
      |                 VIN-     VIN+  VBUS |
      |                                     |
      |                                     |
      |          INA229 BREAKOUT            |
      |                                     |
      |                                     |
      \-------------------------------------/

```

Not tested with hardware, feedback welcome.


### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)
- ° == degree = ALT-0176 (Windows)
- ± == plus minus = ALT-0177 (Windows)


### Related

- https://www.ti.com/product/INA229#tech-docs
- https://www.ti.com/product/INA229#params
- https://www.ti.com/document-viewer/INA229/datasheet
- https://github.com/RobTillaart/INA219  26 Volt, I2C, 12 bit
- https://github.com/RobTillaart/INA226  36 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA228  85 Volt, I2C, 20 bit
- https://github.com/RobTillaart/INA236  48 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA229  85 Volt, SPI, 20 bit
- https://github.com/RobTillaart/INA239  85 Volt, SPI, 16 bit
- https://github.com/RobTillaart/INA3221_RT  26 Volt, I2C, 13 bits (3 channel)
- https://www.adafruit.com/product/5832
- https://www.mateksys.com/?portfolio=i2c-ina-bm
- https://github.com/RobTillaart/printHelpers  (for scientific notation)


### Performance

Run **INA229_performance.ino** sketch to get a first indication.
Numbers below are based upon tests with no hardware (SPI allows that).

Time in micros, HardWare SPI speed in MHz, Arduino UNO (indicative).

|  SPI  |  function         |  time  |  notes  |
|:-----:|:------------------|:------:|:-------:|
|  1.0  |  getBusVoltage    |   68   |  100%
|  1.0  |  getShuntVoltage  |  116   |
|  1.0  |  getCurrent       |   68   |
|  1.0  |  getPower         |   80   |
|  1.0  |  getTemperature   |   56   |
|  1.0  |  getEnergy        |  184   |
|  1.0  |  getCharge        |  176   |
|       |                   |        |  other functions similar gain.
|  2.0  |  getBusVoltage    |   52   |  24% faster
|  4.0  |  getBusVoltage    |   44   |  36% faster
|  8.0  |  getBusVoltage    |   44   |  36% faster


Most non core functions are as fast as **getTemperature()** or better.


## Interface

```cpp
#include "INA229.h"
```

### Constructor

- **INA229(uint8_t select, __SPI_CLASS__ \* mySPI = &SPI)** Constructor HARDWARE SPI
- **INA229(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)**
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
Note the value can be positive or negative as the INA229 is bidirectional.
- **float getShuntVolt()**
- **float getShuntMilliVolt()**
- **float getShuntMicroVolt()**
- **int32_t getShuntVoltageRAW()** integer version requested in issue #3.
Returns raw ADC value, 20 bits with sign extended.

### SHUNT CURRENT

- **float getCurrent()** returns the current through the shunt in Ampere.
Note this value can be positive or negative as the INA229 is bidirectional.
- **float getAmpere()**
- **float getMilliAmpere()**
- **float getMicroAmpere()**

### TEMPERATURE

- **float getTemperature()** returns the temperature in Celsius.

### POWER

- **float getPower()** returns the current x BusVoltage in Watt.
- **float getWatt()**
- **float getMilliWatt()**
- **float getMicroWatt()**
- **float getKiloWatt()**


### ENERGY

See page 13++, page 32, 8.1.2

The **getEnergy()** only has meaning in continuous mode.
This is an accumulation register and can be reset to zero by **setAccumulation(1)**.

The accuracy of **getEnergy()** is 1.0% full scale (maximum).

- **double getEnergy()** return Joule (elaborate).
- **double getJoule()**
- **double getMegaJoule()**
- **double getKiloJoule()**
- **double getMilliJoule()**
- **double getMicroJoule()**
- **double getWattHour()**
- **double getKiloWattHour()**

### CHARGE

The **getCharge()** only has meaning in continuous mode.
This is an accumulation register and can be reset to zero by **setAccumulation(1)**.

The accuracy of **getCharge()** is 1.0% full scale (maximum).

- **double getCharge()** return Coulomb (elaborate).
- **double getCoulomb()**
- **double getMilliCoulomb()**
- **double getMicroCoulomb()**

### Configuration

Read datasheet for details, section 7.6.1.1, page 22

- **void reset()** Resets the device, be aware that you need to calibrate the sensor
(shunt register) again ==> call **setMaxCurrentShunt()** and more.
- **bool setAccumulation(uint8_t value)** value: 0 == normal operation,
1 = clear Energy and Charge registers.
- **bool getAccumulation()** return set value. (TODO check).
- **void setConversionDelay(uint8_t steps)**  Conversion delay in 0..255 steps of 2 ms
- **uint8_t getConversionDelay()** return set value.
- **void setTemperatureCompensation(bool on)** see Shunt temperature coefficient below.
- **bool getTemperatureCompensation()** return set value.
- **bool setADCRange(bool flag)** flag = false => 164 mV, true => 41 mV
Since 0.4.1 setADCRange() calls setMaxCurrentShunt() to update the internal LSB values.
Returns false on failure of setMaxCurrentShunt().
- **bool getADCRange()** return set value.

TODO: wrapper + better name for setAccumulation().

TODO: examples to show the effect of the ADC configuration.

### ADC mode

Read datasheet for details, section 7.6.1.2, page 22++

- **bool setMode(uint8_t mode = INA229_MODE_CONT_TEMP_BUS_SHUNT)** default all on.
- **uint8_t getMode()** return set value.

|  MODE                           |  value  |  notes  |
|:--------------------------------|:-------:|:--------|
| INA229_MODE_SHUTDOWN            |   0x00  |  See 0x08.
| INA229_MODE_TRIG_BUS            |   0x01  |
| INA229_MODE_TRIG_SHUNT          |   0x02  |
| INA229_MODE_TRIG_BUS_SHUNT      |   0x03  |
| INA229_MODE_TRIG_TEMP           |   0x04  |
| INA229_MODE_TRIG_TEMP_BUS       |   0x05  |
| INA229_MODE_TRIG_TEMP_SHUNT     |   0x06  |
| INA229_MODE_TRIG_TEMP_BUS_SHUNT |   0x07  |
| INA229_MODE_SHUTDOWN2           |   0x08  |  There are two shutdowns.
| INA229_MODE_CONT_BUS            |   0x09  |
| INA229_MODE_CONT_SHUNT          |   0x0A  |
| INA229_MODE_CONT_BUS_SHUNT      |   0x0B  |
| INA229_MODE_CONT_TEMP           |   0x0C  |
| INA229_MODE_CONT_TEMP_BUS       |   0x0D  |
| INA229_MODE_CONT_TEMP_SHUNT     |   0x0E  |
| INA229_MODE_CONT_TEMP_BUS_SHUNT |   0x0F  |


### ADC conversion time

- **bool setBusVoltageConversionTime(uint8_t bvct = INA226_1052_us)**
- **uint8_t getBusVoltageConversionTime()** return set value.
- **bool setShuntVoltageConversionTime(uint8_t svct = INA226_1052_us)**
- **uint8_t getShuntVoltageConversionTime()** return set value.
- **bool setTemperatureConversionTime(uint8_t tct = INA226_1052_us)**
- **uint8_t getTemperatureConversionTime()** return set value.

|  TIMING             |  value  |  notes  |
|:--------------------|:-------:|:--------|
| INA229_50_us        |    0    |
| INA229_84_us        |    1    |
| INA229_150_us       |    2    |
| INA229_280_us       |    3    |
| INA229_540_us       |    4    |
| INA229_1052_us      |    5    |
| INA229_2074_us      |    6    |
| INA229_4120_us      |    7    |


- **bool setAverage(uint8_t avg = INA229_1_SAMPLE)**
- **uint8_t getAverage()** return set value.

|  AVERAGE            |  value  |  notes  |
|:--------------------|:-------:|:--------|
| INA229_1_SAMPLE     |    0    |
| INA229_4_SAMPLES    |    1    |
| INA229_16_SAMPLES   |    2    |
| INA229_64_SAMPLES   |    3    |
| INA229_128_SAMPLES  |    4    |
| INA229_256_SAMPLES  |    5    |
| INA229_512_SAMPLES  |    6    |
| INA229_1024_SAMPLES |    7    |


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
- **float getCurrentLSB_mA()** idem.
- **float getCurrentLSB_uA()** idem.


### Shunt temperature coefficient

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
Returns false if ppm is out of range.
- **uint16_t getShuntTemperatureCoefficent()** returns the set value (default 0).


### Diagnose alert

Read datasheet for details, section 7.6.1.12, page 26++.

- **void setDiagnoseAlert(uint16_t flags)** set all flags as bit mask.
- **uint16_t getDiagnoseAlert()** return all flags as bit mask.

INA229.h has an enum for the bit fields.

- **void setDiagnoseAlertBit(uint8_t bit)** set individual bit.
- **void clearDiagnoseAlertBit(uint8_t bit)** clear individual bit.
- **uint16_t getDiagnoseAlertBit(uint8_t bit)** return individual bit.


### Threshold and Limits

Read datasheet for details, section 7.3.7, page 16++

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
- test with hardware

#### Should

- keep in sync with INA228 where possible
- Fix TODO's in code and docs.

#### Could

- replace ina229_diag_enum with bit masks iso bits?
- design and implement better API for THRESHOLD AND LIMIT REGISTERS
- investigate / solve dependency on ADC register -  THRESHOLD AND LIMIT REGISTERS
  - e.g. setShuntOvervoltageTH
- implement error enum / defines
  - INA229_OK = 0
  - INA229_ERR_SHUNT_TOO_LOW = -2
  - 

#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

