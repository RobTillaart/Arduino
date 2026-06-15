
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

From Wikipedia:

_The polymerase chain reaction (PCR) is a method widely used to make millions to 
billions of copies of a specific DNA sample rapidly, allowing scientists to amplify 
a very small sample of DNA (or a part of it) sufficiently to enable detailed study. 
PCR was invented in 1983 by American biochemist **Kary Mullis** at Cetus Corporation._

This library implements a PCR class that helps to control time and temperatures of the 
main PCR cycles.

In short a PCR cycle is a process of controlled heating and cooling to let DNA "reproduce"
to get large quantities. Roughly the amount doubles in every cycle (of step 2, 3, 4).

Furthermore the library can roughly calculate how much time is left until all the PCR
cycles are done.

Feedback as always is welcome.


### Warning

This library should be able to do a decent PCR job (heating cooling cycles) as intended. 
However it is not developed as a replacement for professional laboratory equipment.
Furthermore its working also depends on the quality and accuracy of the used heating 
and cooling equipment, PCR liquids etc.

In short, use with care. 


### Steps

The PCR process exists of repeated cycles of the three main steps. 
The time range and temperature mentioned are based upon Wikipedia.

| step | cycle |  name           |  temperature range    |  time range  |  notes  |
|:----:|:-----:|:----------------|:----------------------|:------------:|:--------|
|  1   |   N   | Initialization  |  94–98°C = 201–208°F  |  00–10 min.  |  to heat up system => hot-start PCR.
|  2   |  Yes  | Denaturation    |  94–98°C = 201–208°F  |  20–30 sec.  |
|  3   |  Yes  | Annealing       |  50–65°C = 122–149°F  |  20–40 sec.  |
|  4   |  Yes  | Extension       |  75–80°C = 167–176°F  |  ? minutes   |
|  5   |   N   | Elongation      |  70–74°C = 158–165°F  |  05–15 min.  |
|  6   |   N   | Final Hold      |   4–15°C =  39–59°F   | indefinitely |  final storage

The PCR function **process()** takes care of the repeating of step 2, 3 and 4.
One needs to call process() as often as possible.


Typical core code looks like:

```cpp
  //  configure all phases
  pcr.setInitial(98, 1.0);        //  temperature, seconds
  pcr.setDenature(94.5, 5.5);
  pcr.setAnnealing(54.2, 2.0);
  pcr.setExtension(75.0, 3.0);
  pcr.setElongation(75.0, 3.5);
  pcr.setHold(8.0);               //  temperature only
  
  pcr.reset(15);  //  iterations.

  //  execute the process.
  while (pcr.getPCRState() != PCR_STATE_HOLD)
  {
    float temp = getTemperature();
    pcr.process(temp);
  }
```


**Note:** this library is meant for educational purposes and is not meant 
to replace professional equipment.


### Hardware notes

The hardware setup needs a device that can be cooled or heated depending on the phase of the cycle.
Furthermore the hardware setup needs to provide an actual temperature to guide the process.
This latter can be an DS18B20 especially the waterproof version.

```
         Processor                            PCR DEVICE
     +---------------+                    +---------------+
     |               |                    |               |
     |               |                    |               |
     |    signalPin o|----(X)---GND       |               |
     |               |                    |  sensor       |
     |      heatPin o|------------------->|o HEATER       |
     |      coolPin o|------------------->|o COOLER       |
     |               |                    |               |
     |    getTemp() O|<-------------------|o temperature  |
     |               |                    |               |
     |               |                    |               |
     |               |                    |               |
     +---------------+                    +---------------+
```

(X) can be a buzzer of a LED.


### Other applications

The PCR class can be used to manage other temperature control processes.
Some examples:
- control an oven with a thermocouple, (e.g. glass melting)
- control the temperature of an aquarium to simulate day and night.
- making perfect home made ice.
- making chocolate 
- boiling the ideal egg :)


### Breaking change 0.5.0

In issue #5 it is stated that reset(0) does not work correctly.
It did not test for zero at the start and it decremented (underflow)
before testing. 

Version 0.5.0 improved the timing accuracy, removing a drift 
of about 0.1%. 

This fix makes pre 0.5.0 versions obsolete.


### Breaking change 0.3.0

Since 0.3.0 the timing of the 6 steps is done in seconds instead of milliseconds.
As the steps take up to 15 minutes of more, defining the time in seconds is a more
natural unit of magnitude than milliseconds.
Note however that the internal math still is done in milliseconds so one can define
a step as taking 15.75 seconds = 15750 milliseconds.

