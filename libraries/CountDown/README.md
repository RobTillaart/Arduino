

[![Arduino CI](https://github.com/RobTillaart/CountDown/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CountDown/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CountDown.svg?maxAge=3600)](https://github.com/RobTillaart/CountDown/releases)


# CountDown

Arduino Library to implement a CountDown clock (in SW polling, no HW timer).


## Description

The countdown library is a clock that counts down from a given time to zero.
It does not call a function or so as the user is responsible to check the time remaining.
Typically one checks the remaining time in every loop.

UNder the hood the function uses **micros()** or **millis()** which results in a maximum time
of 4294 seconds in micros (1h10m) or something like 49+ days when using millis.

For longer periods one could cascade countDown, so when one is finished the next starts.


## Interface

The main functions of the CountDown clock are:

- **bool start(ticks)**
- **bool start(days, hours, minutes, seconds)**
- **bool start(days, hours, minutes)**
- **void stop()**
- **void cont()**  *(continue is a C-Keyword)*
- **uint32_t remaining()**
- **bool isRunning()**

These functions work straightforward.


## Operation

The function **start(days, hours, minutes, seconds)** has changed its
parameters type to minimize them, given that the total time may not exceed 2^32 milliseconds.
This allows the user to call **start()** with e.g. four hundred minutes **start(0, 0, 400, 0)** 
or a million seconds **start(0, 0, 0, 1000000)** as parameter.
The resolution is implicitly set to **SECONDS**.

Since 0.2.4 the function **start()** will check if the parameters cause an overflow
in the underlying math. If there is no overflow call to **start()** returns true. 
If there is an overflow it returns false

Total amount of time to countdown for **MICROS** may not exceed 2\^32 micros ~ 1hr 10 minutes.
Total amount of time to countdown for **MILLIS**, **SECONDS** and **MINUTES**
may not exceed 2\^32 millis  ~49 days


The function **start(days, hours, minutes)** is new since 0.2.2.
It also uses **millis()** under the hood. The resolution is implicitly set to **MINUTES**.


| Call to start()                       | resolution       |  max time | comments |
|:--------------------------------------|:-----------------|:---------:|:---------|
| start(days, hours, minutes, seconds)  | SECONDS = millis |  49+ days |
| start(days, hours, minutes)           | MINUTES = millis |  49+ days |
| start(ticks)                          | MILLIS  = millis |  49+ days | default |
| start(ticks)                          | MICROS  = micros |  ~70 min  | use setResolution(MICROS)  |
| start(ticks)                          | SECONDS = millis |  49+ days | use setResolution(SECONDS) |
| start(ticks)                          | MINUTES = millis |  49+ days | use setResolution(MINUTES) |


The Countdown clock uses by default **millis()** to do the time keeping,
although this can be changed runtime by **setResolution(res)**. The parameter 
**res** can be:
- **MICROS**
- **MILLIS**   // default
- **SECONDS**  // based upon millis()
- **MINUTES**  // based upon millis()

Although possible one should not change the resolution of the CountDown 
clock while it is running as you mix up different timescales.

One can call **start(...)** at any time to reset the running clock to
a new value. This allows to implement a sort of watchdog clock in which e.g. 
the user must press a button at least once per minute to show he is still
awake.


