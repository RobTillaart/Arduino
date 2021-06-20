
[![Arduino CI](https://github.com/RobTillaart/ML8511/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ML8511/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ML8511.svg?maxAge=3600)](https://github.com/RobTillaart/ML8511/releases)

# ML8511

Arduino library for ML8511 UV sensor


## Warning

**Always take precautions as UV radiation can give sunburn, eye damage and possible other problems**. 
Do not expose yourself to the sun as UV source too long and when using artificial UV light 
(TL LED etc) use appropriate shielding.


## Description

ML8511 - UV sensor - library for Arduino UNO. 


## Breakout

```
//      +-------+--+
//  VIN |o      +-+| mounting hole
//  3V3 |o      +-+|
//  GND |o         |
//  OUT |o         |
//   EN |o       S |  Sensor
//      +----------+
```


## Operational

As the sensor / breakout is 3V3 one need to connect to Arduino 3V3.
The library converts the analogRead to voltages, and it uses a
reference of 5.0 Volt == 1023 steps as default.

If one wants to use other ratio e.g. 3.3 volts == 4095 steps, one
can set those with setVoltagePerStep()

```
    ML8511 light(A0, 7);
    light.setVoltagePerStep(3.3, 4095);
```

It is possible to always enable the sensor by connecting the EN to 3V3.
The value of the enablePin in the constructor should then be omitted 
or set to a negative value;

When connecting to an Arduino UNO one can use the 3V3 of the Arduino to power
the sensor. However it is not possible to connect the enable pin directly to the 
sensor. Use a voltage divider (10K + 20K) to convert the 5 Volts to ~3.3 Volts.


## Interface

- **ML8511(uint8_t analogPin, uint8_t enablePin = 0xFF)** Constructor, if enable is connected to 3V3 constantly one does not need to set the enablePin parameter.
- **float getUV(uint8_t energyMode = HIGH)** returns mW per cm2, energyMode = HIGH or LOW
- **void setVoltsPerStep(float voltage, uint32_t steps)** to calibrate the (Internal) ADC used. Voltage must be > 0 otherwise it is not set and the default of 5 volts 1023 steps is used.
- **float getVoltsPerStep()** idem
- **void enable()** manually enable
- **void disable()** manually disable
- **bool isEnabled()** get status.


#### experimental

WARNING: USE WITH CARE

- **float estimateDUVindex(float mWcm2)** input in mW per cm2, returns a value between 0 and ~15(?)
- **void setDUVfactor(float f)** set the conversion factor
- **float getDUVfactor()** returns the set conversion factor (default 1.61)

See below how to determine the DUV factor for your sensor.


## Sensor sensitivity

Indoors there is very little UV light so use a known UV source like 
a black-light or go outside in the sun.

The formula to convert the ADC reading to mW cm^2 is based upon the graph 
shown in the datasheet. As I have no reference source to calibrate the library
the accuracy is limited. (If you have please contact me)

The sensor has its peak sensitivity ( >80% ) from λ = 300-380 nm 
with an absolute peak at λ = 365 nm.


## Experimental DUVindex

Note: this library is **NOT** calibrated so **USE AT OWN RISK**

The DUV index can be used for warning for sunburn etc.

#### DUV index table

Based upon https://en.wikipedia.org/wiki/Ultraviolet_index,

| DUV INDEX | Description |
|:---------:|:------------|
|   0 - 2   |  LOW        |
|   3 - 5   |  MODERATE   |
|   6 - 7   |  HIGH       |
|   8 - 10  |  VERY HIGH  |
|   11+     |  EXTREME    |


#### 0.1.5 and before

The formula for the experimental **estimateDUVindex(power)** is based on
the following facts / assumptions:
- (fact) The sensor cannot differentiate between wavelengths, 
so integration with different weights is not possible.
- (assumption) All the UV is radiated at λ = 300 nm. 
This is the most lethal the sensor can sense > 80%.
- (choice) All the UV is accounted for 100% for the whole value. 
(Erythemal action spectrum) 
As we cannot differentiate this is the safest choice.


#### 0.1.6 

The formula is simplified to a single factor that the user needs to determine.
Below is described how to do the calibration. 


#### Calibrate estimateDUVindex()

To calibrate the **estimateDUVindex()** function one needs to determine
the DUVfactor. To do this you need an external reference e.g. a local or nearby
weather station. You need to make multiple measurements during the
(preferably unclouded) day and calculate the factor.

```
          DUV from weather station
factor = --------------------------
                  getUV();
```

you do this e.g. once per hour, so you get multiple values.
You can then average them to have a single factor.

Hardcode this found value in the library (in the constructor) or better
use the **setDUVfactor(factor)** call in **setup()** to calibrate your sensor.


## More about UV

https://en.wikipedia.org/wiki/Ultraviolet_index


## Notes

- 3V3 Sensor so do not connect to 5V directly.
- do not forget to connect the EN to either an enablePIN or to 3V3 (constantly enabled).
- library does not work with an external ADC. (todo?)

