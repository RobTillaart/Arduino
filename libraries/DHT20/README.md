
[![Arduino CI](https://github.com/RobTillaart/DHT20/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHT20/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHT20/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHT20/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHT20/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHT20/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHT20.svg?maxAge=3600)](https://github.com/RobTillaart/DHT20/releases)


# DHT20

Arduino library for I2C DHT20 temperature and humidity sensor.


## Description

The library must be initiated by calling the **begin()** function, 
or **begin(dataPin, clockPin)** for **ESP32** and similar platforms.

Thereafter one has to call the **read()** function to do the actual reading,
and with **getTemperature()** and **getHumidity()** to get the measured values.
Calling these latter again will return the same values until a new **read()** is called.

The **read()** call of this sensor is blocking for 80+ milliseconds (datasheet 7.4)
so the library also has a asynchronous interface. See below.

Verified to work with Arduino UNO and ESP32.


## Connection

Always check datasheet 

Front view
```
          +--------------+
  VDD ----| 1            |
  SDA ----| 2    DHT20   |
  GND ----| 3            |
  SCL ----| 4            |
          +--------------+
```

## Tested

Examples verified to work with Arduino UNO and ESP32.


## Interface


### Constructor

- **DHT20(TwoWire \*wire = &Wire)** constructor, using a specific Wire (I2C bus).
- **bool begin(uint8_t dataPin, uint8_t clockPin)** begin for ESP32 et al, to set I2C bus pins.
- **bool begin()** initializer for non ESP32. Returns true if connected.
- **bool isConnected()** returns true if the address of the DHT20 can be seen on the I2C bus.


### Core

- **int8_t read()** read the sensor and store the values internally. 
It returns the status of the read which should be 0.
- **float getHumidity()** returns last Humidity read.
- **float getTemperature()** returns last Temperature read.


### Offset

- **void setHumOffset(float offset)** set an offset to calibrate (1st order) the sensor.
- **float getHumOffset()** return current offset, default 0.
- **void setTempOffset(float offset)** set an offset to calibrate (1st order) the sensor.
- **float getTempOffset()** return current offset, default 0.


### Asynchronous interface

Note the async interface is not 100% functional yet. 
Expect functional complete in 0.2.0.

There are two timings that need to be considdered, 
- time between requests = 1000 ms
- time between request and data ready.

The async interface allows one to continue processing whatever after a **requestData()** has been made. Note that there should be at least **1000 milliseconds** between subsequent requests.

After **DHT20_ACQUISITION_TIME == 85 ms** enough time after the request has 
passed to read the data of the measurement. So the sensor can be read with **readData()**.

To interpret the read bits to temperature, humidity and status one needs to call **convert()** as last step.


- **int requestData()** signals the sensor to make a new measurement.
Note there must be at least 1000 milliseconds between requests!
- **int readData()** does the actual reading of the data.
- **int convert()** converts the read bits to temperature and humidity.

See the example **DHT20_async.ino**


### Status

- **uint8_t readStatus()** forced read of the status only.
- **bool isCalibrated()** idem, wrapper around **readStatus()**
- **bool isMeasuring()** idem, wrapper around **readStatus()**
- **bool isIdle()** idem, wrapper around **readStatus()**
- **int internalStatus()** returns the internal status of the sensor. (debug ).

|  status bit  |  meaning                   |
|:------------:|:---------------------------|
|    7         |  busy making measurement   |
|  6 - 4       |  unknown                   |
|    3         |  1 = calibrated, 0 is not  |
|  2 - 0       |  unknown                   |


### Timing

- **uint32_t lastRead()** last time the sensor is read in milliseconds since start.
- **uint32_t lastRequest()** last time a request is made to make a measurement.


### Return codes

| name                        |  value  |  notes  |
|:----------------------------|:-------:|:--------|
| DHT20_OK                    |    00   |  OK
| DHT20_ERROR_CHECKSUM        |   -10   |  values might be OK if they are like recent previous ones.
| DHT20_ERROR_CONNECT         |   -11   |  check connection
| DHT20_MISSING_BYTES         |   -12   |  check connection
| DHT20_ERROR_BYTES_ALL_ZERO  |   -13   |  check connection
| DHT20_ERROR_READ_TIMEOUT    |   -14   |
| DHT20_ERROR_LASTREAD        |   -15   |


## Operation

See examples


## Future

#### must

- update documentation
- comments in .h file

#### should

- add examples
- check TODO's in code.


#### could

- improve unit tests.
- investigate 
  - sensor calibration (website aosong?)


#### won't

- **void setIgnoreChecksum(bool = false)** ignore checksum flag speeds up communication a bit
- **bool getIgnoreChecksum()** get status. for completeness.
- 


