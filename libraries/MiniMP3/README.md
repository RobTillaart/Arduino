
[![Arduino CI](https://github.com/RobTillaart/MiniMP3/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/MiniMP3/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/MiniMP3/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/MiniMP3/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/MiniMP3/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/MiniMP3.svg)](https://github.com/RobTillaart/MiniMP3/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MiniMP3/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MiniMP3.svg?maxAge=3600)](https://github.com/RobTillaart/MiniMP3/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/MiniMP3.svg)](https://registry.platformio.org/libraries/robtillaart/MiniMP3)


# MiniMP3 Library

Arduino library for DFRobotics MP3 player and compatibles.


## Description

**Experimental**

MiniMP3 is an Arduino library to control the DFRobotics MP3 player and compatibles.
Goal is to have basic control of the device via hardware Serial or software Serial.

If you need complete control including all kinds of feedback events like
"card inserted" you need to use the DFRobotics library.

This library is work in progress.


#### Schema

```
               MINI MP3
            +-----__-----+
       VCC  |            |  BUSY
        RX  |            |  USB-
        TX  |            |  USB+
     DAC_R  |            |  ADKEY_2
     DAC_L  |  +------+  |  ADKEY_1
     SPK_1  |  |      |  |  IO_2
       GND  |  |  SD  |  |  GND
     SPK_2  |  | CARD |  |  IO_1
            +--+------+--+

When connecting to a 5V MCU, you need to add a 1K resistor between the
Serial TX and RX as the MiniMP3 is 3V3. Otherwise a big HUM.
```


#### Links

- https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299  (extended library)


## Interface

```cpp
#include "MiniMP3.h"
```

#### Constructor

- **MiniMP3(Stream \* stream = &Serial)** Can be used with software or hardware Serial.
Default stream is Serial.
- **void reset()** reset the player.
- **void lowPower()** set the player in low power mode.


#### Basic controls

- **void play(uint16_t track)** plays SD:/MP3/track.mp3
- **void next()** go to next track.
- **void prev()** go to previous track.
- **void pause()** pause playing
- **void stop()** stop playing.


#### Volume

- **void volume(uint16_t vol = 0)** set volume range 0..30. 
  - default volume off.
- **void volumeUp()** increase volume one step.
- **void volumeDown()** decrease volume one step.
- **void equalizer(uint8_t mode = MP3_EQ_NORMAL)** 
  - Set equalizer mode, see options below.


#### Equalizer modi

|  Mode            |  value  |  notes    |
|:-----------------|:-------:|:---------:|
|  MP3_EQ_NORMAL   |    0    |  default
|  MP3_EQ_POP      |    1    |
|  MP3_EQ_ROCK     |    2    |
|  MP3_EQ_JAZZ     |    3    |
|  MP3_EQ_CLASSIC  |    4    |
|  MP3_EQ_BASS     |    5    |


## Future

#### Must

- improve documentation

#### Should

- test
- keep it minimal.

#### Could

- add playBack modi.
- test different models
- add examples
  - implement playlists
  - implement "skip_search" (play 10 seconds of each file).
  - implement randomizer
- add unit tests (possible?)
- get current track
- last track
- last mode

#### Wont

- implement query commands


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

