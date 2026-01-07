//
//    FILE: BL0942_SPI.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-12-29
// VERSION: 0.1.0
// PURPOSE: Arduino library for BL0942 energy monitor, SPI interface.
//     URL: https://github.com/RobTillaart/BL0942_SPI


#include "BL0942_SPI.h"

//  REGISTERS
//  datasheet page 8.
//
//      NAME                                NUMBER       BITS    RW
//-------------------------------------------------------------------
#define BL0942_REG_I_WAVE                   0x01      //  20     RO
#define BL0942_REG_V_WAVE                   0x02      //  20     RO
#define BL0942_REG_I_RMS                    0x03      //  24     RO
#define BL0942_REG_V_RMS                    0x04      //  24     RO
#define BL0942_REG_I_FAST_RMS               0x05      //  24     RO
#define BL0942_REG_WATT                     0x06      //  24     RO
#define BL0942_REG_CF_CNT                   0x07      //  24     RO
#define BL0942_REG_FREQ                     0x08      //  16     RO
#define BL0942_REG_STATUS                   0x09      //  10     RO

#define BL0942_REG_I_RMSOS                  0x12      //   8     RW
#define BL0942_REG_WA_CREEP                 0x14      //   8     RW
#define BL0942_REG_I_FAST_RMS_TH            0x15      //  16     RW
#define BL0942_REG_I_FAST_RMS_CYC           0x16      //   3     RW
#define BL0942_REG_FREQ_CYC                 0x17      //   2     RW
#define BL0942_REG_OT_FUNX                  0x18      //   6     RW
#define BL0942_REG_MODE                     0x19      //  10     RW
#define BL0942_REG_GAIN_CR                  0x1A      //   2     RW
#define BL0942_REG_SOFT_RESET               0x1C      //  24     RW
#define BL0942_REG_USR_WRPROT               0x1D      //   8     RW

//
//  SPI MAX SPEED
//  datasheet states 900 kHz
//
#define BL0942_SPI_MAX_SPEED        (900000)


//
//  CALIBRATION MAGIC NUMBERS
//  extracted from app note (Chinese)
//  + page 17 datasheet
//  these constants have the factor 1000 for mV and mA in it.
const float BL0942_VREF          = 1.218;
const float BL0942_MAGIC_CURRENT = 305978000;
const float BL0942_MAGIC_VOLT    = 73989000;
const float BL0942_MAGIC_POWER   = 3537000000;


//
//  HARDWARE SPI
//
BL0942_SPI::BL0942_SPI(__SPI_CLASS__ * mySPI)
{
  BL0942_SPI(255, mySPI);
}

BL0942_SPI::BL0942_SPI(uint8_t select, __SPI_CLASS__ * mySPI)
{
  _select   = select;
  _dataIn   = 255;
  _dataOut  = 255;
  _clock    = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
}

//
//  SOFTWARE SPI
//
BL0942_SPI::BL0942_SPI(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock)
{
  _select   = select;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}


bool BL0942_SPI::begin()
{
  pinMode(_select, OUTPUT);
  select(false);

  setSPIspeed(BL0942_SPI_MAX_SPEED);

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
    digitalWrite(_clock,   LOW);
  }

  //  reset variables
  _error = BL0942_OK;
  return true;
}


//////////////////////////////////////////////////////
//
//  CALIBRATION
//
void BL0942_SPI::calibrate(float shunt, float reductionFactor)
{
  //  based upon APPNOTE (Chinese) page 4
  _voltageLSB = BL0942_VREF * reductionFactor / BL0942_MAGIC_VOLT;

  _currentLSB = BL0942_VREF / (BL0942_MAGIC_CURRENT * shunt);

  //  optimized formula
  //  _powerLSB   = _voltageLSB * _currentLSB * 6.3995208E+06;

  //  reference APP NOTE formula
  _powerLSB   = BL0942_VREF * BL0942_VREF * reductionFactor;
  _powerLSB  /= (BL0942_MAGIC_POWER * shunt);

  //  optimized formula
  _energyLSB  = (1638.4 * 256 / 3600000) * _powerLSB;
}

float BL0942_SPI::getVoltageLSB()
{
  return _voltageLSB;
}

void BL0942_SPI::setVoltageLSB(float voltageLSB)
{
  _voltageLSB = voltageLSB;
  // _powerLSB   = _voltageLSB * _currentLSB * 6.3995208E+06;
  // _energyLSB  = 1638.4 * 256 * _powerLSB / 3600000;
}

float BL0942_SPI::getCurrentLSB()
{
  return _currentLSB;
}

void BL0942_SPI::setCurrentLSB(float currentLSB)
{
  _currentLSB = currentLSB;
  // _powerLSB   = _voltageLSB * _currentLSB * 6.3995208E+06;
  // _energyLSB  = 1638.4 * 256 * _powerLSB / 3600000;
}

float BL0942_SPI::getPowerLSB()
{
  return _powerLSB;
}

void BL0942_SPI::setPowerLSB(float powerLSB)
{
  _powerLSB = powerLSB;
}

float BL0942_SPI::getEnergyLSB()
{
  return _energyLSB;
}

