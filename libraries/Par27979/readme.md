# PAR27979

Arduino library for the Parallax 27979 serial display

## Description

The library is essentially a wrapper around a Stream, typically Serial, 
Serial2 (3,4..) or newSoftSerial or equivalent.
This stream is given as parameter in the constructor.

The library implements the **Print** interface to print integers
floats and strings and all printable types.

The library does not keep any state information, it only implements a few
methods to make working with it easier. 
These methods are quite trivial.

* **on()** switch display on
* **off()** switch display off
* **clearHome()** clear the display
* **backlightOn()** enable the backlight
* **backLightOff()** disable the backlight

**Movement**
* **cursorLeft()** move cursor 
* **cursorRight()** move cursor
* **lineFeed()** idem
* **formFeed()** idem
* **gotoXY(x, y)**

**Sound support**
* **octave(octave)**  octave =  3 4 5 6 7
* **duration(duration)** duration = 1 2 4 8 16 32 64
* **play(note)** note = 0 1 2 3 4 5 6 7 8 9 10 11   0=A 1=A# etc
* **noSound()**

## Support Parallax 27976 & 27977

Although not tested, the functions should work with the
Parallax 27976 and 27977 displays too.

## Operation

See example
