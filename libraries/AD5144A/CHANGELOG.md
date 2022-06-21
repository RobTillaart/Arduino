# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.7] - 2022-06-21

- fix ESP32 Wire.begin datatype


## [0.1.6] - 2022-04-25

### Added
- extra comments on **sync()**

### Changed

### Fixed
- fixed issue #14, preloading values should not change cached values


## [0.1.5] - 2022-03-14

### Added
- CHANGELOG.md: moved history from AD5144A.cpp to this file.
- fix #12 always call reset in begin().
- add flag to **begin(bool doReset = true)** to explcitly disable the reset
call. The default is true ==> backwards compatibility / normal use.

### Changed
- updated readme.md

### Fixed


## [0.1.4] - 2021-12-10

### Added
- add check for maxValue in code.

### Changed
- remove experimental from version string.
- add headers to library.json,
- minor edits readme, license,

### Fixed


## [0.1.3] - 2021-10-17

### Added

### Changed
- update build-ci
- improve readme.md

### Fixed


## [0.1.2] - 2021-05-12

### Added
- add increment() 
- add decrement()

### Changed

### Fixed


## [0.1.1] - 2021-05-12

### Added
- add topScale() 
- add bottomScale()

### Changed

### Fixed


## [0.1.0] - 2021-04-30

### Added
- initial version

### Changed

### Fixed


