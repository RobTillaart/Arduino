//
//    FILE: HX711.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: Library for Loadcells for UNO
//     URL: https://github.com/RobTillaart/HX711
//
//  HISTORY:
//  0.1.0   2019-09-04  initial release
//  0.1.1   2019-09-09  change long to float (reduce footprint)
//  0.2.0   2020-06-15  refactor; add price functions;
//  0.2.1   2020-12-28  add arduino-ci + unit test
//  0.2.2   2021-05-10  add read_median(), fix typo, add mode operandi
//  0.2.3   2021-05-26  add running_average() mode


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
  _offset   = 0;
  _scale    = 1;
  _gain     = 128;
  _lastRead = 0;
  _mode     = HX711_AVERAGE_MODE;
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
void HX711::calibrate_scale(uint16_t weight, uint8_t times)
{
  _scale = (1.0 * weight) / (read_average(times) - _offset);
}

// will be obsolete
void HX711::callibrate_scale(uint16_t weight, uint8_t times)
{
  calibrate_scale(weight, times); 
};
  


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
  if (times < 1) times = 1;
  float sum = 0;
  for (uint8_t i = 0; i < times; i++) 
  {
    sum += read();
    yield();
  }
  return sum / times;
}


float HX711::read_median(uint8_t times) 
{
  if (times > 15) times = 15;
  if (times < 3)  times = 3;
  float s[15];
  for (uint8_t i = 0; i < times; i++) 
  {
    s[i] = read();
    yield();
  }
  _insertSort(s, times);
  if (times & 0x01) return s[times/2];
  return (s[times/2] + s[times/2+1])/2;
}


float HX711::read_medavg(uint8_t times) 
{
  if (times > 15) times = 15;
  if (times < 3)  times = 3;
  float s[15];
  for (uint8_t i = 0; i < times; i++) 
  {
    s[i] = read();
    yield();
  }
  _insertSort(s, times);
  float sum = 0;
  // iterate over 1/4 to 3/4 of the array
  uint8_t cnt = 0;
  uint8_t first = (times + 2) / 4;
  uint8_t last  = times - first - 1;
  for (uint8_t i = first; i <= last; i++)  // !! include last too
  {
    sum += s[i];
    cnt++;
  }
  return sum/cnt;
}


float HX711::read_runavg(uint8_t times, float alpha) 
{
  if (times < 1)  times = 1;
  if (alpha < 0)  alpha = 0;
  if (alpha > 1)  alpha = 1;
  float val = read();
  for (uint8_t i = 1; i < times; i++) 
  {
    val += alpha * (read() - val);
    yield();
  }
  return val;
}


void HX711::_insertSort(float * array, uint8_t size)
{
  uint8_t t, z;
  float temp;
  for (t = 1; t < size; t++) 
  {
    z = t;
    temp = array[z];
    while( (z > 0) && (temp < array[z - 1] )) 
    {
      array[z] = array[z - 1];
      z--;
    }
    array[z] = temp;
    yield();
  }
}


float HX711::get_value(uint8_t times) 
{
  float raw;
  switch(_mode)
  {
    case HX711_RUNAVG_MODE:
      raw = read_runavg(times);
      break;
    case HX711_MEDAVG_MODE:
      raw = read_medavg(times);
      break;
    case HX711_MEDIAN_MODE:
      raw = read_median(times);
      break;
    case HX711_AVERAGE_MODE:
    default:
      raw = read_average(times);
      break;
  }
  return raw - _offset;
};


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
