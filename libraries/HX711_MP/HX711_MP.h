#pragma once
//
//    FILE: HX711_MP.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Library for load cells for Arduino
//     URL: https://github.com/RobTillaart/HX711_MP
//     URL: https://github.com/RobTillaart/HX711
//
//  NOTES
//  Superset of interface of HX711 class of Bogde
//  uses float instead of long as float has 23 bits mantissa
//  which almost perfectly matches the 24 bit ADC.


#include "Arduino.h"

#define HX711_MP_LIB_VERSION               (F("0.3.0"))


const uint8_t HX711_AVERAGE_MODE = 0x00;
//  in median mode only between 3 and 15 samples are allowed.
const uint8_t HX711_MEDIAN_MODE  = 0x01;
//  medavg = average of the middle "half" of sorted elements
//  in medavg mode only between 3 and 15 samples are allowed.
const uint8_t HX711_MEDAVG_MODE  = 0x02;
//  runavg = running average
const uint8_t HX711_RUNAVG_MODE  = 0x03;
//  causes read() to be called only once!
const uint8_t HX711_RAW_MODE     = 0x04;


//  supported values for set_gain()
const uint8_t HX711_CHANNEL_A_GAIN_128 = 128;  //  default
const uint8_t HX711_CHANNEL_A_GAIN_64 = 64;
const uint8_t HX711_CHANNEL_B_GAIN_32 = 32;

//  maximum size for internal mapping array
const uint8_t HX711_MP_MAX_SIZE = 10;


class HX711_MP
{
public:
  HX711_MP(uint8_t size);
  ~HX711_MP();

  //  fixed gain 128 for now
  void     begin(uint8_t dataPin, uint8_t clockPin, bool fastProcessor = false);

  void     reset();

  //  checks if load cell is ready to read.
  bool     is_ready();

  //  wait until ready,
  //  check every ms
  void     wait_ready(uint32_t ms = 0);
  //  max # retries
  bool     wait_ready_retry(uint8_t retries = 3, uint32_t ms = 0);
  //  max timeout
  bool     wait_ready_timeout(uint32_t timeout = 1000, uint32_t ms = 0);


  ///////////////////////////////////////////////////////////////
  //
  //  READ
  //
  //  raw read
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


  //  primary user functions
  //  in HX711_RAW_MODE the parameter times will be ignored.
  float    get_value(uint8_t times = 1);
  //  converted to proper units.
  //  in HX711_RAW_MODE the parameter times will be ignored.
  float    get_units(uint8_t times = 1);


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


  ///////////////////////////////////////////////////////////////
  //
  //  GAIN
  //
  //  CORE "CONSTANTS" -> read datasheet
  //  CHANNEL      GAIN   notes
  //  -------------------------------------
  //     A         128    default, tested
  //     A          64
  //     B          32

  //  returns true  ==>  parameter gain is valid
  //  returns false ==>  parameter gain is invalid ==> no change.
  //  note that changing gain/channel takes up to 400 ms (page 3)
  //  if forced == true, the gain will be forced set
  //  even it is already the right value
  bool     set_gain(uint8_t gain = HX711_CHANNEL_A_GAIN_128, bool forced = false);
  uint8_t  get_gain();


  ///////////////////////////////////////////////////////////////
  //
  //  CALIBRATION
  //
  //  clear the scale
  //  call tare() to set the zero offset  (index 0)
  //
  //  put a series of SIZE known weights on the scale in increasing order
  //      thereby skipping 0 (as that is the tare)
  //  call calibrate_scale(index, raw, weight)
  //       index  = 0..size -1
  //       raw    = raw read = getValue() made in any mode
  //       weight = weight in units
  //  setCalibrate() can be adjusted runtime.
  bool     setCalibrate(uint8_t index, float raw, float weight);
  uint8_t  getCalibrateSize();
  float    getCalibrateRaw(uint8_t index);
  float    adjustCalibrateRaw(uint8_t index, float amount);
  float    getCalibrateWeight(uint8_t index);


  ///////////////////////////////////////////////////////////////
  //
  //  POWER MANAGEMENT
  //
  void     power_down();
  void     power_up();


  //  TIME OF LAST READ
  uint32_t last_read();


  ///////////////////////////////////////////////////////////////
  //
  //  DEBUG
  //
  float    testCalibration(float raw)
  {
    return _multiMap(raw);
  }


private:
  uint8_t  _dataPin;
  uint8_t  _clockPin;

  uint8_t  _gain;
  uint32_t _lastRead;
  uint8_t  _mode;

  void     _insertSort(float * array, uint8_t size);
  uint8_t  _shiftIn();

  //  calibration arrays.
  float    _in[HX711_MP_MAX_SIZE];
  float    _out[HX711_MP_MAX_SIZE];
  uint8_t  _size = HX711_MP_MAX_SIZE;
  float    _multiMap(float val);
  bool     _fastProcessor = false;
};


//  -- END OF FILE --

