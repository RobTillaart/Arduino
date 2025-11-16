//    FILE: INA226.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.6.5
//    DATE: 2021-05-18
// PURPOSE: Arduino library for INA226 power sensor
//     URL: https://github.com/RobTillaart/INA226
//
//  Read the datasheet for the details


#include "INA226.h"

//  REGISTERS
#define INA226_CONFIGURATION              0x00
#define INA226_SHUNT_VOLTAGE              0x01
#define INA226_BUS_VOLTAGE                0x02
#define INA226_POWER                      0x03
#define INA226_CURRENT                    0x04
#define INA226_CALIBRATION                0x05
#define INA226_MASK_ENABLE                0x06
#define INA226_ALERT_LIMIT                0x07
#define INA226_MANUFACTURER               0xFE
#define INA226_DIE_ID                     0xFF


//  CONFIGURATION MASKS
#define INA226_CONF_RESET_MASK            0x8000
#define INA226_CONF_AVERAGE_MASK          0x0E00
#define INA226_CONF_BUSVC_MASK            0x01C0
#define INA226_CONF_SHUNTVC_MASK          0x0038
#define INA226_CONF_MODE_MASK             0x0007


////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
INA226::INA226(const uint8_t address, TwoWire *wire)
{
  _address     = address;
  _wire        = wire;
  //  no calibrated values by default.
  _current_LSB = 0;
  _maxCurrent  = 0;
  _shunt       = 0;
  _error       = 0;
}


bool INA226::begin()
{
  if (! isConnected()) return false;
  return true;
}


bool INA226::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t INA226::getAddress()
{
  return _address;
};


////////////////////////////////////////////////////////
//
//  CORE FUNCTIONS
//
float INA226::getBusVoltage()
{
  uint16_t val = _readRegister(INA226_BUS_VOLTAGE);
  //    return val * 1.25e-3 * _bus_V_scaling_e4 / 10000;  //  fixed 1.25 mV
  float voltage = val * 1.25e-3;
  if (_bus_V_scaling_e4 != 10000)
  {
    voltage *= _bus_V_scaling_e4 * 1.0e-4;
  }
  return voltage;
}


float INA226::getShuntVoltage()
{
  int16_t val = _readRegister(INA226_SHUNT_VOLTAGE);
  return val * 2.5e-6;   //  fixed 2.50 uV
}


float INA226::getCurrent()
{
  int16_t val = _readRegister(INA226_CURRENT);
  return val * _current_LSB - _current_zero_offset;
}


float INA226::getPower()
{
  uint16_t val = _readRegister(INA226_POWER);
  return val * (_current_LSB * 25);  //  fixed 25 Watt
}


bool INA226::isConversionReady()
{
  uint16_t mask = _readRegister(INA226_MASK_ENABLE);
  return (mask & INA226_CONVERSION_READY_FLAG) == INA226_CONVERSION_READY_FLAG;
}


bool INA226::waitConversionReady(uint32_t timeout)
{
  uint32_t start = millis();
  while ( (millis() - start) <= timeout)
  {
    if (isConversionReady()) return true;
    delay(1);  //  implicit yield();
  }
  return false;
}


////////////////////////////////////////////////////////
//
//  CONFIGURATION
//
bool INA226::reset()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask |= INA226_CONF_RESET_MASK;
  uint16_t result = _writeRegister(INA226_CONFIGURATION, mask);
  //  Serial.println(result);
  if (result != 0) return false;
  //  reset calibration
  _current_LSB = 0;
  _maxCurrent  = 0;
  _shunt       = 0;
  return true;
}


bool INA226::setAverage(uint8_t avg)
{
  if (avg > 7) return false;
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= ~INA226_CONF_AVERAGE_MASK;
  mask |= (avg << 9);
  _writeRegister(INA226_CONFIGURATION, mask);
  return true;
}


uint8_t INA226::getAverage()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= INA226_CONF_AVERAGE_MASK;
  mask >>= 9;
  return mask;
}


bool INA226::setBusVoltageConversionTime(uint8_t bvct)
{
  if (bvct > 7) return false;
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= ~INA226_CONF_BUSVC_MASK;
  mask |= (bvct << 6);
  _writeRegister(INA226_CONFIGURATION, mask);
  return true;
}


uint8_t INA226::getBusVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= INA226_CONF_BUSVC_MASK;
  mask >>= 6;
  return mask;
}


bool INA226::setShuntVoltageConversionTime(uint8_t svct)
{
  if (svct > 7) return false;
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= ~INA226_CONF_SHUNTVC_MASK;
  mask |= (svct << 3);
  _writeRegister(INA226_CONFIGURATION, mask);
  return true;
}


uint8_t INA226::getShuntVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA226_CONFIGURATION);
  mask &= INA226_CONF_SHUNTVC_MASK;
  mask >>= 3;
  return mask;
}


