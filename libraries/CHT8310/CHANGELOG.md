# Change Log CHT8310

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.0] - 2024-02-16
- redo humidity, Kudos to YouCanNotBeSerious for testing!
- disabled conversion delay handling for now
- add **uint16_t getConfiguration()** 
- add **void setConfiguration(uint16_t mask)**
- add several examples
- update readme.md
- minor edits.


## [0.1.1] - 2024-02-14 (not released)
- handle overflow bit in humidity
- add **ALERT** temperature and humidity limit functions
- add **getStatusRegister()**
- add **softwareReset()**
- add **setConvertRate(uint8_t rate = 4)** 
- add **getConvertRate()**
- add **oneShotConversion()**
- update readme.md
- update keywords.txt
- minor edits

## [0.1.0] - 2024-02-04
- initial version.

