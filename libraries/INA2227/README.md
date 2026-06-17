
[![Arduino CI](https://github.com/RobTillaart/INA2227/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA2227/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA2227/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA2227/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA2227/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA2227.svg)](https://github.com/RobTillaart/INA2227/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA2227/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA2227.svg?maxAge=3600)](https://github.com/RobTillaart/INA2227/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA2227.svg)](https://registry.platformio.org/libraries/robtillaart/INA2227)


# INA2227

Arduino library for the INA2227, I2C, 16 bit, dual channel, voltage, current, power and energy sensor.


## Description

**Experimental - WORK IN PROGRESS**

The INA2227 is a voltage, current, power and energy measurement device.
A difference with most other INA sensors is that this is a **dual channel**
device, so one can think of it as "two INA228's" in one device.
This dual channel allows to make two independent measurements e.g. with
different shunt resistors and different voltages.
This could be used to monitor both the 5 Volt and the 24 Volt part of a system with one INA2227.
An other applications might be the monitoring of the heating and the
pumps of an aquarium separately.
Or simply monitor two different systems simultaneously.
(please share your applications).

A few important maxima, see datasheet.

|  description  |  max  |  unit  |  notes  |
|:--------------|------:|-------:|:--------|
| bus voltage   |  48   | Volt   |  unclear for how long.
| shunt voltage |  80   | mVolt  |  can be set to 20 mV.
| current       |  20   | Ampere |  depends on shunt

Feedback as always is welcome.


**WORK IN PROGRESS**

The library is written based upon the datasheet (and experiences with other INA sensors) 
however it is NOT tested yet with hardware.
Not all functionality is completely implemented, especially the ALERT limit 
and configuration functions. So advise is to use with care.
If you have an INA2227 and you have issues, please let me know so I can fix them.
Of course also interested in the confirmation of the working parts.

_This library and documentation is based upon the INA236 and INA228 library,
and may contain information not updated (or removed) yet.
Please open an issue if needed._

### 0.1.1

Fixes #2 the register addresses for POWER and CURRENT. 
This fix obsoletes 0.1.0.


### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)


### Related

- https://www.ti.com/product/INA2227#tech-docs
- https://www.ti.com/product/INA2227#params
- https://www.ti.com/document-viewer/INA2227/datasheet
- https://github.com/RobTillaart/INA219  26 Volt, I2C, 12 bit
- https://github.com/RobTillaart/INA226  36 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA228  85 Volt, I2C, 20 bit
- https://github.com/RobTillaart/INA229  85 Volt, SPI, 20 bit
- https://github.com/RobTillaart/INA236  48 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA238  85 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA239  85 Volt, SPI, 16 bit
- https://github.com/RobTillaart/INA260  36 Volt, SPI, 16 bit
- https://github.com/RobTillaart/INA2227  48 Volt, I2C, 16 bit, (2 channel)
- https://github.com/RobTillaart/INA3221_RT  26 Volt, I2C, 13 bits (3 channel)
- https://www.adafruit.com/product/5832
- https://www.mateksys.com/?portfolio=i2c-ina-bm
- https://github.com/RobTillaart/printHelpers  - for scientific notation)


## I2C

### Address

The INA2227 comes in two flavours, the INA2227A and INA2227B
with two disjunct address ranges.
Both can have 4 different I2C addresses, which depends on how
the A0 address line is connected to the SCL, SDA, GND and VCC pins.

See table - from datasheet table 7.1, page 16.

|  A0   |  INA2227A  |  HEX   |  INA2227B  |  HEX   |
|:-----:|:----------:|:------:|:----------:|:------:|
|  GND  |     64     |  0x40  |     72     |  0x48  |
|  VS   |     65     |  0x41  |     73     |  0x49  |
|  SDA  |     66     |  0x42  |     74     |  0x4A  |
|  SCL  |     67     |  0x43  |     75     |  0x4B  |


### Performance

To be elaborated, example sketch needed + HW

(From Datasheet 7.5.1)
_The INA2227 supports the transmission protocol for fast mode up to
400 kHz and high-speed mode up to 2.94 MHz._


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


## About Measurements

Calibration with **setMaxCurrentShunt()** is mandatory to get
**getCurrent()** and **getPower()** to work.

Some initial tests shows that the readings do not 100% add up.
I expect this is caused by fluctuations in my power supply used and
more important that the ADC is multiplexed so there is time between
the bus voltage measurement and the shunt voltage measurement.
If the current has changed a bit these values are not necessary in line.

Did some measurements with a load of 194 ohm and a shunt of 0.002 ohm that is a factor 10e5
Being on the edge of the sensitivity of the ADC measurements of current were up to ~9% too low.
Possible cause is that some maths is done in 16 bit so numbers are truncated, not rounded.

(see issue #2) Sensors may have a different shunt resistor than the 0.002 I have. You should
always check and verify what is on the shunt and even verify with a DMM that this value is correct.
With the calibration function **setMaxCurrentShunt()** one can just set the actual value and even
compensate slightly if readings are structural too low or too high.

I noted that the **getPower()** function does not always equal **getBusVoltage()** times **getCurrent()**.
Cause is rounding/trunking maths and time of measurement.
You might prefer to multiply those values yourself to get extra digits.
Please be aware that more digits is not always more exact (think significant digits).

The example sketch **INA2227_setMaxCurrentShunt.ino** switches between two calibration modes.
It shows the **INA266** sensor needs time to accommodate to this change.
In practice you should call **setMaxCurrentShunt()** only once in **setup()**.

Also see INA226 issue 30 for another typical deviation problem.


## Interface

```cpp
#include "INA2227.h"
```

### Constructor

- **INA2227(const uint8_t address, TwoWire \*wire = Wire)** Constructor to set
the address and optional Wire interface.
- **bool begin()** initializes the class.
returns true if the INA2227 address is on the I2C bus.
Note: one needs to set **Wire.begin()** before calling **begin()**.
- **bool isConnected()** returns true if the INA2227 address is on the I2C bus.
- **uint8_t getAddress()** returns the address set in the constructor.


### Bus voltage

Main function + wrappers.

- **float getBusVoltage(uint8_t ch)** returns value in volts. Max 48 Volt.
- **float getBusVolt(uint8_t ch)** idem
- **float getBusMilliVolt(uint8_t ch)** wrapper
- **float getBusMicroVolt(uint8_t ch)** wrapper

### Shunt voltage

- **float getShuntVoltage(uint8_t ch)** returns value in volts.
- **float getShuntVolt(uint8_t ch)** idem
- **float getShuntMilliVolt(uint8_t ch)** wrapper
- **float getShuntMicroVolt(uint8_t ch)** wrapper

### Shunt current

- **float getCurrent(uint8_t ch)** returns the current through the shunt in Ampere.
- **float getAmpere(uint8_t ch)** idem
- **float getMilliAmpere(uint8_t ch)** wrapper
- **float getMicroAmpere(uint8_t ch)** wrapper

### Power

- **float getPower(uint8_t ch)** returns the current x BusVoltage in Watt.
- **float getWatt(uint8_t ch)** idem
- **float getMilliWatt(uint8_t ch)** wrapper
- **float getMicroWatt(uint8_t ch)** wrapper
- **float getKiloWatt(uint8_t ch)** wrapper

### Energy

- **float getEnergy(uint8_t ch)** returns Joule or watt second
- **float getJoule(uint8_t ch)** idem
- **float getMegaJoule(uint8_t ch)** wrapper
- **float getKiloJoule(uint8_t ch)** wrapper
- **float getMilliJoule(uint8_t ch)** wrapper
- **float getMicroJoule(uint8_t ch)** wrapper
- **float getWattHour(uint8_t ch)** wrapper
- **float getKiloWattHour(uint8_t ch)** wrapper

Use - https://github.com/RobTillaart/printHelpers for scientific or engineering notation.


### Enable / Disable

Enable or disable one or both channels.
Default both channels are enabled.

- **void enableChannel(uint8_t ch)**
- **void disableChannel(uint8_t ch)**
- **void enableAllChannels()**
- **void disableAllChannels()**
- **bool isEnabled(uint8_t ch)**


### Average

- **bool setAverage(uint8_t avg = INA2227_1_SAMPLE)** see table below.
(0 = default ==> 1 read), returns false if parameter > 7.
- **uint8_t getAverage()** returns the value set. See table below.
Note this is not the count of samples.

|  enum description     | value | # samples |  notes  |
|:---------------------:|:-----:|----------:|--------:|
|  INA2227_1_SAMPLE     |   0   |      1    |  default
|  INA2227_4_SAMPLES    |   1   |      4    |
|  INA2227_16_SAMPLES   |   2   |     16    |
|  INA2227_64_SAMPLES   |   3   |     64    |
|  INA2227_128_SAMPLES  |   4   |    128    |
|  INA2227_256_SAMPLES  |   5   |    256    |
|  INA2227_512_SAMPLES  |   6   |    512    |
|  INA2227_1024_SAMPLES |   7   |   1024    |


### ADC Voltage conversion time

**Note:**
The internal conversions runs in the background in the device.
If a conversion is finished the measured value is stored in the appropriate register.
The last obtained values can always be read from the registers, so they will not block.
Result can be that you get the very same value if no new data is available yet.
This is especially true if you increase the number of samples.
(See also discussion in INA219 GitHub, issue 11).

Using more samples reduces the noise level, but one will miss the faster
changes in voltage or current.
Depending on your project needs you can choose one over the other.

As a rule of thumb one could take the time between two I2C reads of
a register as an upper limit.
This would result in a fresh measurement every time one reads the register.
NB it is always possible to average readings fetched from the device
in your own code.


- **bool setBusVoltageConversionTime(uint8_t bvct = INA2227_1100_us)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **uint8_t getBusVoltageConversionTime()** return the value set.
Note the value returned is not a unit of time.
- **bool setShuntVoltageConversionTime(uint8_t svct = INA2227_1100_us)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **uint8_t getShuntVoltageConversionTime()** return the value set.
Note the value returned is not a unit of time.


|  enum description   | BVCT SVCT |   time    |  notes  |
|:-------------------:|:---------:|:---------:|--------:|
|  INA2227_140_us     |     0     |  140 us   |
|  INA2227_204_us     |     1     |  204 us   |
|  INA2227_332_us     |     2     |  332 us   |
|  INA2227_588_us     |     3     |  588 us   |
|  INA2227_1100_us    |     4     |  1.1 ms   |  default
|  INA2227_2100_us    |     5     |  2.1 ms   |
|  INA2227_4200_us    |     6     |  4.2 ms   |
|  INA2227_8300_us    |     7     |  8.3 ms   |


Note: times are typical, check datasheet for operational range.
(max is ~10% higher)

Note: total conversion time can take up to 1024 \* 8.3 ms ~ 10 seconds
if many samples are averaged.


### Operating mode

Read datasheet for details.

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


### Reset + reset Energy Accumulator

- **bool reset()** software power on reset. Returns true upon success.
After calling **reset()** the calibration with **setMaxCurrentShunt()** needs to be done again.
- **bool resetEnergyAccumulator(uint8_t ch)** resets energy accumulators to zero and resets overflow flags.
- **bool getEnergyAccumulatorChannel(uint8_t ch)** get flag


### ALERT pin configuration

See datasheet 7.1.3

- **bool setAlertConvertReady(bool cnvr = false)** ALERT pin reflects conversion ready.
- **bool getAlertConvertReady()** returns set value.
- **bool setAlertEnergyOverflow(bool enof = false)** ALERT pin reflects energy overflow.
- **bool getAlertEnergyOverflow()** returns set value.
- **bool setAlertLatchEnable(bool latch = false)** ALERT pin latches during fault
- **bool getAlertLatchEnable()** returns set value.
- **bool setAlertPolarity(bool inverted = false)** ALERT pin polarity.
- **bool getAlertPolarity()**  returns set value.


### ADCRange

The INA2227 can set the ADC range to 20 mV (adcRange == true)
or to 80 mV (adcRange == false) to optimize the accuracy.

- **bool setADCRange(bool flag)** The function sets the voltage/LSB,
flag = false => 81.92 mV, true => 20.48 mV
Since 0.1.3 setADCRange() calls setMaxCurrentShunt() to update the internal LSB values.
Returns false on failure of setMaxCurrentShunt().
- **uint8_t getADCRange()** returns set value.

Note: this function is not available on INA226.


### FLAGS register

See datasheet

The FLAGS register (0x12) holds several flags that can be polled.

- **bool isConversionReady()** returns true if conversion ready flag is set.
- **bool waitConversionReady(uint32_t timeout = INA2227_MAX_WAIT_MS)**
active waiting for ready flag.
Polling for max timeout time, default 600 milliseconds, for wake up time.
- **bool hasMathOverflow()** current and/or power data can be invalid.
- **bool hasAlertLimit(uint8_t ch)** idem
- **bool hasEnergyOverflow(uint8_t ch)** idem
- **uint16_t getFlags()** to check all flags at once.
See below, should become an enum (See future).

default 0x0000.

|  Flags register masks       |  mask    |  notes  |
|:----------------------------|:--------:|:--------|
|  INA2227_FLAG_LIMIT1_ALERT  |  0x2000  |
|  INA2227_FLAG_LIMIT0_ALERT  |  0x1000  |
|  INA2227_FLAG_ENERGYOF_CH1  |  0x0200  |
|  INA2227_FLAG_ENERGYOF_CH0  |  0x0100  |
|  INA2227_FLAG_CONV_READY    |  0x0080  |
|  INA2227_FLAG_OVERFLOW      |  0x0040  |


### ALERT functions

See datasheet

ALERT LIMIT
- **bool setAlertLimit(uint8_t ch, uint16_t limit)** sets the limit that belongs to the configured ALERT flag.
Returns true if write to register successful.
- **uint16_t getAlertLimit(uint8_t ch)** returns the limit set.


ALERT CONFIG
- **bool setAlertConfig(uint8_t ch, uint16_t mask)**
- **uint16_t getAlertConfig(uint8_t ch)**


The **ALERT** pin changes when alert is reached.
Falling or rising depends on polarity set.


|  Alert Configuration masks    |  mask  |  short  |
|:------------------------------|:------:|--------:|
|  INA2227_SHUNT_OVER_VOLTAGE   |    1   |   SOL   |
|  INA2227_SHUNT_UNDER_VOLTAGE  |    2   |   SUL   |
|  INA2227_BUS_OVER_VOLTAGE     |    3   |   BOL   |
|  INA2227_BUS_UNDER_VOLTAGE    |    4   |   BUL   |
|  INA2227_POWER_OVER_LIMIT     |    5   |   POL   |


### Calibration

See datasheet.

Calibration is mandatory to get **getCurrent()** and **getPower()** to work.

- **int setMaxCurrentShunt(float ampere = 20.0, float ohm = 0.002, bool normalize = true)**
set the calibration register based upon the shunt and the max Ampere.
From these two values the current_LSB is derived, the steps of the ADC when measuring current.
This function also calls **setADCRange()** to optimize accuracy.
Returns Error code, see below.
- **bool isCalibrated()** returns true if CurrentLSB has been calculated by **setMaxCurrentShunt()**.
Value should not be zero.
- **float getCurrentLSB()** returns the LSB in Ampere == precision of the calibration.
- **float getCurrentLSB_mA()** returns the LSB in milliAmpere.
- **float getCurrentLSB_uA()** returns the LSB in microAmpere.
- **float getShunt()** returns the value set for the shunt in ohm.
- **float getMaxCurrent()** returns the value for the maxCurrent which can be corrected.

To print these values in scientific notation use https://github.com/RobTillaart/printHelpers


### About normalization

**setMaxCurrentShunt()** will round the current_LSB to nearest round value (typical 0.001) by default (normalize == true).
- The user **must** check the return value == 0x000, otherwise the calibration register is **not** set.
- Normalization typically gives smaller steps => improve precision
- Normalization can cause that the maxCurrent passed cannot be reached any more.
Solution is not to normalize if this max range is needed.


Note: in 0.5.1 the **setMaxCurrentShunt()** function is rewritten after it showed a bug when
normalize flag was set to true.
See https://github.com/RobTillaart/INA2227/pull/29 for details of the discussion.


### Error codes setMaxCurrentShunt

|  descriptive name error        |  value   |  meaning  |
|:-------------------------------|:--------:|:----------|
|  INA2227_ERR_NONE               |  0x0000  |  OK
|  INA2227_ERR_SHUNTVOLTAGE_HIGH  |  0x8000  |  maxCurrent \* shunt > 80 mV
|  INA2227_ERR_MAXCURRENT_LOW     |  0x8001  |  maxCurrent < 0.001
|  INA2227_ERR_SHUNT_LOW          |  0x8002  |  shunt      < 0.001
|  INA2227_ERR_NORMALIZE_FAILED   |  0x8003  |  not possible to normalize.


### Meta information

- **uint16_t getManufacturerID()** should return 0x5449
- **uint16_t getDieID()** should return 0xA080.


### Debugging

- **uint16_t getRegister(uint8_t reg)** fetch registers directly, for debugging only.


### Error Handling

- **int getLastError()** returns last (I2C) error.


## Adjusting the range of the INA2227

**use at own risk**

See INA226, issue 26 - https://github.com/RobTillaart/INA226/issues/26
See INA2227, issue 8  - https://github.com/RobTillaart/INA2227/issues/8

In issue #26 of INA226 a hack is made to scale the INA226 to 300A by using a very small shunt.
The INA2227 library has a minimal limit for the shunt of 0.001 Ohm = 1 mOhm.
This limit can be overruled to support wider ranges like the one discussed in #26.
Overruling can be done by changing the value in the **INA2227.h** file,
or by defining INA2227_MINIMAL_SHUNT on the command line.

```cpp
#ifndef INA2227_MINIMAL_SHUNT
#define INA2227_MINIMAL_SHUNT             (0.001)
#endif
```

Be aware that
- **you should NOT do this unless you understand the implications**.
- you do this at your own risk.
- the resistance of wires used affect measurements with very small shunts.
- solder might change the resistance too.
- you do this at your own risk.


## Future


#### Must

- keep in sync with INA226 where possible.
- improve documentation
  - readability, completeness tables, missing sections?
- buy hardware to test


#### Should

- make enum of flags register fields.
- copy/convert INA236/228 alike examples
- add performance sketch and do 1st order measurements


#### Could

- check keywords.txt
- optimize if it works and if possible
- look at unit tests

#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