////////////////////////////////////////////////////////
//
//  CALIBRATION
//
int INA226::setMaxCurrentShunt(float maxCurrent, float shunt, bool normalize)
{
  //  https://github.com/RobTillaart/INA226/pull/29

  //  #define printdebug true

  //  fix #16 - datasheet 6.5 Electrical Characteristics: 81.92 mV
  //            rounded value to 80 mV
  //  fix #49 - changed to 81.90 mV to have parameters (0.8, 0.1) working
  //            81.90 == datasheet limit - 0.02 mV to catch math overflow
  float shuntVoltage = maxCurrent * shunt;
  if (shuntVoltage > 0.08190)           return INA226_ERR_SHUNTVOLTAGE_HIGH;
  if (maxCurrent < 0.001)               return INA226_ERR_MAXCURRENT_LOW;
  if (shunt < INA226_MINIMAL_SHUNT_OHM) return INA226_ERR_SHUNT_LOW;

  _current_LSB = maxCurrent * 3.0517578125e-5;      //  maxCurrent / 32768;

#ifdef printdebug
  Serial.println();
  Serial.print("normalize:\t");
  Serial.println(normalize ? " true" : " false");
  Serial.print("initial current_LSB:\t");
  Serial.print(_current_LSB * 1e+6, 1);
  Serial.println(" uA / bit");
#endif

  //  normalize the LSB to a round number
  //  LSB will increase
  if (normalize)
  {
    /*
       check if maxCurrent (normal) or shunt resistor
       (due to unusual low resistor values in relation to maxCurrent) determines currentLSB
       we have to take the upper value for currentLSB

       (adjusted in 0.6.0)
       calculation of currentLSB based on shunt resistor and calibration register limits (2 bytes)
       cal = 0.00512 / ( shunt * currentLSB )
       cal(max) = 2^15-1
       currentLSB(min) = 0.00512 / ( shunt * cal(max) )
       currentLSB(min) ~= 0.00512 / ( shunt * 2^15 )
       currentLSB(min) ~= 2^9 * 1e-5 / ( shunt * 2^15 )
       currentLSB(min) ~= 1e-5 / 2^6 / shunt
       currentLSB(min) ~= 1.5625e-7 / shunt
    */
    if ( 1.5625e-7 / shunt > _current_LSB ) {
      //  shunt resistor determines current_LSB
      //  => take this a starting point for current_LSB
      _current_LSB = 1.5625e-7 / shunt;
    }

#ifdef printdebug
    Serial.print("Pre-scale current_LSB:\t");
    Serial.print(_current_LSB * 1e+6, 1);
    Serial.println(" uA / bit");
#endif

    //  normalize _current_LSB to a value of 1, 2 or 5 * 1e-6 to 1e-3
    //  convert float to int
    uint16_t currentLSB_uA = float(_current_LSB * 1e+6);
    currentLSB_uA++;  //  ceil() would be more precise, but uses 176 bytes of flash.

    uint16_t factor = 1;  //  1uA to 1000uA
    uint8_t i = 0;        //  1 byte loop reduces footprint
    bool result = false;
    do {
      if ( 1 * factor >= currentLSB_uA) {
        _current_LSB = 1 * factor * 1e-6;
        result = true;
      } else if ( 2 * factor >= currentLSB_uA) {
        _current_LSB = 2 * factor * 1e-6;
        result = true;
      } else if ( 5 * factor >= currentLSB_uA) {
        _current_LSB = 5 * factor * 1e-6;
        result = true;
      } else {
        factor *= 10;
        i++;
      }
    } while ( (i < 4) && (!result) );  //  factor < 10000

    if (result == false)  //  not succeeded to normalize.
    {
      _current_LSB = 0;
      return INA226_ERR_NORMALIZE_FAILED;
    }

#ifdef printdebug
    Serial.print("After scale current_LSB:\t");
    Serial.print(_current_LSB * 1e+6, 1);
    Serial.println(" uA / bit");
#endif
    // done
  }

  //  auto scale calibration if needed.
  uint32_t calib = round(0.00512 / (_current_LSB * shunt));
  while (calib > 32767)
  {
    _current_LSB *= 2;
    calib >>= 1;
  }
  _writeRegister(INA226_CALIBRATION, calib);

  _maxCurrent = _current_LSB * 32768;
  _shunt = shunt;

#ifdef printdebug
  Serial.println("\n***** INA 226 SET VALUES *****");
  Serial.print("Shunt:\t");
  Serial.print(_shunt, 4);
  Serial.println(" Ohm");
  Serial.print("Current_LSB:\t");
  Serial.print(_current_LSB * 1e+6, 1);
  Serial.println(" uA / bit");
  Serial.print("Calibration:\t");
  Serial.println(calib);
  Serial.print("Max Measurable Current:\t");
  Serial.print(_maxCurrent, 3);
  Serial.println(" A");
  Serial.print("maxShuntVoltage:\t");
  Serial.print(shuntVoltage, 4);
  Serial.println(" Volt");
#endif

  return INA226_ERR_NONE;
}


