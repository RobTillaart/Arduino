
[![Arduino CI](https://github.com/RobTillaart/pressure/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/pressure/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/pressure/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/pressure/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/pressure/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/pressure/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/pressure.svg?maxAge=3600)](https://github.com/RobTillaart/pressure/releases)


# pressure

Arduino library for pressure conversion.


## Description

Simple library to convert between several pressure formats.
It consists of a number of setters and getters and internally it uses millibar. 
In fact it just hides all conversion constants.

Pressure is implemented as a float so this limits the precision of the value.

Note: as the conversion is 2 steps the conversion error might be larger than in a single conversion step.

Note: constants need to be verified.


## Interface


#### Constructor

- **pressure(float value = 0.0)** Constructor, with optional initial value.


#### setters

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


#### getters

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

- update documentation
- find a good reference for conversion formula constants.


