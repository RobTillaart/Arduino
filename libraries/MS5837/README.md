
[![Arduino CI](https://github.com/RobTillaart/MS5837/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MS5837/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MS5837/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MS5837/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MS5837/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MS5837.svg)](https://github.com/RobTillaart/MS5837/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MS5837/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MS5837.svg?maxAge=3600)](https://github.com/RobTillaart/MS5837/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MS5837.svg)](https://registry.platformio.org/libraries/robtillaart/MS5837)


# MS5837

Library for the MS5837 temperature and pressure sensor and compatibles.


## Description

**Experimental**

The MS5837 is a waterproof device to measure temperature and pressure to a high level
of accuracy.
From the pressure one can calculate the depth or the altitude of the sensor to some extend.
- The MS5837_30 can go to depth of 300 meter (30 Bar).
- The MS5837_02 is meant for altitude measurements as it can as low as 300 mBar.

The library does not use the integer math from the datasheet but float math. 
Assumption is that it reduces footprint and increases math speed.
This will have an effect on the accuracy of the results, 
although these are expected relative small. (to be investigated)


#### Related

- https://github.com/RobTillaart/pressure Conversions
- https://github.com/RobTillaart/temperature Conversions
- https://github.com/RobTillaart/MS5611 temperature and pressure sensor

See also .h file


#### Compatibles

See mathType notes below.

|  Sensor        | mathType |  Celsius °C  |  pressure mBar  |  Notes  |
|:---------------|:--------:|:------------:|:---------------:|:-------:|
|  MS5837-30bar  |    0     |  -20 to +85  |  0 to 30000     |  for depth
|  MS5837-02bar  |    1     |  -20 to +85  |  300 to 1200    |  for altitude
|  MS5803-01bar  |    2     |  -40 to +85  |  10 to 1300     |  investigate


#### Pressure mathType 

There are MS5837 compatibles for which the math for the pressure is different.
See **AN520__004: C-code example for MS56xx, MS57xx (except analog sensor), and MS58xx series pressure sensors**
The difference is in the constants (mostly powers of 2) used to calculate the pressure.

The library implements **reset(uint8_t mathMode = 0)** to select the mathMode.
- mathMode = 0 ==> datasheet MS5837_30  page 7
- mathMode = 1 ==> datasheet MS5837_02  page 7
- mathMode = 2 ==> datasheet MS5803_01  page 7

- other values will act as 0


#### Tests

Library uses similar code as the tested MS5611 library.

TODO: tests with hardware.

The library is tested with the following boards: TODO

As always feedback is welcome.
Please let me know of other working platforms / processors (and failing ones!).



##  I2C

User has to call **Wire.begin()** (or equivalent) before calling **ms5611.begin(0)**


#### Performance

The maximum I2C speed is 400 KHz. (TODO verify).


#### Multiplexing

The MS5837 has one fixed address 0x76. So you can have only one per I2C bus.
If one needs to control more MS5837's one need an I2C multiplexer.

- https://github.com/RobTillaart/TCA9548 I2C multiplexer.


## Interface

```cpp
#include MS5837.h
```

#### Constructor

- **MS5837(TwoWire \* wire = &Wire))** constructor, optional 
- **bool begin(uint8_t mathMode)** initializes the library.
- **bool isConnected()** returns true if device visible on I2C bus.
- **bool reset(uint8_t mathMode)** resets the sensor and reads its configuration.
The mathMode must match the type of sensor, see table above.
- **uint8_t getType()** type indicates max pressure. 
Returns 30 or 2 or zero if unknown.
- **uint8_t getAddress()** returns 0x76 as this is a fixed address.


#### Temperature and Pressure

- **bool read(uint8_t bits = 8)** the actual reading of the sensor. 
The bits determines the oversampling factor, see table below. 
Returns true upon success.
The call will block for 3 to 40 milliseconds, depending upon number of bits.
- **float getPressure()** returns mBar.
- **float getTemperature()** returns degrees Celsius.
- **float getAltitude(float airPressure = 1013.25)** calculates the altitude, based upon actual pressure and the pressure at sea level.
Returns altitude in meters.
One can compensate for the actual air pressure at sea level.

|  type       |  bits read()  | 
|:-----------:|:-------------:|
|  MS5837_30  |  8..12        |
|  MS5837_02  |  8..12, 13    |
|  MS5803_01  |  8..12        |


#### Depth

Mainly for the MS5837_30.

Depth calculation depends on the air pressure at sea level, and the density
of the liquid you are submerged in (typical water).
The pressure is in fact the sum of the air pressure and the weight of the liquid above.
If the density is larger the maximum depth of the sensor will decrease.

- **void setDensity(float density)** set liquid density.
- **float getDensity()** returns set liquid density.
- **float getDepth(float airPressure = 1013.25)** calculates the depth, 
based upon actual pressure and the pressure at sea level.
Returns depth in meters.
One can compensate for the actual air pressure at sea level.


## Future

#### Must

- documentation
- buy hardware - 30 or 2 bar version ?
- check TODO's in code / documentation
- test 

#### Should

- add **lastRead()**
- create derived classes?
  - so one does not need to set mathMode.
  - for 5803 
- can we see conversion ready?
- performance test
- investigate the effects of float math on accuracy / precision.


#### Could

- refactor type & mathMode
- add offset functions


#### Won't (unless requested)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

