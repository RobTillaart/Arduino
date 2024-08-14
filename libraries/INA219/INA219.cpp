//    FILE: INA219.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
//    DATE: 2021-05-18
// PURPOSE: Arduino library for INA219 voltage, current and power sensor
//     URL: https://github.com/RobTillaart/INA219


#include "INA219.h"


//  REGISTER ADDRESSES
#define INA219_CONFIGURATION            0x00
#define INA219_SHUNT_VOLTAGE            0x01
#define INA219_BUS_VOLTAGE              0x02
#define INA219_POWER                    0x03
#define INA219_CURRENT                  0x04
#define INA219_CALIBRATION              0x05
#define INA219_MASK_ENABLE              0x06
#define INA219_ALERT_LIMIT              0x07
#define INA219_MANUFACTURER             0xFE
#define INA219_DIE_ID                   0xFF


//  CONFIGURATION REGISTER MASKS
#define INA219_CONF_RESET               0x8000
#define INA219_CONF_BUS_RANGE_VOLTAGE   0x2000
#define INA219_CONF_PROG_GAIN           0x1800
#define INA219_CONF_BUS_ADC             0x0780
#define INA219_CONF_SHUNT_ADC           0x0078
#define INA219_CONF_MODE                0x0007



////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
INA219::INA219(const uint8_t address, TwoWire *wire)
{
  _address     = address;
  _wire        = wire;
  //  no calibrated values by default.
  _current_LSB = 0;
  _maxCurrent  = 0;
  _shunt       = 0;
}


bool INA219::begin()
{
  if (! isConnected()) return false;
  return true;
}


