#pragma once
//
//    FILE: BH1750FVI.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: Arduino library for BH1750FVI (GY-30) lux sensor
//     URL: https://github.com/RobTillaart/BH1750FVI_RT


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


#define BH1750FVI_LIB_VERSION                 (F("0.3.2"))


#define BH1750FVI_DEFAULT_ADDRESS             0x23
#define BH1750FVI_ALT_ADDRESS                 0x5C

#define BH1750FVI_REFERENCE_TIME              0x45   //  69 = default

#define BH1750FVI_MODE_LOW                    0x00
#define BH1750FVI_MODE_HIGH                   0x01
#define BH1750FVI_MODE_HIGH2                  0x02


// ERROR CODES
#define BH1750FVI_OK                          0
#define BH1750FVI_ERROR_WIRE_REQUEST          -10


class BH1750FVI
{
public:

  BH1750FVI(const uint8_t address, TwoWire *wire = &Wire);
  //  returns true if isConnected()
  bool    begin();        //  resets to constructor defaults. (use with care)
  bool    isConnected();  //  returns true if address is on I2C bus


  float   getRaw();       //  no HIGH2 mode + no sensitivity factor.
  float   getLux();       //  corrected for mode, temp, angle and correctionFactor.
  int     getError();


  void    powerOn();
  void    powerOff();
  void    reset();


  //      MODE        TIME        RESOLUTION
  //   2  HIGH2       120 ms      0.5 lux        //  recommended max * 1.5 = 180 ms
  //   1  HIGH        120 ms      1.0 lux
  //   0  LOW          16 ms      4.0 lux
  uint8_t getMode() { return _mode; };


  void    setContHighRes();
  void    setContHigh2Res();
  void    setContLowRes();


  void    setOnceHighRes();
  void    setOnceHigh2Res();
  void    setOnceLowRes();
  bool    isReady();          //  only after setOnce...Res();


  //  read datasheet P11 about details of the correction or sensitivity factor
  //  to be used for very high and very low brightness
  //  or to correct for e.g. transparency
  void    changeTiming(uint8_t time = BH1750FVI_REFERENCE_TIME);   //  69 is default


  //  returns changeTiming() parameter
  uint8_t setCorrectionFactor(float factor = 1);  //  0.45 .. 3.68
  //  returns percentage set.
  float   getCorrectionFactor();


  //  read datasheet P3 and check figure 4 and 5.
  //  setAngle is constrained to -89..+89
  //  returns the angle correction factor
  float   setAngle(float degrees = 0);
  float   getAngle() { return _angle; };


  //  datasheet P3 figure 7
  //  Effect of temperature is about 3% / 60°C ~~ 1% / 20°C
  //  to be used if temp is really hot or cold.
  //  returns the temperature correction factor
  float   setTemperature(int temp = 20);
  int     getTemperature() { return _temperature; };


  //  datasheet Page 3 figure 1  (experimental correction)
  //  Effect of wavelength can be substantial,
  //  correction is calculated by multiple linear approximations.
  //  wavelength of 580 ==> correction == 1
  //  returns the wavelength correction factor
  float   setWaveLength(int waveLength = 580);
  int     getWaveLength() { return _waveLength; };


private:
  uint16_t  readData();
  void      command(uint8_t value);

  uint8_t   _address;
  uint16_t  _data;
  int       _error;
  uint8_t   _sensitivityFactor;
  uint8_t   _mode;

  uint32_t  _requestTime      = 0;
  float     _angleFactor      = 1;
  float     _angle            = 0;
  float     _tempFactor       = 1;
  int       _temperature      = 20;
  float     _waveLengthFactor = 1;
  int       _waveLength       = 580;

  TwoWire*  _wire;
};


//  -- END OF FILE --

