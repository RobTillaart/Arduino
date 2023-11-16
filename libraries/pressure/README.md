
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
The class consists of a number of setters and getters and internally it uses millibar. 
In fact the class just hides all conversion constants to and frm millibar.

Pressure is implemented as a float so this limits the precision of the value.

If other constants / conversions are needed please open an issue on GitHub.

Note: as a conversion uses two steps the conversion error might be (bit) larger 
than in a single conversion step as there are two multiplications involved.

Note: constants need to be verified.


#### Related

- https://github.com/RobTillaart/temperature (a bit)


## Interface

```cpp
#include "pressure.h"
```

#### Constructor

- **pressure(float value = 0.0)** Constructor, with optional initial value.


#### Setters

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


#### Getters

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


#### Gas law (experimental see below)

The **change()** function is applied to the current internal pressure.
All these functions return pressure in milliBar.

- **float change(float T1, float T2, float V1, float V2, float N1, float N2)**
  - apply changing temperature (**Kelvin**), 
  - volume (m3) and moles.
  - If an parameter does not change fill in 1 for both before (T1,V1, N1) and after (T2,V2,n2).
- **float changeTemperature(float T1, float T2)** only change temperature. T in **Kelvin**.
- **float changeVolume(float V1, float V2)** only change volume.
- **float changeMole(float N1, float N2)** only change moles.


#### Constants

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

#### Experimental

Note: names changed in 0.3.0


Apply the ideal gas law : **(P x V) / (n x T) = Constant**

- **float change(float T1, float T2, float V1, float V2, float N1, float N2)**
  - T (temperature) in Kelvin,
  - V (volume) in identical units, 
  - N (# atoms) in mole
  - wrapper around next three.
- **float changeTemperature(float T1, float T2)** only change temperature. T in Kelvin.
- **float changeVolume(float V1, float V2)** only change volume.
- **float changeMole(float N1, float N2)** only change moles.

in code
```cpp
pressure P;
P.setPressure(...);
P.change(T1, T2, V1, V2, N1, N2);  // apply all changes.
x = P.getPressure()
```


Some temperature converters

```cpp
Kelvin = Celsius + 273.15;
Kelvin = (Fahrenheit - 32) \* 5 / 9 + 273.15;
Kelvin = Fahrenheit \* 5 / 9 + 290.93;  // one operator less.
```


## Future

#### Must

- update documentation
- find a good reference for conversion constants.
  - https://www.semicore.com/reference/pressure-conversion-reference

#### Should

- test with gas law.

#### Could

- **float AddMillibar(float value)** simple math with all units (12x)
  - ```return _pressure += value * factor;```
  - does **subtractMillibar()** make more sense?
- **float setMillibar(float value)** return pressure in millibar all setters
  - ```return _pressure = value * factor;```

#### Wont (unless requested)

- **float changeTC(float T1, float T2)** only change temperature, T in Celsius.
- **float changeTF(float T1, float T2)** only change temperature, T in Fahrenheit.
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
  - 1 to get conversion constant?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

