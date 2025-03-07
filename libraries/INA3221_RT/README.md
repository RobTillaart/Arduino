
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

**Experimental** **USE WITH CARE**

The INA3221 is a 3 channel voltage and current sensor, which work with I2C.

The INA3221 is a 3 channel measuring device to measure voltage.
Derived from that voltage and a given shunt, the library calculates current (amperes)
and power (watts).

The measurements runs in the background processing the two voltages per channel.
(continuous mode assumed). When a measurement is ready the measured value is stored
in the appropriate (channel) register. Then the next channel / voltage is measured.
As channels can be disabled, the timing of processing / updates per channels might differ.

The core functions read directly the last measurement from the (channel) registers, 
so they are never blocked.
They can however return the same value if no new measurement is available yet.

Some important maxima, see datasheet for all details.

|  description  |  max   |  unit  |  notes  |
|:--------------|-------:|-------:|:--------|
| channels      |     3  |        |
| bus voltage   |    26  |   Volt |  unclear for how long.
| shunt voltage |   163  |  mVolt |  at 0.1 Ohm
| shunt R       |   100  |   mOhm |  typical
| current       |  1.63  | Ampere |  I = U/R


### 0.4.0 breaking changes.

Fix #8, configuration functions were not working.

### 0.3.0 breaking changes.

Renamed setCriticalCurrect() ==> setCriticalCurrent() to fix typo.

### 0.2.0 breaking changes.

Several functions have been reimplemented after issue #2.
This makes pre 0.2.0 versions obsolete.


### Tests

Still experimental so use with care.

The library is only tested partially with an Arduino UNO.
So not all functionality is tested and verified with hardware yet. 
This is an ongoing process.

One point of attention to be tested and verified is the behaviour 
around negative values in registers.

As always feedback is welcome, please open an issue on GitHub.


### Special characters

- Ω == Ohm = ALT-234 (Windows)
- µ == micro = ALT-0181 (Windows)


### Related

- https://www.ti.com/product/INA3221#tech-docs
- https://www.ti.com/product/INA3221#params
- https://www.ti.com/document-viewer/INA3221/datasheet
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

The INA3221 sensor can have 4 different I2C addresses, depending on how
the A0 address line is connected, to the SCL, SDA, GND or VCC pin.

|  A0   |  DEC  |  HEX   |  Notes  |
|:-----:|:-----:|:------:|:-------:|
|  GND  |   64  |  0x40  |  A0 not connected seems to choose this one too.
|  VS   |   65  |  0x41  |
|  SDA  |   66  |  0x42  |
|  SCL  |   67  |  0x43  |

See datasheet - table 1 + page 20


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


### Performance

(From Datasheet)
_The INA3221 supports the transmission protocol for fast mode (1 kHz to 400 kHz)
and high-speed mode (1 kHz to 2.94 MHz).
All data bytes are transmitted most significant byte first._


(timing in us, Arduino UNO, lib version 0.2.0),  
indicative timing by example INA3221_performance.ino  

Four most important calls.

|  version  |  clock   |  bus V  |  shunt V  |   mA  |   mW   |
|:---------:|:--------:|:-------:|:---------:|:-----:|:------:|
|   0.2.0   |  100000  |   564   |    564    |  612  |  1196  |
|   0.2.0   |  200000  |   320   |    328    |  372  |   720  |
|   0.2.0   |  300000  |   240   |    236    |  288  |   552  |
|   0.2.0   |  400000  |   204   |    204    |  252  |   472  |


## Interface

```cpp
#include "INA3221.h"
```

All parameters channels are zero based => so numbered 0 , 1 or 2.
Using channels > 2 are not handled (correctly).

### Constructor

- **INA3221(uint8_t address, TwoWire \*wire = Wire)** Constructor to set
the address and optional Wire interface.
- **bool begin()** initializes the class.
Returns true if the INA3221 address is valid and on the I2C bus.
Note: one needs to set **Wire.begin()** before calling **begin()**.
- **bool isConnected()** returns true if the INA3221 address is valid and on the I2C bus.
- **uint8_t getAddress()** returns the I2C address set in the constructor.


### Core Functions

