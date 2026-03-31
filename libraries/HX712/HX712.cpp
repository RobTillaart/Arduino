//
//    FILE: HX712.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-03-30
// PURPOSE: Arduino library for HX712 load cells
//     URL: https://github.com/RobTillaart/HX712


#include "HX712.h"


HX712::HX712()
{
  _offset   = 0;
  _scale    = 1;
  _gain     = HX712_GAIN_128;
  _lastTimeRead = 0;
  _mode     = HX712_AVERAGE_MODE;
  _fastProcessor = false;
}


HX712::~HX712()
{
}


void HX712::begin(uint8_t dataPin, uint8_t clockPin, bool fastProcessor, bool doReset)
{
  _dataPin  = dataPin;
  _clockPin = clockPin;
  _fastProcessor = fastProcessor;

  pinMode(_dataPin, INPUT_PULLUP);
  pinMode(_clockPin, OUTPUT);
  digitalWrite(_clockPin, LOW);

  if (doReset)
  {
    reset();
  }
}


void HX712::reset()
{
  power_down();
  power_up();
  _offset   = 0;
  _scale    = 1;
  _gain     = HX712_GAIN_128;
  _rate     = 10;
  _lastTimeRead = 0;
  _mode     = HX712_AVERAGE_MODE;
  read();  //  dummy read to force next call!
}


bool HX712::is_ready()
{
  return digitalRead(_dataPin) == LOW;
}


void HX712::wait_ready(uint32_t milliSeconds)
{
  while (!is_ready())
  {
    delay(milliSeconds);
  }
}


bool HX712::wait_ready_retry(uint8_t retries, uint32_t milliSeconds)
{
  while (retries--)
  {
    if (is_ready()) return true;
    delay(milliSeconds);
  }
  return false;
}


