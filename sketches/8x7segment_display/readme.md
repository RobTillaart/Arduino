
**ROBOTDYN 8 x 7segment display**
https://www.tinytronics.nl/shop/nl/verlichting/led-segment-display/robotdyn-segmenten-display-module-8-karakters-decimalen-groen-74hc595

This example code implements some basic display routines.
- showLong()
- showFloat()
- showHex()
- clear()

The display must be updated every millisecond or so to look smooth.
Although this takes quite some mcu load it is doable.
Due to the constant refresh the brightness is not optimal.

**0.5.x release notes**
- put the tables in PROGMEM (for UNO)
- showEqualizer()   - 8 channel equalizer x 4 levels
- showVUvertical()  - 1 channel equalizer x 17 levels
- ShowRaw(byte arr[8]) allows to display any pattern [HIGH]
  this latter enables all ideas below


**TODO**
If time permits a wrapper class will be written.
Some parts of the code can definitely be optimized.

***PRIO IDEAS***

***EQUALIZER***
- 2 channel equalizer x 17 levels   vertical    use __
- 3 channel equalizer x  8 levels   vertical    use |||
- 1 channel equalizer x 25 levels   vertical    use _ and |

***ANIMATIONS***
- knight Rider pulse ---0-----
- moving pulse: up down; left right
- duty cycle display: 8 steps of 12.5%

***OTHER***
- 8 free font chars (upload).
