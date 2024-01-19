
[![Arduino CI](https://github.com/RobTillaart/MAX31855_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX31855_RT/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX31855_RT/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX31855_RT/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX31855_RT/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MAX31855_RT.svg)](https://github.com/RobTillaart/MAX31855_RT/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX31855_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX31855_RT.svg?maxAge=3600)](https://github.com/RobTillaart/MAX31855_RT/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MAX31855.svg)](https://registry.platformio.org/libraries/robtillaart/MAX31855)


# MAX31855_RT

Arduino library for MAX31855 chip for K type thermocouple.

The library has experimental support for other types of thermocouples E, J, N, R, S, T.


## Description

The MAX38155 is a chip to convert the reading of a K-type thermocouple to a temperature.
The working of thermocouples (TC) is based upon Seebeck effect.
Different TC's have a different Seebeck Coefficient (SC) expressed in µV/°C.
See http://www.analog.com/library/analogDialogue/archives/44-10/thermocouple.html

For every type of TC there exist an MAX31855 variant, this library is primary
developed for the K-type sensor. However it has experimental support for all
other types of TC's. See details below.

Library tested with breakout board.

```
         +---------+
     Vin | o       |
     3V3 | o       |
     GND | o     O | Thermocouple
      D0 | o     O | Thermocouple
      CS | o       |
     CLK | o       |
         +---------+

```


#### 0.6.0 Breaking change

Version 0.6.0 introduced a breaking change to improve handling the SPI dependency.
The user has to call **SPI.begin()** or equivalent before calling **MX.begin()**.
Optionally the user can provide parameters to the **SPI.begin(...)**


#### 0.5.0 Breaking change

The version 0.5.0 has breaking changes in the interface. 
The essence is removal of ESP32 specific code from the library. 
This makes it possible to support the ESP32-S3 and other processors in the future. 
Also it makes the library a bit simpler to maintain.

Note the order of the parameters of the software SPI constructor has changed in 0.5.0.


#### Related

- https://github.com/RobTillaart/MAX6675
- https://github.com/RobTillaart/MAX31850
- https://github.com/RobTillaart/MAX31855_RT


## Hardware SPI vs software SPI

Default pin connections. ESP32 can overrule with **setGPIOpins()**.

 |  HW SPI    |  UNO  |  ESP32 VSPI  |  ESP32 HSPI  |  Notes
 |:-----------|:-----:|:------------:|:------------:|:----------|
 |  CLOCKPIN  |   13  |     18       |     14       |
 |  MISO      |   12  |     19       |     12       |
 |  MOSI      |   11  |     23       |     13       |  *not used...*
 |  SELECT    |    4  |      5       |     15       |  *can be others too.*


Performance read() function, timing in us.  (ESP32 @240MHz)

|   mode   |  clock     |  timing UNO  |  timing ESP32  |  Notes
|:---------|-----------:|-------------:|---------------:|:----------|
|  HW SPI  |  32000000  |       ni     |      ~15       |  *less reliable*
|  HW SPI  |  16000000  |      ~68     |      ~16       |
|  HW SPI  |   4000000  |      ~72     |      ~23       |
|  HW SPI  |   1000000  |      ~100    |      ~51       |
|  HW SPI  |    500000  |      ~128    |      ~89       |
|  SW SPI  |  bit bang  |      ~500    |      ~17 (!)   |


## Interface

```cpp
#include "MAX31855.h"
```

#### Constructor

- **MAX31855(uint8_t select, SPIClassRP2040 \* mySPI)** hardware SPI R2040
- **MAX31855(uint8_t select, SPIClass \* mySPI)** hardware SPI other
- **MAX31855(uint8_t select, uint8_t miso, uint8_t clock)** software SPI
- **void begin()** initialize internals


#### Hardware SPI

To be used only if one needs a specific speed.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **void setSWSPIdelay(uint16_t del = 0)** for tuning SW SPI signal quality. Del is the time in micros added per bit. Even numbers keep the duty cycle of the clock around 50%.
- **uint16_t getSWSPIdelay()** get set value in micros.


#### Reading

To make a temperature reading call **read()**.
It returns the status of the read which is a value between 0..7
The function **getStatus()** returns the same status value. 

Table: values returned from **uint8_t read()** and **uint8_t getStatus()**

| value | Description               | Action       |
|:-----:|:--------------------------|:-------------|
|    0  | OK                        |              |
|    1  | Thermocouple open circuit | check wiring |
|    2  | Thermocouple short to GND | check wiring |
|    4  | Thermocouple short to VCC | check wiring |
|    7  | Generic error             |              |
|  128  | No read done yet          | check wiring |
|  129  | No communication          | check wiring |

There are six functions to check the individual error conditions mentioned above.
These make it easier to check them.

- **bool openCircuit()**
- **bool shortToGND()**
- **bool shortToVCC()**
- **bool genericError()**
- **bool noRead()**
- **bool noCommunication()**

After a **uint8_t read()** you can get the temperature with **float getTemperature()** 
and **float getInternal()** for the internal temperature of the chip / board itself.
Normally these are (almost) equal.

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

To have proper working of the MAX31855 board, you need to add a pull-up resistor 
(e.g. 4K7 - 1K depending on length of the wires) between the MISO pin (from constructor call) 
and the VCC (5Volt). 
This improves the signal quality and will allow you to detect if there is proper communication 
with the board. Without pull-up one might get random noise that could look like real data.

**Note:** the MISO pin can be different from each board, please refer to your board datasheet.

If the MAX31855 board is not connected **tc.read()** will return **STATUS_NO_COMMUNICATION**.

You can verify this by **tc.getRawData()** which will give 32 HIGH bits or 0xFFFFFFFF).

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
  if (thermocouple.getRawData() == 0xFFFFFFFF)
  {
    Serial.println("NO COMMUNICATION");
  }
```


## Operation

See examples


## Experimental part (to be tested)

**NOTE:** 
The support for other thermocouples is experimental **use at your own risk**.


The MAX31855 is designed for K type sensors. It essentially measures a 
voltage difference and converts this voltage using the Seebeck Coefficient (SC) 
to the temperature. As the SC is linear in its nature it is possible
to replace the K-type TC with one of the other types of TC.


Datasheet Table 1, page 8  SC = Seebeck Coefficient

| Sensor type | SC in µV/°C | Temp Range in °C | Material                  |
|:-----------:|:------------|:-----------------|:--------------------------|
|   E_TC      |    76.373   |   -270 to +1000  | Constantan Chromel        |
|   J_TC      |    57.953   |   -210 to +1200  | Constantan Iron           |
|   K_TC      |    41.276   |   -270 to +1372  | Alumel Chromel            |
|   N_TC      |    36.256   |   -270 to +1300  | Nisil Nicrosil            |
|   R_TC      |    10.506   |    -50 to +1768  | Platinum Platinum/Rhodium |
|   S_TC      |     9.587   |    +50 to +1768  | Platinum Platinum/Rhodium |
|   T_TC      |    52.18    |   -270 to +400   | Constantan Copper         |


The core formula to calculate the temperature is  (Datasheet page 8)
```
Vout = (41.276µV/°C) x (Temp_R - Temp_internal)
```
As we know the internal temperature and the returned temperature from the sensor
the library can calculate the Vout measured (as the chip assumes that a K-type 
thermocouple is connected. 
Having that Vout we can redo the math for the actual thermocouple type and
calculate the real temperature. 

The library has two functions **setSeebeckCoefficient(float factor)** and 
**float getSeebeckCoefficient()**
to get/set the Seebeck Coefficient (== thermocouple) to be used. 
One can adjust the values to improve the accuracy of the temperature read. 

The **float getTemperature()** has implemented this algorithm, however as long
as one does not set the Seebeck Coefficient it will use the K_TC as default.


## Future

#### Must

#### Should

- investigate other TC's 

#### Could

- move code to .cpp

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

