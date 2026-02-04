//
//    FILE: BL0940_SPI.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-02-03
// VERSION: 0.1.0
// PURPOSE: Arduino library for BL0940 energy monitor, SPI interface.
//     URL: https://github.com/RobTillaart/BL0940_SPI


#include "BL0940_SPI.h"

//  REGISTERS
//  datasheet page 8. checked.
//
//      NAME                                NUMBER       BITS    RW   checked
//-------------------------------------------------------------------
#define BL0940_REG_I_FAST_RMS               0x00      //  24     RO
#define BL0940_REG_I_WAVE                   0x01      //  20s    RO     v
#define BL0940_REG_V_WAVE                   0x03      //  20s    RO     v
#define BL0940_REG_I_RMS                    0x04      //  24     RO
#define BL0940_REG_V_RMS                    0x06      //  24     RO
#define BL0940_REG_WATT                     0x08      //  24s    RO     v
#define BL0940_REG_CF_CNT                   0x0A      //  24     RO
#define BL0940_REG_ANGLE                    0x0C      //  16     RO
#define BL0940_REG_INT_TEMP                 0x0E      //  10     RO
#define BL0940_REG_EXT_TEMP                 0x0F      //  10     RO

//  RW REG
#define BL0940_REG_I_FAST_RMS_CTL           0x10      //  16     RW
#define BL0940_REG_I_RMSOS                  0x12      //   8     RW
#define BL0940_REG_WATT_OS                  0x15      //   8     RW
#define BL0940_REG_WA_CREEP                 0x17      //   8     RW
#define BL0940_REG_MODE                     0x18      //  16     RW
#define BL0940_REG_SOFT_RESET               0x19      //  24     RW
#define BL0940_REG_USR_WRPROT               0x1A      //   8     RW
#define BL0940_REG_TEMP_CTRL                0x1B      //  16     RW
#define BL0940_REG_TPS2_GAIN                0x1C      //   8     RW
#define BL0940_REG_TPS2_OS                  0x1D      //   8     RW

//
//  SPI MAX SPEED
//  datasheet states 900 kHz
//
#define BL0940_SPI_MAX_SPEED        (900000)


//
//  CALIBRATION MAGIC NUMBERS
//  extracted from app note (Chinese)
//  + page 17 datasheet
//  these constants have the factor 1000 for mV and mA in it.
//        for power the factor = 1000 x 1000.
const float BL0940_VREF          = 1.218f;      //  APP NOTE p.4
const float BL0940_MAGIC_CURRENT = 324004000;   //  APP NOTE p.4
const float BL0940_MAGIC_VOLT    = 79931000;    //  APP NOTE p.4
const float BL0940_MAGIC_POWER   = 4046000000;  //  APP NOTE p.4


//
//  HARDWARE SPI
//
BL0940_SPI::BL0940_SPI(__SPI_CLASS__ * mySPI)  //v
{
  //  255 is not used on any known board.
  BL0940_SPI(255, mySPI);
}

BL0940_SPI::BL0940_SPI(uint8_t select, __SPI_CLASS__ * mySPI)  //v
{
  _select   = select;
  //  255 is not used on any known board.
  _dataIn   = 255;
  _dataOut  = 255;
  _clock    = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
}

//
//  SOFTWARE SPI
//
BL0940_SPI::BL0940_SPI(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _select   = select;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}


bool BL0940_SPI::begin()  //v
{
  pinMode(_select, OUTPUT);
  select(false);

  setSPIspeed(BL0940_SPI_MAX_SPEED);

  if(_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else
  {
    pinMode(_dataIn, INPUT);
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);  //  datasheet TODO
  }

  //  reset variables
  _error = BL0940_OK;
  return true;
}


//////////////////////////////////////////////////////
//
//  CALIBRATION 1
//
void BL0940_SPI::calibrate(float shunt, float reductionFactor)  //v app note
{
  //  based upon APPNOTE (Chinese) page 4
  _voltageLSB = BL0940_VREF * reductionFactor / BL0940_MAGIC_VOLT;
  //  _voltageLSB = reductionFactor * (BL0940_VREF / BL0940_MAGIC_VOLT);

  _currentLSB = BL0940_VREF / (BL0940_MAGIC_CURRENT * shunt);

  //  optimized formula
  //  _powerLSB   = _voltageLSB * _currentLSB * x.xxxxE+06;

  //  reference APP NOTE formula
  _powerLSB   = (BL0940_VREF * BL0940_VREF) * reductionFactor;
  _powerLSB  /= (BL0940_MAGIC_POWER * shunt);

  //  optimized formula
  _energyLSB  = ((1638.4f * 256) / 3600000) * _powerLSB;
}

