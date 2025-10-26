
[![Arduino CI](https://github.com/RobTillaart/logicAnalyzer/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/logicAnalyzer/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/logicAnalyzer/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/logicAnalyzer/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/logicAnalyzer/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/logicAnalyzer.svg)](https://github.com/RobTillaart/logicAnalyzer/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/logicAnalyzer/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/logicAnalyzer.svg?maxAge=3600)](https://github.com/RobTillaart/logicAnalyzer/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/logicAnalyzer.svg)](https://registry.platformio.org/libraries/robtillaart/logicAnalyzer)


# logicAnalyzer

Arduino library for building a logicAnalyzer. (non performant).


## Description

**Experimental**

This library is to create a logicAnalyzer, although a non performant one. 

The library was written after a question on the Arduino forum and the OP did not
have a logic analyser or scope. 
The library allows to build (and tune) a very simple logic analyzer and is therefore 
useful for educational purposes.

The library is working but has (severe) limitations and cannot be compared to a full 
hardware logic analyzer with PC software with a giga buffer for data.
The samples made by the library must be processed immediately otherwise the RAM of e.g. 
an Arduino UNO R3 is filled up in no time. 
Performance is also not superb but it still is a useful tool to detect and possibly 
analyse (slow) communication. An ESP32 or other fast board is recommended.

The library has a few examples how the library can be used to make a dedicated
logic analyzer.

The library can monitor up to 32 data pins, although performance drops linearly with the
number of channels monitored.
An important functionality of the library is to define a clock pin which can be monitored
separately. Several functions evaluate the state or change of that pin, so one will
only sample the data pins if the clock pin is RISING or FALLING. 
One can also use a timer or millis() to have less samples. 

The level of the library is work in progress, as there are ideas to improve / enhance
the concept.

As always feedback is welcome!


### Related

- https://github.com/RobTillaart/logicAnalyzer
- https://github.com/RobTillaart/I2C_SCANNER
- https://github.com/RobTillaart/MultiSpeedI2CScanner


### Performance

Performance test are done in a tight loop of sampling and printing it to Serial,
e.g. think the Serial plotter. Speed of Serial during test = 1.000.000 baud
to be as less blocking as possible.

Result is the number of samples in ~10 seconds, is about maximum feasible in
"live view" on the serial plotter.

|  Board   |   clock  |  example                 |   s + p  |  sample   |
|:--------:|:--------:|:-------------------------|:--------:|:---------:|
|  UNO R3  |  16 MHz  |  LA_1_channel.ino        |  126218  |   913990  |
|  UNO R3  |  16 MHz  |  LA_4_channel.ino        |   23822  |   289153  |
|  ESP32   | 240 MHx  |  LA_1_channel_esp32.ino  |  193179  |  5688244  |
|  ESP32   | 240 MHx  |  LA_4_channel_esp32.ino  |   64948  |  3142406  |

s + p == sample + plot == live view on serial plotter.

The maximum number of channels is hardcoded to 32 due to internal storage.


#### Conclusions on 0.1.0 version

Performance wise the "live view" in the serial plotter is pretty slow, 
mainly due the time it takes to send the data over Serial. 
At the same time the serial plotter only holds the last 500 points so data
even from 8 channels will only be visible for (a part of) a second.
Still a serial uart up to 9600 baud is in theory just within the "live view" scope,
although in practice live view (Serial plotter).

Dedicated sampling, directly with registers especially on AVR is faster.
However the plotting would still be "blocking".

Storing samples in a buffer and analyse the buffer afterwards would allow much
higher sampling rate. Furthermore it would allow to gow through the data in a 
pace humans can see. RAM might fill up easily, however run length compression 
could be worth investigating.

In short, it is worth to elaborate in the future when needed and time permits.


## Interface

```cpp
#include "logicAnalyzer.h"
```

### Constructor

- **logicAnalyzer(Stream \* str = &Serial)** set the serial port to "dump" data.
- **bool configPins(uint8_t pins[], uint8_t size)** define the array of data 
pins that must be used for the sample() function. 
Channels = 1..32, the function returns false if channels is out of range.
- **void setChannels(uint8_t channels)** set the number of channels for the output. 
Mandatory for the inject() function. 
Channels = 1..32, the function returns false if channels is out of range.
- **uint8_t getChannels()** return the number of channels (size of pin array above).


### Sample and Plot

- **uint32_t sample()** sample all channels once an put the HIGH/LOW values together
in one uint32_t variable. This value is returned but also kept internally.
- **void inject(uint32_t data)** injects generated data that plot() can send as plotter values. (e.g. output control lines or boolean states)
- **void plot()** plots the latest internal value for the serial plotter, with a
defined offset per channel. Value can be patched in the logicAnalyzer.cpp file
- **void plotRaw()** plot the latest internal value as 0 and 1

Note one can mix sample() and inject(), the data pins will always be in the lower channels
and one can add / inject some higher bits. See example.


### Clock

- **bool configClock(uint8_t clockPin)** set the optional clockPin.
- **bool clockChanged()** returns true when the pin has changed since last call. Function to monitor the clockPin so one knows when to sample
the data pins (channels). This reduces the amount of data in a buffer.
- **bool clockFalling()** returns true when the clock pin went from HIGH to LOW since last call.
- **bool clockRising()** returns true when the clock pin went from LOW to HIGH since last call. 
- **bool clockHIGH()** returns true when the pin == HIGH. 
- **bool clockLOW()** returns true when the pin == LOW. 

The latter two allows one to wait until a clock (or trigger) line goes HIGH / LOW.
The following snippet shows how it could be used.

```cpp
while(LA.clockHIGH()); // wait for LOW
while (LA.clockLOW())
{
  LA.sample();
  LA.plot();
}
```

Note: The clock functions do not log a timestamp but the user might do so.

Note: the clockPin can be (ab)used to trigger the start of measurements.


### Count

Just to get the amount of samples made since the start.

- **void setCount(uint32_t count = 0)** reset the sample counter, default to zero.
- **uint32_t getCount()** get the sample counter since last reset / start.


## Future

#### Must

- improve documentation
- rename channels / size to be more logical.
  - dataChannels, injectChannels

#### Should

- AVR performance
  - optimize performance by using registers for IO.(see fastShiftIn library)
    how much gain will there be?

#### Could

- reduce max channel to 16? why? performance?
- examples 
  - use Serial plotter to view and scroll through the buffer.
  - decoding communication, start with combining 8 bits (PAR and SER)
  - detector for signals
- ideas
  - store 8 samples of a 1 channel LA in a byte => 1000 bytes == 8000 samples.
    - channel to bytes... decoding.
    - need clockPin or defined baud rate.
  - investigate external storage in FRAM (SPI).
  - use HW SPI to export the samples to a second (faster) processor / PC
  - add analog sampling too?
  - pulse to timestamp device (when do the pulses come).
- add functionality
  - **uint32_t samplePlot()**  //  slightly optimized?
  - **void plotHeader()** ?
  

#### Wont (for now)

- **uint32_t getSPS()** = counter / time (no time measured in the lib)
- add clockChanged() in configClock()?
  - user must call clockChanged once to get initial value. NB there can be time
    between configClock() and start of measurements.
- heartbeat LED? (costs performance).
- add trigger pin to start the sampling / storing
  - clockPin can be used for that?
  

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


