
[![Arduino CI](https://github.com/RobTillaart/DS1821/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DS1821/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DS1821.svg?maxAge=3600)](https://github.com/RobTillaart/DS1821/releases)

# DS1821

Arduino library for DS1821 temperature sensor (experimental)

## Description

The DS1821 is a temperature sensor that uses the oneWire protocol.
This library supports one sensor per pin.
As this library is tested minimally please consider it experimental.

The sensor is hard to get however still available on internet.

## Interface (temperature sensor)

The interface of the library is an async interface so there are no blocking calls.

The return value **DS1821_RESET_ERROR == -999** means that the oneWire bus failed to reset.

- **DS1821(onewire)** initializes the library with a reference to a oneWire object.  
See examples.
- **int requestTemperature()** this call will trigger a conversion of temperature,
however it does not read the temperature. May return **DS1821_RESET_ERROR**
- **int conversionReady()** when the conversion is ready it returns 1, else 0.  
May return **DS1821_RESET_ERROR**
- **float readTemperature()** when conversion is ready, one can fetch the temperature.  
May return **DS1821_RESET_ERROR**
- **int error()** read the last error.

The low / high functions can be used to monitor if a threshold has been exceeded
between reads of the temperature.

- **setLow(lo)** set low (OFF) threshold temperature
- **getLow()** read back from config
- **setHigh(hi)** set high (ON) threshold temperature
- **getHigh()** read back from config.
- **getHighFlag()** flag is set if temperature has exceeded high threshold.
- **clrHighFlag()** reset the high threshold flag
- **getLowFlag()** flag is set if temperature has exceeded low threshold.
- **clrLowFlag()** reset the low threshold flag


## Interface (thermostat)

Please read datasheet.

The DS1821 can be setup as a standalone thermostat with a high level and low level.
In this mode the DS1821 uses the **DQ** pin to switch a device ON when the high level
is exceeded and switches OFF when the low level is reached. 
This prevents too frequent toggling which would happen if only one temperature was used.
To configure the thermostat mode please check the example.

The library provides the following functions for configuring the Thermostat mode

- **setOneWireMode(VDD, DQ)** 
This function puts a DS1821 in Thermostat mode back into oneWire mode.
DQ must be the same as oneWire(pin). 
VDD is the voltage controlling pin of the sensor. 
- **setThermostatMode()** sets the flag in the config register to start in 
Thermostat mode next restart.

The polarity functions are also available in temperature sensor mode,
however they have no effect in that mode.

- **setPolarity(activstate)** When in thermostat mode the DQ pin controls e.g.
a fan or a motor. Activstate defines which value is ON and OFF.
- **getPolarity()** reads back polarity from the device.

The Low / High values set in sensor mode gives the DS1821 the thresholds 
to toggle the DQ line in the thermostat mode.

## Future

- Get new sensors to test test test...
- merge clrLowFlag() into getLowFlag() ? high idem?
- 

## Operation

See examples.

