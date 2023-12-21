
[![Arduino CI](https://github.com/RobTillaart/PCA9685_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9685_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9685_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9685_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9685_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/PCA9685_RT.svg)](https://github.com/RobTillaart/PCA9685_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9685_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9685_RT.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9685_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/PCA9685.svg)](https://registry.platformio.org/libraries/robtillaart/PCA9685)


# PCA9685_RT

Arduino library for PCA9685 I2C LED driver, 16 channel PWM, 12 bit.


## Description

This library is to control the I2C PCA9685 PWM extender. 
The 16 channels are independently configurable in steps of 1/4096.
This allows for better than 0.1% fine tuning of the duty-cycle
of the PWM signal. 

The PWM's of the different channels have individual start and stop moments. 
This can be used to distribute the power more evenly over multiple servo's 
or give special effects when used in an RGB LED.

The frequency of the PWM can be set from 24 to 1526 according to the datasheet, 
however in practice not all frequencies are set accurate.
Lower frequencies do better than higher frequencies.



#### 0.7.0 Breaking change

The version 0.7.0 has breaking changes in the interface. 
The rationale is that the programming environment of the **Arduino ESP32 S3** 
board uses a remapping by means of the include file **io_pin_remap.h**.
This file remaps the pins of several core Arduino functions. 
The remapping is implemented by #define macros and these implement "hard" text 
replacements without considering context. 
The effect is that methods from this class (and several others) which have the same 
name as those Arduino core functions will be remapped into something not working.

The following library functions have been renamed:

|  old name        |  new name    |  notes  |
|:-----------------|:-------------|:--------|
|  analogRead()    |  read()      |
|  analogWrite()   |  write()     |
|  pinMode()       |  pinMode1()  |
|  digitalRead()   |  read1()     |
|  digitalWrite()  |  write1()    |


#### 0.6.0 Breaking change

Version 0.6.0 introduced a breaking change.
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
#include "PCA9685.h"
```

### Constructor

- **PCA9685(uint8_t deviceAddress, TwoWire \* wire = &Wire)** Constructor with I2C device address, 
and optional the Wire interface as parameter.
- **bool begin(uint8_t mode1_mask = PCA9685_MODE1_AUTOINCR | PCA9685_MODE1_ALLCALL, uint8_t mode2_mask = PCA9685_MODE2_TOTEMPOLE)** 
initializes the library after startup. Optionally setting the MODE1 and MODE2 configuration registers. 
See PCA9685.h and datasheet for settings possible.
- **void configure(uint8_t mode1_mask, uint8_t mode2_mask)** 
To configure the library after startup one can set the MODE1 and MODE2 configuration registers. 
See PCA9685.h and datasheet for settings possible.
- **bool isConnected()** checks if address is available on I2C bus.
- **uint8_t channelCount()** returns the number of channels = 16.


### Mode registers

Used to configure the PCA9685 general behaviour.

- **uint8_t writeMode(uint8_t reg, uint8_t value)** configuration of one of the two configuration registers.
Check datasheet for details.
- **uint8_t readMode(uint8_t reg)** reads back the configured mode, 
useful to add or remove a single flag (bit masking).
- **uint8_t setMode1(uint8_t value)** convenience wrapper.
- **uint8_t setMode2(uint8_t value)** convenience wrapper.
- **uint8_t getMode1()** convenience wrapper.
- **uint8_t getMode2()** convenience wrapper.


#### Constants for mode registers

(added 0.4.0)

| Name                    | Value | Description                        |
|:------------------------|:-----:|:-----------------------------------|
| PCA9685_MODE1_RESTART   | 0x80  | 0 = disable       1 = enable       |
| PCA9685_MODE1_EXTCLK    | 0x40  | 0 = internal      1 = external     |
| PCA9685_MODE1_AUTOINCR  | 0x20  | 0 = disable       1 = enable       |
| PCA9685_MODE1_SLEEP     | 0x10  | 0 = normal        1 = sleep        |
| PCA9685_MODE1_SUB1      | 0x08  | 0 = disable       1 = enable       |
| PCA9685_MODE1_SUB2      | 0x04  | 0 = disable       1 = enable       |
| PCA9685_MODE1_SUB3      | 0x02  | 0 = disable       1 = enable       |
| PCA9685_MODE1_ALLCALL   | 0x01  | 0 = disable       1 = enable       |
| PCA9685_MODE1_NONE      | 0x00  |                                    |
|                         |       |                                    |
| PCA9685_MODE2_INVERT    | 0x10  | 0 = normal        1 = inverted     |
| PCA9685_MODE2_STOP      | 0x08  | 0 = on STOP       1 = on ACK       |
| PCA9685_MODE2_TOTEMPOLE | 0x04  | 0 = open drain    1 = totem-pole   |
| PCA9685_MODE2_OUTNE     | 0x03  | check datasheet                    |
| PCA9685_MODE2_NONE      | 0x00  |                                    |

These constants makes it easier to set modes without using a non descriptive
bit mask. The constants can be merged by OR-ing them together, see snippet:

```cpp
ledArray.writeMode(PCA9685_MODE2, 0b00010100);

// would become

uint8_t mode2_mask = PCA9685_MODE2_INVERT | PCA9685_MODE2_TOTEMPOLE;
ledArray.writeMode(PCA9685_MODE2, mode2_mask);

// or even

ledArray.setMode2(PCA9685_MODE2_INVERT | PCA9685_MODE2_TOTEMPOLE);

```

### PWM

- **void setPWM(uint8_t channel, uint16_t onTime, uint16_t offTime)** The chip has 16 channels to do PWM.
The signal is divided in 4096 steps, 0..4095. 
The pulse can begin **onTime** on any step and it can stop on any step **offTime**.
This allows e.g. to distribute the power over the 16 channels, e.g. the
channels do not need to start at the same moment with HIGH.
- **void setPWM(uint8_t channel, offTime)** simple PWM that always start on **onTime = 0**.
- **void getPWM(uint8_t channel, uint16_t \* onTime, uint16_t \* offTime)** 
read back the configuration of the channel.
- **void allOFF()** switches all PWM channels OFF. **Experimental** in 0.3.0.
To "undo" the allOFF one can call the **reset()** function and set all 
PWM channels again.
- **void write1(channel, mode)** mode = HIGH or LOW, just use the PCA9685 as 
a digital pin, write 1 bit.
This single function replaces the setON() and setOFF() that will become
obsolete in the future.


### Frequency 

- **void setFrequency(uint16_t freq, int offset = 0)** set the update speed of the channels. 
This value is set the same for all channels at once.
- **int getFrequency(bool cache = true)** get the current update frequency of the channels. 
This is same for all channels. If cache is false, the frequency is fetched and
calculated from the **preScaler** register and will probably differ from the 
value set with **setFrequency()**.

The frequency is constrained to be between 24 and 1526 Hz.
As the frequency is converted to an 8 bit **preScaler**,
the frequency set will seldom be exact.
After changing the frequency, one must set all channels (again), 
so one should set the frequency in **setup()**

The parameter offset can be used to tune the **preScaler** to get a frequency
closer to the requested value. See **PCA9685_setFrequency_offset** example. 
Default the offset = 0. As the **preScaler** is smaller at higher frequencies 
higher frequencies are less accurate.
Making offset too large can result in very incorrect frequencies.

When using offset, the **getFrequency(false)** will return the adjusted **preScaler**.


### Miscellaneous

- **int lastError()** returns **PCA9685_OK = 0** if all is OK, and 

| Error code          | Value | Description |
|:--------------------|:-----:|:------------|
| PCA9685_OK          | 0x00  | Everything went well
| PCA9685_ERROR       | 0xFF  | generic error
| PCA9685_ERR_CHANNEL | 0xFE  | Channel out of range
| PCA9685_ERR_MODE    | 0xFD  | Invalid mode register chosen    | 
| PCA9685_ERR_I2C     | 0xFC  | PCA9685 I2C communication error |


### SUB CALL and ALL CALL

(new since 0.4.0)

Please read the datasheet to understand the working of **SUB CALL** and **ALL CALL**.

Since version 0.4.0 there is (experimental) support for the **SUB CALL** and **ALL CALL** functions.
It needs more testing and if there are issues, please report.

AllCall is automatically activated for each device on startup.


#### Description

**SUB CALL** allows one to make groups of PCA9685 devices and control them on group level.
The number of groups one can make depends on free I2C addresses on one I2C bus.
Using multiple I2C buses or multiplexers will even increase the possible number. 
Every PCA9685 device can be member of up to three of these groups. 
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

Since 0.4.2 (experimental) support to control the OE (Output Enable) pin of the PCA9685.
This OE pin can control all LEDs simultaneously. 
It also allows to control multiple PCA9685 modules by connecting the OE pins.
Think of simultaneous switching ON/OFF or get dimming with a high frequency PWM.
Or use 2 modules alternatively by placing an inverter in between.

See datasheet for the details

- **bool setOutputEnablePin(uint8_t pin = 255)** sets the IO pin to connect to the OE pin of the PCA9634.
A value of 255 indicates no pin set/selected.
Sets the OE pin to HIGH.
Returns true on success.
- **bool setOutputEnable(uint8_t value)** Sets the OE pin HIGH or LOW.
All non zero values are LOW.
Returns true on success.
- **uint8_t getOutputEnable()** get the current value of the OE pin.
If pin is not set/selected it will return HIGH.

Note: the OE is LOW active. 
The user has to set the power on value by means of a PULL DOWN resistor.


#### I2C Software reset

The goal of this function is to reset ALL PCA9685 devices on the bus.
When using the software reset, ALL devices attached to the bus are set to their hardware startup conditions.
Generally, there are multiple definitions of software resets by the I2C inventor NXP.
To accommodate this, two different modes for this function have been defined and tested (See PCA9634).

- Method 1 is a tested method which is specific to the PCA9634.
Since the number of different types of I2C chips is very large, side-effects on other chips might be possible.
Before using this method, consult the data sheets of all chips on the bus to mitigate potential undefined states.
- Method 0 is a somewhat “general” method which resets many chips on the I2C-bus.
However, this method DOES NOT reset the PCA9685 chip.
Therefore, consult the data sheet of all different chips on the bus to mitigate potential undefined states.

When only working with PCA9685 chips on a bus, only method 1 is required.

```cpp
ledArray.I2C_SoftwareReset(1);  //  for method 1
ledArray.I2C_SoftwareReset(0);  //  for method 0
```

In case you experience issues with this function on your chips (non-PCA9685),
please give feedback, so the documentation can be improved.

For further details of the development, see - #10 (PCA9634 repo)


## Operation

See examples


## Future

#### Must

- improve documentation

#### Should

- add unit tests (if possible)

#### Could

- investigate int vs uint16_t ?
  - **setFrequency(), getFrequency(), \_freq**
- sync with PCA9634/35/85 where possible
  - error handling?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


