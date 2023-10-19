
[![Arduino CI](https://github.com/RobTillaart/DMM/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DMM/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DMM/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DMM/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DMM/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DMM.svg)](https://github.com/RobTillaart/DMM/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DMM/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DMM.svg?maxAge=3600)](https://github.com/RobTillaart/DMM/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DMM.svg)](https://registry.platformio.org/libraries/robtillaart/DMM)


# DMM = Digital MultiMeter.

Arduino library for a DMM (digital multimeter) class.


## Description

DMM is a class that uses the Arduino analogRead to make measurements.
It is based upon the UNO but will work on some other boards too.

The first version only works as a voltmeter, DC only.
It is meant to be extended in the future to be a complete Digital MultiMeter class.
that includes amps ohms, diode testing etc.

This is an old 'toy' project, wrapped into a class. 
Do not expect high precision or accuracy.


#### Related

- https://github.com/RobTillaart/ACS712 (current measurement).


## Interface

```cpp
#include "DMM.h"
```

#### Constructor

- **DMM()** constructor.

#### Configuration

- **begin(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023)** configuration.
Note these are the specifications of the ADC used. 
- **void  setMaxVoltage(float maxVoltage)**
- **float getMaxVoltage()**
- **void  setGain(float factor = 1.0)** GAIN e.g. due to voltage divider.
A 25V to 5V divider has a factor = 5.
- **float getGain()** returns the set gain.


#### ReadVolts

One must connect GND of Arduino to the GND of the device.
```
    [A0]---- V unknown
   [GND]---- GND

or with a divider => setGain(x)

    [A0]----[divider]---- V unknown
   [GND]----[divider]---- GND

```

- **float readVolts(uint8_t times = 1)** read voltage.
Times can be set to average multiple measurements.
- **float readMilliVolts(uint8_t times = 1)** convenience wrapper.
- **float readNoise(uint8_t times = 1)** measure the noise on the wire.
Assumes connected to constant voltage e.g. GND.


#### ReadOhm

The schema for measuring resistors is based on a simple voltage divider.
See below. This schema can be extended with a selector switch that can
switch between different reference resistors.

```
   [GND] ----[ R reference ]----[A0]----[ R unknown ]----[+5V]
```

- **void setReferenceR(uint32_t ohm = 1000)** set the reference resistor.
units are Ohm, default = 1K.
- **uint32_t readOhm(uint8_t times = 1)** read ohm.
Times can be set to average multiple measurements.
- **uint32_t readKiloOhm(uint8_t times = 1)** read ohm.
Times can be set to average multiple measurements.

Character ohm = Ω  (ALT-234 or ALT-0216 might work)


#### Calibration

- **float readNoise(uint8_t times = 1)** get noise level for accuracy.


## Operation

Basic operation is to connect the Arduino GND to the projects GND (or - )
and use the configured analog pin to measure a (positive) voltage.

By adding a voltage divider one can measure larger voltages.
The divider factor can be set with **setGain(factor)**.

To elaborate.
- GND, VCC


## Future

#### Functional

- AMPS  (how -> measure voltage over a known resistor)
- CAPS  (how -> RC timing)
  - RC (load 5 seconds)
  - disconnect
  - measure drop rate / time in micros.
- DIODE (how -> 5V or 0V)
  - DigitalRead(INPUT PULLUP) => HIGH or LOW
  - or 0.7 volt drop from 5V


#### Must

- update documentation
- update examples
- add use of AREF
  - external or internal 1.1 Volt
- **float setOffset(float offset)** adjust the voltage used.
  - this is not the voltage the ADC uses internally.

#### Should

- investigate noise
- analogReference(EXTERNAL) for external voltage for build in ADC
- support external ADC e.g. ADS1115 for 16 bit resolution.

#### Could

- multichannel compare
- schema for
- scope functionality?

#### Won't


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


