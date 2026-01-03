# Change Log RS485

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.5.2] - 2026-01-03
- update GitHub actions
- update examples
- minor edits

## [0.5.1] - 2024-04-04
- improve **flush()** to work for STM32
- add **void setMicrosPerByte(mpb)** to set delay after flush() for last byte.
- add **uint16_t getMicrosPerByte()**
- update GitHub actions
- minor edits


## [0.5.0] - 2024-02-01
- merge PR #28, Fix for FS conflict on ESP32 (kudos to DoomHammer)
  - all ASCII control characters get a **ASCII_** prefix.
- update MESSAGES.MD with new control characters.
- add unit test for the new ASCII control characters.
- update readme.md.
- add new control characters to keywords.txt

----

## [0.4.0] - 2023-12-18
- fix **write(array, length)**
- add two examples (ack_nack + controller)
- updated experimental protocol, still experimental
- update readme.md
- minor edits

----

## [0.3.0] - 2023-12-05
- Fix #15 - use flush() instead of calculation.
- remove **setMicrosPerByte()** and **getMicrosPerByte()**
  - not needed any more.
- optimize **write(array, length)** when yield flag is set

----

## [0.2.6] - 2023-11-21
- update readme.md

## [0.2.5] - 2023-04-28
- fix send / receive protocol bugs (as far as known)
- add **RS485_master_send_receive.ino** demo
- add **RS485_slave_send_receive.ino** demo
- add **RS485_sniffer.ino** debug tool
- add **EXPERIMENTAL** SoftwareSerial examples.
- update examples.
- move some code from .h to .cpp
- update readme.md

## [0.2.4] - 2023-02-05
- update readme.md
- added messages.md to give som ideas about handshakes/protocols.
- update GitHub actions
- update license 2023

## [0.2.3] - 2022-11-23
- add changelog.md
- add RP2040 to build-CI
- remove version from ASCII_CONTROL
- update keywords.txt
- minor edits

## [0.2.2] - 2022-05-25
- rewrite blocking write(uint8_t \* array, length).
- added write(char \* array, length). (convenience)

## [0.2.1] - 2022-05-24
- add setTXmode(), setRXmode(), getMode().

## [0.2.0] - 2022-05-24
- first published version

----

## [0.1.x] - 2017-10-30
- experimental versions.
