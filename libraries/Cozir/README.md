
[![Arduino CI](https://github.com/RobTillaart/Cozir/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Cozir/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Cozir.svg?maxAge=3600)](https://github.com/RobTillaart/Cozir/releases)


# Cozir

Arduino library for COZIR range of temperature, humidity and CO2 sensors.


## Description

The Cozir library is **experimental** as I do not have a sensor to test the library.
The polling mode as used in the examples seems to work quite well.

#### Notes
- the **CozirDemoHWSerial.ino** example needs to run on a MEGA or a Teensy, 
at least a board with more than one Serial port. 
- Read the datasheet before using this library. It helps to understand the working of the Cozir sensor.


## Interface

Read the datasheet (again)


### Constructor and initialisation

- **COZIR(Stream \*)** constructor
- **void init()** sets operatingMode to CZR_POLLING
- **void SetOperatingMode(uint8_t mode)** set the operating mode either to **CZR_COMMAND**, **CZR_POLLING** or  **CZR_STREAMING**


### Core 
- **float Celsius()** idem
- **float Fahrenheit()** idem, wrapper around **Celsius()**
- **float Humidity()** idem
- **float Light()** idem
- **uint32_t CO2() ** idem.
- **uint16_t getPPMFactor()** returns 1, 10, 100 See Page 14.


### Calibration

Read datasheet before use

- **uint16_t FineTuneZeroPoint(uint16_t v1, uint16_t v2)**
- **uint16_t CalibrateFreshAir()**
- **uint16_t CalibrateNitrogen()**
- **uint16_t CalibrateKnownGas(uint16_t value)**


#### Calibration NOT Recommended 

Following 3 functions are **NOT RECOMMENDED** by the datasheet. 
Feel free to uncomment but use at your own risk. Read datasheet before use.

- **uint16_t CalibrateManual(uint16_t value)**
- **uint16_t SetSpanCalibrate(uint16_t value)**
- **uint16_t GetSpanCalibrate()**


### Digifilter

use with care, read datasheet before use

| value | meaning |
|:-----:|:--------|
|   0   | Special, see datasheet page ... |
|   1   | fast, but can be noisy |
|  32   | default, good average  |
| 255   | slow, max smoothed     |

- **void SetDigiFilter(uint8_t value)**
- **uint8_t  GetDigiFilter()**


### Streaming MODE

Warning: Not tested ,

- **void SetOutputFields(uint16_t fields)** Sets the fields in the output stream.
- **void ClrOutputFields()** clears all the fields.
- **void GetRecentFields()** After a call to GetRecentFields() you must read the serial port yourself as the internal buffer of this Class cannot handle the possible large output. It can be over 100 bytes long lines!

The fields must be set as a bit mask, the order of the fields in the output is undetermined. So parse carefully.

| Field             | Value  | Notes |
|:------------------|:-------|:------|
| CZR_LIGHT         | 0x2000 |       |
| CZR_HUMIDITY      | 0x1000 |       |
| CZR_FILTLED       | 0x0800 |       |
| CZR_RAWLED        | 0x0400 |       |
| CZR_MAXLED        | 0x0200 |       |
| CZR_ZEROPOINT     | 0x0100 |       |
| CZR_RAWTEMP       | 0x0080 |       |
| CZR_FILTTEMP      | 0x0040 |       |
| CZR_FILTLEDSIGNAL | 0x0020 |       |
| CZR_RAWLEDSIGNAL  | 0x0010 |       |
| CZR_SENSTEMP      | 0x0008 |       |
| CZR_FILTCO2       | 0x0004 |       |
| CZR_RAWCO2        | 0x0002 |       |
| CZR_NONE          | 0x0001 | reset |
| CZR_HTC           | 0x1082 | shortcut |
| CZR_ALL           | 0x3FFE | debug    |


### EEPROM

Read datasheet Page 11-12 about the addresses and their meaning.
Use with care.

- **void SetEEPROM(uint8_t address, uint8_t value)**
- **uint8_t  GetEEPROM(uint8_t address)**


| Name     | Address | Default | Notes |
|:---------|:-------:|:-------:|:------|
| AHHI     | 0x00    |         | reserved |
| ANLO     | 0x01    |         | reserved |
| ANSOURCE | 0x02    |         | reserved |
| ACINITHI | 0x03    | 87      |        |
| ACINITLO | 0x04    | 192     |        |
| ACHI     | 0x05    | 94      |        |
| ACLO     | 0x06    | 128     |        |
| ACONOFF  | 0x07    | 0       |        |
| ACPPMHI  | 0x08    | 1       |        |
| ACPPMLO  | 0x09    | 194     |        |
| AMBHI    | 0x0A    | 1       |        |
| AMBLO    | 0x0B    | 194     |        |
| BCHI     | 0x0C    | 0       |        |
| BCLO     | 0x0D    | 8       |        |


### Misc

- **void GetVersionSerial()** requests version over serial. The user should read (and parse) the serial output as it can become large. Also the user must  reset the operating mode either to **CZR_POLLING** or  **CZR_STREAMING**
- **void GetConfiguration()** requests configuration over serial. The user should read (and parse) the serial output as it can become large. Also the user must  reset the operating mode either to **CZR_POLLING** or  **CZR_STREAMING**


## Operation

See examples.


## Test sensor

People who have a spare sensor for me, or are willing to run tests, please contact me.
