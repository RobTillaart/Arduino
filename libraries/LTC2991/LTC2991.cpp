//
//    FILE: LTC2991.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2021-05-10
// PURPOSE: Library for LTC2991 temperature and voltage control IC
//     URL: https://github.com/RobTillaart/LTC2991


#include "LTC2991.h"


/////////////////////////////////////////////////////
//
//  REGISTERS
//
#define STATUS_LOW            0x00
#define STATUS_HIGH           0x01
// 0x02..0x05 reserved
#define CONTROL_V1_V4         0x06
#define CONTROL_V5_V8         0x07
#define PWM_THRESHOLD_LSB     0x08
#define PWM_THRESHOLD_MSB     0x09

#define V_BASE                0x0A
#define V1_MSB                0x0A
#define V1_LSB                0x0B
#define V2_MSB                0x0C
#define V2_LSB                0x0D
#define V3_MSB                0x0E
#define V3_LSB                0x0F
#define V4_MSB                0x10
#define V4_LSB                0x11
#define V5_MSB                0x12
#define V5_LSB                0x13
#define V6_MSB                0x14
#define V6_LSB                0x15
#define V7_MSB                0x16
#define V7_LSB                0x17
#define V8_MSB                0x18
#define V8_lSB                0x19

#define T_INTERNAL_MSB        0x1A
#define T_INTERNAL_LSB        0x1B
#define VCC_MSB               0x1C
#define VCC_LSB               0x1D


/////////////////////////////////////////////////////
//
//  MAGIC NUMBERS
//
//  PAGE 21
const float SINGLE_ENDED_FACTOR  = 2.5 / 8192;     //  2^13
const float DIFFERENTIAL_FACTOR  = 2.5 / 131072;   //  2^17
const float VCC_FACTOR           = 2.5 / 8192;     //  2^13
const float TEMPERATURE_FACTOR   = 1.0 / 16;
const float DIODE_VOLTAGE_FACTOR = 2.5 / 65536;    //  2^16


