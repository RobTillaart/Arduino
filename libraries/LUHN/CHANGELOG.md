# Change Log LUHN

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.1] - 2023-10-26
- update readme.md
- update keywords.txt


## [0.2.0] - 2023-05-08
- add unit test
- fix stream mode - **add()** and **reset()**
- fix bugs in generation / validation.
- add **generateChecksum(const char \* buffer)**
- change **count** to be 32 bit to support really large streams.
- add **count()** function to return internal counter.
- updates readme.md
- 0.1.x versions are obsolete

----

## [0.1.1] - 2022-12-29
- add stream interface
  - **char add(char c)**
  - **char reset()**
- add example
- update documentation
- fix warning

## [0.1.0] - 2022-12-24
- initial version