//  datasheet page TODO
float BL0940_SPI::getMaxCurrent()  //v app note
{
  return _currentLSB * ((0.050f * BL0940_MAGIC_CURRENT) / BL0940_VREF);
}

float BL0940_SPI::getMaxVoltage()  //v app note
{
  return _voltageLSB * ((0.100f * BL0940_MAGIC_VOLT) / BL0940_VREF);
}

float BL0940_SPI::getMaxCurrentRMS()  //v app note
{
  return _currentLSB * ((0.035f * BL0940_MAGIC_CURRENT) / BL0940_VREF);
}

float BL0940_SPI::getMaxVoltageRMS()  //v app note
{
  return _voltageLSB * ((0.070f * BL0940_MAGIC_VOLT) / BL0940_VREF);
}


//////////////////////////////////////////////////////
//
//  CALIBRATION 2
//
float BL0940_SPI::getVoltageLSB()  //v
{
  return _voltageLSB;
}

void BL0940_SPI::setVoltageLSB(float voltageLSB)  //v
{
  _voltageLSB = voltageLSB;
  // _powerLSB   = _voltageLSB * _currentLSB * 6.3995208E+06;
  // _energyLSB  = 1638.4 * 256 * _powerLSB / 3600000;
}

float BL0940_SPI::getCurrentLSB()  //v
{
  return _currentLSB;
}

void BL0940_SPI::setCurrentLSB(float currentLSB)  //v
{
  _currentLSB = currentLSB;
  // _powerLSB   = _voltageLSB * _currentLSB * 6.3995208E+06;
  // _energyLSB  = 1638.4 * 256 * _powerLSB / 3600000;
}

float BL0940_SPI::getPowerLSB()  //v
{
  return _powerLSB;
}

void BL0940_SPI::setPowerLSB(float powerLSB)  //v
{
  _powerLSB = powerLSB;
}

float BL0940_SPI::getEnergyLSB()  //v
{
  return _energyLSB;
}

void BL0940_SPI::setEnergyLSB(float energyLSB)  //v
{
  _energyLSB = energyLSB;
}


//////////////////////////////////////////////////////
//
//  READ ONLY REGISTERS
//
float BL0940_SPI::getIRMSFast()  //v
{
  //  datasheet p.19
  //  unsigned 24 bit
  uint32_t raw = readRegister(BL0940_REG_I_FAST_RMS);
  raw &= 0x00FFFFFF;
  return raw * _currentLSB;
}

float BL0940_SPI::getIWave()  //v
{
  //  datasheet p.13
  //  signed 20 bit
  int32_t raw = readRegister(BL0940_REG_I_WAVE);
  raw &= 0x000FFFFF;
  //  extend sign bit
  if (raw & 0x00800000) raw |= 0xFFF00000;
  return raw * _currentLSB;
}

float BL0940_SPI::getVWave() //v
{
  //  datasheet p.13
  //  signed 20 bit
  int32_t raw = readRegister(BL0940_REG_V_WAVE);
  raw &= 0x000FFFFF;
  //  extend sign bit
  if (raw & 0x00080000) raw |= 0xFFF00000;
  return raw * _voltageLSB;
}

float BL0940_SPI::getIRMS()  //v
{
  //  unsigned 24 bit
  uint32_t raw = readRegister(BL0940_REG_I_RMS);
  raw &= 0xFFFFFF;
  return raw * _currentLSB;
}

float BL0940_SPI::getVRMS()  //v
{
  //  unsigned 24 bit
  uint32_t raw = readRegister(BL0940_REG_V_RMS);
  raw &= 0xFFFFFF;
  return raw * _voltageLSB;
}

