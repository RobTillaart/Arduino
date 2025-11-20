# Change Log SparseMatrix

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.7] - 2025-11-19
- fix #8, readme.md badges and more
- add bounding box functions
  - **bool boundingBoxX(uint8_t &minX, uint8_t &maxX)**
  - **bool boundingBoxY(uint8_t &minY, uint8_t &maxY)**
- add traversing
  - **bool first(uint8_t &x, uint8_t &y, float &value)**
  - **bool next(uint8_t &x, uint8_t &y, float &value)**
  - **bool prev(uint8_t &x, uint8_t &y, float &value)**
  - **bool last(uint8_t &x, uint8_t &y, float &value)**
  - add example **sparse_matrix_traverse.ino**
- add low level API
  - **int32_t findPosition(uint8_t x, uint8_t y)**
  - **float getValue(uint16_t position)**
  - **bool setValue(uint16_t position, float value);
  - **int compact()**
- minor edits

## [0.1.6] - 2025-09-15
- update GitHub actions
- minor edits

## [0.1.5] - 2023-11-22
- update readme.md

## [0.1.4] - 2022-11-25
- Add RP2040 support to build-CI.
- Add CHANGELOG.md
- update readme.md

## [0.1.3] - 2022-07-16
- add boundingBox(...)
- fix #4 set() add()

## [0.1.2] - 2022-07-14
- increase size to uint16_t
- add SPARSEMATRIX_MAX_SIZE
- improve documentation

## [0.1.1] - 2022-07-13
- add clear()
- add add(x, y, value)
- fix set(x, y, 0)

## [0.1.0] - 2022-07-12
- initial version

