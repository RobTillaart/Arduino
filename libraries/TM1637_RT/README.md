[![Arduino CI](https://github.com/robtillaart/TM1637_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TM1637_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TM1637_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TM1637_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TM1637_RT/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TM1637_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TM1637_RT.svg?maxAge=3600)](https://github.com/RobTillaart/TM1637_RT/releases)


# TM1637

Library for TM1637 driven displays and keyscans.


## Description

The TM1637 drives 7 segment displays and can also scan a 16 key keyboard.

Library is tested with Arduino UNO and a 6 digits display.

ESP32 is supported since 0.2.0 see https://github.com/RobTillaart/TM1637_RT/pull/5


## Interface

- **TM1637()** constructor
- **void begin(uint8_t clockPin, uint8_t dataPin, uint8_t digits = 6)** set up the connection of the pins to the display.
As the display is only tested with a 6 digit display, this is used as the default of the digits parameter.
- **void displayRaw(uint8_t \* data, uint8_t pointPos)** low level write function.
- **void displayInt(long value)** idem
- **void displayFloat(float value)** idem
- **void displayHex(uint32_t value)** idem
- **void displayClear()** writes spaces to all positions, effectively clearing the display.
- **void setBrightness(uint8_t b)** brightness = 0 .. 7 default = 3.
- **uint8_t getBrightness()** returns value set.
- **uint8_t keyscan(void)** scans the keyboard once and return result. The keyscan() function cannot detect multiple keys.


**displayRaw()** can display multiple decimal points, by setting the high bit (0x80) in each character for which you wish to have a decimal lit.  Or you can use the pointPos argument to light just one decimal at that position.

**displayRaw()** can display some of the alphabet as follows:
   - space (blank) is 0x10
   - '-' (minus) is 0x11
   - a-f are coded as 0x0a-0x0f
   - g-z are coded as 0x12-0x25.  Characters that cannot be represented in 7 segments render as blank.

So "hello " is coded as 0x13, 0x0e, 0x17, 0x17, 0x1a, 0x10

See routine **ascii_to_7segment()** in the example TM1637_keyscan_cooked.ino.  It presents a more convenient interface for displaying text messages on the display.

Routine **button_poll()** in the same example shows one way of polling and de-bouncing button presses.


#### Obsolete (0.4.0)

- **void init(uint8_t clockPin, uint8_t dataPin, uint8_t digits = 6)** replaced by begin().



### Display support

The library is tested with a 6 (=2x3) digit - decimal point - display and a 4 (=1x4) digit - clock - display. 
At low level these displays differ in the order the digits have to be clocked in.
To adjust the order for a not supported display, the following function can be used with care:

- **void setDigitOrder(uint8_t a, uint8_t b,... uint8_t h)** sets the order in which up to 8 digits should be clocked in.

If you have a (7 segment) display that is not supported by the library, 
please open an issue on Github so it can be build in.


### Tuning function

To tune the timing of writing bytes.

- **void    setBitDelay(uint8_t bitDelay = 10)**
- **uint8_t getBitDelay()**


### Tuning minimum pulse length

The class has a conditional code part in writeSync to guarantee the length of pulses
when the library is used with an ESP32. The function called there **nanoDelay(n)**
needs manual adjustment depending upon processor frequency and time needed for a digitalWrite.
Feel free to file an issue to get your processor supported.

### Keyboard Scanner usage and notes


Calling keyscan() returns a uint8_t, whose value is 0xff if no keys are being pressed at the time.  The TM1637 can only see one key press at a time, and there is no "rollover".  If a key is pressed, then the values are as follows:

<CENTER>
<TABLE>
<TR>
<TD colspan = 10 align="center">
   keyscan results are reversed left for right from the data sheet.
</TD>
</TR>
<TR>
<TH>pin</TH><TD>&nbsp</TD><TD>2</TD><TD>3</TD><TD>4</TD><TD>5</TD><TD>6</TD><TD>7</TD><TD>8</TD><TD>9</TD>
</TR>
<TR>
</TD><TD>&nbsp;</TD><TH>name</TH><TD>sg1</TD><TD>sg2</TD><TD>sg3</TD><TD>sg4</TD><TD>sg5</TD><TD>sg6</TD><TD>sg7</TD><TD>sg8</TD>
</TR>
<TR>
</TD><TD>19</TD><TD>k1</TD><TD>0xf7</TD><TD>0xf6</TD><TD>0xf5</TD><TD>0xf4</TD><TD>0xf3</TD><TD>0xf2</TD><TD>0xf1</TD><TD>0xf0</TD>
</TR>
<TR>
</TD><TD>20</TD><TD>k2</TD><TD>0xef</TD><TD>0xee</TD><TD>0xed</TD><TD>0xec</TD><TD>0xeb</TD><TD>0xea</TD><TD>0xe9</TD><TD>0xe8</TD>
</TR>
</TABLE>
</CENTER>
<P>
To modify a "generic" TM1637 board for use with a keyboard, you must add connections to either or both of pins 19 and 20 (these are the "row" selects) and then to as many of pins 2 through 9 (the "columns") as needed.  It is easiest to connect to the "column pins" (2-9) by picking them up where they connect to the LED displays (see second photo).  Generic keyboards that are a 4x4 matrix won't work; the TM1637 can only scan a 2x8 matrix.  Of course, fewer keys are acceptable; I use a 1x4 keyboard in my projects.
</P>
<P>
Further, the TM1637 chip needs a fairly hefty pull-up on the DIO pin for the keyscan() routine to work.  There is no pull-up in the TM1637 itself, and the clone boards don't seem to have one either, despite the data sheet calling for 10K ohms pull-ups on DIO and CLOCK.  10K is too weak anyway.  The slow rise-time of the DIO signal means that the "true/high" value isn't reached fast enough and reliably enough for the processor to read it correctly.  The new pull-up reduces the rise time of the signal, so that true/high values are achieved in a few microseconds.  I find that a 1K (1000) ohm resistor from DIO to 3.3 v works well.  This is perfect with a 3.3 volt processor like the ESP8266 or ESP32, and a 5V Atmega 328 ("Arduino UNO") family processor is happy with that as well.
</P>
<P>
The TM1637 boards want to be run off of 5 volts, regardless of what the processor voltage is.  Their logic levels are compatible with 3.3 volt processors, and they need 5 volts to make sure the LEDs light up.
</P>
The unmodified generic TM1637 board (front and back).</br>
<IMG src="images/unmodified.jpg">
</br>
The modified generic TM1637 board with connector for 1x4 keyboard. The blue wire is bringing out pin 19 (k1).  Four segments/columns are picked up from the LEDs.</br>
<IMG src="images/modified.jpg">
</br>
The 4 button keyboard plugged into the TM1637 board.</br>
<IMG src="images/disp_plus_kbd.jpg"></br>
</br>
Scope photo showing slow rise time of DIO pin (upper trace) on the unmodified TM1637.  The lower trace is the CLK.  The 8 fast CLK pulses on the left represent the 0x42 command to read keyboard being sent to the TM1637.</br>
<IMG src="images/slow_rise.jpg"></br>
</br>
Scope photo showing faster rise time of DIO pin (upper trace) with 1000 ohm pull-up on DIO.  In both scope photos, the F5 key is pressed; the bits are least significant bit (LSB) first, so read as 10101111 left to right.</br>
<IMG src="images/fast_rise.jpg"></br>

The scope photos were taken using the TM1637_keyscan_raw example, with the scope trigger hooked to the TRIGGER pin, and the two channel probes hooked to DIO and CLK.  Vertical sensitivity is 2v/division, horizontal timebase is 20usec/division.


## Keyscan

Implemented in version 0.3.0  Please read the datasheet to understand the limitations.

```
// NOTE: 
// on the TM1637 boards tested by @wfdudley, keyscan() works well 
// if you add a 910 ohm or 1 Kohm pull-up resistor from DIO to 3.3v
// This reduces the rise time of the DIO signal when reading the key info.
// If one only uses the pull-up inside the microcontroller, 
// the rise time is too long for the data to be read reliably.
```


## Operation

See examples


## Future

### 0.4.0

- remove obsolete **init()** from code

### other

- testing platforms.
- investigate if code can be optimized
  - performance measurement
- **keyScan()** camelCase ?


