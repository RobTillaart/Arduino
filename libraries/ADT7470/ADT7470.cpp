//
//    FILE: ADT7470.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for I2C ADT7470 Fan Monitoring
//     URL: https://github.com/RobTillaart/ADT7470
//          http://forum.arduino.cc/index.php?topic=363218.0
//


#include "ADT7470.h"


// CONFIG REGISTER 1
#define ADT7470_CONFIG_REGISTER_1      0x40
// bits
#define ADT7470_START                  0x01
#define ADT7470_TODIS                  0x08
#define ADT7470_LOCK                   0x10
#define ADT7470_FAST_TACH              0x20
#define ADT7470_LOW_FREQ_DRIVE         0x40
#define ADT7470_T05_STB                0x80   // full speed pin

// CONFIG REGISTER 2
#define ADT7470_CONFIG_REGISTER_2      0x74
// bits
#define ADT7470_POWERDOWN              0x01

// OTHER REGISTERS
#define ADT7470_DEVICEID_REGISTER      0x3D
#define ADT7470_COMPANYID_REGISTER     0x3E
#define ADT7470_REVISION_REGISTER      0x3F

// TEMPERATURE
#define ADT7470_TEMP_BASE              0x20
#define ADT7470_TEMP_MAX               0x78
#define ADT7470_TEMP_LIMIT_BASE        0x44

// SPEED
#define ADT7470_TACH_BASE              0x2A
#define ADT7470_TACH_LOW_LIMIT_BASE    0x58
#define ADT7470_TACH_HIGH_LIMIT_BASE   0x60
#define ADT7470_FAN_PPR_REGISTER       0x43
#define ADT7470_FAN_PWM_BASE           0x32
// Page 21   invert PWM signal
#define ADT7470_FAN_PWM_CONFIG_1       0x68
#define ADT7470_FAN_PWM_CONFIG_2       0x69


// INTERRUPTS
#define ADT7470_IRQ_STATUS_1           0x41
#define ADT7470_IRQ_STATUS_2           0x42
#define ADT7470_IRQ_MASK_REG_1         0x72
#define ADT7470_IRQ_MASK_REG_2         0x73



//////////////////////////////////////////////////////////////////////////////
//
//  PUBLIC
//

ADT7470::ADT7470(uint8_t address, TwoWire *wire)
{
  _wire = wire;
  // allowed 0x2C, 0x2E, 0x2F
  _address = address;
}


bool ADT7470::begin()
{
  return isConnected();
}


//
//  GENERIC
//
bool ADT7470::isConnected()
{
  return ((getDeviceID() == 0x70) && (getCompanyID() == 0x41));
}


uint8_t ADT7470::getRevision()
{
  return getReg8(ADT7470_REVISION_REGISTER);
}


uint8_t ADT7470::getDeviceID()
{
  return getReg8(ADT7470_DEVICEID_REGISTER);
}


uint8_t ADT7470::getCompanyID()
{
  return getReg8(ADT7470_COMPANYID_REGISTER);
}


void ADT7470::startMonitoring()
{
  setRegMask(ADT7470_CONFIG_REGISTER_1, ADT7470_START);
}


void ADT7470::stopMonitoring()
{
  clrRegMask(ADT7470_CONFIG_REGISTER_1, ADT7470_START);
}


void ADT7470::powerDown()
{
  setRegMask(ADT7470_CONFIG_REGISTER_2, ADT7470_POWERDOWN);
}


void ADT7470::powerUp()
{
  clrRegMask(ADT7470_CONFIG_REGISTER_2, ADT7470_POWERDOWN);
}


//
//  MEASURE TEMPERATURE
//

