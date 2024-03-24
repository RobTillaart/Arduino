# Change Log DHTNEW

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.20] - 2024-03-24
- fix #95, units of T & H
- update GitHub actions
- refactor **setType()** map invalid types to 0
- update readme.md
- update unit test (minor)
- minor edits


## [0.4.19] - 2023-10-25
- update readme.md

## [0.4.18] - 2023-01-09
- update license to 2023
- update GitHub actions
- fix #89, add experimental support for AM2320, AM2321, AM2322.
- update readme.md.

## [0.4.17] - 2022-11-05
- fix #86, define constants explicit as float.

## [0.4.16] - 2022-10-17
- Fix #84 correct the reading of type 70 for Sonoff Si7021.
- fix keywords.txt

## [0.4.15] - 2022-10-13
- Fix #81, recognize DHT22 as type 70. Add minimal wakeup delay.

## [0.4.14] - 2022-10-13
- Fix #79, experimental support for Si7021.
- Add RP2040 pico in build-CI
- Add CHANGELOG.md

## [0.4.13] - 2022-07-05
- Fix #76, disable interrupts for ESP32.

## [0.4.12] - 2022-01-31
- Fix #72, delayMicroseconds() for wakeUp

## [0.4.11] - 2021-12-16
- update library.json, license, minor edits (clean up),
- add constants to unit tests

## [0.4.10] - 2021-11-18
- update build-CI - compilation test on M4 and ESP32 of examples
- update readme.md, badges, typos, reorganizing
- added note: MKR1010 Wifi support - setDisableIRQ(false)
- minor edits in examples
- changed TIMEOUT_C to 90us (after endurance test on MKR1010 Wifi)

## [0.4.9] - 2021-06-13
- add optional flag DHTLIB_VALUE_OUT_OF_RANGE

## [0.4.8] - 2021-05-27
- fixes to improve Arduino-lint

## [0.4.7] - 2021-04-09
- fix #60 negative temperatures below -25.5°C + readme.md

## [0.4.6] - 2021-04-09
- fix #57 negative temperatures DHT22
- Do not use 0.4.5 and 0.4.4 as these are incorrect for negative temperature.

## [0.4.5] - 2021-02-14
- fix -0°C encoding of DHT22  ( bit pattern 0x8000 )

## [0.4.4] - 2021-02-01
- fix negative temperatures DHT22 (again)

## [0.4.3] - 2021-01-13
- add reset(), add lastRead()

## [0.4.2] - 2020-12-15
- fix negative temperatures

## [0.4.1] - 2020-11-11
- getType() attempts to detect sensor type
- add Arduino -CI + readme

## [0.4.0] - 2020-11-10
- added DHTLIB_WAITING_FOR_READ as return value of read (minor break of interface)

----

## [0.3.4] - 2020-09-23
- Added **waitFor(state, timeout)** to follow timing from datasheet.
- Restored disableIRQ flag as problems occurred on AVR.
  The default of this flag on AVR is false so interrupts are allowed.
- This need some investigation
- Fix wake up timing for DHT11 as it does not behave according datasheet.
- fix wakeupDelay bug in setType();

## [0.3.3] - 2020-08-18
- fix #29, create explicit delay between pulling line HIGH and
  waiting for LOW in handshake to trigger the sensor.
- On fast ESP32 this fails because the capacity / voltage of the long wire
- cannot rise fast enough to be read back as HIGH.

## [0.3.2] - 2020-07-17
- fix #23 added get/setSuppressError(); overridable DHTLIB_INVALID_VALUE

## [0.3.1] - 2020-07-08
- added powerUp() powerDown();

## [0.3.0] - 2020-06-12
- added getReadDelay & setReadDelay to tune reading interval
- removed get/setDisableIRQ; adjusted wakeup timing; refactor

----

## [0.2.2] - 2020-06-08
- added ERROR_SENSOR_NOT_READY and differentiate timeout errors

## [0.2.1] - 2020-05-27
- Fix #11 - Adjust bit timing threshold

## [0.2.0] - 2020-05-02
- made temperature and humidity private (Kudo's to Mr-HaleYa),

----

## [0.1.7] - 2020-05-01
- prevent premature read; add waitForReading flag (Kudo's to Mr-HaleYa),

## [0.1.6] - 2020-04-09
- #pragma once, readme.md, own repo

## [0.1.5] - 2019-01-20
- fix negative temperature DHT22 - issue #120

## [0.1.4] - 2018-04-03
- add get-/setDisableIRQ(bool b)

## [0.1.3] - 2018-01-08
- removed begin() + moved detection to read() function

## [0.1.2] - 2018-01-08
- improved begin() + refactor()

## [0.1.1] - 2017-07-29
- add begin() to determine type once and for all instead of every call + refactor

## [0.1.0] - 2017-07-24
- initial version based upon DHTStable


