
[![Arduino CI](https://github.com/RobTillaart/PCA9634/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9634/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9634/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9634/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9634/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCA9634.svg)](https://github.com/RobTillaart/PCA9634/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9634/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9634.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9634/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCA9634.svg)](https://registry.platformio.org/libraries/robtillaart/PCA9634)


# PCA9634

Arduino library for PCA9634 I2C 8 bit PWM LED driver, 8 channel.


## Description

This library is to control the I2C PCA9634 PWM extender.
The 8 channels are independently configurable in steps of 1/256.
This allows for better than 1% fine tuning of the duty-cycle
of the PWM signal.


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change.
You cannot set the pins in **begin()** any more.
This reduces the dependency of processor dependent Wire implementations.
The user has to call **Wire.begin()** and can optionally set the Wire pins 
before calling **begin()**.


#### Related

- https://github.com/RobTillaart/PCA9634 (8 channel)
- https://github.com/RobTillaart/PCA9635 (16 channel)
- https://github.com/RobTillaart/PCA9685_RT (16 channel)


## Interface

```cpp
#include "PCA9634.h"
```


#### Constructor

- **PCA9634(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with I2C device address,
and optional the Wire interface as parameter.
- **bool begin(uint8_t mode1_mask = PCA963X_MODE1_ALLCALL, uint8_t mode2_mask = PCA963X_MODE2_NONE)**
initializes the library after startup. Optionally setting the MODE1 and MODE2 configuration registers.
See PCA9634.h and datasheet for settings possible.
- **void configure(uint8_t mode1_mask, uint8_t mode2_mask)**
To configure the library after startup one can set the MODE1 and MODE2 configuration registers.
See PCA9634.h and datasheet for settings possible.
- **bool isConnected()** checks if address is available on I2C bus.
- **uint8_t channelCount()** returns the number of channels = 8.


#### LedDriverMode

Configure LED behaviour.

- **uint8_t setLedDriverMode(uint8_t channel, uint8_t mode)** mode is 0..3 See datasheet for full details.
  - returns error code, see below.
- **uint8_t setLedDriverMode(uint8_t mode)** set same mode for ALL channels.
- **uint8_t getLedDriverMode(uint8_t channel)** returns the current mode of the channel.

|  LED mode           |  Value  |  Description                        |
|:--------------------|:-------:|:------------------------------------|
|  PCA963X_LEDOFF     |   0x00  |  led is 100% off, default @startup  |
|  PCA963X_LEDON      |   0x01  |  led is 100% on.                    |
|  PCA963X_LEDPWM     |   0x02  |  set LED in PWM mode, 0..255        |
|  PCA963X_LEDGRPPWM  |   0x03  |  add LED to the GRPPWM*             |


\* all LEDs in the group GRPPWM can be set to the same PWM value in one set.
This is ideal to trigger e.g. multiple LEDs (servo's) at same time.


#### Read and write

Read and write individual values to LED channels. 
Requires LEDs' DriverMode of the specific channels to be in PWM mode.

- **uint8_t write1(uint8_t channel, uint8_t value)** writes a single 8 bit PWM value.
- **uint8_t write3(uint8_t channel, uint8_t R, uint8_t G, uint8_t B)** 
writes three consecutive PWM registers.
typical use is to write R, G, B values for a full colour LED.
- **uint8_t writeN(uint8_t channel, uint8_t \* array, uint8_t count)** 
write count consecutive PWM registers.
May return **PCA963X_ERR_CHAN** if array has too many elements 
(including channel as offset).


#### Mode registers

Used to configure the PCA963x general behaviour.

- **uint8_t writeMode(uint8_t reg, uint8_t value)** configuration of one of the two configuration registers.
Check datasheet for details.
- **uint8_t readMode(uint8_t reg)** reads back the configured mode, 
useful to add or remove a single flag (bit masking).
- **uint8_t setMode1(uint8_t value)** convenience wrapper.
- **uint8_t setMode2(uint8_t value)** convenience wrapper.
- **uint8_t getMode1()** convenience wrapper.
- **uint8_t getMode2()** convenience wrapper.


#### Constants for mode registers


|  Name                     |  Value  |  Description                         |
|:--------------------------|:-------:|:-------------------------------------|
|  PCA963X_MODE1_AUTOINCR2  |  0x80   |  Read Only, 0 = disable  1 = enable  |
|  PCA963X_MODE1_AUTOINCR1  |  0x40   |  Read Only, bit1                     |
|  PCA963X_MODE1_AUTOINCR0  |  0x20   |  Read Only, bit0                     |
|  PCA963X_MODE1_SLEEP      |  0x10   |  0 = normal        1 = sleep         |
|  PCA963X_MODE1_SUB1       |  0x08   |  0 = disable       1 = enable        |
|  PCA963X_MODE1_SUB2       |  0x04   |  0 = disable       1 = enable        |
|  PCA963X_MODE1_SUB3       |  0x02   |  0 = disable       1 = enable        |
|  PCA963X_MODE1_ALLCALL    |  0x01   |  0 = disable       1 = enable        |
|  PCA963X_MODE1_NONE       |  0x00   |                                      |
|  ----                     |         |                                      |
|  PCA963X_MODE2_BLINK      |  0x20   |  0 = dim           1 = blink         |
|  PCA963X_MODE2_INVERT     |  0x10   |  0 = normal        1 = inverted      |
|  PCA963X_MODE2_STOP       |  0x08   |  0 = on STOP       1 = on ACK        |
|  PCA963X_MODE2_TOTEMPOLE  |  0x04   |  0 = open drain    1 = totem-pole    |
|  PCA963X_MODE2_NONE       |  0x00   |                                      |


These constants makes it easier to set modes without using a non descriptive
bit mask. The constants can be merged by OR-ing them together, see snippet:

```cpp
ledArray.writeMode(PCA963X_MODE2, 0b00110100);

// would become

uint8_t mode2_mask = PCA963X_MODE2_BLINK | PCA963X_MODE2_INVERT | PCA963X_MODE2_TOTEMPOLE;
ledArray.writeMode(PCA963X_MODE2, mode2_mask);

// or even

ledArray.setMode2(PCA963X_MODE2_BLINK | PCA963X_MODE2_INVERT | PCA963X_MODE2_TOTEMPOLE);
```


#### Group PWM and frequency

Check datasheet for the details.

- **void setGroupPWM(uint8_t value)** sets all channels that are part of the PWM group to value.
- **uint8_t getGroupPWM()** get the current PWM setting of the group.
- **void setGroupFREQ(uint8_t value)** is used for blinking the group of configured LED. 
Value goes from 0 to 255 with each step representing an increase of approx. 41 ms. 
So 0x00 results in 41 ms blinking period (on AND off) and 0xFF in approx. 10.5 s.
- **uint8_t getGroupFREQ()** returns the set frequency of the PWM group.


#### Miscellaneous

- **int lastError()** returns **PCA963X_OK** if all is OK, and other error codes otherwise.

|  Error code         |  Value  |  Description           |
|:--------------------|:-------:|:-----------------------|
|  PCA963X_OK         |   0x00  |  Everything went well
|  PCA963X_ERROR      |   0xFF  |  Generic error
|  PCA963X_ERR_WRITE  |   0xFE  |  Tries to write more elements than PWM channels
|  PCA963X_ERR_CHAN   |   0xFD  |  Channel out of range
|  PCA963X_ERR_MODE   |   0xFC  |  Invalid mode
|  PCA963X_ERR_REG    |   0xFB  |  Invalid register
|  PCA963X_ERR_I2C    |   0xFA  |  I2C communication error


## SUB CALL and ALL CALL

Please read the datasheet to understand the working of **SUB CALL** and **ALL CALL**.

Since version 0.2.0 there is (experimental) support for the **SUB CALL** and **ALL CALL** functions.
It needs more testing and if there are issues, please report.

AllCall is automatically activated for each device on startup.


#### Description

**SUB CALL** allows one to make groups of PCA9634 devices and control them on group level.
The number of groups one can make depends on free I2C addresses on one I2C bus.
Using multiple I2C buses or multiplexers will even increase the possible number. 
Every PCA9634 device can be member of up to three of these groups. 
To become member one needs to set the **setSubCallAddress(nr, address)** and enable 
it with **enableSubCall(nr)**.

In the same way one can become member of an **ALL CALL** group.
Typically there is only one such group but one can configure more of them by applying different addresses.


#### Interface

The functions to enable all/sub-addresses are straightforward:

- **bool enableSubCall(uint8_t nr)** nr = 1,2,3
- **bool disableSubCall(uint8_t nr)** nr = 1,2,3
- **bool isEnabledSubCall(uint8_t nr)** nr = 1,2,3
- **bool setSubCallAddress(uint8_t nr, uint8_t address)**
- **uint8_t getSubCallAddress(uint8_t nr)**

- **bool enableAllCall()**
- **bool disableAllCall()**
- **bool isEnabledAllCall()**
- **bool setAllCallAddress(uint8_t address)**
- **uint8_t getAllCallAddress()**


#### OutputEnable

Since 0.2.6 (experimental) support to control the OE (Output Enable) pin of the PCA9634.
This OE pin can control all LEDs simultaneously. 
It also allows to control multiple devices by connecting the OE pins.
Think of simultaneous switching ON/OFF or get dimming with a high frequency PWM.
Or use 2 modules alternatively by placing an inverter in between.

See datasheet for the details

- **bool setOutputEnablePin(uint8_t pin = 255)** sets the IO pin to connect to the OE pin of the device.
A value of 255 indicates no pin set/selected.
Sets the OE pin to HIGH.
Returns true on success.
- **bool setOutputEnable(uint8_t value)** Sets the OE pin HIGH or LOW.
All non zero values are LOW.
Returns true on success.
- **uint8_t getOutputEnable()** get the current value of the OE pin.
If pin is not set/selected it will return HIGH.

Note: the OE is LOW active. 
The user has to set the power on value by means of a PULL UP / DOWN resistor.


#### I2C Software reset

The goal of this function is to reset ALL devices on the bus.
When using the software reset, ALL devices attached to the bus are set to their hardware startup conditions.
Generally, there are multiple definitions of software resets by the I2C inventor NXP.
To accommodate this, two different modes for this function have been defined and tested (library version 0.2.2).

- Method 1 is a tested method which is specific to the PCA9634.
Since the number of different types of I2C chips is very large, side-effects on other chips might be possible.
Before using this method, consult the data sheets of all chips on the bus to mitigate potential undefined states.
- Method 0 is a somewhat “general” method which resets many chips on the I2C-bus.
However, this method DOES NOT reset the PCA9634 chip.
Therefore, consult the data sheet of all different chips on the bus to mitigate potential undefined states.

When only working with PCA9634 chips on a bus, only method 1 is required.

```cpp
ledArray.I2C_SoftwareReset(1);  //  for method 1
ledArray.I2C_SoftwareReset(0);  //  for method 0
```

In case you experience issues with this function on your chips (non-PCA9634),
please give feedback, so the documentation can be improved.

For further details of the development, see - #10 (comment)


#### LEDOUT

Experimental, needs testing, read datasheet 7.3.6

The LEDOUT0 (12) and LEDOUT1 (13) registers can be used to set the 
operational mode how each channel / LED is controlled. 
The typical use case is to use PWM per channel
but one can also set a channel / LED fully ON or OFF. 
These functions are a fast way to switch multiple LEDs ON/OFF.

The two registers LEDOUT0 .. LEDOUT1 each control 4 channels

|  register  |  channels  |  mask layout  |  notes  |
|:----------:|:----------:|:-------------:|:-------:|
|    0       |   0 ..  3  |   33221100    |  every channel has 2 bits.
|    1       |   4 ..  7  |   idem        |


- **uint8_t writeLedOut(uint8_t reg, uint8_t mask)**
  - reg = 0..1, if larger than 1 **PCA963X_ERROR** returned.
  - mask see below.
- **uint8_t readLedOut(uint8_t reg)**
  - reg = 0..1, if larger than 1 **0x00** is returned. Use with care.
  - returns the register 

To set channel 6 OFF and 7 ON simultaneously:

```cpp
uint8_t mask = PCA.readLedOut(1);
mask &= 0b00001111;  //  set OFF both 6 and 7
mask |= 0b01000000;  //  set ON 7
PCA.writeLedOut(1, mask);
```


## Synchronous multi-chip multi-LED operation

In scenarios in which multiple LED states should be updated synchronously, the datasheet specifies a specific sequence. 
Therefore, it is possible to update multiple LED registers in one or more PCA963x chips synchronously and have them 
change their state at a final STOP command. For this only a few configurations are required.
1. Make sure, the `PCA963X_MODE2_ACK` bit in the `MODE2` register is not set (it should be set to 0). 
Therefore, the LED states will be updated at the STOP command of the I2C master and not during the ACK command of the PCA963x slave
2. Do NOT use the `write1()`, `write3()` or `writeN()` functions for changing LED states. 
These commands already include a STOP command.
3. Use consecutive `writeN_noStop()` commands for multiple LEDs (can be on the same or different chips) and finish 
the communication with the `writeStop()` command. The latter will send a STOP command and end the transmission. 
If the PCA963x chips are configured to update their states on the STOP command, this will be the point in time, 
when all previously send commands since the last STOP command will be executed.
4. DISCLAIMER:
  - This should not be used during the configuration of the chips as the library has not been tested for this. 
  Furthermore, the configuration functions `writeMode` have STOP commands included  
  - This function has not been tested for edge cases (what happened when no STOP command is send? 
  In theory nothing should happen until the next transmission with an STOP command has been send). 
  Test functionality before implementation into your projects.



## Future

#### Must

- improve documentation
  - restructure readme.md


#### Should

- improve error handling
  - return values etc.
  - documentation.
- keep in sync with PCA9634/5 developments


#### Could

- unit tests
  - SUB CALL if possible?
  - ALL CALL if possible?
- add examples
  - read/writeLedOut()
- **setOutputEnablePWM(uint16_t value)** PWM support ?
  - getter?
- restructure function groups 
  - in  .cpp to match .h
  - readme.md
- **setGroupFreq()**
  -  set time in milliseconds and round to nearest value?


#### Wont

- consider implementing 
  - clearMode1() and clearMode2() functions.
  - only upon request.
- merge with PCA9634/5 and a PCA963X base class if possible
  - not easy, more alignment is desirable.
  - only upon request.
- **setGroupPWM()**
  - PWM also in %% ?  (trivial for user)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

