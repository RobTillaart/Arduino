
[![Arduino CI](https://github.com/RobTillaart/SHT2x/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SHT2x/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SHT2x/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SHT2x/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SHT2x/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SHT2x.svg)](https://github.com/RobTillaart/SHT2x/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SHT2x/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SHT2x.svg?maxAge=3600)](https://github.com/RobTillaart/SHT2x/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SHT2x.svg)](https://registry.platformio.org/libraries/robtillaart/SHT2x)


# SHT2x

Arduino library for the SHT2x, HTU2x and Si70xx temperature and humidity sensors.


## Description

This library is not tested extensively yet.
It works for the Si7021 including the asynchronous interface.
It should work for SHT20, SHT21 and SHT25 but these are not tested yet.
The SHT2x family of sensors should work up to 400 KHz I2C.

Furthermore there are several other sensors that should be compatible
(see table below), but have not been tested either.

Accuracy table

|  Sensor   | Temperature | Humidity |  Notes  |
|:---------:|:-----------:|:--------:|:--------|
|  SHT20    |   ~0.3      |  ±3.0    |         |
|  SHT21    |   ~0.3      |  ±3.0    |         |
|  SHT25    |   ~0.3      |  ±1.8    |         |
|  HTU20    |             |          |  to-do  |
|  HTU21    |             |          |  to-do  |
|  Si7013   |             |          |  to-do  |
|  Si7020   |             |          |  to-do  |
|  Si7021   |   ~0.3      |  ~2.0    |         |
|  GY21     |             |          |  to-do  |


All sensors in this family of sensors have address 0x40 (64 decimal).
If you want to use more on one I2C bus one needs either an I2C multiplexer
or one should switch sensors on/off like the select in SPI communication.


#### 0.5.0 Breaking change

Version 0.5.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/SHT31
- https://github.com/RobTillaart/SHT85
- https://github.com/RobTillaart/tinySHT2x


## Interface

```cpp
#include "SHT2x.h"
```

The SHT2x library provides a comprehensive interface for interacting with SHT2x, HTU2x, and Si70xx series temperature and humidity sensors.

#### Constructors

These constructors initialize a sensor object. All specific sensor classes (SHT20, Si7021, etc.) are derived from the base `SHT2x` class.

- **SHT2x(TwoWire \*wire = &Wire)**: Base class constructor. Optionally takes a pointer to a `TwoWire` interface, allowing usage with multiple I2C buses on platforms that support it.
- **SHT20(TwoWire \*wire = &Wire)**: Constructor for SHT20 sensors.
- **SHT21(TwoWire \*wire = &Wire)**: Constructor for SHT21 sensors.
- **SHT25(TwoWire \*wire = &Wire)**: Constructor for SHT25 sensors.
- **HTU20(TwoWire \*wire = &Wire)**: Constructor for HTU20 sensors.
- **HTU21(TwoWire \*wire = &Wire)**: Constructor for HTU21 sensors.
- **Si7013(TwoWire \*wire = &Wire)**: Constructor for Si7013 sensors.
- **Si7020(TwoWire \*wire = &Wire)**: Constructor for Si7020 sensors.
- **Si7021(TwoWire \*wire = &Wire)**: Constructor for Si7021 sensors.
- **GY21(TwoWire \*wire = &Wire)**: Constructor for GY21 sensor modules (often using SHT2x compatible sensors).


#### Core/Basic Functions

These functions provide fundamental control and status information for the sensor.

- **bool begin()**: Initializes the sensor. This function calls `reset()` internally, which can take up to 15 ms. Returns `false` if the device address is not reachable or if the sensor fails to reset.
- **bool isConnected()**: Checks if the sensor is reachable over the I2C bus. Returns `false` if the sensor is not connected or does not acknowledge.
- **bool reset()**: Performs a soft reset of the sensor. This can take up to 15 ms. Hard reset is not supported by this library.
- **uint32_t lastRead()**: Returns the timestamp (in milliseconds since program start) of the last successful `read()` operation.
- **uint8_t getStatus()**: Returns a 2-bit status code indicating the sensor's current operational state. See the "Status fields" table for details on interpreting these bits.


#### Temperature and Humidity (Synchronous Reading)

These functions are used for synchronous (blocking) reads of temperature and humidity.

- **bool read()**: Reads both temperature and humidity from the sensor. This is a blocking call; program execution will pause until the readings are complete.
- **float getTemperature()**: Returns the temperature in degrees Celsius (°C) based on the latest raw data acquired by `read()`.
- **float getHumidity()**: Returns the relative humidity in percent (%) based on the latest raw data acquired by `read()`.
- **uint16_t getRawTemperature()**: Returns the raw, not calibrated 16-bit integer value for temperature directly from the sensor, as acquired by `read()`.
- **uint16_t getRawHumidity()**: Returns the raw, not calibrated 16-bit integer value for humidity directly from the sensor, as acquired by `read()`.

**Note on `read()` and data retrieval:**
The `getTemperature()` and `getHumidity()` functions recalculate values from raw data on every call. If performance is critical, cache these values in your code after a `read()` instead of calling them repeatedly. Raw values are useful for minimizing storage or communication overhead.

The Si70xx sensors (Si7013, Si7020, Si7021) also support reading the temperature value that was internally measured during the last humidity acquisition. This can be useful to get a temperature reading without initiating a new, separate temperature measurement.
- **bool readCachedTemperature()**: For Si70xx sensors, this function retrieves the temperature value measured during the last humidity reading. This is available after a `getHumidity()` call (using the synchronous `read()` method) or after a `requestHumidity()` and successful `readHumidity()` (using the asynchronous interface). See [pull request #27 comment](https://github.com/RobTillaart/SHT2x/pull/27#issuecomment-1836718214) for more details on calling sequences.


#### Asynchronous Operations

The asynchronous interface allows you to initiate a temperature or humidity reading and then continue with other tasks while the sensor is performing the measurement. This is useful for non-blocking applications, preventing your main loop from being stalled while waiting for sensor data. This interface is experimental (since 0.2.2) and may change in future versions. See discussion in [issue #16](https://github.com/RobTillaart/SHT2x/issues/16).

**General Workflow for Asynchronous Operations:**

1.  **Initiate a request:** Call `requestTemperature()` to start a temperature measurement or `requestHumidity()` to start a humidity measurement. The library sends the command to the sensor, which then begins its internal conversion process.
2.  **Periodically check for data readiness:** In your main loop or a timed function, call `reqTempReady()` (for temperature) or `reqHumReady()` (for humidity) to see if the sensor has finished its measurement. These functions return `true` if data is available, `false` otherwise. `requestReady()` can be used to check if *any* requested data is ready.
3.  **Read the value:** Once the corresponding "ready" function returns `true`, call `readTemperature()` to retrieve the temperature value or `readHumidity()` to retrieve the humidity value. These functions then fetch the data from the sensor and update the internal raw values. You can then use `getTemperature()` or `getHumidity()` to get the processed values.

**Difference between synchronous `read()` and asynchronous operations:**
- **Synchronous `read()`**: When you call `read()`, your program stops and waits for the sensor to complete both temperature and humidity measurements. This is simpler to use but can block other operations for the duration of the sensor's measurement time (which can be tens of milliseconds).
- **Asynchronous functions**: You explicitly manage the measurement process. You start a measurement, can perform other tasks, and then check back later to retrieve the result. This avoids blocking but requires a slightly more complex program structure to periodically check the sensor's status.

**Asynchronous Function Descriptions:**

- **`bool requestTemperature()`**: Initiates a request for a temperature reading from the sensor. If a previous asynchronous request (either temperature or humidity) was still pending, it will be overridden by this new request. Returns `true` if the request command was successfully sent to the sensor, `false` otherwise (e.g., I2C communication error).
- **`bool requestHumidity()`**: Initiates a request for a humidity reading from the sensor. If a previous asynchronous request was pending, it will be overridden. Returns `true` if the request command was successfully sent, `false` otherwise.
- **`bool reqTempReady()`**: Checks if the temperature data previously requested by `requestTemperature()` is ready to be read from the sensor. Returns `true` if data is available, `false` if the measurement is still in progress or if no temperature request was made.
- **`bool reqHumReady()`**: Checks if the humidity data previously requested by `requestHumidity()` is ready to be read. Returns `true` if data is available, `false` if the measurement is still in progress or if no humidity request was made.
- **`bool requestReady()`**: Checks if *any* previously requested asynchronous data (either temperature or humidity) is ready. This is useful if you don't need to distinguish which type of data is ready, only that some data can be read. Returns `true` if either temperature or humidity data is available.
- **`bool readTemperature()` (in asynchronous context)**: Reads the temperature data from the sensor *after* `requestTemperature()` has been called and `reqTempReady()` has returned `true`. This function fetches the raw data from the sensor. After this call, `getTemperature()` and `getRawTemperature()` will return the newly acquired values. Returns `true` if the read was successful, `false` otherwise (e.g., CRC error, I2C error).
- **`bool readHumidity()` (in asynchronous context)**: Reads the humidity data from the sensor *after* `requestHumidity()` has been called and `reqHumReady()` has returned `true`. This function fetches the raw data. After this call, `getHumidity()` and `getRawHumidity()` will return the newly acquired values. Returns `true` if the read was successful, `false` otherwise.
- **`uint32_t lastRequest()`**: Returns the timestamp (in milliseconds, based on `millis()`) of when the last asynchronous request (`requestTemperature()` or `requestHumidity()`) was made. This can be useful for implementing timeouts for asynchronous operations.
- **`uint8_t getRequestType()`**: Returns the type of the currently pending or last completed asynchronous request. This helps in determining what kind of data was requested or is ready. The possible return values are:

| Value  | Symbolic                |  Description  |
|:------:|:------------------------|:--------------|
| 0x00   | `SHT2x_REQ_NONE`        | No request pending or last request completed/cleared. |
| 0x01   | `SHT2x_REQ_TEMPERATURE` | A temperature request is currently pending or was the last one made. |
| 0x02   | `SHT2x_REQ_HUMIDITY`    | A humidity request is currently pending or was the last one made.    |
| 0xFF   | `SHT2x_REQ_FAIL`        | A humidity request is currently pending or was the last one made.    |

**Example Snippet (Asynchronous Reading):**

```cpp
#include "SHT2x.h"
#include "Wire.h"

SHT21 sht; // Or SHT20, SHT25, Si7021, etc.

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!sht.begin()) {
    Serial.println("SHT2x sensor not found!");
    while (1);
  }
  Serial.println("SHT2x sensor initialized.");

  // Request initial temperature reading
  if (!sht.requestTemperature()) {
    Serial.println("Failed to request temperature.");
  }
}

void loop() {
  // Non-blocking check for temperature data
  if (sht.getRequestType() == SHT2x_REQ_TEMPERATURE && sht.reqTempReady()) {
    if (sht.readTemperature()) {
      Serial.print("Temperature: ");
      Serial.print(sht.getTemperature());
      Serial.println(" °C");

      // Now request humidity
      if (!sht.requestHumidity()) {
        Serial.println("Failed to request humidity.");
      }
    } else {
      Serial.println("Failed to read temperature.");
      // Optionally, re-request temperature or handle error
      if (!sht.requestTemperature()) {
        Serial.println("Failed to re-request temperature.");
      }
    }
  }

  // Non-blocking check for humidity data
  if (sht.getRequestType() == SHT2x_REQ_HUMIDITY && sht.reqHumReady()) {
    if (sht.readHumidity()) {
      Serial.print("Humidity: ");
      Serial.print(sht.getHumidity());
      Serial.println(" %");

      // Now request temperature for the next cycle
      if (!sht.requestTemperature()) {
        Serial.println("Failed to request temperature for next cycle.");
      }
    } else {
      Serial.println("Failed to read humidity.");
      // Optionally, re-request humidity or handle error
      if (!sht.requestHumidity()) {
        Serial.println("Failed to re-request humidity.");
      }
    }
  }

  // Do other non-blocking things in your loop here
  // For example, yield() or delay(1) can be used if appropriate
  // to prevent busy-waiting, depending on the platform.
  // A simple delay to slow down serial output for this example:
  delay(100); 
}
```

**Waiting until the device is ready:**

These sensors typically need a bit of time to start up before they can accept commands. The SHT21, for instance, requires up to 15ms after it's been powered up. In many programs, the delay that the Arduino framework introduces between your `setup()` and `loop()` functions is sufficient, but if you intend to request your first reading in `setup()` immediately after calling `begin()`, the request may fail. If `requestTemperature()` or `requestHumidity()` returns false and the error code returned from `getError()` is `0x81` (`SHT2x_ERR_WRITECMD`), this may be a sign that the sensor isn't ready.

To work around this, introduce a short delay after calling `begin()` and before requesting a reading. 15ms is probably more than sufficient, although this hasn't been tested extensively.

#### Heater Functions

The built-in heater can be used to test the sensor or to drive off condensation.

**WARNING:** Do not use the heater for long periods. The datasheet for SHT2x sensors does not specify a maximum on-time, so the library conservatively uses the SHT3x series guideline:
Use the heater for a maximum of **180 seconds** (3 minutes), then allow it to cool down for at least **180 seconds**. The library enforces a cool-down period by preventing `heatOn()` from succeeding if called within 180 seconds of the last `heatOff()` call. This guarding is not reboot persistent.
**WARNING:** The user is responsible for switching the heater off manually using `heatOff()`. The library does **NOT** do this automatically.

- **void setHeatTimeout(uint8_t seconds)**: Sets the duration (in seconds) for the heater to be active when `heatOn()` is called. This value is capped at a maximum of 180 seconds.
- **uint8_t getHeatTimeout()**: Returns the currently set heat timeout value in seconds.
- **bool heatOn()**: Turns the internal heater on. Returns `false` if the heater cannot be turned on (e.g., during the mandatory cool-down period or if I2C communication fails), setting an error code (SHT2x_ERR_HEATER_COOLDOWN or SHT2x_ERR_HEATER_ON).
- **bool heatOff()**: Turns the internal heater off. Returns `false` if the heater cannot be switched off (e.g., I2C communication error), setting the SHT2x_ERR_HEATER_OFF error.
- **bool isHeaterOn()**: Checks if the heater is currently active (i.e., within the `_heatTimeout` period since `heatOn()` was called and before `heatOff()` is called). Calling this function will also turn the heater off if the timeout has expired.
- **bool setHeaterLevel(uint8_t level)**: Sets the heater power level. The level is a value from 0 to 15. (Note: This function's availability might depend on the specific sensor model; refer to the sensor datasheet.)
- **bool getHeaterLevel(uint8_t &level)**: Reads the current heater power level. (Note: Availability might depend on the specific sensor model.)


#### Electronic ID

Functions to retrieve the unique electronic identification code and firmware version from the sensor.
(These functions need more testing and have primarily been tested with Si7021 sensors.)

- **uint32_t getEIDA()**: Returns the first part (A) of the electronic ID.
- **uint32_t getEIDB()**: Returns the second part (B) of the electronic ID.
- **uint8_t getFirmwareVersion()**: Returns the firmware version of the sensor.


#### Resolution Control

Allows adjustment of the measurement resolution for temperature and humidity.
**Warning: This feature is experimental** (since 0.2.0) and requires more testing, as initial results are not perfectly aligned with datasheet specifications. It has been primarily tested on HTUxx and Si7021 sensors using the `SHT2X_resolution.ino` example.

- **bool setResolution(uint8_t res)**: Sets the measurement resolution. `res` can be 0, 1, 2, or 3. Other values will result in the function returning `false`.
- **uint8_t getResolution()**: Returns the currently set resolution (cached value).

Datasheet SHT20 Table 8: Resolution settings

| RES | Humidity | Temperature |
|:---:|:--------:|:-----------:|
|  0  |  12 bit  |   14 bit    |
|  1  |  08 bit  |   12 bit    |
|  2  |  10 bit  |   13 bit    |
|  3  |  11 bit  |   11 bit    |

Datasheet SHT20 Table 7: Measurement timing (milliseconds) vs. observed real-world measurements.
(See details at https://github.com/RobTillaart/SHT2x/pull/11)

| RES | HUM (datasheet) | TEMP (datasheet) | TOTAL (datasheet) | REAL (observed) |
|:---:|:---------------:|:----------------:|:-----------------:|:---------------:|
|  0  |       29        |        85        |        114        |       116       |
|  1  |        4        |        22        |         26        |       113       |
|  2  |        9        |        43        |         52        |       084       |
|  3  |       15        |        11        |         26        |       102       |


#### Battery Status

- **bool batteryOK()**: Checks the sensor's battery status indicator. Returns `true` if VCC is above approximately 2.25V (threshold may vary slightly by sensor). Not all sensors support this feature.


#### Error Handling

- **int getError()**: Returns the last error code set by a library function and then clears the internal error flag. It's important to call `getError()` to check for errors after sensor operations, especially if a function returns `false`. Calling `getError()` before another operation ensures you are checking the result of the most recent operation.

Error Codes:
| Value  | Symbolic                  | Description                       | Notes     |
|:------:|:--------------------------|:----------------------------------|:----------|
| 0x00   | SHT2x_OK                  | No error                          |           |
| 0x81   | SHT2x_ERR_WRITECMD        | I2C write command failed          |           |
| 0x82   | SHT2x_ERR_READBYTES       | I2C read bytes failed             |           |
| 0x83   | SHT2x_ERR_HEATER_OFF      | Could not switch off heater       |           |
| 0x84   | SHT2x_ERR_NOT_CONNECT     | Could not connect to sensor       |           |
| 0x85   | SHT2x_ERR_CRC_TEMP        | CRC check failed for temperature  |           |
| 0x86   | SHT2x_ERR_CRC_HUM         | CRC check failed for humidity     |           |
| 0x87   | SHT2x_ERR_CRC_STATUS      | CRC check failed for status reg   | Not used  |
| 0x88   | SHT2x_ERR_HEATER_COOLDOWN | Heater needs to cool down         |           |
| 0x89   | SHT2x_ERR_HEATER_ON       | Could not switch on heater        | (Note: 0x88 was duplicated in original, assuming 0x89 for HEATER_ON based on .h) |
| 0x8A   | SHT2x_ERR_RESOLUTION      | Invalid resolution setting        | Added in 0.2.0 |

Note: HTU20 / HTU21 classes share these error codes. The error SHT2x_ERR_HEATER_ON was listed with code 0x88 in the original README but is 0x89 in SHT2x.h; this table uses 0x89.


#### Status fields

The `getStatus()` function returns a 2-bit value that indicates the type of measurement in the last user register read.
From HTU20 datasheet (consult your specific sensor's datasheet for definitive details).

| Bits | Value | Symbolic                    | Description         |
|:----:|:-----:|:----------------------------|:--------------------|
|  00  |   0   | SHT2x_STATUS_OPEN_CIRCUIT   | Open circuit        |
|  01  |   1   | SHT2x_STATUS_TEMPERATURE  | Temperature reading |
|  10  |   2   | SHT2x_STATUS_HUMIDITY     | Humidity reading    |
|  11  |   3   | SHT2x_STATUS_CLOSED_CIRCUIT | Closed circuit      |


## Future

#### Must

- improve documentation
  - reorganize interface
  - async documentation
- clean up code.

#### Should

- test test test
  - get hardware
- add examples
  - test resolutions
  - performance different resolutions
  - test battery

#### Could

- fix TODO in code (.cpp and .h) and documentation
- update unit tests
- add type info in derived classes?

#### Wont

- add **getSerialNumber()**
  **getEIDA()** and **getEIDB()** covers this


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,
