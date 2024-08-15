
[![Arduino CI](https://github.com/RobTillaart/INA3221_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/INA3221_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/INA3221_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/INA3221_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/INA3221_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/INA3221_RT.svg)](https://github.com/RobTillaart/INA3221_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA3221_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA3221_RT.svg?maxAge=3600)](https://github.com/RobTillaart/INA3221_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/INA3221.svg)](https://registry.platformio.org/libraries/robtillaart/INA3221)


# INA3221

Arduino library for the I2C INA3221 3 channel voltage and current sensor.


## Description

**Experimental** library for the I2C INA3221. ==> **USE WITH CARE**

The INA3221 is a 3 channel measuring device to measure voltage.
Derived from that voltage and a given shunt, the library calculates current (amperes)
and power (watts).

The measurements runs in the background processing the two voltages per channel.
(continuous mode assumed). When a measurement is ready the measured value is stored
in the appropriate (channel) register. Then the next channel / voltage is measured.
As channels can be disabled, the timing of processing / updates per channels might differ.

The core functions read from the (channel) registers, so they are never blocked.
They can however return the same value if no new data is available yet.

Some important maxima, see datasheet for all details.

|  description  |  max   |  unit  |  notes  |
|:--------------|-------:|-------:|:--------|
| channels      |  3     |        |
| bus voltage   |  26    | Volt   |  unclear for how long.
| shunt voltage |  163   | mVolt  |  at 0.1 Ohm
| shunt R       |  100   | mOhm   |  typical
| current       |  1.63  | Ampere |  I = U/R


#### 0.3.0 breaking changes.

Renamed setCriticalCurrect() ==> setCriticalCurrent() to fix typo.


#### 0.2.0 breaking changes.

Several functions have been reimplemented after issue #2.
This makes pre 0.2.0 versions obsolete.


#### Test

==> **USE WITH CARE**

Only tested partially with an Arduino UNO.

Not all functionality is tested and investigated with hardware.

Another point to be tested and verified is negative values in registers.

Read datasheet for details.

As always feedback is welcome, please open an issue on GitHub.


#### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)


#### Related

- https://github.com/RobTillaart/INA219
- https://github.com/RobTillaart/INA226
- https://github.com/RobTillaart/INA228
- https://github.com/RobTillaart/INA3221_RT



## I2C

#### Address

The sensor can have 4 different I2C addresses, which depends on how
the A0 address line is connected to the SCL, SDA, GND and VCC pins.

|  A0   |  DEC  |  HEX   |  Notes  |
|:-----:|:-----:|:------:|:------:|
|  GND  |   64  |  0x40  |  not connected seems to choose this one too.
|  VS   |   65  |  0x41  |
|  SDA  |   66  |  0x42  |
|  SCL  |   67  |  0x43  |

See datasheet - table 1, page 20 - datasheet.


#### Performance

(From Datasheet)
_The INA3221 supports the transmission protocol for fast mode (1 kHz to 400 kHz)
and high-speed mode (1 kHz to 2.94 MHz).
All data bytes are transmitted most significant byte first._


(timing in us, Arduino UNO),  
indicative by example INA3221_performance.ino  
Four most important calls.

|  Clock   |  bus V  |  shunt V  |   mA  |   mW   |
|:--------:|:-------:|:---------:|:-----:|:------:|
|  100000  |   568   |    568    |  584  |  1152  |
|  100000  |   324   |    328    |  340  |   672  |
|  100000  |   236   |    236    |  260  |   504  |
|  100000  |   200   |    200    |  220  |   428  |


## Interface

```cpp
#include "INA3221.h"
```

All parameters channels are zero based => so numbered 0 , 1 or 2.
Using channels > 2 are not handled (correctly).

### Constructor

- **INA3221(const uint8_t address, TwoWire \*wire = Wire)** Constructor to set
the address and optional Wire interface.
- **bool begin()** initializes the class.
returns true if the INA3221 address is valid and on the I2C bus.
Note: one needs to set **Wire.begin()** before calling **begin()**.
- **bool isConnected()** returns true if the INA3221 address is valid and on the I2C bus.
- **uint8_t getAddress()** returns the address set in the constructor.


### Core Functions

Note the power and the current are not meaningful without calibrating the sensor.
Also the value is not meaningful if there is no shunt connected.

The parameter **channel** should always be 0..2

- **float getBusVoltage(uint8_t channel)** idem. in volts. Max 26 Volt.
- **float getShuntVoltage(uint8_t channel)** idem, in volts.
- **float getCurrent(uint8_t channel)** is the current through the shunt in Ampere.
- **float getPower(uint8_t channel)** is the current x BusVoltage in Watt.

The library has wrapper functions to convert above output to a more appropriate scale of units.

Wrapper functions for the milli scale.

- **float getBusVoltage_mV(uint8_t channel)** idem, in milliVolts.
- **float getShuntVoltage_mV(uint8_t channel)** idem, in milliVolts.
- **float getCurrent_mA(uint8_t channel)** idem, in milliAmpere.
- **float getPower_mW(uint8_t channel)** idem, in milliWatt.

Wrapper functions for the micro scale.

- **float getBusVoltage_uV(uint8_t channel)** idem, in microVolts.
- **float getShuntVoltage_uV(uint8_t channel)** idem, in microVolts.
- **float getCurrent_uA(uint8_t channel)** idem, in microAmpere.
- **float getPower_uW(uint8_t channel)** idem, in microWatt.


### Shunt Resistor

The shunt resistor is typical in the order of 0.100 Ohm.

- **int setShuntR(uint8_t channel, float ohm)** sets value in Ohm.
- **float getShuntR(uint8_t channel)** returns value in Ohm.


### Shunt Alerts, warning and critical

(not tested)
Read datasheet!

The user is responsible to be sure that the critical value >= warning value
if he decides to use both.
If only one of the two is used, critical might be less than warning.

The parameter **channel** should always be 0..2

The parameter **microVolt** should not exceed 163800 µV, will return error -2.
NOTE: LSB = 40 uV so microVolt should be >= 40uV

- **int setCriticalAlert(uint8_t channel, uint32_t microVolt)**
sets the critical alert level in microvolts.
- **uint32_t getCriticalAlert(uint8_t channel)** returns microVolt
- **int setWarningAlert(uint8_t channel, uint32_t microVolt)**
sets the warning alert level in microvolts.
- **uint32_t getWarningAlert(uint8_t channel)** returns microVolt

Wrappers using milliAmpere (assuming Shunt is set correctly!).
These are often more intuitive from user perspective.
NOTE: LSB = 40 uV so milliAmpere should be >= 0.4 mA (assume Shunt = 0.1 Ohm)

- **int setCriticalCurrent(uint8_t channel, float milliAmpere)**
sets the critical alert level in milliAmpere.
- **float getCriticalCurrent(uint8_t channel)** returns milliAmpere
- **int setWarningCurrent(uint8_t channel, float milliAmpere)**
sets the warning alert level in milliAmpere.
- **float getWarningCurrent(uint8_t channel)** returns milliAmpere


### Shunt voltage sum

(not tested)
Read datasheet!

- **int16_t getShuntVoltageSum()** returns microVolt
- **int setShuntVoltageSumLimit(int16_t microVolt)** idem.
- **int16_t getShuntVoltageSumLimit()** returns set value in microVolt.


### Configuration

(partially tested)
Read datasheet for bit pattern of the mask.

Setting all bits at once with a mask is faster, atomic and uses less code.

- **int setConfiguration(uint16_t mask = 0x7127)**  0x7127 = power on default.
- **uint16_t getConfiguration()** returns bit mask.

The library also provides getters and setters per field.

- **int reset()** triggers software power on reset.
- **int enableChannel(uint8_t channel)** add a channel to the background measurements loop.
- **int disableChannel(uint8_t channel)** remove a channel to the background measurements loop.
- **int getEnableChannel(uint8_t channel)** check if a channel is enabled.
- **int setAverage(uint8_t avg = 0)** see table below.
(0 = default ==> 1 read), returns false if parameter > 7.
- **int getAverage()** returns the value set. See table below.
Note this is not the count of samples.


| Average | # samples |  notes  |
|:-------:|----------:|--------:|
|    0    |      1    | default |
|    1    |      4    |         |
|    2    |     16    |         |
|    3    |     64    |         |
|    4    |    128    |         |
|    5    |    256    |         |
|    6    |    512    |         |
|    7    |   1024    |         |


- **int setBusVoltageConversionTime(uint8_t bvct = 4)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **int getBusVoltageConversionTime()** return the value set.
Note the value returned is not a unit of time.
- **int setShuntVoltageConversionTime(uint8_t svct = 4)** see table below.
(4 = default ==> 1.1 ms), returns false if parameter > 7.
- **int getShuntVoltageConversionTime()** return the value set.
Note the value returned is not a unit of time.


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
(max can be ~10% higher)

Note: In combination with average the total conversion time can take up to
1024 x 8.3 ms almost 9 seconds (+ 10% deviation ==> 10 seconds)


### Operating mode

(not tested)
See datasheet!

Mode = 4 is not used, is also a **shutdown()** unknown if there is a difference with mode == 0.
The underlying bit pattern (not used).

|  bit  |  value  |  description  |
|:-----:|:-------:|:--------------|
|   0   |   0x01  |  shunt bit on (0x01) / off (0x00)
|   1   |   0x02  |  bus bit on (0x02) / off (0x00)
|   2   |   0x04  |  continuous (0x04) / one shot (0x00) bit.

- **int setMode(uint8_t mode = 7)** mode = 0..7. Default = 7 ==> ShuntBusContinuous mode.
- **int getMode()** returns the mode (0..7).

Descriptive mode functions (convenience wrappers).

- **int shutDown()** mode 0
- **int setModeShuntTrigger()** mode 1
- **int setModeBusTrigger()** mode 2
- **int setModeShuntBusTrigger()** mode 3
- **int setModeShuntContinuous()** mode 5
- **int setModeBusContinuous()** mode 6
- **int setModeShuntBusContinuous()** mode 7 - default - (only one tested)


### Mask / enable register

(not tested)
See datasheet!

Setting all bits at once with a mask is faster, atomic and uses less code.

- **int setMaskEnable(uint16_t mask)**
- **uint16_t getMaskEnable()**

TODO: convenience wrappers
- 9 x setters
- 9 x getters


### Power Limit

(not tested)
See datasheet!

To guard the BUS voltage, max value 32760

- **int setPowerUpperLimit(int16_t milliVolt)**
- **int16_t getPowerUpperLimit()**
- **int setPowerLowerLimit(int16_t milliVolt)**
- **int16_t getPowerLowerLimit()**


### Meta information

(tested)

- **uint16_t getManufacturerID()** should return 0x5449, mine returns 0x5449.
- **uint16_t getDieID()** should return 0x2260, mine returns 0x3220.


### Debugging

- **uint16_t getRegister(uint8_t reg)** fetch registers directly, for debugging only.
- **uint16_t putRegister(uint8_t reg, uint16_t value)** load registers directly, for debugging only.


## Future


#### Must

- update documentation.
  - return values
- test all functionality
  - negative values = two complements - does it work?


#### Should

- keep in sync with INA219/226 where possible.


#### Could

- convenience wrappers MASK/ENABLE register.
  - 9 x getters  9 x setters (quite a lot)
- error handling / documentation
- clean up magic numbers in the code (e.g. 40 uV and 8 mV)
  - comments?


#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

