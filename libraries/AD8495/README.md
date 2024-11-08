
[![Arduino CI](https://github.com/RobTillaart/AD8495/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD8495/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD8495/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD8495/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD8495/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD8495.svg)](https://github.com/RobTillaart/AD8495/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD8495/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD8495.svg?maxAge=3600)](https://github.com/RobTillaart/AD8495/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD8495.svg)](https://registry.platformio.org/libraries/robtillaart/AD8495)


# AD8495

Arduino library for the AD8494, AD8495, AD8496 and AD8497 thermocouple.


## Description

**Experimental**

The library is NOT tested with hardware yet.

The AD8494/AD8495/AD8496/AD8497 are precision instrumentation amplifiers 
for J and K thermocouples. The devices output 5 mV/°C output.

The AD8494/AD8495/AD8496/AD8497 allow a wide variety of supply voltages. 
With a 5 V single supply, the 5 mV/°C output allows the devices to cover 
nearly 1000 degrees of a thermo-couple’s temperature range. 

The AD8494/AD8495/AD8496/AD8497 also work with 3 V supplies,
allowing them to interface directly to 3V3 processors like ESP32.
They work up to 36 V, think of industrial or automotive systems.

The library supports positive temperatures only.


### Performance

As the device needs an **analogRead()** and a few float operations, the 
performance depends mostly on the duration of the **analogRead()**.


### Modi

The AD849x can be configured in 2 different operational modi:
- In measurement mode, connect sense pin to output, this is "normal" mode.
- in setpoint mode, connect sense pin to setpoint voltage.

In the setPoint mode the OUT voltage will drop to -Vcc if the temperature
drops below the setpoint voltage.

See datasheet for details.

The library does not provide means to switch between these modi.


### Compatibles


|  device  |  TC  |  accuracy  |  range            |  Notes  |
|:--------:|:----:|:----------:|:-----------------:|:-------:|
|  AD8494  |  J   |  ±2°C      |  −35°C to  +95°C  |  J = iron-constantan
|  AD8495  |  K   |  ±2°C      |  −25°C to +400°C  |  K = chromel-alumel
|  AD8496  |  J   |  ±2°C      |  +55°C to +565°C  |
|  AD8497  |  K   |  ±2°C      |  −25°C to +295°C  |

Note the library supports only positive temperatures.

See datasheet page 15, how to handle negative temperatures.


### Hardware


```
              TOPVIEW AD8495
          +--------------------+
          |                    |
    - IN  | 1                8 |  + IN
     REF  | 2                7 |  + Vs
    - Vs  | 3                6 |  OUT
      NC  | 4                5 |  SENSE
          |                    |
          +--------------------+
```

|  pin  |   name  |  description      |  Notes  |
|:-----:|:-------:|:------------------|:-------:|
|   1   |   - IN  |  Negative Input   |
|   2   |    REF  |  Reference.       |
|   3   |   - Vs  |  Negative Supply. |
|   4   |     NC  |  not connected    |
|   5   |  SENSE  |  Sense Pin        |
|   6   |    OUT  |  Output voltage   |
|   7   |   + Vs  |  Positive Supply  |
|   8   |   + IN  |  Positive Input   |


Sense Pin: 
- In measurement mode, connect to output; 
- in setpoint mode, connect to setpoint voltage.


### Related

- https://github.com/RobTillaart/AD8495
- https://github.com/RobTillaart/MAX6675
- https://github.com/RobTillaart/MAX31850
- https://github.com/RobTillaart/MAX31855_RT
- https://github.com/RobTillaart/Temperature

- https://www.analog.com/media/en/technical-documentation/data-sheets/ad8494_8495_8496_8497.pdf
- https://www.analog.com/en/resources/app-notes/an-1087.html


## Interface

```cpp
#include "AD8495.h"
```

### Constructor

- **AD849x(int analogPin, int steps, float maxVoltage)** constructor base class.
- **AD8494(int analogPin, int steps, float maxVoltage)** constructor.
- **AD8495(int analogPin, int steps, float maxVoltage)** constructor.
- **AD8496(int analogPin, int steps, float maxVoltage)** constructor.
- **AD8497(int analogPin, int steps, float maxVoltage)** constructor.


### Base

- **float getPrecision()** returns voltage LSB. Debugging.
- **float getVoltage(int times = 1)** returns voltage as average 
of times readings.
- **float voltageToTemperatureC(float voltage)** conversion function,
Can be used when using an external ADC to read the AD849x device.
- **float getTemperatureC(int times = 1)** returns temperature Celsius 
as average of times readings. 
Larger values of times take more time and give a better precision.
- **float getTemperatureF(int times = 1)** returns temperature Fahrenheit 
as average of times readings. Wrapper around getTemperatureC().


### Offset

Used to calibrate a measurement with an offset **in °Celsius**.
The effect is that the offset will be 1.8 x larger for **getTemperatureF()**.
Can be used to make the temperature scale Kelvin by adding an offset of 273.15.
Note that the library will still not measure below zero °C.

- **void setOffset(float offset = 0)** idem, typical between -2.0 and 2.0.
- **float getOffset()** returns set offset.


### SetPoint mode

Read datasheet for details.

In the setPoint mode the **OUT** voltage will drop to -Vcc if the temperature
drops below the setpoint voltage which is connected to the **SENSE** pin

This setPoint mode allows the AD849x to guard a defined temperature level. 
Be aware that the accuracy is still about +-2 degrees Celsius.

- **float getSetPointVoltage(float Temperature)** helper function to 
calculate the needed setPoint voltage in milliVolts.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- investigate transfer functions (from application notes) for 95/96/97
- need yield(); for RTOS?

#### Could

- example external ADC e.g. ADS1115

#### Wont

- add getType()
- add getTemperatureK(), Kelvin

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


