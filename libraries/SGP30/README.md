
[![Arduino CI](https://github.com/RobTillaart/SGP30/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SGP30/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SGP30/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SGP30/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SGP30/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SGP30.svg)](https://github.com/RobTillaart/SGP30/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SGP30/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SGP30.svg?maxAge=3600)](https://github.com/RobTillaart/SGP30/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SGP30.svg)](https://registry.platformio.org/libraries/robtillaart/SGP30)


# SGP30

Arduino library for SGP30 environment sensor

Warning: experimental, library is not functional complete yet.


## Description

The SGP30 from Sensirion is an environment sensor that measures H2 and Ethanol in the air. 
From these numbers an intern algorithm in the sensor derives an CO2 equivalent and a TVOC 
measurement. The library has an experimental conversion for H2 and Ethanol.

The CO2 units are ppm, the TVOC units are ppb. Units for H2 and Ethanol are ppm. 
Note that for larger concentrations the resolution of the measurements drops, see datasheet.

The library supports 2 types of interfaces, a synchronous and an asynchronous interface. 
The sync interface is blocking for up to 40 milliseconds which was enough to trigger the 
implementation of an async interface. 

Note: the sync interface is implemented with the async interface.

Note: versions prior to 0.2.0 are obsolete due to a bug in **setBaseline()**.


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Sample frequency

The CO2 and TVOC values can be read up to once per second (1 Hz). 
Ethanol and H2, the raw data can be sampled up to 40 Hz.

The first 15 seconds the sensor needs to stabilize. Thereafter one gets real data.


#### I2C performance

The SGP30 works with I2C bus at 100 KHz and 400 KHz. In a short test it worked well up to 500 KHz. 
A faster I2C clock does not give the sync interface much (relative) gain, 
however for the async interface the relative gain is much more.

(indicative test run with UNO - IDE 1.8.13, CO2 and TVOC only, times in micros)

|  I2C speed | measure() | request() | read() |
|:----------:|:---------:|:---------:|:------:|
|  100 kHz   |   12360   |    336    |   732  |
|  200 kHz   |   12212   |    196    |   408  |
|  300 kHz   |   12168   |    144    |   300  |
|  400 kHz   |   12140   |    132    |   264  |
|  500 kHz   |   12128   |    124    |   236  |

Note the blocking of measure() takes 11 to 12 milliseconds extra.


#### Multiple sensors.

The SGP30 sensor has a fixed I2C address 0x58 so only one sensor per I2C bus can be used. 
If one needs more, one should use an I2C multiplexer or an MCU with multiple I2C buses 
or switch the VCC as a sort of ChipSelect signal.

- https://github.com/RobTillaart/TCA9548  (I2C 8 channel multiplexer)

See **TCA9548_demo_SGP30.ino** example.


#### Related

CO2 sensors and more. 

- https://www.adafruit.com/product/3709 - the SGP30 sensor.
- https://emariete.com/en/sensor-co2-mh-z19b/
- https://emariete.com/en/sensor-co2-low-consumption-mh-z1311a-winsen/
- https://revspace.nl/MHZ19
- https://www.co2.earth/ - current outdoor CO2 level can be used for calibrating.
- https://keelingcurve.ucsd.edu/ - historical outdoor CO2 level.
- https://github.com/RobTillaart/ACD10
- https://github.com/RobTillaart/MTP40C
- https://github.com/RobTillaart/MTP40F
- https://github.com/RobTillaart/Cozir


## Interface

```cpp
#include "SGP30.h"
```

#### Constructor

- **SGP30(TwoWire \*wire = &Wire)** Constructor with optional the Wire interface as parameter.
- **bool begin()** initializes the library.
Returns true if the (fixed) device address 0x58 is visible on the I2C bus.
- **bool isConnected()** checks if the device address 0x58 is visible on the I2C bus.
- **void GenericReset()** WARNING resets all I2C devices on the bus that support this call!


#### Meta

- **bool getID()** reads the sensor ID into 12 bytes. (needs rework).
- **uint16_t getFeatureSet()** returns 0x0022, indicates that commands used in this library are supported.
- **bool measureTest()** verify the chip is working.


#### Synchronous measurements

- **uint32_t lastMeasurement()** timestamp in milliseconds of the last sync measurement made. 
This convenience function is useful to prevent reading the sensor too often.
- **bool measure(bool all = false)** if all == false, only the TVOC and CO2 are updated (slow due to blocking), 
if all == true, also the H2 and the Ethanol values are updated (even slower). 
Note the measurement is slow as there is an active blocking until the sensor is done. 
If the last measurement is less than a second ago, no measurement is made and the function returns false.


#### Asynchronous measurements

With the async interface, the user should control that reads are at least one second apart. 
The user should also take care not to mix up different requests. See examples.

- **void request()** sends a request to the sensor to read CO2 and TVOC. 
- **bool read()** returns true if the last request is more than 12 milliseconds ago the 
CO2 and TVOC are read and updated. Otherwise false is returned.
- **void requestRaw()** sends a request to the sensor to read H2 and Ethanol.
- **bool readRaw()** returns true if the last request is more than 25 milliseconds ago the 
H2 and Ethanol are read and updated. Otherwise false is returned.


#### Get the data

The library caches the last read values, and these are the functions to access them. 

- **uint16_t getTVOC()** gets the TVOC concentration (ppb)
- **uint16_t getCO2()** gets the CO2 **equivalent** concentration (ppm)
- **uint16_t getH2_raw()** gets the raw H2. Units unknown.
- **uint16_t getEthanol_raw()** gets the raw Ethanol. Units unknown.


#### Calibration

Check the datasheet for operating range, figure 7.

- **float setRelHumidity(float T, float RH)** sets the compensation for temperature (5-55°C) and **relative** humidity (10-95%). 
These values can be obtained e.g. from an SHT30, DHT22 or similar sensor. 
The function returns the absolute humidity. 
- **void setAbsHumidity(float absoluteHumidity)** sets the compensation for **absolute** humidity. 
Concentration is in gram per cubic meter (g/m3)


#### Baseline functions

The baseline functions give the sensor a reference value. 
After running in a known condition e.g. outside in open air, one can get the baseline values as a sort of calibration. 
Please read the datasheet carefully before using these functions.

Note: if the sensor has no reads done, these values tend to go to zero. 
This is because the baselines are based upon recent reads.

- **bool getBaseline(uint16_t \*CO2, uint16_t \*TVOC)** retrieves the baseline values from the sensor.
- **void setBaseline(uint16_t CO2, uint16_t TVOC)** sets the baseline values.

Note the outdoor calibration CO2 level differs per day and one should check 
a local airport or weather station for a good reference.

The University of San Diego keeps track of CO2 for a long time now.
See - https://keelingcurve.ucsd.edu/ 


For faster accurate results for the TVOC under bad air conditions, read **Inceptive Baseline for TVOC measurements**
(not tested)
- **bool getTVOCBaseline(uint16_t \*TVOC)** retrieves the TVOC start value from the sensor.
- **void setTVOCBaseline(uint16_t TVOC)** sets the TVOC start value.


#### Miscellaneous

- **int lastError()** returns last error. (needs rework)


#### Experimental H2 Ethanol

use at own risk.

Since 0.1.2 the library has experimental support for H2 and Ethanol concentration in ppm. 

One should use these functions more as a relative indication than as an absolute measurement as it is definitely not calibrated.
Runs with different temperature and humidity (different days) give very different values including overflow and infinity.

- **float getH2()** gets the H2 concentration. Units ppm.
- **float getEthanol()** gets the Ethanol concentration. Units ppm.

The used references are based upon   
(1) averaging raw data in outside air at 22°C @ 1 meter and 
(2) the assumption that this is 0.4 resp 0.5 ppm. 
(Note only 1 significant digit) as mentioned in datasheet P2.

- **void  setSrefH2(uint16_t s = 13119)**  13119 is my measurement.
- **uint16_t getSrefH2()** returns value set.
- **void setSrefEthanol(uint16_t s = 18472)** 18472 is my measurement.
- **uint16_t getSrefEthanol()** returns value set.


## Future

#### Must

- improve documentation

#### Should

- test 
  - different boards
  - different gasses / atmosphere if possible.

#### Could

- move code from .h to .cpp
- add/extend error handling
- better name for **measureTest()**

The CRC checking + error handling (since 0.1.4) adds around 330 bytes PROGMEM on an UNO.
There might be a need for a minimal class that only reads CO2 and TVOC, no baselines etc.
for the smallest platforms e.g. tiny.

#### Wont (unless)

- make defines for the magic numbers (commands)
  - only used once.
- improve/merge the private **command()** function (made no difference)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


