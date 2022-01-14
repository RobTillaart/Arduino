
[![Arduino CI](https://github.com/RobTillaart/AM2315/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AM2315/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AM2315/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AM2315/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AM2315/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AM2315/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AM2315.svg?maxAge=3600)](https://github.com/RobTillaart/AM2315/releases)


# AM2315

Arduino library for I2C AM2315 temperature and humidity sensor.

The AM2315 can also be read with the https://github.com/RobTillaart/AM232X library as it uses the same protocol. The AM232X library allows to read some internal registers.


## Description

The library must be initiated by calling the **begin()** function, 
optionally **begin(dataPin, clockPin)** for **ESP32** and similar platforms.

Thereafter one has to call the **read()** function to do the actual reading,
and with **getTemperature()** and **getHumidity()** to get the read values.
Calling these latter again will return the same values until a new **read()** is called.

The I2C address is 0x5C and is hardcoded in the device. 
If you need multiple AM2315 devices use a I2C multiplexer e.g. https://github.com/RobTillaart/TCA9548


### I2C clock speed

The datasheet states the AM2315 should be used on 100 KHz I2C only. 
When overclocking I got good readings up to 190 KHz in a test with 
- Arduino UNO
- very short wires (< 1 meter)
- not using pull ups.
- version 0.1.1 of this library


| I2C clock | timing us | Notes                 |
|:---------:|:---------:|:----------------------|
|   50 KHz  |    4570   | under-clocking works (e.g. long wires)
|  100 KHz  |    3276   | specs default, robust
|  150 KHz  |    2836   |
|  160 KHz  |    2792   |
|  170 KHz  |    2750   | 0.5 ms off, interesting for performance.
|  180 KHz  |    2700   | near critical. DO NOT USE.
|  190 KHz  |    2672   | near critical. DO NOT USE.
|  200 KHz  |   crash   | sensor needs a power cycle reboot. DO NOT USE.


If robustness is mandatory stick to the default of 100 KHz.
If performance is mandatory do not go beyond 170 KHz.


### Wake up

As the sensor goes to sleep after 3 seconds after last read, it needs to be woken up.
This is hard coded in the **readSensor()** function. 
There is also a **wakeUp()** function so the wake up can be done some time before the 
read is actual needed.


## Interface


### Constructor

- **AM2315(TwoWire \*wire = &Wire)** constructor, default using Wire (I2C bus), optionally set to Wire0 .. WireN.
- **bool begin(uint8_t dataPin, uint8_t clockPin)** begin for ESP32 et al, to set I2C bus pins, returns true if device is connected.
- **bool begin()** initializer for non ESP32. Returns true if connected.
- **bool isConnected(uint16_t timeout = 3000)** returns true if the address of the AM2315 can be seen on the I2C bus.
As the device can be in sleep modus it will retry for the defined timeout (in micros) with a minimum of 1 try. 
minimum = 800 us and maximum = 3000 us according to datasheet.


### Core

- **int8_t read()** read the sensor and store the values internally. 
It returns the status of the read which should be **AM2315_OK** == 0.
- **float getHumidity()** returns last Humidity read + optional offset, or **AM2315_INVALID_VALUE** == -999 in case of error. This error can be suppressed, see below.
- **float getTemperature()** returns last Temperature read + optional offset, or **AM2315_INVALID_VALUE** == -999 in case of error. This error can be suppressed, see below.
- **uint32_t lastRead()** returns the timestamp in milliseconds since startup of the last successful read.


### Offset

- **void setHumOffset(float offset = 0)** set an offset for humidity to calibrate (1st order) the sensor.
Default offset = 0, so no parameter will reset the offset.
- **float getHumOffset()** return current humidity offset, default 0.
- **void setTempOffset(float offset = 0)** set an offset for temperature to calibrate (1st order) the sensor.
Default offset = 0, so no parameter will reset the offset.
- **float getTempOffset()** return current temperature offset, default 0.


### Control

Functions to adjust the communication with the sensor.

- **void setWaitForReading(bool b )** flag to enforce a blocking wait (up to 2 seconds) when **read()** is called.
- **bool getWaitForReading()** returns the above setting.
- **void setSuppressError(bool b)** suppress error values of **AM2315_INVALID_VALUE** == -999 => you need to check the return value of read() instead.  
This can be used to keep spikes out of your graphs / logs. 
- **bool getSuppressError()**  returns the above setting.


### Misc

- **bool wakeUp()** function that will try for 3 milliseconds to wake up the sensor. 
This can be done before an actual read to minimize the **read()** call.


### error codes


| name                              | value | notes       |
|:----------------------------------|------:|:------------|
| AM2315_OK                         |  0    |
| AM2315_ERROR_CHECKSUM             |  -10  | I2C problem.
| AM2315_ERROR_CONNECT              |  -11  | I2C problem.
| AM2315_MISSING_BYTES              |  -12  | I2C problem.
| AM2315_WAITING_FOR_READ           |  -50  | called **read()** too fast, within 2 seconds.
| AM2315_HUMIDITY_OUT_OF_RANGE      |  -100 | not used by default.
| AM2315_TEMPERATURE_OUT_OF_RANGE   |  -101 | not used by default.
| AM2315_INVALID_VALUE              |  -999 | can be suppressed. 


## Operation

See examples


## Future

- documentation
- test
- update unit test
- add examples
- merge with the AM232X library in a far future.

**wont**
- add calls for meta information (no description yet)
  - 0x07 status register
  - 0x08-0x0B user register HIGH LOW HIGH2 LOW2
  (use AM232x library to access those)

