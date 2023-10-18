
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
It is possible to detect a wide range from 0.11 - 100000 lux.

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
The **isReady()** an **getLux()** functions keep track of the adjustment needed.


## Interface hardware

Library was tested with a breakout board.

```
//  breakout BH1750FVI / GY-30
//
//      +-----------------------+
//  GND |o                      |
//  ADD |o                      |
//  SDA |o            +         |  + = sensor
//  SCL |o                      |
//  VCC |o                      |
//      +-----------------------+
//
// ADD = ADDRESS:
//   0 = 0x23
//   1 = 0x5C
//
```
The sensor works on 2.4 - 3.6 volt so be careful not to connect directly to 5.0 volt.  
Note: the breakout board was 5 volt tolerant.


## Interface

```cpp
#include "BH1750FVI.h"
```

### Constructor

- **BH1750FVI(uint8_t address, uint8_t dataPin, uint8_t clockPin)**  ESP constructor with I2C parameters.
- **BH1750FVI(uint8_t address, TwoWire \*wire = &Wire)** constructor for other platforms.
- **bool begin()** resets some internal variables to default. Use with care.
- **bool isConnected()** returns true if address is on I2C bus.


### Base

- **float getRaw()** reads the lux sensor.
- **float getLux()** reads the lux sensor and corrects for correctionFactor, mode, temperature and angle.


### Management

- **int getError()** get the latest error code, mainly for debugging.
- **void powerOn()** wakes up the sensor.
- **void powerOff()** set sensor to sleep.
- **void reset()** resets the data register to 0, effectively removing last measurement.


### Mode operators

- **uint8_t getMode()** gets the mode set by one of the set functions. 
See table above.
- **void setContHighRes()** continuous mode in HIGH resolution.
- **void setContHigh2Res()** continuous mode in HIGH2 resolution.
- **void setContLowRes()** continuous mode in LOW resolution.
- **void setOnceHighRes()** single shot mode in HIGH resolution.
- **void setOnceHigh2Res()** single shot mode in HIGH2 resolution.
- **void setOnceLowRes()** single shot mode in LOW resolution.


### CorrectionFactor

Please read datasheet P11 about details of the correction factor.

- **bool isReady()** can be used to check if the sensor is ready.
This is based on a calculated time, the sensor does not have a means to indicate ready directly.
Needed only for the single shot modi.
The function **isReady()** takes the correction factor into account.
- **void changeTiming(uint8_t time = BH1750FVI_REFERENCE_TIME)** 69 is default.
- **uint8_t setCorrectionFactor(float factor = 1)** preferred wrapper around changeTiming factor = 0.45 .. 3.68.  
Returns changeTiming() parameter.
- **float getCorrectionFactor()** returns the correction factor.
Note this can differ as it is stores as an integer internally.


### Angle sensitivity

Note: experimental - use carefully

The lux sensor is really sensitive for the angle of the light.
If one makes measurements outside, the position of the sun changes
during the day. The **setAngle(int degrees)** function provides a mean to correct that.

The angle adjustments is based upon the figure 4 and 5 (directional characteristics.)
which describe **Lambert’s Cosine Law**. (details see  Wikipedia)
So the correction factor is ```factor = 1.0 / cos(angle)```.
At 90 degrees it would fail (divide by zero) so the input is constrained
to angles between -89 - +89 degrees.

If the light is perpendicular on the sensor the angle to use is 0 degrees.
Light coming from the side is 90 degrees.

- **float setAngle(int degrees = 0)** adjust the lux to incoming angle in degrees (-89..89).
Returns the angle correction factor.
- **int getAngle()** returns set angle in degrees, 0 by default is perpendicular.


### Temperature Compensation

The reference temperature of the sensor = 20°C.
The effect of temperature is small, about 3% per 60°C ==> 1% per 20°C
so only on either a hot roof or on a icy cold day the effect is substantial.

- **float setTemperature(int temp = 20)**  see datasheet P3 fig 7.
Returns the temperature correction factor.
- **int getTemperature()** returns temperature set, default = 20°C.


### Spectral Compensation ! EXPERIMENTAL !

Spectral compensation is experimental and not tested. It is a compensation based upon the 
graph figure 1, page 3 of the datasheet. If one has light of a known wavelength one can 
compensate for it by setting the wavelength. It can also be used when using filters. 
As said it is not tested so use at your own risk, but I am interested in your experiences
if you do real tests with it.

- **float setWaveLength(int wavelength = 580)** set wavelength.
Returns the wavelength correction factor.
- **int getWaveLength()** returns set wavelength.

As the graph (figure 1) is not linear it is approximated by linear interpolation with the 
following six points.

| WaveLength | Perc % |
|:-----------|:------:|
|     400    |    1   |
|     440    |   10   |
|     510    |   90   |
|     545    |   80   |
|     580    |  100   |
|     700    |   07   |
|     715    |    1   |

Values outside the range will be mapped upon 400 or 715. 
Default wavelength will be 580 as that gives 100%.


## Operation

See samples...


## Future

#### Must

#### Should

#### Could

- **Intelligent isReady()**
After a **getLux()** call one can clean the data register explicitly with
**reset()**. Then a call to **isReady()** fetches data and as long as
data equals zero the sensor is not ready.
- **DVI interface**
To investigate, sort of external reset?
- move code to .cpp

#### Wont

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

