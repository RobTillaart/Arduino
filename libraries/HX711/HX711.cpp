//
//    FILE: HX711.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.0
// PURPOSE: Library for load cells for UNO
//     URL: https://github.com/RobTillaart/HX711_MP
//     URL: https://github.com/RobTillaart/HX711


#include "HX711.h"


HX711::HX711()
{
  _gain     = HX711_CHANNEL_A_GAIN_128;
  _offset   = 0;
  _scale    = 1;
  _lastRead = 0;
  _price    = 0;
  _mode     = HX711_AVERAGE_MODE;
  _fastProcessor = false;
}


HX711::~HX711()
{
}


void HX711::begin(uint8_t dataPin, uint8_t clockPin, bool fastProcessor )
{
  _dataPin  = dataPin;
  _clockPin = clockPin;
  _fastProcessor = fastProcessor;

  pinMode(_dataPin, INPUT);
  pinMode(_clockPin, OUTPUT);
  digitalWrite(_clockPin, LOW);

  reset();
}


void HX711::reset()
{
  power_down();
  power_up();
  _gain     = HX711_CHANNEL_A_GAIN_128;
  _offset   = 0;
  _scale    = 1;
  _lastRead = 0;
  _price    = 0;
  _mode     = HX711_AVERAGE_MODE;
}


