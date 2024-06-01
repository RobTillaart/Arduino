
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

From Wikipedia:

_The polymerase chain reaction (PCR) is a method widely used to make millions to 
billions of copies of a specific DNA sample rapidly, allowing scientists to amplify 
a very small sample of DNA (or a part of it) sufficiently to enable detailed study. 
PCR was invented in 1983 by American biochemist Kary Mullis at Cetus Corporation._

This library implements a PCR class that helps to control time and temperatures of the 
main PCR cycles.

In short a PCR cycle is a process of controlled heating and cooling to let DNA "reproduce"
to get large quantities. Roughly the amount doubles in every cycle (of step 2,3,4).

This process exists of repeated cycles of the three main steps. (times and temp from Wikipedia)

| step | cycle |  name           |  temperature range    |  time range  |  notes  |
|:----:|:-----:|:----------------|:----------------------|:------------:|:--------|
|  1   |   N   | Initialization  |  94–98°C = 201–208°F  |  00–10 min.  |  to heat up system => hot-start PCR.
|  2   |  Yes  | Denaturation    |  94–98°C = 201–208°F  |  20–30 sec.  |
|  3   |  Yes  | Annealing       |  50–65°C = 122–149°F  |  20–40 sec.  |
|  4   |  Yes  | Extension       |  75–80°C = 167–176°F  |  ? minutes   |
|  5   |   N   | Elongation      |  70–74°C = 158–165°F  |  05–15 min.  |
|  6   |   N   | Final Hold      |   4–15°C =  39–59°F   | indefinitely |  final storage

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


**Note:** this library is meant for educational purposes and is not meant 
to replace professional equipment.


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


#### Breaking change 0.3.0

Since 0.3.0 the timing of the 6 steps is done in seconds instead of milliseconds.
As the steps take up to 15 minutes of more, defining the time in seconds is a more
natural order of magnitude than milliseconds.
Note however that the internal math still is done in milliseconds so one can define
a step as taking 15.75 seconds = 15750 milliseconds.

Pre 0.3.0 versions are now obsolete.

#### Related

- https://en.wikipedia.org/wiki/Polymerase_chain_reaction
- https://github.com/RobTillaart/PCR
- https://github.com/RobTillaart/Temperature  scale conversions.
- https://forum.arduino.cc/t/problem-with-arduino-pcr-amplifies-of-dna/314808 
- https://www.scientificamerican.com/article/the-unusual-origin-of-the-polymeras/ (paid site)


## Interface

```cpp
#include "PCR.h"
```

#### Constructor

- **PCR(uint8_t heatPin, uint8_t coolPin)** constructor defines the hardware pins to which 
the heater and cooler are connected.
- **void reset(uint16_t iterations)** full stop of the process, also stops heating and cooling,
resets the state to IDLE and defines the number of iterations for the next run.
The parameter iterations must be >= 0 so it changed to unsigned int in 0.3.0.
- **uint8_t process(float temperature)** The worker core. This function runs the main process 
and iterates over the DENATURE, ANNEALING and EXTENSION phase. Returns the current state.  
The user **MUST** provide the actual temperature of the sample so process can heat and cool
the sample on a need to basis.  
The user **MUST** call this function as often as possible in a tight loop. 
- **int iterationsLeft()** returns the number of iterations left.
- **float timeLeft()** estimator of the time left to reach the HOLD state.
Since 0.3.0 returns its value in seconds.
This function assumes that the duration per phase does not change runtime,
however it will adapt its estimate.
Returns the value in milliseconds. 


#### About phases

Temperatures are in **°Celsius**, timing is in **seconds** (since 0.3.0 version).  

The timing is the time that the process will be in this state, so it includes
the time to heat / cool to reach the temperature defined.
The timing parameter is a float so you can use e.g. 10.5 seconds, or even use
scientific notation like 1.2e2.
In theory the maximum time is 4294967 seconds which is 49.7 days,
In practice the phases are much shorter.
- 1 hour = 3600 seconds, 1 day = 86400 seconds

