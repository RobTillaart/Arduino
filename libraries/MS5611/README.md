
[![Arduino CI](https://github.com/RobTillaart/MS5611/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MS5611/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MS5611.svg?maxAge=3600)](https://github.com/RobTillaart/MS5611/releases)

# MS5611

Arduino library for MS5611 temperature and pressure sensor


## Description

The MS5611 is a high resolution temperature and pressure sensor.
The high resolution is made possible by oversampling (many times).

#### 0.3.0 breaking changes

1. fixed math error so previous versions are obsolete
2. temperature is a float expressed in degrees Celsius.
3. pressure is a float expressed in mBar.


## Interface

- **MS5611(uint8_t deviceAddress)** constructor
- **bool begin(uint8_t sda, uint8_t scl, TwoWire \*wire = &Wire)** for ESP and alike, optionally set Wire interface. initializes internals, 
- **bool begin(TwoWire \*wire = &Wire)** for UNO and alike, optionally set Wire interface. Initializes internals
- **bool isConnected()** checks availability of deviceaddress on the I2C bus.
- **reset()** resets the chip and loads constants from it.
- **int read(uint8_t bits = 8)** the actual reading of the sensor. Returns MS5611_READ_OK upon success
- **float getTemperature()** returns temperature in �C. Subsequent calls will return same value until a new **read()** is called.
- **float getPressure()** pressure is in mBar. Subsequent calls will return same value until a new **read()** is called.
- **int getLastResult()** checks last I2C communication (replace with more informative error handling?)
- **uint32_t lastRead()** last time in millis() when **read()** was called.


## Disclaimer

The library is experimental. As I have no such sensor the quality is hard to test.
So if you happen to have such a sensor, please give it a try and let me know.


## TODO

- proper error handling
- redo lower level functions?
- SPI version?


## Operation

See examples
