
[![Arduino CI](https://github.com/RobTillaart/MAX31855_RT/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX31855_RT/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX31855_RT.svg?maxAge=3600)](https://github.com/RobTillaart/MAX31855_RT/releases)

# MAX31855_RT

Arduino library for MAX31855 chip for K type thermocouple


## Description

The MAX38155 is a chip to convert the reading of a K-type thermocouple to a temperature.
The working of thermocouples (TC) is based upon Seebeck effect.
Different TC's have a different Seebeck Coefficient (SC) expressed in µV/°C.
See http://www.analog.com/library/analogDialogue/archives/44-10/thermocouple.html

For every type of TC there exist an MAX31855 variant, this library is primary
developed for the K-type sensor. However it has experimental support for all
other types of TC's. See details below.

Library tested with breakout board

```
     +---------+
 Vin | o       |
 3Vo | o       |
 GND | o     O | Thermocouple
  D0 | o     O | Thermocouple
  CS | o       |
 CLK | o       |
     +---------+

```

## Hardware SPI vs software SPI

Default pin connections (ESP32 has more options)

 | HW SPI   |  UNO  |  ESP32  |
 |:---------|:-----:|:-------:|
 | CLOCKPIN |   13  |   18    |
 | MISO     |   12  |   19    |
 | MOSI     |   11  |   23    |

Performance read() function, timing in us.

| mode | clock | timng UNO |
|:----|----:|----:|
| HWSPI | 16000000 | ~68  |
| HWSPI |  4000000 | ~72  |
| HWSPI |  1000000 | ~100 |
| HWSPI |   500000 | ~128 |
| SWSPI | bitbang  | ~500 |



## Interface

To make a temperature reading call **tc.read()**.
It returns the status of the read which is a value between 0..7
The function **getStatus()** returns the same status value. 

Table: values returned from **read()** and **getStatus()**

| value | Description | Action |
|:----:|:----|:----|
| 0 | OK | - |
| 1 | Thermocouple open circuit | check wiring |
| 2 | Thermocouple short to GND | check wiring |
| 4 | Thermocouple short to VCC | check wiring |
| 7 | Generic error | |
| 128 | No read done yet | check wiring |
| 129 | No communication | check wiring |

There are six functions to check the individual error conditions mentioned above.
These make it easier to check them.

- **openCircuit()**
- **shortToGND()**
- **shortToVCC()**
- **genericError()**
- **noRead()**
- **noCommunication()**

After a **tc.read()** you can get the temperature with **tc.getTemperature()** 
and **tc.getInternal()** for the interrnal temperature of the chip / board itself.

Repeated calls to **tc.getTemperature()** will give the same value until a new **tc.read()**.
The latter fetches a new value from the sensor. Note that if the **tc.read()** fails
the value of **tc.getTemperature()** can become incorrect. 

The library supports a fixed offset to callibrate the thermocouple.
For this the functions **tc.getOffset()** and **tc.setOffset(offset)** are available.
This offset is included in the **tc.getTemperature()** function.

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

The **tc** object keeps track of the last time **tc.read()** is called in the function **tc.lastRead()**.
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


## GetRawData 

The function **tc.getRawData()** allows you to get all the 32 bits raw data from the board, 
after the standard **tc.read()** call.

Example code can be found in the examples folder.

```cpp
  int state = thermocouple.read();              
  uint32_t value = thermocouple.getRawData();  // Read the raw Data value from the module
```


## Pull Up Resistor 

To have proper working of the MAX31855 board, you need to add a pull-up resistor 
(e.g. 4K7 - 1K depending on wirelength) between the MISO pin (from constructor call) and the 
VCC (5Volt). This improves the signal quality and will allow you to detect if there is
proper communication with the board. WIthout pull-up one might get random noise that could 
look like real data.

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
to the temperature. As the SC is lineair in its nature it is possible
to replace the K-type TC with one of the other types of TC.

Datasheet Table 1, page 8

| Sensor type | Seebeck Coefficient (µV/°C) | Temp Range (°C) | Material |
|:----:|:----|:----|:----|
| E_TC | 76.373 | -270 to +1000 | Constantan Chromel |
| J_TC | 57.953 | -210 to +1200 | Constantan Iron |
| K_TC | 41.276 | -270 to +1372 | Alumel Chromel |
| N_TC | 36.256 | -270 to +1300 | Nisil Nicrosil |
| R_TC | 10.506 | -50 to +1768 | Platinum Platinum/Rhodium |
| S_TC | 9.587  | +50 to +1768 | Platinum Platinum/Rhodium |
| T_TC | 52.18  | -270 to +400 | Constantan Copper |

The core formula to calculate the temperature is  (Datasheet page 8)
```
Vout = (41.276µV/°C) x (Temp_R - Temp_internal)
```
As we know the internal temperature and the returned temperature from the sensor
the library can calculate the Vout measured (as the chip assumes that a K-type 
thermocouple is connected. 
Having that Vout we can redo the math for the actual thermocouple type and
calculate the real temperature. 

The library has two functions **tc.setSeebeckCoefficient(factor)** and 
**tc.getSeebeckCoefficient()**
to get/set the Seebeck Coefficient (== thermocouple) to be used. 
One can adjust the values to improve the accuracy of the temperature read. 

The **tc.getTemperature()** has implemented this algorithm, however as long
as one does not set the Seebeck Coefficient it will use the K_TC as default.

