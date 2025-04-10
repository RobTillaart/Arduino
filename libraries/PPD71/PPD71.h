#pragma once
//
//    FILE: PPD71.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for PPD71
//    DATE: 2025-04-09
//     URL: https://github.com/RobTillaart/PPD71


#include "Arduino.h"

#define PPD71_LIB_VERSION       (F("0.1.0"))

//  special bytes
//  #define PPD71_STX     0x02
//  #define PPD71_ETX     0x03
//  #define PPD71_DATA    0x10
//  #define PPD71_PROD    0x12
//  #define PPD71_EOT     0x04


class PPD71
{
public:
  PPD71(Stream* stream)
  {
    _stream = stream;
  };

  //  DATA
  bool dataAvailable()
  {
    return _stream->available() >= 29;
  };

  void dataFlush()
  {
    while (_stream->available()) _stream->read();
  };

  bool getData()
  {
    //  wait until enough data.
    if (!dataAvailable()) return false;
    int c;
    //  find start byte.
    while ( (_stream->available() > 0) && (_stream->peek() != 0x02))  //  STX
    {
      _stream->read();
    }
    if (!dataAvailable()) return false;

    //  pos = 0
    c = _stream->read();  //  STX
    c = _stream->read();  //  number of bytes till EOT (0x1B = 27?)
    //  Serial.println(c, HEX);
    c = _stream->read();  //  command 0x10
    if (c != 0x10)
    {
      dataFlush();
      return false;
    }

    //  pos = 3
    //  read 4x average
    for (int i = 0; i < 4; i++)
    {
      _average[i] = 256 * _stream->read();
      _average[i] += _stream->read();
    }

    //  pos = 11
    //  read 4x pulse ratio output
    for (int i = 0; i < 4; i++)
    {
      _pulseRatio[i] = 256 * _stream->read();
      _pulseRatio[i] += _stream->read();
    }

    //  pos = 19
    //  read status
    _status = 256 * _stream->read();
    _status += _stream->read();

    //  pos = 21
    //  read SW version
    _version = _stream->read();

    //  pos = 22
    //  read production number
    for (int i = 0; i < 4; i++)
    {
      _product <<= 8;
      _product += _stream->read();
    }

    //  pos = 16
    c = _stream->read();  //  ETX
    c = _stream->read();  //  checksum
    c = _stream->read();  //  EOT
    return true;
  };

  //  AVERAGE
  uint16_t getAverage10()  { return _average[0]; };
  uint16_t getAverage30()  { return _average[1]; };
  uint16_t getAverage60()  { return _average[2]; };
  uint16_t getAverage180() { return _average[3]; };

  //  PULSE RATIO
  uint16_t getPulseRatio05() { return _pulseRatio[0]; };
  uint16_t getPulseRatio07() { return _pulseRatio[1]; };
  uint16_t getPulseRatio10() { return _pulseRatio[2]; };
  uint16_t getPulseRatio25() { return _pulseRatio[3]; };

  //  STATUS (meaning unknown)
  uint16_t getStatus() { return _status; };

  //  META INFO
  uint16_t getSWVersion() { return _version; };
  uint16_t getProductNumber() { return _product; };


private:
  Stream * _stream  = NULL;

  void     _skip(int n)
  {
    while(n--) _stream->read();
  };

  uint16_t _average[4] = { 0, 0, 0, 0 };
  uint16_t _pulseRatio[4] = { 0, 0, 0, 0 };
  uint16_t _status = 0;
  uint8_t  _version = 0;
  uint32_t _product = 0;
};


//  https://www.shinyei.co.jp/stc/eng/products/optical/ppd71.html
//  https://forum.arduino.cc/t/integration-of-a-ppd-71-sensor/1371827

