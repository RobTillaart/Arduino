# Change Log TLC5947

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-02-09
- add daisy chaining support
- add deviceCount parameter in constructor
- add **int getChannels()**
- add examples (thanks to DevilsCave)
- fix polarity BLANK line
  - **enable()** and **disable()** (P7 datasheet)
  - also initial value constructor + examples
- add **write(uint16_t channels)** interface.
- add const int MAXPWM to replace "magic" number.
- fix changelog.md
- update readme.md (breaking change)
- update unit tests
- adjust examples
- minor edits

----

## [0.2.0] - 2024-02-09
- fix #2 bug in **write()**, now sending 12 bits instead of 13 per channel.
- add **setRGB(led, R, G, B)**
- add **getRGB(led, R, G, B)**
- improved error handling (return values)
- add **bool isEnabled()** get status blank line.
- update unit test
- added performance sketch output
- update readme.md
- minor edits

----

## [0.1.2] - 2023-11-22
- update readme.md
- add **TLC5947_CHANNEL_ERROR**
- catch negative percentages.

## [0.1.1] - 2023-06-21
- improve performance AVR
- add percentage wrappers
- update unit test
- add channel guard in **setPWM()**
- changed return type **setPWM()** to bool.
- update keywords.txt
- minor edits.


## [0.1.0] - 2023-06-17
- initial version


