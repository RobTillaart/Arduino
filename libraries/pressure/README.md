
[![Arduino CI](https://github.com/RobTillaart/pressure/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/pressure/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/pressure/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/pressure/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/pressure/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/pressure.svg)](https://github.com/RobTillaart/pressure/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/pressure/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/pressure.svg?maxAge=3600)](https://github.com/RobTillaart/pressure/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/pressure.svg)](https://registry.platformio.org/libraries/robtillaart/pressure)


# pressure

Arduino library for pressure conversion.


## Description

Arduino library to convert between several pressure units (formats).
The class consists of a number of setters and getters. 
Internally the class uses millibar, although Pascal is the **SI** unit. 
In fact the class just hides all conversion constants to and from millibar.

Pressure is implemented as a float so this limits in theory the precision of the value.
However there are few sensors that can provide more than 7 digits of accuracy.

If other constants / conversions are needed please open an issue on GitHub.

Note: as a conversion uses two steps the conversion error might be (bit) larger 
than in a single conversion step as there are two multiplications involved.

Note: constants need to be verified.

As always, feedback is welcome.


### Related

- https://github.com/RobTillaart/pressure - pressure conversions
- https://github.com/RobTillaart/Temperature - temperature conversions 
- https://github.com/RobTillaart/MS5837 - temperature pressure sensor  (incl pressure to altitude)
- https://github.com/RobTillaart/MS5611 - temperature pressure sensor  (incl pressure to altitude)
- https://github.com/RobTillaart/MSP300 - industrial pressure transducer
- https://swharden.com/blog/2017-04-29-precision-pressure-meter-project/


## Interface

```cpp
#include "pressure.h"
```

### Constructor

- **pressure(float value = 0.0)** Constructor, with optional initial value in mBar.


### Setters

- **void setMilliBar(float value)** sets pressure in milliBar.
- **void setBar(float value)** sets pressure in bar.
- **void setPSI(float value)** sets pressure in PSI = Pounds per Square Inch.
- **void setATM(float value)** sets pressure in Atmosphere.
- **void setDynes(float value)** sets pressure in Dynes.
- **void setInchHg(float value)** sets pressure in inches mercury.
- **void setInchH2O(float value)** sets pressure in inches water.
- **void setPascal(float value)** sets pressure in Pascal. Note this is the **SI** unit.
- **void setTORR(float value)** sets pressure in TORR.
- **void setCmHg(float value)** sets pressure in centimetre mercury.
- **void setCmH2O(float value)** sets pressure in centimetre water.
- **void setMSW(float value)** sets pressure in Meters of Sea Water. (under water pressure unit).
- **void setKGCM2(float value)** sets pressure in Kg per square cm.

### Getters

- **float getMilliBar()** returns pressure in milliBar.
- **float getBar()** returns pressure in bar.
- **float getPSI()** returns pressure in PSI = Pounds per Square Inch.
- **float getATM()** returns pressure in Atmosphere.
- **float getDynes()** returns pressure in Dynes.
- **float getInchHg()** returns pressure in inches mercury.
- **float getInchH2O()** returns pressure in inches water.
- **float getPascal()** returns pressure in Pascal. Note this is the **SI** unit.
- **float getTORR()** returns pressure in TORR.
- **float getCmHg()** returns pressure in centimetre mercury.
- **float getCmH2O()** returns pressure in centimetre water.
- **float getMSW()** returns pressure in Meters of Sea Water. (under water pressure unit).
- **float getKGCM2()** returns pressure in Kg per square cm.

### Gas law, applied

**Experimental**

Apply the ideal gas law : **(P x V) / (n x T) = Constant**

The **change()** function is applied to the current internal pressure.
All these functions return pressure in milliBar.

- **float change(float T1, float T2, float V1, float V2, float N1, float N2)**
  - apply changing temperature (**Kelvin**), 
  - volume and moles are the actual (or relative) change. Units must be the same.
  - If an parameter does not change fill in 1.0 for both before (T1, V1, N1) and after (T2, V2, N2).
- **float changeTemperatureKelvin(float T1, float T2)** only change temperature. T in **Kelvin**.
- **float changeTemperatureCelsius(float T1, float T2)** idem.
- **float changeTemperatureFahrenheit(float T1, float T2)** idem.
- **float changeVolume(float V1, float V2)** only change volume. Units must be the same.
- **float changeMole(float N1, float N2)** only change moles. Units must be the same.

E.g. if the pressure is 1025 mBar and one changes the molarity from 4 to 8,
one can call **P.changeMole(4, 8)** as absolute change or **P.changeMole(1, 2)**
as relative change.

In code:

```cpp
pressure P;
P.setPressure(...);
P.change(T1, T2, V1, V2, N1, N2);  // apply all changes.
x = P.getPressure()
```

Some temperature converters

```cpp
Kelvin = Celsius + 273.15;
Kelvin = (Fahrenheit - 32) * 5.0 / 9.0 + 273.15;
Kelvin = Fahrenheit * 5.0 / 9.0 + 290.93;  // one operator less.
```

### Gas law, factors

If you need a conversion factor for temperature, volume or moles, 
e.g. to make a table fast, you can use the following functions. 
These functions do not affect the internal pressure state.

- **float factor(float T1, float T2, float V1, float V2, float N1, float N2)**
Temperature in Kelvin, other see below.
- **float factorTemperatureKelvin(float T1, float T2)** 
- **float factorTemperatureCelsius(float T1, float T2)**
- **float factorTemperatureFahrenheit(float T1, float T2)**
- **float factorVolume(float V1, float V2)** volume must be in same units
- **float factorMole(float N1, float N2)** moles must be in same units.


### Constants

The library has a number of constants to convert units. See the pressure.h file.
These constants can be used to write specific convertors or define specific constants.

A dedicated conversion is faster as it has only one float multiplication runtime.
The constants will multiply compile time!


```cpp
inline float PSI2MSW(float value)
{
  return value * (PSI2MILLIBAR * MILLIBAR2MSW);
}
```

or
```cpp 
#define PSI2MSW     (PSI2MILLIBAR * MILLIBAR2MSW)
...
float out = in * PSI2MSW;
```


## Operation

```cpp
pressure P;

...

P.setDynes(1000);
Serial.print("mBar: ");
Serial.println(P.getMilliBar()); // 1000 Dynes in mBar
Serial.print("TORR: ");
Serial.println(P.getTORR());     // 1000 Dynes in Torr
```


## Future

#### Must

- update documentation
- find a good reference for conversion constants.
  - https://www.semicore.com/reference/pressure-conversion-reference

#### Should

- test with gas law.
- optimize code if possible.

#### Could

- **float AddMillibar(float value)** simple math with all units (12x)
  - ```return _pressure += value * factor;```
  - does **subtractMillibar()** make more sense?
- **float setMillibar(float value)** return pressure in millibar all setters
  - ```return _pressure = value * factor;```

Possible additional interface
- **changeTemperatureKelvin(float factor)**  Heat it with 10% => factor = 1.1


#### Wont (unless requested)

- move code to .cpp file
- rename parameters so they make more sense?  (simple enough)
```
  void  setMilliBar(float milliBar )  { _pressure = milliBar; };
  void  setBar(float Bar)             { _pressure = Bar * BAR2MILLIBAR; };
  void  setPSI(float PSI)             { _pressure = PSI * PSI2MILLIBAR; };
```
- defaults for functions?
  - none  <<<<<<<<<<<<<<<<<<<<<<<<<<<
  - 0 like constructor?
  - 1 to get conversion constant?  user can do this easily.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