This fix makes pre 0.3.0 versions obsolete.


### Related

- https://en.wikipedia.org/wiki/Polymerase_chain_reaction backgrounder
- https://github.com/RobTillaart/PCR this library
- https://github.com/RobTillaart/Temperature temperature scale conversions.
- https://github.com/RobTillaart/HeartBeat to add "process is alive" indication
- https://github.com/RobTillaart/printHelpers scientific notation a.o.
- https://forum.arduino.cc/t/problem-with-arduino-pcr-amplifies-of-dna/314808 
- https://www.scientificamerican.com/article/the-unusual-origin-of-the-polymeras/ (paid site)


## Interface

```cpp
#include "PCR.h"
```

### Constructor

- **PCR(uint8_t heatPin, uint8_t coolPin, uint8_t signalPin = 255)** constructor defines the 
hardware pins to which the heater and cooler are connected.
Also defines a signal pin to connect a buzzer / LED to indicate phase transitions.
You might think of the transitions as phase heart beats.


### PCR Process

- **void reset(uint16_t iterations)** full stop of the process, also stops heating and cooling,
resets the state to IDLE and defines the number of iterations for the next run.
The parameter iterations must be >= 0 so it changed to unsigned int in 0.3.0.
The process (re)starts by calling **process()**.
Note when iterations is set to zero (0), state 2,3,4 are skipped.
- **uint8_t process(float temperature)** The worker core. This function runs the main process 
and iterates over the **DENATURE**, **ANNEALING** and **EXTENSION** phases. 
The function returns the current state.
The user **MUST** provide the actual temperature of the sample so process can heat and cool
the sample on a need to basis.  
The user **MUST** call this function as often as possible in a tight loop.

|  nr  |  PCR state             |  Notes  |
|:----:|:-----------------------|:--------|
|   0  |  PCR_STATE_IDLE        |  set in reset()
|   1  |  PCR_STATE_INITIAL     |  starts with first call to process()
|   2  |  PCR_STATE_DENATURE    |
|   3  |  PCR_STATE_ANNEALING   |
|   4  |  PCR_STATE_EXTENSION   |
|   5  |  PCR_STATE_ELONGATION  |  starts when no iterations are left
|   6  |  PCR_STATE_HOLD        |  when done.


### State

- **uint16_t iterationsLeft()** returns the number of iterations left.
- **uint16_t iterationsTotal()** total iterations set in **reset()**.
- **uint8_t getPCRState()** returns current state.
Note one cannot set the state, except by **reset()**.


### Timing

- **float timeLeft()** estimator of the time left to reach the HOLD state.
Since 0.3.0 returns its value in seconds. 
The function assumes it is at the start of an iteration.
Furthermore it assumes that the duration per phase does not change runtime,
however it will adapt its estimate after changes are made with a new call.
- **float timeIteration()** duration in seconds of one iteration, DENATURE, ANNEALING plus EXTENSION time.
- **float timeTotal()** duration of the total PCR job with current settings.
The value is calculated in reset() call.

One can use the **timeLeft()** and **timeTotal()** to calculate the 
percentage done.


### About phases (state)

Temperatures are defined in degrees **Celsius**, timing is in **seconds**.  

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

- **getPCRState()** returns current state. Allows users to add actions on
certain states (phases). Note that **process()** also returns current state.

See also table in Steps section.

### 1 Initial phase

This step used in **hot-start PCR** (See Wikipedia) to bring the system to starting temperature.

- **void setInitial(float Celsius, float seconds)** Sets temperature and duration.
- **float getInitialTemp()** returns set value.
- **float getInitialTime()** returns set value.

### 2 Denature phase

This step breaks the double DNA helix into two single strands.
Typical this is the highest temperature of the cycle.

- **void setDenature(float Celsius, float seconds)** Sets temperature and duration.
- **float getDenatureTemp()** returns set value.
- **float getDenatureTime()** returns set value.

### 3 Annealing phase

This step let **primers** (See Wikipedia) connect to the single strands.
The primers create a starting point for the replication.
The temperature and duration depends on many factors, so very specific for the reaction.

- **void setAnnealing(float Celsius, float seconds)** Sets temperature and duration.
- **float getAnnealingTemp()** returns set value.
- **float getAnnealingTime()** returns set value.

### 4 Extension phase

