#pragma once
//
//    FILE: VolumeConverter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library to convert volume units.
//     URL: https://github.com/RobTillaart/VolumeConverter


#include "Arduino.h"


#define VOLUMECONVERTER_LIB_VERSION        (F("0.1.1"))


/////////////////////////////////////////////////////////////
//
//  VOLUME CONVERTER CLASS
//
class VolumeConverter
{
public:
  VolumeConverter()                     { _v = 0; };

  //  SETTERS
  void setLiters(float value = 0)       { _v = value; };
  void setMilliLiters(float value = 0)  { _v = value * 0.001; };
  void setCubicMeters(float value = 0)  { _v = value * 1000; };
  void setLongTons(float value = 0)     { _v = value * 1284.16209; };
  void setShortTons(float value = 0)    { _v = value * 906.98184; };
  void setBarrels(float value = 0)      { _v = value * 158.9868; };
  void setGallons(float value = 0)      { _v = value * 3.7854; };
  void setQuarts(float value = 0)       { _v = value * 0.94635296; };
  void setPints(float value = 0)        { _v = value * 0.47317648; };
  void setCups(float value = 0)         { _v = value * 0.23658824; };
  void setFluidOunces(float value = 0)  { _v = value * 0.02957353; };
  void setTableSpoons(float value = 0)  { _v = value * 0.01478677; };
  void setTeaSpoons(float value = 0)    { _v = value * 0.00492892; };


  //  ADDERS
  void addLiters(float value = 0)       { _v += value; };
  void addMilliLiters(float value = 0)  { _v += value * 0.001; };
  void addCubicMeters(float value = 0)  { _v += value * 1000; };
  void addLongTons(float value = 0)     { _v += value * 1284.16209; };
  void addShortTons(float value = 0)    { _v += value * 906.98184; };
  void addBarrels(float value = 0)      { _v += value * 158.9868; };
  void addGallons(float value = 0)      { _v += value * 3.7854; };
  void addQuarts(float value = 0)       { _v += value * 0.94635296; };
  void addPints(float value = 0)        { _v += value * 0.47317648; };
  void addCups(float value = 0)         { _v += value * 0.23658824; };
  void addFluidOunces(float value = 0)  { _v += value * 0.02957353; };
  void addTableSpoons(float value = 0)  { _v += value * 0.01478677; };
  void addTeaSpoons(float value = 0)    { _v += value * 0.00492892; };


  //  GETTERS
  float getLiters()                     { return _v; };
  float getMilliLiters()                { return _v * 1000; };
  float getCubicMeters()                { return _v * 0.001; };
  float getLongTons()                   { return _v * (1.0 / 1284.16209); };
  float getShortTons()                  { return _v * (1.0 / 906.98184); };
  float getBarrels()                    { return _v * (1.0 / 158.9868); };
  float getGallons()                    { return _v * (1.0 / 3.7854); };
  float getQuarts()                     { return _v * (1.0 / 0.94635296); };
  float getPints()                      { return _v * (1.0 / 0.47317648); };
  float getCups()                       { return _v * (1.0 / 0.23658824); };
  float getFluidOunces()                { return _v * (1.0 / 0.02957353); };
  float getTableSpoons()                { return _v * (1.0 / 0.01478677); };
  float getTeaSpoons()                  { return _v * (1.0 / 0.00492892); };


  private:
    float _v;  //  liters
};


//  -- END OF FILE --

