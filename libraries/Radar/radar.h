#pragma once
//
//    FILE: radar.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.8
// PURPOSE: Arduino library for a pan tilt radar.
//     URL: https://github.com/RobTillaart/RADAR


#include "Arduino.h"


#define RADAR_LIB_VERSION         (F("0.1.8"))


//  TODO # positions in a begin() or constructor?
#ifndef RADAR_POSITIONS
#define RADAR_POSITIONS           10
#endif


class RADAR
{
public:
  RADAR(const uint8_t pinPan, const uint8_t pinTilt);


  //  no valid range checking or negative value check.
  void     setPanPerSecond(float pps)  { _panPerSecond = pps; };
  float    getPanPerSecond()           { return _panPerSecond; };
  void     setTiltPerSecond(float tps) { _tiltPerSecond = tps; };
  float    getTiltPerSecond()          { return _tiltPerSecond; };


  //  basic moves
  void     gotoPan(const int16_t pan);
  int16_t  getPan();
  void     gotoTilt(const int16_t tilt);
  int16_t  getTilt();
  void     gotoPanTilt(const int16_t pan, const int16_t tilt);


  //  memory positions - store / recall?
  uint8_t  getMaxPositions()            { return RADAR_POSITIONS; };
  bool     setPosition(const uint8_t index, const int16_t pan, const int16_t tilt);
  bool     getPosition(const uint8_t index, int16_t & pan, int16_t & tilt);
  bool     gotoPosition(const uint8_t index);
  void     setHomePosition(const int16_t pan, const int16_t tilt);
  void     gotoHomePosition();


  //  feedback on positions.
  bool     isMoving()     { return isPanMoving() || isTiltMoving(); };
  bool     isPanMoving()  { return getPan() != _pan; };
  bool     isTiltMoving() { return getTilt() != _tilt; };


  //  TODO NIY
  uint32_t ping();
  uint32_t ping(const int16_t pan, const int16_t tilt);


private:
  int16_t  _pinPan;
  int16_t  _pinTilt;

  int16_t  _prevPan;
  int16_t  _pan;
  int16_t  _homePan;
  uint32_t _lastPanTime;

  int16_t  _prevTilt;
  int16_t  _tilt;
  int16_t  _homeTilt;
  uint32_t _lastTiltTime;

  int16_t  _panArray[RADAR_POSITIONS];
  int16_t  _tiltArray[RADAR_POSITIONS];

  float    _panPerSecond = 15;
  float    _tiltPerSecond = 15;
};


//  -- END OF FILE --
