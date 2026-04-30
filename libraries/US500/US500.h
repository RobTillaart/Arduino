#pragma once
//
//    FILE: US500.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-29
// VERSION: 0.1.0
// PURPOSE: Arduino library for US500 underwater distance sensor.
//     URL: https://github.com/RobTillaart/US500
//          https://www.tinytronics.nl/nl/sensoren/afstand/pono-us500-hx-onderwater-ultrasone-afstandssensor-uart-50cm


#include "Arduino.h"


#define US500_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values < 0 are errors.
constexpr int US500_CMD_ERROR = -1;
constexpr int US500_CRC_ERROR = -2;
constexpr int US500_TIMEOUT_ERROR = -3;


class US500
{
public:
  US500(Stream * str);
  uint16_t getAddress();

  float getDistance();                      //  in cm.
  int   setMaxDistance(uint16_t distance);  //  in 0.1 mm
  float getTemperature();                   //  in degrees C
  void  startMeasurement();  //  idem.
  void  stopMeasurement();   //  idem.

  void  flush();

protected:
  Stream * _stream;
  char     _buffer[16];
  uint16_t _address = 0x0005;

  void  _command(uint8_t * arr, uint8_t TXsize);
  int   _request(uint8_t * arr, uint8_t TXsize, uint8_t RXsize);
};


/*
TODO
class US4000 : public US500
{
public:
  US4000() : US500()
  {
    _address = 0x0A;
  }
  
int setMaxDistance() { return 0x01; };  //  not supported...
}
*/


//  -- END OF FILE --





