#pragma once
//
//    FILE: MS5837.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2023-11-12
// PURPOSE: Arduino library for MS5837 temperature and pressure sensor.
//     URL: https://github.com/RobTillaart/MS5837


#include "Arduino.h"
#include "Wire.h"


#define MS5837_LIB_VERSION        (F("0.1.1"))


//  TYPES
#define MS5803_TYPE_01             1
#define MS5837_TYPE_02             2
#define MS5837_TYPE_30            30


class MS5837
{
public:
  MS5837(TwoWire *wire = &Wire);

  //  MS5837_30 bar = 0
  //  MS5837_02 bar = 1
  //  MS5803_02 bar = 2
  bool     begin(uint8_t mathMode);
  bool     isConnected();
  bool     reset(uint8_t mathMode);
  uint8_t  getType();
  uint8_t  getAddress();


  //////////////////////////////////////////////////////////////////////
  //
  //  READ
  //
  //  call will block 3-40 milliseconds, depends on # bits.
  //  bits = 8-12 for the MS5803_02
  //  bits = 8-13 for the MS5837_02 and MS5837_30)
  bool     read(uint8_t bits = 8);
  uint32_t lastRead();

  //  see https://github.com/RobTillaart/pressure for conversions.
  //  returns mBar
  float    getPressure();
  //  see https://github.com/RobTillaart/temperature for conversions.
  //  returns Celsius
  float    getTemperature();
  //       compensate for actual air pressure if needed
  float    getAltitude(float airPressure = 1013.25);


  //////////////////////////////////////////////////////////////////////
  //
  //  DEPTH
  //
  //  density is temperature dependent, see
  //  https://www.usgs.gov/special-topics/water-science-school/science/water-density
  //
  //  density water 20°C = 0.99802
  //  density seawater is
  //  density in grams / cm3  (so not in grams per liter
  void     setDensity(float density = 0.99802);
  float    getDensity();
  //       returns meters (SI unit)
  //       compensate for actual air pressure if needed
  float    getDepth(float airPressure = 1013.25);


  //////////////////////////////////////////////////////////////////////
  //
  //  ERROR (experimental)
  //
  int      getLastError();


protected:
  int        command(uint8_t cmd);
  void       initConstants(uint8_t mathMode);
  uint32_t   readADC();


  uint8_t   _address = 0x76;
  TwoWire * _wire = NULL;

  float     _pressure;
  float     _temperature;

  float     C[8];
  uint8_t   _type;
  int       _result;

  float     _density = 0.99802;  //  water at 20 °C
  //  prepare error handling.
  int       _error = 0;
  uint32_t  _lastRead;
};


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//

//////////////////////////////////////////////////////////////////////
//
//  MS5803
//
class MS5803 : public MS5837
{
public:
  MS5803(TwoWire *wire = &Wire);
  MS5803(uint32_t address, TwoWire *wire = &Wire);
};


//////////////////////////////////////////////////////////////////////
//
//  MS5837_30
//  MS5837_02
//


//  -- END OF FILE --

