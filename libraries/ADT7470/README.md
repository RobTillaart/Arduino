
[![Arduino CI](https://github.com/RobTillaart/ADT7470/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ADT7470/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ADT7470.svg?maxAge=3600)](https://github.com/RobTillaart/ADT7470/releases)

# ADT7470 Library

Arduino library for I2C ADT7470 Fan Monitoring

## Description

The ADT7470 Fan Monitoring library offers an I2C device that can
monitor and control up to four fans. Further this module can daisy 
chain up to 10 (specific TMP05/06) temperature sensors.

Please read datasheet carefully before working with the module.

**Experimental**  
This library was build in 2015 from datasheet (PDF) on request and
is never tested by me. So it is experimental at best and if you have the 
hardware and are able to try this library I would really appreciate it
as it is a quite unique module.

That said the library is supporting setting the fan speed and measure 
the RPM, so it should be usable e.g. for a climate controlled room or
cabinet.

**Warning**
Do not forget to put a diode over the Fan to prevent damage due to
inductive pulse when switched off.

## ADT7470 Address Select Mode

(from datasheet)

| Pin 11 | (ADDR) State | Address |
|:----:|:----:|:----:|
| High (10 kΩ to VCC)   | 010 1111 (0x5E left-justified or 0x2F right-justified) | 
| Low (10 kΩ to GND)    | 010 1100 (0x58 left-justified or 0x2C right-justified) |
| Floating (no pull-up) | 010 1110 (0x5C left-justified or 0x2E right-justified) |


## Interface

The interface consists of:

- **ADT7470()** constructor
- **begin()** initialize the I2C bus
- **isConnected()** check if the module is connected to the I2C bus
- **getRevision()** version of the firmware
- **getDeviceID()** should return 0x70
- **getCompanyID()** should return 0x41
- **startMonitoring()** 
- **stopMonitoring()**
- **powerDown()** energy save mode
- **powerUp()** active mode
- **getTemperature(idx)** idx = 0..9; if connected it returns the temperature 
of sensor idx. Temperature sensors are daisy chaned.
- **getMaxTemperature()** get max temperature of connected temperature sensors.
- **setTemperatureLimit(idx, low, high)** for ALARM function
- **getTemperatureLowLimit(idx)**
- **getTemperatureHighLimit(idx)**
- **setPWM(idx, val)** set the speed of the fan at idx
- **getPWM(idx)** read back the speed set. 
- **setFanLowFreq(val = 0)** 
- **setFanHighFreq(val = 0)** 
- **setInvertPWM(idx)**
- **getInvertPWM(idx)**
- **setPulsesPerRevolution(idx, val)** val should be 1..4 as a fan gives 1..4 pulses per revolution. 
This valus is needed to calculate a correct tach and RPM.
- **getPulsesPerRevolution(idx)** read back PulsePerRevolution. returns 1..4.
- **setFastTach()** Tach register is updated 4x per second.
- **setSlowTach()** Tach register is updated 1x per second. 
- **getTach(idx)** get the raw pulses.
- **getRPM(idx)** get a Revolutions Per Minute, based upon **getTach()**
- **setTachLimits(idx, low, high)** 
- **getTachLowLimits(idx)** 
- **getTachHighLimits(idx)** 
- **getTemperatureIRQstatus()**
- **setTemperatureIRQMask(idx)**
- **clrTemperatureIRQMask(idx)**
- **getTemperatureIRQMask(idx)**
- **getFanIRQstatus()**
- **setFanIRQMask(idx)**
- **clrFanIRQMask(idx)**
- **getFanIRQMask(idx)**

The descriptions are short and need to be extended. 

## Todo / investigate / not implemented yet

- get the hardware to test 
- change pins from PWM to digital IO
- temperature sensors    (functions are prepared)
- How to connect temp sensors  (daisy chained)  
https://ez.analog.com/temperature_sensors/f/discussions/77540/adt7470-and-tmp05-daisy-chain-temeparure-sensing
- FULLSPEED pin, must it be in the library?  
software version ==> fullspeed(idx)
- automode
- improve documentation, readme.md file.
- ...


## Operation

See examples