float BL0940_SPI::getWatt()  //v
{
  //  signed 24 bit
  int32_t raw = readRegister(BL0940_REG_WATT);
  raw &= 0x00FFFFFF;
  //  extend sign bit
  if (raw & 0x00800000) raw |= 0xFF000000;
  return raw * _powerLSB;
}

uint32_t BL0940_SPI::getCFPulseCount()  //v
{
  //  unsigned 24 bit
  uint32_t raw = readRegister(BL0940_REG_CF_CNT);
  raw &= 0xFFFFFF;
  return raw;
}

float BL0940_SPI::getEnergy()  //v
{
  //  unsigned 24 bit
  uint32_t raw = readRegister(BL0940_REG_CF_CNT);
  raw &= 0xFFFFFF;
  return raw * _energyLSB;
}

float BL0940_SPI::getPhaseAngle()  //v
{
  //  datasheet p.20
  //  unsigned 16 bit
  uint32_t raw = readRegister(BL0940_REG_ANGLE);
  raw &= 0xFFFF;
  //  TODO elaborate, hard coded for 0.1.0
  //  factor depends on 50 Hz or 60 Hz.  (AC_FREQ_SEL in MODE REGISTER, 50 default)
  //  factor depends on sampling freq. typical 1 MHz
  return raw * (2.0 * PI * 50.0 * 1E-6);
}

float BL0940_SPI::getIntTemperature()  //v
{
  //  datasheet p.22
  //  only 10 bits defined, see BL0940.h file
  uint32_t raw = readRegister(BL0940_REG_INT_TEMP);
  raw &= 0x03FF;
  //  datasheet p.23
  float temperature = (170.0 / 448.0) * (raw / 2.0 - 32.0) - 45.0;
  return temperature;
}

float BL0940_SPI::getExtTemperature() //v
{
  //  datasheet p.22
  //  only 10 bits defined, see BL0940.h file
  uint32_t raw = readRegister(BL0940_REG_EXT_TEMP);
  raw &= 0x03FF;
  //  datasheet p.23
  float temperature = (170.0 / 448.0) * (raw / 2.0 - 32.0) - 45.0;
  return temperature;
}


//////////////////////////////////////////////////////
//
//  READ WRITE REGISTERS
//
uint16_t BL0940_SPI::getFastRMSControl()  //v
{
  //  datasheet p.18/19
  //  unsigned 15 bits
  uint16_t raw = readRegister(BL0940_REG_I_FAST_RMS_CTL);
  raw &= 0x7FFF;
  return raw;
}

//  TODO GETTER for flag cycle

void BL0940_SPI::setFastRMSControl(uint16_t ctrl, bool half)  //v
{
  //  datasheet p.18/19
  //  unsigned 15 bits
  uint16_t raw = ctrl & 0x7FFF;
  if (half) raw |= 0x8000;  //  0 = half cycle, 1 = full cycle.
  writeRegister(BL0940_REG_I_FAST_RMS_CTL, raw);
}

float BL0940_SPI::getCurrentRMSOffset()  //v
{
  //  datasheet p.18
  //  unclear signed or not => signed makes more sense for offset.
  int32_t raw = readRegister(BL0940_REG_I_RMSOS);
  raw &= 0xFF;
  return raw * (9.3132 * 32768);  //  2^15;
}

void BL0940_SPI::setCurrentRMSOffset(float offset)  //v
{
  //  datasheet p.18
  //  unclear signed or not => signed makes more sense for offset.
  uint32_t raw = offset / (9.3132 * 32768);  //  2^15;
  if (raw > 255) raw = 255;
  writeRegister(BL0940_REG_I_RMSOS, raw);
}

float BL0940_SPI::getPowerOffset()  //v
{
  //  datasheet p.15
  //  unsigned 8 bits  TODO
  uint32_t raw = readRegister(BL0940_REG_WATT_OS);
  float watt = raw * (8 * 3.05172);
  return watt;
}

void BL0940_SPI::setPowerOffset(float deltaWatt) //v
{
  //  datasheet p.15
  //  unsigned 8 bits
  uint32_t raw = deltaWatt / (8 * 3.05172);
  if (raw > 255) raw = 255;
  writeRegister(BL0940_REG_WATT_OS, raw);
}

