
[![Arduino CI](https://github.com/RobTillaart/DMM/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DMM/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DMM/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DMM/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DMM/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DMM/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DMM.svg?maxAge=3600)](https://github.com/RobTillaart/DMM/releases)


# DMM = Digital MultiMeter.

Arduino library for a DMM class.


## Description

DMM is a class that uses the Arduino analogRead to make measurements.
It is based upon the UNO but will work on some other boards too.

The first version only works as a voltmeter, DC only.
It is meant to be extended in the future to be a complete Digital MultiMeter class.
that includes amps ohms, diode testing etc.

(this is an old 'toy' project, wrapped into a class)


#### Related 

- https://github.com/RobTillaart/ACS712 (current measurement).


## Interface

- **DMM()** constructor.

#### Configuration
- **begin(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023)** configuration. 
- **void  setMaxVoltage(float maxVoltage)**
- **float getMaxVoltage()**
- **void  setGain(float factor = 1.0)** GAIN e.g. due to voltage divider.
a 25V to 5V divider has a factor = 5.
- **float getGain()** returns the set gain.

#### Read
- **float readVolts(uint8_t times = 1)** read voltage. 
Times can be set to average multiple measurements.
- **float readMilliVolts(uint8_t times = 1)** convenience wrapper.

#### Calibration
- **float readNoise(uint8_t times = 1)** get noise level for accuracy.

## Operation

Basic operation is to connect the Arduino GND to the projects GND (or -)
and use the configured analog pin to measure (positive) voltage.

By adding a voltage divider one can measure larger voltages.
The divider factor can be set with **setGain(factor)**.

To elaborate.
- GND, VCC


## Future

#### Functional
- AMPS  (how -> measure voltage over a known resistor)
- OHM   (how -> known divider)
- DIODE (how -> 5V or 0V)
- CAPS  (how -> RC timing)


#### Must
- update documentation
- update examples
- add use of AREF 
  - external or internal 1.1 Volt


#### Should
- investigate noise
- analogReference(EXTERNAL) for external voltage for build in ADC
- support external ADC e.g. ADS1115 for 16 bit resolution.



#### Could
- multichannel compare
- schema for 
- scope functionality?


#### Won't


