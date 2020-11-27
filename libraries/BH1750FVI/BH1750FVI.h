#pragma once
//
//    FILE: BH1750FVI_H.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.2.4
// PURPOSE: Arduino library for BH1750FVI (GY-30) lux sensor
// HISTORY: See BH1750FVI.cpp
//


//  breakout BH1750FVI / GY-30
//
//      +-----------------------+
//  GND |o                      |
//  ADD |o                      |
//  SDA |o            +         |  + = sensor
//  SCL |o                      |
//  VCC |o                      |
//      +-----------------------+
//
// ADD = ADDRESS:
//   0 = 0x23
//   1 = 0x5C
//

#include "Wire.h"
#include "Arduino.h"

#define BH1750FVI_LIB_VERSION       "0.2.4"
#define BH1750FVI_DEFAULT_ADDRESS   0x23
#define BH1750FVI_ALT_ADDRESS       0x5C

// COMMANDS P5
#define BH1750FVI_POWER_ON          0x00
#define BH1750FVI_POWER_OFF         0x01
#define BH1750FVI_RESET             0x07
#define BH1750FVI_CONT_HIGH         0x10
#define BH1750FVI_CONT_HIGH2        0x11
#define BH1750FVI_CONT_LOW          0x13
#define BH1750FVI_ONCE_HIGH         0x20
#define BH1750FVI_ONCE_HIGH2        0x21
#define BH1750FVI_ONCE_LOW          0x23

#define BH1750FVI_REFERENCE_TIME    0x45   // 69

#define BH1750FVI_MODE_LOW          0x00
#define BH1750FVI_MODE_HIGH         0x01
#define BH1750FVI_MODE_HIGH2        0x02

// ERROR CODES
#define BH1750FVI_OK                         0
#define BH1750FVI_ERROR_WIRE_REQUEST         -10


class BH1750FVI
{
public:

#if defined(ESP8266) || defined(ESP32)
  // dataPin and clockPin can be used for ESP8266
  BH1750FVI(const uint8_t address , const uint8_t dataPin, const uint8_t clockPin);
#endif

  BH1750FVI(const uint8_t address, TwoWire *wire = &Wire);

  float   getRaw();      // no HIGH2 mode + no sensitivity factor.
  float   getLux();
  int     getError();

  void    powerOn()          { command(BH1750FVI_POWER_ON); };
  void    powerOff()         { command(BH1750FVI_POWER_OFF); };
  void    reset()            { command(BH1750FVI_RESET); };

  //      MODE        TIME        RESOLUTION
  //   2  HIGH2       120 ms      0.5 lux        // recommended max * 1.5 = 180 ms
  //   1  HIGH        120 ms      1.0 lux
  //   0  LOW          16 ms      4.0 lux
  uint8_t getMode()          { return _mode; };

  void    setContHighRes();
  void    setContHigh2Res();
  void    setContLowRes();

  void    setOnceHighRes();
  void    setOnceHigh2Res();
  void    setOnceLowRes();
  bool    isReady();          // only after setOnce...Res();

  // read datasheet P11 about details of the correction or sensitivity factor
  // to be used for very high and very low brightness
  // or to correct for e.g. transparancy
  void    changeTiming(uint8_t val);            // 69 is default = BH1750FVI_REFERENCE_TIME
  void    setCorrectionFactor(float f);         // 0.45 .. 3.68
  float   getCorrectionFactor();

  // read datasheet P3 and check figure 4 and 5.
  // setAngle is constrained to -89..+89
  void    setAngle(int degrees);
  int     getAngle() { return _angle; };
  
  // datasheet P3 figure 7
  // Effect of temperature is about 3% / 60°C ~~ 1% / 20°C
  // to be used if temp is really hot or cold.
  void    setTemperature(int temp) { _temp = temp; };
  int     getTemperature() { return _temp; };


  // datasheet Page 3 figure 1  (experimental correction)
  // Effect of wavelength can be substantial, 
  // correctionfactor is calculated by multiple linear approximations.
  void    setWaveLength(int waveLength);
  int     getWaveLength() { return _waveLength; };

private:
  uint16_t  readData();
  void      command(uint8_t value);

  uint8_t   _address;
  uint16_t  _data;
  int       _error;
  uint8_t   _sensitivityFactor;
  uint8_t   _mode;
  uint32_t  _requestTime = 0;
  float     _angleFactor = 1;
  int       _angle = 0;
  int       _temp = 20;
  float     _waveLengthFactor = 1;
  int       _waveLength = 580;

  TwoWire*  _wire;
};

// -- END OF FILE --