Note that the parameters of the phases can change while the process is running,
e.g. one can increase the duration of the extension phase per cycle to give 
that part of the PCR process more time (adjust to concentration?).


#### 1 Initial phase

This step used in **hot-start PCR** (Wikipedia) to bring the system to starting temperature.

- **void setInitial(float Celsius, float seconds)** Sets temperature and duration.
- **float getInitialTemp()** returns set value.
- **float getInitialTime()** returns set value.

#### 2 Denature phase

This step breaks the double DNA helix into two single strands.

- **void setDenature(float Celsius, float seconds)** Sets temperature and duration.
- **float getDenatureTemp()** returns set value.
- **float getDenatureTime()** returns set value.

#### 3 Annealing phase

This step let **primers** (Wikipedia) connect to the single strands.
The primers create a starting point for the replication.
The temperature and duration depends on many factors, so very specific for the reaction.

- **void setAnnealing(float Celsius, float seconds)** Sets temperature and duration.
- **float getAnnealingTemp()** returns set value.
- **float getAnnealingTime()** returns set value.

#### 4 Extension phase

This step extends the primers with **dNTP's** nucleotides (Wikipedia) to complete
the duplication process.

- **void setExtension(float Celsius, float seconds)** Sets temperature and duration.
- **float getExtensionTemp()** returns set value.
- **float getExtensionTime()** returns set value.

#### 5 Elongation phase

This step is used to finalize the remaining DNA strands that are not fully extended
in step 4 Extension phase.

- **void setElongation(float Celsius, float seconds)** Sets temperature and duration.
- **float getElongationTemp()** returns set value.
- **float getElongationTime()** returns set value.

#### 6 Hold phase

The Hold phase goes on forever and is meant to store the result on a cool temperature
for final storage.

- **void setHold(float Celsius)** Sets temperature for final phase.
- **float getHoldTemp()** returns set value.

#### Heater, cooler control

The temperature control functions are made public so the user can use these directly 
from their own code.

In 0.2.x version the heater / cooler are switched on/off for a short period.
This prevent excessive heating or cooling due to not switching of the heater / cooler in time.
This pulsed heating / cooling makes the process safer as after the call it is switched off.
Drawback is that the pulsed behaviour makes the process a bit slower to heat up / cool down.
Therefore the length of the period can be adjusted between 0 and 1000 milliseconds to increase
the efficiency of the process. Be aware that the heat() and cool() will block longer.

- **void heat()** Switches off cooler first, and then switches the heater for (default) 
10 milliseconds. Before return the heater is switched off again.
- **void cool()** switch on the cooler for (default) 10 milliseconds. Switches off heater first.
- **void off()** switch off both heater and cooler.
- **void setHeatPulseLength(uint16_t ms = 10)** adjust the timing for heat() and cool().
  - The maximum value is 1000 milliseconds == 1 second (this limit is to prevent overheating).
  - The minimum value is 0 milliseconds but it would slow down the heating / cooling.
  - Assumption: optimal time == time to increase 0.1°C. This depends on the specific heat.
  - Warning: the heat() and cool() will block for the set period.
- **uint16_t getHeatPulseLength()** returns set value.


#### Debug

- **void debug()** is a function used to output some state to Serial.
Users can patch this function when needed, or make it empty.


## Future

#### Must

- improve documentation
  - description of the phases.
- build hardware setup to test

#### Should

- investigate the blocking version
  - void keepTempTime(temp, time, getTemperature());

#### Could

- PCR scripting language, simple example?
- add examples
- add stir pin, to control the stirring of the PCR device.
- add signalling pin to indicate ready by a buzzer.

#### Wont

- add callback function when ready (user can check state)
- Fahrenheit interface  (C = (F-32) x 5/9.0;  F = C x 9/5.0 + 32;
- Kelvin or other temperature scale.
- optimize code
  - have an array of times and temperatures to go through.
- add continuous heating (unsafe mode) versus the current pulsed heating(safe mode).

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


