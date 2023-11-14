# Change Log MS5611

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] - 2023-11-14
- simplify begin()
- refactor constructor
- update readme.md
- update examples
- add ESP32 and RP2040 minimal example.
- update keywords.txt

----

## [0.3.9] - 2022-10-26
- add RP2040 support to build-CI
- add CHANGELOG.md
- add getManufacturer()
- add getSerialCode()
- add parameter mathMode to **reset()** to switch between pressure math.
  - see readme for details.

## [0.3.8] - 2022-01-24
- reset() returns bool indicating successful ROM read
- get/setCompensation() to enable/disable compensation.

## [0.3.7] - 2022-01-22  
- fix #26 added getPromHash() == **getDeviceID()**
  - add getDeviceID(), to provide a sort of unique device ID (experimental) based 
upon uniqueness of the factory calibration values.
- fix #24 default all examples address 0x77
- default address for constructor, can be set as define on the command line.
MS5611_DEFAULT_ADDRESS.

## [0.3.6] - 2022-01-15 
- add setOffset functions; minor refactor;
- The timing for convert is adjusted from TYPICAL to MAX 
  - datasheet page 3. - see issue #23
- The **write(0)** in **isConnected()** is made conditional explicit for the NANO 33 BLE.

## [0.3.5] - 2022-01-13
- fix isConnected() for NANO 33 BLE

## [0.3.4] - 2021-12-29
- fix #16 compilation for MBED

## [0.3.3] - 2021-12-25
- Update oversampling timings to reduce time spent waiting

## [0.3.2] - 2021-12-24
- add get/set oversampling, read() (thanks to LyricPants66133)

## [0.3.1] - 2021-12-21
- update library.json, readme, license, minor edits

## [0.3.0] - 2021-01-27
- fix #9 math error (thanks to Emiel Steerneman)
  - previous versions ==>  **obsolete**.
  - temperature is a float expressed in degrees Celsius.
  - pressure is a float expressed in mBar.
- add Wire1..WireN support (e.g. teensy)
- changed getTemperature() and getPressure()
- add reset()

----

## [0.2.2] - 2021-01-01
- add Arduino-CI + unit tests + isConnected()

## [0.2.1] - 2020-06-28
- fix #1 min macro compile error

## [0.2.0] - 2020-06-21
- refactor; #pragma once;

----

## [0.1.8] - 2018-07-01
- fix #109 incorrect constants (thanks to flauth)

## [0.1.7] = 2017-07-26
- revert double to float (issue 33)

## [0.1.6] - 2015-07-12
- refactor

## [0.1.05] - 2015-03-07
- moved 6 float multiplies to init() ==> adds ~70 bytes !!!
- moved the MS5611_LIB_VERSION to PROGMEM

## [0.1.04] - 2014-10-19
- changed float to double (for platforms which support it)
- changed divisions in multiplications
- fixed uint32_t readADC()
- reduced size of C array by 1 float
- added second order temperature compensation

## [0.1.03] - 2014-10-17
- changed math to float (test version)

## [0.1.02] - 2014-10-17
- fixed bug return value read()
- fixed bug #bits D2
- added MS5611_READ_OK
- added inline getters for temp & pres & lastResult.
- adjusted delay's based on datasheet
- merged convert functions
- fixed offset in readProm()

## [0.1.01] - 2014-10-16
- small refactoring

## [0.1.00]
- added temperature and Pressure code

## [0.0.00] - 2014-10-15
- initial version