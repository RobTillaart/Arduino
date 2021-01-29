
[![Arduino CI](https://github.com/RobTillaart/Cozir/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Cozir/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Cozir.svg?maxAge=3600)](https://github.com/RobTillaart/Cozir/releases)


# Cozir

Arduino library for COZIR range of temperature, humidity and CO2 sensors.

## Description

The Cozir library is still experimental as I do not have a sensor to test the library.
The polling mode as used in the examples seems to work quite well.

Note: the **CozirDemoHWSerial.ino** example needs to run on a MEGA or a Teensy, 
at least a board with more than one Serial port. 

## Interface



## Operation

See examples.

There are functions commented that are **NOT RECOMMENDED** by the datasheet. 
Feel free to uncomment but use at your own risk.

## Notes

Note: the 0.2.0 library is still experimental, see several TODO's in the code.
That said, the default polling mode used in the examples works stable (last version tested).

## Test sensor

People who have a spare sensor for me, or are willing to run tests, please contact me.