float BL0940_SPI::getPowerCreep()  //v
{
  //  datasheet p.15
  //  unsigned 8 bits
  uint32_t raw = readRegister(BL0940_REG_WA_CREEP);
  raw &= 0xFF;
  float watt = raw * (8 * 3.0517578125);
  return watt;
}

void BL0940_SPI::setPowerCreep(float watt) //v
{
  //  datasheet p.15
  //  unsigned 8 bits
  uint32_t raw = watt / (8 * 3.0517578125);
  if (raw > 255) raw = 255;
  writeRegister(BL0940_REG_WA_CREEP, raw);
}

uint16_t BL0940_SPI::getUserMode()  //v
{
  //  datasheet p.9+19
  uint16_t raw = readRegister(BL0940_REG_MODE);
  raw &= 0x1300;
  return raw;
}

void BL0940_SPI::setUserMode(uint16_t mode)  //v
{
  //  datasheet p.9+19
  uint16_t raw = mode;
  //  limit to settable bits, reserved bits => 0.
  raw &= 0x1300;
  writeRegister(BL0940_REG_MODE, raw);
}

void BL0940_SPI::softReset()  //v
{
  // datasheet p.8
  //  24 bit magic number
  const uint32_t SOFT_RESET = 0x5A5A5A;
  writeRegister(BL0940_REG_SOFT_RESET, SOFT_RESET);
}

uint8_t BL0940_SPI::getWriteProtect()
{
  // datasheet p.8
  //  8 bit magic number TODO
  uint8_t raw = readRegister(BL0940_REG_USR_WRPROT);
  return raw;
}

void BL0940_SPI::setWriteProtect(bool wp)
{
  // datasheet p.8
  //  8 bit magic number
  const uint32_t WRITE_PROTECT = 0x55;  //  magic number
  writeRegister(BL0940_REG_USR_WRPROT, wp ? 0 : WRITE_PROTECT);
}

//  TODO
uint16_t BL0940_SPI::getTemperatureControl()
{
  //  datasheet p.22
  //  unsigned 16 bits TODO
  uint16_t raw = readRegister(BL0940_REG_TEMP_CTRL);
  raw &= 0xFFFF;
  return raw;
}

void BL0940_SPI::setTemperatureControl(uint16_t ctrl)
{
  //  datasheet p.22
  //  unsigned 16 bits TODO
  writeRegister(BL0940_REG_TEMP_CTRL, ctrl);
}

uint16_t BL0940_SPI::getExtTempGain()
{
  //  datasheet p.23
  //  unsigned 16 bits TODO
  uint16_t raw = readRegister(BL0940_REG_TPS2_GAIN);
  raw &= 0xFFFF;
  return raw;
}

void BL0940_SPI::setExtTempGain(uint16_t gain)
{
  //  datasheet p.23
  //  unsigned 16 bits TODO
  writeRegister(BL0940_REG_TPS2_GAIN, gain);
}

uint16_t BL0940_SPI::getExtTempOffset()
{
  //  datasheet p.23
  //  unsigned 16 bits TODO
  uint16_t raw = readRegister(BL0940_REG_TPS2_OS);
  raw &= 0xFFFF;
  return raw;
}

void BL0940_SPI::setExtTempOffset(uint16_t offset)
{
  //  datasheet p.23
  //  unsigned 16 bits
  writeRegister(BL0940_REG_TPS2_OS, offset);
}


//////////////////////////////////////////////////////
//
//  SPI
//
void BL0940_SPI::setSPIspeed(uint32_t speed)
{
  //  datasheet page 20, section 3.1
  //  900 KHz max datasheet
  _SPIspeed = speed;
  if (_SPIspeed > BL0940_SPI_MAX_SPEED)
  {
    _SPIspeed = BL0940_SPI_MAX_SPEED;
  }
  //  datasheet 3.1
  //  CPOL=0, CPHA=1 => SPI_MODE1
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
}

uint32_t BL0940_SPI::getSPIspeed()
{
  return _SPIspeed;
}

bool BL0940_SPI::usesHWSPI()
{
  return _hwSPI;
}

