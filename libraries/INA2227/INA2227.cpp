//    FILE: INA2227.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-05-18
// PURPOSE: Arduino library for the INA2227, I2C, 16 bit, dual channel, voltage, current, power and energy sensor.
//     URL: https://github.com/RobTillaart/INA2227
//
//  Read the datasheet for the details


#include "INA2227.h"


//  REGISTERS                              ADDR  (+8 for channel 1)
#define INA2227_SHUNT_VOLTAGE              0x00
#define INA2227_BUS_VOLTAGE                0x01
#define INA2227_POWER                      0x02
#define INA2227_CURRENT                    0x03
#define INA2227_ENERGY                     0x04
#define INA2227_CALIBRATION                0x05
#define INA2227_ALERT_LIMIT                0x06
#define INA2227_ALERT_CONFIG               0x07

#define INA2227_CONFIG1                    0x10
#define INA2227_CONFIG2                    0x11
#define INA2227_FLAGS                      0x12
#define INA2227_MANUFACTURER               0x7E
#define INA2227_DEVICE_ID                  0x7F


//  MASKS INA2227_CONFIG1  (default 0xF127)
#define INA2227_CONF_CHANNEL_ALL_MASK      0x3000
#define INA2227_CONF_CHANNEL1_MASK         0x2000
#define INA2227_CONF_CHANNEL0_MASK         0x1000
#define INA2227_CONF_AVERAGE_MASK          0x0E00
#define INA2227_CONF_VBUSCT_MASK           0x01C0
#define INA2227_CONF_VSHCT_MASK            0x0038
#define INA2227_CONF_MODE_MASK             0x0007

//  MASKS INA2227_CONFIG2  (default 0x0000)
#define INA2227_CONF_RESET_MASK            0x8000
#define INA2227_CONF_ACC_RST_MASK          0x0F00
#define INA2227_CONF_ACC_RST1_MASK         0x0200
#define INA2227_CONF_ACC_RST0_MASK         0x0100
#define INA2227_CONF_CNVR_MASK             0x0080
#define INA2227_CONF_ENOF_MASK             0x0040
#define INA2227_CONF_ALERT_LATCH_MASK      0x0020
#define INA2227_CONF_ALERT_POL_MASK        0x0010
#define INA2227_CONF_ADCRANGE1_MASK        0x0002
#define INA2227_CONF_ADCRANGE0_MASK        0x0001

//  MASKS INA2227_FLAGS  (default 0x0000)
#define INA2227_FLAG_LIMIT1_ALERT          0x2000
#define INA2227_FLAG_LIMIT0_ALERT          0x1000
#define INA2227_FLAG_ENERGYOF_CH1          0x0200
#define INA2227_FLAG_ENERGYOF_CH0          0x0100
#define INA2227_FLAG_CONV_READY            0x0080
#define INA2227_FLAG_OVERFLOW              0x0040


////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
INA2227::INA2227(const uint8_t address, TwoWire *wire)
{
  _address        = address;
  _wire           = wire;
  //  no calibrated values by default.
  _shunt[0]       = 0;
  _shunt[1]       = 0;
  _maxCurrent[0]  = 0;
  _maxCurrent[1]  = 0;
  _current_LSB[0] = 0;
  _current_LSB[1] = 0;
  _error          = 0;
}

bool INA2227::begin()
{
  if (! isConnected()) return false;
  //  default initialization...?
  return true;
}

bool INA2227::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}

uint8_t INA2227::getAddress()
{
  return _address;
}


////////////////////////////////////////////////////////
//
//  ENABLE FUNCTIONS
//
void INA2227::enableChannel(uint8_t ch)
{
  if (ch > 1) return;
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  if (ch == 0) mask |= INA2227_CONF_CHANNEL0_MASK;
  else         mask |= INA2227_CONF_CHANNEL1_MASK;
  _writeRegister(INA2227_CONFIG1, mask);
}

