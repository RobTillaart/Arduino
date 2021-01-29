#pragma once
//
//    FILE: HX711.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Library for Loadcells for UNO
//     URL: https://github.com/RobTillaart/HX711
//
// HISTORY: see HX711.cpp
//
// NOTES
// Superset of interface of HX711 class of Bogde
// float iso long as float has 23 bits mantisse.


#include "Arduino.h"

#define HX711_LIB_VERSION  (F("0.2.1"))

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
  // multiple raw reads
  float    read_average(uint8_t times = 10);
  // corrected for offset
  float    get_value(uint8_t times = 1) { return read_average(times) - _offset; };
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
  void     set_scale(float scale = 1.0) { _scale = 1 / scale; };
  float    get_scale()                  { return 1 / _scale; };
  // OFFSET > 0
  void     set_offset(long offset = 0)  { _offset = offset; };
  long     get_offset()                 { return _offset; };

  // CALIBRATION
  // clear the scale
  // call tare() to set the zero offset
  // put a known weight on the scale 
  // call callibrate_scale(weight) 
  // scale is calculated.
  void     callibrate_scale(uint16_t weight, uint8_t times = 10);

  // POWER MANAGEMENT
  void     power_down();
  void     power_up();

  // TIME OF LAST READ
  uint32_t last_read()                  { return _lastRead; };

  // PRICING  (idem calories?)
  float    get_price(uint8_t times = 1) { return get_units(times) * _price; };
  void     set_unit_price(float price)  { _price = price; };
  float    get_unit_price()             { return _price; };

private:
  uint8_t  _dataPin;
  uint8_t  _clockPin;

  uint8_t  _gain     = 128;     // default channel A
  long     _offset   = 0;
  float    _scale    = 1;
  uint32_t _lastRead = 0;
  float    _price    = 0;
};

// -- END OF FILE --
