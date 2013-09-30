//
//    FILE: radar.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: pan tilt radar framework
//     URL:
//
// Released to the public domain
//

#include "radar.h"

////////////////////////////////////////////////////////////
//
// CONSTRUCTOR
//
RADAR::RADAR(int pinPan, int pinTilt)
{
    _pinPan = pinPan;
    _pinTilt = pinTilt;
}

// PUBLIC
void RADAR::setPan(int pan)
{
    _prevPan = _pan;  // remember last postion // TODO should in fact be getPan() to get current position.
    _pan = pan;
    digitalWrite(_pinPan, pan);
    _lastPanTime = millis();
}

int RADAR::getPan()
{
    // ESTIMATE current pan on time it takes to go from _prevPan to _pan
    // and the time since setPan ==> millis() - _lastPanTime
    // 
    // TODO CHECK MATH 

    unsigned long duration = millis() - lastPanTime;

    int pan = 0;

    if (duration >= abs(_pan - _prevPan) * PAN_PER_SEC/1000) pan = _pan;
    else if (_pan > _prevpan) pan = _pan - duration * PAN_PER_SEC/1000;
    else pan = _pan - duration * PAN_PER_SEC/1000;

    return pan;
}

void RADAR::setTilt(int tilt)
{
    _prevTilt = _tilt;
    _tilt = tilt;
    digitalWrite(_pinTilt, tilt);
    _lastTiltTime = millis();
}

int RADAR::getTilt()
{
    // TODO see pan
    return 0;
}

// TODO extend this to an array of 10 memory positions
void setHomePosition(int pan, int tilt)
{
    _homePan = pan;
    _homeTilt = tilt;
}

void home()
{
    setPan(_homePan);
    setTilt(_homeTilt);
}

bool RADAR::ready()
{
    return ((getPan() == _pan) && (getTilt == _tilt));
}

unsigned long RADAR::ping()
{
  // TODO ping code here - playground or teckel's improved ping)))
  return 0;
}

unsigned long RADAR::ping(int pan, int tilt)
{
  setPan(pan);
  setTilt(tilt);
  while (!ready());
  return ping();
}
// PRIVATE

// TODO distill private parts (getPan and getTilt share a lot

// -- END OF FILE --