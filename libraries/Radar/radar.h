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
  #include "SoftwareSerial.h"
#else
  #include "WProgram.h"
  #include "NewSoftSerial.h"
#endif

#define RADAR_LIB_VERSION "0.1.00"

#define PAN_PER_SEC     20      // TODO determine emperically
#define TILT_PER_SEC    10      // TODO determine emperically

class RADAR
{
  public:
    RADAR(int, int);

    void setPan(int pan);
    int getPan();
    void setTilt(int tilt);
    int getTilt();

    void setHomePosition(int pan, int tilt);
    void home();

    bool ready();

    unsigned long ping();
    unsigned long ping(int pan, int tilt);
    
  private:
    int _pinPan;
    int _pinTilt;
    
    int _prevPan;
    int _pan;
    int _homePan;
    unsigned long _lastPanTime 
    
    int _prevTilt;
    int _tilt;
    int _homeTilt;
    unsigned long _lastTiltTime 
};

#endif
// -- END OF FILE --