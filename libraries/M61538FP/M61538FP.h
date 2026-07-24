#pragma once
//
//    FILE: M61538FP.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-07-23
// VERSION: 0.1.0
// PURPOSE: Arduino library for M61538FP 6 channel audio volume processor.
//     URL: https://github.com/RobTillaart/M61538FP

// https://forum.arduino.cc/t/controlling-m61538f-ic-with-arduino/1452974

#include "Arduino.h"



#define M61538FP_LIB_VERSION                   (F("0.1.0"))

//  adjust to speed up performance.
const uint16_t PULSE_DELAY = 4;


class M61538FP
{
public:
  M61538FP(uint8_t dataPin, uint8_t clockPin)
  {
    _dataPin = dataPin;
    _clockPin = clockPin;
  }

  void begin()
  {
    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_dataPin, LOW);
    digitalWrite(_clockPin, LOW);
  }

  void setVolumeFrontLeftRight(uint16_t left, uint16_t right)
  {
    if (left > 96) left = 96;
    if (right > 96) right = 96;
    _volumeFrontLeft = left;
    _volumeFrontRight = right;
    //  note: data is build up in reverse (page 7, datasheet)
    uint16_t data = (left << 9) | (right << 2) | 0x00;
    sendData(data);
  }

  void setVolumeRearLeftRight(uint16_t left, uint16_t right)
  {
    if (left > 96) left = 96;
    if (right > 96) right = 96;
    _volumeRearLeft = left;
    _volumeRearRight = right;
    //  note: data is build up in reverse (page 7, datasheet)
    uint16_t data = (left << 9) | (right << 2) | 0x01;
    sendData(data);
  }

  void setVolumeCenterWoofer(uint16_t center, uint16_t woofer)
  {
    if (center > 96) center = 96;
    if (woofer > 96) woofer = 96;
    _volumeCenter = center;
    _volumeWoofer = woofer;
    //  note: data is build up in reverse (page 7, datasheet)
    uint16_t data = (center << 9) | (woofer << 2) | 0x02;
    sendData(data);
  }

  void setVolumeAll(uint16_t left, uint16_t right, uint16_t center, uint16_t woofer, uint16_t rearLeft, uint16_t rearRight)
  {
    setVolumeFrontLeftRight(left, right);
    setVolumeCenterWoofer(center, woofer);
    setVolumeRearLeftRight(rearLeft, rearRight);
  }

  void muteAll()
  {
    setVolumeFrontLeftRight(0, 0);
    setVolumeCenterWoofer(0, 0);
    setVolumeRearLeftRight(0, 0);
  }

  //  SETTERS per channel reusing cached values
  void setVolumeFrontLeft(uint16_t vol)
  {
    setVolumeFrontLeftRight(vol, _volumeFrontRight);
  }

  void setVolumeFrontRight(uint16_t vol)
  {
    setVolumeFrontLeftRight(_volumeFrontLeft, vol);
  }

  void setVolumeCenter(uint16_t vol)
  {
    setVolumeCenterWoofer(vol, _volumeWoofer);
  }

  void setVolumeWoofer(uint16_t vol)
  {
    setVolumeCenterWoofer(_volumeCenter, vol);
  }

  void setVolumeRearLeft(uint16_t vol)
  {
    setVolumeRearLeftRight(vol, _volumeRearRight);
  }

  void setVolumeRearRight(uint16_t vol)
  {
    setVolumeRearLeftRight(_volumeRearLeft, vol);
  }


  //  GETTERS for the cached volume
  uint8_t getVolumeFrontLeft()  { return _volumeFrontLeft; };
  uint8_t getVolumeFrontRight() { return _volumeFrontRight; };
  uint8_t getVolumeCenter()     { return _volumeCenter; };
  uint8_t getVolumeWoofer()     { return _volumeWoofer; };
  uint8_t getVolumeRearLeft()   { return _volumeRearLeft; };
  uint8_t getVolumeRearRight()  { return _volumeRearRight; };



private:
  void sendData(uint16_t data)
  {
    //  note: MSB first as data is reversed
    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      digitalWrite(_dataPin, data & mask ? HIGH : LOW);
      digitalWrite(_clockPin, HIGH);
      if (PULSE_DELAY) delayMicroseconds(PULSE_DELAY);
      if (mask == 0x0001)  //  last bit => latch
      {
        digitalWrite(_dataPin, HIGH);
        if (PULSE_DELAY) delayMicroseconds(PULSE_DELAY);
      }
      digitalWrite(_clockPin, LOW);
      if (PULSE_DELAY) delayMicroseconds(PULSE_DELAY);
    }
    digitalWrite(_dataPin, LOW);
  }

  uint8_t  _dataPin;
  uint8_t  _clockPin;

  uint8_t  _volumeFrontLeft = 0;
  uint8_t  _volumeFrontRight = 0;
  uint8_t  _volumeCenter = 0;
  uint8_t  _volumeWoofer = 0;
  uint8_t  _volumeRearLeft = 0;
  uint8_t  _volumeRearRight = 0;
};


//  -- END OF FILE --
