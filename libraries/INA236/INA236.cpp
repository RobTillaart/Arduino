//    FILE: INA236.cpp
//  AUTHOR: Rob Tillaart
//          ported from INA226 to INA236 by Josef Tremmel
// VERSION: 0.1.5
//    DATE: 2024-05-27
// PURPOSE: Arduino library for the INA236, I2C, 16 bit, voltage, current and power sensor.
//     URL: https://github.com/RobTillaart/INA236
//
//  Read the datasheet for the details


#include "INA236.h"


//  REGISTERS
#define INA236_CONFIGURATION              0x00
#define INA236_SHUNT_VOLTAGE              0x01
#define INA236_BUS_VOLTAGE                0x02
#define INA236_POWER                      0x03
#define INA236_CURRENT                    0x04
#define INA236_CALIBRATION                0x05
#define INA236_MASK_ENABLE                0x06
#define INA236_ALERT_LIMIT                0x07
#define INA236_MANUFACTURER               0x3E
#define INA236_DIE_ID                     0x3F


//  CONFIGURATION MASKS
#define INA236_CONF_RESET_MASK            0x8000
#define INA236_CONF_ADCRANGE_MASK         0x1000
#define INA236_CONF_AVERAGE_MASK          0x0E00
#define INA236_CONF_BUSVC_MASK            0x01C0
#define INA236_CONF_SHUNTVC_MASK          0x0038
#define INA236_CONF_MODE_MASK             0x0007


////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
INA236::INA236(const uint8_t address, TwoWire *wire)
{
  _address     = address;
  _wire        = wire;
  //  no calibrated values by default.
  _current_LSB = 0;
  _maxCurrent  = 0;
  _shunt       = 0;
  _error       = 0;
}


bool INA236::begin()
{
  if (! isConnected()) return false;
  getADCRange();
  return true;
}


bool INA236::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t INA236::getAddress()
{
  return _address;
}


////////////////////////////////////////////////////////
//
//  CORE FUNCTIONS
//
float INA236::getBusVoltage()
{
  uint16_t value = _readRegister(INA236_BUS_VOLTAGE);
  float bus_LSB = 1.6e-3;  //  1.6 mV/LSB fixed
  float voltage = value * bus_LSB;
  return voltage;
}


float INA236::getShuntVoltage()
{
  //  shunt_LSB depends on ADCRANGE in INA236_CONFIG register.
  float shunt_LSB = 2.5e-6;  //  2.5 mV
  if (_ADCRange == true)
  {
    shunt_LSB = 0.625e-6;    //  625 nV
  }
  int16_t value = _readRegister(INA236_SHUNT_VOLTAGE);
  float voltage = value * shunt_LSB;
  return voltage;
}


float INA236::getCurrent()
{
  int16_t val = _readRegister(INA236_CURRENT);
  return val * _current_LSB;
}


float INA236::getPower()
{
  uint16_t val = _readRegister(INA236_POWER);
  return val * (_current_LSB * 32);  //  fixed 32 Watt
}


bool INA236::isConversionReady()
{
  uint16_t mask = _readRegister(INA236_MASK_ENABLE);
  return (mask & INA236_CONVERSION_READY_FLAG) == INA236_CONVERSION_READY_FLAG;
}


bool INA236::waitConversionReady(uint32_t timeout)
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
bool INA236::reset()
{
  uint16_t mask = _readRegister(INA236_CONFIGURATION);
  mask |= INA236_CONF_RESET_MASK;
  uint16_t result = _writeRegister(INA236_CONFIGURATION, mask);
  //  Serial.println(result);
  if (result != 0) return false;
  //  reset calibration
  _current_LSB = 0;
  _maxCurrent  = 0;
  _shunt       = 0;
  return true;
}


bool INA236::setADCRange(bool flag)
{
  uint16_t value = _readRegister(INA236_CONFIGURATION);
  _ADCRange = (value & INA236_CONF_ADCRANGE_MASK) > 0;
  //  nothing changed ==> we're done.
  if (flag == _ADCRange) return true;
  _ADCRange = flag;
  if (flag) value |= INA236_CONF_ADCRANGE_MASK;
  else      value &= ~INA236_CONF_ADCRANGE_MASK;
  _writeRegister(INA236_CONFIGURATION, value);
  //  INA228, #26
  bool rv = setMaxCurrentShunt(getMaxCurrent(), getShunt()) == 0;
  return rv;
}


uint8_t INA236::getADCRange()
{
  uint16_t mask = _readRegister(INA236_CONFIGURATION);
  _ADCRange = (mask & INA236_CONF_ADCRANGE_MASK) > 0;
  return _ADCRange;
}


bool INA236::setAverage(uint8_t avg)
{
  if (avg > 7) return false;
  uint16_t mask = _readRegister(INA236_CONFIGURATION);
  mask &= ~INA236_CONF_AVERAGE_MASK;
  mask |= (avg << 9);
  _writeRegister(INA236_CONFIGURATION, mask);
  return true;
}