//  TODO:
//  make these calls async as waiting up to 2 seconds is an 'eternity'
//  void startConversion();
//  bool conversionReady();
//  int8_t getTemperature(uin8_t index);
int8_t ADT7470::getTemperature(uint8_t index)
{
  if (index >= 10) return 0;
  //  1. Set Register 40 Bit[7] = 1. This starts the temperature measurements.
  setRegMask(ADT7470_CONFIG_REGISTER_1, ADT7470_T05_STB);
  //  2. Wait 200 ms for each TMP05/TMP06 in the loop.
  delay(2000);  // way to long
  //  3. Set Register 40 Bit[7] = 0.
  clrRegMask(ADT7470_CONFIG_REGISTER_1, ADT7470_T05_STB);
  //  4. Read the temperature registers.
  return (int8_t) getReg8(ADT7470_TEMP_BASE + index);
}


int8_t ADT7470::getMaxTemperature()
{
  return (int8_t)getReg8(ADT7470_TEMP_MAX);
}


bool ADT7470::setTemperatureLimit(uint8_t index, int8_t low, int8_t high)
{
  if ((index >= 10) || (low >= high)) return false;
  setReg8(ADT7470_TEMP_LIMIT_BASE + index * 2, low);
  setReg8(ADT7470_TEMP_LIMIT_BASE + index * 2 + 1, high);
  return true;
}


int8_t ADT7470::getTemperatureLowLimit(uint8_t index)
{
  int8_t rv = getReg8(ADT7470_TEMP_LIMIT_BASE + 2 * index);
  return rv;
}


int8_t ADT7470::getTemperatureHighLimit(uint8_t index)
{
  int8_t rv = getReg8(ADT7470_TEMP_LIMIT_BASE + 2 * index + 1);
  return rv;
}


//
//  SET FAN SPEED
//
bool ADT7470::setPWM(uint8_t index, uint8_t value)
{
  if (index >= 4) return false;
  setReg8(ADT7470_FAN_PWM_BASE + index, value);
  return true;
}


uint8_t ADT7470::getPWM(uint8_t index)
{
  if (index >= 4) return 0;
  return getReg8(ADT7470_FAN_PWM_BASE + index);
}


bool ADT7470::setFanLowFreq(uint8_t value)
{
  if (value > 7) return false;
  setRegMask(ADT7470_CONFIG_REGISTER_1, ADT7470_LOW_FREQ_DRIVE);
  //  make sure all bits are 0.
  //  Can be more efficient  check previous value.
  //  getReg8()
  //  if equal co change
  //  else clear bits & set
  //  write them
  clrRegMask(ADT7470_CONFIG_REGISTER_2, (0x07 << 4));  // clear 3 bits
  setRegMask(ADT7470_CONFIG_REGISTER_2, (value << 4));
  return true;
}


bool ADT7470::setFanHighFreq(uint8_t value)
{
  if (value > 7) return false;
  clrRegMask(ADT7470_CONFIG_REGISTER_1, ADT7470_LOW_FREQ_DRIVE);
  //  make sure all bits are 0 first.
  //  Can be more efficient  check previous value.
  clrRegMask(ADT7470_CONFIG_REGISTER_2, (0x07 << 4));  //  clear 3 bits
  setRegMask(ADT7470_CONFIG_REGISTER_2, (value << 4));
  return true;
}


void ADT7470::setInvertPWM(uint8_t index)
{
  if (index == 0) setReg8(ADT7470_FAN_PWM_CONFIG_1, 0x10);  //  bit 5
  if (index == 1) setReg8(ADT7470_FAN_PWM_CONFIG_1, 0x80);  //  bit 4
  if (index == 2) setReg8(ADT7470_FAN_PWM_CONFIG_2, 0x10);
  if (index == 3) setReg8(ADT7470_FAN_PWM_CONFIG_2, 0x80);
}


uint8_t ADT7470::getInvertPWM(uint8_t index)
{
  if (index == 0) return getReg8(ADT7470_FAN_PWM_CONFIG_1) & 0x10;
  if (index == 1) return getReg8(ADT7470_FAN_PWM_CONFIG_1) & 0x80;
  if (index == 2) return getReg8(ADT7470_FAN_PWM_CONFIG_2) & 0x10;
  if (index == 3) return getReg8(ADT7470_FAN_PWM_CONFIG_2) & 0x80;
  return 0;
}