void BL0942_SPI::setEnergyLSB(float energyLSB)
{
  _energyLSB = energyLSB;
}


//////////////////////////////////////////////////////
//
//  READ ONLY REGISTERS
//
float BL0942_SPI::getIWave()
{
  int32_t raw = readRegister(BL0942_REG_I_WAVE);
  //  extend sign bit
  if (raw & 0x00040000) raw |= 0xFFF0000;
  //  TODO formula units?
  return raw * _currentLSB;
}

float BL0942_SPI::getVWave()
{
  int32_t raw = readRegister(BL0942_REG_V_WAVE);
  //  extend sign bit
  if (raw & 0x00040000) raw |= 0xFFF0000;
  return raw * _voltageLSB;
}

float BL0942_SPI::getIRMS()
{
  //  unsigned
  uint32_t raw = readRegister(BL0942_REG_I_RMS);
  return raw * _currentLSB;
}

float BL0942_SPI::getVRMS()
{
  //  unsigned
  uint32_t raw = readRegister(BL0942_REG_V_RMS);
  //  RMS factor?
  return raw * _voltageLSB;
}

float BL0942_SPI::getIRMSFast()
{
  //  unsigned
  uint32_t raw = readRegister(BL0942_REG_I_FAST_RMS);
  //  RMS factor?
  return raw * _currentLSB;
}

float BL0942_SPI::getWatt()
{
  int32_t raw = readRegister(BL0942_REG_WATT);
  //  extend sign bit
  if (raw & 0x00800000) raw |= 0xFF00000;
  return raw * _powerLSB;
}

uint32_t BL0942_SPI::getCFPulseCount()
{
  //  unsigned
  uint32_t raw = readRegister(BL0942_REG_CF_CNT);
  return raw;
}

float BL0942_SPI::getEnergy()
{
  //  unsigned
  uint32_t raw = readRegister(BL0942_REG_CF_CNT);
  return raw * _energyLSB;
}

float BL0942_SPI::getFrequency()
{
  //  unsigned
  uint32_t raw = readRegister(BL0942_REG_FREQ);
  //  page 19 formula  default 20000 == 50 Hz
  return 1e6 / raw;
}

//  only 10 bits defined,
//  see BL0942.h file
uint16_t BL0942_SPI::getStatus()
{
  uint32_t raw = readRegister(BL0942_REG_STATUS);
  return raw & 0x03FF;
}


//////////////////////////////////////////////////////
//
//  READ WRITE REGISTERS
//
float BL0942_SPI::getCurrentRMSOffset()
{
  int32_t raw = readRegister(BL0942_REG_I_RMSOS);
  //  TODO formula units?
  //  _currentLSB  ?
  return raw;
}

void BL0942_SPI::setCurrentRMSOffset(float offset)
{
  uint8_t raw = offset;  //  _currentLSB  ?
  writeRegister(BL0942_REG_I_RMSOS, raw);
}

float BL0942_SPI::getPowerCreep()
{
  int32_t raw = readRegister(BL0942_REG_WA_CREEP);
  float watt = raw * (3125.0/256.0);
  return watt;
}

void BL0942_SPI::setPowerCreep(float watt)
{
  uint8_t raw = watt * (256.0 / 3125.0);
  writeRegister(BL0942_REG_WA_CREEP, raw);
}

//  threshold = Ampere
//  If I_FAST_RMS[23:8] >= I_FAST_RMS_TH[15:0] ==> flag
//  ???  only 16 upper bits compared to 16 bit value
//  ==> there must be a factor 256 somewhere.
float BL0942_SPI::getFastRMSThreshold()
{
  uint16_t raw = readRegister(BL0942_REG_I_FAST_RMS_TH);
  //  TODO formula units?
  //  raw * _currentLSB * 256;
  return raw;
}

void BL0942_SPI::setFastRMSThreshold(float threshold)
{
  uint16_t raw = threshold;
  writeRegister(BL0942_REG_I_FAST_RMS_TH, raw);
}


uint8_t BL0942_SPI::getFastRMSCycles()
{
  uint8_t raw = readRegister(BL0942_REG_I_FAST_RMS_CYC);
  return raw;
}

//  0    == 0.5 cycles
//  1    == 1 cycles
//  2    == 2 cycles
//  3    == 4 cycles
//  4..7 == 8 cycles
void BL0942_SPI::setFastRMSCycles(uint8_t cycles)
{
  uint8_t raw = cycles;
  if (raw > 7) raw = 7;
  writeRegister(BL0942_REG_I_FAST_RMS_CYC, raw);
}


uint8_t BL0942_SPI::getFrequencyCycles()
{
  uint8_t raw = readRegister(BL0942_REG_FREQ_CYC);
  return raw;
}

void BL0942_SPI::setFrequencyCycles(uint8_t cycles)
{
  uint8_t raw = cycles;
  if (raw > 3) raw = 3;
  writeRegister(BL0942_REG_FREQ_CYC, raw);
}

uint8_t BL0942_SPI::getOutputConfigMask()
{
  uint8_t raw = readRegister(BL0942_REG_OT_FUNX);
  return raw;
}

