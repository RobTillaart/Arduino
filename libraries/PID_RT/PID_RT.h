#pragma once
//
//    FILE: PID_RT.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.7
// PURPOSE: PID library for Arduino
//     URL: https://github.com/RobTillaart/PID_RT


#include "Arduino.h"


#define PID_LIB_VERSION               (F("0.1.7"))


class PID_RT
{
public:
  PID_RT();
  PID_RT(float sp, float Kp, float Ki, float Kd);

  void     reset();


  void     setPoint(float sp) { _setPoint = sp; };
  float    getSetPoint()      { return _setPoint; };


  bool     compute(float input);
  float    getOutput()        { return _output; };


  //  set PID controller on / off
  void     start()     { _running = true; };
  void     stop()      { _running = false; };
  bool     isRunning() { return _running; };


  //  reverse the behaviour (not implemented yet)
  void     setReverse(bool reverse) { _reverse = reverse; };
  bool     getReverse() { return _reverse; };


  //  how often should one do the math
  bool     setInterval(uint32_t interval);
  uint32_t getInterval() { return _interval; };


  //  tune the output range, default 0..100
  void     setOutputRange(float rangeMin, float rangeMax) { _rangeMin = rangeMin; _rangeMax = rangeMax; };
  float    getOutputMin() { return _rangeMin; };
  float    getOutputMax() { return _rangeMax; };


  //  set the initial K values,
  //  runtime updates are allowed - at your own risk
  bool     setK(float Kp, float Ki, float Kd);
  bool     setKp(float Kp);
  bool     setKi(float Ki);
  bool     setKd(float Kd);
  float    getKp() { return _Kp; };
  float    getKi() { return _Ki; };
  float    getKd() { return _Kd; };


  //  set Proportional on Input or on Error
  void setPropOnInput() { _POI = true; };      //  default
  void setPropOnError() { _POI = false; };
  bool isPropOnInput()  { return _POI == true; };
  bool isPropOnError()  { return _POI == false; };


  //  debugging
  float getInput()       { return _input; };
  float getLastError()   { return _error; };
  uint32_t getLastTime() { return _lastTime; };


private:
  uint32_t _lastTime = 0;
  uint32_t _interval = 250;

  float _errorSum    = 0.0;

  float _setPoint    = 0.0;
  float _input       = 0.0;
  float _lastInput   = 0.0;
  float _error       = 0.0;
  float _output      = 0.0;
  float _rangeMin    = 0.0;
  float _rangeMax    = 100.0;

  float _Kp          = 0.0;
  float _Ki          = 0.0;
  float _Kd          = 0.0;
  float __Kp         = 0.0;
  float __Ki         = 0.0;
  float __Kd         = 0.0;

  bool _reverse      = false;
  bool _running      = false;
  bool _POI          = true;   //  Proportional On Input - Error
};


//  -- END OF FILE --

