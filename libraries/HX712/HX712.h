#pragma once
//
//    FILE: HX712.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-03-30
// PURPOSE: Arduino library for HX712 load cells
//     URL: https://github.com/RobTillaart/HX712
//

#include "Arduino.h"

#define HX712_LIB_VERSION               (F("0.1.0"))


const uint8_t HX712_AVERAGE_MODE = 0x00;
//  in median mode only between 3 and 15 samples are allowed.
const uint8_t HX712_MEDIAN_MODE  = 0x01;
//  medavg = average of the middle "half" of sorted elements
//  in medavg mode only between 3 and 15 samples are allowed.
const uint8_t HX712_MEDAVG_MODE  = 0x02;
//  runavg = running average
const uint8_t HX712_RUNAVG_MODE  = 0x03;
//  causes read() to be called only once!
const uint8_t HX712_RAW_MODE     = 0x04;

//  TODO
//  causes read() ???
const uint8_t HX712_BATTERY_MODE = 0x05;


//  supported values for set_gain_rate()
const uint16_t HX712_GAIN_128 = 128;  //  default
const uint16_t HX712_GAIN_256 = 256;
const uint8_t  HX712_RATE_10 = 10;    //  default
const uint8_t  HX712_RATE_40 = 40;


class HX712
{
public:
  HX712();
  ~HX712();

  //  fixed gain 128 for now
  void     begin(uint8_t dataPin, uint8_t clockPin,
                 bool fastProcessor = false,
                 bool doReset = true);

  void     reset();

  //  checks if load cell is ready to read.
  //  use this to prevent blocking reads, esp at startup, 1st read.
  bool     is_ready();

  //  wait until ready,
  //  check every ms milliSeconds
  void     wait_ready(uint32_t milliSeconds = 0);
  //  max # retries, check every ms milliSeconds
  bool     wait_ready_retry(uint8_t retries = 3, uint32_t milliSeconds = 0);
  //  max timeout, check every ms milliSeconds
  bool     wait_ready_timeout(uint32_t timeout = 1000, uint32_t milliSeconds = 0);


  ///////////////////////////////////////////////////////////////
  //
  //  READ
  //
  //  raw read, is blocking until device is ready to read().
  //  this blocking period can be long up to 400 ms in first read() call.
  float    read();

  //  get average of multiple raw reads
  //  times = 1 or more
  float    read_average(uint8_t times = 10);

  //  get median of multiple raw reads
  //  times = 3..15 - odd numbers preferred
  float    read_median(uint8_t times = 7);

  //  get average of "middle half" of multiple raw reads.
  //  times = 3..15 - odd numbers preferred
  float    read_medavg(uint8_t times = 7);

  //  get running average over times measurements.
  //  the weight alpha can be set to any value between 0 and 1
  //  times = 1 or more.
  float    read_runavg(uint8_t times = 7, float alpha = 0.5);

  //  TODO test with hardware.
  //  0.1.0 behaviour
  //  saves current mode
  //  reads the battery
  //  restores current mode.
  float    read_battery();


  ///////////////////////////////////////////////////////////////
  //
  //  MODE
  //
  //  get set mode for get_value() and indirect get_units().
  //  in median and medavg mode only 3..15 samples are allowed.
  void     set_raw_mode();
  void     set_average_mode();
  void     set_median_mode();
  void     set_medavg_mode();
  //  set_run_avg will use a default alpha of 0.5.
  void     set_runavg_mode();
  uint8_t  get_mode();

  //  corrected for offset.
  //  in HX712_RAW_MODE the parameter times will be ignored.
  float    get_value(uint8_t times = 1);
  //  converted to proper units, corrected for scale.
  //  in HX712_RAW_MODE the parameter times will be ignored.
  float    get_units(uint8_t times = 1);


  ///////////////////////////////////////////////////////////////
  //
  //  GAIN + RATE
  //
  //  allowed combinations
  //
  //  GAIN     RATE    notes
  //  -----------------------------
  //  128       10     default, tested
  //  128       40
  //  256       10
  //  256       40


  //  returns true  ==>  parameter gain is valid
  //  returns false ==>  parameter gain is invalid ==> no change.
  //  note that changing gain/channel takes up to 400 ms (page 3)
  //  if forced == true, the gain will be forced set
  //  even it is already the right value
  bool     set_gain_rate(uint16_t gain = HX712_GAIN_128,
                         uint8_t rate = 10);
  uint16_t get_gain();
  uint8_t  get_rate();


  ///////////////////////////////////////////////////////////////
  //
  //  TARE
  //  call tare to calibrate zero
  void     tare(uint8_t times = 10);
  float    get_tare();
  bool     tare_set();


  ///////////////////////////////////////////////////////////////
  //
  //  CALIBRATION
  //
  //  SCALE > 0
  //  returns false if scale == 0;
  bool     set_scale(float scale = 1.0);
  float    get_scale();

  //  OFFSET > 0
  void     set_offset(int32_t offset = 0);
  int32_t  get_offset();

  //  clear the scale
  //  call tare() to set the zero offset
  //  put a known weight on the scale
  //  call calibrate_scale(weight)
  //  scale is calculated.
  void     calibrate_scale(float weight, uint8_t times = 10);


  ///////////////////////////////////////////////////////////////
  //
  //  POWER MANAGEMENT
  //
  void     power_down();
  void     power_up();

  //  TIME OF LAST READ
  uint32_t last_time_read();


private:
  uint8_t  _dataPin;
  uint8_t  _clockPin;

  int32_t  _offset;
  float    _scale;
  uint16_t _gain;
  uint32_t _lastTimeRead;
  uint8_t  _mode;
  bool     _fastProcessor;
  uint8_t  _rate = 10;

  void     _insertSort(float * array, uint8_t size);
  uint8_t  _shiftIn();
};


//  -- END OF FILE --

