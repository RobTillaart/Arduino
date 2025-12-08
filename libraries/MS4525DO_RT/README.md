
[![Arduino CI](https://github.com/RobTillaart/MS4525DO_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MS4525DO_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MS4525DO_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MS4525DO_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MS4525DO_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MS4525DO_RT.svg)](https://github.com/RobTillaart/MS4525DO_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MS4525DO_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MS4525DO_RT.svg?maxAge=3600)](https://github.com/RobTillaart/MS4525DO_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MS4525DO.svg)](https://registry.platformio.org/libraries/RobTillaart/MS4525DO)


# MS4525DO

Arduino library for the I2C MS4525DO pressure and temperature sensor.


## Description

**Experimental**

The MS4525DO library can read the I2C version of the sensor and return the 
pressure in millibar or PSI. 
Furthermore the library provides temperature in Celsius or Fahrenheit.

Pressure is measured in 14 bit = 16384 "steps", from which 80% (type A) 
or 90% (type B) are actually used. 
This means 13107 or 14745 steps for the full range, giving at least 3 
significant digits.

Temperature is measured in 11 bit = 2048 "steps" all used. 
The range is -50-150 degrees C.

Note: library is based upon I2C_ASDX library.

Note: the library does not support the SPI version of the sensor.

Feedback, as always, is welcome.


### Types

Type numbers look like 4525DO – DS 3 B K 030 D P M -   see datasheet for details.

|  field         |  value                  |  notes  |
|:---------------|:------------------------|:--------|
|  Package Type  |  DS                     |
|  Voltage       |  3 = 3.3V; 5 = 5.0V     |
|  Output Type   |  A (10-90) or B (5-95)  |
|  Interface     |  S = SPI, other = I2C   |  0x28,0x36,0x46,0x48..0x51
|  Pressure PSI  |  150,100,50,30,15,5,2,1 |
|  Pressure Type |  D,G,V,A,C              |
|  Pin Type      |  P,S,L                  |
|  Option Type   |  F,L,M (blank)          |


### Hardware connection

Always check datasheet for the exact pins.

```
      MS4525DO            ARDUINO
    +----------+        +----------+
    |          |        |          |
    |     GND o|--------|o GND     |
    |     VCC o|--------|o VCC     |
    |     SDA o|--------|o SDA     |
    |     SCL o|--------|o SCL     |
    |          |        |          |
    +----------+        +----------+
```


### Related

- https://github.com/RobTillaart/pressure - pressure conversions
- https://github.com/RobTillaart/Temperature - temperature conversions 
- https://github.com/RobTillaart/I2C_ASDX - (I2C) pressure + conversions 
- https://github.com/RobTillaart/MS4525DO - (I2C) temperature pressure sensor 
- https://github.com/RobTillaart/MS5837 - (I2C) temperature pressure sensor  (incl pressure to altitude)
- https://github.com/RobTillaart/MS5611 - (I2C) temperature pressure sensor  (incl pressure to altitude)
- https://github.com/RobTillaart/MSP300 - (I2C) industrial pressure transducer
- https://swharden.com/blog/2017-04-29-precision-pressure-meter-project/



## I2C

Valid addresses are: 0x28,0x36,0x46,0x48..0x51 (interface type, I,J,K,0..9).


## Interface

```cpp
#include "MS4525DO.h"
```


### Constructor

- **MS4525DO(uint8_t address, TwoWire \*wire = &Wire)** Constructor,
I2C address and optional the wire (I2C bus) interface can be defined.
- **bool begin(uint8_t psi, char type = 'A')** sets the maximum PSI
and the device type ('A' or 'B') and initializes internals.
Allowed values for psi parameter: 150, 100, 50, 30, 15, 5, 2, 1
Returns true if address can be found on the I2C bus.
- **void reset()** resets the internal variables, including pressure and temperature.
- **bool isConnected()** tests if the I2C address can be found on the I2C bus.
- **uint8_t getAddress()** returns the I2C address used.
Mainly for debug message.


### Read

Before any call to **getMilliBar()** or **getTemperature()** one need to call **read()** unless one wants the last value read.

- **int read()** actually reads the sensor, checks for errors,
calculates the pressure and temperature and set the lastRead timestamp.
Returns **MS4525DO_OK** or an error code.
- **float getMilliBar()** returns pressure in milliBar.
Returns 0 after a reset() and if no read() has been done yet.
Calling **getMilliBar()** (Or any of the other pressure functions) multiple times
without read() will return the same value again.
- **float getPSI()** returns pressure in PSI = Pounds per Square Inch.

Related library: https://github.com/RobTillaart/pressure additional conversions.

- **float getCelsius()** returns temperature in Celsius.
- **float getFahrenheit()** returns temperatue in Fahrenheit.

Related library: https://github.com/RobTillaart/temperature additional conversions.


### State

- **uint16_t errorCount()** total counter for the number of errors occurred.
internal counter wraps after 65535.
- **uint32_t lastRead()** time in milliseconds of last successful read of the sensor.
- **int state()** last known state of read(), which is also returned by **read()**

|  state                   |  meaning             |
|:-------------------------|:---------------------|
|  MS4525DO_OK             |  no error            |
|  MS4525DO_INIT           |  begin() not called  |
|  MS4525DO_READ_ERROR     |  I2C error           |
|  MS4525DO_OVF_ERROR      |  sensor error        |
|  MS4525DO_CONNECT_ERROR  |  I2C error           |


### Debugging

Raw counter API, for debugging or your own conversion.

- **int rawPressureCount()** idem.
- **int rawTemperatureCount()** idem.


## Testing

TODO:

|  Type number        |  result  |  notes  |
|:--------------------|:--------:|:--------|
|                     |          |
|                     |          |
|                     |          |


## Future

#### Must

- update documentation.
- get hardware
- test
- keep in sync with I2C_ASDX

#### Should

- support Vacuum series transport function (page 6)
  - for now one might use P = -sensor.getPSI();

#### Could

- add examples
- add altitude code (from MS5837)
- improve state code after reset() and before read() ?
  - MS4525DO_NO_READ or MS4525DO_RESET?
- MS4525DO_OVF_ERROR should bits just be masked?
- int begin(float psi) to allow calibration or even arbitrary units.
  - return state?
- pressure in N/m2 => pitot formula. `v = sqrt(2 * pressure / rho);`
  - rho is specific weight in kg/m3, depends on humidity temperature and height.


#### Wont

-  move code from .h to .cpp


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