//
//  MEASURE FAN SPEED
//
bool ADT7470::setPulsesPerRevolution(uint8_t index, uint8_t value)
{
  if (index >= 4) return false;
  if ((value == 0) || (value > 4)) return false;
  uint8_t mask = 0x03 << (index * 2);

  uint8_t reg;
  _read(ADT7470_FAN_PPR_REGISTER, &reg);
  reg &= ~mask;
  reg |= ((value - 1) << (index * 2));
  _write(ADT7470_FAN_PPR_REGISTER, reg);
  return true;
}


uint8_t ADT7470::getPulsesPerRevolution(uint8_t index)
{
  if (index >= 4) return 0;
  uint8_t reg = getReg8(ADT7470_FAN_PPR_REGISTER);
  return ((reg >> (index * 2)) & 0x03) + 1;
}


void ADT7470::setFastTach()
{
  setRegMask(ADT7470_CONFIG_REGISTER_1, ADT7470_FAST_TACH);
}


void ADT7470::setSlowTach()
{
  clrRegMask(ADT7470_CONFIG_REGISTER_1, ADT7470_FAST_TACH);
}


uint16_t ADT7470::getTach(uint8_t index)
{
  if (index >= 4) return 0;
  return getReg16(ADT7470_TACH_BASE + index * 2);
}


uint32_t ADT7470::getRPM(uint8_t index)
{
  if (index >= 4) return 0;
  uint32_t clock = 90000UL;
  uint16_t measurementsPerMinute = 60;
  uint16_t tach = getTach(index);

  //  P23 stalling tach or very slow < 100 ==> 0xFFFF
  if (tach == 0xFFFF) return 0;
  if (tach == 0) return 0;   //  explicit prevents divide by zero

  //  formula P24            //  tach/2 == integer rounding of division.
  return (clock * measurementsPerMinute + tach / 2) / tach;
}


//////////////////////////////////////////////////////////////////////////////

bool ADT7470::setTachLimits(uint8_t index, uint16_t low, uint16_t high)
{
  if ((index >= 4) || (low >= high)) return false;
  setReg16(ADT7470_TACH_LOW_LIMIT_BASE + index * 2, low);
  setReg16(ADT7470_TACH_HIGH_LIMIT_BASE + index * 2, high);
  return true;
}


uint16_t ADT7470::getTachLowLimits(uint8_t index)
{
  uint16_t rv = getReg16(ADT7470_TACH_LOW_LIMIT_BASE + index * 2);
  return rv;
}


uint16_t ADT7470::getTachHighLimits(uint8_t index)
{
  uint16_t rv = getReg16(ADT7470_TACH_HIGH_LIMIT_BASE + index * 2);
  return rv;
}


//
//  INTERRUPTS
//
uint16_t ADT7470::getTemperatureIRQstatus()
{
  //  TODO -  NORM bit not handled
  //  uint8_t NORM = (getReg8(ADT7470_IRQ_STATUS_2) & 0x08) >> 3;

  uint16_t value = 0;
  value = (getReg8(ADT7470_IRQ_STATUS_2) & 0x07) << 7;
  value |= (getReg8(ADT7470_IRQ_STATUS_1) & 0x7F);
  return value;
}


uint8_t ADT7470::getFanIRQstatus()
{
  uint8_t value = (getReg8(ADT7470_IRQ_STATUS_2) & 0xF0) >> 4;
  return value;
}


//  TODO MERGE? setTemperatureIRQMask(index, value);  ?
void ADT7470::setTemperatureIRQMask(uint8_t index)
{
  uint8_t reg = ADT7470_IRQ_MASK_REG_1;
  if (index > 7)
  {
    reg = ADT7470_IRQ_MASK_REG_2;
    index -= 7;
  }
  uint8_t value = getReg8(reg);
  value |= (1 << index);
  setReg8(reg, value);
}


