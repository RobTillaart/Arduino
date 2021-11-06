
[![Arduino CI](https://github.com/RobTillaart/Kelvin2RGB/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Kelvin2RGB/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Kelvin2RGB/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Kelvin2RGB/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Kelvin2RGB/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Kelvin2RGB/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Kelvin2RGB.svg?maxAge=3600)](https://github.com/RobTillaart/Kelvin2RGB/releases)


# Kelvin2RGB

Arduino library for converting temperature and brightness to RGB values


## Credentials

This library is based upon an article of Tanner Helland
and a related story by Neil Bartlett
http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
http://www.zombieprototypes.com/?p=210  
https://en.wikipedia.org/wiki/Color_temperature#Categorizing_different_lighting

There are more approximation formulas, some claim to be better, 
however these are not investigated. On request these can be added.


## Description

The library converts a temperature in Kelvin and a brightness (0..100%) 
 to 3 numbers red, green and blue.
These numbers are weights can be used to correct a colorimage for virtual white temperature.

There are 2 convert functions where the **convert_NB()** is claimed to be 
the more accurate one.

With the numbers R,G,B calculated one can convert images so they will look
more like taken with candle light, sunrise or sunset etc. 


**pseudo code**
```cpp
Kelvin2RGB KRGB;

KRGB.convert(1850, 100);  // sunrise light factors

for each pixel in image
{
  red   *= KRGB.red();
  green *= KRGB.green();
  blue  *= KRGB.blue();
  drawPixel();
}
```

The numbers can also be used to reduce the blue channel so it has less effect 
on "getting sleepy".

The library uses floats for the R,G and B weights to keep values as accurate as possible.
Especially with images with more than 8 bits per channel this is preferred.
That said it is also possible to use this on a 565 image or to adjust color lookup tables.


## Interface

The interface is straightforward:

- **Kelvin2RGB()** constructor
- **void begin()** empty function for now.
- **void reset()** resets all internal values to 0.
- **void convert_TH(float temperature, float brightness = 100)**  
    temperature = 0..65500   temperature below 1000 is not well defined.  
    brightness = 0..100%, 
- **void convert_NB(float temperature, float brightness = 100)**  
    temperature = 0..65500   temperature below 1000 is not well defined.  
    brightness = 0..100%, 
    Is a bit more accurate and slightly slower (few %). Read link above for more information.
- **float temperature()** returns temperature, to check the value used.
- **float brightness()** returns brightness, to check the value used.
- **float red()** returns red channel weight 0.0 .. 1.0  
note this is different from Helland / Bartlett who both use an integer value 0 .. 255
- **float green()** returns green channel weight 0.0 .. 1.0
- **float blue()** returns blue channel weight 0.0 .. 1.0
- **uint32_t setRGB(float red, float green, float blue, float brightness = 100)** sets RGB values 
red, green, blue should be in 0 .. 1.0 range. brightness should be in 0..100%, Default = 100%.
returns a 24 bit RGB value,  
- **uint32_t RGB()** returns a 24 bit RGB value, 0 .. 16777215
more efficient than 3 floats for communication. 
- **uint16_t RGB565()** returns a 16 bit RGB value, 
5 bits for red, 6 for green and 5 for blue.
- **uint32_t BGR()** returns a 24 bit BGR value, 0 .. 16777215
- **uint32_t CMYK()** returns a 32 bit = 4 byte CMYK value,  


## Future

- separate brightness per colour channel to mimic "artificial illumination"  (0.2.0 ?)
- define constants like candleLight as parameter.
- investigate other formulas.
- investigate timing and performance
- investigate usability for RGB led strip.
- remove begin() ?
- add examples 
  - CMYK()
  - BGR()
  - Led-strip()


## Operations

See examples

