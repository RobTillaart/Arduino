
[![Arduino CI](https://github.com/RobTillaart/PCA9634/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9634/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9634/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9634/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9634/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9634/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9634.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9634/releases)


# PCA9634

Arduino library for PCA9634 I2C 8 bit PWM LED driver, 8 channel.


## Description

This library is to control the I2C PCA9634 PWM extender.
The 8 channels are independently configurable in steps of 1/256.
this allows for better than 1% fine tuning of the duty-cycle
of the PWM signal. 

library is a 8 channel derived variation of the PCA9635 class.
(these might merge in the future)


## Interface


### Constructor

- **PCA9634(uint8_t deviceAddress, TwoWire \*wire = &Wire)** Constructor with I2C device address, 
and optional the Wire interface as parameter.
- **bool begin(uint8_t mode1_mask = PCA9634_MODE1_ALLCALL, uint8_t mode2_mask = PCA9634_MODE2_NONE)** 
initializes the library after startup. Optionally setting the MODE1 and MODE2 configuration registers. 
See PCA9634.h and datasheet for settings possible.
- **bool begin(uint8_t sda, uint8_t scl, uint8_t mode1_mask = PCA9634_MODE1_ALLCALL, uint8_t mode2_mask = PCA9634_MODE2_NONE)** 
idem, ESP32 ESP8266 only. 
- **void configure(uint8_t mode1_mask, uint8_t mode2_mask)** 
To configure the library after startup one can set the MODE1 and MODE2 configuration registers. 
See PCA9634.h and datasheet for settings possible. 
- **bool isConnected()** checks if address is available on I2C bus.
- **uint8_t channelCount()** returns the number of channels = 8.


### LedDriverMode

Configure LED behaviour.

- **uint8_t setLedDriverMode(uint8_t channel, uint8_t mode)** mode is 0..3 See datasheet for full details.
- **uint8_t getLedDriverMode(uint8_t channel)** returns the current mode of the channel.

| LED mode           | Value | Description                       |
|:-------------------|:-----:|:----------------------------------|
| PCA9634_LEDOFF     | 0x00  | led is 100% off, default @startup |
| PCA9634_LEDON      | 0x01  | led is 100% on.                   |
| PCA9634_LEDPWM     | 0x02  | set LED in PWM mode, 0..255       |
| PCA9634_LEDGRPPWM  | 0x03  | add LED to the GRPPWM*            |

\* all LEDs in the group GRPPWM can be set to the same PWM value in one set.
This is ideal to trigger e.g. multiple LEDs (servo's) at same time.


### Read and write

Read and write individual values to LED channels. 
Requires LEDs' DriverMode of the specific channels to be in PWM mode.

- **uint8_t write1(uint8_t channel, uint8_t value)** writes a single 8 bit PWM value.
- **uint8_t write3(uint8_t channel, uint8_t R, uint8_t G, uint8_t B)** 
writes three consecutive PWM registers.
typical use is to write R, G, B values for a full colour LED.
- **uint8_t writeN(uint8_t channel, uint8_t \* array, uint8_t count)** 
write count consecutive PWM registers. 
May return **PCA9634_ERR_WRITE** if array has too many elements 
(including channel as offset).


### Mode registers

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

(added 0.1.2)

| Name                    | Value | Description                        |
|:------------------------|:-----:|:-----------------------------------|
| PCA9634_MODE1_AUTOINCR2 | 0x80  | Read Only, 0 = disable  1 = enable |
| PCA9634_MODE1_AUTOINCR1 | 0x40  | Read Only, bit1                    |
| PCA9634_MODE1_AUTOINCR0 | 0x20  | Read Only, bit0                    |
| PCA9634_MODE1_SLEEP     | 0x10  | 0 = normal        1 = sleep        |
| PCA9634_MODE1_SUB1      | 0x08  | 0 = disable       1 = enable       |
| PCA9634_MODE1_SUB2      | 0x04  | 0 = disable       1 = enable       |
| PCA9634_MODE1_SUB3      | 0x02  | 0 = disable       1 = enable       |
| PCA9634_MODE1_ALLCALL   | 0x01  | 0 = disable       1 = enable       |
|                         |       |                                    |
| PCA9634_MODE2_BLINK     | 0x20  | 0 = dim           1 = blink        |
| PCA9634_MODE2_INVERT    | 0x10  | 0 = normal        1 = inverted     |
| PCA9634_MODE2_STOP      | 0x08  | 0 = on STOP       1 = on ACK       |
| PCA9634_MODE2_TOTEMPOLE | 0x04  | 0 = open drain    1 = totem-pole   |


These constants makes it easier to set modes without using a non descriptive
bit mask. The constants can be merged by OR-ing them together, see snippet:

```cpp
ledArray.writeMode(PCA9634_MODE2, 0b00110100);

// would become

uint8_t mode2_mask = PCA9634_MODE2_BLINK | PCA9634_MODE2_INVERT | PCA9634_MODE2_TOTEMPOLE;
ledArray.writeMode(PCA9634_MODE2, mode2_mask);

// or even

ledArray.setMode2(PCA9634_MODE2_BLINK | PCA9634_MODE2_INVERT | PCA9634_MODE2_TOTEMPOLE);

```


### Group PWM and frequency

Check datasheet for the details.

- **void setGroupPWM(uint8_t value)** sets all channels that are part of the PWM group to value.
- **uint8_t getGroupPWM()** get the current PWM setting of the group.
- **void setGroupFREQ(uint8_t value)** is used for blinking the group of configured LED. 
Value goes from 0 to 255 with each step representing an increase of approx. 41 ms. 
So 0x00 results in 41 ms blinking period (on AND off) and 0xFF in approx. 10.5 s.
- **uint8_t getGroupFREQ()** returns the set frequency of the PWM group.


### Miscellaneous

- **int lastError()** returns **PCA9634_OK** if all is OK, and other error codes otherwise.

| Error code        | Value | Description          |
|:------------------|:-----:|:---------------------|
| PCA9634_OK        | 0x00  | Everything went well
| PCA9634_ERROR     | 0xFF  | Generic error
| PCA9634_ERR_WRITE | 0xFE  | Tries to write more elements than PWM channels
| PCA9634_ERR_CHAN  | 0xFD  | Channel out of range
| PCA9634_ERR_MODE  | 0xFC  | Invalid mode
| PCA9634_ERR_REG   | 0xFB  | Invalid register
| PCA9634_ERR_I2C   | 0xFA  | I2C communication error


### SUB CALL and ALL CALL

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


## Operation

See examples


## Future

- improve documentation
- unit tests
  - SUB CALL if possible?
  - ALL CALL if possible?
- add examples
- sync with PCA9635 developments
- merge with PCA9635 and a PCA963X base class if possible

