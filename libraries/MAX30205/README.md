
[![Arduino CI](https://github.com/RobTillaart/MAX30205/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX30205/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX30205/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX30205/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX30205/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX30205.svg)](https://github.com/RobTillaart/MAX30205/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX30205/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX30205.svg?maxAge=3600)](https://github.com/RobTillaart/MAX30205/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX30205.svg)](https://registry.platformio.org/libraries/robtillaart/MAX30205)


# MAX30205

Arduino library for the MAX30205, I2C, 16 bit, high accuracy temperature sensor.


## Description

**Experimental**

This library is to use MAX30205 high accuracy (16 bits) temperature sensor.

This library is work in progress and needs testing with actual hardware.
So feedback is welcome!

The MAX30205 temperature sensor is especially meant for skin contact measurements in the range 0..50°C.
It has a high accuracy in the human temperature range, see table.

|   range °C       |  accuracy  |  notes  |
|:----------------:|:----------:|:-------:|
|  0°C to 15°C     |    ±0.5°C  |
|  15°C to 35.8°C  |    ±0.3°C  |
|  35.8°C to 37°C  |    ±0.2°C  |
|  37°C to 39°C    |    ±0.1°C  |
|  39°C to 41°C    |    ±0.2°C  |
|  41°C to 45°C    |    ±0.3°C  |
|  45°C to 50°C    |    ±0.5°C  |

The MAX30205 is a 3.3V device so do not connect it to a 5V as this can
or will harm the sensor. If needed use a voltage convertor or use an
appropriate board that supports the 5V.

The conversion time is about 50 ms or a bit less.

The datasheet states that the sensor operates between 0 and 50 degrees Celsius,
and at the same time the datasheet shows the sensor provides a sign bit.
There is also a bit in the configuration register to set an extended temperature
range.
This library handles the sign bit as a sign bit as it not verified what the sensor
does when freezing in normal vs extended mode.

The MAX30205 has an OUTPUT (OS) pin that can be used as an over temperature
alarm, thresholds or interrupts.
This OUTPUT pin needs more investigation how this works in detail.

Feedback as always is welcome.


### Special characters

ALT241 = ±
ALT0176 = °


### Warning

Disclaimer!

_Do not apply this product to safety protection devices or emergency stop equipment,
and any other applications that may cause personal injury due to the product's failure._

### Fever

Disclaimer!

The temperature of the human body can be too low, normal or too hot.
The first case is called hypothermia, the latter case is called fever.
There are no official temperature ranges for fever, so the table below 
is indicative and definitely no medical advice or whatsoever.

The colour codes are no standard either but could be used as a visual 
indication of the temperature measured. 
One can use - https://github.com/RobTillaart/map2colour for this.

|  Celsius     |  description      |   colour  |  action  |
|:-------------|:------------------|----------:|:---------|
|  below 35.0  |  hypothermia      |   PURPLE  |  doctor
|  35.0..36.0  |  low temperature  |     BLUE  |
|  36.0..37.2  |  Normal           |    GREEN  |
|  37.5..38.0  |  low grade fever  |   YELLOW  |
|  38.0..38.9  |  mild fever       |   ORANGE  |  doctor
|  39.0..39.9  |  high fever       |      RED  |  doctor
|  40.0 and up |  very high fever  |      RED  |  doctor

- Armpit measures 0.3-0.6°C lower.
- Oral measures 0.0-0.2°C lower.


### Hardware


```
             TOPVIEW MAX30205
         +--------------------+
         |                    |
   pin 1 | o                o |  pin 8
   pin 2 | o                o |  pin 7
   pin 3 | o                o |  pin 6
   pin 4 | o                o |  pin 5
         |                    |
         +--------------------+
```

|  pin  |  name  |  description          |  notes  |
|:-----:|:--------:|:--------------------|:-------:|
|   1   |  SDA     |  I2C data           |  3-5V
|   2   |  SCL     |  I2C clock          |  3-5V
|   3   |   OS     |  OverTemp Shutdown  |  Open-drain. use pull-up resistor.
|   4   |  GND     |  Ground             |
|   5   |   A2     |  address pins       |  see datasheet
|   6   |   A1     |  address pins       |
|   7   |   A0     |  address pins       |
|   8   |  VDD     |  +3.3V              |  Bypass GND with 0.1μF cap


### Compatibles

There are no known compatible sensors.


### Related

- https://github.com/RobTillaart/MAX30205 - this library
- https://github.com/RobTillaart/DS18B20_RT - well known temperature sensor
- https://github.com/RobTillaart/PCT2075 - bit I2C temperature sensor with thermal watchdog.
- https://github.com/RobTillaart/SHT85 - Sensirion humidity / temperature sensor
- https://github.com/RobTillaart/Temperature - conversions and more.
- https://github.com/RobTillaart/map2colour - mapping a float to colours

Other MAX30205 libraries

- https://github.com/Protocentral/Protocentral_MAX30205


### Tested

TODO: need hardware


## I2C

### I2C Address

The device has three address lines and depending on connection a different address
can be chosen. The full range is 32 addresses, 0x40..0x5F ==> decimal 64..95

See datasheet for the full range of connections needed.
Note the datasheet mentions the shifted addresses (x 2).


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


### I2C Performance

Only test **read()** as that is the main function called most.

|  Clock     |  time (us)  |  Notes  |
|:----------:|:-----------:|:--------|
|   100 KHz  |             |  default
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |  max per datasheet


TODO: run performance sketch on hardware.


## Interface

```cpp
#include "MAX30205.h"
```

### Constructor

- **MAX30205(uint8_t address, TwoWire \*wire = &Wire)** optional select I2C bus.
- **bool begin()** checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns the fixed address 0x2A (42).


### Read

Note there must be 44-50 ms between read() calls, otherwise an
**MAX30205_READ_TOO_FAST (0x12)** will be returned.

The datasheet mentions to use a sample period larger than 10 seconds to
eliminate self-heating effects. The user can use lastRead() for this.

- **int read()** returns MAX30205_OK after a successful read of the temperature, an error code otherwise. 
- **float getTemperature()** returns the last successful read temperature.
- **float getAccuracy()** returns the maximum error e.g. 0.3 => ±0.3°C.
This is based on 3 sigma from datasheet. The actual error is probably smaller.
- **uint32_t lastRead()** returns timestamp of last read call.


### Configuration mask

See datasheet page 12, 13

- **void setConfig(uint8_t mask = 0x00)** allows to set the configuration
register in one call. The default is the POR (Power On Reset) value 0x00.
- **uint8_t getConfig()** read back configuration register.

### Configuration field

See datasheet page 12, 13

These functions set the configuration register per bit(s).

- **void shutDown()** idem
- **void wakeUp()** idem
- **void setModeComparator()** see datasheet
- **void setModeInterrupt()** see datasheet
- **void setPolarity(uint8_t polarity = LOW)** polarity = LOW HIGH
- **void setFaultQueLevel(uint8_t level = 0)** level = 0..3
- **void setDataFormat(uint8_t range = 0)** range = 0 => 0..50;
range = 1 => extended (slower).
Changing dataformat takes at least 2 read times = 100ms.
Note The minimum and maximum of the extended range is not defined
in the datasheet.
- **void setTimeout(uint8_t timeout = 0)** timeout = 0, 1, used to suppress
I2C bus reset when SDA is LOW for more than 50 ms.
- **void setModeContinuous()** Continuous implies wakeup.
- **void setModeOneShot()** OneShot implies shutdown.


### Hysteresis and OverTemperature

See datasheet page 8

- **bool setHysteresis(float Celsius = 75)**
- **float getHysteresis()**
- **bool setOverTemperature(float Celsius = 80)**
- **float getOverTemperature()**

See Comparator mode and Interrupt mode below.


### Error handling

To be elaborated

- **uint16_t lastError()** returns last error of the communication.

|  code                    |  value  |  notes  |
|:-------------------------|:-------:|:--------|
|  MAX30205_OK             |   0x00  |
|  MAX30205_NOT_READY      |   0x10  |
|  MAX30205_REQUEST_ERROR  |   0x11  |
|  MAX30205_READ_TOO_FAST  |   0x12  |  wait up to 50 ms before read().
|  other                   |         |


## Comparator mode

Datasheet Figure 2. OS Output Temperature Response Diagram

The OS pin is open drain so a pull up resistor is needed to pull the output to HIGH.

By calling **setModeComparator()** the MAX30205 OS pin has the following behaviour.

- Default the OS output is HIGH (by means of the pull up resistor).
- if the temperature rises above the value in the over-temperature register,
the OS output goes to LOW.
- if the temperature drops below the value in the hysteresis register,
the OS output goes to HIGH again.

The values in the registers can be changed with 
- **setOverTemperature(float Celsius = 80)** and
- **setHysteresis(float Celsius = 75)**

Note one might need to also set the extended temperature range with 
**setDataFormat(1)** to get this working.
Furthermore one might need to **setPolarity()** to get the signal needed.
Finally one might set the **setFaultQueLevel()** to determine the number of
consecutive reads to trigger an OS change. Used to suppress noise.

The comparator mode is ideal to use the sensor as a thermostat e.g. to control
a fan, a heater, an alarm etc.

TODO: verify with hardware.


## Interrupt mode

Datasheet Figure 2. OS Output Temperature Response Diagram

The OS pin is open drain so a pull up resistor is needed to pull the output to HIGH.

By calling **setModeInterrupt()** the MAX30205 OS pin has the following behaviour.

- Default the OS output is HIGH (by means of the pull up resistor).
- it waits until if the temperature rises above the value in the over-temperature register, if so the OS output goes to LOW.
- when the sensor is **read()** the OS output goes HIGH again.
- then it waits until the temperature drops below the value in the hysteresis register, if so the OS output goes to LOW.
- if the sensor is **read()** the OS output goes HIGH again.

So the interrupt is triggered **alternately** by the OS and hysteresis register value.

The values in the registers can be changed with 
- **setOverTemperature(float Celsius = 80)** and
- **setHysteresis(float Celsius = 75)**

Note one might need to also set the extended temperature range with 
**setDataFormat(1)** to get this working. 
Furthermore one might need to **setPolarity()** to get the signal needed.
Finally one might set the **setFaultQueLevel()** to determine the number of
consecutive reads to trigger an OS change. Used to suppress noise.

The interrupt mode assumes when the temperature is HIGH, an action is taken 
that lowers the temperature. When the lower threshold is met a new interrupt
is triggered which allows to take another action.

Note: there are no additional interrupts if the temperature "dances" around
the value in the OS register.

TODO: verify with hardware.


## Future

#### Must

- improve documentation
- get hardware to test

#### Should

- add examples
  - interrupt

#### Could

- create unit tests if possible
- improve error handling

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


