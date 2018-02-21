
This is the 0.2.3 version of the DHTlib.
This version is stable for both ARM and AVR.

You can use most examples from https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTlib/examples

update 2015-10-12:
For multithreading environments for Arduino one could replace
    delay(wakeupDelay);
with
    delayMicroseconds(wakeupDelay * 1000UL);
see also - https://github.com/RobTillaart/Arduino/pull/25 -

