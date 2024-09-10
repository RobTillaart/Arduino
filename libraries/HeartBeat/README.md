
[![Arduino CI](https://github.com/RobTillaart/HeartBeat/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HeartBeat/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HeartBeat/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HeartBeat/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HeartBeat/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HeartBeat.svg)](https://github.com/RobTillaart/HeartBeat/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HeartBeat/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HeartBeat.svg?maxAge=3600)](https://github.com/RobTillaart/HeartBeat/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HeartBeat.svg)](https://registry.platformio.org/libraries/robtillaart/HeartBeat)


# HeartBeat

Arduino library for a HeartBeat with frequency and duty cycle.


## Description

### HeartBeat

The **HeartBeat** library offers a simple heart beat by sending pulses to 
a digital pin. 
Typical usage is to blink a (built in) LED as indicator a program is running (alive).
Besides a LED other devices can be triggered by the heart beat, 
think of a buzzer, relay, stepper motor or a peristaltic pump.

The library uses no hardware timer and is based upon micros().
The user is responsible to call the **beat()** function as often as needed.
Or better even more often.

The library allows to set the frequency runtime.
This allows the HeartBeat to be used as a first level debugging tool. 
Different frequencies can indicate a different state of the program 
or a different level of some sensor.
No heart beat indicates the program is stuck or blocked.


### HeartBeatSL

Since version 0.3.0 a derived class **HeartBeatSL** is added which can  
send specific diagnostic or error patterns.
A pattern exists of 1 to 7 HIGH pulses separated by a fixed length LOW pulse.
The length of the HIGH pulses can be coded with characters S and L (short and long).
An example of an SOS pattern is "SLS".
The unit length of the base pulse is determined by the frequency.

If a pattern is started it cannot be overwritten until it is either ready
or explicitly stopped. 
If one wants to repeat a pattern the application has to repeat the call.


### HeartBeatDiag

Since version 0.3.0 a derived class **HeartBeatDiag** is added which can  
send specific diagnostic or error patterns.
A pattern exists of 1 to 9 HIGH pulses separated by a fixed length LOW pulse.
The (relative) length of the HIGH pulses can be coded with the digits 1 to 9.
An example of an SOS pattern is 111333111.
The unit length of the base pulse is determined by the frequency.
The **HeartBeatDiag** gives some extra control compared to **HeartBeatSL**.

If a pattern is started it cannot be overwritten until it is either ready
or explicitly stopped. 
If one wants to repeat a pattern the application has to repeat the call.

To keep patterns recognizable one can exaggerate the difference in length.
121 is harder to differentiate than 131, a rule of thumb is to use multiples 
of 3 (1, 3, 6 and 9) as length as it allows 4 length levels.

Many applications only need 2 lengths, short and long (BIOS alike), 
but the interface allows more. 
One could start with an extra long HIGH to indicate the start of a pattern 
or to get attention (think buzzzzzzzer).
The variable length can also be used to indicate a level of a measurement.

HeartBeatDiag uses more RAM and PROGMEM than HeartBeatSL.

For more complex patterns, please check my pulsePattern library.


### Related

- https://github.com/RobTillaart/pulsePattern


## Interface

```cpp
#include "HeartBeat.h"
```


### HeartBeat

The interface of the base **HeartBeat** consists of the following functions:

- **HeartBeat()** constructor
- **void begin(uint8_t pin, float frequency = 1.0)** to configure the HeartBeat.
The output pin should be unique.
The default frequency is 1.0.
- **void setFrequency(float frequency = 1.0)** change the frequency of the pulsing.
The default frequency is 1.0.
Setting the frequency will not enable or disable the HeartBeat.  
The frequency must be > 0.001 otherwise it will be constrained to 0.001.
On the upper side values beyond 10 Hz are hard for humans but are allowed.
- **void setDutyCycle(float dutyCycle = 50)** duty cycle in percentage time HIGH.
The default duty cycle = 50 %.
The duty cycle must be between 0.0 and 100.0 %.  
A value of 0 will put the heartbeat effectively off.
- **float getFrequency()** returns set frequency (or constrained value).
- **float getDutyCycle()** returns set duty cycle (or constrained value).
- **void enable()** enables the heart beat.
- **void disable()** disable the heart beat. Will switch the pin to LOW.
- **bool isEnabled()** returns true if the heart beat is enabled (running).
- **void beat()** the worker; this function checks if the HeartBeat is enabled 
and the OUTPUT (LED) must be toggled.  
It must be called as often as possible to keep a steady pace,
preferably at least 4 times the given frequency.  
Not calling **beat()** effectively stops the heartbeat.
- **uint8_t getState()** returns the state of the heartbeat.
Useful for debugging.


### HeartBeatSL

The interface of **HeartBeatSL** adds of the following functions to **HeartBeat**:

- **HeartBeatSL()** constructor.
- **bool code(const char \* str)** executes the pattern ONE time. 
Repeating the pattern means repeating the call. 
The max supported string length is **7** as pattern is stored in a byte.
- **void codeOff()** explicitly stops the pattern. Forced stop.
- **bool codeCompleted()** returns true if pattern is executed completely.


Minimal example
```cpp
#include "HeartBeat.h"

HeartBeatSL HB;

void setup() 
{
  HB.begin(13, 3);  // PIN 13 with frequency 3

  // other setup here
}


void loop()
{
  HB.beat();
  if (some_error) HB.code("LSSLSL");  // ==> L HHHHHH L H L H L HHH 

  // other code here
}


void someOtherfunction()
{
  // ..
  if (other_error) HB.code("LSLSLS");
  // ..
}
```

Note: a code will be executed, even if the HB is disabled.



### HeartBeatDiag

The interface of **HeartBeatDiag** adds of the following functions:

- **HeartBeatDiag()** constructor
- **bool code(uint32_t pattern)** executes the pattern ONE time. 
Repeating the pattern means repeating the call. 
The max supported pattern length is **9**.
- **void codeOff()** explicitly stops the pattern. Forced stop.
- **bool codeCompleted()** returns true if pattern is executed completely.


Minimal example
```cpp
#include "HeartBeat.h"

HeartBeatDiag HB;

void setup() 
{
  HB.begin(13, 3);  // PIN 13 with frequency 3

  // other setup here
}


void loop()
{
  HB.beat();
  if (some_error) HB.code(6113);  // ==> L HHHHHH L H L H L HHH 

  // other code here
}
```

Note: a code will be executed, even if the HB is disabled. 


## Applications

Applications include but are not limited to
- show an alive sign, typical freq of 1 Hz is sufficient.
- show error code by means of different frequencies.
  - 1 Hz = OK
  - 2 Hz = Warning
  - 5 Hz = Error
  - no signal would indicate also an error.
- indicate state of power sensor
  - e.g. freq = round(amps) or duty cycle = round(amps)
  - optional map the range! logarithmic
  - continuous scale vs stair-cased
- indicate the volume by increasing heartBeat
- indicate a changing distant - increasing or decreasing.
- Geiger counter style.

With the HeartBeatDiag and HeartBeatSL one can give different and 
therefore more specific "(error) messages" depending on the state 
of the application or a sensor.


## Operation

See examples


## Future

#### Must

- test HeartBeatDiag version in more detail.

#### Should

- add examples
  - ACS712 current sensor
  - buffer % filled (e.g. stream)

#### Could

- investigate a pattern recognizer (fun)
  - e.g. with an LDR or lux sensor.
- HeartBeatSL
  - extend code length to 16 (bit)?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