int INA226::configure(float shunt, float current_LSB_mA, float current_zero_offset_mA, uint16_t bus_V_scaling_e4)
{
  if (shunt < INA226_MINIMAL_SHUNT_OHM) return INA226_ERR_SHUNT_LOW;
  float maxCurrent = min((INA226_MAX_SHUNT_VOLTAGE / shunt), 32768 * current_LSB_mA * 1e-3);
  if (maxCurrent < 0.001)               return INA226_ERR_MAXCURRENT_LOW;

  _shunt               = shunt;
  _current_LSB         = current_LSB_mA * 1e-3;
  _current_zero_offset = current_zero_offset_mA * 1e-3;
  _bus_V_scaling_e4    = bus_V_scaling_e4;
  _maxCurrent          = maxCurrent;

  uint32_t calib = round(0.00512 / (_current_LSB * _shunt));
  _writeRegister(INA226_CALIBRATION, calib);

// #define printdebug

#ifdef printdebug
  Serial.println("\n***** INA 226 USER SET VALUES *****");
  Serial.print("Shunt:\t");
  Serial.print(_shunt, 4);
  Serial.println(" Ohm");
  Serial.print("current_LSB:\t");
  Serial.print(_current_LSB * 1e+6, 1);
  Serial.println(" uA / bit");
  Serial.print("Calibration:\t");
  Serial.println(calib);
  Serial.print("Max Measurable Current:\t");
  Serial.print(_maxCurrent, 3);
  Serial.println(" A");
  Serial.print("maxShuntVoltage:\t");
  Serial.print(_maxCurrent * _shunt, 4);
  Serial.println(" Volt");
#endif

  return INA226_ERR_NONE;
}


////////////////////////////////////////////////////////
//
//  OPERATING MODE
//
bool INA226::setMode(uint8_t mode)
{
  if (mode > 7) return false;
  uint16_t config = _readRegister(INA226_CONFIGURATION);
  config &= ~INA226_CONF_MODE_MASK;
  config |= mode;
  _writeRegister(INA226_CONFIGURATION, config);
  return true;
}


uint8_t INA226::getMode()
{
  uint16_t mode = _readRegister(INA226_CONFIGURATION);
  mode &= INA226_CONF_MODE_MASK;
  return mode;
}


////////////////////////////////////////////////////////
//
//  ALERT
//
bool INA226::setAlertRegister(uint16_t mask)
{
  uint16_t result = _writeRegister(INA226_MASK_ENABLE, mask);
  if (result != 0) return false;
  return true;
}


uint16_t INA226::getAlertRegister()
{
  return _readRegister(INA226_MASK_ENABLE);
}


//  OBSOLETE
uint16_t INA226::getAlertFlag()
{
  return _readRegister(INA226_MASK_ENABLE) & 0x001F;
}


bool INA226::setAlertLatchEnable(bool latch)
{
  uint16_t mask = _readRegister(INA226_MASK_ENABLE);
  if (latch) mask |= INA226_ALERT_LATCH_ENABLE_FLAG;
  else       mask &= ~INA226_ALERT_LATCH_ENABLE_FLAG;
  uint16_t result = _writeRegister(INA226_MASK_ENABLE, mask);
  if (result != 0) return false;
  return true;
}


bool INA226::getAlertLatchEnable()
{
  uint16_t mask = _readRegister(INA226_MASK_ENABLE);
  return mask & INA226_ALERT_LATCH_ENABLE_FLAG;
}


bool INA226::setAlertPolarity(bool inverted)
{
  uint16_t mask = _readRegister(INA226_MASK_ENABLE);
  if (inverted) mask |= INA226_ALERT_POLARITY_FLAG;
  else          mask &= ~INA226_ALERT_POLARITY_FLAG;
  uint16_t result = _writeRegister(INA226_MASK_ENABLE, mask);
  if (result != 0) return false;
  return true;
}


bool INA226::getAlertPolarity()
{
  uint16_t mask = _readRegister(INA226_MASK_ENABLE);
  return mask & INA226_ALERT_POLARITY_FLAG;
}


bool INA226::setAlertLimit(uint16_t limit)
{
  uint16_t result = _writeRegister(INA226_ALERT_LIMIT, limit);
  //  Serial.println(result);
  if (result != 0) return false;
  return true;
}


uint16_t INA226::getAlertLimit()
{
  return _readRegister(INA226_ALERT_LIMIT);
}


////////////////////////////////////////////////////////
//
//  META INFORMATION
//
uint16_t INA226::getManufacturerID()
{
  return _readRegister(INA226_MANUFACTURER);
}


uint16_t INA226::getDieID()
{
  return _readRegister(INA226_DIE_ID);
}


////////////////////////////////////////////////////////
//
//  ERROR HANDLING
//
int INA226::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint16_t INA226::_readRegister(uint8_t reg)
{
  _error = 0;
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    _error = -1;
    return 0;
  }

  uint16_t value = 0;
  if (2 == _wire->requestFrom(_address, (uint8_t)2))
  {
    value = _wire->read();
    value <<= 8;
    value |= _wire->read();
  }
  else
  {
    _error = -2;
    return 0;
  }
  return value;
}


uint16_t INA226::_writeRegister(uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value >> 8);
  _wire->write(value & 0xFF);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    _error = -1;
  }
  return n;
}


//  -- END OF FILE --

