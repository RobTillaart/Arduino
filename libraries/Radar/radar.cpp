//
//    FILE: radar.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: demo pan tilt radar framework
//     URL:
//
// Released to the public domain
//
// 0.1.00 - 2013-09-30 (?) outline
// 0.1.01 - 2015-03-06 updated some code, still not functional

#include "radar.h"

////////////////////////////////////////////////////////////
//
// CONSTRUCTOR
//
RADAR::RADAR(uint8_t pinPan, uint8_t pinTilt)
{
    _pinPan = pinPan;
    _pinTilt = pinTilt;
    _homePan = 0;
    _homeTilt = 0;
    _pan = _prevPan = 0;
    _tilt = _prevTilt = 0;
    _lastPanTime = _lastTiltTime = millis();
        
}

// PUBLIC
void RADAR::gotoPan(int pan)
{
    if (pan == _pan) return;
    _prevPan = getPan();
    _pan = pan;
    analogWrite(_pinPan, _pan);
    _lastPanTime = millis();
}

int RADAR::getPan()
{
    // ESTIMATE current position on time it takes to go from previous to new
    if (_pan == _prevPan) return _pan;
    // if (enough time passed to move to new position) return new position
    unsigned long duration = millis() - _lastPanTime;
    if ( abs(_pan - _prevPan) <= (duration * PAN_PER_SEC)/1000UL) return _pan;
    // else estimate by linear interpolation 
    if (_pan > _prevPan) return _prevPan + (duration * PAN_PER_SEC)/1000UL;
    return _prevPan - (duration * PAN_PER_SEC)/1000UL;
}

void RADAR::gotoTilt(int tilt)
{
    if (tilt == _tilt) return;
    _prevTilt = getTilt();
    _tilt = tilt;
    analogWrite(_pinTilt, _tilt);
    _lastTiltTime = millis();
}

int RADAR::getTilt()
{
    // comments see getPan()
    if (_tilt == _prevTilt) return _tilt;
    unsigned long duration = millis() - _lastTiltTime;
    if (abs(_tilt - _prevTilt) <= (duration * TILT_PER_SEC)/1000UL) return _tilt;
    if (_tilt > _prevTilt) return _prevTilt + (duration * TILT_PER_SEC)/1000UL;
    return _prevTilt - (duration * TILT_PER_SEC)/1000UL;
}

void RADAR::gotoPanTilt(int pan, int tilt)
{
    gotoPan(pan);
    gotoTilt(tilt);
}

void RADAR::setPosition(uint8_t n, int pan, int tilt)
{
    _parray[n] = pan;
    _tarry[n] = tilt;
}

bool RADAR::getPosition(uint8_t n, int *pan, int *tilt)
{
    if (n > 10) return false;
    *pan = _parray[n];
    *tilt = _tarry[n];
    return true;
}

bool RADAR::gotoPosition(uint8_t n)
{
    if (n > 10) return false;
    gotoPan(_parray[n]);
    gotoTilt(_tarry[n]);
    return true;
}

void RADAR::setHomePosition(int pan, int tilt)
{
    _homePan = pan;
    _homeTilt = tilt;
}

void RADAR::gotoHomePosition()
{
    gotoPan(_homePan);
    gotoTilt(_homeTilt);
}

bool RADAR::isMoving()
{
    return ((getPan() != _pan) || (getTilt() != _tilt));
}

unsigned long RADAR::ping()
{
  // TODO ping code here - playground or teckel's improved ping)))
  return 0;
}

unsigned long RADAR::ping(int pan, int tilt)
{
  gotoPan(pan);
  gotoTilt(tilt);
  while (isMoving());
  return ping();
}
// PRIVATE

// TODO distill private parts (getPan and getTilt share a lot

// -- END OF FILE --