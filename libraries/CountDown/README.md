
[![Arduino CI](https://github.com/RobTillaart/CountDown/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CountDown/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CountDown/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CountDown/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CountDown/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/CountDown.svg)](https://github.com/RobTillaart/CountDown/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CountDown/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CountDown.svg?maxAge=3600)](https://github.com/RobTillaart/CountDown/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/CountDown.svg)](https://registry.platformio.org/libraries/robtillaart/CountDown)


# CountDown

Arduino Library to implement a CountDown clock (in software polling, no hardware timer).


## Description

The countdown library is a clock that counts down from a given time to zero.
It does not call a function or so as the user is responsible to check the time remaining.
Typically one checks the remaining time at least once in every **loop()**.

Under the hood the function uses **micros()** or **millis()** which results in a maximum time
of 4294 seconds in micros (1h 10m) or about 49+ days when using milliseconds.

For longer periods one could cascade countDown objects, so when one is finished the next one starts.

Note the countdown object is as accurate as the underlying **millis()** or **micros()**.
Interrupts etc. might cause deviations.


#### Related

- https://github.com/RobTillaart/StopWatch_RT


## Interface

```cpp
#include "CountDown.h"
```


The main functions of the CountDown clock are:

- **CountDown(const enum Resolution res = MILLIS)** constructor, with default resolution of milliseconds.
- **void setResolution(const enum Resolution res = MILLIS)** set the resolution,
default to MILLIS.
- **enum Resolution resolution()** return the current resolution (integer).
- **char getUnits()** return the current resolution as printable char (u,m,s,M)
- **bool start(uint32_t ticks)** (re)start in current resolution.
Typical used for MILLIS and MICROS which must be set manually.
- **bool start(uint8_t days, uint16_t hours, uint32_t minutes, uint32_t seconds)** Implicit set resolution to SECONDS.
Returns false if total exceeds 2^32 milliseconds ~49 days.
Note that **remaining()** will report in SECONDS.
- **bool start(uint8_t days, uint16_t hours, uint32_t minutes)** Implicit set resolution to MINUTES.
Returns false if total exceeds 2^32 milliseconds ~49 days.
Note that **remaining()** will report in MINUTES.
- **void stop()** stop the count down.
- **void cont()** resumes / continue the count down.
*(note continue is a C-Keyword)*
- **void restart()** restart the CountDown with the same resolution and ticks as before.
resets the \_ticks and starts again.
- **uint32_t remaining()** returns the remaining ticks in current resolution.
- **bool isRunning()** idem.
- **bool isStopped()** idem.

These functions work straightforward.


## Operation

The function **start(days, hours, minutes, seconds)** allows all combinations
as long as the total time may not exceed 2^32 milliseconds. 
The function will return false if it exceeds this (rounded) maximum.
Example calls are:
- four hundred minutes **start(0, 0, 400, 0)** 
- a million seconds **start(0, 0, 0, 1000000)** 
- an unusual mix **start(0, 0, 400, 1000)** as parameter.
Note: the resolution is implicitly set to **CountDown::SECONDS**.

Since 0.2.4 all **start()** functions will check if the parameters cause an overflow
in the underlying math. 
- If there is no overflow, **start()** returns true. 
- If there is an overflow, **start()** returns false.

Total amount of time to countdown for **CountDown::MICROS** may not exceed 2\^32 micros 
which equals about 1 hour and 10 minutes.
Total amount of time to countdown for **CountDown::MILLIS**, **CountDown::SECONDS** 
and **CountDown::MINUTES** may not exceed 2\^32 milliseconds, about 49 days.

The function **start(days, hours, minutes)** is new since 0.2.2.
It also uses **millis()** under the hood. 
The resolution is implicitly set to **CountDown::MINUTES**.


|  Call to start()                       |  resolution        |  max time  |  comments  |
|:---------------------------------------|:-------------------|:----------:|:-----------|
|  start(days, hours, minutes, seconds)  |  SECONDS = millis  |  49+ days  |            |
|  start(days, hours, minutes)           |  MINUTES = millis  |  49+ days  |            |
|  start(ticks)                          |  MILLIS  = millis  |  49+ days  |  default   |
|  start(ticks)                          |  MICROS  = micros  |  ~70 min   |  setResolution(CountDown::MICROS)  |
|  start(ticks)                          |  SECONDS = millis  |  49+ days  |  setResolution(CountDown::SECONDS) |
|  start(ticks)                          |  MINUTES = millis  |  49+ days  |  setResolution(CountDown::MINUTES) |


The Countdown clock uses by default **millis()** to do the time keeping,
although this can be changed runtime by **setResolution(res)**. 

The parameter **res** can be:

|  unit                |  uses      |  getUnits()  |  Notes  |
|:---------------------|:-----------|:------------:|:--------|
|  CountDown::MICROS   |  micros()  |     u        |
|  CountDown::MILLIS   |  millis()  |     m        |  default
|  CountDown::SECONDS  |  millis()  |     s        |
|  CountDown::MINUTES  |  millis()  |     M        |

Although possible one should not change the resolution of the CountDown 
clock while it is running as you mix up different timescales.
The user should handle this by selecting the smallest resolution needed.

Alternative one can get the remaining units, stop the countdown, and start
with another resolution and converted time. 
This will probably lead to rounding errors i the total countdown time.
See example **countdown_adaptive_display.ino**

Finally the user has to check **remaining()** as frequent as needed to meet 
the accuracy. E.g checking once a minute while doing milliseconds makes only sense
if the number of milliseconds is still very large. Think of an adaptive strategy.


#### Watchdog 

One can call **start(...)** at any time to reset the running clock to a new value. 
This allows to implement a sort of watchdog clock in which e.g. 
the user must press a button at least once per minute to show he is still awake.

Since version 0.3.1 the library supports **restart()** to start the countdown with
the last used parameters of **start()**. The user does not need to remember the 
number of ticks or hours + minutes + seconds any more. Much easier tom implement 
a repeating (timed) function or a watchdog. See examples.


## Future

#### Must

- documentation

#### Should


#### Could

- does **restart()** need to return some information? what?
- add examples
  - visualisations - hexadecimal - alphabetical (radix 26)
  - depends on sensor
- add resolution::HOURS + **start(days, hours)**
  - extend adaptive display example
  - or default 00 minutes?


#### Wont (unless)

- if counting MINUTES and reaching 1 MINUTES and automatic
  change to SECONDS could be NICE
  - easy implementable by user, by starting in seconds 
    and handle the display oneself.
- incorporate a real time clock
  - or EEPROM to be reboot proof? cannot be guaranteed.
- Countdown based upon external pulses.
  - pulse counter class
- uint64_t version ==> **CountDown64** class? 
  - would be useful for micros() in theory 
    but drift / interrupts would make it fail in practice.
- countdown with a big number e.g. billions/ second ==> national deficit counter.
  - not time triggered (is just a big variable)
- printable interface (stopwatch_rt)
- add call-back function when **0** is reached
  - cannot be guaranteed as interface polls.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