void BL0940_SPI::resetSPI()
{
  //  datasheet 3.1.3
  if (_hwSPI)  //  Hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    select(true);
    for (int i = 0; i < 6; i++)
    {
      _mySPI->transfer(0xFF);
    }
    select(false);
    _mySPI->endTransaction();
  }
  else         //  Software SPI
  {
    select(true);
    for (int i = 0; i < 6; i++)
    {
      swSPI_transfer(0xFF);
    }
    select(false);
  }
}


//
//  ERROR
//
int BL0940_SPI::getLastError()
{
  int e = _error;
  _error = BL0940_OK;
  return e;
}


///////////////////////////////////////////////
//
//  OPEN KNX extra API
//
#ifdef BL0940_SPI_CALLBACK
void BL0940_SPI::setChannelSelector(ChannelSelector selector) {
  _channelSelector = selector;
}
#endif


//////////////////////////////////////////////////////
//
//  PRIVATE
//
void BL0940_SPI::select(bool active)
{
//  OPEN KNX support
#ifdef BL0940_SPI_CALLBACK
  if (_channelSelector)
    _channelSelector(active);
#else
  digitalWrite(_select, active ? LOW : HIGH);
#endif
}


#define BL0940_CMD_WRITE                  0xA8
#define BL0940_CMD_READ                   0x58

int BL0940_SPI::writeRegister(uint8_t regAddr, uint32_t value)
{
  uint8_t checkSum = 0;
  uint8_t bytes = 3;

  _error = BL0940_OK;
  if (_hwSPI)  //  Hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    select(true);
    _mySPI->transfer(BL0940_CMD_WRITE);
    _mySPI->transfer(regAddr);
    checkSum = BL0940_CMD_WRITE + regAddr;
    while (bytes--)
    {
      uint8_t val = value >> (bytes * 8);
      _mySPI->transfer(val);
      checkSum += val;
    }
    //  INVERT CHECKSUM
    checkSum ^= 0xFF;
    _mySPI->transfer(checkSum);
    select(false);
    _mySPI->endTransaction();
  }
  else         //  Software SPI
  {
    select(true);
    swSPI_transfer(BL0940_CMD_WRITE);
    swSPI_transfer(regAddr);
    checkSum = BL0940_CMD_WRITE + regAddr;
    while (bytes--)
    {
      uint8_t val = value >> (bytes * 8);
      swSPI_transfer(val);
      checkSum += val;
    }
    //  INVERT CHECKSUM
    checkSum ^= 0xFF;
    swSPI_transfer(checkSum);
    select(false);
  }
  return _error;
}


uint32_t BL0940_SPI::readRegister(uint8_t regAddr)
{
  uint32_t value = 0;
  uint8_t  checkSum = 0;
  uint8_t  bytes = 3;

  _error = BL0940_OK;
  if (_hwSPI)  //  Hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    select(true);
    _mySPI->transfer(BL0940_CMD_READ);
    _mySPI->transfer(regAddr);
    checkSum = BL0940_CMD_READ + regAddr;

    while (bytes--)
    {
      value <<= 8;
      value += _mySPI->transfer(0x00);
      checkSum += value;
    }
    uint8_t crc = _mySPI->transfer(0x00);
    if (crc != (checkSum ^ 0xFF))
    {
      _error = BL0940_ERR_CHECKSUM;
      _errorCount++;
    }
    select(false);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    select(true);
    swSPI_transfer(BL0940_CMD_READ);
    swSPI_transfer(regAddr);
    checkSum = BL0940_CMD_READ + regAddr;

    while (bytes--)
    {
      value <<= 8;
      value += swSPI_transfer(0x00);
      checkSum += value;
    }
    uint8_t crc = swSPI_transfer(0x00);
    if (crc != (checkSum ^ 0xFF))
    {
      _error = BL0940_ERR_CHECKSUM;
      _errorCount++;
    }
    select(false);
  }
  //  debugging
  //  Serial.println(value, HEX);
  return value;
}


uint8_t BL0940_SPI::swSPI_transfer(uint8_t val)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  uint8_t dai = _dataIn;
  uint8_t value = 0;
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(val & mask));
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
    if (digitalRead(dai) == HIGH)
    {
      value |= mask;
    }
    //  force below 900.000 Hz rate (hard coded for now).
    delayMicroseconds(1);
  }
  return value;
}


//  -- END OF FILE --

