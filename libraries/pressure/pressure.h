#pragma once
//
//    FILE: pressure.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for pressure conversion
//     URL: https://github.com/RobTillaart/pressure
//


//  CONSTANTS NEED TO BE VERIFIED
//  Temperature 25°C ?

// CONSTANTS SETTERS
#define BAR2MILLIBAR       1000
#define ATM2MILLIBAR       1013.25
#define PSI2MILLIBAR       68.9475729318
#define DYNES2MILLIBAR     0.001
#define INHG2MILLIBAR      33.85355
#define INH202MILLIBAR     2.4908890833333
#define PASCAL2MILLIBAR    0.01
#define TORR2MILLIBAR      1.33322368
#define CMHG2MILLIBAR      13.3322368
#define CMH2O2MILLIBAR     0.980665
#define MSW2MILLIBAR       0.01

// CONSTANTS GETTERS
#define MILLIBAR2BAR       0.001
#define MILLIBAR2ATM       9.86923267e-4
#define MILLIBAR2PSI       0.0145037738
#define MILLIBAR2DYNES     1000
#define MILLIBAR2INHG      2.9539e-2
#define MILLIBAR2INH2O     0.40146307866177
#define MILLIBAR2PASCAL    100
#define MILLIBAR2TORR      0.750061683
#define MILLIBAR2CMHG      0.0750061683
#define MILLIBAR2CMH2O     1.0197162129779 
#define MILLIBAR2MSW       100


#define PRESSURE_LIB_VERSION        (F("0.1.0"))


class pressure
{
public:
  //  CONSTRUCTOR
  pressure(float value = 0)       { _pressure = value; };


  void  setMilliBar(float value)  { _pressure = value; };
  void  setBar(float value)       { _pressure = value * MILLIBAR2BAR; };
  void  setPSI(float value)       { _pressure = value * MILLIBAR2PSI; };
  void  setATM(float value)       { _pressure = value * MILLIBAR2ATM; }
  void  setDynes(float value)     { _pressure = value * MILLIBAR2DYNES; }
  void  setInchHg(float value)    { _pressure = value * MILLIBAR2INHG; }
  void  setInchH2O(float value)   { _pressure = value * MILLIBAR2INH2O; }
  void  setPascal(float value)    { _pressure = value * MILLIBAR2PASCAL; }
  void  setTORR(float value)      { _pressure = value * MILLIBAR2TORR; }
  void  setCmHg(float value)      { _pressure = value * MILLIBAR2CMHG; }
  void  setCmH2O(float value)     { _pressure = value * MILLIBAR2CMH2O; }
  void  setMSW(float value)       { _pressure = value * MILLIBAR2MSW; }


  float getMilliBar()  { return _pressure; };
  float getBar()       { return _pressure * MILLIBAR2BAR; };
  float getPSI()       { return _pressure * MILLIBAR2PSI; };
  float getATM()       { return _pressure * MILLIBAR2ATM; }
  float getDynes()     { return _pressure * MILLIBAR2DYNES; }
  float getInchHg()    { return _pressure * MILLIBAR2INHG; }
  float getInchH2O()   { return _pressure * MILLIBAR2INH2O; }
  float getPascal()    { return _pressure * MILLIBAR2PASCAL; }
  float getTORR()      { return _pressure * MILLIBAR2TORR; }
  float getCmHg()      { return _pressure * MILLIBAR2CMHG; }
  float getCmH2O()     { return _pressure * MILLIBAR2CMH2O; }
  float getMSW()       { return _pressure * MILLIBAR2MSW; }

private:
  float    _pressure;
};


// -- END OF FILE --
