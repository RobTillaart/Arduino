#pragma once
//
//    FILE: AngleConvertor.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2022-12-01
// PURPOSE: Angle conversion class
//     URL: https://github.com/RobTillaart/AngleConvertor


#include "Arduino.h"


#define ANGLECONVERTOR_LIB_VERSION        (F("0.2.2"))


/////////////////////////////////////////////////////////////
//
//  ANGLE CONVERTER CLASS
//
class AngleConvertor
{
public:
  AngleConvertor() { _degrees = 0; };

  //  SETTERS
  void setDegrees(double value = 0)       { _degrees = value; };
  void setRadians(double value = 0)       { _degrees = value * (180.0 / M_PI); };
  void setGradians(double value = 0)      { _degrees = value * (180.0 / 200.0); };
  void setAngularMil(double value = 0)    { _degrees = value * (180.0 / 3200.0); };
  void setBinaryRadians(double value = 0) { _degrees = value * (180.0 / 128.0); };
  void setCentiTurn(double value = 0)     { _degrees = value * (180.0 / 50.0); };
  void setDiameterPart(double value = 0)  { _degrees = value * (180.0 / 60.0); };
  void setHexacontade(double value = 0)   { _degrees = value * (180.0 / 30.0); };
  void setHourAngle(double value = 0)     { _degrees = value * (180.0 / 12.0); };
  void setMilliRadians(double value = 0)  { _degrees = value * (180.0 / (M_PI * 1000.0)); };
  void setMilliTurn(double value = 0)     { _degrees = value * (180.0 / 500.0); };

  void setMinuteTime(double value = 0)    { _degrees = value * (180.0 / 720.0); };
  void setOctant(double value = 0)        { _degrees = value * (180.0 / 4.0); };
  void setPechus(double value = 0)        { _degrees = value * (180.0 / 90.0); };    //  assumes 2°
  void setPercent(double value = 0)       { _degrees = value * (180.0 / 50.0); };    //  equals centiTurn..
  void setPoints(double value = 0)        { _degrees = value * (180.0 / 16.0); };
  void setQuadrant(double value = 0)      { _degrees = value * (180.0 / 2.0); };
  void setQuarterPoint(double value = 0)  { _degrees = value * (180.0 / 64.0); };
  void setSecondsTime(double value = 0)   { _degrees = value * (180.0 / 43200); };
  void setSextant(double value = 0)       { _degrees = value * (180.0 / 3.0); };
  void setSign(double value = 0)          { _degrees = value * (180.0 / 6.0); };
  void setTurn(double value = 0)          { _degrees = value * (180.0 / 0.5); };


  //  GETTERS
  double getDegrees()        { return _degrees; };
  double getRadians()        { return _degrees * (M_PI   / 180.0); };
  double getGradians()       { return _degrees * (200.0  / 180.0); };
  double getAngularMil()     { return _degrees * (3200.0 / 180.0); };
  double getBinaryRadians()  { return _degrees * (128.0  / 180.0); };
  double getCentiTurn()      { return _degrees * (50.0   / 180.0); };
  double getDiameterPart()   { return _degrees * (60.0   / 180.0); };
  double getHexacontade()    { return _degrees * (30.0   / 180.0); };
  double getHourAngle()      { return _degrees * (12.0   / 180.0); };
  double getMilliRadians()   { return _degrees * (M_PI * 1000.0  / 180.0); };
  double getMilliTurn()      { return _degrees * (500.0  / 180.0); };

  double getMinuteTime()     { return _degrees * (720.0  / 180.0); };
  double getOctant()         { return _degrees * (4.0    / 180.0); };
  double getPechus()         { return _degrees * (90.0   / 180.0); };     //  assumes 2°
  double getPercent()        { return _degrees * (50.0   / 180.0); }
  double getPoints()         { return _degrees * (16.0   / 180.0); };
  double getQuadrant()       { return _degrees * (2.0    / 180.0); };
  double getQuarterPoint()   { return _degrees * (64.0   / 180.0); };
  double getSecondsTime()    { return _degrees * (43200  / 180.0); };
  double getSextant()        { return _degrees * (3.0    / 180.0); };
  double getSign()           { return _degrees * (6.0    / 180.0); };
  double getTurn()           { return _degrees * (0.5    / 180.0); };


  //  WINDROSE
  //
  char * windrose()
  {
    return windrose(_degrees);
  }

  char * windrose(double degrees)
  {
    uint8_t idx = (degrees + 11.25) * 0.044444444444444;  //  1.0 / 22.5
    return _windRose2[idx];
  }

private:
  double _degrees;  //  internal use degrees (0.2.0).
  char   _windRose2[17][4] = {
  "N","NNE","NE","ENE","E","ESE","SE","SSE","S","SSW","SW","WSW","W","WNW","NW","NNW", "N"};

};


//  -- END OF FILE --

