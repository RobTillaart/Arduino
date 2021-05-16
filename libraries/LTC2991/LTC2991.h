#pragma once
//
//    FILE: LTC2991.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-05-10
// PURPOSE: Library for LTC2991 temperature and voltage control IC
//     URL: https://github.com/RobTillaart/LTC2991


#include "Arduino.h"
#include "Wire.h"

#define LTC2991_LIB_VERSION         (F("0.1.0"))


class LTC2991
{
public:
  explicit LTC2991(const int8_t address, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool    begin(uint8_t sda, uint8_t scl);
#endif

  bool    begin();
  bool    isConnected();


  // REGISTER 0x00 .. 0x01
  // channel = 1..8
  bool    new_data(uint8_t channel);  // external
  bool    new_temperature();          // internal
  bool    new_voltage();              // VCC
  bool    is_busy();

  //
  // EXTERNAL CHANNELS  (8 voltage or 4 temperature)
  //
  // n = 1 ==> V1 V2  T1
  // n = 2 ==> V3 V4  T2
  // n = 3 ==> V5 V6  T3
  // n = 4 ==> V7 V8  T4
  void    enable(uint8_t n, bool enable);
  bool    is_enabled(uint8_t n);

  // REGISTER 0x06 .. 0x07
  //    n: 1..4
  void    enable_filter(uint8_t n, bool enable);
  bool    is_enabled_filter(uint8_t n);
  void    set_Kelvin(uint8_t n);  // implicit set_mode_temperature
  void    set_Celsius(uint8_t n); // implicit set_mode_temperature
  void    set_temp_scale(uint8_t n, bool Kelvin = true);  // MIGHT BECOME OBSOLETE ?
  //      returns 'C' or 'K'
  char    get_temp_scale(uint8_t n);
  void    set_mode_temperature(uint8_t n);
  void    set_mode_voltage_differential(uint8_t n);
  void    set_mode_voltage_normal(uint8_t n);
  uint8_t get_operational_mode(uint8_t n);
  uint8_t get_differential_mode(uint8_t n);

  // REGISTER 0x0A .. 0x19
  float    get_value(uint8_t channel);      // chan = 1..8



  //
  // PWM
  //
  // REGISTER 0x08 .. 0x09
  // value = 0..511
  void     set_PWM(uint16_t value);
  uint16_t get_PWM();
  void     invert_PWM(bool invert);
  bool     is_inverted_PWM();
  void     enable_PWM(bool enable);
  bool     is_enabled_PWM();


  //
  // CONFIGURATION
  //
  void     set_acquisition_repeat();
  void     set_acquisition_single();
  uint8_t  get_acquisition_mode();


  //
  // INTERNAL SENSORS
  //
  void     enable_Tintern_Vcc(bool enable);
  bool     is_enabled_Tintern_Vcc();
  void     enable_filter_Tintern(bool enable);
  bool     is_enabled_filter_Tintern();
  void     set_Kelvin_Tintern()   { set_temp_scale_Tintern(true); };
  void     set_Celsius_Tintern()  { set_temp_scale_Tintern(false); };
  void     set_temp_scale_Tintern(bool Kelvin = true);
  //      returns 'C' or 'K'
  char     get_temp_scale_Tintern();
  // REGISTER 0x1A .. 0x1B
  float    get_Tintern();
  // REGISTER 0x1C .. 0x1D
  float    get_VCC();


private:

  uint8_t  _writeRegister(const uint8_t reg, const uint8_t value);
  uint8_t  _readRegister(const uint8_t reg);
  uint16_t _readRegister16(const uint8_t reg);


  void    _setRegisterMask(const uint8_t reg, uint8_t mask);
  void    _clrRegisterMask(const uint8_t reg, uint8_t mask);
  uint8_t _getRegisterMask(const uint8_t reg, uint8_t mask);

  uint8_t   _address;
  TwoWire * _wire;

};

// -- END OF FILE --
