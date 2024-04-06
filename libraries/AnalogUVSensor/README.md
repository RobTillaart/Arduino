
[![Arduino CI](https://github.com/RobTillaart/AnalogUVSensor/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AnalogUVSensor/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AnalogUVSensor/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AnalogUVSensor/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AnalogUVSensor/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AnalogUVSensor.svg)](https://github.com/RobTillaart/AnalogUVSensor/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AnalogUVSensor/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AnalogUVSensor.svg?maxAge=3600)](https://github.com/RobTillaart/AnalogUVSensor/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AnalogUVSensor.svg)](https://registry.platformio.org/libraries/robtillaart/AnalogUVSensor)


# AnalogUVSensor

Arduino library for an analogue UV sensor.


## Description

![Foo](https://www.tinytronics.nl/shop/image/cache/catalog/products/product-003601/uv-light-sensor-module-200-370nm-80x80w.jpg)
Image courtesy Tinytronics

This small (type-less) UV-sensor is powered by 3.3 .. 5.0 V so it can be used by almost any microprocessor.

The sensor has an analogue output that is roughly linear with the UV-index (sunlight assumed, see notes).


|  Voltage  |  UV index  |  risk of harm  |  Colour   |
|:---------:|:----------:|:---------------|:---------:|
|   <0.050  |     0      |  low           |  Green    |
|   0.227   |     1      |  low           |  Green    |
|   0.318   |     2      |  low           |  Green    |
|   0.408   |     3      |  moderate      |  Yellow   |
|   0.503   |     4      |  moderate      |  Yellow   |
|   0.606   |     5      |  moderate      |  Yellow   |
|   0.696   |     6      |  high          |  Orange   |
|   0.795   |     7      |  high          |  Orange   |
|   0.881   |     8      |  very high     |  Red      |
|   0.976   |     9      |  very high     |  Red      |
|   1.079   |    10      |  very high     |  Red      |
|   1.170>  |    11      |  extreme       |  Purple   |


From this table the formula is derived (spreadsheet) which is pretty linear between UV 1 and 11.
Between 0 and 1 there seems to be a curve / other linear relation.


#### Notes

Note: risk of harm based upon Wikipedia.

Note: The sensor is not calibrated and the table is indicative for sunlight (warning, assumption!)
and therefore not suitable for e.g. medical or industrial usage.

Note: UV radiation will not go through normal glass, so inside (a house) you will most likely always read zero.
This may of course help to calibrate the zero level of the sensor.

Note: depending on the light source used, the table above is not correct.
If one wants to use other values one need to fix the formula in the **mv2index()** function.
(mv stands for millivolt)

Note: the output of the sensor is typically 0 .. 1.1 volt. To increase precision one might configure
the ADC used to match this voltage range. E.g. Arduino UNO can be set to use an internal 1.1 volt reference.
See Arduino manual **setAnalogReference()**

Note: for a continuous colour scale check
- https://github.com/RobTillaart/map2colour


#### Wavelength sensitivity

The sensor is sensitive for wavelengths from 200 - 370 nm, so mostly in UVB and UVA region and less in the UVC.
There is no information about the detailed wavelength sensitivity, so it is not possible to compensate.
However one could assume that there is a normal (or other) distribution over the 200 - 370 nm range and create
a compensation table based upon the assumed distribution.

More about UV see - https://en.wikipedia.org/wiki/Ultraviolet


#### Related

- https://github.com/RobTillaart/ML8511
- https://github.com/RobTillaart/map2colour


## Interface

```cpp
#include "AnalogUVSensor.h"
```

- **AnalogUVSensor()** Constructor.
- **void begin(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023)**
set the parameters of the sensor, analogPin, volts and maxADC to specify the internal ADC.
Volts and maxADC have a default so these can be omitted if these match.
  - Note: one needs to reset these parameters if the settings of the internal ADC are
changed e.g. to INTERNAL_1V1 to change the accuracy.
- **float read(uint8_t times = 1)** Returns the UV index.
Read the analogue sensor one (or more) times to average the reading.
This can improve the accuracy of the reading.
If times == 0 it is set to 1.
- **float mV2index(uint16_t milliVolt)** MilliVolt to index. Returns the UV index.
The conversion formula from milliVolt to the UV index is used internally by the **read()** function.
This function can also be called with a voltage measured with an external ADC.
The function will return a value between 0.0 and 12.0.
- **char index2color(float index)** Converts an UV index to the first letter of **G**reen,
**Y**ellow, **O**range, **R**ed or **P**urple.
Can be used as indication on a user interface.
This function can also be called with an index from an other UV index sensor.


#### Power interface

Works only if setPowerPin is called properly.

- **void setPowerPin(uint8_t powerPin, bool invert = false)**
Can be used to control the power of the sensor e.g. for low power mode.
Optionally one can set the invert flag to **true** to invert the **HIGH LOW** levels
e.g. when the analogue sensor is switched through a MOSFET.
- **void switchOff()** switch off the power of the sensor.
- **void switchOn()** switch on the power of the sensor.


## Future

#### Must

- verify vs calibrated sensor

#### Should

- documentation
  - investigate with different light sources (UVled, TL, sunlight).
- move powerPin setting to constructor (breaking 0.2.0 ?)

#### Could

- investigate angle sensitivity e.g. if the UV light comes from an angle - cosine law.
  - see https://github.com/RobTillaart/BH1750FVI library
- investigate response time to stabilize e.g. does it react fast on clouds.
- investigate time needed to first (stable) measurement.


#### Wont

- **index2time()** calculate max exposure time?
  - dangerous advice, so better keep that out of the library ?
- **uint32_t index2RGB(float index)** full (smooth) colour RGB mapping.
  - created a https://github.com/RobTillaart/map2colour lib for this feature
    to keep footprint in this library small.
- add code for external ADC (see ACS712)
  - users can call **mV2index()**


## Sponsor

The development of this library is sponsored by [TinyTronics, Netherlands](https://www.tinytronics.nl/shop/nl).


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

