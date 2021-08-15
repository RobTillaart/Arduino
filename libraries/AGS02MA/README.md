[![Arduino CI](https://github.com/RobTillaart/AGS02MA/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AGS02MA/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AGS02MA.svg?maxAge=3600)](https://github.com/RobTillaart/AGS02MA/releases)

# AGS02MA

Arduino library for AGS02MA TVOC sensor.

This library is experimental, so please use with care.
Note the warning about the I2C speed, the device works at 30 KHz.


## I2C - warning low speed

The sensor uses I2C at very low speed <= 30 KHz.
For an Arduino UNO the lowest speed possible is about 30.4KHz (TWBR = 255) which works.
Tests with ESP32 / ESP8266 at 30 KHz look good, tests with lower clock speeds are to be done but expected to work.
First runs indicate 2 failed reads in > 500 Reads, so less than 1%

The library sets the clock speed to 30 KHz (for non AVR) during operation and resets it to 100 KHz after operation.
This is done to minimize interference with the communication of other devices. The reset clock speed can be changed with **setI2CResetSpeed()** e.g. to 200 or 400 KHz.


## Interface


### Constructor

- **AGS02MA(uint8_t deviceAddress = 26, TwoWire \*wire = &Wire)** constructor, with default address and default I2C interface.
- **bool begin(uint8_t sda, uint8_t scl)** begin for ESP32 and ESP8266.
- **bool begin()** initializer for Arduino UNO a.o.
- **bool isConnected()** returns true if device address can be seen on I2C.


### Timing

- **bool isHeated()** returns true if 2 minutes have passed after startup (call of **begin()** ).
Otherwise the device is not optimal ready.
According to the datasheet the preheating will improve the quality
of the measurements.
- **uint32_t lastRead()** last time the device is read, timestamp is in milliseconds since start.
Returns 0 if **readPPB()** or **readUGM3()** is not called yet.
This function allows to implement sort of asynchronous wait.
One must keep reads ~3 seconds apart according to the datasheet.


### Administration

- **bool setAddress(const uint8_t deviceAddress)** sets a new addres for the sensor. If function succeeds the address changes immediately and will be persistent over a reboot.
- **uint8_t getAddress()** returns the set address. Default the function will return 26 or 0x1A.
- **uint8_t getSensorVersion()** reads sensor version from device.
If the version cannot be read the function will return 255.

The library sets the clock speed to 30 KHz (for non AVR) during operation and resets it to 100 KHz after operation.
This is done to minimize interference with the communication of other devices.
The following function can change the I2C reset speed to e.g. 200 or 400 KHz.

- **setI2CResetSpeed(uint32_t s)** sets the I2C speed the library need to reset the I2C speed to.
- **getI2CResetSpeed()** returns the set value above. Default is 100 KHz.


### setMode

The default mode at startup of the sensor is PPB = parts per billion.

- **bool setPPBMode()** sets device in PartPerBillion mode. Returns true on success.
- **bool setUGM3Mode()** sets device in micro gram per cubic meter mode. Returns true on success.
- **uint8_t getMode()** returns mode set. 0 = PPB, 1 = UGm3, 255 = not set.


#### PPB versus UGM3

There is no 1 to 1 relation between the PPB and the uG/m3 readings as this relation depends on the weight of the individual molecules.
PPB is therefore an more an absolute indicator where uG/m3 is sort of relative indicator.
If the gas is unknown, PPB is imho the preferred measurement.


### Reading

WARNING: Datasheet advises to take 3 seconds between reads.
You might be able to squeeze time down to 1.5 second at your own risk.

- **uint32_t readPPB()** reads PPB from device.
Returns 0xFFFFFFFF if failed.
Typical value should be between 1..999999.
Check lastStatus() to get more info about success.
- **uint32_t readUGM3()** reads current value from device. 
Returns 0xFFFFFFFF if failed.


### Other

- **bool zeroCalibration()** to be called after at least 5 minutes in fresh air.
See example sketch.
- **int lastError()** returns last error.
- **uint8_t lastStatus()** returns status byte from last read.
Read datasheet for details. 


## Future

- test test test ...
- buy a few sensors

### Documentation

- improve
- add table for molecular weights
- add indicative table for PPB health zone

### Code

- add examples 
- add **float readPPM()**
- add **float readmGM3()**
- add **bool RDYbit()** split the RDY bit of the status byte
- check the mode bits of the status byte with internal \_mode.
- optimize code where possible
- optimize timing 30ms between low level I2C reads and writes.
- elaborate error handling.
- improve unit testing?
- investigate max frequency of reads (now 3 seconds apart)


