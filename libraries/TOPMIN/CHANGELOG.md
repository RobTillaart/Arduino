# Change Log TOPMIN

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.1] - 2023-11-23
- update readme.md


## [0.2.0] - 2023-06-16
- breaking change!
  - reverses the order of the minima when requested.
  - results in the top one always have index 0
  - top position is independent of the size of the TOPMIN object.
- fix boundary bug  **getValue() / getTag()** (index >= count).
- add allocation checks.
- **fill()** returns bool (true upon success)
- update unit tests
- update readme.md
- minor edits.

----

## [0.1.1] - 2023-06-13
- add **TOPMINext**, holds a value + tag (e.g. timestamp or counter)
- add examples.
- changed **get()** into **getValue()**
- update readme.md
- minor edits.

## [0.1.0] - 2023-05-18
- initial version

