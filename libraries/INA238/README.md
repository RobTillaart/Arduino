
[![Arduino CI](https://github.com/RobTillaart/INA238/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA238/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA238/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA238/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA238/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA238.svg)](https://github.com/RobTillaart/INA238/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA238/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA238.svg?maxAge=3600)](https://github.com/RobTillaart/INA238/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA238.svg)](https://registry.platformio.org/libraries/robtillaart/INA238)


# INA238

Arduino library for the INA238 power sensor.


## Description

**Experimental**

This library controls the INA238, a device that measures voltage,
current, power and temperature.

The library implements a derived INA237 class which is compatible
but less precise.

The INA238 sensor differs from the better known INA228.
Most important difference is that the INA238 has a 16 bit ADC.
This means it is slightly faster than the 20 bit INA228, but less precise.
Furthermore the INA238 has no energy and no charge register.
Finally there is no configurable temperature compensation.

The INA238 also provides an **ALERT** line, to generate an interrupt
in case a predefined threshold has been met.
This can be an under- or over-voltage, temperature or power limit.
The library does not handle the interrupts.
The alert / limits part of the library's API still needs a redesign.

The library is not yet tested or verified with hardware.

==> **USE WITH CARE**

Feedback as always is welcome.


### Details

The INA238 is a voltage, current and power measurement device.
A few important data, Read the datasheet for the details,
Section 7, Page 12++.


|  description   |  value      |  notes  |
|:---------------|:-----------:|:--------|
|  bus voltage   |  85 Volt    |  unclear for how long.
|  ADC           |  16 bit     |
|  alert timing  |  75 µs.     |


One breakout board is known.
https://www.adafruit.com/product/6349
Not tested.


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
      |          INA238 BREAKOUT            |
      |                                     |
      |                                     |
      \-------------------------------------/

```

TODO Test


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
      |          INA238 BREAKOUT            |
      |                                     |
      |                                     |
      \-------------------------------------/

```

_Tested - see #2_


### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)
- ° == degree = ALT-0176 (Windows)
- ± == plus minus = ALT-0177 (Windows)


### Related

- https://www.ti.com/product/INA238#tech-docs
- https://www.ti.com/product/INA238#params
- https://www.ti.com/document-viewer/INA238/datasheet
- https://github.com/RobTillaart/INA219  26 Volt, I2C, 12 bit
- https://github.com/RobTillaart/INA226  36 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA228  85 Volt, I2C, 20 bit
- https://github.com/RobTillaart/INA236  48 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA238  85 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA229  85 Volt, SPI, 20 bit
- https://github.com/RobTillaart/INA239  85 Volt, SPI, 16 bit
- https://github.com/RobTillaart/INA3221_RT  26 Volt, I2C, 13 bits (3 channel)
- https://www.adafruit.com/product/6349
- https://www.mateksys.com/?portfolio=i2c-ina-bm
- https://github.com/RobTillaart/printHelpers  (for scientific notation)


## I2C

### Address

The sensor can have 16 different I2C addresses,
which depends on how the A0 and A1 address lines
are connected to the SCL, SDA, GND and VCC pins.

See table - from datasheet table 7-2, page 19.

|  A1   |  A0   |  Addr  |  HEX   |   |  A1   |  A0   |  Addr  |  HEX   |
|:-----:|:-----:|:------:|:------:|:-:|:-----:|:-----:|:------:|:------:|
|  GND  |  GND  |   64   |  0x40  |   |  SDA  |  GND  |   72   |  0x48  |
|  GND  |  VCC  |   65   |  0x41  |   |  SDA  |  VCC  |   73   |  0x49  |
|  GND  |  SDA  |   66   |  0x42  |   |  SDA  |  SDA  |   74   |  0x4A  |
|  GND  |  SCL  |   67   |  0x43  |   |  SDA  |  SCL  |   75   |  0x4B  |
|  VCC  |  GND  |   68   |  0x44  |   |  SCL  |  GND  |   76   |  0x4C  |
|  VCC  |  VCC  |   69   |  0x45  |   |  SCL  |  VCC  |   77   |  0x4D  |
|  VCC  |  SDA  |   70   |  0x46  |   |  SCL  |  SDA  |   78   |  0x4E  |
|  VCC  |  SCL  |   71   |  0x47  |   |  SCL  |  SCL  |   79   |  0x4F  |


Note this might differ per breakout board.


### Performance

Run **INA238_performance.ino** sketch to get a first indication of your
board used.
Numbers below are based upon tests with RP2040 (see issue #2).

Time in micros, I2C speed in kHz.

|  I2C  |  function         |  time  |  notes  |
|:-----:|:------------------|:------:|:-------:|
|  100  |  getBusVoltage    |   620  |  100%
|  100  |  getShuntVoltage  |   590  |   95%
|  100  |  getCurrent       |   583  |   94%
|  100  |  getPower         |   728  |  117%
|  100  |  getTemperature   |   601  |   97%
|       |                   |        |  other functions similar gain.
|  200  |  getBusVoltage    |   350  |   56%
|  400  |  getBusVoltage    |   237  |   38%
|  800  |  getBusVoltage    |   167  |   27%


Most non core functions are as fast as **getTemperature()**


### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up
to eight channels (think of it as I2C subnets) which can use the complete
address range of the device.

Drawback of using a multiplexer is that it takes more administration in
your code e.g. which device is on which channel.
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


## Interface

```cpp
#include "INA238.h"
```

### Constructor

- **INA238(const uint8_t address, TwoWire \*wire = Wire)** Constructor to set
the address and optional Wire interface.
- **bool begin()** initializes the class.
Returns true if the INA238 address is on the I2C bus.
  - Note: one needs to set **Wire.begin()** before calling **begin()**.
  - Note: call **setMaxCurrentShunt(maxCurrent, shunt)** to calibrate your INA238
- **bool isConnected()** returns true if the INA238 address is on the I2C bus.
- **uint8_t getAddress()** returns the address set in the constructor.

### BUS VOLTAGE

Main function + wrappers.

- **float getBusVoltage()** idem. Returns value in volts. Max 85 Volt.
This value is always positive.
- **float getBusVolt()**
- **float getBusMilliVolt()**
- **float getBusMicroVolt()**

### SHUNT VOLTAGE

- **float getShuntVoltage()** idem. Returns value in volts.
Note the value can be positive or negative as the INA238 is bidirectional.
- **float getShuntVolt()**
- **float getShuntMilliVolt()**
- **float getShuntMicroVolt()**

### SHUNT CURRENT

- **float getCurrent()** returns the current through the shunt in Ampere.
Note this value can be positive or negative as the INA238 is bidirectional.
- **float getAmpere()**
- **float getMilliAmpere()**
- **float getMicroAmpere()**

### POWER

- **float getPower()** returns the current x BusVoltage in Watt.
- **float getWatt()**
- **float getMilliWatt()**
- **float getMicroWatt()**
- **float getKiloWatt()**

### TEMPERATURE

- **float getTemperature()** returns the temperature in Celsius.


### Configuration

Read datasheet for details, section 7.6.1.2, page 21++

- **void reset()** Resets the device, be aware that you need to calibrate the sensor
(shunt register) again ==> call **setMaxCurrentShunt()** and more.
- **void setConversionDelay(uint8_t steps)**  Conversion delay in 0..255 steps of 2 ms
- **uint8_t getConversionDelay()** return set value.
- **void setADCRange(bool flag)** flag = false => ~163.84 mV, true => ~40.96 mV
- **bool getADCRange()** return set value.


### ADC mode

Read datasheet for details, section 7.6.1.2, page 22++

- **bool setMode(uint8_t mode = INA238_MODE_CONT_TEMP_BUS_SHUNT)** default all on.
- **uint8_t getMode()** return set value.

|  MODE                           |  value  |  notes  |
|:--------------------------------|:-------:|:--------|
| INA238_MODE_SHUTDOWN            |   0x00  |  See 0x08.
| INA238_MODE_TRIG_BUS            |   0x01  |
| INA238_MODE_TRIG_SHUNT          |   0x02  |
| INA238_MODE_TRIG_BUS_SHUNT      |   0x03  |
| INA238_MODE_TRIG_TEMP           |   0x04  |
| INA238_MODE_TRIG_TEMP_BUS       |   0x05  |
| INA238_MODE_TRIG_TEMP_SHUNT     |   0x06  |
| INA238_MODE_TRIG_TEMP_BUS_SHUNT |   0x07  |
| INA238_MODE_SHUTDOWN2           |   0x08  |  There are two shutdowns.
| INA238_MODE_CONT_BUS            |   0x09  |
| INA238_MODE_CONT_SHUNT          |   0x0A  |
| INA238_MODE_CONT_BUS_SHUNT      |   0x0B  |
| INA238_MODE_CONT_TEMP           |   0x0C  |
| INA238_MODE_CONT_TEMP_BUS       |   0x0D  |
| INA238_MODE_CONT_TEMP_SHUNT     |   0x0E  |
| INA238_MODE_CONT_TEMP_BUS_SHUNT |   0x0F  |


### ADC conversion time

- **bool setBusVoltageConversionTime(uint8_t bvct = INA226_1052_us)**
- **uint8_t getBusVoltageConversionTime()** return set value.
- **bool setShuntVoltageConversionTime(uint8_t svct = INA226_1052_us)**
- **uint8_t getShuntVoltageConversionTime()** return set value.
- **bool setTemperatureConversionTime(uint8_t tct = INA226_1052_us)**
- **uint8_t getTemperatureConversionTime()** return set value.

|  TIMING             |  value  |  notes  |
|:--------------------|:-------:|:--------|
| INA238_50_us        |    0    |
| INA238_84_us        |    1    |
| INA238_150_us       |    2    |
| INA238_280_us       |    3    |
| INA238_540_us       |    4    |
| INA238_1052_us      |    5    |
| INA238_2074_us      |    6    |
| INA238_4120_us      |    7    |


### ADC Average

- **bool setAverage(uint8_t avg = INA238_1_SAMPLE)**
- **uint8_t getAverage()** return set value.

|  AVERAGE            |  value  |  notes  |
|:--------------------|:-------:|:--------|
| INA238_1_SAMPLE     |    0    |
| INA238_4_SAMPLES    |    1    |
| INA238_16_SAMPLES   |    2    |
| INA238_64_SAMPLES   |    3    |
| INA238_128_SAMPLES  |    4    |
| INA238_256_SAMPLES  |    5    |
| INA238_512_SAMPLES  |    6    |
| INA238_1024_SAMPLES |    7    |


### Shunt Calibration

To elaborate, read datasheet for details, section 7.6.1.3, page 23

Note: **setMaxCurrentShunt()** must be called to calibrate your sensor.
Otherwise several functions will return zero or incorrect data.

- **int setMaxCurrentShunt(float maxCurrent, float shunt)** The maxCurrent
depends on breakout used, See section above.
The shunt should be 0.0001 Ω and up.
  - returns 0 if OK.
  - returns -2 if shunt < 0.0001 Ohm. ( Mateksys == 0.0002 Ω )
  - returns -3 if maxCurrent < 0.0.
- **bool isCalibrated()** is valid calibration value. The currentLSB > 0.
- **float getMaxCurrent()** return set value.
- **float getShunt()** return set value.
- **float getCurrentLSB()** return actual currenLSB. <= 0.0 means not calibrated.


### Diagnose alert

Read datasheet for details, section 7.6.1.9, page 24++.

- **void setDiagnoseAlert(uint16_t flags)** set all flags as bit mask.
- **uint16_t getDiagnoseAlert()** return all flags as bit mask.

INA238.h has an enum for the bit fields.

- **void setDiagnoseAlertBit(uint8_t bit)** set individual bit.
- **void clearDiagnoseAlertBit(uint8_t bit)** clear individual bit.
- **uint16_t getDiagnoseAlertBit(uint8_t bit)** return individual bit.


### Threshold and Limits

Read datasheet for details, section 7.3.6, page 16++

Note: the implementation of this part is rather minimalistic and
might be changed / extended in the future.
Idem see my INA228 library.

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

- **bool getManufacturer()** Returns 0x5449, can be used to check right sensor. Note 0x5449 == TI in ASCII.
- **uint16_t getDieID()** Returns 0x238, can be used to check right sensor.
(INA237 will return 0x237).
- **uint16_t getRevision()** Returns revision, probably 0x01.


## Future

#### Must

- update documentation.
- test and verify with hardware
- keep sync INA228 where possible.
- fix TODO's in code + readme.md

#### Should

- how to detect nothing connected?
  - vshunt >  maxVShunt (new variable)
  - current > maxCurrent
- examples
  - example to show the effect of the ADC configuration.
- improve error handling (INA228)
  - constants/enum

#### Could

- improve API thresholds and limits (INA228)
- improve API use bitmasks for diagnostics (INA228)
- write examples, (please share yours).
- improve unit tests
- clean up magic numbers in the code?

#### Won't

- cache registers for performance
  - first get library working / tested.
  - reset should reread all cached values...


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