void BL0942_SPI::setOutputConfigMask(uint8_t mask)
{
  uint8_t raw = mask;
  if (raw > 63) raw = 63;
  writeRegister(BL0942_REG_OT_FUNX, raw);
}

uint16_t BL0942_SPI::getUserMode()
{
  uint16_t raw = readRegister(BL0942_REG_MODE);
  return raw;
}

void BL0942_SPI::setUserMode(uint16_t mode)
{
  uint16_t raw = mode;
  //  limit to 10 bits
  raw &= 0x03FF;
  writeRegister(BL0942_REG_MODE, raw);
}

uint8_t BL0942_SPI::getCurrentGain()
{
  uint8_t raw = readRegister(BL0942_REG_GAIN_CR);
  return raw;
}

void BL0942_SPI::setCurrentGain(uint8_t gain)
{
  uint8_t raw = gain;
  if (raw > 3) raw = 3;
  writeRegister(BL0942_REG_GAIN_CR, raw);
}

void BL0942_SPI::softReset()
{
  const uint32_t SOFT_RESET = 0x5A5A5A;  //  magic number
  writeRegister(BL0942_REG_SOFT_RESET, SOFT_RESET);
}

uint8_t BL0942_SPI::getWriteProtect()
{
  uint8_t raw = readRegister(BL0942_REG_USR_WRPROT);
  return raw;
}

void BL0942_SPI::setWriteProtect(bool wp)
{
  const uint32_t WRITE_PROTECT = 0x55;  //  magic number
  writeRegister(BL0942_REG_USR_WRPROT, wp ? 0 : WRITE_PROTECT);
}


//////////////////////////////////////////////////////
//
//  SPI
//
void BL0942_SPI::setSPIspeed(uint32_t speed)
{
  //  datasheet page 20, section 3.1
  //  900 KHz max datasheet
  _SPIspeed = speed;
  if (_SPIspeed > BL0942_SPI_MAX_SPEED) _SPIspeed = BL0942_SPI_MAX_SPEED;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
}

uint32_t BL0942_SPI::getSPIspeed()
{
  return _SPIspeed;
}

bool BL0942_SPI::usesHWSPI()
{
  return _hwSPI;
}


//
//  ERROR
//
int BL0942_SPI::getLastError()
{
  int e = _error;
  _error = BL0942_OK;
  return e;
}


///////////////////////////////////////////////
//
//  OPEN KNX extra API
//
#ifdef BL0942_SPI_CALLBACK
void BL0942_SPI::setChannelSelector(ChannelSelector selector) {
  _channelSelector = selector;
}
#endif


//////////////////////////////////////////////////////
//
//  PRIVATE
//
void BL0942_SPI::select(bool active)
{
//  OPEN KNX support
#ifdef BL0942_SPI_CALLBACK
  if (_channelSelector)
    _channelSelector(active);
#else
  digitalWrite(_select, active ? LOW : HIGH);
#endif
}


#define BL0942_CMD_WRITE                  0xA8
#define BL0942_CMD_READ                   0x58

int BL0942_SPI::writeRegister(uint8_t regAddr, uint32_t value)
{
  uint8_t checkSum = 0;
  uint8_t bytes = 3;

  _error = BL0942_OK;
  if (_hwSPI)  //  Hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    select(true);
    _mySPI->transfer(BL0942_CMD_WRITE);
    _mySPI->transfer(regAddr);
    checkSum = BL0942_CMD_WRITE + regAddr;
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
    swSPI_transfer(BL0942_CMD_WRITE);
    swSPI_transfer(regAddr);
    checkSum = BL0942_CMD_WRITE + regAddr;
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


uint32_t BL0942_SPI::readRegister(uint8_t regAddr)
{
  uint32_t value = 0;
  uint8_t  checkSum = 0;
  uint8_t  bytes = 3;

  _error = BL0942_OK;
  if (_hwSPI)  //  Hardware SPI
  {
    _mySPI->beginTransaction(_spi_settings);
    select(true);
    _mySPI->transfer(BL0942_CMD_READ);
    _mySPI->transfer(regAddr);
    checkSum = BL0942_CMD_READ + regAddr;

    while (bytes--)
    {
      value <<= 8;
      value += _mySPI->transfer(0x00);
      checkSum += value;
    }
    uint8_t crc = _mySPI->transfer(0x00);
    if (crc != (checkSum ^ 0xFF))
    {
      _error = BL0942_ERR_CHECKSUM;
    }
    select(false);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    select(true);
    swSPI_transfer(BL0942_CMD_READ);
    swSPI_transfer(regAddr);
    checkSum = BL0942_CMD_READ + regAddr;

    while (bytes--)
    {
      value <<= 8;
      value += swSPI_transfer(0x00);
      checkSum += value;
    }
    uint8_t crc = swSPI_transfer(0x00);
    if (crc != (checkSum ^ 0xFF))
    {
      _error = BL0942_ERR_CHECKSUM;
    }
    select(false);
  }
  //  debugging
  //  Serial.println(value, HEX);
  return value;
}


uint8_t BL0942_SPI::swSPI_transfer(uint8_t val)
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

