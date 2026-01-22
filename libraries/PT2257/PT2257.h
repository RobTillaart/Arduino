#pragma once
//
//    FILE: PT2257.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-01-20
// VERSION: 0.1.1
// PURPOSE: Arduino library for the PT2257 two channel volume controller.
//     URL: https://github.com/RobTillaart/PT2257
//


#include "Arduino.h"
#include "Wire.h"


#define PT2257_LIB_VERSION         (F("0.1.1"))

//  ERROR CODES
//  values <> 0 are errors.
#define PT2257_OK                  0x00


class PT2257
{
public:
  PT2257(TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  Functions, datasheet p.6
  void     allOff();
  void     mute();
  void     muteOff();
  bool     isMuted();

  //  dB = 0..79
  bool     stereo(int dB);
  bool     left(int dB);
  bool     right(int dB);
  int      getLeft();
  int      getRight();

  //       DEBUG
  int      getLastError();


protected:
  uint8_t  _address = 0x2A;
  TwoWire* _wire;
  int      _write(uint8_t command);
  int      _write2(uint8_t val1, uint8_t val2);

  int      _left  = 79;  //  holds absolute value
  int      _right = 79;  //  holds absolute value
  bool     _muted = false;

  uint8_t  _error;
};


class PT2259 : public PT2257
{
public:
  PT2259(TwoWire *wire = &Wire);

  //  Functions, datasheet p.8
  void     allOff();
  void     mute();
  void     muteOff();
  void     muteLeft();
  void     muteRight();

  void     clearRegister();
};


//  -- END OF FILE --





