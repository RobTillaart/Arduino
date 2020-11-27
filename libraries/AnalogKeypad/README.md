# AnalogKeypad

Library for (Robotdyn) 4x4 and 4x3 analog keypad

## Description
AnalogKeypad is a simple library to read the keys from a (robotdyn) 4x4 or 4x3 keypad.
No other keypads are tested, but they should work with this library after adjusting
the **MAGIC NUMBERS** in the function **rawRead()**.

## Operation
The simplest usage is to use the **read()** function. 
This will return a 0 (NOKEY) when no key is pressed and
a number 1 to 16 for the keys pressed. Note the return value may
fluctuate randomly when multiple keys are pressed.

The **pressed()** function is a bit more robust.
It returns the key pressed first, so multiple key presses simultaniously 
are less likely to disturbe your program.

The **event()** function checks if an event has happened.
The events are:
* PRESSED   0x80
* RELEASED  0x40
* REPEATED  0x20
* CHANGED   0x10

**key()** can be called to check the last key involved.




