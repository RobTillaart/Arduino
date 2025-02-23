
[![Arduino CI](https://github.com/RobTillaart/PCT2075/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCT2075/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCT2075/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCT2075/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCT2075/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCT2075.svg)](https://github.com/RobTillaart/PCT2075/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCT2075/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCT2075.svg?maxAge=3600)](https://github.com/RobTillaart/PCT2075/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCT2075.svg)](https://registry.platformio.org/libraries/robtillaart/PCT2075)


# PCT2075

Arduino library for I2C PCT2075 temperature sensor / thermal watchdog.


### Description

**Experimental**

The PCT2075 is a temperature sensor with a range of -55°C - 125°C,
an accuracy of ±2°C and 11 bit precision, steps = 0.125°C.
In the range -25°C - 100°C, the accuracy is ±1°C.
The sensor is a drop in replacement for the LM75.

The special feature of this sensor is an output pin OS = Overflow Shutdown,
which can be used to trigger external events based upon two different 
temperature levels. Thus for me OS stands for Output Signal.

This OS pin can be used in two modi, first and default is comparator 
mode, which is ideal to control e.g. a cooling or heating device.
This signal can also be used for interrupts, either CHANGE, FALLING
or RISING edge.
The second mode is an interrupt mode which can be used to trigger
a microprocessor with a short pulse.
Check the datasheet for the details.

Library is limited tested with an Arduino UNO.


### Please report your experiences.

If you have a PCT2075 device, please let me know your experiences
with the sensor and this (or other) library.

### I2C bus reset

See section 7.2.1 of datasheet how to implement this.
The library does not support this.


### Related

- https://github.com/RobTillaart/DHTNew DHT11/22 etc humidity / temperature sensor
- https://github.com/RobTillaart/DS18B20_RT OneWire temperature sensor
- https://github.com/RobTillaart/PCT2075 this library
- https://github.com/RobTillaart/SHT31 Sensirion humidity / temperature sensor
- https://github.com/RobTillaart/Temperature (conversions, dewPoint, heat index etc.)

There are more temperature libraries, just follow the links.


### Compatibles

The PCT2075 is a drop in replacement for the LM75, so this sensor
is expected to be compatible. To be verified.


## Interface

```cpp
#include "PCT2075.h"
```

### Constructor

- **PCT2075(const uint8_t address, TwoWire \* wire = &Wire)** set address to
reflect the A0..A2 pin. See table 5 + 6, page 8 datasheet for 27 possible addresses.
- **bool begin()** checks if address can be found on the I2C bus.
- **bool isConnected()** checks if address can be found on the I2C bus.
- **uint8_t getAddress()** returns address set.


### Configuration

- **void setConfiguration(uint8_t mask)** set all bits in configuration at once.
- **uint8_t getConfiguration()** return the current configuration bit mask.

COnfiguration register

|  bit  |  symbol       |  description  |
|:-----:|:--------------|:--------------|
|  7:5  |  reserved     |  not used
|  4:3  |  OS_F_QUE     |  fault queue, see datasheet for details
|   2   |  OS_POL       |  polarity, 0 = LOW (default), 1 = HIGH
|   1   |  OS_COMP_INT  |  mode flag, 0 = comparator (default), 1 = interrupt
|   0   |  SHUTDOWN     |  0 = normal (default), 1 = shutdown

Some wrapper functions for easy control.

- **setOSFQUE(uint8_t value)** 0..3, see table below.
See page 6 datasheet for details.
- **setOSPolarityLOW()** idem.
- **setOSPolarityHIGH()** idem.
- **setOSComparatorMode()** idem.
- **setOSInterruptMode()** idem.
- **wakeUp()** idem, starts making measurements. See datasheet 7.1.
Note it takes ~28 milliseconds to get a first new temperature reading.
- **shutDown()** idem, stops making measurements.

|  OS_F_QUE  |  times  |  notes  |
|:----------:|:-------:|:--------|
|     0      |   1x    |  default, OS triggers on first occurrence
|     1      |   2x    |
|     2      |   4x    |
|     3      |   6x    |  OS triggers on sixth occurrence


### Temperature

- **float getTemperature()** Returns -25°C to +100°C.
Accuracy = ±1°C, precision = 0.125°C.

New measurements are made continuously, and the frequency of that process
can be set with **setSampleDelay()**, see below.
The sampling process can be stopped and restarted by using **shutDown()**
and **wakeUp()**, see above.

Reading the temperature does not affect the conversion in progress.


### Operating mode OS, interrupt vs comparator.

The OS pin (Overtemp Shutdown) of the PCT2075 can generate pulses to trigger 
interrupts or follow hysteresis to control an external device. 
The OS pin is default HIGH, and goes LOW when "active".
The polarity can be changed in the configuration register (see above).

The behaviour can be tuned by **setOSFQUE(value)** in the configuration
register. This defines the number of times a threshold needs to be crossed
before the OS pin toggles. See page 6 datasheet.  

In **comparator mode** the OS pin goes 
- LOW, when the temperature RISES above the configured overTemperature.
- HIGH, when the temperature FALLS below the configured hysteresis temperature.

This makes the comparator mode ideal e.g. to **directly** control a fan, a 
cooling or heating system. Additional electronics like a relay might be needed.

In **interrupt mode** the OS pin gives a LOW pulse when the temperature
- RISES above the configured overTemperature, or
- FALLS below the configured hysteresis temperature.

This makes the interrupt mode ideal to send a signal to a microprocessor which
can take an action, e.g. send a message to people or write it to a log file.

Read datasheet section 7.1 for details

- **void setHysteresis(float temp)** set lower temperature trigger level.
- **float getHysteresis()** get current set level. Default = 75°C.

- **void setOverTemperature(float temp)** set upper temperature trigger level.
- **float getOverTemperature()** get current set level. Default = 80°C.

It is not known how the sensor behaves when the lower temperature is set
above the upper temperature. The library does not prevent this.


### Sample frequency

Allows the time between the automatic samples to be in steps of 100 milliseconds.
This allows to save energy. 
The temperature sampling itself takes about 28 milliseconds.

- **void setSampleDelay(uint8_t steps = 1)**  steps = 0..31, 1 step == 100 ms  (0==1).
So timing can be set from 100 ms to 3.1 seconds.
- **uint8_t getSampleDelay()** Returns set value (steps).


### Error handling

- **uint16_t  lastError()** for now to check I2C error.

## Future

#### Must

- improve documentation
- test with hardware

#### Should

#### Could

- extend error handling
- add examples
- add **void setOffset()** and **float getOffset()** to calibrate temperature.
  - drawback is that this does not affect the two threshold registers.
  - can cause confusion (so at least a warning should be in place)
- getters for configuration fields.
  - **uint8_t getXYZ()**
  - **bool isAwake()**

#### Wont

- section 7.2.1 => controllable reset?
  - blocking for 35 ms? ==> User can do that.
- detailed getters for configuration register.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

