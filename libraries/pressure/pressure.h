#pragma once
//
//    FILE: pressure.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Arduino library for pressure conversion
//     URL: https://github.com/RobTillaart/pressure



#define PRESSURE_LIB_VERSION        (F("0.3.3"))


//  CONSTANTS NEED TO BE VERIFIED
//  Temperature 25°C ?

//  CONSTANTS SETTERS
#define BAR2MILLIBAR           1000
#define ATM2MILLIBAR           1013.25
#define PSI2MILLIBAR           68.9475729318
#define DYNES2MILLIBAR         0.001
#define INHG2MILLIBAR          33.85355
#define INH2O2MILLIBAR         2.4908890833333
#define PASCAL2MILLIBAR        0.01
#define TORR2MILLIBAR          1.33322368
#define CMHG2MILLIBAR          13.3322368
#define CMH2O2MILLIBAR         0.980665
#define MSW2MILLIBAR           0.01
#define KGCM22MILLIBAR         980.4

//  CONSTANTS GETTERS
#define MILLIBAR2BAR           (1.0 / BAR2MILLIBAR)
#define MILLIBAR2ATM           (1.0 / ATM2MILLIBAR)
#define MILLIBAR2PSI           (1.0 / PSI2MILLIBAR)
#define MILLIBAR2DYNES         (1.0 / DYNES2MILLIBAR)
#define MILLIBAR2INHG          (1.0 / INHG2MILLIBAR)
#define MILLIBAR2INH2O         (1.0 / INH2O2MILLIBAR)
#define MILLIBAR2PASCAL        (1.0 / PASCAL2MILLIBAR)
#define MILLIBAR2TORR          (1.0 / TORR2MILLIBAR)
#define MILLIBAR2CMHG          (1.0 / CMHG2MILLIBAR)
#define MILLIBAR2CMH2O         (1.0 / CMH2O2MILLIBAR)
#define MILLIBAR2MSW           (1.0 / MSW2MILLIBAR)
#define MILLIBAR2KGCM2         (1.0 / KGCM22MILLIBAR)

/*
//  was
#define MILLIBAR2BAR           0.001
#define MILLIBAR2ATM           9.86923267e-4
#define MILLIBAR2PSI           0.0145037738
#define MILLIBAR2DYNES         1000
#define MILLIBAR2INHG          2.9539e-2
#define MILLIBAR2INH2O         0.40146307866177
#define MILLIBAR2PASCAL        100
#define MILLIBAR2TORR          0.750061683
#define MILLIBAR2CMHG          0.0750061683
#define MILLIBAR2CMH2O         1.0197162129779
#define MILLIBAR2MSW           100
#define MILLIBAR2KGCM2         1.012E-3
*/



class pressure
{
public:
  //  CONSTRUCTOR
  pressure(float value = 0.0)     { _pressure = value; };


  void  setMilliBar(float value)  { _pressure = value; };
  void  setBar(float value)       { _pressure = value * BAR2MILLIBAR; };
  void  setPSI(float value)       { _pressure = value * PSI2MILLIBAR; };
  void  setATM(float value)       { _pressure = value * ATM2MILLIBAR; }
  void  setDynes(float value)     { _pressure = value * DYNES2MILLIBAR; }
  void  setInchHg(float value)    { _pressure = value * INHG2MILLIBAR; }
  void  setInchH2O(float value)   { _pressure = value * INH2O2MILLIBAR; }
  void  setPascal(float value)    { _pressure = value * PASCAL2MILLIBAR; }
  void  setTORR(float value)      { _pressure = value * TORR2MILLIBAR; }
  void  setCmHg(float value)      { _pressure = value * CMHG2MILLIBAR; }
  void  setCmH2O(float value)     { _pressure = value * CMH2O2MILLIBAR; }
  void  setMSW(float value)       { _pressure = value * MSW2MILLIBAR; }
  void  setKGCM2(float value)     { _pressure = value * KGCM22MILLIBAR; }


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
  float getKGCM2()     { return _pressure * MILLIBAR2KGCM2; }


  ////////////////////////////////////////////////////////////
  //
  //  EXPERIMENTAL
  //  temperature in KELVIN !
  float change(float T1, float T2, float V1, float V2, float N1, float N2)
  {
    changeTemperatureKelvin(T1, T2);
    changeVolume(V1, V2);
    changeMole(N1, N2);
    return _pressure;
  }

  //  temperature must be in KELVIN!
  float changeTemperatureKelvin(float T1, float T2)
  {
    if ((T1 != T2) && (T1 > 0) && (T2 > 0))
    {
      _pressure *= (T2 / T1);
    }
    return _pressure;
  }

  float changeTemperatureCelsius(float T1, float T2)
  {
    T1 += 273.15;
    T2 += 273.15;
    if ((T1 != T2) && (T1 > 0) && (T2 > 0))
    {
      _pressure *= (T2 / T1);
    }
    return _pressure;
  }

  float changeTemperatureFahrenheit(float T1, float T2)
  {
    T1 = T1 * (5.0 / 9.0) + 290.93;
    T2 = T2 * (5.0 / 9.0) + 290.93;
    if ((T1 != T2) && (T1 > 0) && (T2 > 0))
    {
      _pressure *= (T2 / T1);
    }
    return _pressure;
  }

  //  volume must be in same units
  float changeVolume(float V1, float V2)
  {
    if ((V1 != V2) && (V1 > 0) && (V2 > 0))
    {
      _pressure *= (V1 / V2);
    }
    return _pressure;
  }

  //  moles must be in same units.
  float changeMole(float N1, float N2)
  {
    if ((N1 != N2) && (N1 > 0) && (N2 > 0))
    {
      _pressure *= (N2 / N1);
    }
    return _pressure;
  }


  ////////////////////////////////////////////////////////////
  //
  //  EXPERIMENTAL
  //
  float factor(float T1, float T2, float V1, float V2, float N1, float N2)
  {
    float f = factorTemperatureKelvin(T1, T2);
    f *= factorVolume(V1, V2);
    f *= factorMole(N1, N2);
    return f;
  }

  float factorTemperatureKelvin(float T1, float T2)
  {
    if ((T1 != T2) && (T1 > 0) && (T2 > 0))
    {
      return (T2 / T1);
    }
    return 1.0;
  }

  float factorTemperatureCelsius(float T1, float T2)
  {
    T1 += 273.15;
    T2 += 273.15;
    return factorTemperatureKelvin(T1, T2);
  }

  float factorTemperatureFahrenheit(float T1, float T2)
  {
    T1 = T1 * (5.0 / 9.0) + 290.93;
    T2 = T2 * (5.0 / 9.0) + 290.93;
    return factorTemperatureKelvin(T1, T2);
  }

  //  volume must be in same units
  float factorVolume(float V1, float V2)
  {
    if ((V1 != V2) && (V1 > 0) && (V2 > 0))
    {
      return (V1 / V2);
    }
    return 1.0;
  }

  //  moles must be in same units.
  float factorMole(float N1, float N2)
  {
    if ((N1 != N2) && (N1 > 0) && (N2 > 0))
    {
      return (N2 / N1);
    }
    return 1.0;
  }



private:
  float    _pressure;    //  millibar.
};


//  -- END OF FILE --

