//
//    FILE: radar.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: Arduino library for a pan tilt radar.
//     URL: https://github.com/RobTillaart/RADAR
//
//  0.1.00  2013-09-30  (?) outline
//  0.1.01  2015-03-06  updated some code, still not functional
//  0.1.2   2017-07-16  refactor & review
//  0.1.3   2020-07-06  refactor, clean up and some documentation
//  0.1.4   2021-01-07  arduino-ci, unit-test


#include "radar.h"


////////////////////////////////////////////////////////////
//
// CONSTRUCTOR
//
RADAR::RADAR(const uint8_t pinPan, const uint8_t pinTilt)
{
  _pinPan = pinPan;
  _pinTilt = pinTilt;
  _homePan = 0;
  _homeTilt = 0;
  _pan = _prevPan = 0;
  _tilt = _prevTilt = 0;
  _panPerSecond = 15;
  _tiltPerSecond = 15;
  _lastPanTime = _lastTiltTime = millis();
  for (uint8_t i = 0; i < RADAR_POSITIONS; i++)
  {
    _panArray[i] = 0;
    _tiltArray[i] = 0;
  }
}


// PUBLIC
void RADAR::gotoPan(const int16_t pan)
{
  if (pan == _pan) return;
  _prevPan = getPan();
  _pan = pan;
  analogWrite(_pinPan, _pan);
  _lastPanTime = millis();
}


int16_t RADAR::getPan()
{
  // ESTIMATE current position on time it takes to go from previous to new
  if (_pan == _prevPan) return _pan;

  // if (enough time passed to move to new position) return new position
  uint32_t duration = millis() - _lastPanTime;
  uint32_t movement = round(duration * _panPerSecond * 0.001);
  if ( abs(_pan - _prevPan) <= movement) return _pan;

  // else estimate PAN by linear interpolation 
  if (_pan > _prevPan) return _prevPan + movement;
  return _prevPan - movement;
}


void RADAR::gotoTilt(const int16_t tilt)
{
  if (tilt == _tilt) return;

  _prevTilt = getTilt();
  _tilt = tilt;
  analogWrite(_pinTilt, _tilt);  // 0..180
  _lastTiltTime = millis();
}


int16_t RADAR::getTilt()
{
  // ESTIMATE current position on time it takes to go from previous to new
  if (_tilt == _prevTilt) return _tilt;

  // if (enough time passed to move to new position) return new position
  uint32_t duration = millis() - _lastTiltTime;
  uint32_t movement = round(duration * _tiltPerSecond * 0.001);
  if (abs(_tilt - _prevTilt) <= movement) return _tilt;

  // estimate TILT by linear interpolation 
  if (_tilt > _prevTilt) return _prevTilt + movement;  
  return _prevTilt - movement;
}


void RADAR::gotoPanTilt(const int16_t pan, const int16_t tilt)
{
  gotoPan(pan);
  gotoTilt(tilt);
}


bool RADAR::setPosition(const uint8_t n, const int16_t pan, const int16_t tilt)
{
  if (n >= RADAR_POSITIONS) return false;
  _panArray[n] = pan;
  _tiltArray[n] = tilt;
  return true;
}


bool RADAR::getPosition(const uint8_t n, int16_t & pan, int16_t & tilt)
{
  if (n >= RADAR_POSITIONS) return false;
  pan = _panArray[n];
  tilt = _tiltArray[n];
  return true;
}


bool RADAR::gotoPosition(const uint8_t n)
{
  if (n >= RADAR_POSITIONS) return false;
  gotoPan(_panArray[n]);
  gotoTilt(_tiltArray[n]);
  return true;
}


void RADAR::setHomePosition(const int16_t pan, const int16_t tilt)
{
  _homePan = pan;
  _homeTilt = tilt;
}


void RADAR::gotoHomePosition()
{
  gotoPan(_homePan);
  gotoTilt(_homeTilt);
}


uint32_t RADAR::ping()
{
  // TODO ping code here - playground or teckel's improved ping)))
  return 0;
}


uint32_t RADAR::ping(const int16_t pan, const int16_t tilt)
{
  gotoPan(pan);
  gotoTilt(tilt);
  while (isMoving());
  return ping();
}
// PRIVATE

// TODO distill private parts (getPan and getTilt share a lot

// -- END OF FILE --