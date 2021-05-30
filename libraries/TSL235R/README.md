
[![Arduino CI](https://github.com/RobTillaart/TSL235R/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TSL235R/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TSL235R.svg?maxAge=3600)](https://github.com/RobTillaart/TSL235R/releases)


# TSL235R

Arduino library for the TSL235R light to frequency convertor.


## Description

This library does not measure the frequency but has some functions to compensate e.g. 
for wavelength and voltage used.

The library is not tested extensively yet.

The sensor operating voltage is between 2.7 and 5.5 max.

For measurements below 1uW/cm2 one bests measures for multiple seconds
Above 1 uW/cm2 1 second or shorter is OK. 

Note that for longer and shorter measurements than 1 second one must convert the
value to Hz, which is the nr of pulses in 1 second.


## Connection

```
// PIN 1 - GND
// PIN 2 - VDD      2.7 V .. 5.5 V
// PIN 3 - SIGNAL   1 Hz  .. 800 KHz
```


## Interface

- **TSL235R(float voltage = 5.0)** constructor, optionally one can give the operational voltage 
to add a small correction (< 1.5%)
- **float irradiance(uint32_t Hz)** returns the irradiance in uW/cm2.
NOte that Hz implies the measured pulses for 1 second.
- **float irradiance(uint32_t pulses, uint32_t milliseconds)** returns the irradiance in uW/cm2
This formula is used for other duration than 1 second.
To get irradiance in W/m2 one must divide by 100.
- **float getFactor()** returns the inner conversion factor from Hz to Watt/cm2.
- **void setWavelength(uint16_t wavelength = 635)** sets the wavelength so the formulas can use a correction factor. At the default wavelength of 635 nm the wavelength correction factor == 1.0
- **uint16_t getWavelength()** returns the set wavelength. Convenience function.
- **float getWaveLengthFactor()** returns the wavelength correction factor. 
As the sensor is most sensitive around 750 nm this value helps to normalize the signal.
This works only for (almost) monochomatic light.
- **void setVoltage(float voltage)** sets the voltage so the formulas can use a correction factor.
This voltage correction factor is rather small < 1.5%
- **float getVoltage()** returns the set voltage. Convenience function.


## Operations

See examples for typical usage.


## Future

- investigate correction factor for white light and mixed light sources.
