#pragma once
//
//    FILE: weight.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: Collection weight conversion functions
//     URL: https://github.com/RobTillaart/weight


#include "Arduino.h"


#define WEIGHT_LIB_VERSION        (F("0.3.1"))


/////////////////////////////////////////////////////////////
//
//  WEIGHT CONVERSION FUNCTIONS
//
float lbs2kilo(float lbs)     { return lbs   * 0.45359237; };
float kilo2lbs(float kilos)   { return kilos * 2.20462262185; };

float ounce2gram(float ounce) { return ounce * 28.349523125; };
float gram2ounce(float gram)  { return gram  * 0.03527396195; };

float gram2kilo(float gram)   { return gram  * 0.001; };
float kilo2gram( float kilo)  { return kilo  * 1000; };

float lbs2ounce(float lbs)    { return lbs   * 16; };
float ounce2lbs(float ounce)  { return ounce * 0.0625; };

float stone2lbs(float stone)  { return stone * 14; };
float lbs2stone(float lbs)    { return lbs   * 0.0714285714; };

float stone2kilo(float stone) { return stone * 6.35029318; };
float kilo2stone(float kilo)  { return kilo  * 0.157473044; };


//  returns kilo
float US2metric(float stone, float lbs, float ounce)
{
  float kilo = stone * 6.35029318;
  kilo += lbs * 0.45359237;
  kilo += ounce * (0.0625 * 0.45359237);
  return kilo;
};


//  returns lbs
float metric2US(float kilo, float &stone, float &lbs, float &ounce)
{
  float val = kilo * 2.20462262185;
  lbs = val;
  stone = int(lbs * 0.0714285714);
  lbs -= stone * 14;
  ounce = (lbs - int(lbs)) * 16;
  lbs = int(lbs);
  return val;
}


/////////////////////////////////////////////////////////////
//
//  WEIGHT CONVERTER CLASS
//
class weightConverter
{
public:
  weightConverter()                    { _w = 0; };

  //  SETTERS
  void setKilogram(float value = 0)    { _w = value * 1000; };
  void setGram(float value = 0)        { _w = value; };
  void setLBS(float value = 0)         { _w = value * 453.59237; };
  void setStone(float value = 0)       { _w = value * 6350.29318; };
  void setOunce(float value = 0)       { _w = value * 28.349523125; };
  void setLongTonUK(float value = 0)   { _w = value * 1016046.9088; };
  void setShortTonUS(float value = 0)  { _w = value * 907184.74; };
  void setQuarterUK(float value = 0)   { _w = value * 12700.58636; };
  void setQuarterUS(float value = 0)   { _w = value * 11339.80925; };
  void setSlug(float value = 0)        { _w = value * 14593.903; };
  void setTroyPound(float value = 0)   { _w = value * 373.2417216; };
  void setTroyOunce(float value = 0)   { _w = value * 31.1034768; };
  void setRobie(float value = 0)       { _w = value * 10; };
  void setDram(float value = 0)        { _w = value * 1.77184519531; };
  void setDrachme(float value = 0)     { _w = value * 3.8; };
  void setPoint(float value = 0)       { _w = value * 0.002; };
  void setGrain(float value = 0)       { _w = value * 0.0647989; };
  void setCarat(float value = 0)       { _w = value * 0.2; };


  //  ADDERS
  void addKilogram(float value = 0)    { _w += value * 1000; };
  void addGram(float value = 0)        { _w += value; };
  void addLBS(float value = 0)         { _w += value * 453.59237; };
  void addStone(float value = 0)       { _w += value * 6350.29318; };
  void addOunce(float value = 0)       { _w += value * 28.349523125; };
  void addLongTonUK(float value = 0)   { _w += value * 1016046.9088; };
  void addShortTonUS(float value = 0)  { _w += value * 907184.74; };
  void addQuarterUK(float value = 0)   { _w += value * 12700.58636; };
  void addQuarterUS(float value = 0)   { _w += value * 11339.80925; };
  void addSlug(float value = 0)        { _w += value * 14593.903; };
  void addTroyPound(float value = 0)   { _w += value * 373.2417216; };
  void addTroyOunce(float value = 0)   { _w += value * 31.1034768; };
  void addRobie(float value = 0)       { _w += value * 10; };
  void addDram(float value = 0)        { _w += value * 1.77184519531; };
  void addDrachme(float value = 0)     { _w += value * 3.8; };
  void addPoint(float value = 0)       { _w += value * 0.002; };
  void addGrain(float value = 0)       { _w += value * 0.0647989; };
  void addCarat(float value = 0)       { _w += value * 0.2; };


  //  GETTERS
  float getKilogram()   { return _w * 0.001; }
  float getGram()       { return _w; }
  float getLBS()        { return _w * 0.00220462262185; }
  float getStone()      { return _w * 0.000157473044418;}
  float getOunce()      { return _w * 0.03527396195;  }
  float getLongTonUK()  { return _w * 9.84206527611e-7;};
  float getShortTonUS() { return _w * 0.00000110231131092;};
  float getQuarterUK()  { return _w * 0.0000787365222089;};
  float getQuarterUS()  { return _w * 0.000088184904874;};
  float getSlug()       { return _w * 0.000068521765562;};
  float getTroyPound()  { return _w * 0.00267922888072;};
  float getTroyOunce()  { return _w * 0.0321507465686;};
  float getRobie()      { return _w * 0.1;};
  float getDram()       { return _w * 0.564383391193;};
  float getDrachme()    { return _w * 0.263157894737;};
  float getPoint()      { return _w * 500;};
  float getGrain()      { return _w * 15.4323607345;};
  float getCarat()      { return _w * 5; };

  private:
    float _w;  //  grams
};


//  -- END OF FILE --

