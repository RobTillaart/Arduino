
[![Arduino CI](https://github.com/RobTillaart/I2C_ASDX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_ASDX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_ASDX.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_ASDX/releases)


# I2C_ASDX

Arduino library for I2C ASDX pressure sensor

## Description

The ASDX sensor of Honeywell exist in many variations.
Check the datasheet for all the details.

The I2C_ASDX library can read the sensor and give the pressure in millibar, bar or PSI.

The interface consists of the following:

- **I2C_ASDX(address, psi)** COnstructor, I2C address and maximum pressure.
- **begin(sda, scl)** I2C parameters for ESP32
- **begin()** for UNO and other boards supporting Wire.
- **reset()** resets internal variables,
- **available()** tests if ASDX sensor is available (just address check)
- **read()** reads the sensor, checks for errors, calculates the pressure and set lastRead
- **getPressure()** retuns an int in milliBar, will return 0 after reset() and no read done.
- **getMilliBar()** returns a float in milliBar
- **getBar()** returns a float in bar
- **getPSI()** returns a float in PSI = Pounds per Square Inch.
- **errorCount()** total counter for
- **lastRead()** time in millis since last succesful reading the sensor
- **state()** last known state of read, also returned by read()


## Testing

The library is tested with only 3 different sensors, all of the PG type.
Code is prepared but not tested for 15, 5 and 1 PSI too.

```
    ID    UNIT       TYPE   DESCRIPTION
                              output is porportional to difference
    PG    PSI        Gage   * between applied pressure and atmospheric pressure
    MG    mBar       Gage   * idem
    BG    Bar        Gage   * idem
    KG    KiloPascal Gage   * idem
     D    Differential      * between pressure applied to each of the ports.
     A    Absolute          * between applied pressure and built-in reference to vacuum.


    ADDRESS   PRESSURE   RANGE          TYPE      P   A T V
    0x58      100 psi    0..6895 mBar   SSCDANN 100PG 5 A 5
    0x38       60 psi    0..4137 mbar   SSCDANN 060PG 3 A 5
    0x28       30 psi    0..2068 mbar   SSCDANN 030PG 2 A 5

    P = pressure range
    A = I2C address indicator
    T = accuracy range
    V = voltage (3 volt also supported, not tested)
```

That saidm it is expected that the library is modifyable to support many
more as long as they have the following raw read values.

```
    1638  =   0 PSI
    14746 = max PSI
```

## Testing

TESTED TYPES - type A 10% - 90% only



## Operation

See examples