uint8_t INA236::getAverage()
{
  uint16_t mask = _readRegister(INA236_CONFIGURATION);
  mask &= INA236_CONF_AVERAGE_MASK;
  mask >>= 9;
  return mask;
}


bool INA236::setBusVoltageConversionTime(uint8_t bvct)
{
  if (bvct > 7) return false;
  uint16_t mask = _readRegister(INA236_CONFIGURATION);
  mask &= ~INA236_CONF_BUSVC_MASK;
  mask |= (bvct << 6);
  _writeRegister(INA236_CONFIGURATION, mask);
  return true;
}


uint8_t INA236::getBusVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA236_CONFIGURATION);
  mask &= INA236_CONF_BUSVC_MASK;
  mask >>= 6;
  return mask;
}


bool INA236::setShuntVoltageConversionTime(uint8_t svct)
{
  if (svct > 7) return false;
  uint16_t mask = _readRegister(INA236_CONFIGURATION);
  mask &= ~INA236_CONF_SHUNTVC_MASK;
  mask |= (svct << 3);
  _writeRegister(INA236_CONFIGURATION, mask);
  return true;
}


uint8_t INA236::getShuntVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA236_CONFIGURATION);
  mask &= INA236_CONF_SHUNTVC_MASK;
  mask >>= 3;
  return mask;
}


////////////////////////////////////////////////////////
//
//  CALIBRATION
//
int INA236::setMaxCurrentShunt(float maxCurrent, float shunt, bool normalize)
{
  //  https://github.com/RobTillaart/INA226/pull/29

  //  #define printdebug true

#ifdef printdebug
  Serial.println("start calibration");
#endif
  //  Handle error in parameters first
  //
  //  fix #16 - datasheet 6.5 Electrical Characteristics
  //            rounded value to 80 mV

  float shuntVoltage = maxCurrent * shunt;
  if (shuntVoltage > 0.080)
  {
#ifdef printdebug
    Serial.print("[Error] max current too large for measurement range");
#endif
    return INA236_ERR_SHUNTVOLTAGE_HIGH;
  }
  if (maxCurrent < 0.001)
  {
#ifdef printdebug
    Serial.print("[Error] current to low for measurement");
#endif
    return INA236_ERR_MAXCURRENT_LOW;
  }
  if (shunt < INA236_MINIMAL_SHUNT)
  {
#ifdef printdebug
    Serial.print("[Error] shunt to low for measurement");
#endif
    return INA236_ERR_SHUNT_LOW;
  }

  bool adcRange = false;
  int adcRangeFactor = 1;
  if (shuntVoltage <= 0.020)  //  20 mV
  {
    adcRange = true;
    adcRangeFactor = 4;
  }
  else if (shuntVoltage <= 0.080)  //  80 mV
  {
    adcRange = false;
    adcRangeFactor = 1;
  }
  setADCRange(adcRange);

#ifdef printdebug
  Serial.print("max shunt voltage \t");
  Serial.println(shuntVoltage * 1000);
  Serial.print("max current lsb \t");
  Serial.println(0.8 / (adcRangeFactor * shunt * pow(2, 15)) * 1e6);
#endif


  setADCRange(adcRange);


  _current_LSB = maxCurrent * 3.0517578125e-5;      //  maxCurrent / 32768;

#ifdef printdebug
  Serial.println();
  Serial.print("normalize:\t");
  Serial.println(normalize ? " true" : " false");
  Serial.print("initial current_LSB:\t");
  Serial.print(_current_LSB * 1e+6, 1);
  Serial.println(" uA / bit");
  Serial.print("adcRange:\t");
  Serial.println(adcRange);
#endif

  //  normalize the LSB to a round number
  //  LSB will increase
  if (normalize)
  {
    /*
       check if maxCurrent (normal) or shunt resistor
       (due to unusual low resistor values in relation to maxCurrent) determines currentLSB
       we have to take the upper value for currentLSB

       calculation of currentLSB based on shunt resistor and calibration register limits (2 bytes)
       cal = 0.00512 / ( shunt * currentLSB )
       cal(max) = 2^15-1
       currentLSB(min) = 0.00512 / ( shunt * cal(max) )
       currentLSB(min) ~= 0.00512 / ( shunt * 2^15 )
       currentLSB(min) ~= 2^9 * 1e-5 / ( shunt * 2^15 )
       currentLSB(min) ~= 1e-5 / 2^6 / shunt
       currentLSB(min) ~= 1.5625e-7 / shunt
    */
    if ( 1.5625e-7 / (shunt * adcRangeFactor) > _current_LSB ) {
      //  shunt resistor determines currentLSB -> take this a starting point for currentLSB
      _current_LSB = 1.5625e-7 / (shunt * adcRangeFactor);
    }

#ifdef printdebug
    Serial.print("Pre-scale current_LSB:\t");
    Serial.print(_current_LSB * 1e+6, 1);
    Serial.println(" uA / bit");
#endif

    //  normalize _current_LSB to a value of 1, 2 ,4,or 5 * 1e-6 to 1e-3
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
      } else if ( 3 * factor >= currentLSB_uA) {
        _current_LSB = 3 * factor * 1e-6;
        result = true;
      } else if ( 4 * factor >= currentLSB_uA) {
        _current_LSB = 4 * factor * 1e-6;
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
      return INA236_ERR_NORMALIZE_FAILED;
    }

#ifdef printdebug
    Serial.print("After scale current_LSB:\t");
    Serial.print(_current_LSB * 1e+6, 1);
    Serial.println(" uA / bit");
#endif
    // done
  }

  //  auto scale calibration if needed.
  uint32_t calib = round(0.00512 / (_current_LSB * shunt * adcRangeFactor));
  while (calib > 32767)  // was 32768 (?)
  {
    _current_LSB *= 2;
    calib >>= 1;
  }
  _writeRegister(INA236_CALIBRATION, calib);

  _maxCurrent = _current_LSB * 32768;
  _shunt = shunt;

