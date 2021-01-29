//
//    FILE: HX711.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Library for Loadcells for UNO
//     URL: https://github.com/RobTillaart/HX711
//
//  HISTORY:
//  0.1.0   2019-09-04  initial release
//  0.1.1   2019-09-09  change long to float (reduce footprint)
//  0.2.0   2020-06-15  refactor; add price functions;
//  0.2.1   2020-12-28  add arduino-ci + unit test


#include "HX711.h"

HX711::HX711()
{
  reset();
}

HX711::~HX711() {}

void HX711::begin(uint8_t dataPin, uint8_t clockPin)
{
  _dataPin = dataPin;
  _clockPin = clockPin;

  pinMode(_dataPin, INPUT);
  pinMode(_clockPin, OUTPUT);
  digitalWrite(_clockPin, LOW);

  reset();
}

void HX711::reset()
{
  _offset = 0;
  _scale = 1;
  _gain = 128;
}

bool HX711::is_ready()
{
  return digitalRead(_dataPin) == LOW;
}

float HX711::read() 
{
  // this waiting takes most time...
  while (digitalRead(_dataPin) == HIGH) yield();
  
  union
  {
    long value = 0;
    uint8_t data[4];
  } v;

  noInterrupts();

  // Pulse the clock pin 24 times to read the data.
  v.data[2] = shiftIn(_dataPin, _clockPin, MSBFIRST);
  v.data[1] = shiftIn(_dataPin, _clockPin, MSBFIRST);
  v.data[0] = shiftIn(_dataPin, _clockPin, MSBFIRST);

  // TABLE 3 page 4 datasheet
  // only default verified, so other values not supported yet
  uint8_t m = 1;   // default gain == 128
  if (_gain == 64) m = 3;
  if (_gain == 32) m = 2;

  while (m > 0)
  {
    digitalWrite(_clockPin, HIGH);
    digitalWrite(_clockPin, LOW);
    m--;
  }

  interrupts();

  // SIGN extend
  if (v.data[2] & 0x80) v.data[3] = 0xFF;

  _lastRead = millis();
  return 1.0 * v.value;
}

// assumes tare() has been set.
void HX711::callibrate_scale(uint16_t weight, uint8_t times)
{
  _scale = (1.0 * weight) / (read_average(times) - _offset);
}

void HX711::wait_ready(uint32_t ms) 
{
  while (!is_ready())
  {
    delay(ms);
  }
}

bool HX711::wait_ready_retry(uint8_t retries, uint32_t ms) 
{
  while (retries--)
  {
    if (is_ready()) return true;
    delay(ms);
  }
  return false;
}

bool HX711::wait_ready_timeout(uint32_t timeout, uint32_t ms)
{
  uint32_t start = millis();
  while (millis() - start < timeout) 
  {
    if (is_ready()) return true;
    delay(ms);
  }
  return false;
}

float HX711::read_average(uint8_t times) 
{
  float sum = 0;
  for (uint8_t i = 0; i < times; i++) 
  {
    sum += read();
    yield();
  }
  return sum / times;
}

float HX711::get_units(uint8_t times)
{
  float units = get_value(times) * _scale;
  return units;
};

void HX711::power_down() 
{
  digitalWrite(_clockPin, LOW);
  digitalWrite(_clockPin, HIGH);
}

void HX711::power_up() 
{
  digitalWrite(_clockPin, LOW);
}

// -- END OF FILE --
