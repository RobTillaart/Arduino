# Change Log TLC5917

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.0] - 2024-07-12
- fix deviceCount in **write()**.
- fix allocation buffer for channels in constructor.
- update performance sketch.
- add demo_setChannel sketch (array param).
- rename blank to **outputEnable**.
- update readme.md.
- minor edits.

----

## [0.1.2] - 2024-06-02
- add **TLC5917_NORMAL_MODE** and **TLC5917_SPECIAL_MODE**
- add **uint8_t getMode()**
- rename setCurrentAdjustMode() to **void setSpecialMode()**
- rename **getChannels()** into **channelCount()** (looked like getChannel)
- refactored **writeConfiguration()**
- add **uint8_t getConfiguration()**
- add **bool setGain(bool CM, bool HC, uint8_t CC)**
- add **bool setCurrentGain(float n)**
- add **float getVoltageGain()**
- add **float getCurrentGain()**
- update readme.md
- add / update examples.
- minor edits.

## [0.1.1] - 2024-06-02
- fix **setChannel()**
- rename **getChannels()** to **channelCount()**
- update examples
- update readme.md
- minor edits

## [0.1.0] - 2024-03-17
- initial version