Note the power and the current are not meaningful without calibrating the sensor.
Also the value is not meaningful if there is no shunt connected.

The parameter **channel** should always be 0..2. 
The functions return -1 if channel is out of range.

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


### Average

Datasheet, section 8.4.1

The average does not make multiple measurements and then return the average, 
one should think of it as a low pass filter that reduces noise.

in code:
```cpp
value = value + (measurement - value) * (1/samples);

e.g. (1/samples) == (1/128) 
```

The higher the average number of samples the less noise you have. 
Higher values for average cause the measurements take more time to stabilize.
Therefor it reacts slower on changes in voltage and current. 
So choose the level of averaging with care.


- **int setAverage(uint16_t avg = 0)** see table below.
(avg 0 = default ==> 1 read)
  - return 0 is OK.
  - return -10 if parameter > 7.
  - other is I2C error.
- **uint16_t getAverage()** returns the value set. See table below.
Note this is not the count of samples.


| Average | # samples |  notes  |
|:-------:|----------:|--------:|
|    0    |       1   | default |
|    1    |       4   |         |
|    2    |      16   |         |
|    3    |      64   |         |
|    4    |     128   |         |
|    5    |     256   |         |
|    6    |     512   |         |
|    7    |    1024   |         |


### Conversion time

- **int setBusVoltageConversionTime(uint16_t bvct = 4)** see table below.
(4 = default ==> 1.1 ms), 
  - return 0 is OK.
  - return -10 if parameter > 7.
  - other is I2C error.
- **uint16_t getBusVoltageConversionTime()** return the value set 0..7.
See table below. Note the value returned is not a unit of time.
- **int setShuntVoltageConversionTime(uint16_t svct = 4)** see table below.
(4 = default ==> 1.1 ms), 
  - return 0 is OK.
  - return -10 if parameter > 7.
  - other is I2C error.
- **uint16_t getShuntVoltageConversionTime()** return the value set 0..7.
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
The maximum time can be up to ~10% higher than typical!


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

- **int setMode(uint16_t mode = 7)** mode = 0..7. Default = 7 ==> ShuntBusContinuous mode.
  - return 0 is OK.
  - return -10 if parameter > 7.
  - other is I2C error.
- **uint16_t getMode()** returns the mode (0..7).

Descriptive mode functions (convenience wrappers).
These have the same return value as **setMode()**.

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
  - return 0 is OK.
  - other is I2C error.
- **uint16_t getMaskEnable()**


### Power Limit

(not tested)
See datasheet!

To guard the BUS voltage, max value 32760

- **int setPowerUpperLimit(int16_t milliVolt)**
  - return 0 is OK.
  - other is I2C error.
- **int16_t getPowerUpperLimit()** returns limit in mV.
- **int setPowerLowerLimit(int16_t milliVolt)**
  - return 0 is OK.
  - other is I2C error.
- **int16_t getPowerLowerLimit()** returns limit in mV.


### Meta information

(tested)

- **uint16_t getManufacturerID()** should return 0x5449, mine returns 0x5449.
- **uint16_t getDieID()** should return 0x2260, mine returns 0x3220.

If your device returns other ManufacturerID or DieID, please let me know.


### Debugging

- **uint16_t getRegister(uint8_t reg)** fetch registers directly, for debugging only.
- **uint16_t putRegister(uint8_t reg, uint16_t value)** load registers directly, for debugging only.


### Error Handling

- **int getLastError()** returns last (I2C) error.


## Future


#### Must

- update documentation.
  - return values
- test all functionality
  - negative values = two complements - does it work?


#### Should

- keep in sync with INA219/226 where possible.
- run performance test with 0.4.x
- do error codes conflict with results (negative nrs. 
  - getBusVoltage() returns -1 to indicate channel error.
    would be a problem if VBus can be < 0. Others idem.
- error handling
  - parameter error
  - I2C error
  - documentation
- add table of bitfields for **setMaskEnable()** register

#### Could

- convenience wrappers MASK/ENABLE register.
  - 9 x getters  9 x setters (quite a lot)
- clean up magic numbers in the code (e.g. 40 uV and 8 mV)
  - comments?


#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

