#pragma once
//
//    FILE: HX711.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: Library for Loadcells for UNO
//     URL: https://github.com/RobTillaart/HX711
//
// HISTORY: see HX711.cpp
//
// NOTES
// Superset of interface of HX711 class of Bogde
// float iso long as float has 23 bits mantisse.


#include "Arduino.h"

#define HX711_LIB_VERSION  (F("0.2.3"))


const uint8_t HX711_AVERAGE_MODE = 0x00;
// in median mode only between 3 and 15 samples are allowed.
const uint8_t HX711_MEDIAN_MODE = 0x01;
// medavg = average of the middle "half" of sorted elements
// in medavg mode only between 3 and 15 samples are allowed.
const uint8_t HX711_MEDAVG_MODE = 0x02;
// runavg = running average
const uint8_t HX711_RUNAVG_MODE = 0x03;


class HX711
{
public:
  HX711();
  ~HX711();

  // fixed gain 128 for now
  void     begin(uint8_t dataPin, uint8_t clockPin);

  void     reset();

  // checks if loadcell is ready to read.
  bool     is_ready();
  
  // wait until ready, 
  // check every ms
  void     wait_ready(uint32_t ms = 0);
  // max # retries
  bool     wait_ready_retry(uint8_t retries = 3, uint32_t ms = 0);
  // max timeout
  bool     wait_ready_timeout(uint32_t timeout = 1000, uint32_t ms = 0);

  // raw read
  float    read();
  // get average of multiple raw reads
  // times = 1 or more
  float    read_average(uint8_t times = 10);

  // get median of multiple raw reads  
  // times = 3..15 - odd numbers preferred
  float    read_median(uint8_t times = 7);  

  // get average of "middle half" of multiple raw reads.
  // times = 3..15 - odd numbers preferred
  float    read_medavg(uint8_t times = 7);  

  // get running average over times measurements.
  // the weight alpha can be set to any value between 0 and 1
  // times = 1 or more.
  float    read_runavg(uint8_t times = 7, float alpha = 0.5);  


  // get set mode for get_value() and indirect get_units().
  // in median and medavg mode only 3..15 samples are allowed.
  void     set_average_mode() { _mode = HX711_AVERAGE_MODE; };
  void     set_median_mode()  { _mode = HX711_MEDIAN_MODE; };
  void     set_medavg_mode()  { _mode = HX711_MEDAVG_MODE; };
  // set_run_avg will use a default alpha of 0.5.
  void     set_runavg_mode()  { _mode = HX711_RUNAVG_MODE; };
  uint8_t  get_mode()         { return _mode; };
 
  // corrected for offset
  float    get_value(uint8_t times = 1);
  // converted to proper units.
  float    get_units(uint8_t times = 1);


  // TARE
  // call tare to calibrate zero
  void     tare(uint8_t times = 10)     { _offset = read_average(times); };
  float    get_tare()                   { return -_offset * _scale; };
  bool     tare_set()                   { return _offset != 0; };


  // CORE "CONSTANTS" -> read datasheet
  // GAIN values: 128, 64 32  [only 128 tested & verified]
  void     set_gain(uint8_t gain = 128) { _gain = gain; };
  uint8_t  get_gain()                   { return _gain; };
  // SCALE > 0
  void     set_scale(float scale = 1.0) { _scale = 1.0 / scale; };
  float    get_scale()                  { return 1.0 / _scale; };
  // OFFSET > 0
  void     set_offset(long offset = 0)  { _offset = offset; };
  long     get_offset()                 { return _offset; };


  // CALIBRATION
  // clear the scale
  // call tare() to set the zero offset
  // put a known weight on the scale 
  // call calibrate_scale(weight) 
  // scale is calculated.
  void     calibrate_scale(uint16_t weight, uint8_t times = 10);
  // obsolete typo but just do not want to break interface yet
  void     callibrate_scale(uint16_t weight, uint8_t times = 10); 


  // POWER MANAGEMENT
  void     power_down();
  void     power_up();


  // TIME OF LAST READ
  uint32_t last_read()                  { return _lastRead; };


  // PRICING  (idem calories?)
  float    get_price(uint8_t times = 1) { return get_units(times) * _price; };
  void     set_unit_price(float price = 1.0) { _price = price; };
  float    get_unit_price() { return _price; };


private:
  uint8_t  _dataPin;
  uint8_t  _clockPin;

  uint8_t  _gain     = 128;     // default channel A
  long     _offset   = 0;
  float    _scale    = 1;
  uint32_t _lastRead = 0;
  float    _price    = 0;
  uint8_t  _mode     = 0;

  void     _insertSort(float * array, uint8_t size);
};

// -- END OF FILE --