void INA2227::disableChannel(uint8_t ch)
{
  if (ch > 1) return;
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  if (ch == 0) mask &= ~INA2227_CONF_CHANNEL0_MASK;
  else         mask &= ~INA2227_CONF_CHANNEL1_MASK;
  _writeRegister(INA2227_CONFIG1, mask);
}

void INA2227::enableAllChannels()
{
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  mask |= INA2227_CONF_CHANNEL_ALL_MASK;
  _writeRegister(INA2227_CONFIG1, mask);
}

void INA2227::disableAllChannels()
{
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  mask &= ~INA2227_CONF_CHANNEL_ALL_MASK;
  _writeRegister(INA2227_CONFIG1, mask);
}

bool INA2227::isEnabled(uint8_t ch)
{
  if (ch > 1) return false;
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  if (ch == 0) return (mask & INA2227_CONF_CHANNEL0_MASK) > 0;
  return (mask & INA2227_CONF_CHANNEL1_MASK) > 0;
}


////////////////////////////////////////////////////////
//
//  CORE FUNCTIONS
//
//  page 23  7.1.7
float INA2227::getBusVoltage(uint8_t ch)
{
  uint8_t reg = INA2227_BUS_VOLTAGE;
  if (ch == 1) reg += 8;
  uint16_t value = _readRegister(reg);
  //  page 26  8.1.1
  float bus_LSB = 1.6e-3;  //  1.6 mV/LSB fixed
  float voltage = value * bus_LSB;
  return voltage;
}

//  page 23  7.1.6
float INA2227::getShuntVoltage(uint8_t ch)
{
  uint8_t reg = INA2227_SHUNT_VOLTAGE;
  if (ch == 1) reg += 8;
  //  shunt_LSB depends on ADCRANGE in INA2227_CONFIG register.
  //  page 26  8.1.1
  float shunt_LSB = 2.5e-6;            //  2.5 uV/LSB
  if (_ADCRange[ch]) shunt_LSB = 625.0e-9;  //  0.625 uV/LSB  (factor 4)
  int16_t value = _readRegister(reg);
  float voltage = value * shunt_LSB;
  return voltage;
}

//  page 24  7.1.8
float INA2227::getCurrent(uint8_t ch)
{
  uint8_t reg = INA2227_CURRENT;
  if (ch == 1) reg += 8;
  int16_t val = _readRegister(reg);
  //  page 27  equation 3
  return val * _current_LSB[ch];
}

//  page 24  7.1.9
float INA2227::getPower(uint8_t ch)
{
  uint8_t reg = INA2227_POWER;
  if (ch == 1) reg += 8;
  uint16_t val = _readRegister(reg);
  //  page 27  equation 4
  return val * (_current_LSB[ch] * 32);
}

//  page 24  7.1.10
float INA2227::getEnergy(uint8_t ch)
{
  uint8_t reg = INA2227_ENERGY;
  if (ch == 1) reg += 8;
  //  read 32 bit unsigned !
  uint32_t value = _readRegister32(INA2227_ENERGY);
  //  Page28  equation 5
  return value * (_current_LSB[ch] * 32);
}


////////////////////////////////////////////////////////
//
//  FLAGS REGISTER 0x12
//
//  page 25  7.1.11
bool INA2227::isConversionReady()
{
  uint16_t mask = _readRegister(INA2227_FLAGS);
  return (mask & INA2227_FLAG_CONV_READY) > 0;
}

//  page 25  7.1.11
bool INA2227::waitConversionReady(uint32_t timeout)
{
  uint32_t start = millis();
  while ( (millis() - start) < timeout)
  {
    if (isConversionReady()) return true;
    delay(1);  //  implicit yield();
  }
  return false;
}

bool INA2227::hasMathOverflow()
{
  uint16_t mask = _readRegister(INA2227_FLAGS);
  return (mask & INA2227_FLAG_OVERFLOW) > 0;
}

