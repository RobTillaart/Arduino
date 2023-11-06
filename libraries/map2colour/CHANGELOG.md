# Change Log map2colour

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.1] - 2023-11-05
- update readme.md
- minor edits


## [0.2.0] - 2023-04-24
- add dynamic size in constructor (minimum 7 for backwards)
- add destructor.
- add **uint8_t size()**
- add **m2c_colours.h** for colour constants
- add **M2C_GRAY** constants
- array of values now may be non-decreasing (iso increasing)
- update readme.md
- minor edits

----

## [0.1.6] - 2023-02-21
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.1.5] - 2022-10-19
- redo **begin()** of map2colourFast to always create divFactors.
- add compare example to compare map2colour and map2colourFast.
- extent unit test with compare map2colour and map2colourFast.
- update examples
- add RP2040 in build-CI
- add changelog.md
- fix keywords.txt

## [0.1.4] - 2021-12-08
- add derived class map2colourFast: faster + uses more MEMORY / RAM

## [0.1.3] - 2021-12-07
- improve performance map2RGB()

## [0.1.2] - 2021-12-06
- add map2_565()
- add + improve examples.
- fix value > upper bug.

## [0.1.1] - 2021-12-05
- add user defined colour-map.
- add unit tests, update readme.md.

## [0.1.0] - 2021-12-04
- initial version.
