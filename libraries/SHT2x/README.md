
[![Arduino CI](https://github.com/robtillaart/SHT2x/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![JSON check](https://github.com/RobTillaart/SHT2x/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SHT2x/actions/workflows/jsoncheck.yml)
[![Arduino-lint](https://github.com/RobTillaart/SHT2x/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SHT2x/actions/workflows/arduino-lint.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SHT2x/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SHT2x.svg?maxAge=3600)](https://github.com/RobTillaart/SHT2x/releases)


# SHT2x

Arduino library for the SHT2x, HTU2x and Si70xx temperature and humidity sensors.


## Description

This library is not tested extensively yet. 
It should work for SHT20, SHT21 and SHT25 but these are not tested yet.
The SHT2x family of sensors should work up to 400 KHz I2C.

Furthermore there are a number of compatible sensors, these are not tested either.

Accuracy table

| Sensor  | Temperature | Humidity | Notes  |
|:-------:|:-----------:|:--------:|:-------|
| SHT20   |   ~0.3      |  ±3.0    |        |
| SHT21   |   ~0.3      |  ±3.0    |        |
| SHT25   |   ~0.3      |  ±1.8    |        |
| HTU20   |             |          |  to-do |
| HTU21   |             |          |  to-do |
| Si7013  |             |          |  to-do |
| Si7020  |             |          |  to-do |
| Si7021  |             |          |  to-do |


All sensors in this family of sensors have address 0x40 (64 decimal).
If you want to use more on one I2C bus one needs either an I2C multiplexer
or one should switch sensors on/off like the select in SPI communication.


## Interface

### Constructors

All classes below are derived from SHT2x class.

- **SHT2x()** constructor base class.
- **SHT20()** constructor.
- **SHT21()** constructor.
- **SHT25()** constructor.
- **HTU20()** constructor.
- **HTU21()** constructor.
- **Si7013()** constructor.
- **Si7020()** constructor.
- **Si7021()** constructor.


### Base interface

- **bool begin(int dataPin, int clockPin)** begin function for ESP8266 & ESP32;
returns false if device address is incorrect or device cannot be reset.
- **bool begin(TwoWire \*wire = &Wire)** optional set the wire interface 
for platforms with multiple I2C buses. **begin()** calls **reset()** which can take up to 15 ms. 
- **bool read()** Reads both the temperature and humidity.  
Initial release has a blocking delay. 
- **bool isConnected()** check if sensor is reachable over I2C. Returns false if not connected.
- **uint16_t getStatus()** returns a 2 bit status. See Status fields below.
- **uint32_t lastRead()** in milliSeconds since start of program.
- **bool reset()** resets the sensor, soft reset, no hard reset supported.
- **float getHumidity()** computes the relative humidity in % based off the latest raw reading, and returns it.
- **float getTemperature()** computes the temperature in °C based off the latest raw reading, and returns it.
- **uint16_t getRawHumidity()** returns the raw two-byte representation of humidity directly from the sensor.
- **uint16_t getRawTemperature()** returns the raw two-byte representation of temperature directly from the sensor.

Note that the temperature and humidity values are recalculated on every call to getHumidity() and getTemperature(). 
If you're worried about the extra cycles, you should make sure to cache these values or only request them 
after you've performed a new **read()**.

Note: The raw temperature and raw humidity are ideal to minimize storage or to minimize communication.


### Error interface

- **int getError()** returns last set error flag and clear it. 
Be sure to clear the error flag by calling **getError()** before calling any command as the error flag could be from a previous command.

| Value  | Symbolic                  | Description                 | Notes    |
|:------:|:--------------------------|:----------------------------|:---------|
|  0x00  | SHT2x_OK                  | no error                    |          |
|  0x81  | SHT2x_ERR_WRITECMD        | I2C write failed            |          |
|  0x82  | SHT2x_ERR_READBYTES       | I2C read failed             |          |
|  0x83  | SHT2x_ERR_HEATER_OFF      | Could not switch off heater |          |
|  0x84  | SHT2x_ERR_NOT_CONNECT     | Could not connect           |          |
|  0x85  | SHT2x_ERR_CRC_TEMP        | CRC error in temperature    |          |
|  0x86  | SHT2x_ERR_CRC_HUM         | CRC error in humidity       |          |
|  0x87  | SHT2x_ERR_CRC_STATUS      | CRC error in status field   | not used |
|  0x88  | SHT2x_ERR_HEATER_COOLDOWN | Heater need to cool down    |          |
|  0x88  | SHT2x_ERR_HEATER_ON       | Could not switch on heater  |          |

Note: the HTU20 / HTU21 classes share the same error codes.


### Heater interface

**WARNING:** Do not use heater for long periods.  
Datasheet SHT2x does not mention max time so the maximum time of the SHT3x series is assumed here.

Use the heater for max **180** seconds, and let it cool down **180** seconds = 3 minutes. 
THe library guards the cool down time by preventing switching the heater on 
within **180** seconds of the last switch off. Note: this guarding is not reboot persistent. 

**WARNING:** The user is responsible to switch the heater off manually!

The class does **NOT** do this automatically.  
Switch off the heater by directly calling **heatOff()** or indirectly by calling **isHeaterOn()**.

- **void setHeatTimeout(uint8_t seconds)** Set the time out of the heat cycle.
This value is truncated to max 180 seconds. 
- **uint8_t getHeatTimeout()** returns the value set.
- **bool heatOn()** switches heat cycle on if not already on.
Returns false if fails, setting error to **SHT2x_ERR_HEATER_COOLDOWN** 
or to **SHT2x_ERR_HEATER_ON**. 
- **bool heatOff()** switches heat cycle off. 
Returns false if fails, setting error to **SHT2x_ERR_HEATER_OFF**.
- **bool isHeaterOn()** is the sensor still in heating cycle?


### Electronic ID

To be tested.

- **uint32_t getEIDA()** returns unique ID part A.
- **uint32_t getEIDB()** returns unique ID part B.
- **uint8_t getFirmwareVersion()** returns firmware version.
  

### Status fields

From HTU20 datasheet

|  bits  | value  | meaning             |
|:------:|:------:|:--------------------|
|  00    |   0    | open circuit        |
|  01    |   1    | temperature reading |
|  10    |   2    | humidity reading    |
|  11    |   3    | closed circuit      |


### Resolution

**Warning experimental** 
- needs more testing as results are not in line with the datasheet.
- only tested on a HTUxx sensor.
- tested with **SHT2X_resolution.ino**

- **void setResolution(uint8_t res)** res = 0..3, other values return false.
- **uint8_t getResolution()** returns resolution set 0..3.


Datasheet SHT20 Table 8: (resolution)

|  RES  |  Humidity | Temperature |
|:-----:|:---------:|:-----------:|
|   0   |  12 bit   |    14 bit   |
|   1   |  08 bit   |    12 bit   |
|   2   |  10 bit   |    13 bit   |
|   3   |  11 bit   |    11 bit   |

Datasheet SHT20 Table 7: (timing) and results of real measurements.
( https://github.com/RobTillaart/SHT2x/pull/11 )

|  RES  |  HUM  |  TEMP  |  TOTAL  |  REAL  |
|:-----:|:-----:|:------:|:-------:|:------:|
|   0   |   29  |   85   |   114   |   116  |
|   1   |    4  |   22   |    26   |   113  |
|   2   |    9  |   43   |    52   |   084  |
|   3   |   15  |   11   |    26   |   102  |

Timing in milliseconds.


 
### Battery

- **bool batteryOK()** returns true if VCC > 2.5 Volts.


## Future

#### must
- improve documentation


#### 0.3.0
- add crc8 check (need sensor)
- improve error handling (all code paths)
- investigate blocking delay() in read 
  - **ASYNC** NO HOLD call to read T or H
  - **void requestTemperature()** ==> **void readTemperature()**
  - **void requestHumidity()** ==> **void readHumidity()**


#### should
- test test test
  - get hardware
- add examples
  - test resolutions
  - performance different resolutions
  - test battery


#### could
- investigate resolution anomalies
- fix TODO in code (.cpp and .h)
- update unit tests


#### wont

- add **getSerialNumber()**
  **getEIDA()** and **getEIDB()** covers this

