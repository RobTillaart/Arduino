//
//    FILE: FSR40X.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-16
// VERSION: 0.1.0
// PURPOSE: Arduino library for FSR40X Force Sensing Resistors.
//     URL: https://github.com/RobTillaart/FSR40X


#include "FSR40X.h"


constexpr float KGF2NEWTON = 9.80655;      //  = acceleration of gravity
constexpr float NEWTON2KGF = 0.101971621;  //  1.0 / KGF2NEWTON
constexpr float NEWTON2LBF = 0.224808943;


FSR40X::FSR40X(uint8_t ADCpin, float voltage, uint16_t steps)
{
  _adcPin  = ADCpin;
  _voltage = voltage;
  _steps   = steps;
  _resistor = 10000;
}

bool FSR40X::begin(float resistor)
{
  _resistor = resistor;
  return true;
}

bool FSR40X::setVoltage(float voltage)
{
  if (_voltage <= 1.0) return false;
  _voltage = voltage;
  return true;
}


/////////////////////////////////////////////
//
//  READ
//
float FSR40X::readRaw(uint8_t times)
{
  //  test code
  //  static int x = 0;
  //  x++;
  //  return x;
  if (times == 0) times = 1;
  uint32_t raw = 0;
  for (uint8_t i = 0; i < times; i++)
  {
    raw += analogRead(A0);
  }
  return (1.0 * raw) / times;
}

float FSR40X::readNewton(uint8_t times)
{
  float raw = readRaw(times);
  //  convert to voltage
  _vout = (raw * _voltage) / _steps;
  //  reverse calculate voltage divider
  _fsr = (_resistor * _voltage)/ _vout - _resistor;

  //  MAGIC formula from data-points datasheet.
  //  should the magic numbers be configurable?
  //  formula uses FSR in kiloOhm
  //  _kgf = 2.69117452575 * pow(_fsr * 0.001, -1.114166333);
  //  _newton =  _kgf * 9.80665;
  //  return _newton;
  //  as Newtons are preferred.
  _newton = (9.80665 * 2.69117452575) * pow(_fsr * 0.001, -1.114166333);
  return _newton;
}

float FSR40X::getVout()
{
  return _vout;
}

float FSR40X::getNewton()
{
  return _newton;
}

float FSR40X::getKgf()
{
  return _newton * NEWTON2KGF;
}

float FSR40X::getLbf()
{
  return _newton * NEWTON2LBF;
}

float FSR40X::getFSR()
{
  return _fsr;
}


///////////////////////////////////////////////
//
//  DERIVED CLASSES
//
FSR400::FSR400(uint8_t ADCpin, float voltage, uint16_t steps)
       :FSR40X(ADCpin, voltage, steps)
{
}

FSR402::FSR402(uint8_t ADCpin, float voltage, uint16_t steps)
       :FSR40X(ADCpin, voltage, steps)
{
}


FSR404::FSR404(uint8_t ADCpin, float voltage, uint16_t steps)
       :FSR40X(ADCpin, voltage, steps)
{
}


FSR406::FSR406(uint8_t ADCpin, float voltage, uint16_t steps)
       :FSR40X(ADCpin, voltage, steps)
{
}


FSR408::FSR408(uint8_t ADCpin, float voltage, uint16_t steps)
       :FSR40X(ADCpin, voltage, steps)
{
}


//  -- END OF FILE --

