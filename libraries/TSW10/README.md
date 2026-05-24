
[![Arduino CI](https://github.com/RobTillaart/TSW10/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TSW10/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TSW10/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TSW10/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TSW10/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TSW10.svg)](https://github.com/RobTillaart/TSW10/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TSW10/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TSW10.svg?maxAge=3600)](https://github.com/RobTillaart/TSW10/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TSW10.svg)](https://registry.platformio.org/libraries/robtillaart/TSW10)


# TSW10

Arduino library for the TSW10 analog turbidity sensor.


## Description

**Experimental**

This library is to make measurements with the TSW-10 turbidity sensor, e.g. in the 
SEN0189 of DFRobotics. It is not to replace a professional turbidity sensor, however
it should be possible to get reasonable indications of turbidity.

Turbidity is an important and widely used indication of the clarity and quality of the water.
The less turbid or the cleaner the water the less it might be polluted.
Note that not all turbidity is pollution, in a fast flowing river there are always 
fine grains of sand in the stream.

Turbidity is expressed in units of NTU (Nephelometric Turbidity Units) or FTU (Formazin Turbidity Units).
This library only supports NTU as the datasheet of the TSW-10 provides an **indicating graph**. 
This graph uses a 5 Volt so for 3.3V processors adaptions are needed, e.g. a voltage converter.

The library is meant to be used with an internal ADC, however using an external ADC 
is possible if one converts the ADC measurements to volts and use **volts2NTU(volts)**.

The library does not support run-time calibration (yet).
For now the volts to NTU conversion table in TSW10.cpp file can be adjusted manually 
in the function **volts2NTU(volts)**.
Furthermore one can adjust for power differences by calling **begin(volts, steps)** 
again to get some extra accuracy.

**WORK IN PROGRESS**

The library is not tested with hardware yet.

Feedback as always is welcome.


### Sensor specifications

Some specs.

|               |  range         |  notes  |
|:--------------|:--------------:|:-------:|
|  temperature  |  -30°C ~ 80°C  |
|  voltage      |   5V           |  3.3V devices need
|  current      |   Max. 30 mA   |  do not power with an IO pin.


### Other turbidity units

The scientific literature mentions also FNU, FAU, FBU, FNRU units, which are all different
methods of determining turbidity. 
These include using visible or IR light and using a different detector angle.
More information see - https://documents.thermofisher.com/TFS-Assets/LPD/Application-Notes/Turbidity-Units-A-Cloudy-Issue.pdf


### Warning

_Do not apply this product to safety protection devices or emergency stop equipment, 
and any other applications that may cause personal injury due to the product's failure._


### Calibration

Also important is the calibration of the sensor. 
Currently not supported other than a graph as defined in the datasheet.

The library does not support run-time calibration (yet). 
For now the lookup table in TSW10.cpp file needs to be adjusted manually in the 
function **volts2NTU(volts)**.


### Related

Datasheet Sensor
- https://wiki.seeedstudio.com/Grove-Turbidity-Sensor-Meter-for-Arduino-V1.0/
- https://amphenol-sensors.com/en/thermometrics/turbidity/934-tsw-10
- https://documents.thermofisher.com/TFS-Assets/LPD/Application-Notes/Turbidity-Units-A-Cloudy-Issue.pdf

Backgrounder
- https://en.wikipedia.org/wiki/Turbidity
- https://www.sciencedirect.com/topics/medicine-and-dentistry/nephelometry

Libraries
- https://github.com/RobTillaart/TSW10 - this library
- https://github.com/RobTillaart/TSL235R - light to frequency convertor
- https://github.com/RobTillaart/TSL260R - IR to voltage convertor
- https://github.com/RobTillaart/printHelpers - scientific notation et al.
- https://github.com/RobTillaart/map2colour - mapping ranges upon colours.

The TSL sensors can be used for turbidity measurement too. See documents folder.


### Tested

Not yet (order pending :).


## Multiplexing

One could use an HC4051 as multiplexer so it uses only one analog port.
- https://github.com/RobTillaart/HC4051  (other multiplexer libs are mentioned there).


## Interface

```cpp
#include "TSW10.h"
```

### Constructor

- **TSW10(uint8_t analogPin)** defines the (internal) analog pin to be used
for the measurements.
- **bool begin(float voltage, uint16_t maxSteps)** 


### Read

- **float getVoltage(uint8_t times = 1)** read one or more times the sensor and
return the average voltage.
The parameter times is constrained between 1..32.
- **float getNTU(uint8_t times = 1)** read one or more times the sensor and
return the average NTU.
The parameter times is constrained between 1..32.
- **float volts2NTU(float volts)** conversion function for volts to NTU, based
upon the graph in the datasheet.
Can be used with an external ADC.
- **uint32_t lastRead()** timestamp in millis of the last time a read function 
was called.


## Future

#### Must

- improve documentation
- get hardware to test (DFRobotics SEN0189).

#### Should

- add runtime calibration?
  - is this possible?
  - use fixed NTU levels and change voltage?

#### Could

- track minimum and maximum turbidity + reset.
- add gradient detection
- uint32_t uptime() { return millis(); };
  - add bool maintenanceNeeded() ?  (uptime > threshold, reboot proof?)
- add callback function if a certain threshold is met.

#### Wont

- add getFTU() / getFNU() wrappers? 
  - no data how to do this correctly.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