bool INA2227::hasAlertLimit(uint8_t ch)
{
  if (ch > 1) return false;
  uint16_t mask = _readRegister(INA2227_FLAGS);
  if (ch == 0) return (mask & INA2227_FLAG_LIMIT0_ALERT) > 0;
  return (mask & INA2227_FLAG_LIMIT1_ALERT) > 0;
}

bool INA2227::hasEnergyOverflow(uint8_t ch)
{
  if (ch > 1) return false;
  uint16_t mask = _readRegister(INA2227_FLAGS);
  if (ch == 0) return (mask & INA2227_FLAG_ENERGYOF_CH0) > 0;
  return (mask & INA2227_FLAG_ENERGYOF_CH1) > 0;
}

uint16_t INA2227::getFlags()
{
  return _readRegister(INA2227_FLAGS);
}



////////////////////////////////////////////////////////
//
//  CONFIG1 REGISTER 0x10
//
//  page 20  7.1.1
bool INA2227::setAverage(uint8_t avg)
{
  if (avg > 7) return false;
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  mask &= ~INA2227_CONF_AVERAGE_MASK;
  mask |= (avg << 9);
  _writeRegister(INA2227_CONFIG1, mask);
  return true;
}

uint8_t INA2227::getAverage()
{
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  mask &= INA2227_CONF_AVERAGE_MASK;
  mask >>= 9;
  return mask;
}

bool INA2227::setBusVoltageConversionTime(uint8_t bvct)
{
  if (bvct > 7) return false;
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  mask &= ~INA2227_CONF_VBUSCT_MASK;
  mask |= (bvct << 6);
  _writeRegister(INA2227_CONFIG1, mask);
  return true;
}

uint8_t INA2227::getBusVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  mask &= INA2227_CONF_VBUSCT_MASK;
  mask >>= 6;
  return mask;
}

bool INA2227::setShuntVoltageConversionTime(uint8_t svct)
{
  if (svct > 7) return false;
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  mask &= ~INA2227_CONF_VSHCT_MASK;
  mask |= (svct << 3);
  _writeRegister(INA2227_CONFIG1, mask);
  return true;
}

uint8_t INA2227::getShuntVoltageConversionTime()
{
  uint16_t mask = _readRegister(INA2227_CONFIG1);
  mask &= INA2227_CONF_VSHCT_MASK;
  mask >>= 3;
  return mask;
}

bool INA2227::setMode(uint8_t mode)
{
  if (mode > 7) return false;
  uint16_t config = _readRegister(INA2227_CONFIG1);
  config &= ~INA2227_CONF_MODE_MASK;
  config |= mode;
  _writeRegister(INA2227_CONFIG1, config);
  return true;
}

uint8_t INA2227::getMode()
{
  uint16_t mode = _readRegister(INA2227_CONFIG1);
  mode &= INA2227_CONF_MODE_MASK;
  return mode;
}


////////////////////////////////////////////////////////
//
//  CONFIG2 REGISTER 0x11
//
//  page 20  7.1.2
bool INA2227::reset()
{
  uint16_t result = _writeRegister(INA2227_CONFIG2, INA2227_CONF_RESET_MASK);
  //  Serial.println(result);
  if (result != 0) return false;
  //  reset calibration
  _shunt[0]       = 0;
  _shunt[1]       = 0;
  _maxCurrent[0]  = 0;
  _maxCurrent[1]  = 0;
  _current_LSB[0] = 0;
  _current_LSB[1] = 0;
  _error          = 0;
  return true;
}

bool INA2227::resetEnergyAccumulator(uint8_t ch)
{
  if (ch > 1) return false;
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  //  can be optimized with bit magic.
  if (ch == 0)
  {
    mask |= INA2227_CONF_ACC_RST0_MASK;
  }
  else
  {
    mask |= INA2227_CONF_ACC_RST1_MASK;
  }
  _writeRegister(INA2227_CONFIG2, mask);
  return true;
}

