# Change Log DS18B20_INT

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.3] - 2024-06-27
- add connectCheck parameter to getTempC()
- update readme.md
- minor edits

## [0.3.2] - 2024-01-03
- fix examples
- minor edits

## [0.3.1] - 2023-10-19
- update readme.md

## [0.3.0] - 2023-03-05
- fix #15 infinite loop
- move sources to src folder to comply with PlatformIO dependency system. 
- make oneWire dependency explicit in library.properties
- refactor resolution handling
- update readme.md
- fix changelog.md

----

## [0.2.2] - 2023-02-03
- improve disconnect detection
- add **isConnected(retries)**
- change signature **bool setResolution(bits)** to see if device is still available.
- update GitHub actions
- update license 2023
- add example DS18B20_performance.ino (start not complete)
- add example DS18B20_two_sensor.ino
- add example oneWireSearch.ino
- update readme.md

## [0.2.1] - 2022-11-02
- add changelog.md
- add rp2040 to build-CI

## [0.2.0] - 2022-06-23
- fix #10 getTempCentiC() (thanks negroKiordi)
- fix reading sensor

----

## [0.1.7] - 2021-12-17
- update library.json
- update license
- minor edits

## [0.1.6] - 2021-10-03
- add dependency
- fix build-CI

## [0.1.5] - 2021-06-16
- add retries parameter to begin()

## [0.1.4] - 2021-05-26
- add OneWire.reset() to begin()


## [0.1.3] - 2020-12-20
- add Arduino-CI + unit test

## [0.1.2] - 2020-08-05
- refactor
- sync with DS18B20

## [0.1.1] - 2019-??-??

## [0.1.0] - 2017-07-25
- initial version



