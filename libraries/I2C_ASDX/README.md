
[![Arduino CI](https://github.com/RobTillaart/I2C_ASDX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_ASDX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_ASDX.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_ASDX/releases)


# I2C_ASDX

Arduino library for I2C ASDX pressure sensor

## Description

The ASDX sensor of Honeywell exist in many variations.
Check the datasheet of your type for all the details.

The I2C_ASDX library can read the sensor and give the pressure in millibar, bar or PSI or many other units. See below.

The interface:

#### Constructor

- **I2C_ASDX(address, psi)** Constructor, I2C address and maximum pressure.
- **void begin(sda, scl)** I2C parameters for ESP32 a.o.
- **void begin()** for UNO and other boards supporting Wire.
- **void reset()** resets internal variables, incl pressure.
- **bool isConnected()** tests if address can be found on I2C bus.
- **bool available()** wrapper around isConnected. Obsolete in the future.

#### Read

Before any call to **getPressure()** one need to call **read()** unless one wants the last value read.

- **int read()** actually reads the sensor, checks for errors, calculates the pressure and set lastRead, Returns **I2C_ASDX_OK** or error code.


#### Units

- **int getPressure()** retuns pressure (integer format) in milliBar, will return 0 after reset() and no read done.
- **float getMilliBar()** returns pressure in milliBar.
- **float getBar()** returns presure in bar.
- **float getPSI()** returns pressure in PSI = Pounds per Square Inch.
- **float getATM()** returns pressure in Atmosphere.
- **float getDynes()** returns pressure in Dynes.
- **float getInchHg()** returns pressure in inches mercury.
- **float getInchH2O()** returns pressure in inches water.
- **float getPascal()** returns pressure in Pascal. Note this is the SI unit.
- **float getTORR()** returns pressure in TORR.
- **float getCmHg()** returns pressure in centimeter mercury.
- **float getCmH2O()** returns pressure in centimeter water.
- **float getMSW()** returns pressure in Meters of Sea Water. (under water pressure unit).

#### State

- **uint16_t errorCount()** total counter for the number of errors occured.
- **uint32_t lastRead()** time in millis of last succesful read of the sensor.
- **int state()** last known state of read, also returned by **read()**


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


## Future

#### Must

- multiple Wire interface  (breaks interface)
- test isCOnnected in bool begin(). (breaks interface?)
- find a good reference for conversion formula constants.
- 



## Operation

See examples
