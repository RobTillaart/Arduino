
[![Arduino CI](https://github.com/RobTillaart/INA226/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/INA226/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/INA226.svg?maxAge=3600)](https://github.com/RobTillaart/INA226/releases)


# INA226

Arduino library for the INA226 power sensor


## Description

Experimental library for the INA226 power sensor.
Not all functionality is tested / investigated.

==> **USE WITH CARE**

The INA226 is a voltage, current and power measurement device. a few important maxima. (See datasheet, chapter 6)

|  description  |  max  |  unit  |
|:--------------|------:|-------:|
| bus voltage   |  36   | Volt   |
| shunt voltage |  80   | mVolt  |
| current       |  20   | Ampere | 


The sensor can have 16 different I2C addresses, which depends on how the A0 and A1 address lines are connected to the SCL, SDA, GND and VCC pins.

See datasheet - table 2 - datasheet.


## About Measurements

Calibration is mandatory to get **getCurrent()** and **getPower()** to work.

Some initial tests shows that the readings do not 100% add up. 
I expect this is caused by fluctuations in my power supply used and
more important that the ADC is multiplexed so there is time between the bus voltage measurement
and the shunt voltage measurement. If the current has changed a bit these values are not necessary 
in line.

Did some measurements with a load of 194 ohm and a shunt of 0.002 ohm that is a factor 10e5
Being on the edge of the sensitivity of the ADC measurements of current were up to ~9% too low.
Possible cause is that some math is done in 16 bit so numbers are truncated, not rounded.

(see issue #2) Sensors may have a different shunt resistor than the 0.002 I have. You should 
always check and verify what is on the shunt and even verify with a DMM that this value is correct.
With the calibration function **setMaxCurrentShunt()** one can just set the actual value and even
compensate slightly if readings are structural too low or too high.

I noted that the **getPower()** function does not always equal **getBusVoltage()** times **getCurrent()**
Cause is rounding/trunking maths and time of measurement.  You might prefer to multiply those values yourself 
to get extra digits. Please be aware that more digits is not always more exact (think significant digits)


## Interface

read datasheet for details


### Constructor

- **INA226(const int8_t address, TwoWire \*wire = Wire)** Constructor to set address and optional Wire interface.
- **bool begin(const uint8_t sda, const uint8_t scl)** for ESP32 and ESP8266;  initializes the class.
sets I2C pins. Returns true if the INA226 address is on the I2C bus.
- **bool begin()** UNO ea. initializes the class. 
returns true if the INA226 address is on the I2C bus.
- **bool isConnected()** returns true if the INA226 address is on the I2C bus.


### Core Functions

Note the power and the current are not meaningful without calibrating
the sensor. Also the value is not meaningful if there is no shunt connected.

- **float getShuntVoltage()** idem.
- **float getBusVoltage()** idem. Max 36 Volt.
- **float getCurrent()** is the current through the shunt in Ampere
- **float getPower()** is the current x BusVoltage in Watt
- **float getShuntVoltage_mV()** idem, in millivolts
- **float getCurrent_mA()** idem in milliAmpere
- **float getPower_mW()** idem in milliWatt


### Configuration

to be tested.

- **void reset()** software power on reset
- **bool setAverage(uint8_t avg = 0)** see table below
(0 = default ==> 1 read), returns false if parameter > 7
- **uint8_t getAverage()** returns the value set. Note this is not the count of samples.
- **bool setBusVoltageConversionTime(uint8_t bvct = 4)** see table below
(4 = default ==> 1.1 ms), returns false if parameter > 7
- **uint8_t getBusVoltageConversionTime()** return the value set. Note this is not a unit of time.
- **bool setShuntVoltageConversionTime(uint8_t svct = 4)** see table below
(4 = default ==> 1.1 ms), returns false if parameter > 7
- **uint8_t getShuntVoltageConversionTime()** return the value set. Note this is not a unit of time.


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


Note that total conversion time can take up to 1024 \* 8.3 ms ~ 10 seconds.


### Calibration

See datasheet

Calibration is mandatory to get **getCurrent()** and **getPower()** to work.

- **bool setMaxCurrentShunt(float ampere = 20.0, float ohm = 0.002, bool normalize = true)** set the calibration register based upon the shunt and the max ampere. From this the LSB is derived. Note the function will round up the LSB to nearest round value by default. This may cause loss of precision.
- **float getCurrentLSB()** returns the LSB == precision of the calibration


### Operating mode

See datasheet, partially tested.

Mode = 4 is not used, is also a **shutdown()** unknown if there is a difference.

- **bool setMode(uint8_t mode = 7)** mode = 0 .. 7
- **bool shutDown()** mode 0 - not tested yet
- **bool setModeShuntTrigger()** mode 1 - not tested yet - how to trigger to be investigated
- **bool setModeBusTrigger()** mode 2 - not tested yet -
- **bool setModeShuntBusTrigger()** mode 3 - not tested yet -
- **bool setModeShuntContinuous()** mode 5
- **bool setModeBusContinuous()** mode 6
- **bool setModeShuntBusContinuous()** mode 7 - default
- **uint8_t getMode()** returns the mode (0..7) set by one of the functions above.


### Alert functions

See datasheet, not tested yet.

- **void setAlertRegister(uint16_t mask)** by setting the mask one of five an over- or underflow can be detected. Another feature that can be set is the conversion ready flag.
- **uint16_t getAlertFlag()** returns the mask set by **setAlertRegister()**
- **void setAlertLimit(uint16_t limit)** sets the limit that belongs to the chosen Alert Flag
- **uint16_t getAlertLimit()** returns the limit set by **setAlertLimit()**


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


### Meta information

- **uint16_t getManufacturerID()** should return 0x5449
- **uint16_t getDieID()** should return 0x2260


## Operational

See examples.. 


## TODO

- test different loads (low edge)
- test unit tests
- test examples
- investigate alert functions / interface
- improve readme.md
- disconnected load, can it be recognized?
- **lastError()** do we need this...
- cache configuration ? ==> 2 bytes
- getCurrentLSB_mA()
- bool isCalibrated()