bool INA219::isConnected()
{
  if ((_address < 0x40) || (_address > 0x4F)) return false;
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t INA219::getAddress()
{
  return _address;
}


////////////////////////////////////////////////////////
//
//  CORE FUNCTIONS
//
float INA219::getShuntVoltage()
{
  int16_t value = _readRegister(INA219_SHUNT_VOLTAGE);
  return value * 1e-5;  //  fixed 10 uV
}


float INA219::getBusVoltage()
{
  uint16_t value = _readRegister(INA219_BUS_VOLTAGE);
  uint8_t flags = value & 0x03;
  //  math overflow handling
  if (flags & 0x01) return -100;
  //  if flags && 0x02 ==> convert flag;  not handled
  float voltage = (value >> 3) * 4e-3;  //  fixed 4 mV
  return voltage;
}


float INA219::getPower()
{
  uint16_t value = _readRegister(INA219_POWER);
  return value * (_current_LSB * 20);  //  fixed 20 Watt
}

//  TODO CHECK
//  needs _current_LSB factor?
float INA219::getCurrent()
{
  int16_t value = _readRegister(INA219_CURRENT);
  return value * _current_LSB;
}


bool INA219::getMathOverflowFlag()
{
  uint16_t value = _readRegister(INA219_BUS_VOLTAGE);
  return ((value & 0x0001) == 0x0001);
}


bool INA219::getConversionFlag()
{
  uint16_t value = _readRegister(INA219_BUS_VOLTAGE);
  return ((value & 0x0002) == 0x0002);
}


////////////////////////////////////////////////////////
//
//  CONFIGURATION
//
bool INA219::reset()
{
  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config |= 0x8000;
  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  //  reset calibration
  _current_LSB = 0;
  _maxCurrent  = 0;
  _shunt       = 0;
  return (wrrv == 0);
}


bool INA219::setBusVoltageRange(uint8_t voltage)
{
  if (voltage > 32) return false;
  if (voltage > 16) voltage = 32;
  else voltage = 16;
  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= ~INA219_CONF_BUS_RANGE_VOLTAGE;
  if (voltage == 32) config |= INA219_CONF_BUS_RANGE_VOLTAGE;

  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  return (wrrv == 0);
}


uint8_t INA219::getBusVoltageRange()
{
  uint16_t config = _readRegister(INA219_CONFIGURATION);
  if (config & INA219_CONF_BUS_RANGE_VOLTAGE) return 32;
  return 16;  //  volts
}


bool INA219::setGain(uint8_t factor)
{
  if (factor != 1 && factor != 2 && factor != 4 && factor != 8)
  {
    return false;
  }
  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= ~INA219_CONF_PROG_GAIN;
  //  factor == 1 ==> mask = 00
  if      (factor == 2) config |= (1 << 11);
  else if (factor == 4) config |= (2 << 11);
  else if (factor == 8) config |= (3 << 11);

  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  return (wrrv == 0);
}


uint8_t INA219::getGain()
{
  uint16_t config = _readRegister(INA219_CONFIGURATION);
  uint16_t mask = (config & INA219_CONF_PROG_GAIN);
  if (mask == 0x0000) return 1;
  else if (mask == 0x0800) return 2;
  else if (mask == 0x1000) return 4;
  return 8;
}


int INA219::getMaxShuntVoltage()
{
  int gain = getGain();  //  1,  2,  4,   8
  return gain * 40;      //  40, 80, 160, 320
}


////////////////////////////////////////////////////////
//
//  BUS
//
bool INA219::setBusResolution(uint8_t bits)
{
  if ((bits < 9) || (bits > 12)) return false;
  bits -= 9;

  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= ~INA219_CONF_BUS_ADC;
  config |= (bits << 7);

  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  return (wrrv == 0);
}


//  value = 0..7, always 12 bit resolution
bool INA219::setBusSamples(uint8_t value)
{
  if (value > 7) return false;
  value |= 8;

  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= ~INA219_CONF_BUS_ADC;
  config |= (value << 7);

  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  return (wrrv == 0);
}


bool INA219::setBusADC(uint8_t mask)
{
  if (mask > 0x0F) return false;

  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= ~INA219_CONF_BUS_ADC;
  config |= (mask << 7);

  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  return (wrrv == 0);
}


uint8_t INA219::getBusADC()
{
  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= INA219_CONF_BUS_ADC;
  return config >> 7;
}


////////////////////////////////////////////////////////
//
//  SHUNT
//
bool INA219::setShuntResolution(uint8_t bits)
{
  if ((bits < 9) || (bits > 12)) return false;
  bits -= 9;

  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= ~INA219_CONF_SHUNT_ADC;
  config |= (bits << 3);

  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  return (wrrv == 0);
}


//  value = 0..7, always 12 bit resolution
bool INA219::setShuntSamples(uint8_t value)
{
  if (value > 7) return false;
  value |= 8;

  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= ~INA219_CONF_SHUNT_ADC;
  config |= (value << 3);

  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  return (wrrv == 0);
}


bool INA219::setShuntADC(uint8_t mask)
{
  if (mask > 0x0F) return false;

  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= ~INA219_CONF_SHUNT_ADC;
  config |= (mask << 3);

  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  return (wrrv == 0);
}


uint8_t INA219::getShuntADC()
{
  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= INA219_CONF_SHUNT_ADC;
  return config >> 3;
}


////////////////////////////////////////////////////////
//
//  MODE
//
bool INA219::setMode(uint8_t mode)
{
  if (mode > 7) return false;
  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= ~INA219_CONF_MODE;
  config |= mode;

  uint16_t wrrv = _writeRegister(INA219_CONFIGURATION, config);
  return (wrrv == 0);
}


uint8_t INA219::getMode()
{
  uint16_t config = _readRegister(INA219_CONFIGURATION);
  config &= INA219_CONF_MODE;
  return config;
}


////////////////////////////////////////////////////////
//
//  CALIBRATION
//
bool INA219::setMaxCurrentShunt(float maxCurrent, float shunt)
{
  // #define PRINTDEBUG
  if (maxCurrent < 0.001) return false;
  if (shunt < 0.001) return false;

  //  _current_LSB = maxCurrent / 32768;
  _current_LSB = maxCurrent * 3.0517578125e-5;
  _maxCurrent = maxCurrent;
  _shunt = shunt;

  uint16_t calib = uint16_t(0.04096 / (_current_LSB * shunt));
  uint16_t wrrv = _writeRegister(INA219_CALIBRATION, calib);

  #ifdef PRINTDEBUG
    Serial.println();
    Serial.print("current_LSB:\t");
    Serial.print(_current_LSB, 8);
    Serial.println(" uA / bit");

    Serial.print("Calibration:\t");
    Serial.println(calib);
    Serial.print("Max current:\t");
    Serial.print(_maxCurrent, 3);
    Serial.println(" A");
    Serial.print("Shunt:\t");
    Serial.print(_shunt, 8);
    Serial.println(" ohm Ω");
  #endif

  return (wrrv == 0);
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//

uint16_t INA219::_readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->endTransmission();

  _wire->requestFrom(_address, (uint8_t)2);
  uint16_t value = _wire->read();
  value <<= 8;
  value |= _wire->read();
  return value;
}


uint16_t INA219::_writeRegister(uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value >> 8);
  _wire->write(value & 0xFF);
  return _wire->endTransmission();
}


//  -- END OF FILE --

