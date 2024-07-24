
[![Arduino CI](https://github.com/RobTillaart/BH1750FVI_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/BH1750FVI_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/BH1750FVI_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/BH1750FVI_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/BH1750FVI_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/BH1750FVI_RT.svg)](https://github.com/RobTillaart/BH1750FVI_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/BH1750FVI_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/BH1750FVI_RT.svg?maxAge=3600)](https://github.com/RobTillaart/BH1750FVI_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/BH1750FVI_RT.svg)](https://registry.platformio.org/libraries/robtillaart/BH1750FVI_RT)


# BH1750FVI_RT

Arduino library for BH1750FVI (GY-30) 16 bit I2C Lux sensor.


## Description

The BH1750FVI is a 16 bit lux sensor with an I2C interface.
This sensor has a wide working range from 0.11 - 100000 lux.

To be able to support this wide range, the sensor can operate in three modi.

|  ID  | Mode  | Integration time | Resolution | Notes                     |
|:----:|:-----:|:----------------:|:----------:|:--------------------------|
|  0   | LOW   |     16 ms        |  4.0 Lux   | measure very bright light |
|  1   | HIGH  |    120 ms        |  1.0 lux   | default                   |
|  2   | HIGH2 |    120 ms        |  0.5 lux   | measure very dim light    |

Furthermore one can set a correction factor to reduce / increase the
integration time of the sensor.
The factor should be between 0.45 - 3.68.
It can be used to increase the working range like very bright or very low light conditions.
Another application is to correct the transparency of material, or the type of light used.

Note that the typical integration time will differ if the correction factor is changed.
The **isReady()** and **getLux()** functions keep track of the adjustment needed.


### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the I2C pins in the constructor any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins
before calling **begin()**.


### Lux levels

The following table is an indication for Lux levels.
These might differ due to angle of incoming light or other causes.
Note that the table is not linear.

|  LUX     |  Description        |
|:--------:|:--------------------|
|  1       |  Night              |
|  10      |  Twilight           |
|  100     |  Dark day           |
|  1000    |  Cloudy day         |
|  10000   |  Indirect sunlight  |
|  100000  |  Direct sunlight    |

More elaborated table, e.g https://en.wikipedia.org/wiki/Lux


### Related

- https://en.wikipedia.org/wiki/Lux
- https://github.com/RobTillaart/BH1750FVI_RT
- https://github.com/RobTillaart/Max44007
- https://github.com/RobTillaart/Max44009
- https://github.com/RobTillaart/TSL235R  pulse based irradiance variant.

UV sensors
- https://github.com/RobTillaart/AnalogUVSensor
- https://github.com/RobTillaart/ML8511

IR sensor
- https://github.com/RobTillaart/TSL260R  analog IR irradiance variant.


## Interface hardware

Library was tested with a breakout board.

```
//  breakout BH1750FVI / GY-30
//
//        +-----------------------+
//    GND |o                      |
//    ADD |o                      |
//    SDA |o            +         |  + = sensor
//    SCL |o                      |
//    VCC |o                      |
//        +-----------------------+
//
```
The sensor works on 2.4 - 3.6 volt so be careful not to connect directly to 5.0 volt.  
Note: the breakout board was 5 volt tolerant.


### I2C address

I2C address can be set with the ADDRESS pin.

|  ADD PIN  |  address  |
|:---------:|:---------:|
|  LOW      |   0x23    |
|  HIGH     |   0x5C    |

Note these two addresses are inverted (7 bit).


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


## Interface

```cpp
#include "BH1750FVI.h"
```

### Constructor

- **BH1750FVI(uint8_t address, TwoWire \*wire = &Wire)** constructor.
- **bool begin()** resets some internal variables to default. Use with care.
Returns true if address can be found on I2C bus.
- **bool isConnected()** returns true if address can be found on I2C bus.


### Base

- **float getRaw()** reads the lux sensor.
- **float getLux()** reads the lux sensor and corrects for correctionFactor, 
mode, temperature and angle.


### Management

- **int getError()** get the latest error code, mainly for debugging.
- **void powerOn()** wakes up the sensor.
- **void powerOff()** set the sensor to sleep.
- **void reset()** resets the data register to 0, effectively removing last measurement.


### Mode operators

|  ID  | Mode  | Integration time | Resolution | Notes                     |
|:----:|:-----:|:----------------:|:----------:|:--------------------------|
|  0   | LOW   |     16 ms        |  4.0 Lux   | measure very bright light |
|  1   | HIGH  |    120 ms        |  1.0 lux   | default                   |
|  2   | HIGH2 |    120 ms        |  0.5 lux   | measure very dim light    |

- **uint8_t getMode()** gets the mode set by one of the set functions. 
See table above.
- **void setContHighRes()**  continuous mode in HIGH resolution.
- **void setContHigh2Res()** continuous mode in HIGH2 resolution.
- **void setContLowRes()**   continuous mode in LOW resolution.
- **void setOnceHighRes()**  single shot mode in HIGH resolution.
- **void setOnceHigh2Res()** single shot mode in HIGH2 resolution.
- **void setOnceLowRes()**   single shot mode in LOW resolution.

- **bool isReady()** can be used to check if the sensor is ready.
This is based on a calculated time, the sensor does not have a means to indicate ready directly.
Needed only when one of the single shot modi is set.
The function **isReady()** takes the correction factor into account.


### CorrectionFactor

Please read datasheet P11 about details of the correction factor.

- **void changeTiming(uint8_t time = BH1750FVI_REFERENCE_TIME)** 69 is default.
- **uint8_t setCorrectionFactor(float factor = 1)** preferred wrapper around 
changeTiming factor = 0.45 .. 3.68.  
Returns changeTiming() parameter.
- **float getCorrectionFactor()** returns the correction factor.
Note the returned value can differ slightly from the set value as the value is 
stored as an integer internally.


### Angle sensitivity

Note: experimental - use carefully

The lux sensor is really sensitive for the angle of the light.
If one makes measurements outside, the position of the sun changes
during the day. The **setAngle(int degrees)** function provides a mean to correct that.

The angle adjustments is based upon the figure 4 and 5 (directional characteristics.)
which describe **Lambert’s Cosine Law**. (details see Wikipedia)
So the correction factor is ```factor = 1.0 / cos(angle)```.
At 90 degrees it would fail (divide by zero) so the input is constrained
to angles between -89.9 - +89.9 degrees.

If the light is perpendicular on the sensor the angle to use is 0 degrees.
Light coming from the side is ±90 degrees.

- **float setAngle(float degrees = 0)** adjust the lux to incoming angle in degrees (-89..89).
Returns the angle correction factor.
- **float getAngle()** returns set angle in degrees, 0 by default is perpendicular.

Note: it could be enough to be able to set the angle to 0..89.9 degrees as the
sign is not relevant.


### Temperature Compensation

The reference temperature of the sensor = 20°Celsius.
The effect of temperature is small, about 3% per 60°C ==> 1% per 20°C
so only on either a hot roof or on a icy cold day the effect is substantial.  
See datasheet P3 fig 7.

- **float setTemperature(int temp = 20)** set the temperature in Celsius to compensate for.
Returns the temperature correction factor.
- **int getTemperature()** returns temperature set, default = 20°C.


### Spectral Compensation ! EXPERIMENTAL !

Spectral compensation is experimental and not tested. It is a compensation based upon the 
graph figure 1, page 3 of the datasheet. If one has light of a known wavelength one can 
compensate for it by setting the wavelength. It can also be used when using filters. 
As said it is not tested so use at your own risk, but I am interested in your experiences
if you do real tests with it.

- **float setWaveLength(int wavelength = 580)** set wavelength of the light.
Returns the wavelength correction factor.
- **int getWaveLength()** returns set wavelength.

As the graph (figure 1) is not linear it is approximated by linear interpolation with the 
following six points.

| WaveLength |  Colour  |  Perc %  |
|:-----------|:--------:|:--------:|
|     400    |  violet  |      1   |
|     440    |  blue    |     10   |
|     510    |  green   |     90   |
|     545    |  green   |     80   |
|     580    |  yellow  |    100   |
|     700    |  red     |     07   |
|     715    |  red     |      1   |

Colour is indicative.

Values outside the range will be mapped upon 400 or 715. 
Default wavelength will be 580 as that gives 100%.


## Future

#### Must

#### Should

- test

#### Could

- **Intelligent isReady()**
After a **getLux()** call one can clear the data register explicitly with
**reset()**. Then a call to **isReady()** fetches data and as long as
data equals zero the sensor is not ready (or sensor is in pitch dark?)
- **DVI interface**
To investigate, sort of external reset?
- move code to .cpp


#### Wont

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

