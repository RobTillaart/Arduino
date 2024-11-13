
[![Arduino CI](https://github.com/RobTillaart/DAC8574/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8574/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8574/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8574/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8574/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAC8574.svg)](https://github.com/RobTillaart/DAC8574/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8574/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8574.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8574/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAC8574.svg)](https://registry.platformio.org/libraries/robtillaart/DAC8574)


# DAC8574

Arduino library for DAC8574, I2C, 4 channel, 16 bit DAC.

## Description

**Experimental**

The DAC8574 is a small low-power, four channel, 16-bit voltage 
Power-On Reset to Zero output DAC.

The output value of each channel can be set from 0..65535.
This results in a voltage which depends on a reference voltage Vref (see datasheet).
At power up each channel always will start with a value of zero.

The DAC8574 has a temporary register in which a value can be preloaded.
This can be used to change the DAC at a later moment.

**Not supported** is the broadcast function to change multiple DAC8574 
(and compatibles) at the same moment by using this temporary register.

As said the library is experimental need to be tested with hardware.
Feedback is always welcome, please open an issue.

Kudos to Doctea for first tests.


### Settling time

From datasheet page 24.

Settling time to within the 16-bit accurate range of the DAC8574 is achievable within 
10 μs for a full-scale code change at the input. 
Worst case settling times between consecutive code changes is typically less than 2 μs,
therefore, the update rate is limited by the I2C interface.


## I2C

### Address

The DAC8574 support 2 addresses by means of an A0 address pin.


|  Address  |   A0   |   A1   |
|:---------:|:------:|:------:|
|   0x4C    |   LOW  |   LOW  |
|   0x4D    |   LOW  |  HIGH  |
|   0x4E    |  HIGH  |   LOW  |
|   0x4F    |  HIGH  |  HIGH  |

It might be possible to connect one address pin to an IO pin and 
keep only of multi DAC's HIGH and the remaining LOW to support multiple devices.
This is not tested, feedback welcome.


### I2C pull ups

To be able to reach 1 MHz (ESP32) the pull ups need to be fairly strong.
Preliminary tests (DAC8571) indicate that 2K work.


### I2C performance

Extend table, use output of **DAC8574_performance.ino**

Time in microseconds.  
array == write(array, length)
Assumption all write modi have similar performance.

Test Arduino UNO  - version 0.1.0

|  Speed   |  function  |  time  |  notes  |
|:--------:|:----------:|:------:|:-------:|
|  100000  |  write()   |        |
|  100000  |  read()    |        |
|  200000  |  write()   |        |
|  200000  |  read()    |        |
|  400000  |  write()   |        |
|  400000  |  read()    |        |


Test ESP32 - version 0.1.0

|  Speed   |  write()  |  read()  |  write(array)  |  Notes  |
|:--------:|:---------:|:--------:|:--------------:|:--------|
|  50000   |           |          |                |
|  100000  |           |          |                |
|  200000  |           |          |                |
|  300000  |           |          |                |
|  400000  |           |          |                |
|  500000  |           |          |                |
|  600000  |           |          |                |
|  700000  |           |          |                |
|  800000  |           |          |                |
|  900000  |           |          |                |
|  1000000 |           |          |                |



### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up 
to eight channels (think of it as I2C subnets) which can use the complete 
address range of the device. 

Drawback of using a multiplexer is that it takes more administration in 
your code e.g. which device is on which channel. 
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices 
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


### Related

- https://github.com/RobTillaart/AD5680 (18 bit DAC)
- https://github.com/RobTillaart/DAC8550
- https://github.com/RobTillaart/DAC8551
- https://github.com/RobTillaart/DAC8552
- https://github.com/RobTillaart/DAC8554
- https://github.com/RobTillaart/DAC8571
- https://github.com/RobTillaart/DAC8574
- https://github.com/RobTillaart/MCP_DAC
- https://github.com/RobTillaart/MCP_ADC


## Interface

```cpp
#include "DAC8574.h"
```

### Constructor

- **DAC8574(uint8_t address = 0x4C, TwoWire \*wire = &Wire)** constructor with I2C address.
Default is 0x4C, optional set the WireN I2C bus.
- **bool begin(uint16_t value = 0)** Set initial value for the DAC, typical zero (power on default).
Returns false if address out of range, or if device cannot be seen on the I2C bus.
Returns **true** if successful.
- **bool isConnected()** test to see if address can be reached on the I2C bus.
- **uint8_t getAddress()** returns address set in constructor.


### Core

The DAC8574 has one 16 bit DAC. The output value can be set from 0..65535.

- **bool write(uint8_t channel, uint16_t value)** writes a value 0..65535 to the 
selected channel of the DAC.
No default, user must explicit set value.
- **uint16_t lastWrite(uint8_t channel)** get last value written from cache (fast).
- **uint16_t read(uint8_t channel)** get last written value from device.

Percentage wrappers

- **void setPercentage(uint8_t channel, float perc)** set 0.00 .. 100.00.
Value is constrained to 0..100
- **float getPercentage(uint8_t channel)** returns 0.0 .. 100.0 from cache.


### Write modi

The DAC8574 can be written in different modi (datasheet page 19).
Not all modi are supported yet, these need testing.

- **void setWriteMode(uint8_t mode = DAC8574_MODE_NORMAL)**
- **uint8_t getWriteMode()**


Setting the mode will be applied for all writes until mode is changed.

|  Mode                    |  Meaning  |
|:-------------------------|:----------|
| DAC8574_MODE_STORE_CACHE |  store value in temporary register. Preparation for (2, 3 and 4)
| DAC8574_MODE_NORMAL      |  update DAC with value written. **DEFAULT**.
| DAC8574_MODE_WRITE_CACHE |  writes the temporary register to DAC, ignores new value.
| DAC8574_MODE_BRCAST_0    |  broadcast update. **Not supported yet**. See below.
| DAC8574_MODE_BRCAST_1    |  broadcast update. **Not supported yet**. See below.
| DAC8574_MODE_BRCAST_2    |  broadcast update. **Not supported yet**. See below.
| other                    |  maps onto default **DAC8574_MODE_NORMAL**.


### Write multiple values - High speed mode.

The maximum length depends on the internal I2C BUFFER of the board.
For Arduino this is typical 32 bytes so it allows 14 values.

- **void write(uint16_t arr[n], uint8_t length)** Writes a buffer with 
max 14 values in one I2C call. 
The last value written will be remembered in **lastWrite()**.


### Power Down mode

To investigate: Mixes also with broadcast ==> complex API.

- **bool powerDown(uint8_t pdMode = 0)** default low power.
returns false on failure.
- **bool wakeUp(uint16_t value = 0)** wake up, DAC value set to zero by default.
returns false on failure.

See table 8, page 27 datasheet for details.

|  Power Down Mode       |  value  |  Meaning  |
|:-----------------------|:-------:|:----------|
|  DAC8574_PD_LOW_POWER  |    0    |  170 uA
|  DAC8574_PD_1_KOHM     |    1    |  200 nA, GND 1 KOhm
|  DAC8574_PD_100_KOHM   |    2    |  200 nA, GND 100 KOhm
|  DAC8574_PD_HI_Z       |    3    |  200 nA, open circuit, high impedance


### Broadcast mode

**Not supported**

Different ways possible, need to investigate API. (page 19)

Three broadcast commands exists:

|  Mode                   |  Meaning  |
|:------------------------|:----------|
|  DAC8574_MODE_BRCAST_0  | Load all devices from temporary register
|  DAC8574_MODE_BRCAST_1  | Load all devices with data.
|  DAC8574_MODE_BRCAST_2  | Power down all devices


### Error codes

- **int lastError()** always check this value after a read() / write() 
to see if it was DAC8574_OK.
After the call to **lastError()** the error value is reset to DAC8574_OK.

|  Error code             |  Value  |  Notes  |
|:------------------------|:-------:|:--------|
|  DAC8574_OK             |  0x00   |
|  DAC8574_I2C_ERROR      |  0x81   |
|  DAC8574_ADDRESS_ERROR  |  0x82   |
|  DAC8574_BUFFER_ERROR   |  0x83   |  write(arr, length) length error
|  DAC8574_CHANNEL_ERROR  |  0x84   |


## Future

#### Must

- get hardware to test
- improve documentation
- test different write modi

#### Should

- extend / fill performance table
- replace magic numbers
- derived classes **DAC7574** (12 bit) **DAC6574** (10 bit)?

#### Could

- add examples

#### Wont

- investigate broadcast support

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


