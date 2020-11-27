# Stopwatch_RT

Arduino Library implementing a stopwatch including seconds, milliseconds microseconds

# Description

The stopwatch class allows one to create a stopwatch with 4 levels of resolution
* MICROS - microseconds 
* MILLIS - milliseconds (default)
* SECONDS - seconds
* MINUTES - minutes (added 0.2.0)

Note that the resolution chosen implies the finest granularity of units measured.
E.g. if chosen minutes then one cannot measure half (30 sec) or other part of a minute.

The resolution is typically set in the constructor, however since 0.2.0 one can call
**setResolution()** to change the 'tick unit' of the clock runtime. 
This way one can reuse the stopwatch object without creating a new one and thereby
save some memory.

**Warning:** Changing the resolution will reset the stopwatch 
as start time and stop time will become meaningless.
The stopwatch will reset even when the resolution is the current resolution.

The other methods of the stopwatch are trivial
* start()
* stop()
* elapsed()  - - will return the time in chosen units since last **start()**
* reset()
* isRunning()
* state()
* resolution()

This library is based upon millis() and micros() and therefore has the same 
restrictions and limitations as these functions with respect to overflow 
and precision.
This means minutes and seconds will overflow also after about 49 days.

# Operation

See examples
