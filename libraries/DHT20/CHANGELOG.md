# Change Log DHT20

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.0] - 2022-10-30
- add changelog.md
- add rp2040 to build-CI
- add workaround for #8 to readme.md
- fix requestFrom() ambiguity
- fix #8 - embed **resetSensor()** into **read()**.
  This makes reads slightly slower.
- update readme.md

----

## [0.1.4] - 2022-09-18
- add resetSensor() code.
- add comments in .h file
- add examples
- stabilize readStatus()
- update readme.md

## [0.1.3] - 2022-09-17
- add wrapper status functions
- improve performance read()
- refactor, update readme.md

## [0.1.2] - 2022-09-16
- fix #4 DHT20_ERROR_BYTES_ALL_ZERO error condition.
- fix keywords
- add readStatus()  fix _readStatus()
- add setWireTimeout(250000, true);  //  in comments

## [0.1.1] - 2022-09-10
- add hardware schema to readme.md.
- fix async interface (first version)

## [0.1.0] - 2022-01-11
- initial version (based upon DHT20 datasheet)

