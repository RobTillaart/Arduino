# PCF8574

Arduino library for PCF8574 - I2C IO expander

# Description

This library gives easy control over the 8 pins of a PCF8574 and PCF8574A chip.
These chips are identical in behavior although there are two distinct address ranges.

| TYPE     | ADDRESS-RANGE |
|:----|:----:|
|PCF8574   | 0x20 to 0x27 |
|PCF8574A  | 0x38 to 0x3F |

THe library allows to read and write both single pins or 8 pins at once.
Furthermore some additional functions are implemented that are a little more
playfull but still are useful.


### Interface

**PCF8574(deviceAddress)** Constructor with device address as parameter.

**begin(val = 0xFF)** set the initial value for the pins and masks.

**begin(sda, scl, val = 0xFF)** idem, for the ESP32 where one can choose the I2C pins

What needs to be added in the future is a parameter to choose another Wire interface
as some processors have multiple hardware Wire interfaces.

----

**read8()** reads all 8 pins at once. This one does the actual reading.

**read(pin)** reads a single pin; pin = 0..7

**value()** returns the last read inputs again, as this information is buffered 
in the class this is faster than reread the pins.

----

**write8(value)** writes all 8 pins at once. This one does the actual reading.

**write(pin, value)** writes a single pin; pin = 0..7; value is HIGH(1) or LOW (0)

**valueOut()** returns the last written data. 

----

TODO

**setButtonMask(mask)** 

**readButton8()**

**readButton8(mask = 0xFF)**

**readButton(pin)**

----

**toggle(pin)** toggles a single pin

**toggleMask(mask)** toggles a selection of pins, if you want to invert all pins use 0xFF.

**shiftRight(n = 1)** shifts output channels n pins (default 1) pins right (e.g. leds ). 
Fills the higher lines with zero's.

**shiftLeft(n = 1)**  shifts output channels n pins (default 1) pins left (e.g. leds ).
Fills the lower lines with zero's.


**rotateRight(n = 1)** rotates output channels to right, moving lowest line to highest line.

**rotateLeft(n = 1)** rotates output channels to left, moving highest line to lowest line.

**reverse()** revers the "bit pattern" of the lines, high to low and vice versa.

# Operation

See examples
