
[![Arduino CI](https://github.com/RobTillaart/PCF8575/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCF8575/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCF8575/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCF8575/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCF8575/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCF8575/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCF8575.svg?maxAge=3600)](https://github.com/RobTillaart/PCF8575/releases)


# PCF8575

Arduino library for PCF8575 - 16 channel I2C IO expander.


## Description

Related to the PCF8574 8 channel IO expander library  https://github.com/RobTillaart/PCF8574.

The library gives easy control over the 16 pins of the PCF8575 chips.

Base address = 0x20 + 0..7 depending on address pins A0..A2.

|  type      | address-range  |  notes                    |
|:-----------|:--------------:|:-------------------------:|
|  PCF8575   |  0x20 to 0x27  |  same range as PCF8574 !  |


So you can connect up to 8 PCF8575 on one I2C bus, giving access 
to 8 x 16 = 128 IO lines. 
To maximize IO lines combine 8 x PCF8575 + 8 x PCF8574A giving
128 + 64 = 192 IO lines. 
Be sure to have a well dimensioned power supply.

The library allows to read and write both single pins or 16 pins at once.
Furthermore some additional functions are implemented that are playful and useful.


#### Interrupts

The PCF8575 has an interrupt output line (INT) to notify an MCU that one of the input lines has changed.
This can be used to prevent active polling of the PCF8575, which can be more efficient.

The library cannot handle the PCF8575 interrupts as it has no code for it. 
The user should catch the interrupt in his own code and can use the library to see which line has changed.

There is one example to show how interrupts can be used:
- PCF8575_interrupt.ino


#### Related

16 bit port expanders

- https://github.com/RobTillaart/MCP23017_RT
- https://github.com/RobTillaart/MCP23S17
- https://github.com/RobTillaart/PCF8575


8 bit port expanders

- https://github.com/RobTillaart/MCP23008
- https://github.com/RobTillaart/MCP23S08
- https://github.com/RobTillaart/PCF8574


## I2C Clock

Testing showed that the PCF8575 still works at 600 KHz and failed at 800 KHz.
These values are outside the specs of the datasheet so they are not recommended.
However when performance is needed you can try to overclock the chip. 

TODO table (see PCF8574)


## Interface

```cpp
#include "PCF8575.h"
```

**PCF8575_INITIAL_VALUE** is a define that can be set compile time or before
the include of "pcf8575.h" to overrule the default value used with the 
**begin()** call.


### Constructor

- **PCF8575(uint8_t deviceAddress = 0x20, TwoWire \*wire = &Wire)** Constructor with the optional 
I2C device address, default 0x20, and the optional Wire interface as parameter.
- **bool begin(uint8_t value = PCF8575_INITIAL_VALUE)** set the initial value for the pins and masks.
- **bool begin(int dataPin, int clockPin, uint8_t value = PCF8575_INITIAL_VALUE)** idem, 
for the ESP32 where one can choose the I2C pins.
- **bool isConnected()** checks if the address is visible on the I2C bus.
- **bool setAddress(const uint8_t deviceAddress)** sets the device address after construction. 
Can be used to switch between PCF8575 modules runtime. Note this corrupts internal buffered values, 
so one might need to call **read16()** and/or **write16()**. Returns true if address can be found on I2C bus.
- **uint8_t getAddress()** returns the device address.


### Read and Write

- **uint16_t read16()** reads all 16 pins at once. This one does the actual reading.
- **uint8_t read(uint8_t pin)** reads a single pin; pin = 0..15.
- **uint16_t value()** returns the last read inputs again, as this information is buffered 
in the class this is faster than reread the pins.
- **void write16(uint16_t value)** writes all 16 pins at once. This one does the actual reading.
- **void write(uint8_t pin, uint8_t value)** writes a single pin; pin = 0..15; value is HIGH(1) or LOW (0).
- **uint16_t valueOut()** returns the last written data.


### Button

The **"button"** functions are to be used when you mix input and output on one IC.
It does not change / affect the pins used for output by masking these.
Typical usage is to call **setButtonMask()** once in setup as pins do not (often) change
during program execution. 

- **void setButtonMask(const uint16_t mask)** sets the (bit) mask which lines are input.
- **uint16_t getButtonMask()** returns the set buttonMask.
- **uint16_t readButton16()** use the mask set by setButtonMask to select specific input pins.
- **uint16_t readButton16(uint16_t mask)** use a specific mask to select specific input pins.
Note this can be a subset of the pins set with **setButtonMask()** if one wants to process not all.
- **uint8_t readButton(uint8_t pin)** read a singe input pin.

Background - https://github.com/RobTillaart/Arduino/issues/38


### Special

- **void toggle(uint8_t pin)** toggles a single pin.
- **void toggleMask(uint16_t mask)** toggles a selection of pins, 
if you want to invert all pins use 0xFFFF (default value).
- **void shiftRight(uint8_t n = 1)** shifts output channels n pins (default 1) pins right (e.g. LEDs ).
Fills the higher lines with zero's.
- **void shiftLeft(uint8_t n = 1)**  shifts output channels n pins (default 1) pins left (e.g. LEDs ).
Fills the lower lines with zero's.
- **void rotateRight(uint8_t n = 1)** rotates output channels to right, moving lowest line to highest line.
- **void rotateLeft(uint8_t n = 1)** rotates output channels to left, moving highest line to lowest line.
- **void reverse()** reverse the "bit pattern" of the lines, swapping pin 15 with 0, 14 with 1, 13 with 2 etc..


### Select

Some convenience wrappers.

- **void select(const uint8_t pin)** sets a single pin to HIGH, all others are set to LOW.
If pin > 15 all pins are set to LOW.
Can be used to select one of n devices.
- **void selectN(const uint8_t pin)** sets pins 0..pin to HIGH, all others are set to LOW.
If pin > 15 all pins are set to LOW.
This can typical be used to implement a VU meter.
- **void selectNone()** sets all pins to LOW.
- **void selectAll()** sets all pins to HIGH.


### Miscellaneous

- **int lastError()** returns the last error from the lib. (see .h file).


## Error codes

|  name               |  value  |  description              |
|:--------------------|:-------:|:--------------------------|
|  PCF8575_OK         |  0x00   |  no error                 |
|  PCF8575_PIN_ERROR  |  0x81   |  pin number out of range  |
|  PCF8575_I2C_ERROR  |  0x82   |  I2C communication error  |


## Testing

Testing the initial library is done by Colin Mackay (thanks!).
Platforms used for testing include: Nano, ESP32 and Seeed Xiao.


## Operation

See examples.

It is advised to use pull-up or pull-down resistors so the lines have a defined state at startup.


## Future

#### Must

- update documentation.


#### Should

- keep in sync with pcf8574 (as far as meaningful)


#### Could

- **value()** => **lastRead16()**  ??


#### Wont

