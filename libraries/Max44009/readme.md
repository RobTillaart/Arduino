
[![Arduino CI](https://github.com/RobTillaart/MAX44009/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX44009/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX44009/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX44009/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX44009/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX44009.svg)](https://github.com/RobTillaart/MAX44009/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX44009/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX44009.svg?maxAge=3600)](https://github.com/RobTillaart/MAX44009/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX44009.svg)](https://registry.platformio.org/libraries/robtillaart/MAX44009)


# MAX44009 I2C LUX sensor

Library for MAX44009 / GY-49 I2C lux sensor.


## Description

a.k.a. GY-49

The MAX44009 ambient light sensor is an I2C sensor, that has a 22 bit
dynamic range from 0.045 lux to 188,000 lux.


#### MAX44007

The MAX44007 is an almost identical sensor that uses a step size of 0.025.
This implies that this library is not useable 1 to 1 for the MAX44007, however some parts will work.


#### Related

- https://github.com/RobTillaart/Max44007  (range 0.025 lux to 104,448 lux)
- https://github.com/RobTillaart/Max44009  (range 0.045 lux to 188,000 lux)


## Schema breakout max44009 / GY-49


```cpp
//       breakout MAX44009 / GY-49
//
//          +--------+
//      VCC |o       |
//      GND |o       |
//      SCL |o      o| ADDRESS
//      SDA |o      o| -INT
//          +--------+
//
//  ADDRESS:
//  0 = 0x4A
//  1 = 0x4B
//
//  INT:
//  Connect the INT pin to an pull up resistor
//  0 = interrupt
//  1 = no interrupt
//  connect to an LED or an interrupt pin of an Arduino
//
```

## I2C

#### Address

The MAX44009 can have 2 addresses:

- 0x4A = **MAX44009_DEFAULT_ADDRESS**
- 0x4B = **MAX44009_ALT_ADDRESS**

See schema above.


#### I2C multiplexing

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


#### I2C Performance

Performance of the getLux function in microseconds.

|  Clock   |   UNO   |  ESP32  |  Notes  |
|:--------:|:-------:|:-------:|:-------:|
|  100000  |         |         |
|  200000  |         |         |
|  300000  |         |         |
|  400000  |         |         |
|  500000  |         |         |
|  600000  |         |         |

TODO fill table.


## Interface

```cpp
#include "Max44009.h"
```

### Constructor

- **Max44009(const uint8_t address = MAX44009_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)** Constructor.
Optional address and optional I2C interface.\
- **bool isConnected()** returns true if the device address configured is available on I2C bus.
- **uint8_t getAddress()** returns device address. Convenience function.

NOTE: The user must call **Wire.begin()** or **Wire.begin(SDA, SCL)** in **setup()**.


### Basic

- **float getLux()** read the sensor and return the value in LUX. If the value is negative, an error has occurred.
- **int getError()** returns last error.

```cpp
// ERROR CODES
#define MAX44009_OK                     0
#define MAX44009_ERROR_WIRE_REQUEST    -10
#define MAX44009_ERROR_OVERFLOW        -20
#define MAX44009_ERROR_HIGH_BYTE       -30
#define MAX44009_ERROR_LOW_BYTE        -31
```


### Configure thresholds

check datasheet for details

- **bool setHighThreshold(float value)** sets the upper threshold for the interrupt
generation (INT pulls LOW). Works only if INTE bit is set by **enableInterrupt()**.
Function returns false if the value is out of range.
- **float getHighThreshold()** returns the value set.
- **bool setLowThreshold(float value)** sets the lower threshold for the interrupt
generation (INT pulls LOW). Works only if INTE bit is set by **enableInterrupt()**.
Function returns false if the value is out of range.
- **float getLowThreshold()** returns the value set.
- **void setThresholdTimer(uint8_t value)** Time the threshold needs to be exceeded,
defined in steps of 100ms. 2 seems to be a practical minimum.
- **uint8_t getThresholdTimer()** returns the value set.


### Configure interrupts

check datasheet for details

- **void enableInterrupt()** enables the upper and lower threshold interrupts.
- **void disableInterrupt()** disables the threshold interrupts.
- **bool interruptEnabled()** returns 1 if the interrupt mode is enabled.
- **uint8_t getInterruptStatus()** returns 1 if an interrupt has occurred.


### Configure flags

check datasheet for details

- **void setConfiguration(uint8_t)** writes directly to configuration register.
**warning** Use with care.
- **uint8_t getConfiguration()** reads the current configuration register.


### Configure sample mode

Check datasheet for details.

CDR = Current Divisor Ratio.

TIM = Integration time.

- **void setAutomaticMode()** in automatic mode the MAX44009 determines the CDR and TIM
parameters.
- **void setContinuousMode()** continuous mode uses more power than a "single" conversion.
Advantage is that the latest data is always available fast.
- **void clrContinuousMode()** uses less power so better for LOW power configurations.
- **void setManualMode(uint8_t CDR, uint8_t TIM)** Set the Current Divisor Ratio and the
integration time manually. Effectively disable automatic mode.
- **int getIntegrationTime()** returns the set integration time in milliseconds.
Note these are rounded down (12 == 12.5 and 6 == 6.25) to minimize math.
- **int getCurrentDivisorRatio()** returns the set Current Divisor Ratio.
This is either 0 (full intensity) or 1 (1/8th intensity).

```
    CDR = Current Divisor Ratio
    CDR = 1 ==> only 1/8th is measured

    TIM = Time Integration Measurement (table)
    000   800ms
    001   400ms
    010   200ms
    011   100ms
    100    50ms       manual only
    101    25ms       manual only
    110    12.5ms     manual only
    111     6.25ms    manual only
```


### Test functions

Function for the conversion math, not meant to be used directly,
but by making it public the math becomes testable.

- **float convertToLux(uint8_t dataHigh, uint8_t dataLow)** convert intern register
format to a LUX value.


## Examples

**Max44009\examples\max44009_test01**
- use for e.g. UNO (use voltage convertor!)

**Max44009\examples\max44009_test02**
- will **not** compile for UNO
- use for e.g. ESP32


## Notes

Please be aware this is a **3.3 Volt device** so it should not be connected
to an Arduino UNO or other 5 Volt device directly.
Use a level convertor to solve this.

Do not forget to connect the address pin as you cannot read the sensor
in a reliable way. As the line will float it will sometimes have the
right address and sometimes not. (been there ;)

Pull ups on I2C bus are recommended.


## Future

#### Must

- improve documentation
- buy hardware

#### Should

- run performance test on UNO and ESP32.

#### Could

- merge MAX44007 / MAX44009 library in the future. (shared base class?)
- read data high and low in one call?
- convertToLux() overflow test, when exponent == 15.

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

