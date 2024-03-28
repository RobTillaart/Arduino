# Change Log KT0803

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-03-27
- fix #5, getChannel()
- fix KT0803K setChannel()
- fix readData()
- add several KT0803K specific functions (experimental)
  - bool setMono()
  - bool setStereo()
  - bool isStereo()
  - bool setBass(uint8_t bass)
  - uint8_t getBass()
  - bool powerOK()
  - bool silenceDetected()
- update GitHub actions
- update readme.md
- update keywords.txt
- minor edits

----

## [0.2.0] - 2024-03-09
- Fix #2 frequency to channel formula
- add derived **class KT0803K**
- add examples
- add parameter checks functions.
- add default frequency + mute to **begin()**
- update documentation
- update GitHub actions
- minor edits

----

## [0.1.0] - 2023-12-27
- initial version