void ADT7470::clrTemperatureIRQMask(uint8_t index)
{
  uint8_t reg = ADT7470_IRQ_MASK_REG_1;
  if (index > 7)
  {
    reg = ADT7470_IRQ_MASK_REG_2;
    index -= 7;
  }
  uint8_t value = getReg8(reg);
  value &= ~(1 << index);
  setReg8(reg, value);
}


uint8_t ADT7470::getTemperatureIRQMask(uint8_t index)
{
  uint8_t reg = ADT7470_IRQ_MASK_REG_1;
  if (index > 7)
  {
    reg = ADT7470_IRQ_MASK_REG_2;
    index -= 7;
  }
  return getReg8(reg) & (1 << index);
}


void ADT7470::setFanIRQMask(uint8_t index)
{
  uint8_t value = getReg8(ADT7470_IRQ_MASK_REG_2);
  value |= (1 << (index + 4));
  setReg8(ADT7470_IRQ_MASK_REG_2, value);
}


void ADT7470::clrFanIRQMask(uint8_t index)
{
  uint8_t value = getReg8(ADT7470_IRQ_MASK_REG_2);
  value &= ~(1 << (index + 4));
  setReg8(ADT7470_IRQ_MASK_REG_2, value);
}


uint8_t ADT7470::getFanIRQMask(uint8_t index)
{
  return getReg8(ADT7470_IRQ_MASK_REG_2) & (1 << (index + 4));
}


//////////////////////////////////////////////////////////////////////////////
//
//  REGISTER OPERATORS
//
void ADT7470::setRegMask(uint8_t reg, uint8_t mask)
{
  uint8_t prevMask;
  _read(reg, &prevMask, (uint8_t)1);
  prevMask |= mask;
  _write(reg, prevMask);
}


void ADT7470::clrRegMask(uint8_t reg, uint8_t mask)
{
  uint8_t prevMask;
  _read(reg, &prevMask, (uint8_t)1);
  prevMask &= ~mask;
  _write(reg, prevMask);
}


uint8_t ADT7470::getReg8(uint8_t reg)
{
  uint8_t value;
  _read(reg, &value);
  return value;
}


void ADT7470::setReg8(uint8_t reg, uint8_t value)
{
  _write(reg, value);
}


uint16_t ADT7470::getReg16(uint8_t reg)
{
  uint8_t h, l;
  _read(reg, &l);
  _read(reg + 1, &h);
  return (((uint16_t)h) << 8) | l;
}


void ADT7470::setReg16(uint8_t reg, uint16_t value)
{
  _write(reg + 1, value & 0xFF);
  _write(reg, value >> 8);
}


//////////////////////////////////////////////////////////////////////////////
//
//  PRIVATE - LOW LEVEL I2C
//
int ADT7470::_write(const uint8_t reg, uint8_t value)
{
  return _write(reg, &value, 1);
}


int ADT7470::_write(const uint8_t reg, uint8_t *buffer, uint8_t length)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  for (uint8_t i = 0; i < length; i++)
  {
    _wire->write(buffer[i]);
  }
  int rv = _wire->endTransmission();
  return rv;
}


int ADT7470::_read(const uint8_t reg, uint8_t *value)
{
  return _read(reg, value, 1);
}


int ADT7470::_read(const uint8_t reg, uint8_t *buffer, uint8_t length)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int rv = _wire->endTransmission(false);
  if (rv != 0) return 0;                  //  nothing read

  uint8_t len = _wire->requestFrom(_address, length);
  uint8_t cnt = 0;
  uint32_t before = millis();
  while ((cnt < len) && ((millis() - before) < ADT7470_TIMEOUT))
  {
    if (_wire->available()) buffer[cnt++] = _wire->read();
  }
  return cnt;
}


//  -- END OF FILE --