#ifdef printdebug
  Serial.print("Final current_LSB:\t");
  Serial.print(_current_LSB * 1e+6, 1);
  Serial.println(" uA / bit");
  Serial.print("Calibration:\t");
  Serial.println(calib);
  Serial.print("Max current:\t");
  Serial.print(_maxCurrent, 3);
  Serial.println(" A");
  Serial.print("Shunt:\t");
  Serial.print(_shunt, 4);
  Serial.println(" Ohm");
  Serial.print("ShuntV:\t");
  Serial.print(shuntVoltage, 4);
  Serial.println(" Volt");
#endif

  return INA236_ERR_NONE;
}


////////////////////////////////////////////////////////
//
//  OPERATING MODE
//
bool INA236::setMode(uint8_t mode)
{
  if (mode > 7) return false;
  uint16_t config = _readRegister(INA236_CONFIGURATION);
  config &= ~INA236_CONF_MODE_MASK;
  config |= mode;
  _writeRegister(INA236_CONFIGURATION, config);
  return true;
}


uint8_t INA236::getMode()
{
  uint16_t mode = _readRegister(INA236_CONFIGURATION);
  mode &= INA236_CONF_MODE_MASK;
  return mode;
}


////////////////////////////////////////////////////////
//
//  ALERT
//
bool INA236::setAlertRegister(uint16_t mask)
{
  uint16_t result = _writeRegister(INA236_MASK_ENABLE, mask);
  //  Serial.println(result);
  if (result != 0) return false;
  return true;
}


uint16_t INA236::getAlertRegister()
{
  return _readRegister(INA236_MASK_ENABLE);
}


//  OBSOLETE
uint16_t INA236::getAlertFlag()
{
  return _readRegister(INA236_MASK_ENABLE) & 0x001F;
}


bool INA236::setAlertLatchEnable(bool latch)
{
  uint16_t mask = _readRegister(INA236_MASK_ENABLE);
  if (latch) mask |= INA236_ALERT_LATCH_ENABLE_FLAG;
  else       mask &= ~INA236_ALERT_LATCH_ENABLE_FLAG;
  uint16_t result = _writeRegister(INA236_MASK_ENABLE, mask);
  if (result != 0) return false;
  return true;
}


bool INA236::getAlertLatchEnable()
{
  uint16_t mask = _readRegister(INA236_MASK_ENABLE);
  return mask & INA236_ALERT_LATCH_ENABLE_FLAG;
}


bool INA236::setAlertPolarity(bool inverted)
{
  uint16_t mask = _readRegister(INA236_MASK_ENABLE);
  if (inverted) mask |= INA236_ALERT_POLARITY_FLAG;
  else          mask &= ~INA236_ALERT_POLARITY_FLAG;
  uint16_t result = _writeRegister(INA236_MASK_ENABLE, mask);
  if (result != 0) return false;
  return true;
}


bool INA236::getAlertPolarity()
{
  uint16_t mask = _readRegister(INA236_MASK_ENABLE);
  return mask & INA236_ALERT_POLARITY_FLAG;
}


bool INA236::setAlertLimit(uint16_t limit)
{
  uint16_t result = _writeRegister(INA236_ALERT_LIMIT, limit);
  //  Serial.println(result);
  if (result != 0) return false;
  return true;
}


uint16_t INA236::getAlertLimit()
{
  return _readRegister(INA236_ALERT_LIMIT);
}


////////////////////////////////////////////////////////
//
//  META INFORMATION
//
uint16_t INA236::getManufacturerID()
{
  return _readRegister(INA236_MANUFACTURER);
}


uint16_t INA236::getDieID()
{
  return _readRegister(INA236_DIE_ID);
}


////////////////////////////////////////////////////////
//
//  ERROR HANDLING
//
int INA236::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint16_t INA236::_readRegister(uint8_t reg)
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


uint16_t INA236::_writeRegister(uint8_t reg, uint16_t value)
{
  _error = 0;
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

