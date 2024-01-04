#pragma once
//
//    FILE: LTC2991.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2021-05-10
// PURPOSE: Library for LTC2991 temperature and voltage control IC
//     URL: https://github.com/RobTillaart/LTC2991


#include "Arduino.h"
#include "Wire.h"


#define LTC2991_LIB_VERSION               (F("0.2.1"))

//
//  DEFINES for readability
//
#define LTC2991_NEW_DATA                  0x01
#define LTC2991_NO_DATA                   0x00

#define LTC2991_BUSY                      0x01
#define LTC2991_IDLE                      0x00

#define LTC2991_TRIGGER_ENABLED           0x01
#define LTC2991_TRIGGER_DISABLED          0x00

#define LTC2991_FILTER_ENABLED            0x01
#define LTC2991_FILTER_DISABLED           0x00

#define LTC2991_VOLTAGE_DIFF              0x01
#define LTC2991_VOLTAGE_NORMAL            0x00

#define LTC2991_PWM_INVERTED              0x01
#define LTC2991_PWM_NORMAL                0x00

#define LTC2991_PWM_ENABLED               0x01
#define LTC2991_PWM_DISABLED              0x00

#define LTC2991_MODE_REPEAT               0x01
#define LTC2991_MODE_SINGLE               0x00

#define LTC2991_TINTERN_ENABLED           0x01
#define LTC2991_TINTERN_DISABLED          0x00

#define LTC2991_TINTERN_FILTER_ENABLED    0x01
#define LTC2991_TINTERN_FILTER_DISABLED   0x00

#define LTC2991_KELVIN                    0x01
#define LTC2991_CELSIUS                   0x00


class LTC2991
{
public:
  explicit LTC2991(const uint8_t address, TwoWire *wire = &Wire);

  bool    begin();
  bool    isConnected();
  uint8_t getAddress();

  //
  //  CORE functions
  //
  //  channel = 1..8
  bool    new_data(uint8_t channel);  //  external
  bool    new_temperature();          //  internal
  bool    new_voltage();              //  VCC
  bool    is_busy();


  //
  //  EXTERNAL CHANNELS  (8 voltage, 4 differentials or 4 temperature)
  //
  //      n = 1 ==> V1 V2  T1
  //      n = 2 ==> V3 V4  T2
  //      n = 3 ==> V5 V6  T3
  //      n = 4 ==> V7 V8  T4
  //
  void    trigger_conversion(uint8_t n);  //  wrapper around enable()
  void    trigger_conversion_all();
  void    enable(uint8_t n, bool enable);
  bool    is_enabled(uint8_t n);


  //      n: 1..4  see above
  void    enable_filter(uint8_t n, bool enable);
  bool    is_enabled_filter(uint8_t n);

  void    set_Kelvin(uint8_t n);      //  implicit set_mode_temperature
  void    set_Celsius(uint8_t n);     //  implicit set_mode_temperature
  void    set_temp_scale(uint8_t n, bool Kelvin = true);
  char    get_temp_scale(uint8_t n);           //  returns 'C' or 'K'
  void    set_mode_temperature(uint8_t n);

  void    set_mode_voltage_differential(uint8_t n);
  void    set_mode_voltage_normal(uint8_t n);
  uint8_t get_operational_mode(uint8_t n);     //  enumeration?
  uint8_t get_differential_mode(uint8_t n);
  float   get_value(uint8_t channel);          //  chan = 1..8


  //
  //  PWM functions
  //
  //  value = 0..511
  void     set_PWM(uint16_t value = 0);
  void     set_PWM_fast(uint16_t value = 0);   //  less resolution
  uint16_t get_PWM();
  void     invert_PWM(bool invert = false);
  bool     is_inverted_PWM();
  void     enable_PWM(bool enable);
  bool     is_enabled_PWM();


  //
  //  CONFIGURATION
  //
  void     set_acquisition_repeat();
  void     set_acquisition_single();
  uint8_t  get_acquisition_mode();


  //
  //  INTERNAL SENSORS
  //
  void     enable_Tintern_Vcc(bool enable);
  bool     is_enabled_Tintern_Vcc();
  void     enable_filter_Tintern(bool enable);
  bool     is_enabled_filter_Tintern();

  void     set_Kelvin_Tintern();
  void     set_Celsius_Tintern();
  void     set_temp_scale_Tintern(bool Kelvin = true);
  char     get_temp_scale_Tintern();         //  returns 'C' or 'K'
  float    get_Tintern();
  float    get_VCC();


private:

  uint8_t  _writeRegister(const uint8_t reg, const uint8_t value);
  uint8_t  _readRegister(const uint8_t reg);
  uint16_t _readRegister16(const uint8_t reg);


  void     _setRegisterMask(const uint8_t reg, uint8_t mask);
  void     _clrRegisterMask(const uint8_t reg, uint8_t mask);
  uint8_t  _getRegisterMask(const uint8_t reg, uint8_t mask);

  uint8_t   _address;
  TwoWire * _wire;

};


//  -- END OF FILE --

