# Change Log HX712
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.1] - 2026-10-28
- fix #2, add timeout parameter in read()
- change return type to bool begin() to report the timeout.
- change return type to bool reset() to report the timeout.
- add getLastError() - HX712_READ_TIMEOUT only for now
- update readme.md
- removed m4 from build-CI to reduce build time (expect in 1 sketch).
- minor edits

## [0.1.0] - 2026-03-30
- initial version (loosely based upon HX711 0.6.3)
