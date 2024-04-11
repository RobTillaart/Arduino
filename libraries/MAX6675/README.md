
[![Arduino CI](https://github.com/RobTillaart/MAX6675/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX6675/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX6675/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX6675/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX6675/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX6675.svg)](https://github.com/RobTillaart/MAX6675/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX6675/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX6675.svg?maxAge=3600)](https://github.com/RobTillaart/MAX6675/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX6675.svg)](https://registry.platformio.org/libraries/robtillaart/MAX6675)


# MAX6675

Max6675 is an Arduino library for MAX6675 chip with a K type thermocouple. 

The library is based upon (stripped and adapted version of) the https://github.com/RobTillaart/MAX31855_RT library.

Currently the library is experimental, so use with care.

Hardware has finally arrived (April 2022) and I had time to do my first round of tests with an UNO @ 16 MHz. 
The library works and it reads temperatures well, both with HW SPI and SW SPI. 


## Description

The MAX6675 is a chip to convert the reading of a K-type thermocouple to a temperature. 
The MAX6675 only supports positive degrees Celsius.

The values are read with an precision of **0.25°C.** 
Typical noise seen during usage are **± 0.5°C**, so using a low pass filter on the temperature might be a good idea.

The working of thermocouples (TC) is based upon Seebeck effect.
Different TC's have a different Seebeck Coefficient (SC) expressed in µV/°C.
See http://www.analog.com/library/analogDialogue/archives/44-10/thermocouple.html


#### Breakout

The library is tested with a breakout board with following pins:

```
             +---------------------+
             |          signal out |  -->  MISO
             | -       chip select |  <--  SELECT
    TC here  |               clock |  <--  CLOCK    processor side
             | +               VCC |  ---  VCC
             |                 GND |  ---  GND
             +---------------------+
```


#### 0.3.0 Breaking change

Version 0.3.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **AD.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.2.0 Breaking change

The version 0.2.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.

Note the order of the parameters of the software SPI constructor has changed in 0.2.0.


#### Related

- https://github.com/RobTillaart/MAX6675
- https://github.com/RobTillaart/MAX31850
- https://github.com/RobTillaart/MAX31855_RT


## Hardware SPI vs software SPI


#### Pins

Default pin connections.

 | HW SPI   |  UNO  |  ESP32 VSPI |  ESP32 HSPI | Notes
 |:---------|:-----:|:-----------:|:-----------:|:----------|
 | CLOCK    |  13   |   18        |   14        |
 | MISO     |  12   |   19        |   12        |
 | MOSI     |  11   |   23        |   13        |  *not used...*
 | SELECT   | eg. 4 |    5        |   15        |  *can be others too.*


#### Performance 

Performance read() function, timing in us.  
- UNO @ 16 MHz
- TODO ESP32 @ 240 MHz

| mode   |  clock   | timing UNO | timing ESP32 | Notes
|:-------|---------:|-----------:|-------------:|:----------|
| HW SPI |  4000000 |    36      |              | highest supported.
| HW SPI |  3500000 |    40      |              |
| HW SPI |  3000000 |    40      |              |
| HW SPI |  2500000 |    40      |              |
| HW SPI |  2000000 |    40-44   |              |
| HW SPI |  1500000 |    48      |              |
| HW SPI |  1000000 |    48-52   |              |
| HW SPI |   500000 |    64-68   |              |
| SW SPI | bit bang |    276     |              |

Note the UNO micros() has a 4 us precision, but it is clear that
4 Mb is not even twice the speed of 0.5 Mb.  
Tested with **MAX6675_test_HWSPI.ino**


## Interface

```cpp
#include "MAX6675.h"
```

#### Constructor

- **MAX6675(uint8_t select, SPIClassRP2040 \* mySPI)** hardware SPI R2040
- **MAX6675(uint8_t select, SPIClass \* mySPI)** hardware SPI other
- **MAX6675(uint8_t select, uint8_t miso, uint8_t clock)** software SPI
- **void begin()** initialize internals


#### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **void setSWSPIdelay(uint16_t del = 0)** for tuning SW SPI signal quality. 
Del is the time in micros added per bit. Even numbers keep the duty cycle of the clock around 50%.
- **uint16_t getSWSPIdelay()** get set value in micros.


#### Reading

To make a temperature reading call **read()**.
It returns the status of the read which is a value between 0..7
The function **getStatus()** returns the same status value. 

Table: values returned from **uint8_t read()** and **uint8_t getStatus()**

Note: this list is a subset of MAX31855 errors.

| value | Description               | Action       |
|:-----:|:--------------------------|:-------------|
|    0  | OK                        |              |
|    4  | Thermocouple short to VCC | check wiring |
|  128  | No read done yet          | check wiring |
|  129  | No communication          | check wiring |


After a **uint8_t read()** you can get the temperature with **float getTemperature()**.

Repeated calls to **getTemperature()** will give the same value until a new **read()**.
The latter fetches a new value from the sensor. Note that if the **read()** fails
the value of **getTemperature()** can become incorrect. So it is important to check 
the return value of **read()**.


#### Offset

The library supports a fixed offset to calibrate the thermocouple.
For this the functions **float getOffset()** and **void setOffset(float offset)** are available.
This offset is "added" in the **getTemperature()** function.

Notes
- the offset can be positive or negative.
- the offset used is a float, so decimals can be used.
A typical usage is to call **setOffset(273.15)** to get ° Kelvin.
- the offset can cause negative temperatures.


#### Delta analysis

As the **tc** object holds its last known temperature it is easy to determine the delta 
with the last known temperature, e.g. for trend analysis.

```cpp
  float last = tc.getTemperature();
  int state  = tc.read();
  if (state == STATUS_OK)
  {
    float new  = tc.getTemperature();
    float delta = new - last;
    // process data
  }
```


#### Last time read

The **tc** object keeps track of the last time **read()** is called in the function **uint32_t lastRead()**.
The time is tracked in **millis()**. This makes it easy to read the sensor at certain intervals.

```cpp
if (millis() - tc.lastRead() >= interval)
{
  int state = tc.read();
  if (state == STATUS_OK)
  {
    float new = tc.getTemperature();
    // process read value.
  }
  else
  {
    // handle error
  }
}
```


#### GetRawData 

The function **uint32_t getRawData()** allows you to get all the 32 bits raw data from the board, 
after the standard **uint8_t tc.read()** call.

Example code can be found in the examples folder.

```cpp
  int state = thermocouple.read();              
  uint32_t value = thermocouple.getRawData();  // Read the raw Data value from the module
```

This allows one to compact the measurement e.g. for storage or sending over a network.


## Pull Up Resistor 

To have proper working of the MAX6675 board, you need to add a pull-up resistor 
(e.g. 4K7 - 1K depending on wire length) between the MISO pin (from constructor call) and the 
VCC (5 Volt). This improves the signal quality and will allow you to detect if there is
proper communication with the board. Without pull-up one might get random noise that could 
look like real data.

**Note:** the MISO pin can be different from each board, please refer to your board datasheet.

If the MAX6675 board is not connected **tc.read()** will return **STATUS_NO_COMMUNICATION**.

You can verify this by **tc.getRawData()** which will give 16 HIGH bits or 0xFFFF).

You can use a simple code to detect connection error board:

```cpp
  uint8_t status = thermocouple.read();
  if (status == STATUS_NO_COMMUNICATION)
  {
    Serial.println("NO COMMUNICATION");
  }
```

or

```cpp
  uint8_t status = thermocouple.read();
  if (thermocouple.getRawData() == 0xFFFF)
  {
    Serial.println("NO COMMUNICATION");
  }
```


## Operation

See examples


## Future

#### Must

- update and verify documentation (as it is copied from MAX31855 lib)

#### Should

- keep interface in sync with MAX31855 if possible.

#### Could

- create example to distinguish between MAX6675 and MAX31855
  - https://github.com/RobTillaart/MAX6675/issues/5

#### Wont
 

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

