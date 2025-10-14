#pragma once
//
//    FILE: PCR.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
//    DATE: 2015-06-10
// PURPOSE: Arduino library for PCR process control.
//     URL: https://github.com/RobTillaart/PCR
//          https://forum.arduino.cc/t/problem-with-arduino-pcr-amplifies-of-dna/314808


#include "Arduino.h"

#define PCR_LIB_VERSION         (F("0.4.0"))

//  comment next line if no debug output is needed.
#define PCR_DEBUG   1


enum PCRSTATE {
  PCR_STATE_IDLE = 0,
  PCR_STATE_INITIAL,
  PCR_STATE_DENATURE,
  PCR_STATE_ANNEALING,
  PCR_STATE_EXTENSION,
  PCR_STATE_ELONGATION,
  PCR_STATE_HOLD
};


class PCR
{
public:
  PCR(uint8_t heatPin, uint8_t coolPin, uint8_t signalPin = 255)
  {
    _state = PCR_STATE_IDLE;
    _heatPin = heatPin;
    _coolPin = coolPin;
    _signalPin = signalPin;
    pinMode(_heatPin, OUTPUT);
    pinMode(_coolPin, OUTPUT);
    pinMode(_signalPin, OUTPUT);
    off();
  }


  //  PARAMETERS
  void     setInitial(float Celsius, float seconds)
  {
    _initialTemp = Celsius;
    _initialTime = seconds * 1000;
  }
  float    getInitialTemp() { return _initialTemp; }
  float    getInitialTime() { return _initialTime * 0.001f; }


  void     setDenature(float Celsius, float seconds)
  {
    _denatureTemp = Celsius;
    _denatureTime = seconds * 1000;
  }
  float    getDenatureTemp() { return _denatureTemp; }
  float    getDenatureTime() { return _denatureTime * 0.001f; }


  void     setAnnealing(float Celsius, float seconds)
  {
    _annealingTemp = Celsius;
    _annealingTime = seconds * 1000;
  }
  float    getAnnealingTemp() { return _annealingTemp; }
  float    getAnnealingTime() { return _annealingTime * 0.001f; }


  void     setExtension(float Celsius, float seconds)
  {
    _extensionTemp = Celsius;
    _extensionTime = seconds * 1000;
  }
  float    getExtensionTemp() { return _extensionTemp; }
  float    getExtensionTime() { return _extensionTime * 0.001f; }


  void     setElongation(float Celsius, float seconds)
  {
    _elongationTemp = Celsius;
    _elongationTime = seconds * 1000;
  }
  float    getElongationTemp() { return _elongationTemp; }
  float    getElongationTime() { return _elongationTime * 0.001f; }


  void     setHold(float Celsius) { _holdTemp = Celsius; }
  float    getHoldTemp() { return _holdTemp; }


  //  PROCESS CONTROL
  void reset(uint16_t iterations)
  {
    _startTime = millis();
    _cycles = iterations;
    _state = PCR_STATE_IDLE;
    off();
    debug();
  }

  uint16_t iterationsLeft()
  {
    return _cycles;
  }


  //  returns state ==> PCR_STATE_HOLD when ready;
  uint8_t process(float temperature)
  {
    uint32_t now = millis();
    _temperature = temperature;

    //  switch off the signal.
    if (_pulse)
    {
      if (now - _startTime >= _signalPulseLength)
      {
        _pulse = false;
        digitalWrite(_signalPin, LOW);
      }
    }

    uint8_t prevState = _state;
    switch(_state)
    {
      case PCR_STATE_IDLE:
        _state = PCR_STATE_INITIAL;
      break;

      case PCR_STATE_INITIAL:
        if (_temperature < _initialTemp) heat();
        else if (_temperature > _initialTemp) cool();
        else off();
        if (now - _startTime >= _initialTime)
        {
          _state = PCR_STATE_DENATURE;
        }

      break;

      case PCR_STATE_DENATURE:
        if (_temperature < _denatureTemp) heat();
        else if (_temperature > _denatureTemp) cool();
        else off();
        if (now - _startTime >= _denatureTime)
        {
          _state = PCR_STATE_ANNEALING;
        }
      break;

      case PCR_STATE_ANNEALING:
        if (_temperature < _annealingTemp) heat();
        else if (_temperature > _annealingTemp) cool();
        else off();
        if (now - _startTime >= _annealingTime)
        {
          _state = PCR_STATE_EXTENSION;
        }
      break;

      case PCR_STATE_EXTENSION:
        if (_temperature < _extensionTemp) heat();
        else if (_temperature > _extensionTemp) cool();
        else off();
        if (now - _startTime >= _extensionTime)
        {
          _cycles--;
          if (_cycles > 0) _state = PCR_STATE_DENATURE;
          else _state = PCR_STATE_ELONGATION;
        }
      break;

      case PCR_STATE_ELONGATION:
        if (_temperature < _elongationTemp) heat();
        else if (_temperature > _elongationTemp) cool();
        else off();
        if (now - _startTime >= _elongationTime)
        {
          _state = PCR_STATE_HOLD;
        }
      break;

      case PCR_STATE_HOLD:
        if (_temperature < _holdTemp) heat();
        else if (_temperature > _holdTemp) cool();
        else off();
      break;

      default:
        Serial.println("UNKNOWN STATE ERROR!");
      break;
    }
    //  new state ? => actions.
    if (prevState != _state)
    {
      _startTime = now;
      if (_signalPulseLength > 0)
      {
        _pulse = true;
        digitalWrite(_signalPin, HIGH);
      }
      debug();
    }
    return _state;
  }

