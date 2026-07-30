#pragma once
//
//    FILE: M61538FP.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-07-23
// VERSION: 0.1.2
// PURPOSE: Arduino library for M61538FP 6 channel audio volume processor.
//     URL: https://github.com/RobTillaart/M61538FP

// https://forum.arduino.cc/t/controlling-m61538f-ic-with-arduino/1452974


#include "Arduino.h"


#define M61538FP_LIB_VERSION                   (F("0.1.2"))

//  adjust if needed (4 us pulse is minimum).
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


  //
  //  VOLUME PAIRS API
  //
  //  Volume 0 = silent; 100 = full open
  void setVolumeFrontLeftRight(uint16_t left, uint16_t right)
  {
    //  constrain
    if (left > 100)  left  = 100;
    if (right > 100) right = 100;
    //  convert volume to attenuation
    if (left == 0) left = 96;
    else left  = 92 - 20 * log(left);
    if (right == 0) right = 96;
    else right = 92 - 20 * log(right);
    setAttnFrontLeftRight(left, right);
  }

  void setVolumeRearLeftRight(uint16_t left, uint16_t right)
  {
    //  constrain
    if (left > 100)  left  = 100;
    if (right > 100) right = 100;
    //  convert volume to attenuation
    if (left == 0) left = 96;
    else left  = 92 - 20 * log(left);
    if (right == 0) right = 96;
    else right = 92 - 20 * log(right);
    setAttnRearLeftRight(left, right);
  }

  void setVolumeCenterWoofer(uint16_t center, uint16_t woofer)
  {
    if (center > 100) center = 100;
    if (woofer > 100) woofer = 100;
    //  convert volume to attenuation
    if (center == 0) center = 96;
    else center = 92 - 20 * log(center);
    if (woofer == 0) woofer = 96;
    else woofer = 92 - 20 * log(woofer);
    setAttnCenterWoofer(center, woofer);
  }


  //
  //  ATTN PAIRS API
  //
  //  Attenuation  0dB = full open; 96dB = silent.
  void setAttnFrontLeftRight(uint16_t left, uint16_t right)
  {
    //  constrain
    if (left > 96)  left  = 96;
    if (right > 96) right = 96;
    //  remember volume
    _attnFrontLeft = left;
    _attnFrontRight = right;
    //  note: data is build up in reverse (page 7, datasheet)
    uint16_t data = (left << 9) | (right << 2) | 0x00;
    sendData(data);
  }

  void setAttnRearLeftRight(uint16_t left, uint16_t right)
  {
    //  constrain
    if (left > 96)  left  = 96;
    if (right > 96) right = 96;
    //  remember volume
    _attnRearLeft = left;
    _attnRearRight = right;
    //  note: data is build up in reverse (page 7, datasheet)
    uint16_t data = (left << 9) | (right << 2) | 0x01;
    sendData(data);
  }

  void setAttnCenterWoofer(uint16_t center, uint16_t woofer)
  {
    //  constrain
    if (center > 96) center = 96;
    if (woofer > 96) woofer = 96;
    //  remember volume
    _attnCenter = center;
    _attnWoofer = woofer;
    //  note: data is build up in reverse (page 7, datasheet)
    uint16_t data = (center << 9) | (woofer << 2) | 0x02;
    sendData(data);
  }


  //
  //  WRAPPERS
  //
  void setVolumeAll(uint16_t left, uint16_t right, uint16_t center, uint16_t woofer, uint16_t rearLeft, uint16_t rearRight)
  {
    setVolumeFrontLeftRight(left, right);
    setVolumeCenterWoofer(center, woofer);
    setVolumeRearLeftRight(rearLeft, rearRight);
  }

  void setAttnAll(uint16_t left, uint16_t right, uint16_t center, uint16_t woofer, uint16_t rearLeft, uint16_t rearRight)
  {
    setAttnFrontLeftRight(left, right);
    setAttnCenterWoofer(center, woofer);
    setAttnRearLeftRight(rearLeft, rearRight);
  }

  void muteAll()
  {
    setAttnFrontLeftRight(96, 96);
    setAttnCenterWoofer(96, 96);
    setAttnRearLeftRight(96, 96);
  }

  //  PREP UNMUTE, cache may not be overwritten with zero's
  // void unmuteAll()
  // {
    // setAttnFrontLeftRight(_attnFrontLeft, _attnFrontRight);
    // setAttnCenterWoofer(_attnCenter, _attnWoofer);
    // setAttnRearLeftRight(_attnRearLeft, _attnRearRight);
  // }


  //
  //  VOLUME SETTERS per channel reusing cached values
  //
  void setVolumeFrontLeft(uint16_t volume)
  {
    if (volume > 100) volume = 100;
    setAttnFrontLeftRight(V2A(volume), _attnFrontRight);
  }

  void setVolumeFrontRight(uint16_t volume)
  {
    if (volume > 100) volume = 100;
    setAttnFrontLeftRight(_attnFrontLeft, V2A(volume));
  }

  void setVolumeCenter(uint16_t volume)
  {
    if (volume > 100) volume = 100;
    setAttnCenterWoofer(V2A(volume), _attnWoofer);
  }

  void setVolumeWoofer(uint16_t volume)
  {
    if (volume > 100) volume = 100;
    setAttnCenterWoofer(_attnCenter, V2A(volume));
  }

  void setVolumeRearLeft(uint16_t volume)
  {
    if (volume > 100) volume = 100;
    setAttnRearLeftRight(V2A(volume), _attnRearRight);
  }

  void setVolumeRearRight(uint16_t volume)
  {
    if (volume > 100)  volume  = 100;
    setAttnRearLeftRight(_attnRearLeft, V2A(volume));
  }


  //
  //  ATTN SETTERS per channel reusing cached values
  //
  void setAttnFrontLeft(uint16_t attn)
  {
    setAttnFrontLeftRight(attn, _attnFrontRight);
  }

  void setAttnFrontRight(uint16_t attn)
  {
    setAttnFrontLeftRight(_attnFrontLeft, attn);
  }

  void setAttnCenter(uint16_t attn)
  {
    setAttnCenterWoofer(attn, _attnWoofer);
  }

  void setAttnWoofer(uint16_t attn)
  {
    setAttnCenterWoofer(_attnCenter, attn);
  }

  void setAttnRearLeft(uint16_t attn)
  {
    setAttnRearLeftRight(attn, _attnRearRight);
  }

  void setAttnRearRight(uint16_t attn)
  {
    setAttnRearLeftRight(_attnRearLeft, attn);
  }


  //
  //  VOLUME GETTERS for the cache
  //
  uint8_t getVolumeFrontLeft()  { return A2V(_attnFrontLeft); };
  uint8_t getVolumeFrontRight() { return A2V(_attnFrontRight); };
  uint8_t getVolumeCenter()     { return A2V(_attnCenter); };
  uint8_t getVolumeWoofer()     { return A2V(_attnWoofer); };
  uint8_t getVolumeRearLeft()   { return A2V(_attnRearLeft); };
  uint8_t getVolumeRearRight()  { return A2V(_attnRearRight); };


  //
  //  ATTN GETTERS for the cache
  //
  uint8_t getAttnFrontLeft()  { return _attnFrontLeft; };
  uint8_t getAttnFrontRight() { return _attnFrontRight; };
  uint8_t getAttnCenter()     { return _attnCenter; };
  uint8_t getAttnWoofer()     { return _attnWoofer; };
  uint8_t getAttnRearLeft()   { return _attnRearLeft; };
  uint8_t getAttnRearRight()  { return _attnRearRight; };