bool INA2227::getEnergyAccumulatorChannel(uint8_t ch)
{
  if (ch > 1) return false;
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  //  can be optimized with bit magic.
  if (ch == 0) return ( mask & INA2227_CONF_ACC_RST0_MASK) > 0;
  return ( mask & INA2227_CONF_ACC_RST0_MASK) > 0;
}

bool INA2227::setAlertConvertReady(bool cnvr)
{
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  if (cnvr) mask |= INA2227_CONF_CNVR_MASK;
  else mask &= ~INA2227_CONF_CNVR_MASK;
  _writeRegister(INA2227_CONFIG2, mask);
  return true;
}

bool INA2227::getAlertConvertReady()
{
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  return (mask & INA2227_CONF_CNVR_MASK) > 0;
}

bool INA2227::setAlertEnergyOverflow(bool enof)
{
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  if (enof) mask |= INA2227_CONF_ENOF_MASK;
  else mask &= ~INA2227_CONF_ENOF_MASK;
  _writeRegister(INA2227_CONFIG2, mask);
  return true;
}

bool INA2227::getAlertEnergyOverflow()
{
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  return (mask & INA2227_CONF_ENOF_MASK) > 0;
}

bool INA2227::setAlertLatchEnable(bool latch)
{
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  if (latch) mask |= INA2227_CONF_ALERT_LATCH_MASK;
  else mask &= ~INA2227_CONF_ALERT_LATCH_MASK;
  _writeRegister(INA2227_CONFIG2, mask);
  return true;
}

bool INA2227::getAlertLatchEnable()
{
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  return (mask & INA2227_CONF_ALERT_LATCH_MASK) > 0;
}

bool INA2227::setAlertPolarity(bool inverted)
{
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  if (inverted) mask |= INA2227_CONF_ALERT_POL_MASK;
  else mask &= ~INA2227_CONF_ALERT_POL_MASK;
  _writeRegister(INA2227_CONFIG2, mask);
  return true;
}

bool INA2227::getAlertPolarity()
{
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  return (mask & INA2227_CONF_ALERT_POL_MASK) > 0;
}

bool INA2227::setADCRange(uint8_t ch, bool flag)
{
  if (ch > 1) return false;

  uint16_t value = _readRegister(INA2227_CONFIG2);
  //  can be optimized with bit magic.
  if (ch == 0)
  {
    _ADCRange[0] = (value & INA2227_CONF_ADCRANGE0_MASK) > 0;
    if (_ADCRange[0] == flag) return true;  //  already OK
    //  prep write new value
    if (flag) value |= INA2227_CONF_ADCRANGE0_MASK;
    else      value &= ~INA2227_CONF_ADCRANGE0_MASK;
  }
  else
  {
    _ADCRange[1] = (value & INA2227_CONF_ADCRANGE1_MASK) > 0;
    if (_ADCRange[1] == flag) return true;  //  already OK
    //  prep write new value
    if (flag) value |= INA2227_CONF_ADCRANGE1_MASK;
    else      value &= ~INA2227_CONF_ADCRANGE1_MASK;
  }
  _writeRegister(INA2227_CONFIG2, value);

  //  recalculate
  bool rv = setMaxCurrentShunt(getMaxCurrent(ch), getShunt(ch)) == 0;
  return rv;
}

uint8_t INA2227::getADCRange(uint8_t ch)
{
  if (ch > 1) return 0;  //  error flag
  uint16_t mask = _readRegister(INA2227_CONFIG2);
  //  can be optimized with bit magic.
  if (ch == 0)
  {
    _ADCRange[0] = (mask & INA2227_CONF_ADCRANGE0_MASK) > 0;
  }
  else
  {
    _ADCRange[1] = (mask & INA2227_CONF_ADCRANGE1_MASK) > 0;
  }
  return _ADCRange[ch];
}


