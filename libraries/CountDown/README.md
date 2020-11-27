# CountDown

Arduino Library to implement a CountDown clock (in SW polling, no HW timer).

## Description

The main functions of the CountDown clock are:

* **void start(ticks);**
* **void start(days, hours, minutes, seconds);**
* **void start(days, hours, minutes);**
* **void stop();**
* **void cont();**  *(continue is a C-Keyword)*
* **uint32_t remaining();**
* **bool isRunning();**

These functions work straightforward.

The function **start(days, hours, minutes, seconds)** has changed its
parameters type to minimize them, given that the total time may not exceed 2^32 milliseconds.
This allows the user to call **start()** with e.g. four hundred minutes **start(0, 0, 400, 0)** 
or a million seconds **start(0, 0, 0, 1000000)** as parameter.
The resolution is implicitly set to *SECONDS*.

Note: the function **start()** does not check if the parameters cause an overflow
in the underlying math. That is responsibility of the user.

The function **start(days, hours, minutes)** is new since 0.2.2.
It also uses **millis()** under the hood. The resolution is implicitly set to *MINUTES*.

Total amount of time to countdown for **MICROS** may not exceed 2\^32 micros ~ 1hr 10 minutes.
Total amount of time to countdown for **MILLIS**, **SECONDS** and **MINUTES**
may not exceed 2\^32 millis  ~49 days

## Operation

The Countdown clock uses by default **millis()** to do the time keeping,
although this can be changed runtime by **setResolution(res)**. The parameter 
**res** can be:
- *MICROS*
- *MILLIS*
- *SECONDS*  // based upon millis()
- *MINUTES*  // based upon millis()

Although possible one should not change the resolution of the CountDown 
clock while it is running as you mix up different timescales.

One can call **start(...)** at any time to reset the running clock to
a new value. This allows to implement a sort of watchdog clock in which e.g. 
the user must press a button at least once per minute to show he is still
awake.


