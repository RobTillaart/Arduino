#pragma once
//
//    FILE: KT0803.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino Library for KT0803 and KT0803K FM transmitter
//     URL: https://github.com/RobTillaart/KT0803


#include "Arduino.h"
#include "Wire.h"


#define KT0803_LIB_VERSION          (F("0.3.0"))


class KT0803
{
public:
  KT0803(TwoWire * wire = &Wire);

  bool     begin(float freq = 90.0, bool mute = true);
  bool     isConnected();


  //  FM FREQUENCY (70-108)
  //  KT0803 truncates to 0.1 MHz
  //  KT0803K (L&M) truncates to 0.05 MHz
  bool     setFrequency(float MHz);
  float    getFrequency();


  //  FM CHANNEL (1400-2160)
  //  KT0803 only supports even channels
  //  KT0803K (L&M) supports all channels
  bool     setChannel(uint16_t channel);
  uint16_t getChannel();


  //  GAIN
  bool     setPGA(uint8_t pga);  //  0-3 = 0..-12dB   4-7 = 0..12dB
  // 111: 12dB
  // 110: 8dB
  // 101: 4dB
  // 100: 0dB
  // 000: 0dB
  // 001: -4dB
  // 010: -8dB
  // 011: -12dB
  uint8_t  getPGA();

  bool     setRFGain(uint8_t rfgain);  //  0-15
  uint8_t  getRFgain();


  //  REGION SELECTION
  //  first four are wrappers
  void     setEurope()    { setPHTCNST(true); };
  void     setAustralia() { setPHTCNST(true); };
  void     setUSA()       { setPHTCNST(false); };
  void     setJapan()     { setPHTCNST(false); };
  bool     setPHTCNST(bool on);
  bool     getPHTCNST();


  //  PILOT TONE ADJUST (PLTADJ)
  bool     setPilotToneAdjust(uint8_t mode);  //  HIGH = 1 LOW = 0
  uint8_t  getPilotToneAdjust();


  //  MUTE software
  bool     setMute(bool mute);  //  true == muted
  bool     getMute();           //  isMuted().


  //  direct access to registers - debug / develop
  //  to access not implemented functions.
  bool     writeData(uint8_t reg, uint8_t data);
  int      readData(uint8_t reg);

protected:

  uint8_t   _address = 0x3E;  //  fixed address for KT0803.
  TwoWire * _wire = NULL;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class KT0803K : public KT0803
{
public:
  KT0803K(TwoWire * wire = &Wire);

  //  CHANNEL
  bool     setChannel(uint16_t channel);
  uint16_t getChannel();

  //  KT0803K SPECIFIC
  bool     setMono();
  bool     setStereo();
  bool     isStereo();

  bool     setBass(uint8_t bass);  //  0..3 = 0, 5, 11, 17 dB
  uint8_t  getBass();

  bool     powerOK();
  bool     silenceDetected();
};


//  -- END OF FILE --

