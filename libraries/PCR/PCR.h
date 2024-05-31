#pragma once
//
//    FILE: PCR.h
//  AUTHOR: Rob Tillaart
//    DATE: 2015-06-10
// VERSION: 0.2.0
// PURPOSE: Arduino library for PCR process control.
//     URL: https://github.com/RobTillaart/PCR
//          https://forum.arduino.cc/t/problem-with-arduino-pcr-amplifies-of-dna/314808



#include "Arduino.h"

#define PCR_LIB_VERSION         (F("0.2.0"))

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
  PCR(uint8_t heatPin, uint8_t coolPin)
  {
    _state = PCR_STATE_IDLE;
    _heatPin = heatPin;
    _coolPin = coolPin;
    pinMode(_heatPin, OUTPUT);
    pinMode(_coolPin, OUTPUT);
    off();
  }


  //  PARAMETERS
  void     setInitial(float temp, uint32_t ms)
  {
    _initialTemp = temp;
    _initialTime = ms;
  }
  float    getInitialTemp() { return _initialTemp; }
  uint32_t getInitialTime() { return _initialTime; }

  void     setDenature(float temp, uint32_t ms)
  {
    _denatureTemp = temp;
    _denatureTime = ms;
  }
  float    getDenatureTemp() { return _denatureTemp; }
  uint32_t getDenatureTime() { return _denatureTime; }

  void     setAnnealing(float temp, uint32_t ms)
  {
    _annealingTemp = temp;
    _annealingTime = ms;
  }
  float    getAnnealingTemp() { return _annealingTemp; }
  uint32_t getAnnealingTime() { return _annealingTime; }

  void     setExtension(float temp, uint32_t ms)
  {
    _extensionTemp = temp;
    _extensionTime = ms;
  }
  float    getExtensionTemp() { return _extensionTemp; }
  float    getExtensionTime() { return _extensionTime; }

  void     setElongation(float temp, uint32_t ms)
  {
    _elongationTemp = temp;
    _elongationTime = ms;
  }
  float    getElongationTemp() { return _elongationTemp; }
  float    getElongationTime() { return _elongationTime; }

  void     setHold(float temp) { _holdTemp = temp; }
  float    getHoldTemp() { return _extensionTemp; }


  //  PROCESS CONTROL
  void reset(int iterations)
  {
    _startTime = millis();
    _cycles = iterations;
    _state = PCR_STATE_IDLE;
    off();
    debug();
  }

  int iterationsLeft() { return _cycles; };

  //  returns PCR_STATE_HOLD when ready;
  uint8_t process(float temperature)
  {
    _temperature = temperature;
    switch(_state)
    {
      case PCR_STATE_IDLE:
        _state = PCR_STATE_INITIAL;
        _startTime = millis();
        debug();
      break;

      case PCR_STATE_INITIAL:
        if (_temperature < _initialTemp) heat();
        else if (_temperature > _initialTemp) cool();
        else off();
        if (millis() - _startTime >= _initialTime)
        {
          _state = PCR_STATE_DENATURE;
          _startTime = millis();
          debug();
        }
      break;
      
      case PCR_STATE_DENATURE:
        if (_temperature < _denatureTemp) heat();
        else if (_temperature > _denatureTemp) cool();
        else off();
        if (millis() - _startTime >= _denatureTime)
        {
          _state = PCR_STATE_ANNEALING;
          _startTime = millis();
          debug();
        }
      break;

      case PCR_STATE_ANNEALING:
        if (_temperature < _annealingTemp) heat();
        else if (_temperature > _annealingTemp) cool();
        else off();
        if (millis() - _startTime >= _annealingTime)
        {
          _state = PCR_STATE_EXTENSION;
          _startTime = millis();
          debug();
        }
      break;
      
      case PCR_STATE_EXTENSION:
        if (_temperature < _extensionTemp) heat();
        else if (_temperature > _extensionTemp) cool();
        else off();
        if (millis() - _startTime >= _extensionTime)
        {
          _cycles--;
          if (_cycles > 0) _state = PCR_STATE_DENATURE;
          else _state = PCR_STATE_ELONGATION;
          _startTime = millis();
          debug();
        }
      break;
      
      case PCR_STATE_ELONGATION:
        if (_temperature < _elongationTemp) heat();
        else if (_temperature > _elongationTemp) cool();
        else off();
        if (millis() - _startTime >= _elongationTime)
        {
          _state = PCR_STATE_HOLD;
          _startTime = millis();
          debug();
        }
      break;

      case PCR_STATE_HOLD:
        if (_temperature < _holdTemp) heat();
        else if (_temperature > _holdTemp) cool();
        else off();
      break;
    }
    return _state;
  }


  //  HEATER / COOLER CONTROL
  void heat()
  {
    digitalWrite(_heatPin, HIGH);
    delay(10);
    digitalWrite(_coolPin, LOW);
  }

  void cool()
  {
    digitalWrite(_coolPin, HIGH);
    delay(10);
    digitalWrite(_coolPin, LOW);
  }

  void off()
  {
    digitalWrite(_heatPin, LOW);
    digitalWrite(_coolPin, LOW);
  }


  //  blocking version of single step.
  //  to be tested what to do with it
  //  could be a separate class.
  /*
  void keepTempTime(float temperature, uint32_t ms,  float (*getTemp)())
  {
    _startTime = millis();
    _temperature = temperature;
    while (millis() - _startTime < ms)
    {
      if (getTemp() < _temperature ) heat();
      else if (getTemp() > _temperature) cool();
      else off();
    }
  }
  */

  //  estimator timeLeft, assumes process is not stopped.
  uint32_t timeLeft()
  {
    uint32_t sum = 0;
    if (_state < PCR_STATE_DENATURE) sum += _initialTime;
    sum += _denatureTime  * _cycles;
    sum += _annealingTime * _cycles;
    sum += _extensionTime * _cycles;
    if (_state <= PCR_STATE_ELONGATION) sum += _elongationTime;
    return sum;
  }

private:
  // development.
  void debug()
  {
    //  log for plotting temperature
    //
    //  Serial.print(_cycles);
    //  Serial.print("\t");
    //  Serial.println(_temperature);

    //  log for seeing state transitions.
    Serial.print(_startTime);
    Serial.print("\t");
    Serial.print(_cycles);
    if (_state == PCR_STATE_IDLE) Serial.println("\tIdle");
    if (_state == PCR_STATE_INITIAL) Serial.println("\tInitialization");
    if (_state == PCR_STATE_DENATURE) Serial.println("\tDenature");
    if (_state == PCR_STATE_ANNEALING) Serial.println("\tAnnealing");
    if (_state == PCR_STATE_EXTENSION) Serial.println("\tExtension");
    if (_state == PCR_STATE_ELONGATION) Serial.println("\tElongation");
    if (_state == PCR_STATE_HOLD) Serial.println("\tHOLD");
  }


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

  int      _heatPin = 0;
  int      _coolPin = 0;
  PCRSTATE _state = PCR_STATE_IDLE;
  int      _cycles = 0;
  uint32_t _startTime = 0;
};


//  -- END OF FILE --





