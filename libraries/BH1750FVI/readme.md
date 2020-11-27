# BH1750FVI_RT

Arduino library for BH1750FVI (GY-30) 16 bit I2C Lux sensor

## Description

The BH1750FVI is a 16 bit lux sensor with an I2C interface
It is possible to detect a wide range from 0.11 - 100000 lux.

To be able to support this wide range, the sensor can operate in three modi.

| ID | Mode | Integration time | Resolution | Notes |
|:----:|:----:|:----:|:----:|:----|
| 0 | LOW | 16 ms | 4.0 Lux | to measure very bright light |
| 1 | HIGH | 120 ms | 1.0 lux | default |
| 2 | HIGH2 | 120 ms | 0.5 lux | to measure very dim light |

Furthermore one can set a correction factor to reduce / increase the
integration time of the sensor.
The factor should be between 0.45 - 3.68.
It can be used to increase the working range like very bright or very low light conditions.
Another aplication is to correct the transparancy of material, or the type of light used.

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
(Note: the breakout board was 5 volt tolerant)

## Interface API

- **BH1750FVI(address, dataPin, clockPin)**  ESP constructor with I2C parameters
- **BH1750FVI(address, TwoWire \*wire = &Wire)** constructor for other platforms
- **getRaw()** reads the lux sensor,
- **getLux()** reads the lux sensor and corrects for correctionFactor and for HIGH2 mode,
- **getError()** get the latest error, mainly for debugging,
- **powerOn()** wakes up the sensor,
- **powerOff()** set sensor to sleep,
- **reset()** resets the dataregister to 0, effectively removing last measurement.
- **getMode()** gets the mode set by one of the set functions. See table above.
- **setContHighRes()** continuous mode in HIGH resolution
- **setContHigh2Res()** continuous mode in HIGH2 resolution
- **setContLowRes()** continuous mode in LOW resolution
- **setOnceHighRes()** single shot mode in HIGH resolution
- **setOnceHigh2Res()** single shot mode in HIGH2 resolution
- **setOnceLowRes()** single shot mode in LOW resolution
- **isReady()** can be used to check if the sensor is ready.
This is based on a calculated time, the sensor does not have a means to indicate ready directly.
Needed only for the single shot modi.
The function **isReady()** takes the correctionfactor into account.

**CorrectionFactor**

Please read datasheet P11 about details of the correction factor.
- **changeTiming(uint8_t val)** 69 is default = BH1750FVI_REFERENCE_TIME
- **setCorrectionFactor(float f)** prefered wrapper around changeTiming f = 0.45 .. 3.68
- **getCorrectionFactor()** returns the correction factor.
Note this can differ as it is stores as an integer internally.

**Angle sensitivity**

Note: experimental - use carefully

The lux sensor is really sensitive for the angle of the light.
If one makes measurements outside, the position of the sun changes
during the day. The **setAngle(degrees)** function provides a mean to correct that.

The angle adjustments is based upon the figure 4 and 5 (directional characteristics.)
which describe **Lambert’s Cosine Law**. (details see  wikipedia)
So the correction factor is ```factor = 1.0 / cos(angle)```.
At 90 degrees it would fail (divide by zero) so the input is constrained
to angles between -89 - +89 degrees.

If the light is perpendicular on the sensor the angle to use is 0 degrees.
Light coming from the side is 90 degrees.

- **setAngle(int degrees)** adjust the lux to incoming angle in dgrees
- **getAngle()** returns set angle in degrees, 0 by default is perpendicular

**Temperature Compensation**

The reference temperature of the sensor = 20°C.
The effect of temperature is small, about 3% per 60°C ==> 1% per 20°C
so only on either a hot roof or on a icy cold day the effect is measurable.

- **setTemperature(int T)**  see datasheet P3 fig7
- **getTemperature()** returns temperature set, default = 20°C


**Spectral Compensation ! EXPERIMENTAL !**

Spectral compensation is experimental and not tested. It is a compensation based upon the 
graph figure 1, page 3 of the datasheet. If one has light of a known wavelength one can 
compensate for it by setting the wavelength. It can also be used when using filters. 
As said it is not tested so use at your own risk, but I am interested in your experiences
if you do real tests with it.

- **void setSpectral(int wavelength)** set wavelength,
- **int getSpectral()** returns wavelength

As the graph (figure 1) is not lineair it is approximated by linear interpolation with the 
following six points.

| WaveLength | Perc % |
|:----|:----:|
| 400 |   1 |
| 440 |  10 |
| 510 |  90 |
| 545 |  80 |
| 580 | 100 |
| 700 |  07 |
| 725 |   1 |

Values outside the range will be mapped upon 400 or 715. 
Default wavelength will be 580 as that gives 100%


## Ideas

**Intelligent isReady()**

After a **getLux()** call one can clean the dataregister explicitly with
**reset()**. Then a call to **isReady()** fetches data and as long as
data equals zero the sensor is not ready.

**DVI interface**

To investigate, sort of external reset?


## Operation

See samples...
