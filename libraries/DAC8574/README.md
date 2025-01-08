
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

Kudos to doctea for first tests of the library.


### Settling time

From datasheet page 24.

Settling time to within the 16-bit accurate range of the DAC8574 is achievable within 
10 μs for a full-scale code change at the input. 
Worst case settling times between consecutive code changes is typically less than 2 μs,
therefore, the update rate is limited by the I2C interface.


## I2C

### Address

The DAC8574 supports 4 addresses by means of an A0 and A1 address pin.

|  Address  |   A1   |   A0   |
|:---------:|:------:|:------:|
|   0x4C    |   LOW  |   LOW  |
|   0x4D    |   LOW  |  HIGH  |
|   0x4E    |  HIGH  |   LOW  |
|   0x4F    |  HIGH  |  HIGH  |

The datasheet states that the address is configured at power-on, 
so it is probably not possible to 'multiplex' these chips by adjusting the 
address pins during operation, but feedback welcome if you try this.

Furthermore the device has two extended address (so called in the datasheet) pins A2 
and A3 which should by default be connected to GND. 
Since 0.1.1 the library supports these two extra address bits, which enables more 
DAC8574 devices on one I2C bus. See section below.


### Extended address

By using the A2 and A3 pins one can "extend" the address of the device, 
effectively use up to 16 devices on the same I2C bus. 
Please note the A2 and A3 pins are not part of the I2C address but are part (2 bits)
of the internal control byte.

The extended address pins (bits) are not seen by any I2C scanner as these (almost)
always use an 8 bits address. The A2 A3 extended address lines are not used
so this might result in anomalies during an I2C scan as multiple devices might
answer. Feedback about this is welcome.

The A2 and A3 pins can be set with **setExtendedAddress()**, see section below.


### I2C pull ups

To be able to reach 1 MHz (ESP32) the pull ups need to be fairly strong.
Preliminary tests (DAC8571 from same family) indicate that 2K works.


### I2C performance

Output of **DAC8574_performance.ino**

Time in microseconds.  
array == write(array, length)
Assumption all write modi have similar performance.

#### Test Teensy 4.1
 
| Wire clock | write() | read() |
|:----------:|:-------:|:------:|
| 50000 | 387.25 | 497.75 | 
| 100000 | 387.25 | 497.75 | 
| 150000 | 387.25 | 497.75 | 
| 200000 | 387.25 | 497.75 | 
| 250000 | 387.25 | 497.75 | 
| 300000 | 387.25 | 497.75 | 
| 350000 | 387.25 | 497.75 | 
| 400000 | 107.13 | 137.83 | 
| 450000 | 107.13 | 137.83 | 
| 500000 | 107.13 | 137.83 | 
| 550000 | 107.13 | 137.83 | 
| 600000 | 107.13 | 137.83 | 
| 650000 | 107.13 | 137.83 | 
| 700000 | 107.13 | 137.83 | 

#### Test RP2040 (Seeed Xiao 2040)

| Wire clock | write() | read() |
|:----------:|:-------:|:------:|
| 50000 | 800.72 | 1028.23 | 
| 100000 | 405.48 | 518.30 | 
| 150000 | 274.26 | 348.84 | 
| 200000 | 208.11 | 263.41 | 
| 250000 | 168.40 | 212.35 | 
| 300000 | 142.50 | 181.35 | 
| 350000 | 123.73 | 157.87 | 
| 400000 | 109.71 | 140.55 | 
| 450000 | 98.54 | 126.35 | 
| 500000 | 89.44 | 115.50 | 
| 550000 | 82.84 | 106.05 | 
| 600000 | 76.68 | 99.12 | 
| 650000 | 71.63 | 92.22 | 
| 700000 | 67.14 | 87.07 | 

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


## Related

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

Percentage wrappers. Note these might give small rounding errors.

- **void setPercentage(uint8_t channel, float perc)** set 0.00 .. 100.00.
Value is constrained to 0..100
- **float getPercentage(uint8_t channel)** returns 0.0 .. 100.0 from cache.


### Write modi

The DAC8574 can be written in different modi (datasheet page 19).
Not all modi are supported yet, these need investigation and testing.

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
For Arduino UNO this is typical 32 bytes so it allows 14 values.

- **void write(uint8_t channel, uint16_t \* array, uint8_t length)** Writes a buffer with 
max 14 values in one I2C call. 
The last value written will be cached in **lastWrite()**.

Other boards may have larger I2C buffers so the hard coded limit of 14 should 
be changed / removed in the future.


### Extended Address

Please note the A2 and A3 pins are not part of the I2C address but are part (2 bits)
of the internal control byte. See datasheet page 18.

- **bool setExtendedAddress(uint8_t A2A3)** returns true if A2A3 = 0, 1, 2, 3
if A2A3 > 3 the function returns false.
- **uint8_t getExtendedAddress()** returns set value, default 0.

|  A2A3  |   A3  |   A2  |
|:------:|:-----:|:-----:|
|   0    |  LOW  |  LOW  |
|   1    |  LOW  | HIGH  |
|   2    | HIGH  |  LOW  |
|   3    | HIGH  | HIGH  |


### Power Down mode

To investigate: Mixes also with broadcast ==> complex API.

- **bool powerDown(uint8_t pdMode = 0)** default low power.
returns false on failure.
- **bool wakeUp(uint16_t value = 0)** wake up, DAC value set to zero by default.
returns false on failure.

See datasheet table 8, page 27, for details.

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

- adjust limit 14 of write(array) to something more dynamic
  - make user responsible
- add examples

#### Wont

- investigate broadcast support

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


