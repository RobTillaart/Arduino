
[![Arduino CI](https://github.com/RobTillaart/INA226/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA226/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA226/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA226/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA226/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA226/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA226.svg?maxAge=3600)](https://github.com/RobTillaart/INA226/releases)


# INA226

Arduino library for the INA226 power sensor.


## Description

**Experimental** library for the INA226 power sensor.
Not all functionality is tested / investigated.

Read datasheet for details.

==> **USE WITH CARE**

The INA226 is a voltage, current and power measurement device. 
A few important maxima, see datasheet, chapter 6.

|  description  |  max  |  unit  | notes |
|:--------------|------:|-------:|:------|
| bus voltage   |  36   | Volt   | unclear for how long.
| shunt voltage |  80   | mVolt  |
| current       |  20   | Ampere | 


#### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)


#### Links

Relates to https://github.com/RobTillaart/INA219


## I2C

#### Address

The sensor can have 16 different I2C addresses, 
which depends on how the A0 and A1 address lines 
are connected to the SCL, SDA, GND and VCC pins.

See datasheet - table 2 - datasheet.


#### Performance

To be elaborated, example sketch available.


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

The example sketch **INA226_setMaxCurrentShunt.ino** switches between two calibration modes.
It shows the **INA266** sensor needs time to accommodate to this change. 
In practice you should call **setMaxCurrentShunt()** only once in **setup()**.


## Interface

```cpp
#include "INA226.h"
```


#### Constructor

- **INA226(const uint8_t address, TwoWire \*wire = Wire)** Constructor to set 
the address and optional Wire interface.
- **bool begin(const uint8_t sda, const uint8_t scl)** for ESP32 and ESP8266;  
initializes the class. Sets I2C pins. 
Returns true if the INA226 address is on the I2C bus.
- **bool begin()** UNO ea. initializes the class.
returns true if the INA226 address is on the I2C bus.
- **bool isConnected()** returns true if the INA226 address is on the I2C bus.
- **uint8_t getAddress()** returns the address set in the constructor.


#### Core Functions

Note the power and the current are not meaningful without calibrating the sensor.
Also the value is not meaningful if there is no shunt connected.

- **float getShuntVoltage()** idem, in volts.
- **float getBusVoltage()** idem. in volts. Max 36 Volt.
- **float getCurrent()** is the current through the shunt in Ampere.
- **float getPower()** is the current x BusVoltage in Watt.

Helper functions for the milli scale.

- **float getBusVoltage_mV()** idem, in milliVolts.
- **float getShuntVoltage_mV()** idem, in milliVolts.
- **float getCurrent_mA()** idem, in milliAmpere.
- **float getPower_mW()** idem, in milliWatt.

Helper functions for the micro scale.

- **float getBusVoltage_mV()** idem, in microVolts.
- **float getShuntVoltage_uV()** idem, in microVolts.
- **float getCurrent_uA()** idem, in microAmpere.
- **float getPower_uW()** idem, in microWatt.


#### Configuration

Note: the conversion time runs in the background and if done value is stored in a register. 
The core functions read from the registers, so they are not blocked.
They return the same value if no new data is available / ready.

- **void reset()** software power on reset. 
This implies calibration with **setMaxCurrentShunt()** needs to be redone.
- **bool setAverage(uint8_t avg = 0)** see table below.
(0 = default ==> 1 read), returns false if parameter > 7.
- **uint8_t getAverage()** returns the value set. See table below.
Note this is not the count of samples.
- **bool setBusVoltageConversionTime(uint8_t bvct = 4)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **uint8_t getBusVoltageConversionTime()** return the value set. 
Note the value returned is not a unit of time.
- **bool setShuntVoltageConversionTime(uint8_t svct = 4)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **uint8_t getShuntVoltageConversionTime()** return the value set. 
Note the value returned is not a unit of time.


| Average | # samples |  notes  |
|:-------:|----------:|--------:|
|  0      |      1    | default |
|  1      |      4    |         |
|  2      |     16    |         |
|  3      |     64    |         |
|  4      |    128    |         |
|  5      |    256    |         |
|  6      |    512    |         |
|  7      |   1024    |         |



| BVCT SVCT |   time    |  notes  |
|:---------:|----------:|--------:|
|    0      |  140 us   |
|    1      |  204 us   |
|    2      |  332 us   |
|    3      |  588 us   |
|    4      |  1.1 ms   | default |
|    5      |  2.1 ms   |
|    6      |  4.2 ms   |
|    7      |  8.3 ms   |

Note: times are typical, check datasheet for operational range.
(max is ~10% higher)

Note: total conversion time can take up to 1024 \* 8.3 ms ~ 10 seconds.


#### Calibration

See datasheet.

Calibration is mandatory to get **getCurrent()** and **getPower()** to work.

- **int setMaxCurrentShunt(float ampere = 20.0, float ohm = 0.002, bool normalize = true)** 
set the calibration register based upon the shunt and the max Ampere. 
From this the LSB is derived.
The function may force normalization if underflow is detected.
Returns Error code, see below.
- **bool isCalibrated()** returns true if CurrentLSB has been calculated by **setMaxCurrentShunt()**.
Value should not be zero.
- **float getCurrentLSB()** returns the LSB in Ampere == precision of the calibration.
- **float getCurrentLSB_mA()** returns the LSB in milliAmpere.
- **float getCurrentLSB_uA()** returns the LSB in microAmpere.
- **float getShunt()** returns the value set for the shunt in ohm.
- **float getMaxCurrent()** returns the value for the maxCurrent which can be corrected.

To print these values in scientific notation use https://github.com/RobTillaart/printHelpers 


#### About normalization

**setMaxCurrentShunt()** will round the LSB to nearest round value (typical 0.001) by default (normalize == true). 
- The user **must** check the return value == 0x000, otherwise the calibration register is **not** set.
- Normalization typically gives smaller steps => improve precision
- Normalization can cause that the maxCurrent passed cannot be reached any more.
Solution is not to normalize if this max range is needed. 


#### Error codes setMaxCurrentShunt

| descriptive name error        |  value   |  meaning  |
|:------------------------------|---------:|:----------|
| INA226_ERR_NONE               |  0x0000  | OK
| INA226_ERR_SHUNTVOLTAGE_HIGH  |  0x8000  | maxCurrent \* shunt > 80 mV 
| INA226_ERR_MAXCURRENT_LOW     |  0x8001  | maxCurrent < 0.001
| INA226_ERR_SHUNT_LOW          |  0x8002  | shunt      < 0.001


#### Operating mode

See datasheet, partially tested.

Mode = 4 is not used, is also a **shutdown()** unknown if there is a difference with mode == 0.

- **bool setMode(uint8_t mode = 7)** mode = 0 .. 7
- **bool shutDown()** mode 0 - not tested yet
- **bool setModeShuntTrigger()** mode 1 - not tested yet - how to trigger to be investigated
- **bool setModeBusTrigger()** mode 2 - not tested yet
- **bool setModeShuntBusTrigger()** mode 3 - not tested yet
- **bool setModeShuntContinuous()** mode 5
- **bool setModeBusContinuous()** mode 6
- **bool setModeShuntBusContinuous()** mode 7 - default.
- **uint8_t getMode()** returns the mode (0..7) set by one of the functions above.


#### Alert functions

See datasheet, not tested yet.

- **void setAlertRegister(uint16_t mask)** by setting the mask 
one of five types of over- or underflow can be detected. 
Another feature that can be set is the conversion ready flag.
- **uint16_t getAlertFlag()** returns the mask set by **setAlertRegister()**.
- **void setAlertLimit(uint16_t limit)** sets the limit that belongs to the chosen Alert Flag
- **uint16_t getAlertLimit()** returns the limit set by **setAlertLimit()**.


| description alert register | value  | a.k.a.  |
|:---------------------------|-------:| -------:|
| INA226_SHUNT_OVER_VOLTAGE  | 0x8000 |  SOL    |
| INA226_SHUNT_UNDER_VOLTAGE | 0x4000 |  SUL    |
| INA226_BUS_OVER_VOLTAGE    | 0x2000 |  BOL    |
| INA226_BUS_UNDER_VOLTAGE   | 0x1000 |  BUL    |
| INA226_POWER_OVER_LIMIT    | 0x0800 |  POL    |
| INA226_CONVERSION_READY    | 0x0400 |         |


| description alert flags        | value  |
|:-------------------------------|-------:|
| INA226_ALERT_FUNCTION_FLAG     | 0x0010 |
| INA226_CONVERSION_READY_FLAG   | 0x0008 |
| INA226_MATH_OVERFLOW_FLAG      | 0x0004 |
| INA226_ALERT_POLARITY_FLAG     | 0x0002 |
| INA226_ALERT_LATCH_ENABLE_FLAG | 0x0001 |


The alert line falls when alert is reached.


#### Meta information

- **uint16_t getManufacturerID()** should return 0x5449
- **uint16_t getDieID()** should return 0x2260


#### debugging

- **uint16_t getRegister(uint8_t reg)** fetch registers directly, for debugging only.


## Adjusting the range of the INA226

**use at own risk**
In issue #26 a hack is made to scale the INA226 to 300A by using a very small shunt.
The library has a minimal limit for the shunt of 0.001 ohm.
This limit can be overruled to support other ranges like the one discussed in #26.
Overruling can be done by patching the following value in the INA226.h file.

```cpp
#define INA226_MINIMAL_SHUNT             (0.001)
```

Be aware that
- **you should NOT do this unless you understand the implications**.
- you do this at your own risk.
- the resistance of wires used affect measurements with very small shunts.
- solder might change the resistance too.
- you do this at your own risk.


## Operational

See examples.. 


## Future


#### Must


#### Should

- test different loads (low edge).
- test examples.
- investigate alert functions / interface.
- disconnected load.
  - can it be recognized? => current drop?


#### Could

- make defines of "magic" numbers
  - const floats (most used only once)
- default address 0x40 ?


#### Won't

- **lastError()** do we need this?
  - no
- if **BVCT SVCT** is set to 6 or 7
  - does the long timing affects RTOS? ==> yield()
  - wait for issue
- expand unit tests possible?
  - need virtual device => too much work
- cache configuration ? ==> 2 bytes.
  - what is gained? updates are faster. footprint code?
  - how often operational?
  - 15 times used..
- can the calibration math be optimized?
  - integer only?
  - less iterations?
  - would cause rounding errors
  

## Resources

- [TI - INA226 Details](https://www.ti.com/product/INA226#params)
- [TI - INA226 datasheet](https://www.ti.com/document-viewer/INA226/datasheet)

