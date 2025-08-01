
[![Arduino CI](https://github.com/RobTillaart/INA236/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA236/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA236/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA236/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA236/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA236.svg)](https://github.com/RobTillaart/INA236/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA236/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA236.svg?maxAge=3600)](https://github.com/RobTillaart/INA236/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA236.svg)](https://registry.platformio.org/libraries/robtillaart/INA236)


# INA236

Arduino library for the INA236, I2C, 16 bit, voltage, current and power sensor.


## Description

_This documentation is based upon the INA226 library, 
and may contain information not updated yet.
Please open an issue if needed._

**Experimental** library for the INA236 current and power sensor.  
Ported and updated from INA226 to INA236 by Josef Tremmel (thanks!).

Read datasheet for details.

==> **USE WITH CARE**

The INA236 is a voltage, current and power measurement device. 
A few important maxima, see datasheet, chapter 6.

|  description  |  max  |  unit  |  notes  |
|:--------------|------:|-------:|:--------|
| bus voltage   |  48   | Volt   |  unclear for how long.
| shunt voltage |  80   | mVolt  |  can be set to 20 mV.
| current       |  20   | Ampere |  ?? TODO check


### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)


### Related

- https://www.ti.com/product/INA236#tech-docs
- https://www.ti.com/product/INA236#params
- https://www.ti.com/document-viewer/INA236/datasheet
- https://github.com/RobTillaart/INA219  26 Volt, I2C, 12 bit
- https://github.com/RobTillaart/INA226  36 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA228  85 Volt, I2C, 20 bit
- https://github.com/RobTillaart/INA236  48 Volt, I2C, 16 bit
- https://github.com/RobTillaart/INA239  85 Volt, SPI, 16 bit
- https://github.com/RobTillaart/INA3221_RT  26 Volt, I2C, 13 bits (3 channel)
- https://www.adafruit.com/product/5832
- https://www.mateksys.com/?portfolio=i2c-ina-bm
- https://github.com/RobTillaart/printHelpers  (for scientific notation)


## I2C

### Address

The INA236 comes in two flavours, the INA236A and INA236B
with two disjunct address ranges.
Both can have 4 different I2C addresses, which depends on how 
the A0 address line is connected to the SCL, SDA, GND and VCC pins.

See table - from datasheet table 7.1, page 16.

|  A0   |  INA236A  |  HEX   |  INA236B  |  HEX   |
|:-----:|:---------:|:------:|:---------:|:------:|
|  GND  |     64    |  0x40  |     72    |  0x48  |
|  VS   |     65    |  0x41  |     73    |  0x49  |
|  SDA  |     66    |  0x42  |     74    |  0x4A  |
|  SCL  |     67    |  0x43  |     75    |  0x4B  |


### Performance

To be elaborated, example sketch available.

(From Datasheet 7.5.1)  
_The INA236 supports the transmission protocol for fast mode up to 
400 kHz and high-speed mode up to 2.94 MHz._


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

The example sketch **INA236_setMaxCurrentShunt.ino** switches between two calibration modes.
It shows the **INA266** sensor needs time to accommodate to this change. 
In practice you should call **setMaxCurrentShunt()** only once in **setup()**.

Also see INA226 issue 30 for another typical deviation problem.


## Interface

```cpp
#include "INA236.h"
```


### Constructor

- **INA236(const uint8_t address, TwoWire \*wire = Wire)** Constructor to set 
the address and optional Wire interface.
- **bool begin()** initializes the class.
returns true if the INA236 address is on the I2C bus.
Note: one needs to set **Wire.begin()** before calling **begin()**.
- **bool isConnected()** returns true if the INA236 address is on the I2C bus.
- **uint8_t getAddress()** returns the address set in the constructor.

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

### POWER

- **float getPower()** returns the current x BusVoltage in Watt.
- **float getWatt()**
- **float getMilliWatt()**
- **float getMicroWatt()**
- **float getKiloWatt()**


### Conversion Ready

Note the power and the current are not meaningful without calibrating the sensor.
Also the value is not meaningful if there is no shunt connected.

- **bool isConversionReady()** returns true if conversion ready flag is set.
- **bool waitConversionReady(uint32_t timeout = INA236_MAX_WAIT_MS)** 
active waiting for ready flag.
Polling for max timeout time, default 600 milliseconds, for wake up time.


### ADC conversion time

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


- **bool reset()** software power on reset. 
This implies calibration with **setMaxCurrentShunt()** needs to be redone.
Returns true upon success.
- **bool setBusVoltageConversionTime(uint8_t bvct = INA236_1100_us)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **uint8_t getBusVoltageConversionTime()** return the value set. 
Note the value returned is not a unit of time.
- **bool setShuntVoltageConversionTime(uint8_t svct = INA236_1100_us)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **uint8_t getShuntVoltageConversionTime()** return the value set. 
Note the value returned is not a unit of time.


|  enum description  | BVCT SVCT |   time    |  notes  |
|:------------------:|:---------:|:---------:|--------:|
|  INA236_140_us     |     0     |  140 us   |
|  INA236_204_us     |     1     |  204 us   |
|  INA236_332_us     |     2     |  332 us   |
|  INA236_588_us     |     3     |  588 us   |
|  INA236_1100_us    |     4     |  1.1 ms   |  default
|  INA236_2100_us    |     5     |  2.1 ms   |
|  INA236_4200_us    |     6     |  4.2 ms   |
|  INA236_8300_us    |     7     |  8.3 ms   |


- **bool setAverage(uint8_t avg = INA236_1_SAMPLE)** see table below.
(0 = default ==> 1 read), returns false if parameter > 7.
- **uint8_t getAverage()** returns the value set. See table below.
Note this is not the count of samples.

|  enum description    | value | # samples |  notes  |
|:--------------------:|:-----:|----------:|--------:|
|  INA236_1_SAMPLE     |   0   |      1    |  default
|  INA236_4_SAMPLES    |   1   |      4    |
|  INA236_16_SAMPLES   |   2   |     16    |
|  INA236_64_SAMPLES   |   3   |     64    |
|  INA236_128_SAMPLES  |   4   |    128    |
|  INA236_256_SAMPLES  |   5   |    256    |
|  INA236_512_SAMPLES  |   6   |    512    |
|  INA236_1024_SAMPLES |   7   |   1024    |


Note: times are typical, check datasheet for operational range.
(max is ~10% higher)

Note: total conversion time can take up to 1024 \* 8.3 ms ~ 10 seconds.


### ADCRange

The INA236 can set the ADC range to 20 mV (adcRange == true) 
or to 80 mV (adcRange == false) to optimize the accuracy.

- **bool setADCRange(bool flag)** The function sets the voltage/LSB,
flag = false => 81.92 mV, true => 20.48 mV
Since 0.1.3 setADCRange() calls setMaxCurrentShunt() to update the internal LSB values.
Returns false on failure of setMaxCurrentShunt().
- **uint8_t getADCRange()** returns set value.

Note: this function is not available on INA226.


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
See https://github.com/RobTillaart/INA236/pull/29 for details of the discussion.


### Error codes setMaxCurrentShunt

|  descriptive name error        |  value   |  meaning  |
|:-------------------------------|:--------:|:----------|
|  INA236_ERR_NONE               |  0x0000  |  OK
|  INA236_ERR_SHUNTVOLTAGE_HIGH  |  0x8000  |  maxCurrent \* shunt > 80 mV 
|  INA236_ERR_MAXCURRENT_LOW     |  0x8001  |  maxCurrent < 0.001
|  INA236_ERR_SHUNT_LOW          |  0x8002  |  shunt      < 0.001
|  INA236_ERR_NORMALIZE_FAILED   |  0x8003  |  not possible to normalize.


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
Returns true if write to register successful.
- **uint16_t getAlertFlag()** returns the mask set by **setAlertRegister()**.
- **bool setAlertLimit(uint16_t limit)** sets the limit that belongs to the chosen Alert Flag.
Returns true if write to register successful.
- **uint16_t getAlertLimit()** returns the limit set by **setAlertLimit()**.


|  description alert register  |  value   | a.k.a.  |
|:-----------------------------|:--------:| -------:|
|  INA236_SHUNT_OVER_VOLTAGE   |  0x8000  |  SOL    |
|  INA236_SHUNT_UNDER_VOLTAGE  |  0x4000  |  SUL    |
|  INA236_BUS_OVER_VOLTAGE     |  0x2000  |  BOL    |
|  INA236_BUS_UNDER_VOLTAGE    |  0x1000  |  BUL    |
|  INA236_POWER_OVER_LIMIT     |  0x0800  |  POL    |
|  INA236_CONVERSION_READY     |  0x0400  |         |


|  description alert flags         |  value   |
|:---------------------------------|:--------:|
|  INA236_ALERT_FUNCTION_FLAG      |  0x0010  |
|  INA236_CONVERSION_READY_FLAG    |  0x0008  |
|  INA236_MATH_OVERFLOW_FLAG       |  0x0004  |
|  INA236_ALERT_POLARITY_FLAG      |  0x0002  |
|  INA236_ALERT_LATCH_ENABLE_FLAG  |  0x0001  |


The alert line falls when alert is reached.


### Meta information

- **uint16_t getManufacturerID()** should return 0x5449.
- **uint16_t getDieID()** should return 0xA080.


### Debugging

- **uint16_t getRegister(uint8_t reg)** fetch registers directly, for debugging only.


### Error Handling

- **int getLastError()** returns last (I2C) error.


## Adjusting the range of the INA236

**use at own risk**
In issue #26 a hack is made to scale the INA236 to 300A by using a very small shunt.
The library has a minimal limit for the shunt of 0.001 ohm.
This limit can be overruled to support other ranges like the one discussed in #26.
Overruling can be done by patching the following value in the INA236.h file.

```cpp
#define INA236_MINIMAL_SHUNT             (0.001)
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

#### Should

#### Could


#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