//
//  PRIVATE
//
private:
  void sendData(uint16_t data)
  {
    //  note: MSB first as data is reversed
    for (uint16_t mask = 0x8000; mask; mask >>= 1)
    {
      //  check bits written
      //  Serial.print( data & mask ? HIGH : LOW);
      digitalWrite(_dataPin, data & mask ? HIGH : LOW);
      digitalWrite(_clockPin, HIGH);
      if (PULSE_DELAY) delayMicroseconds(PULSE_DELAY);
      if (mask == 0x0001)  //  last bit => latch
      {
        //  Serial.println("LATCH");
        digitalWrite(_dataPin, HIGH);
        if (PULSE_DELAY) delayMicroseconds(PULSE_DELAY);
      }
      digitalWrite(_clockPin, LOW);
      if (PULSE_DELAY) delayMicroseconds(PULSE_DELAY);
    }
    //  newline after all bits.
    //  Serial.println();
    digitalWrite(_dataPin, LOW);
  }

  //  CONVERTORS.
  inline float A2V(float attn)
  {
    return round(100.0f * exp(-0.05f * attn));
  }

  inline float V2A(float volume)
  {
    if (volume == 0) return 96;
    return 92 - 20 * log(volume);
  }


  uint8_t  _dataPin;
  uint8_t  _clockPin;

  uint8_t  _attnFrontLeft  = 0;
  uint8_t  _attnFrontRight = 0;
  uint8_t  _attnCenter     = 0;
  uint8_t  _attnWoofer     = 0;
  uint8_t  _attnRearLeft   = 0;
  uint8_t  _attnRearRight  = 0;
};


//  -- END OF FILE --
