
[![Arduino CI](https://github.com/RobTillaart/ML8511/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ML8511/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ML8511/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ML8511/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ML8511/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ML8511/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ML8511.svg?maxAge=3600)](https://github.com/RobTillaart/ML8511/releases)


# ML8511

Arduino library for the ML8511 UV sensor.


## Warning

**Always take precautions as UV radiation can cause sunburn, eye damage and other problems**.

Do not expose yourself to the sun as UV source too long.

When using artificial UV light (TL LED laser a.o.) use appropriate shielding.


## Description

ML8511 - UV sensor - library for Arduino UNO. 

- 3V3 Sensor so do **NOT** connect to 5V directly.
- do not forget to connect the EN to either an enablePIN or to 3V3 (constantly enabled).


#### Related

- https://github.com/RobTillaart/TSL235R pulse based irradiance variant.
- https://github.com/RobTillaart/TSL260R analog IR irradiance variant.
- https://github.com/RobTillaart/AnalogUVSensor
- https://github.com/RobTillaart/ML8511  UV sensor


#### Breakout

```
//        +-------+--+
//    VIN |o      +-+|  mounting hole
//    3V3 |o      +-+|
//    GND |o         |
//    OUT |o         |
//     EN |o       S |  Sensor
//        +----------+
```


## Operational

As the sensor / breakout is 3V3 one need to connect to Arduino 3V3.
The library converts the **analogRead()** to voltages, and it uses a
reference of 5.0 Volt == 1023 steps as default.

If one wants to use another ratio e.g. 3.3 volts == 4095 steps, one
can set those with **setVoltagePerStep()**.

```cpp
    ML8511 light(A0, 7);
    light.setVoltagePerStep(3.3, 4095);
```

It is possible to always enable the sensor by connecting the EN pin to 3V3.
The value of the enablePin in the constructor should then be omitted 
or set to a negative value.

When connecting to an Arduino UNO one can use the 3V3 of the Arduino to power the sensor. 
However it is not possible to connect the enable pin directly to the sensor. 
Use a voltage divider (10K + 20K) to convert the 5 Volts to ~3.3 Volts.


## Interface

```cpp
#include "ML8511.h"
```

#### Constructor

- **ML8511(uint8_t analogPin, uint8_t enablePin = 0xFF)** Constructor, 
if enable is connected to 3V3 constantly one does not need to set the enablePin parameter.

#### Core

- **float getUV(uint8_t energyMode = HIGH)** returns mW per cm2, energyMode = HIGH or LOW.
LOW will disable the sensor after each read.
- **float voltage2mW(float voltage)** returns mW per cm2 from voltage. 
To be used when one uses an external ADC e.g. ADS1115
- **void setVoltsPerStep(float voltage, uint32_t steps)** to calibrate the **internal** ADC used. 
Voltage must be > 0 otherwise it is not set and the default of 5 volts 1023 steps is used.
This function has no meaning for an external ADC.
- **float getVoltsPerStep()** idem.
- **void enable()** manually enable.
- **void disable()** manually disable.
- **bool isEnabled()** get enabled status.


#### Experimental

WARNING: USE WITH CARE

- **float estimateDUVindex(float mWcm2)** input in mW per cm2, returns a value between 0 and ~15(?)
- **void setDUVfactor(float factor)** set the conversion factor
- **float getDUVfactor()** returns the set conversion factor (default 1.61)

See below (Experimental DUVindex) how to determine the DUV factor for your sensor.

_Note: 
The UV index can be very high, in La Paz, Bolivia, one of the highest cities in the world
the DUV index can go above 20. See link below.
This is really extreme and it is unknown how the ML8511 sensor (and this library) behaves under such conditions, and how long the sensor would survive.
Datasheet goes up to 15 mW per cm2, with a default DUVfactor of ~1.61 the measurements could handle DUV of ~24 in theory._

https://edition.cnn.com/2021/11/03/americas/bolivia-heatwave-highlands-intl/index.html


## Sensor sensitivity

Indoors there is very little or no UV light so use a known UV source like 
a black-light or go outside in the sun.

The formula to convert the ADC reading to mW cm^2 is based upon the graph 
shown in the datasheet. As I have no reference source to calibrate the library
the accuracy is limited at best. If you know of a calibrated source please let me know.

The sensor has its peak sensitivity ( >80% ) from λ = 300-380 nm 
with an absolute peak at λ = 365 nm.


## Experimental DUVindex

Note: this library is **NOT** calibrated so **USE AT OWN RISK**

The DUV index can be used for warning for sunburn etc.


#### DUV index table

Based upon https://en.wikipedia.org/wiki/Ultraviolet_index,

|  DUV INDEX  |  Description  |
|:-----------:|:--------------|
|    0 - 2    |   LOW         |
|    3 - 5    |   MODERATE    |
|    6 - 7    |   HIGH        |
|    8 - 10   |   VERY HIGH   |
|    11+      |   EXTREME     |



#### Calibrate estimateDUVindex()

To calibrate the **estimateDUVindex()** function one needs to determine the DUVfactor. 
To do this you need an external reference e.g. a local or nearby weather station. 
You need to make multiple measurements during the (preferably unclouded) day and 
calculate the factor.

```
          DUV from weather station
factor = --------------------------
                  getUV();
```

you do this e.g. once per hour, so you get multiple values.
You can then average them to have a single factor.

Hardcode this found value in the library (in the constructor) or better
use the **setDUVfactor(factor)** call in **setup()** to calibrate your sensor.


## Version info

#### 0.1.5 and before

The formula for the experimental **estimateDUVindex(mWcm2)** is based on
the following facts / assumptions:
- (fact) The sensor cannot differentiate between wavelengths, 
so integration with different weights is not possible.
- (assumption) All the UV is radiated at λ = 300 nm. 
This is the most lethal the sensor can sense > 80%.
- (choice) All the UV is accounted for 100% for the whole value. 
(Erythemal action spectrum) 
As we cannot differentiate wavelengths, this is the safest choice.


#### 0.1.6 

The formula is simplified to a single factor that the user needs to determine.
Below is described how to do the calibration. 



## External ADC

**float voltage2mW(float voltage)** can be used for an external ADC e.g ADS1015,
ADS1115 or one of the (fast) MCP_ADC's.

- https://github.com/RobTillaart/ADS1X15 
- https://github.com/RobTillaart/MCP_ADC


## More about UV

https://en.wikipedia.org/wiki/Ultraviolet_index


## Future

#### Must
- improve documentation
- refactor / reorganize readme.md

#### Should
- test more
- get unit tests up and running
- investigate in calibration 
- check performance

#### Could
- investigate serial UV communication with UV led
- voltage2mW -> handle negative voltages by taking abs value?

#### Wont