////////////////////////////////////////////////////////
//
//  CALIBRATION REGISTER 0x05 / 0x0D
//
//  page 27  8.1.2
int INA2227::setMaxCurrentShunt(uint8_t ch, float maxCurrent, float shunt, bool normalize)
{
  if (ch > 1) return INA2227_ERR_CHANNEL_RANGE;

  //  check parameters
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
    return INA2227_ERR_SHUNTVOLTAGE_HIGH;
  }
  if (maxCurrent < 0.001)
  {
#ifdef printdebug
    Serial.print("[Error] current to low for measurement");
#endif
    return INA2227_ERR_MAXCURRENT_LOW;
  }
  if (shunt < INA2227_MINIMAL_SHUNT)
  {
#ifdef printdebug
    Serial.print("[Error] shunt to low for measurement");
#endif
    return INA2227_ERR_SHUNT_LOW;
  }


  //  here starts calibration (per channel!)
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
  setADCRange(ch, adcRange);

#ifdef printdebug
  Serial.print("channel: \t");
  Serial.println(ch);
  Serial.print("max shunt voltage \t");
  Serial.println(shuntVoltage * 1000);
  Serial.print("max current lsb \t");
  Serial.println(0.8 / (adcRangeFactor * shunt * pow(2, 15)) * 1e6);
#endif

  //  page 27  equation 2
  //  _current_LSB[ch] = maxCurrent / 32768;
  _current_LSB[ch] = maxCurrent * 3.0517578125e-5;

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

  //  normalize the LSB to a round number  (math identical to INA236)
  //  LSB will increase
  if (normalize)
  {
    //  check if maxCurrent (normal) or shunt resistor
    //  (due to unusual low resistor values in relation to maxCurrent) determines currentLSB
    //  we have to take the upper value for currentLSB
    //
    //  calculation of currentLSB based on shunt resistor and calibration register limits (2 bytes)
    //
    //    page 27, equation 1
    //    cal = 0.00512 / ( shunt * currentLSB )
    //
    //    cal(max) = 2^15-1   (32767)
    //    currentLSB(min) = 0.00512     / ( shunt * cal(max) )
    //    currentLSB(min) ~= 0.00512    / ( shunt * 2^15 )
    //    currentLSB(min) ~= 2^9 * 1e-5 / ( shunt * 2^15 )
    //    currentLSB(min) ~= 1e-5 / 2^6 / shunt
    //    currentLSB(min) ~= 1.5625e-7  / shunt
    if ( 1.5625e-7 / (shunt * adcRangeFactor) > _current_LSB[ch] )
    {
      //  shunt resistor determines currentLSB
      //  -> take this as a starting point for currentLSB
      _current_LSB[ch] = 1.5625e-7 / (shunt * adcRangeFactor);
    }

#ifdef printdebug
    Serial.print("Pre-scale current_LSB:\t");
    Serial.print(_current_LSB * 1e+6, 1);
    Serial.println(" uA / bit");
#endif

    //  normalize _current_LSB to a value of 1, 2 ,4, or 5 * 1e-6 to 1e-3
    //  convert float to int
    uint16_t currentLSB_uA = float(_current_LSB[ch] * 1e+6);
    currentLSB_uA++;  //  ceil() would be more precise, but uses 176 bytes of flash.

    uint16_t factor = 1;  //  1uA to 1000uA
    uint8_t i = 0;        //  1 byte loop reduces footprint
    bool result = false;
    do {
      if ( 1 * factor >= currentLSB_uA) {
        _current_LSB[ch] = 1 * factor * 1e-6;
        result = true;
      } else if ( 2 * factor >= currentLSB_uA) {
        _current_LSB[ch] = 2 * factor * 1e-6;
        result = true;
      } else if ( 3 * factor >= currentLSB_uA) {
        _current_LSB[ch] = 3 * factor * 1e-6;
        result = true;
      } else if ( 4 * factor >= currentLSB_uA) {
        _current_LSB[ch] = 4 * factor * 1e-6;
        result = true;
      } else if ( 5 * factor >= currentLSB_uA) {
        _current_LSB[ch] = 5 * factor * 1e-6;
        result = true;
      } else {
        factor *= 10;
        i++;
      }
    } while ( (i < 4) && (!result) );  //  factor < 10000

    if (result == false)  //  not succeeded to normalize.
    {
      _current_LSB[ch] = 0;
      return INA2227_ERR_NORMALIZE_FAILED;
    }

#ifdef printdebug
    Serial.print("After scale current_LSB:\t");
    Serial.print(_current_LSB * 1e+6, 1);
    Serial.println(" uA / bit");
#endif
    // done
  }


  //  auto scale calibration if needed.
  uint32_t calib = round(0.00512 / (_current_LSB[ch] * shunt * adcRangeFactor));
  //  page 21  7.1.3 => must fit in 15 bit (max 0x7FFF)
  while (calib > 32767)
  {
    _current_LSB[ch] *= 2;
    calib >>= 1;
  }
  uint8_t reg = INA2227_CALIBRATION;
  if (ch == 1) reg += 8;
  _writeRegister(reg, calib);

  _maxCurrent[ch] = _current_LSB[ch] * 32768;
  _shunt[ch] = shunt;

