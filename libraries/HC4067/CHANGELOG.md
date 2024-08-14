# Change Log HC4067

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-08-14
- Fix for setChannel(), Thanks to C. Fraser!
- update readme.md

----

## [0.2.1] - 2024-05-28
- change return type of **bool setChannel()**
- verify the channel parameter of **bool setChannel()**
- add parameter to **bool setChannel(channel, disable = true)**
- update readme.md

## [0.2.0] - 2024-04-03
- fix ghost channels when using for OUTPUT
  - add disable/enable in setChannel()
- improve setChannel(), only write changed pins.
- update HC4067_performance.ino
- update readme.md
- update GitHub actions
- minor edits

----

## [0.1.2] - 2023-11-04
- update readme.md


## [0.1.1] - 2023-01-25
- fix bit mask
- removed return value **setCHannel()** as makes no sense.
- updated readme.md.
- add example HC4067_performance.ino 
- add example HC4067_16_buttons.ino
- minor edits.

## [0.1.0] - 2023-01-25
- initial version

