#pragma once
//
//    FILE: MHZCO2.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino Library for MHZ series CO2 sensors
//    DATE: 2020-05-05
//     URL: https://github.com/RobTillaart/MHZCO2
//

#include "Arduino.h"

#define MHZCO2_LIB_VERSION        (F("0.2.0"))

#define MHZCO2_OK                 0
#define MHZCO2_TIMEOUT            -10
#define MHZCO2_ERROR_CRC          -11


class MHZCO2
{
public:
  MHZCO2();
  //  Stream is either a HW or SW serial.
  void     begin(Stream * str);
  uint32_t uptime();


  //  PPM = 2000, 5000, 10000 (other values unknown)
  //  check datasheet
  void     setPPM(uint16_t PPM);
  uint16_t getPPM();


  //  MEASUREMENT
  int      measure();
  uint32_t lastMeasurement();
  int      getCO2();
  int      getTemperature();
  int      getAccuracy();
  int      getMinCO2();


  //  CALIBRATION
  //  USE WITH CARE => READ DATASHEET!
  void     calibrateZero();
  void     calibrateSpan(uint16_t span);
  void     calibrateAuto(bool mode = true);


protected:
  Stream * _str;
  uint32_t _startTime;
  uint32_t _lastMeasurement;

  uint16_t _PPM         = 0;
  int      _CO2         = 0;
  int      _temperature = 0;
  int      _accuracy    = 0;
  int      _minCO2      = 0;

  void     send(uint8_t * data, uint8_t len);
  int      receive(uint8_t * answer);
  uint8_t  checksum(uint8_t  * arr);
};



/////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class MHZ1311A : public MHZCO2
{
public:
  MHZ1311A();
};


class MHZ19 : public MHZCO2
{
public:
  MHZ19();
};

class MHZ19B : public MHZCO2
{
public:
  MHZ19B();
};

class MHZ19C : public MHZCO2
{
public:
  MHZ19C();
};

class MHZ19D : public MHZCO2
{
public:
  MHZ19D();
};

class MHZ19E : public MHZCO2
{
public:
  MHZ19E();
};



//  -- END OF FILE --
