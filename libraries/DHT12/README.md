
[![Arduino CI](https://github.com/RobTillaart/DHT12/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHT12/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHT12.svg?maxAge=3600)](https://github.com/RobTillaart/DHT12/releases)


# DHT12

Arduino library for I2C DHT12 temperature and humidity sensor.

## Description

The library should be initiated by calling the **begin()** function, 
optionally **begin(datapin, clockpin)** for **ESP32** and similar platforms.

Thereafter one has to call the **read()** function to do the actual reading,
and with **getTemperature()** and **getHumidity()** to get the read values.
Calling these latter again will return the same values until a new **read()** is called.

## Interface

### Constructor
- **DHT12(TwoWire \*wire)** constructor, using a specific Wire (I2C bus).
- **begin(dataPin, clockPin)** begin for ESP32 et al, to set I2C bus pins
- **begin()** initializer for non ESP32.

### Core
- **read()** read the sensor and store the values intenally. It returns the status of the read which should be 0.
- **getHumidity()** returns last Humidity read, or -999 in case of error.
- **getTemperature()** returns last Temperature read, or -999 in case of error.

### Offset
- **void setHumOffset(float offset)** set an offset to calibrate (1st order) the sensor.
- **float getHumOffset()** return current offset, default 0.
- **void setTempOffset(float offset)** set an offset to calibrate (1st order) the sensor
- **float getTempOffset()** return current offset, default 0.
  
### version 0.3.0

- The members **temperature** and **humidity** became private in 0.3.0.
- added offset for temperature and humidity.

## Operation

See examples
