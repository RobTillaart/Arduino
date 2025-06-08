
# Change Log I2C_PWM_generator

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.1] - 2025-05-16
- add LED 13 as heartbeat indicator.
- add watchdog reset (2 seconds)
- add POSValue array, power on start values.
- add currentValue array to prep getPWM()
- add get PWM value - request register 0..5, 1 byte
- add set all - register 0x20
- add set to power on reset - register (command) 0x21
- update readme.md


## [0.1.0] - 2024-11-25
- initial version


//  -- END OF FILE --