bool HX712::wait_ready_timeout(uint32_t timeout, uint32_t milliSeconds)
{
  uint32_t start = millis();
  while (millis() - start < timeout)
  {
    if (is_ready()) return true;
    delay(milliSeconds);
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
//  Blocking period can be long up to 400 ms in first read() call.
float HX712::read()
{
  //  this BLOCKING wait takes most time...
  while (digitalRead(_dataPin) == HIGH)
  {
    yield();
  }

  union
  {
    int32_t value = 0;
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

  //  TABLE 3 page 5 datasheet HX712
  //
  //  CLOCK  INPUT          GAIN    SPS     m
  //  ----------------------------------------
  //   25    Differential    128     10      1    //  default
  //   26    Battery          -      40      2
  //   27    Differential    128     40      3
  //   28    Differential    256     10      4
  //   29    Differential    256     40      5
  //
  //  selection goes through the set_gain_rate(gain, rate)
  //
  uint8_t m = 1;
  if (_mode == HX712_BATTERY_MODE) m = 2;
  else if (_gain == HX712_GAIN_128)
  {
    if (_rate == 40) m = 3;
    else             m = 1;
  }
  else if (_gain == HX712_GAIN_256)
  {
    if (_rate == 40) m = 5;
    else             m = 4;
  }

  while (m > 0)
  {
    //  delayMicroSeconds(1) is needed for fast processors
    //  T2  >= 0.2 us
    digitalWrite(_clockPin, HIGH);
    if (_fastProcessor) delayMicroseconds(1);
    digitalWrite(_clockPin, LOW);
    //  keep duty cycle ~50%
    if (_fastProcessor) delayMicroseconds(1);
    m--;
  }

  interrupts();
  //  yield();

  //  SIGN extend
  if (v.data[2] & 0x80) v.data[3] = 0xFF;

  _lastTimeRead = millis();
  return 1.0 * v.value;
}


float HX712::read_average(uint8_t times)
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


float HX712::read_median(uint8_t times)
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


float HX712::read_medavg(uint8_t times)
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


float HX712::read_runavg(uint8_t times, float alpha)
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
void HX712::set_raw_mode()
{
  _mode = HX712_RAW_MODE;
}


void HX712::set_average_mode()
{
  _mode = HX712_AVERAGE_MODE;
}


void HX712::set_median_mode()
{
  _mode = HX712_MEDIAN_MODE;
}


void HX712::set_medavg_mode()
{
  _mode = HX712_MEDAVG_MODE;
}


//  set_run_avg will use a default alpha of 0.5.
void HX712::set_runavg_mode()
{
  _mode = HX712_RUNAVG_MODE;
}

float HX712::read_battery()
{
  //  save current mode
  uint8_t previousMode = _mode;
  //  set battery mode
  _mode = HX712_BATTERY_MODE;
  read();
  float volts = read();
  //  restire mode
  _mode = previousMode;
  read();
  return volts;
}


uint8_t HX712::get_mode()
{
  return _mode;
}


float HX712::get_value(uint8_t times)
{
  float raw;
  switch(_mode)
  {
    case HX712_RAW_MODE:
      raw = read();
      break;
    case HX712_RUNAVG_MODE:
      raw = read_runavg(times);
      break;
    case HX712_MEDAVG_MODE:
      raw = read_medavg(times);
      break;
    case HX712_MEDIAN_MODE:
      raw = read_median(times);
      break;
    case HX712_AVERAGE_MODE:
    default:
      raw = read_average(times);
      break;
  }
  return raw - _offset;
}


float HX712::get_units(uint8_t times)
{
  float units = get_value(times) * _scale;
  return units;
}


///////////////////////////////////////////////////////////////
//
//  GAIN + RATE
//
bool HX712::set_gain_rate(uint16_t gain, uint8_t rate)
{
  if ((gain != HX712_GAIN_128) ||
      (gain != HX712_GAIN_256) ||
      (rate != HX712_RATE_10) ||
      (rate != HX712_RATE_40))
      {
        return false;
      }
  _gain = gain;
  _rate = rate;
  read();     //  next user read() has right gain
  return true;
}

uint16_t HX712::get_gain()
{
  return _gain;
}

uint8_t HX712::get_rate()
{
  return _rate;
}



///////////////////////////////////////////////////////
//
//  TARE
//
void HX712::tare(uint8_t times)
{
  _offset = read_average(times);
}


float HX712::get_tare()
{
  return -_offset * _scale;
}


bool HX712::tare_set()
{
  return _offset != 0;
}


///////////////////////////////////////////////////////////////
//
//  CALIBRATION  (tare see above)
//
bool HX712::set_scale(float scale)
{
  if (scale == 0) return false;
  _scale = 1.0 / scale;
  return true;
}


float HX712::get_scale()
{
  return 1.0 / _scale;
}


void HX712::set_offset(int32_t offset)
{
  _offset = offset;
}


int32_t HX712::get_offset()
{
  return _offset;
}


//  assumes tare() has been set.
void HX712::calibrate_scale(float weight, uint8_t times)
{
  _scale = weight / (read_average(times) - _offset);
}


///////////////////////////////////////////////////////////////
//
//  POWER MANAGEMENT
//
void HX712::power_down()
{
  //  at least 60 us HIGH
  digitalWrite(_clockPin, HIGH);
  delayMicroseconds(64);
}


void HX712::power_up()
{
  digitalWrite(_clockPin, LOW);
}


///////////////////////////////////////////////////////////////
//
//  MISC
//
uint32_t HX712::last_time_read()
{
  return _lastTimeRead;
}


///////////////////////////////////////////////////////////////
//
//  PRIVATE
//
void HX712::_insertSort(float * array, uint8_t size)
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
uint8_t HX712::_shiftIn()
{
  //  local variables are faster.
  uint8_t clk   = _clockPin;
  uint8_t data  = _dataPin;
  uint8_t value = 0;
  uint8_t mask  = 0x80;
  while (mask > 0)
  {
    digitalWrite(clk, HIGH);
    //  T2  >= 0.2 us
    if(_fastProcessor) delayMicroseconds(1);
    if (digitalRead(data) == HIGH)
    {
      value |= mask;
    }
    digitalWrite(clk, LOW);
    //  keep duty cycle ~50%
    if(_fastProcessor) delayMicroseconds(1);
    mask >>= 1;
  }
  return value;
}


//  -- END OF FILE --