#ifdef printdebug
  Serial.print("Final current_LSB:\t");
  Serial.print(_current_LSB[ch] * 1e+6, 1);
  Serial.println(" uA / bit");
  Serial.print("Calibration:\t");
  Serial.println(calib);
  Serial.print("Max current:\t");
  Serial.print(_maxCurrent[ch], 3);
  Serial.println(" A");
  Serial.print("Shunt:\t");
  Serial.print(_shunt[ch], 4);
  Serial.println(" Ohm");
  Serial.print("ShuntV:\t");
  Serial.print(shuntVoltage, 4);
  Serial.println(" Volt");
#endif

  return INA2227_ERR_NONE;
}


////////////////////////////////////////////////////////
//
//  ALERT LIMIT REGISTER 0x06 / 0x0E
//
bool INA2227::setAlertLimit(uint8_t ch, uint16_t limit)
{
  uint8_t reg = INA2227_ALERT_LIMIT;
  if (ch == 1) reg += 8;
  uint16_t result = _writeRegister(reg, limit);
  //  Serial.println(result);
  if (result != 0) return false;
  return true;
}


uint16_t INA2227::getAlertLimit(uint8_t ch)
{
  uint8_t reg = INA2227_ALERT_LIMIT;
  if (ch == 1) reg += 8;
  return _readRegister(reg);
}


////////////////////////////////////////////////////////
//
//  ALERT CONFIG REGISTER 0x07 / 0x0F
//
bool INA2227::setAlertConfig(uint8_t ch, uint16_t mask)
{
  uint8_t reg = INA2227_ALERT_LIMIT;
  if (ch == 1) reg += 8;
  uint16_t result = _writeRegister(reg, mask);
  //  Serial.println(result);
  if (result != 0) return false;
  return true;
}


uint16_t INA2227::getAlertConfig(uint8_t ch)
{
  uint8_t reg = INA2227_ALERT_LIMIT;
  if (ch == 1) reg += 8;
  return _readRegister(reg);
}


////////////////////////////////////////////////////////
//
//  META INFORMATION
//
//  page 25  7.1.12
uint16_t INA2227::getManufacturerID()
{
  return _readRegister(INA2227_MANUFACTURER);
}

//  page 26  7.1.13
uint16_t INA2227::getDeviceID()
{
  return _readRegister(INA2227_DEVICE_ID);
}


////////////////////////////////////////////////////////
//
//  ERROR HANDLING
//
int INA2227::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint16_t INA2227::_readRegister(uint8_t reg)
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


uint32_t INA2227::_readRegister32(uint8_t reg)
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

  uint32_t value = 0;
  if (4 == _wire->requestFrom(_address, (uint8_t)4))
  {
    value = _wire->read();
    value <<= 8;
    value |= _wire->read();
    value <<= 8;
    value |= _wire->read();
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


uint16_t INA2227::_writeRegister(uint8_t reg, uint16_t value)
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