This step extends the primers with **dNTP's** nucleotides (Wikipedia) to complete
the duplication process.

- **void setExtension(float Celsius, float seconds)** Sets temperature and duration.
- **float getExtensionTemp()** returns set value.
- **float getExtensionTime()** returns set value.

### 5 Elongation phase

This step is used to finalize the remaining DNA strands that are not fully extended
in step 4 Extension phase.

- **void setElongation(float Celsius, float seconds)** Sets temperature and duration.
- **float getElongationTemp()** returns set value.
- **float getElongationTime()** returns set value.

### 6 Hold phase

The Hold phase goes on forever and is meant to store the result on a cool temperature
for final storage.

- **void setHold(float Celsius)** Sets temperature for final phase.
- **float getHoldTemp()** returns set value.

### Heater, cooler control

The temperature control functions are made public so the user can use these directly 
from their own code.

In 0.2.x version the heater / cooler are switched on/off for a short period.
This prevent excessive heating or cooling due to not switching of the heater / cooler in time.
This pulsed heating / cooling makes the process safer as after the call it is switched off.
Drawback is that the pulsed behaviour makes the process a bit slower to heat up / cool down.
Therefore the length of the period can be adjusted between 0 and 1000 milliseconds to increase
the efficiency of the process. Be aware that the heat() and cool() will block longer.

- **void heat()** Switches off cooler first, and then switches the heater on for (default) 
10 milliseconds. Before return the heater is switched off again.
- **void cool()** switch on the cooler for (default) 10 milliseconds. Switches off heater first.
- **void off()** switch off both heater and cooler.
- **void setHeatPulseLength(uint16_t ms = 10)** adjust the timing for heat() and cool().
  - The maximum value is 1000 milliseconds == 1 second (this limit is to prevent overheating).
  - The minimum value is 0 milliseconds but it would slow down the heating / cooling.
  - Assumption: optimal time == time to increase 0.1°C. This depends on the specific heat.
  - Warning: the heat() and cool() will block for the set period.
- **uint16_t getHeatPulseLength()** returns set value.


### Signalling new phase

If the signal pin is defined in the constructor, that pin will get HIGH
for 500 milliseconds (by default) to indicate a new phase has entered.
One can connect a (built-in) LED or e.g. a buzzer or a stirring device.

The duration can be set by the following function, 0 ==> OFF.

- **void setSignalLength(uint16_t ms)** set pulse duration in milliseconds.
A value of 0 means OFF. Typical values are steps of 100 ms, (default 500 ms).
If the value set is larger than phase period signalling will not work as intended..
- **uint16_t getSignalLength()** returns set value in milliseconds.

If one want a signal only once per iteration or for certain state one could use
**getPCRState()**, **timeLeft()** and **iterationsLeft()** to build your
own signalling.


### Debug

- **void debug()** is a function used to output some state to Serial.
Users can patch this function when needed, or make it empty.


## Future

#### Must

- improve documentation
  - description of the phases.

#### Should

- build hardware setup to test (long runs)
- investigate PCR scripting language?


#### Could

- overload **setAnnealing(temp, hours = 0, minutes = 0, seconds = 0)**
  - convenience
  - idem for other functions.
- investigate adding **setTempAccuracy(0.5)**
  - to reduce switching heat / cool too often.
- investigate split reset() => major break... 
  - setIterations(uint16_t iterations); + getIterations();
  - stop();
  - start();
- investigate runtime adjustment of iterations.
  - get/setIterations() would be sufficient.
- investigate the blocking version
  - void keepTempTime(temp, time, getTemperature());
- improve heartbeat (see it is still running)
- add **getCoolPulseLength()**?
- add examples
- add stir pin, to control the stirring of the PCR device.
  - different speed / direction per phase? 
  - speed depending on temperature?
  - decoupled from phases?
- Elaborate debug() ?
  - void **debugStream(Stream str = &Serial)** define the stream used.
  - void **debugOn()** enable.
  - void **debugOff()** disable debug statements
  - defaults? backwards compatibility?


#### Wont

- add callback function when ready (user can check state)
- Fahrenheit interface  (C = (F-32) x 5/9.0;  F = C x 9/5.0 + 32;
- Kelvin or other temperature scale.
- optimize code
  - have an array of times and temperatures to go through.
- add continuous heating (unsafe mode) versus the current pulsed heating(safe mode).
- add ready pin? == HOLD State reached? ==> use getPCRState() 


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


