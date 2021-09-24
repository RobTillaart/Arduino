[![Arduino CI](https://github.com/RobTillaart/AGS02MA/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AGS02MA/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AGS02MA/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AGS02MA/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AGS02MA/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AGS02MA/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AGS02MA.svg?maxAge=3600)](https://github.com/RobTillaart/AGS02MA/releases)

# AGS02MA

Arduino library for AGS02MA TVOC sensor.

This library is experimental, so please use with care.
Note the warning about the I2C speed, the device works at 30 KHz.


## I2C - warning low speed

The sensor uses I2C at very low speed <= 30 KHz.
For an Arduino UNO the lowest speed possible is about 30.4KHz (TWBR = 255) which works.
Tests with ESP32 / ESP8266 at 30 KHz look good, 
tests with lower clock speeds are to be done but expected to work.
First runs indicate 2 failed reads in > 500 Reads, so less than 1%

The library sets the clock speed to 30 KHz (for non AVR) during operation 
and resets it to 100 KHz after operation.
This is done to minimize interference with the communication of other devices. 
The reset clock speed can be changed with **setI2CResetSpeed()** e.g. to 200 or 400 KHz.


## Interface


### Constructor

- **AGS02MA(uint8_t deviceAddress = 26, TwoWire \*wire = &Wire)** constructor, with default address and default I2C interface.
- **bool begin(uint8_t sda, uint8_t scl)** begin for ESP32 and ESP8266.
- **bool begin()** initializer for Arduino UNO a.o.
- **bool isConnected()** returns true if device address can be seen on I2C.
- **void reset()** reset internal variables.


### Timing

- **bool isHeated()** returns true if 2 minutes have passed after startup (call of **begin()** ).
Otherwise the device is not optimal ready.
According to the datasheet the preheating will improve the quality
of the measurements.
- **uint32_t lastRead()** last time the device is read, timestamp is in milliseconds since start.
Returns 0 if **readPPB()** or **readUGM3()** is not called yet.  
This function allows to implement sort of asynchronous wait.  
One must keep reads at least 1.5 seconds but preferred 3 seconds apart according to the datasheet.


### Administration

- **bool setAddress(const uint8_t deviceAddress)** sets a new address for the sensor. 
If function succeeds the address changes immediately and will be persistent over a reboot.
- **uint8_t getAddress()** returns the set address. Default the function will return 26 or 0x1A.
- **uint8_t getSensorVersion()** reads sensor version from device.  
If the version cannot be read the function will return 255.  
(My test sensors all return 117)

The library sets the clock speed to 30 KHz (for non AVR) during operation 
and resets it to 100 KHz after operation.
This is done to minimize interference with the communication of other devices.
The following function can change the I2C reset speed to e.g. 200 or 400 KHz.

- **void setI2CResetSpeed(uint32_t s)** sets the I2C speed the library need to reset the I2C speed to.
- **uint32_t getI2CResetSpeed()** returns the value set. Default is 100 KHz.


### setMode

The default mode at startup of the sensor is PPB = parts per billion.

- **bool setPPBMode()** sets device in PartPerBillion mode. Returns true on success.
- **bool setUGM3Mode()** sets device in micro gram per cubic meter mode. Returns true on success.
- **uint8_t getMode()** returns mode set. 0 = PPB, 1 = UGm3, 255 = not set.


#### PPB versus UGM3

There is no 1 to 1 relation between the PPB and the uG/m3 readings as this relation depends 
on the weight of the individual molecules.
PPB is therefore an more an absolute indicator where uG/m3 is sort of relative indicator.
If the gas is unknown, PPB is in my opinion the preferred measurement.


From an unverified source the following formula:
M = molecular weight of the gas.

**μg/m3 = (ppb)\*(12.187)\*(M) / (273.15 + °C)** 

Simplified formula for 1 atm @ 25°C: 

**μg/m3 = ppb \* M \* 0.04087539829 μg/m3**

Some known gasses

|  gas    |  ratio              | molecular weight M |
|:--------|:--------------------|-------------------:|
| SO2     | 1 ppb = 2.62 μg/m3  | 64 |
| NO2     | 1 ppb = 1.88 μg/m3  | 46 |
| NO      | 1 ppb = 1.25 μg/m3  | 30 |
| O3      | 1 ppb = 2.00 μg/m3  | 48 |
| CO      | 1 ppb = 1.145 μg/m3 | 28 |
| Benzene | 1 ppb = 3.19 μg/m3  | 78 | C6H6 |


### Reading

WARNING: The datasheet advises to take 3 seconds between reads.
You might be able to squeeze time down to 1.5 second at your own risk.

- **uint32_t readPPB()** reads PPB (parts per billion) from device.
Typical value should be between 1 .. 999999.
Returns **lastPPB()** value if failed so one does not get sudden jumps in graphs.
Check **lastStatus()** and **lastError()** to get more info about success.  
Time needed is ~35 milliseconds.

- **uint32_t readUGM3()** reads UGM3 (microgram per cubic meter) current value from device. 
Typical values depend on the molecular weight of the TVOC.
Returns **lastUGM3()** if failed so one does not get sudden jumps in graphs.
- **float readPPM()** returns parts per million (PPM). 
This function is a wrapper around readPPB().
Typical value should be between 1.00 .. 999.99 
- **float readMGM3()** returns milligram per cubic meter.
- **float readUGF3()** returns microgram per cubic feet.


#### Cached values

- **float lastPPM()** returns last readPPM (parts per million) value (cached). 
- **uint32_t lastPPB()** returns last read PPB (parts per billion) value (cached). Should be between 1..999999.
- **uint32_t lastUGM3()** returns last read UGM3 (microgram per cubic meter) value (cached).


### Other

- **bool zeroCalibration()** to be called after at least 5 minutes in fresh air.
See example sketch.
- **int lastError()** returns last error.
- **uint8_t lastStatus()** returns status byte from last read.
Read datasheet or table below for details. 
- **uint8_t dataReady()** returns RDY bit from last read.


#### Status bits.

| bit  | description            |
|:----:|:-----------------------|
| 7-4  | internal use           |
| 3-1  | 000 = PPB  001 = uG/M3 |
|  0   | RDY bit  0 = ready  1 = not ready |


## Future

- test test test ...
- improve documentation
- add indicative table for PPB health zone
- check the mode bits of the status byte with internal \_mode.
- elaborate error handling.

