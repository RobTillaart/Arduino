#pragma once
//
//    FILE: AngleConvertor.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-12-01
// PURPOSE: angle conversion class
//     URL: https://github.com/RobTillaart/AngleCOnvertor


#include "Arduino.h"


#define ANGLECONVERTOR_LIB_VERSION        (F("0.1.0"))


/////////////////////////////////////////////////////////////
//
//  ANGLE CONVERTER CLASS
//
class AngleConvertor
{
public:
  AngleConvertor()  { _v = 0; };

  //  SETTERS
  void setDegrees(float value = 0)       { _v = value * (M_PI / 180.0); };
  void setRadians(float value = 0)       { _v = value; };
  void setGradians(float value = 0)      { _v = value * (M_PI / 200.0); };
  void setAngularMil(float value = 0)    { _v = value * (M_PI / 3200.0); };
  void setBinaryRadians(float value = 0) { _v = value * (M_PI / 128.0); };
  void setCentiTurn(float value = 0)     { _v = value * (M_PI / 50.0); };
  void setDiameterPart(float value = 0)  { _v = value * (M_PI / 60.0); };
  void setHexacontade(float value = 0)   { _v = value * (M_PI / 30.0); };
  void setHourAngle(float value = 0)     { _v = value * (M_PI / 12.0); };
  void setMilliTurn(float value = 0)     { _v = value * (M_PI / 500.0); };
  
  void setMinuteTime(float value = 0)    { _v = value * (M_PI / 720.0); };
  void setOctant(float value = 0)        { _v = value * (M_PI / 4.0); };
  void setPechus(float value = 0)        { _v = value * (M_PI / 90.0); };    //  assumes 2°
  void setPoints(float value = 0)        { _v = value * (M_PI / 16.0); };
  void setQuadrant(float value = 0)      { _v = value * (M_PI / 2.0); };
  void setQuarterPoint(float value = 0)  { _v = value * (M_PI / 64.0); };
  void setSecondsTime(float value = 0)   { _v = value * (M_PI / 43200); };
  void setSextant(float value = 0)       { _v = value * (M_PI / 3.0); };
  void setSign(float value = 0)          { _v = value * (M_PI / 6.0); };
  void setTurn(float value = 0)          { _v = value * (M_PI / 0.5); };


  //  GETTERS
  float getDegrees()        { return _v * (180.0  / M_PI); };
  float getRadians()        { return _v; };
  float getGradians()       { return _v * (200.0  / M_PI); };
  float getAngularMil()     { return _v * (3200.0 / M_PI); };
  float getBinaryRadians()  { return _v * (128.0  / M_PI); };
  float getCentiTurn()      { return _v * (50.0   / M_PI); };
  float getDiameterPart()   { return _v * (60.0   / M_PI); };
  float getHexacontade()    { return _v * (30.0   / M_PI); };
  float getHourAngle()      { return _v * (12.0   / M_PI); };
  float getMilliTurn()      { return _v * (500.0  / M_PI); };
  
  float getMinuteTime()     { return _v * (720.0  / M_PI); };
  float getOctant()         { return _v * (4.0    / M_PI); };
  float getPechus()         { return _v * (90.0   / M_PI); };     //  assumes 2°
  float getPoints()         { return _v * (16.0   / M_PI); };
  float getQuadrant()       { return _v * (2.0    / M_PI); };
  float getQuarterPoint()   { return _v * (64.0   / M_PI); };
  float getSecondsTime()    { return _v * (43200  / M_PI); };
  float getSextant()        { return _v * (3.0    / M_PI); };
  float getSign()           { return _v * (6.0    / M_PI); };
  float getTurn()           { return _v * (0.5    / M_PI); };


private:
  float _v;  // internal use radians.
};


//  -- END OF FILE --

