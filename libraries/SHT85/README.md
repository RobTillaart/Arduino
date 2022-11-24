
[![Arduino CI](https://github.com/robtillaart/SHT85/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SHT85/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SHT85/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SHT85/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SHT85/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SHT85/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SHT85.svg?maxAge=3600)](https://github.com/RobTillaart/SHT85/releases)


# SHT85

Arduino library for the SHT85 temperature and humidity sensor.

Based upon the SHT31 library - https://github.com/RobTillaart/SHT31
however this one will be leading in the future as it implements classes for the following SHT sensors: **SHT30, SHT31 and SHT35.**


**Warning:** to keep self-heating below 0.1°C, the SHT85 sensor should 
not be used for more than 10% of the time.


## Description

```
    // TOPVIEW      SHT85
    //            +-------+
    // +-----\    | SDA 4 -----
    // | /-+  ----+ GND 3 -----
    // | +-+  ----+ +5V 2 -----
    // +-----/    | SCL 1 -----
    //            +-------+
```


The SHT85 sensors should work up to 1000 KHz, however during tests 
with an Arduino UNO it stopped between 500 - 550 KHz so to be safe I recommend
not to use it above 400 KHz. Also the differences in read time becomes
quite small. (max 15% gain). See output example sketch.

| I2C speed | read ms | notes |
|:---------:|:-------:|:------|
|  100 KHz  |  5.11   |       |
|  150 KHz  |  4.79   |       |
|  200 KHz  |  4.64   |       |
|  250 KHz  |  4.56   |       |
|  300 KHz  |  4.50   |       |
|  350 KHz  |  4.47   |       |
|  400 KHz  |  4.45   |       |
|  450 KHz  |  4.43   |       |
|  500 KHz  |  4.42   |       |
|  550 KHz  |  ----   | fail  |


### Compatibility

This library should also work for SHT30, SHT31 and SHT35 but 
this is not verified yet.

Accuracy table

| SENSOR | Temperature | Humidity |
|:------:|:-----------:|:--------:|
| SHT30  |    ~0.3°    |   2.0%   |
| SHT31  |    ~0.3°    |   1.5%   |
| SHT35  |    ~0.2°    |   1.5%   |
| SHT85  |    ~0.2°    |   1.5%   |


Need to investigate if the interface is identical?
If so the libraries might be merged.

An elaborated library for the SHT31 sensor can be found here
https://github.com/hawesg/SHT31D_Particle_Photon_ClosedCube


## Interface

#### Base interface

- **SHT()** constructor of the base class. **getType()** will return 0.
- **SHT30()** constructor.
- **SHT31()** constructor.
- **SHT35()** constructor.
- **SHT85()** constructor.
- **uint8_t getType()** returns numeric part of sensor type.
- **bool begin(uint8_t address, uint8_t dataPin, uint8_t clockPin)** begin function for ESP8266 & ESP32; **WARNING: not verified yet**
returns false if device address is incorrect or device cannot be reset.
- **bool begin(uint8_t dataPin, uint8_t clockPin)** same as above. 
Uses SHT_DEFAULT_ADDRESS as address.
- **bool begin(uint8_t address, TwoWire \*wire = &Wire)** for platforms with multiple I2C buses. Default Wire as I2C bus.
- **bool begin(TwoWire \*wire = &Wire)** same as above.
Uses SHT_DEFAULT_ADDRESS as address.
- **bool read(bool fast = true)** blocks 4 (fast) or 15 (slow) milliseconds + actual read + math.
Does read both the temperature and humidity.
- **bool isConnected()** check sensor is reachable over I2C. Returns false if not connected.
- **uint16_t readStatus()** details see datasheet and **Status fields** below.
- **uint32_t lastRead()** in milliSeconds since start of program.
- **bool reset(bool hard = false)** resets the sensor, soft reset by default. Returns false if fails.
- **float getHumidity()** computes the relative humidity in % based on the latest raw reading, and returns it.
- **float getTemperature()** computes the temperature in °C based on the latest raw reading, and returns it.
- **float getFahrenheit()** computes the temperature in °F based on the latest raw reading, and returns it.
- **uint16_t getRawHumidity()** returns the raw two-byte representation of humidity directly from the sensor.
- **uint16_t getRawTemperature()** returns the raw two-byte representation of temperature directly from the sensor.

Note that the temperature and humidity values are recalculated on every call to getHumidity() and getTemperature(). 
If you're worried about the extra cycles, you should make sure to cache these values or only request them after 
you've performed a new reading.


#### Error interface

- **int getError()** returns last set error flag and clear it. 
Be sure to clear the error flag by calling **getError()** before calling any command as the error flag could be from a previous command.

| Error | Symbolic                  | Description                 |
|:-----:|:--------------------------|:----------------------------|
| 0x00  | SHT_OK                    | no error                    |
| 0x81  | SHT_ERR_WRITECMD          | I2C write failed            |
| 0x82  | SHT_ERR_READBYTES         | I2C read failed             |
| 0x83  | SHT_ERR_HEATER_OFF        | Could not switch off heater |
| 0x84  | SHT_ERR_NOT_CONNECT       | Could not connect           |
| 0x85  | SHT_ERR_CRC_TEMP          | CRC error in temperature    |
| 0x86  | SHT_ERR_CRC_HUM           | CRC error in humidity       |
| 0x87  | SHT_ERR_CRC_STATUS        | CRC error in status field   |
| 0x88  | SHT_ERR_HEATER_COOLDOWN   | Heater need to cool down    |
| 0x89  | SHT_ERR_HEATER_ON         | Could not switch on heater  |


#### Heater interface

**WARNING:** Do not use heater for long periods. 

Use the heater for max **180** seconds, and let it cool down **180** seconds = 3 minutes. 
Version 0.3.3 and up guards the cool down time by preventing switching the heater on 
within **180** seconds of the last switch off. Note: this guarding is not reboot persistent. 

**WARNING:** The user is responsible to switch the heater off manually!

The class does **NOT** do this automatically.
Switch off the heater by directly calling **heatOff()** or indirectly by calling **isHeaterOn()**.

- **void setHeatTimeout(uint8_t seconds)** Set the time out of the heat cycle.
This value is truncated to max 180 seconds. 
- **uint8_t getHeatTimeout
- **bool heatOn()** switches heat cycle on if not already on.
Returns false if fails, setting error to **SHT_ERR_HEATER_COOLDOWN** 
or to **SHT_ERR_HEATER_ON**. 
- **bool heatOff()** switches heat cycle off. 
Returns false if fails, setting error to **SHT_ERR_HEATER_OFF**.
- **bool isHeaterOn()** is the sensor still in heating cycle? replaces **heatUp()**.
Will switch the heater off if max heating time has passed.


#### Async interface

See async example for usage

- **bool requestData()** requests a new measurement. Returns false if the request fails.
- **bool dataReady()** checks if enough time has passed to read the data. (15 milliseconds)
- **bool readData(bool fast = true)** fast = true skips the CRC check. 
Returns false if reading fails or in case of a CRC failure. 


## Status fields

| BIT  | Description                | value   | notes |
|:-----|:---------------------------|:--------|:------|
| 15   | Alert pending status       |  0      | no pending alerts
|      |                            |  1      | at least one pending alert - default
| 14   | Reserved                   |  0      |
| 13   | Heater status              |  0      | Heater OFF - default
|      |                            |  1      | Heater ON 
| 12   | Reserved                   |  0      |
| 11   | Humidity tracking alert    |  0      | no alert - default
|      |                            |  1      | alert
| 10   | Temperature tracking alert |  0      | no alert - default
|      |                            |  1      | alert
| 9-5  | Reserved                   |  00000  |
|  4   | System reset detected      |  0      | no reset since last ‘clear status register’ command
|      |                            |  1      | reset detected (hard or soft reset command or supply fail) - default
| 3-2  | Reserved                   |  00     |
|  1   | Command status             |  0      | last command executed successfully
|      |                            |  1      | last command not processed. Invalid or failed checksum
|  0   | Write data checksum status |  0      | checksum of last write correct
|      |                            |  1      | checksum of last write transfer failed


## Operation

See examples.


## Future

#### should

- testing
  - verify working with ESP32
  - software I2C experiments
- improve error handling / status. (all code paths)
- add offsets for temperature and humidity.
  - like other sensors
- move code from .h to .cpp


#### could

- investigate command ART (auto sampling at 4 Hz)
- investigate command BREAK (stop auto sampling)
- merge with other SHT sensors if possible
- separate release notes.


#### won't

- rename the library? to SHT ? or sensirion.h ?
  - not on short term
- create a SHT85 simulator 
  - I2C slave sketch with e.g. a DHT22 sensor/
  - not within this library.


