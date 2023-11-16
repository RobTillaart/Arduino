#pragma once
//
//    FILE: PulseDivider.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2023-09-13
// PURPOSE: Arduino library to divide a pulse stream with a float factor.
//     URL: https://github.com/RobTillaart/PulseDivider


#include "Arduino.h"

#define PULSEDIVIDER_LIB_VERSION        (F("0.1.2"))


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
    setDuration(duration);
    setEdge(edge);
    setInvert(invert);

    _prevState = _read();
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
    _write(_invert ? HIGH : LOW);
  }

  uint8_t getOutPin()
  {
    return _outPin;
  }

  void setRatio(uint16_t inCount, uint16_t outCount = 1)
  {
    _inCount   = inCount;
    _outCount  = outCount;
    _counter   = inCount / 2;  //  reasonable start position.
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
    if ((edge != FALLING) && (edge != RISING)) return;
    _edge = edge;
  }

  uint8_t getEdge()
  {
    return _edge;
  }

  void setInvert(bool invert)
  {
    _invert = invert;
    _write(_invert ? HIGH : LOW);
  }

  bool getInvert()
  {
    return _invert;
  }

  //  debug
  uint16_t getCounter()
  {
    return _counter;
  }

///////////////////////////////////////////
//
//  CONTROL
//
  void start()
  {
    _prevState = _read();
    _counter   = _inCount / 2;
    _running   = true;
  }


  void stop()
  {
    _running  = false;
    _write(_invert ? HIGH : LOW);
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
    if (_running == false) return;

    uint8_t value = _read();
    if (_prevState != value)
    {
       if (((_edge == RISING) and (value == HIGH)) or
           ((_edge == FALLING) and (value == LOW)))
       {
           doPulse();
       }
    }
    _prevState = value;

    //  reset the output?
    if (_pulseStarted and (micros() - _start >= _duration))
    {
      _write(_invert ? HIGH : LOW);
      _pulseStarted = false;
    }
  }


  inline void doPulse()
  {
    _counter += _outCount;
    if (_counter >= _inCount)
    {
      _counter -= _inCount;
      _start = micros();
      _write(_invert ? LOW : HIGH);
      _pulseStarted = true;
    }
  }


private:

  //  default reference
  void _write(uint8_t value)
  {
    digitalWrite(_outPin, value);
  }

  inline uint8_t _read()
  {
    return digitalRead(_inPin);
  }

  uint8_t  _inPin;
  uint8_t  _outPin;
  uint16_t _inCount   = 1;
  uint16_t _outCount  = 1;
  uint16_t _counter   = 0;

  uint32_t _duration  = 1;
  uint8_t  _edge      = RISING;
  bool     _invert    = false;

  bool     _running   = false;
  uint8_t  _prevState = LOW;
  uint32_t _start     = 0;
  bool     _pulseStarted = false;
};


//  -- END OF FILE --

