
[![Arduino CI](https://github.com/RobTillaart/PCR/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCR/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCR/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCR/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCR/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCR.svg)](https://github.com/RobTillaart/PCR/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCR/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCR.svg?maxAge=3600)](https://github.com/RobTillaart/PCR/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCR.svg)](https://registry.platformio.org/libraries/robtillaart/PCR)


# PCR

Arduino library for PCR process control.


## Description


**Experimental**

From wikipedia:

_The polymerase chain reaction (PCR) is a method widely used to make millions to 
billions of copies of a specific DNA sample rapidly, allowing scientists to amplify 
a very small sample of DNA (or a part of it) sufficiently to enable detailed study. 
PCR was invented in 1983 by American biochemist Kary Mullis at Cetus Corporation._

This library implements a PCR class that helps to control time and temperatures of the 
main PCR cycles.

In short a PCR cycle is a process of controlled heating and cooling to let DNA "reproduce"
to get large quantities. Roughly the amount doubles in every cycle (of step 2,3,4).

This process exists of repeated cycles of the three main steps. (times and temp from wikipedia)

| step |  name           |  temperature range    |  time range  |
|:----:|:----------------|:----------------------|:------------:|
|  1   | Initialization  |  94–98°C = 201–208°F  |  00–10 min.  |
|  2   | Denaturation    |  94–98°C = 201–208°F  |  20–30 sec.  |
|  3   | Annealing       |  50–65°C = 122–149°F  |  20–40 sec.  |
|  4   | Extension       |  70–80°C = 158–176°F  |  ?           |
|  5   | Elongation      |  70–80°C = 158–176°F  |  05–15 min.  |
|  6   | Final Hold      |   4–15°C =  39–59°F   | indefinitely |

The PCR function **process()** takes care of the repeating of step 2,3 and 4.


Typical core code looks like:

```cpp
  //  configure all phases
  pcr.setInitial(98, 10000);  //  temp, ms
  pcr.setDenature(94.5, 5000);
  pcr.setAnnealing(54.2, 2000);
  pcr.setExtension(75.0, 3000);
  pcr.setElongation(75.0, 3000);
  pcr.setHold(8.0);
  
  pcr.reset(15);  //  iterations.
  //  execute the process.
  while (pcr.iterationsLeft() > 0)
  {
    float temp = getTemperature();
    pcr.process(temp);
  }
```


**Note:** this library is meant for educational purposes and is not meant to replace professional equipment.


#### Hardware notes

The hardware setup needs a device that can be cooled or heated depending on the phase of the cycle.
Furthermore the hardware setup needs to provide an actual temperature to guide the process.
This latter can be an DS18B20 especially the waterproof version.

```
         Processor                            PCR DEVICE
     +---------------+                    +---------------+
     |               |                    |               |
     |               |                    |               |
     |      heatPin o|------------------->|o HEATER       |
     |      coolPin o|------------------->|o COOLER       |
     |               |                    |               |
     |    getTemp() O|<-------------------|o temperature  |
     |               |                    |  sensor       |
     |               |                    |               |
     |               |                    |               |
     |               |                    |               |
     +---------------+                    +---------------+
```


#### Other applications

The PCR class can be used to manage other temperature control processes.
Some examples:
- control an oven with a thermocouple, (e.g. glass melting)
- control the temperature of a tropic aquarium to simulate day and night.
- control an ice making machine.


#### Related

- https://en.wikipedia.org/wiki/Polymerase_chain_reaction
- https://github.com/RobTillaart/PCR
- https://forum.arduino.cc/t/problem-with-arduino-pcr-amplifies-of-dna/314808 
- https://www.scientificamerican.com/article/the-unusual-origin-of-the-polymeras/ (paid site)


## Interface

```cpp
#include "PCR.h"
```

#### Constructor

- **PCR(uint8_t heatPin, uint8_t coolPin)** constructor defines the haredware pins to which 
the heater and cooler are connected.
- **void reset(int iterations)** full stop of the process, also stops heating and cooling,
resets the state to IDLE and defines the number of iterations for the next run.
- **uint8_t process(float temperature)** The worker core. This function runs the main process 
and iterates over the DENATURE, ANNEALING and EXTENSION phase. Returns the current state.  
The user **MUST** provide the actual temperature of the sample so process can heat and cool
the sample on a need to basis.  
The user **MUST** call this function as often as possible in a tight loop.
Returns the current state.  
- **int iterationsLeft()** returns the number of iterations left.
- **uint32_t timeLeft()** estimator of the time left to reach the HOLD state.
This function assumes that the duration per phase does not change runtime,
however it will adapt its estimate.
Returns the value in milliseconds. 


#### Initial phase

Temperatures are in °Celsius, timing is in milliseconds.  
Note that these parameters can change while the process is running. 

- **void setInitial(float Celsius, uint32_t ms)** Sets temperature and duration.
- **float getInitialTemp()** returns set value.
- **uint32_t getInitialTime()** returns set value.

#### Denature phase

- **void setDenature(float Celsius, uint32_t ms)** Sets temperature and duration.
- **float getDenatureTemp()** returns set value.
- **uint32_t getDenatureTime()** returns set value.

#### Annealing phase

- **void setAnnealing(float Celsius, uint32_t ms)** Sets temperature and duration.
- **float getAnnealingTemp()** returns set value.
- **uint32_t getAnnealingTime()** returns set value.

#### Extension phase

- **void setExtension(float Celsius, uint32_t ms)** Sets temperature and duration.
- **float getExtensionTemp()** returns set value.
- **float getExtensionTime()** returns set value.

#### Elongation phase

- **void setElongation(float Celsius, uint32_t ms)** Sets temperature and duration.
- **float getElongationTemp()** returns set value.
- **float getElongationTime()** returns set value.

#### Hold phase

The Hold phase goes on forever ans is meant to store the result on a cool temperature
for final storage.

- **void setHold(float Celsius)** Sets temperature for final phase.
- **float getHoldTemp()** returns set value.

#### Heater, cooler control

These are public functions so the user can control these also from their own code.

- **void heat()** switch on the heater for 10 milliseconds.
- **void cool()** switch on the cooler for 10 milliseconds.
- **void off()** switch off all.

#### Debug

- **void debug()** is a function used to output some state to Serial.
Users can patch this function when needed, or make it empty.


## Future

#### Must

- improve documentation
  - description of the phases.
- build setup to test


#### Should

- investigate the blocking version
  - void keepTempTime(temp, time, getTemperature());
- make the 10 milliseconds control pulses configurable (e.g. 10..100 ms)
- investigate continuous heating (unsafe mode)versus the current pulsed heating(safe mode).

#### Could

- PCR scripting language?
- add examples
- optimize code
  - have an array of times and temperatures to go through.
- stir pin, to control the stirring of the PCR device.
- add unit tests


#### Wont
- add callback function when ready (user can check state)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