bool HX711::is_ready()
{
  return digitalRead(_dataPin) == LOW;
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


///////////////////////////////////////////////////////////////
//
//  READ
//
//  From datasheet page 4
//  When output data is not ready for retrieval,
//       digital output pin DOUT is HIGH.
//  Serial clock input PD_SCK should be LOW.
//  When DOUT goes to LOW, it indicates data is ready for retrieval.
float HX711::read()
{
  //  this BLOCKING wait takes most time...
  while (digitalRead(_dataPin) == HIGH) yield();

  union
  {
    long value = 0;
    uint8_t data[4];
  } v;

  //  blocking part ...
  noInterrupts();

  //  Pulse the clock pin 24 times to read the data.
  //  v.data[2] = shiftIn(_dataPin, _clockPin, MSBFIRST);
  //  v.data[1] = shiftIn(_dataPin, _clockPin, MSBFIRST);
  //  v.data[0] = shiftIn(_dataPin, _clockPin, MSBFIRST);
  v.data[2] = _shiftIn();
  v.data[1] = _shiftIn();
  v.data[0] = _shiftIn();

  //  TABLE 3 page 4 datasheet
  //
  //  CLOCK      CHANNEL      GAIN      m
  //  ------------------------------------
  //   25           A         128       1    //  default
  //   26           B          32       2
  //   27           A          64       3
  //
  //  only default 128 verified,
  //  selection goes through the set_gain(gain)
  //
  uint8_t m = 1;
  if      (_gain == HX711_CHANNEL_A_GAIN_128) m = 1;
  else if (_gain == HX711_CHANNEL_A_GAIN_64)  m = 3;
  else if (_gain == HX711_CHANNEL_B_GAIN_32)  m = 2;

  while (m > 0)
  {
    //  delayMicroSeconds(1) needed for fast processors?
    digitalWrite(_clockPin, HIGH);
    if (_fastProcessor)
        delayMicroseconds(1);
    digitalWrite(_clockPin, LOW);
    if (_fastProcessor)
        delayMicroseconds(1);
    m--;
  }

  interrupts();
  //  yield();

  //  SIGN extend
  if (v.data[2] & 0x80) v.data[3] = 0xFF;

  _lastRead = millis();
  return 1.0 * v.value;
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
  float samples[15];
  for (uint8_t i = 0; i < times; i++)
  {
    samples[i] = read();
    yield();
  }
  _insertSort(samples, times);
  if (times & 0x01) return samples[times/2];
  return (samples[times/2] + samples[times/2 + 1]) / 2;
}


float HX711::read_medavg(uint8_t times)
{
  if (times > 15) times = 15;
  if (times < 3)  times = 3;
  float samples[15];
  for (uint8_t i = 0; i < times; i++)
  {
    samples[i] = read();
    yield();
  }
  _insertSort(samples, times);
  float sum = 0;
  //  iterate over 1/4 to 3/4 of the array
  uint8_t count = 0;
  uint8_t first = (times + 2) / 4;
  uint8_t last  = times - first - 1;
  for (uint8_t i = first; i <= last; i++)  //  !! include last one too
  {
    sum += samples[i];
    count++;
  }
  return sum / count;
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


///////////////////////////////////////////////////////
//
//  MODE
//
void HX711::set_raw_mode()
{
  _mode = HX711_RAW_MODE;
}


void HX711::set_average_mode()
{
  _mode = HX711_AVERAGE_MODE;
}


void HX711::set_median_mode()
{
  _mode = HX711_MEDIAN_MODE;
}


void HX711::set_medavg_mode()
{
  _mode = HX711_MEDAVG_MODE;
}


//  set_run_avg will use a default alpha of 0.5.
void HX711::set_runavg_mode()
{
  _mode = HX711_RUNAVG_MODE;
}


uint8_t HX711::get_mode()
{
  return _mode;
}


float HX711::get_value(uint8_t times)
{
  float raw;
  switch(_mode)
  {
    case HX711_RAW_MODE:
      raw = read();
      break;
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


///////////////////////////////////////////////////////
//
//  TARE
//
void HX711::tare(uint8_t times)
{
  _offset = read_average(times);
}


float HX711::get_tare()
{
  return -_offset * _scale;
}


bool HX711::tare_set()
{
  return _offset != 0;
}


///////////////////////////////////////////////////////////////
//
//  GAIN
//
//  note: if parameter gain == 0xFF40 some compilers
//  will map that to 0x40 == HX711_CHANNEL_A_GAIN_64;
//  solution: use uint32_t or larger parameters everywhere.
//  note that changing gain/channel may take up to 400 ms (page 3)
bool HX711::set_gain(uint8_t gain, bool forced)
{
  if ( (not forced) && (_gain == gain)) return true;
  switch(gain)
  {
    case HX711_CHANNEL_B_GAIN_32:
    case HX711_CHANNEL_A_GAIN_64:
    case HX711_CHANNEL_A_GAIN_128:
      _gain = gain;
      read();     //  next user read() is from right channel / gain
      return true;
  }
  return false;   //  unchanged, but incorrect value.
}


uint8_t HX711::get_gain()
{
  return _gain;
}


///////////////////////////////////////////////////////////////
//
//  CALIBRATION
//
bool HX711::set_scale(float scale)
{
  if (scale == 0) return false;
  _scale = 1.0 / scale;
  return true;
}


float HX711::get_scale()
{
  return 1.0 / _scale;
}


void HX711::set_offset(long offset)
{
  _offset = offset;
}


long HX711::get_offset()
{
  return _offset;
}


//  assumes tare() has been set.
void HX711::calibrate_scale(uint16_t weight, uint8_t times)
{
  _scale = (1.0 * weight) / (read_average(times) - _offset);
}


///////////////////////////////////////////////////////////////
//
//  POWER MANAGEMENT
//
void HX711::power_down()
{
  //  at least 60 us HIGH
  digitalWrite(_clockPin, HIGH);
  delayMicroseconds(64);
}


void HX711::power_up()
{
  digitalWrite(_clockPin, LOW);
}


///////////////////////////////////////////////////////////////
//
//  MISC
//
uint32_t HX711::last_read()
{
  return _lastRead;
}


///////////////////////////////////////////////////////////////
//
//  PRIVATE
//

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


//  MSB_FIRST optimized shiftIn
//  see datasheet page 5 for timing
uint8_t HX711::_shiftIn()
{
  //  local variables are faster.
  uint8_t clk   = _clockPin;
  uint8_t data  = _dataPin;
  uint8_t value = 0;
  uint8_t mask  = 0x80;
  while (mask > 0)
  {
    digitalWrite(clk, HIGH);
    if(_fastProcessor)       //  T2  >= 0.2 us
      delayMicroseconds(1);
    if (digitalRead(data) == HIGH)
    {
      value |= mask;
    }
    digitalWrite(clk, LOW);
    if(_fastProcessor)
      delayMicroseconds(1);   //  keep duty cycle ~50%
    mask >>= 1;
  }
  return value;
}


//  -- END OF FILE --

