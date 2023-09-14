#pragma once
//
//    FILE: PulseDivider.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-09-13
// PURPOSE: Arduino library to divide a pulsestream with a float factor.
//     URL: https://github.com/RobTillaart/PulseDivider
//
// Tested with UNO.
//

#include "Arduino.h"

#define PULSEDIVIDER_LIB_VERSION        (F("0.1.0"))


class PulseDivider
{
public:
  //  CONSTRUCTOR
  PulseDivider(uint8_t inPin, uint8_t outPin, uint16_t inCount, uint16_t outCount,
                uint32_t duration = 1, uint8_t edge = RISING, bool invert = false)
  {
    setInPin(inPin);
    setOutPin(outPin);
    setRatio(inCount, outCount);
    _duration  = duration;
    _edge      = edge;
    _prevState = digitalRead(_inPin);
    _invert    = invert;

    stop();
  }


///////////////////////////////////////////
//
//  GETTERS && SETTERS
//
  void  setInPin(uint8_t inPin)
  {
    _inPin = inPin;
    pinMode(_inPin, INPUT);
  }

  uint8_t getInPin()
  {
    return _inPin;
  }

  void  setOutPin(uint8_t outPin)
  {
    _outPin = outPin;
    pinMode(_outPin, OUTPUT);
  }

  uint8_t getOutPin()
  {
    return _outPin;
  }

  void setRatio(uint16_t inCount, uint16_t outCount = 1)
  {
    _inCount   = inCount;
    _outCount  = outCount;
    _counter   = inCount / 2;
  }

  float getRatio()
  {
    return float(_inCount) / _outCount;
  }

  void setDuration(uint32_t duration)
  {
    _duration = duration;
  }

  uint32_t getDuration()
  {
    return _duration;
  }

  void setEdge(uint8_t edge)
  {
    _edge = edge;
  }

  uint8_t getEdge()
  {
    return _edge;
  }

  void setInvert(bool invert)
  {
    _invert = invert;
  }

  bool getInvert()
  {
    return _invert;
  }


///////////////////////////////////////////
//
//  CONTROL
//
  void start()
  {
    _prevState = digitalRead(_inPin);
    _counter   = _inCount / 2;
    _running   = true;
  }


  void stop()
  {
    _running  = false;
    digitalWrite(_outPin, _invert ? HIGH : LOW);
  }


  bool isRunning()
  {
    return _running;
  }


///////////////////////////////////////////
//
//  MAIN WORKER
//
  void check()
  {
    if (!_running) return;
    uint8_t  value = digitalRead(_inPin);
    // handle EDGE
    if ((_edge == RISING) and (_prevState == LOW) and (value == HIGH))
    {
      //  RISING
      doPulse();
    }
    if ((_edge == FALLING) and (_prevState == HIGH) and (value == LOW))
    {
      //  FALLING
      doPulse();
    }
    _prevState = value;

    //  reset the output.
    if (micros() - _start >= _duration)
    {
      digitalWrite(_outPin, _invert ? HIGH : LOW);
    }
  }


  void doPulse()
  {
    _counter += _outCount;
    if (_counter >= _inCount)
    {
      _counter -= _inCount;
      _start = micros();
      digitalWrite(_outPin, _invert ? LOW : HIGH);
    }
  }


private:
  uint8_t  _inPin;
  uint8_t  _outPin;
  uint16_t _inCount;
  uint16_t _outCount;
  uint16_t _counter;

  uint32_t _duration;
  uint8_t  _edge;
  bool     _invert;

  bool     _running;
  uint8_t  _prevState;
  uint32_t _start;
};


//  -- END OF FILE --

