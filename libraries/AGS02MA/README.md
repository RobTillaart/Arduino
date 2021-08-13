[![Arduino CI](https://github.com/RobTillaart/AGS02MA/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AGS02MA/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AGS02MA.svg?maxAge=3600)](https://github.com/RobTillaart/AGS02MA/releases)

# AGS02MA

Arduino library for AGS02MA TVOC sensor. 

This library is experimental, so please use with care. 
Please note the warning about the I2C speed.


## I2C - warning low speed

The sensor uses I2C at very low speed < 30KHz. For an Arduino UNO the lowest speed is about 30.4KHz (TWBR = 255) which works sometimes. During tests roughly 1 in 20 reads of the sensor was successful.
Tests with ESP32, which can go as low as ~5 KHZ are underway and expected to work.

The library sets the clock speed to 25KHz (for non AVR) during operation and resets it to 100 KHz
after operation. This is done to minimize interference with the communication with other devices.

## Interface

- **AGS02MA(uint8_t deviceAddress = 26, TwoWire \*wire = &Wire)** constructor, with default address and default I2C interface.
- **bool begin(uint8_t sda, uint8_t scl)** begin for ESP32 and ESP8266.
- **bool begin()** initializer for Arduino UNO a.o.
- **bool isConnected()** returns true if device address can be seen on I2C.


### Timing

- **bool isHeated()** returns true if 2 minutes have passed after startup. 
Otherwise the device is not ready.
- **uint32_t lastRead()** last time the device is read, timestamp in milliseconds since start.


### Administration

- **bool setAddress(const uint8_t deviceAddress)** Not implemented yet.
- **uint8_t getAddress()** returns set address.
- **uint8_t getSensorVersion()** reads sensor version from device.

The library sets the clock speed to 25KHz (for non AVR) during operation and resets it to 100 KHz
after operation. This is done to minimize interference with the communication with other devices.
The following function can change this reset speed.

- **setI2CResetSpeed(uint32_t s)** sets the I2C speed the library need to reset the I2C speed to.
- **getI2CResetSpeed()** returns the set value above. Default is 100KHz.


### setMode

- **bool setPPBMode()** sets device in PartPerBillion mode. Returns true on success.
- **bool setUGM3Mode()** sets device in micro gram per cubic meter mode. Returns true on success.
- **uint8_t getMode()** returns mode set. 0 = PPB, 1 = UGm3, 255 = not set.


### Reading

WARNING: Take at least 2 seconds between reads.

- **uint32_t readPPB()** reads PPB from device. returns 0xFFFFFFFF if failed. 
Check lastStatus() to get more info
- **uint32_t readUGM3()** reads current value from device. 


### Other

- **bool zeroCalibration()** to be called after at least 5 minutes in fresh air. 
See example sketch. 
- **int lastError()** returns last error.
- **uint8_t lastStatus()** returns status byte from last read. Read datasheet.


## Future

- improve documentation
- test test test ...
- add examples
- optimize code 
- buy a sensor
- elaborate error handling.
- elaborate unit test.



