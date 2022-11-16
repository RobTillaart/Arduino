
[![Arduino CI](https://github.com/RobTillaart/MAX31850/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MAX31850/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MAX14661/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MAX31850/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MAX14661/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MAX31850/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MAX31850.svg?maxAge=3600)](https://github.com/RobTillaart/MAX31850/releases)

# MAX31850

Arduino library for the MAX31850 / MAX31851 thermocouple sensor.

## Description

**WARNING EXPERIMENTAL** needs more testing (no hardware yet).
(feedback welcome)

his MAX31850 library is not a full featured library for the MAX31850 family.

The MAX31850/1 is a Cold-Junction Compensated, 1-Wire Thermocouple-to-Digital Converter.

The MAX31850/1 supports K-, J-, N-, T-, S-, R-, and E-type thermocouples. (to be tested).

The library supports both the MAX31850 and MAX31851 but is limited to one sensor per pin.
The only feature the class supports is the asynchronous reading of the temperature.

This allowed the class to be both minimal in size and non-blocking. 
In fact the class has no support for a synchronous read in one call. 
This choice will teach people how to work in a non-blocking way from the start.

Finally this library will probably make it easier to use a MAX31850 with processing 
boards or IC's with small memory footprint.


## Hardware connection

```
//  PROCESSOR        MAX31850       THERMOCOUPLE
//              +---------------+
//   GND   1    | o           o |   T+
//   DATA  2    | o             |
//   VCC   3    | o           o |   T-
//              |               |
//              |     oooo      |
//              +---------------+
//               4 address pins.
```

This library supports only one MAX31850 per Arduino/ MCU pin.


### Pull up resistor

Connect a pull-up resistor 4.7 KOhm between pin3 and pin2. 
When the wires are longer this resistor needs to be smaller. 

An **indicative** table for pull up resistors, (E12 series), to get started.

Note: thicker wires require smaller resistors (typically 1 step in E12 series) 

| Length        | - 5.0 Volt  | - 3.3 Volt |
|--------------:|------------:|----------:|
| 10cm (4")     | 10K0  | 6K8 |
| 20cm (8")     |  8K2  | 4K7 |
| 50cm (20")    |  4K7  | 3K3 | 
| 100cm (3'4")  |  3K3  | 2K2 | 
| 200cm (6'8")  |  2K2  | 1K0 | 
| 500cm (16'8") |  1K0  | \*  |  
| longer        |    *  | \*  |

\* = no info, smaller 


## Interface

#### Constructor

- **explicit MAX31850(OneWire \* oneWire)** constructor.
- **bool begin(void)** initialize the library.
Returns true if addresses are found.
- **bool getAddress(uint8_t \* buffer)** get the address if found.

#### Read the sensor
- **void requestTemperatures(void)** idem.
- **bool isConversionComplete(void)** idem.
- **float read(void)** read the data from the sensor.
Returns the temperature of the thermoCouple as this is most often needed.
- **float getTempTC(void)** returns temperature of the ThermoCouple.
One must call **read()** to get new measurements.
- **float getTempInternal(void)** returns internal temperature.

#### other
- **uint8_t getAddressPins()** ??
- **uint8_t getErrorCode()**


## Types of thermocouples

The MAX31850 comes in MAX31850E.. MAX31850T types reflecting the version of TC to use.


| Sensor type | SC in µV/°C | Temp Range in °C | Material                  |  notes     |
|:-----------:|:------------|:-----------------|:--------------------------|:-----------|
|   E_TC      |    76.373   |   -270 to +1000  | Constantan Chromel        |
|   J_TC      |    57.953   |   -210 to +1200  | Constantan Iron           |
|   K_TC      |    41.276   |   -270 to +1372  | Alumel Chromel            | most used  |
|   N_TC      |    36.256   |   -270 to +1300  | Nisil Nicrosil            |
|   R_TC      |    10.506   |    -50 to +1768  | Platinum Platinum/Rhodium |
|   S_TC      |     9.587   |    +50 to +1768  | Platinum Platinum/Rhodium |
|   T_TC      |    52.18    |   -270 to +400   | Constantan Copper         |

(MAX31851 idem)


## Error codes

|  name                     |  value  |
|:--------------------------|:-------:|
| MAX31850_OK               |    0    |
| MAX31850_ERR_SHORT_OPEN   |    1    |
| MAX31850_ERR_SHORT_GND    |    2    |
| MAX31850_ERR_SHORT_VDD    |    4    |


## Future

#### must
- improve documentation
- get hardware to test (sponsors welcome)
- test on different platforms


#### should
- investigate different thermocouples 
- test with different platforms


#### could
- expand to multi sensor per pin. 
  - first get one sensor working


