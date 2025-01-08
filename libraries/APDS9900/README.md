
[![Arduino CI](https://github.com/RobTillaart/APDS9900/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/APDS9900/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/APDS9900/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/APDS9900/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/APDS9900/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/APDS9900.svg)](https://github.com/RobTillaart/APDS9900/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/APDS9900/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/APDS9900.svg?maxAge=3600)](https://github.com/RobTillaart/APDS9900/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/APDS9900.svg)](https://registry.platformio.org/libraries/robtillaart/APDS9900)


# APDS9900

Arduino library for the I2C APDS9900 light sensor and proximity detector.


## Description

**Experimental**

This library is to read the APDS9900 or APDS9901 sensor.

The code is not tested with hardware yet.

The APDS9900/ADPS9901 has two main functions:
- measure ambient light (ALS), up to 16 bit.
- proximity detection.

The device supports a sleep mode for power efficiency.

The device can generate an interrupt (INT pin) based upon thresholds set.
The library does not support the interrupt handling, which should be done by user code.

Please read the datasheet carefully.

_The documentation has to be elaborated after testing with hardware._


As always feedback is welcome.


### Related

- https://en.wikipedia.org/wiki/Lux
- https://github.com/RobTillaart/APDS9900
- https://github.com/RobTillaart/BH1750FVI_RT
- https://github.com/RobTillaart/Max44007
- https://github.com/RobTillaart/Max44009
- https://github.com/RobTillaart/TSL235R  pulse based irradiance variant.

UV sensors
- https://github.com/RobTillaart/AnalogUVSensor
- https://github.com/RobTillaart/ML8511

IR sensor
- https://github.com/RobTillaart/TSL260R  analog IR irradiance variant.


### I2C

The device has a fixed I2C address of 0x39 (decimal 57).


### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up 
to eight channels (think of it as I2C subnets) which can use the complete 
address range of the device. 

Drawback of using a multiplexer is that it takes more administration in 
your code e.g. which device is on which channel. 
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices 
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548

See example **TCA9548_demo_APDS9900.ino**


### I2C Performance


|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  default 
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |  maximum datasheet
|   500 KHz  |             |
|   600 KHz  |             |


TODO: run performance sketch.


## Interface

```cpp
#include "APDS9900.h"
```

### Constructor

- **APDS9900(uint8_t address, TwoWire \*wire = &Wire)** set address and optional select I2C bus.
- **ADPS9901(uint8_t address, TwoWire \*wire = &Wire)** set address and optional select I2C bus.
- **bool begin()** checks if the device address is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the address 


### Sleep

- **void wakeUp()** switches the power on of the device.
- **void sleep()** switches the power off of the device.


### Integration time

- **void setIntegrationTime(uint16_t milliseconds)** milliseconds in steps of 2.72 ms, range 3..696
- **uint16_t getIntegrationTime()** returns set value, might differ slightly due to rounding.


### Proximity time

WARNING: USE WITH CARE - read datasheet

- **void setProximityTime(uint8_t value = 0xFF)** this register should be set to 0xFF.
Read datasheet P19.
- **uint8_t getProximityTime()** return current setting.


### Wait time

The WTIME can be set in two ranges, depending on a WLONG bit (See P19, P21)

- WLONG == false: milliseconds in steps of 2.72 ms, range 3..696
- WLONG == true:  milliseconds in steps of 32 ms, range 32..8192

Note there is overlap between 32..696 milliseconds. 
The function setWaitTime() determines if it needs to set the WLONG bit or not.

- **void setWaitTime(uint16_t milliseconds)** set milliseconds in steps of 2.72 ms, range 3..696
If milliseconds is between 696 and 8192 in steps of 32 milliseconds by setting WLONG bit internally.
- **uint16_t getWaitTime()** returns set value, might differ slightly due to rounding.


### Interrupts

To be elaborated.

The following functions to set the interrupt thresholds check if lowTH is smaller than highTH.

- **bool setALSThresholds(uint16_t lowTH, uint16_t highTH)**
- **bool setPROXThresholds(uint16_t lowTH, uint16_t highTH)**
- **void setALSInterruptPersistence(uint8_t value)** value = 0..15
- **void setPROXInterruptPersistence(uint8_t value)** value = 0..15, see datasheet for meaning.

Persistency table:

|  Signal  |      0  |  1  |  2  |  3  |  4  |  5  |  6  |  8  |  10 |  12 |  14 |  15 |
|:--------:|:-------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|   ALS    |  every  |  1  |  2  |  3  |  4  |  5  |  6  |  8  |  10 |  12 |  14 |  15 |
|  PROXI   |  every  |  1  |  2  |  3  |  5  |  10 |  15 |  20 |  30 |  40 |  50 |  60 |


### Proximity Pulse Count

Defines the amount of pulses that will be transmitted if proximity is enabled.
See datasheet.

- **void setProximityPulseCount(uint8_t value)** see datasheet
- **uint8_t getProximityPulseCount()** returns current setting.


### LedDriveStrength

- **bool setLedDriveStrength(uint8_t value)** 0 = 100 mA, 1 = 50 mA, 2 = 25 mA, 3 = 12.5 mA.
Returns false if out of range.
- **uint8_t getLedDriveStrength()** returns 0,1,2,3

TODO Make ENUM for constants?

|  value  |  strength  |
|:-------:|:----------:|
|    0    |   100 mA   |
|    1    |    50 mA   |
|    2    |    25 mA   |
|    3    |   12.5 mA  |


### ProximityDiodeSelect

READ datasheet P22, must be 2.

- **bool setProximityDiodeSelect(uint8_t channel)** channel = 0 or 1.
Returns false if out of range.
- **uint8_t getProximityDiodeSelect()**


### ProximityGain

READ datasheet P22, must be 0.

- **bool setProximityGain(uint8_t gain)** 0 = 1x, 1 = 8x, 2 = 16x, 3 = 120x
Returns false if out of range.
- **uint8_t getProximityGain()** returns 1.


### ALSGain

- **bool setPGain(uint8_t gain)** 0 = 1x, 1 = 8x, 2 = 16x, 3 = 120x
Returns false if out of range.
- **uint8_t getALSGain()** returns 1, 8, 16 or 120, the actual gain.

TODO Make ENUM for constants?


### Misc

These are read only registers.

- **uint8_t getRevision()** typical returns 0x01.
- **uint8_t getDeviceID()** returns 0x29 for APDS9900, 0x20 for APDS9901.


### Status

Read datasheet for the details.

- **uint8_t getStatus()**

|  bit  |  meaning  |
|:-----:|:----------|
|  7-6  |  reserved
|   5   |  PINT, Proximity Interrupt
|   4   |  AINT, ALS Interrupt
|  3-2  |  reserved
|   1   |  PVALID, PS has completed an integration cycle.
|   0   |  AVALID, ALS has completed an integration cycle.


### Measurements

- **float getLux(float GA = 0.48)** Glass Attenuation Factor = default 0.48.
Needs calibration depending on glass / lens.

The raw data

- **uint16_t getALS_CDATA()** Channel 0 diode
- **uint16_t getALS_IRDATA()** Channel 1 diode (IR = infra red)
- **uint16_t getPROX_DATA()** 


### Error

- **int getLastError()** returns last error set. Check to detect e.g. I2C errors.

The error handling itself needs to be elaborated.
- table of errors.


### Angle correction

Based upon figure 5.

If the light is perpendicular (0 degrees) one gets 100% of the light.
If there is an angle the loss is roughly 2% per degree.

```
0 degrees = 100%
50 degrees = 0%
angle = constrain(angle 0, 50)
factor = (100 - angle * 2)
lux = lux * factor * 0.01;
```


## Future

#### Must

- improve documentation.
- get hardware to test library.

#### Should

- difference 9900/9901
  - break-out?
- **getter()** functions where needed.
  - e.g. interrupt thresholds.
- optimization
  - cache certain registers?
  - make write() conditionally where possible.  (analyze footprint impact)
- add examples
- add **clearInterrrupt()**
- add **bool isAwake()**

#### Could

- improve error handling
- enums / defines for constants.
- names of functions may change.
- cache control register?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


