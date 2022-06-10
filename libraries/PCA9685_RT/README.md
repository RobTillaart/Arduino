
[![Arduino CI](https://github.com/RobTillaart/PCA9685_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/PCA9685_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/PCA9685_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/PCA9685_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/PCA9685_RT/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/PCA9685_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/PCA9685_RT.svg?maxAge=3600)](https://github.com/RobTillaart/PCA9685_RT/releases)


# PCA9685_RT

Arduino library for PCA9685 I2C 12 bit PWM LED driver, 16 channel.


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


## Interface


### Constructor

- **PCA9685(uint8_t deviceAddress, TwoWire \* wire = &Wire)** Constructor with I2C device address, 
and optional the Wire interface as parameter.
- **bool begin(uint8_t mode1_mask = PCA9685_MODE1_AUTOINCR | PCA9685_MODE1_ALLCALL, uint8_t mode2_mask = PCA9685_MODE2_TOTEMPOLE)** 
initializes the library after startup. Optionally setting the MODE1 and MODE2 configuration registers. 
See PCA9685.h and datasheet for settings possible.
- **bool begin(uint8_t sda, uint8_t scl, uint8_t mode1_mask = PCA9685_MODE1_AUTOINCR | PCA9685_MODE1_ALLCALL, uint8_t mode2_mask = PCA9685_MODE2_TOTEMPOLE)** 
idem, ESP32 ESP8266 only. 
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
| PCA9685_MODE2_BLINK     | 0x20  | 0 = dim           1 = blink        |
| PCA9685_MODE2_INVERT    | 0x10  | 0 = normal        1 = inverted     |
| PCA9685_MODE2_STOP      | 0x08  | 0 = on STOP       1 = on ACK       |
| PCA9685_MODE2_TOTEMPOLE | 0x04  | 0 = open drain    1 = totem-pole   |
| PCA9685_MODE2_OUTNE     | 0x03  | check datasheet                    |
| PCA9685_MODE2_NONE      | 0x00  |                                    |

These constants makes it easier to set modes without using a non descriptive
bit mask. The constants can be merged by OR-ing them together, see snippet:

```cpp
ledArray.writeMode(PCA9685_MODE2, 0b00110100);

// would become

uint8_t mode2_mask = PCA9685_MODE2_BLINK | PCA9685_MODE2_INVERT | PCA9685_MODE2_TOTEMPOLE;
ledArray.writeMode(PCA9685_MODE2, mode2_mask);

// or even

ledArray.setMode2(PCA9685_MODE2_BLINK | PCA9685_MODE2_INVERT | PCA9685_MODE2_TOTEMPOLE);

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
- **void digitalWrite(channel, mode)** mode = HIGH or LOW, just use the PCA9685 as 
a digital pin. 
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


## Operation

See examples


## Future

- improve documentation
- add unit tests (if possible)
- investigate int vs uint16_t ?
  - **setFrequency(), getFrequency(), \_freq**
- sync with PCA9634/35/85 where possible
  - error handling?