/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
//
LTC2991::LTC2991(const uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


bool LTC2991::begin()
{
  if (! isConnected()) return false;
  return true;
}


bool LTC2991::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t LTC2991::getAddress()
{
  return _address;
}


//
//  CORE functions
//
bool LTC2991::new_data(uint8_t channel)
{
  uint8_t x = _readRegister(STATUS_LOW);
  //  LTC2991_NEW_DATA / NONE
  return (x & (1 << (channel - 1))) > 0;
}


bool LTC2991::new_temperature()
{
  uint8_t x = _readRegister(STATUS_HIGH);
  //  LTC2991_NEW_DATA / NONE
  return (x & 0x02) > 0;
}


bool LTC2991::new_voltage()
{
  uint8_t x = _readRegister(STATUS_HIGH);
  //  LTC2991_NEW_DATA / ??
  return (x & 0x01) > 0;
}


bool LTC2991::is_busy()
{
  uint8_t x = _readRegister(STATUS_HIGH);
  //  LTC2991_BUSY / IDLE
  return (x & 0x04) > 0;
}


//////////////////////////////////////////////////////////////////
//
//  EXTERNAL CHANNELS  (8 voltage or 4 temperature)
//
void LTC2991::trigger_conversion(uint8_t n)
{
  enable(n, true);
}


void LTC2991::trigger_conversion_all()
{
  _setRegisterMask(STATUS_HIGH, 0xF0);
}


void LTC2991::enable(uint8_t n, bool enable)
{
  if (enable) _setRegisterMask(STATUS_HIGH, (0x08 << n));
  else        _clrRegisterMask(STATUS_HIGH, (0x08 << n));
}


bool LTC2991::is_enabled(uint8_t n)
{
  uint8_t x = _readRegister(STATUS_HIGH);
  //  LTC2991_TRIGGER_ENABLED / DISABLED
  return (x & (0x08 << n)) > 0;
}


void LTC2991::enable_filter(uint8_t n, bool enable)
{
  uint8_t reg = CONTROL_V1_V4;
  if (n > 2)
  {
    reg++;
    n -= 2;
  }
  uint8_t    mask = 0x08;
  if (n > 1) mask = 0x80;
  if (enable) _setRegisterMask(reg, mask);
  else        _clrRegisterMask(reg, mask);
}


bool LTC2991::is_enabled_filter(uint8_t n)
{
  uint8_t reg = CONTROL_V1_V4;
  if (n > 2)
  {
    reg++;
    n -= 2;
  }
  uint8_t    mask = 0x08;
  if (n > 1) mask = 0x80;
  //  LTC2991_FILTER_ENABLED / DISABLED
  return _getRegisterMask(reg, mask) > 0;
}


//  can be more efficient in one register addressing.
void LTC2991::set_Kelvin(uint8_t n)
{
  set_temp_scale(n, true);
  set_mode_temperature(n);
};


//  can be more efficient in one register addressing.
void LTC2991::set_Celsius(uint8_t n)
{
  set_temp_scale(n, false);
  set_mode_temperature(n);
};


void LTC2991::set_temp_scale(uint8_t n, bool Kelvin)
{
  uint8_t reg = CONTROL_V1_V4;
  if (n > 2)
  {
    reg++;
    n -= 2;
  }
  uint8_t    mask = 0x04;
  if (n > 1) mask = 0x40;
  if (Kelvin) _setRegisterMask(reg, mask);
  else        _clrRegisterMask(reg, mask);
}


char LTC2991::get_temp_scale(uint8_t n)
{
  uint8_t reg = CONTROL_V1_V4;
  if (n > 2)
  {
    reg++;
    n -= 2;
  }
  uint8_t    mask = 0x04;
  if (n > 1) mask = 0x40;
  if (_getRegisterMask(reg, mask) > 0)
  {
    return 'K';
  }
  return 'C';
}


void LTC2991::set_mode_temperature(uint8_t n)
{
  uint8_t reg = CONTROL_V1_V4;
  if (n > 2)
  {
    reg++;
    n -= 2;
  }
  uint8_t    mask = 0x02;
  if (n > 1) mask = 0x20;
  _setRegisterMask(reg, mask);
}


void LTC2991::set_mode_voltage_differential(uint8_t n)
{
  uint8_t reg = CONTROL_V1_V4;
  if (n > 2)
  {
    reg++;
    n -= 2;
  }
  uint8_t    mask = 0x02;    //  3 == voltage | differential
  if (n > 1) mask = 0x20;
  _clrRegisterMask(reg, mask);
  mask >>= 1;
  _setRegisterMask(reg, mask);
}


void LTC2991::set_mode_voltage_normal(uint8_t n)
{
  uint8_t reg = CONTROL_V1_V4;
  if (n > 2)
  {
    reg++;
    n -= 2;
  }
  uint8_t    mask = 0x02;
  if (n > 1) mask = 0x20;
  _clrRegisterMask(reg, mask);
  mask >>= 1;
  _clrRegisterMask(reg, mask);
}


uint8_t LTC2991::get_operational_mode(uint8_t n)
{
  uint8_t reg = CONTROL_V1_V4;
  if (n > 2)
  {
    reg++;
    n -= 2;
  }
  uint8_t    mask = 0x02;
  if (n > 1) mask = 0x20;
  if (_getRegisterMask(reg, mask) > 0) return 1;
  return 0;
}


uint8_t LTC2991::get_differential_mode(uint8_t n)
{
  uint8_t reg = CONTROL_V1_V4;
  if (n > 2)
  {
    reg++;
    n -= 2;
  }
  uint8_t    mask = 0x01;
  if (n > 1) mask = 0x10;
  //  LTC2991_VOLTAGE_DIFF / NORMAL ???
  if (_getRegisterMask(reg, mask) > 0) return 1;
  return 0;
}


float LTC2991::get_value(uint8_t channel)
{
  uint8_t chan = channel - 1;
  uint8_t pair = (channel + 1)/2;
  int16_t v = _readRegister16(V_BASE + chan * 2);

  if (get_operational_mode(pair) > 0)  //  temperature
  {
    if (get_temp_scale(pair) == 'K')   //  KELVIN
    {
      return TEMPERATURE_FACTOR * (float)v;
    }
    //  CELSIUS positive
    if ((v & 0x1000) == 0)
    {
      return TEMPERATURE_FACTOR * (float)v;
    }
    //  CELSIUS neg two complements  (page 13, 2nd column.)
    v = (v^0x1FFF) + 1;
    return TEMPERATURE_FACTOR * (float)v * -1.0;
  }

  if (get_differential_mode(pair) == 0)  //  SINGLE ENDED
  {
    if ((v & 0x4000) == 0)
    {
      return SINGLE_ENDED_FACTOR * (float)v;
    }
    v = (v^0x7FFFF) + 1;
    return SINGLE_ENDED_FACTOR * (float)v * -1.0;
  }
  //  DIFFERENTIAL
  if ((v & 0x4000) == 0)
  {
    return DIFFERENTIAL_FACTOR * (float)v;
  }
  v = (v^0x7FFFF) + 1;
  return DIFFERENTIAL_FACTOR * (float)v * -1.0;
}


//////////////////////////////////////////////////////////////////
//
//  PWM functions
//
void LTC2991::set_PWM(uint16_t value)
{
  if (value > 511) value = 511;
  _writeRegister(PWM_THRESHOLD_MSB, value >> 1);
  if (value & 0x01) _setRegisterMask(PWM_THRESHOLD_LSB, 0x80);
  else              _clrRegisterMask(PWM_THRESHOLD_LSB, 0x80);
}


void LTC2991::set_PWM_fast(uint16_t value)
{
  if (value > 511) value = 511;
  _writeRegister(PWM_THRESHOLD_MSB, value >> 1);
  //  last bit is never set, only when value is zero
  //  to be sure there is no dangling bit.
  if (value == 0) _clrRegisterMask(PWM_THRESHOLD_LSB, 0x80);
}


uint16_t LTC2991::get_PWM()
{
  uint16_t pwm = _readRegister(PWM_THRESHOLD_MSB);
  pwm <<= 1;
  if (_readRegister(PWM_THRESHOLD_LSB) > 0 ) pwm |= 0x01;
  return pwm;
}


void LTC2991::invert_PWM(bool invert)
{
  if (invert) _setRegisterMask(PWM_THRESHOLD_LSB, 0x40);
  else        _clrRegisterMask(PWM_THRESHOLD_LSB, 0x40);
}


bool LTC2991::is_inverted_PWM()
{
  //  LTC2991_PWM_INVERTED /  LTC2991_PWM_NORMAL
  return _getRegisterMask(PWM_THRESHOLD_LSB, 0x40) > 0;
}


void LTC2991::enable_PWM(bool enable)
{
  if (enable) _setRegisterMask(PWM_THRESHOLD_LSB, 0x20);
  else        _clrRegisterMask(PWM_THRESHOLD_LSB, 0x20);
}


bool LTC2991::is_enabled_PWM()
{
  //  LTC2991_PWM_ENABLED /  LTC2991_PWM_DISABLED
  return _getRegisterMask(PWM_THRESHOLD_LSB, 0x20) > 0;
}


//////////////////////////////////////////////////////////////////
//
//  CONFIGURATION
//
void LTC2991::set_acquisition_repeat()
{
  _setRegisterMask(PWM_THRESHOLD_LSB, 0x10);
}


void LTC2991::set_acquisition_single()
{
  _clrRegisterMask(PWM_THRESHOLD_LSB, 0x10);
}


uint8_t LTC2991::get_acquisition_mode()
{
  //  LTC2991_MODE_REPEAT / LTC2991_MODE_SINGLE
  if (_getRegisterMask(PWM_THRESHOLD_LSB, 0x10) > 0) return 1;
  return 0;
}


//////////////////////////////////////////////////////////////////
//
//  INTERNAL SENSORS
//
void LTC2991::enable_Tintern_Vcc(bool enable)
{
  if (enable) _setRegisterMask(STATUS_HIGH, 0x08);
  else        _clrRegisterMask(STATUS_HIGH, 0x08);
}


bool LTC2991::is_enabled_Tintern_Vcc()
{
  uint8_t x = _readRegister(STATUS_HIGH);
  //  LTC2991_TINTERN_ENABLED / DISABLED
  return ((x & 0x08) > 0);
}


void LTC2991::enable_filter_Tintern(bool enable)
{
  if (enable) _setRegisterMask(PWM_THRESHOLD_LSB, 0x08);
  else        _clrRegisterMask(PWM_THRESHOLD_LSB, 0x08);
}


bool LTC2991::is_enabled_filter_Tintern()
{
  //  LTC2991_TINTERN_FILTER_ENABLED / DISABLED
  return _getRegisterMask(PWM_THRESHOLD_LSB, 0x08) > 0;
}


void LTC2991::set_Kelvin_Tintern()
{
  set_temp_scale_Tintern(true);
}


void LTC2991::set_Celsius_Tintern()
{
  set_temp_scale_Tintern(false);
}


//  true = Kelvin, false = Celsius
void LTC2991::set_temp_scale_Tintern(bool Kelvin)
{
  if (Kelvin) _setRegisterMask(PWM_THRESHOLD_LSB, 0x04);
  else        _clrRegisterMask(PWM_THRESHOLD_LSB, 0x04);
}


char LTC2991::get_temp_scale_Tintern()
{
  if (_getRegisterMask(PWM_THRESHOLD_LSB, 0x04) > 0)
  {
    return 'K';   //  LTC2991_KELVIN
  }
  return 'C';     //  LTC2991_CELSIUS
}


float LTC2991::get_Tintern()
{
  int16_t v = _readRegister16(T_INTERNAL_MSB);

  if (get_temp_scale_Tintern() == 'K')
  {
    return TEMPERATURE_FACTOR * (float)v;
  }
  //  CELSIUS positive value
  if ((v & 0x1000) == 0)
  {
    return TEMPERATURE_FACTOR * (float)v;
  }
  //  CELSIUS neg two complements  (page 13, 2nd colom.)
  v = (v^0x1FFF) + 1;
  return TEMPERATURE_FACTOR * (float)v * -1.0;
}


float LTC2991::get_VCC()
{
  int16_t v = _readRegister16(VCC_MSB);
  if ((v & 0x4000) == 0)
  {
    return VCC_FACTOR * (float)v + 2.5;
  }
  //  can Vcc be negative?
  v = (v^0x7FFFF) + 1;
  return VCC_FACTOR * (float)v * -1.0 + 2.5;
}



//////////////////////////////////////////////////////////////////
//
//  PRIVATE functions
//
uint8_t LTC2991::_writeRegister(const uint8_t reg, const uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  return _wire->endTransmission();
}


uint8_t LTC2991::_readRegister(const uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->endTransmission();

  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


uint16_t LTC2991::_readRegister16(const uint8_t reg)
{
  uint16_t x = _readRegister(reg) << 8;
  x |= _readRegister(reg + 1);
  //  bool dataValid = (x & 0x8000) > 0;   //  TODO error handling
  x &= 0x7FFF;
  return x;
}


void LTC2991::_setRegisterMask(const uint8_t reg, uint8_t mask)
{
  uint8_t x = _readRegister(reg);
  if ((x & mask) != mask)   //  if not all bits set, set them
  {
    x |= mask;
    _writeRegister(reg, x);
  }
}


void LTC2991::_clrRegisterMask(const uint8_t reg, uint8_t mask)
{
  uint8_t x = _readRegister(reg);
  if (x | mask)         //  if any bit of the mask set clear it
  {
    x &= ~mask;
    _writeRegister(reg, x);
  }
}


uint8_t LTC2991::_getRegisterMask(const uint8_t reg, uint8_t mask)
{
  uint8_t x = _readRegister(reg);
  return x & mask;
}


//  -- END OF FILE --

