
[![Arduino CI](https://github.com/RobTillaart/INA260/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA260/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA260/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA260/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA260/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA260.svg)](https://github.com/RobTillaart/INA260/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA260/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA260.svg?maxAge=3600)](https://github.com/RobTillaart/INA260/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA260.svg)](https://registry.platformio.org/libraries/robtillaart/INA260)


# INA260

Arduino library for the INA260 power sensor.


## Description

**Experimental** 

Arduino library for the INA260 power sensor.  
This library is based upon the INA226 library however the INA260 is slightly simpler.

Not all functionality is tested / investigated.

Read datasheet for details.

==> **USE WITH CARE**

The INA260 is a voltage, current and power measurement device. 
A few important maxima, see datasheet, chapter 6.

|  description    |  max  |   unit   |  notes  |
|:----------------|------:|---------:|:--------|
|  bus voltage    |  36   |    Volt  |  See 8.3.2
|  shunt voltage  |  30   |   mVolt  |
|  current        |  15   |  Ampere  |

The INA260 shunt can withstand currents higher than 15 Amps for a certain amount of time.
(See datasheet 8.3.2, figure 22 for details)

Indicative table

|  Amps  |  seconds  |
|:------:|:---------:|
|  100   |    0.2    |
|   80   |    0.4    |
|   60   |    0.8    |
|   55   |    1.0    |
|   50   |    2.0    |
|   40   |    5.0    |


Feedback as always, is welcome.


### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)


### Related

- https://www.ti.com/product/INA260#tech-docs
- https://www.ti.com/product/INA260#params
- https://www.ti.com/document-viewer/INA260/datasheet
- https://github.com/RobTillaart/INA219  26 Volt, I2C, 12 bit
- https://github.com/RobTillaart/INA226  36 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA228  85 Volt, I2C, 20 bit
- https://github.com/RobTillaart/INA229  85 Volt, SPI, 20 bit
- https://github.com/RobTillaart/INA236  48 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA239  85 Volt, SPI, 16 bit
- https://github.com/RobTillaart/INA260  36 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA3221_RT  26 Volt, I2C, 13 bits (3 channel)
- https://www.adafruit.com/product/5832
- https://www.mateksys.com/?portfolio=i2c-ina-bm
- https://github.com/RobTillaart/printHelpers  (for scientific notation)


## I2C

### Address

The sensor can have 16 different I2C addresses, 
which depends on how the A0 and A1 address lines 
are connected to the SCL, SDA, GND and VCC pins.

See table - from datasheet table 2, page 18.

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


### Performance

To be elaborated, example sketch available.

(From Datasheet)  
_The INA260 supports the transmission protocol for fast mode (1 kHz to 400 kHz) 
and high-speed mode (1 kHz to 2.94 MHz).
All data bytes are transmitted most significant byte first._


## About Measurements

The INA260 has a build in shunt of 2 mOhm and has a default maxCurrent of 15 Amperes.
It cannot be reconfigured.

Some initial tests with other devices (INA226) shows that the readings do not 100% add up. 
I expect this is caused by fluctuations in my power supply used and
more important that the ADC is multiplexed so there is time between 
the bus voltage measurement and the shunt voltage measurement. 
If the current has changed a bit these values are not necessary in line.


## Interface

```cpp
#include "INA260.h"
```


### Constructor

- **INA260(const uint8_t address, TwoWire \*wire = Wire)** Constructor to set 
the address and optional Wire interface.
- **bool begin()** initializes the class.
returns true if the INA260 address is on the I2C bus.
Note: one needs to set **Wire.begin()** before calling **begin()**.
- **bool isConnected()** returns true if the INA260 address is on the I2C bus.
- **uint8_t getAddress()** returns the address set in the constructor.


### Core Functions

Note the power and the current are not meaningful without calibrating the sensor.
Also the value is not meaningful if there is no shunt connected.

- **float getShuntVoltage()** idem, in volts.
- **float getBusVoltage()** idem. in volts. Max 36 Volt.
- **float getCurrent()** is the current through the shunt in Ampere.
- **float getPower()** is the current x BusVoltage in Watt.
- **bool isConversionReady()** returns true if conversion ready flag is set.
- **bool waitConversionReady(uint32_t timeout = INA260_MAX_WAIT_MS)** 
active waiting for ready flag.
Polling for max timeout time, default 600 milliseconds, for wake up time.

The library has helper functions to convert above output to a more appropriate scale of units.

Helper functions for the milli scale.

- **float getBusVoltage_mV()** idem, in milliVolts.
- **float getShuntVoltage_mV()** idem, in milliVolts.
- **float getCurrent_mA()** idem, in milliAmpere.
- **float getPower_mW()** idem, in milliWatt.

Helper functions for the micro scale.

- **float getBusVoltage_uV()** idem, in microVolts.
- **float getShuntVoltage_uV()** idem, in microVolts.
- **float getCurrent_uA()** idem, in microAmpere.
- **float getPower_uW()** idem, in microWatt.


### Configuration

**Note:**
The internal conversions runs in the background in the device.
If a conversion is finished the measured value is stored in the appropriate register. 
The last obtained values can always be read from the registers, so they will not block.
Result can be that you get the very same value if no new data is available yet.
This is especially true if you increase the number of samples.
(See also discussion in INA219 issue #11).

Using more samples reduces the noise level, but one will miss the faster 
changes in voltage or current.
Depending on your project needs you can choose one over the other.

As a rule of thumb one could take the time between two I2C reads of 
a register as an upper limit.
This would result in a fresh measurement every time one reads the register. 
NB it is always possible to average readings fetched from the device
in your own code.


- **bool reset()** software power on reset. 
This implies calibration with **setMaxCurrentShunt()** needs to be redone.
Returns true upon success.
- **bool setAverage(uint8_t avg = INA260_1_SAMPLE)** see table below.
(0 = default ==> 1 read), returns false if parameter > 7.
- **uint8_t getAverage()** returns the value set. See table below.
Note this is not the count of samples.
- **bool setBusVoltageConversionTime(uint8_t bvct = INA260_1100_us)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **uint8_t getBusVoltageConversionTime()** return the value set. 
Note the value returned is not a unit of time.
- **bool setShuntCurrentConversionTime(uint8_t scct = INA260_1100_us)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **uint8_t getShuntCurrentConversionTime()** return the value set. 
Note the value returned is not a unit of time.


|  enum description    | value | # samples |  notes  |
|:--------------------:|:-----:|----------:|--------:|
|  INA260_1_SAMPLE     |   0   |      1    |  default
|  INA260_4_SAMPLES    |   1   |      4    |
|  INA260_16_SAMPLES   |   2   |     16    |
|  INA260_64_SAMPLES   |   3   |     64    |
|  INA260_128_SAMPLES  |   4   |    128    |
|  INA260_256_SAMPLES  |   5   |    256    |
|  INA260_512_SAMPLES  |   6   |    512    |
|  INA260_1024_SAMPLES |   7   |   1024    |


|  enum description  | BVCT SVCT |   time    |  notes  |
|:------------------:|:---------:|:---------:|--------:|
|  INA260_140_us     |     0     |  140 us   |
|  INA260_204_us     |     1     |  204 us   |
|  INA260_332_us     |     2     |  332 us   |
|  INA260_588_us     |     3     |  588 us   |
|  INA260_1100_us    |     4     |  1.1 ms   |  default
|  INA260_2100_us    |     5     |  2.1 ms   |
|  INA260_4200_us    |     6     |  4.2 ms   |
|  INA260_8300_us    |     7     |  8.3 ms   |


Note: times are typical, check datasheet for operational range.
(max is ~10% higher)

Note: total conversion time can take up to 1024 \* 8.3 ms ~ 10 seconds.


### Calibration

See datasheet.

The INA260 has a build in shunt of 2 mOhm and has a default maxCurrent of 15 Amperes.
It cannot be reconfigured.

- **float getCurrentLSB()** returns the LSB in Ampere == precision of the calibration.
- **float getCurrentLSB_mA()** returns the LSB in milliAmpere.
- **float getCurrentLSB_uA()** returns the LSB in microAmpere.
- **float getShunt()** returns the value set for the shunt in ohm.
- **float getMaxCurrent()** returns the value for the maxCurrent which can be corrected.

To print these values in scientific notation use https://github.com/RobTillaart/printHelpers 


### Operating mode

See datasheet, partially tested.

Mode = 4 is not used, is also a **shutdown()** unknown if there is a difference with mode == 0.

- **bool setMode(uint8_t mode = 7)** mode = 0..7.
The value 7 == ShuntBusContinuous mode.
- **uint8_t getMode()** returns the mode (0..7).

Descriptive mode functions (convenience wrappers).

- **bool shutDown()** mode 0 - not tested yet
- **bool setModeShuntTrigger()** mode 1 - not tested yet - how to trigger to be investigated
- **bool setModeBusTrigger()** mode 2 - not tested yet
- **bool setModeShuntBusTrigger()** mode 3 - not tested yet
- **bool setModeShuntContinuous()** mode 5
- **bool setModeBusContinuous()** mode 6
- **bool setModeShuntBusContinuous()** mode 7 - default.


### Alert functions

See datasheet, not tested yet.

- **bool setAlertRegister(uint16_t mask)** by setting the mask 
one of five types of over- or underflow can be detected. 
Another feature that can be set is the conversion ready flag.
Returns true if write to register is successful.
- **uint16_t getAlertRegister()** returns the mask set by **setAlertRegister()**.
- **bool setAlertLatchEnable(bool latch = false)** idem.
Returns true if write to register is successful.
- **bool getAlertLatchEnable()** return current status.
- **bool setAlertPolarity(bool inverted = false)** idem.
Returns true if write to register is successful.
- **bool getAlertPolarity()** return current status.


|  description alert register  |   mask   |  short  |
|:-----------------------------|:--------:|--------:|
|  INA260_SHUNT_OVER_VOLTAGE   |  0x8000  |    SOL  |
|  INA260_SHUNT_UNDER_VOLTAGE  |  0x4000  |    SUL  |
|  INA260_BUS_OVER_VOLTAGE     |  0x2000  |    BOL  |
|  INA260_BUS_UNDER_VOLTAGE    |  0x1000  |    BUL  |
|  INA260_POWER_OVER_LIMIT     |  0x0800  |    POL  |
|  INA260_CONVERSION_READY     |  0x0400  |   CNVR  |


|  description alert flags         |   mask   |  short  |
|:---------------------------------|:--------:|--------:|
|  INA260_ALERT_FUNCTION_FLAG      |  0x0010  |    AFF  |
|  INA260_CONVERSION_READY_FLAG    |  0x0008  |   CVRF  |
|  INA260_MATH_OVERFLOW_FLAG       |  0x0004  |    OVF  |


|  description alert configuration |   mask   |  short  |
|:---------------------------------|:--------:|--------:|
|  INA260_ALERT_POLARITY_FLAG      |  0x0002  |   APOL  |
|  INA260_ALERT_LATCH_ENABLE_FLAG  |  0x0001  |    LEN  |


The **ALERT** pin changes when alert is reached.
Falling or rising depends on polarity set.


#### Deprecated

**uint16_t getAlertFlag()** returns the mask set by setAlertRegister(). 
Deprecated, is replaced by **getAlertRegister()**.


### Alert Limits

See datasheet, not tested yet.

- **bool setAlertLimit(uint16_t limit)** sets the limit that belongs to the chosen Alert Flag.
Returns true if write to register successful.
- **uint16_t getAlertLimit()** returns the limit set by **setAlertLimit()**.

The alert line falls when alert is reached.


### Meta information

- **uint16_t getManufacturerID()** should return 0x5449
- **uint16_t getDieID()** should return 0x2270


### Debugging

- **uint16_t getRegister(uint8_t reg)** fetch registers directly, for debugging only.


### Error Handling

- **int getLastError()** returns last (I2C) error.


## Future


#### Must

- update documentation.
- keep in sync with INA226 where possible.
- test with hardware
- See INA226 lib.

#### Should

#### Could

#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

