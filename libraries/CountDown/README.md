
[![Arduino CI](https://github.com/RobTillaart/CountDown/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/CountDown/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/CountDown/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/CountDown/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/CountDown/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/CountDown/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/CountDown.svg?maxAge=3600)](https://github.com/RobTillaart/CountDown/releases)


# CountDown

Arduino Library to implement a CountDown clock (in SW polling, no HW timer).


## Description

The countdown library is a clock that counts down from a given time to zero.
It does not call a function or so as the user is responsible to check the time remaining.
Typically one checks the remaining time in every **loop()**.

Under the hood the function uses **micros()** or **millis()** which results in a maximum time
of 4294 seconds in micros (1h 10m) or about 49+ days when using milliseconds.

For longer periods one could cascade countDown objects, so when one is finished the next one starts.

Note the countdown object is as accurate as the underlying **millis()** or **micros()**.
Interrupts etc might cause deviations.


## Interface

The main functions of the CountDown clock are:

- **CountDown(const enum Resolution res = MILLIS)** constructor, with default resolution of milliseconds.
- **bool start(uint32_t ticks)** (re)start in current resolution.
- **bool start(uint8_t days, uint16_t hours, uint32_t minutes, uint32_t seconds)** Implicit set resolution to SECONDS.
- **bool start(uint8_t days, uint16_t hours, uint32_t minutes)** Implicit set resolution to MINUTES.
- **void stop()** stop the count-down.
- **void cont()** resumes / continue the count-down.
*(note continue is a C-Keyword)*
- **uint32_t remaining()** returns the remaining ticks in current resolution.
- **bool isRunning()** idem.

These functions work straightforward.


## Operation

The function **start(days, hours, minutes, seconds)** has changed its
parameters type to minimize them, given that the total time may not exceed 2^32 milliseconds.
This allows the user to call **start()** with e.g. 
- four hundred minutes **start(0, 0, 400, 0)** 
- a million seconds **start(0, 0, 0, 1000000)** 
- a unusual mix **start(0, 0, 400, 1000)** as parameter.
The resolution is implicitly set to **CountDown::SECONDS**.

Since 0.2.4 the function **start()** will check if the parameters cause an overflow
in the underlying math. 
If there is no overflow, a call to **start()** returns true. 
If there is an overflow, a call to **start()** returns false.

Total amount of time to countdown for **CountDown::MICROS** may not exceed 2\^32 micros 
which equals about 1 hour and 10 minutes.
Total amount of time to countdown for **CountDown::MILLIS**, **CountDown::SECONDS** 
and **CountDown::MINUTES** may not exceed 2\^32 milliseconds, about 49 days.

The function **start(days, hours, minutes)** is new since 0.2.2.
It also uses **millis()** under the hood. 
The resolution is implicitly set to **CountDown::MINUTES**.


| Call to start()                      | resolution       | max time | comments |
|:-------------------------------------|:-----------------|:--------:|:---------|
| start(days, hours, minutes, seconds) | SECONDS = millis | 49+ days |          |
| start(days, hours, minutes)          | MINUTES = millis | 49+ days |          |
| start(ticks)                         | MILLIS  = millis | 49+ days | default  |
| start(ticks)                         | MICROS  = micros | ~70 min  | setResolution(CountDown::MICROS)  |
| start(ticks)                         | SECONDS = millis | 49+ days | setResolution(CountDown::SECONDS) |
| start(ticks)                         | MINUTES = millis | 49+ days | setResolution(CountDown::MINUTES) |


The Countdown clock uses by default **millis()** to do the time keeping,
although this can be changed runtime by **setResolution(res)**. 

The parameter **res** can be:

- **CountDown::MICROS**   // based upon micros()
- **CountDown::MILLIS**   // default
- **CountDown::SECONDS**  // based upon millis()
- **CountDown::MINUTES**  // based upon millis()

Although possible one should not change the resolution of the CountDown 
clock while it is running as you mix up different timescales.


#### Watchdog 

One can call **start(...)** at any time to reset the running clock to a new value. 
This allows to implement a sort of watchdog clock in which e.g. 
the user must press a button at least once per minute to show he is still awake.


## Future

#### must
- documentation

#### should


#### could
- incorporate a real time clock
  - or EEPROM to be reboot proof?
- examples
  - visualisations - hexadecimal - alphabetical (radix 26)
  - depends on sensor
- uint64_t version ==> **CountDown64** class?  (only on request)
  - would be useful for micros() in theory but drift / interrupts would make it fail.
  - countdown with a big number e.g. billions/ second ==> national deficit coounter.

#### wont
- Countdown based upon external pulses.
  - pulse counter


