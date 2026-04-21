#pragma once
//
//    FILE: FSLP.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-18
// VERSION: 0.1.0
// PURPOSE: Arduino library for FSLP Force Sensing Linear Potentiometer.
//     URL: https://github.com/RobTillaart/FSLP


#include "Arduino.h"


#define FSLP_LIB_VERSION         (F("0.1.0"))

constexpr float FSLP_NO_PRESSURE = 0.0f;


class FSLP
{
public:
  //
  //  FSLP(pin1, pin2, pin3, extraPin)
  //  pin1 = GPIO/ADC
  //  pin2 = GPIO
  //  pin3 = GPIO/ADC
  //  ePin = GPIO
  //
  FSLP(uint8_t sense, uint8_t drive1, uint8_t drive2, uint8_t gpio)
  {
    _sense  = sense;
    _drive1 = drive1;
    _drive2 = drive2;
    _gpio   = gpio;
  }


  ///////////////////////////////////////
  //
  //  READ VALUES
  //
  float readPosition(uint8_t times = 1)
  {
    //  From section 5.1, page 8
    //
    //  Step 1: Clear Charge on Sensor by setting all lines LOW
    pinMode(_sense, OUTPUT);
    pinMode(_drive1, OUTPUT);
    pinMode(_drive2, OUTPUT);
    pinMode(_gpio, OUTPUT);
    digitalWrite(_sense, LOW);
    digitalWrite(_drive1, LOW);
    digitalWrite(_drive2, LOW);
    digitalWrite(_gpio, LOW);

    //  Step 2: Set Up Appropriate Driveline Voltages
    //  commented unneeded steps
    //  pinMode(_drive1, OUTPUT);
    digitalWrite(_drive1, HIGH);  //  terminal 2 HIGH
    //  pinMode(_drive2, OUTPUT);
    //  digitalWrite(_drive2, LOW);   //  terminal 3 LOW
    pinMode(_gpio, INPUT);
    //  digitalWrite(_gpio, LOW);     //  LOW
    pinMode(_sense, INPUT);       //  ADC

    //  Step 3: Wait For Voltage to Stabilize
    //  _dm = default 10
    if (_dm) delayMicroseconds(_dm);

    //  Step 4: Take the measurement
    if (times == 0) times = 1;
    uint32_t raw = 0;
    for (int i = 0; i < times; i++)
    {
      raw += analogRead(_sense);
    }
    _lastPosition = (1.0f * raw) / times;
    return _lastPosition;
  }

  float readPressure(uint8_t times = 1)
  {
    //  From section 5.1, page 8
    //
    //  Step 1: Setup the appropriate drive line voltages
    pinMode(_drive1, OUTPUT);
    digitalWrite(_drive1, HIGH);  //  terminal 2 HIGH
    pinMode(_sense, INPUT);       //  ADC
    pinMode(_drive2, INPUT);      //  ADC
    pinMode(_gpio, OUTPUT);
    digitalWrite(_gpio, LOW);     //  LOW

    //  Step 2: Wait For Voltage to Stabilize ADC
    //  _dm = default 10
    if (_dm) delayMicroseconds(_dm);

    //  Step 3: Take first measurements of two
    if (times == 0) times = 1;
    uint32_t raw = 0;
    for (int i = 0; i < times; i++)
    {
      raw += analogRead(_drive2);
    }
    float V1 = raw;  //  divide by times not needed for force.

    //  Step 2: Wait For Voltage to Stabilize ADC
    if (_dm) delayMicroseconds(_dm);

    //  Step 3: Take second measurements of two
    raw = 0;
    for (int i = 0; i < times; i++)
    {
      raw += analogRead(_sense);
    }
    float V2 = raw;  //  divide by times not needed for force.

    //  Step 4: Calculate the pressure
    if (abs(V1 - V2) > 0.01 )  //  prevent divide by zero
    {
      _lastPressure = (_factor * V2) / (V1 - V2);
      return _lastPressure;
    }
    //  V1 == V2
    //  FSLP_NO_PRESSURE == 0 == false ...
    return FSLP_NO_PRESSURE;
  }

  float isPressed()
  {
    return readPressure(1);
  }


  ///////////////////////////////////////
  //
  //  GET CACHED VALUES
  //
  float getLastPosition()
  {
    return _lastPosition;
  }

  float getLastPressure()
  {
    return _lastPressure;
  }


  ///////////////////////////////////////
  //
  //  CONFIGURATION
  //
  // timing = overkill ?
  void setStabilizationDelay(uint8_t microsec = 10)
  {
    _dm = microsec;
  }

  uint8_t getStabilizationDelay()
  {
    return _dm;
  }

  void setPressureFactor(uint8_t factor = 64)
  {
    _factor = factor;
  }

  uint8_t getPressureFactor()
  {
    return _factor;
  }


protected:
  uint8_t  _sense;   //  1
  uint8_t  _drive1;  //  2
  uint8_t  _drive2;  //  3
  uint8_t  _gpio;

  uint8_t  _dm = 10;  // default stabilization delay
  uint8_t  _factor = 64;

  float    _lastPosition = 0;
  float    _lastPressure = 0;
};


//  -- END OF FILE --