  uint8_t getPCRState()
  {
    return _state;
  }

  //  HEATER / COOLER CONTROL
  //  ms = timing in milliseconds
  void setHeatPulseLength(uint16_t ms = 10)
  {
    _heatPulseLength = ms;
    if (_heatPulseLength > 1000) _heatPulseLength = 1000;
  }

  //  returns milliseconds.
  uint16_t getHeatPulseLength()
  {
    return _heatPulseLength;
  }

  void heat()
  {
    digitalWrite(_heatPin, HIGH);
    delay(_heatPulseLength);
    digitalWrite(_coolPin, LOW);
  }

  void cool()
  {
    digitalWrite(_coolPin, HIGH);
    delay(_heatPulseLength);
    digitalWrite(_coolPin, LOW);
  }

  void off()
  {
    digitalWrite(_heatPin, LOW);
    digitalWrite(_coolPin, LOW);
    digitalWrite(_signalPin, LOW);
  }

  //  estimator timeLeft, assumes process is not stopped.
  //  returns value in seconds
  float timeLeft()
  {
    uint32_t sum = 0;
    if (_state < PCR_STATE_DENATURE) sum += _initialTime;
    sum += _denatureTime  * _cycles;
    sum += _annealingTime * _cycles;
    sum += _extensionTime * _cycles;
    if (_state <= PCR_STATE_ELONGATION) sum += _elongationTime;
    return sum * 0.001f;
  }

  //  signal pulses at phase change.
  //  0 == OFF, typical steps of 100 milliseconds.
  void setSignalLength(uint16_t ms)
  {
    _signalPulseLength = ms;
  }

  uint16_t getSignalLength()
  {
    return _signalPulseLength;
  }



protected:
  //  development.
  void debug()
  {
#ifdef PCR_DEBUG
    //  log for seeing state transitions.
    Serial.print(_startTime);
    Serial.print("\t");
    Serial.print(_cycles);
    //  use an array?
    if (_state == PCR_STATE_DENATURE)        Serial.println(F("\tDenature"));
    else if (_state == PCR_STATE_ANNEALING)  Serial.println(F("\tAnnealing"));
    else if (_state == PCR_STATE_EXTENSION)  Serial.println(F("\tExtension"));
    //  less used
    else if (_state == PCR_STATE_ELONGATION) Serial.println(F("\tElongation"));
    else if (_state == PCR_STATE_IDLE)       Serial.println(F("\tIdle"));
    else if (_state == PCR_STATE_INITIAL)    Serial.println(F("\tInitialize"));
    else if (_state == PCR_STATE_HOLD)       Serial.println(F("\tHold"));
    else                                     Serial.println(F("\tUnknown"));
#endif
  }

  //  temperatures in °Celsius
  //  timestamps in milliseconds
  float    _initialTemp = 94;
  uint32_t _initialTime = 0;
  float    _denatureTemp = 94;
  uint32_t _denatureTime = 1000;
  float    _annealingTemp = 54;
  uint32_t _annealingTime = 1000;
  float    _extensionTemp = 76;
  uint32_t _extensionTime = 1000;
  float    _elongationTemp = 76;
  uint32_t _elongationTime = 1000;
  float    _holdTemp = 14;

  float    _temperature = 0;

  //  IO pins
  uint8_t  _heatPin = 255;
  uint8_t  _coolPin = 255;
  uint8_t  _signalPin = 255;

  PCRSTATE _state = PCR_STATE_IDLE;
  uint16_t _cycles = 0;
  uint32_t _startTime = 0;
  uint16_t _heatPulseLength = 10;  //  milliseconds

  uint16_t _signalPulseLength = 500;  //  milliseconds
  bool     _pulse = false;
};


//  -- END OF FILE --


