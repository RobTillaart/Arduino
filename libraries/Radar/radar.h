//
//    FILE: radar.h
//  AUTHOR: Rob Tillaart
// VERSION: see RADAR_LIB_VERSION
// PURPOSE: pan tilt radar framework
//     URL:
//
// Released to the public domain
//

#ifndef Radar_h
#define Radar_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define RADAR_LIB_VERSION "0.1.01"

#define PAN_PER_SEC     25      // TODO determine emperically
#define TILT_PER_SEC    25      // TODO determine emperically

class RADAR
{
  public:
    RADAR(uint8_t, uint8_t);

    void gotoPan(int pan);
    int  getPan();
    void gotoTilt(int tilt);
    int  getTilt();
    void gotoPanTilt(int pan, int tilt);

    // memory positions
    void setPosition(uint8_t idx, int pan, int tilt);
    bool getPosition(uint8_t idx, int *pan, int *tilt);
    bool gotoPosition(uint8_t idx);
    void setHomePosition(int pan, int tilt);
    void gotoHomePosition();

    // 
    bool isMoving();

    unsigned long ping();
    unsigned long ping(int pan, int tilt);
    
  private:
    int _pinPan;
    int _pinTilt;
    
    int _prevPan;
    int _pan;
    int _homePan;
    unsigned long _lastPanTime;
    
    int _prevTilt;
    int _tilt;
    int _homeTilt;
    unsigned long _lastTiltTime;
    
    int _parray[10];
    int _tarry[10];
};

#endif
// -- END OF FILE --