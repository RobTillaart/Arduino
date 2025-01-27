//
//    FILE: APDS9900.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-12-09
// VERSION: 0.2.0
// PURPOSE: Arduino library for the APDS9900 environment sensor.
//     URL: https://github.com/RobTillaart/APDS9900



#include "APDS9900.h"


//
//  REGISTERS
//
#define APDS9900_ENABLE           0x00
#define APDS9900_ATIME            0x01
#define APDS9900_PTIME            0x02
#define APDS9900_WTIME            0x03
#define APDS9900_AILTL            0x04
#define APDS9900_AILTH            0x05
#define APDS9900_AIHTL            0x06
#define APDS9900_AIHTH            0x07
#define APDS9900_PILTL            0x08
#define APDS9900_PILTH            0x09
#define APDS9900_PIHTL            0x0A
#define APDS9900_PIHTH            0x0B
#define APDS9900_PERS             0x0C
#define APDS9900_CONFIG           0x0D
#define APDS9900_PPCOUNT          0x0E
#define APDS9900_CONTROL          0x0F
//                                0x10
#define APDS9900_REV              0x11
#define APDS9900_ID               0x12
#define APDS9900_STATUS           0x13
#define APDS9900_CDATAL           0x14
#define APDS9900_CDATAH           0x15
#define APDS9900_IRDATAL          0x16
#define APDS9900_IRDATAH          0x17
#define APDS9900_PDATAL           0x18
#define APDS9900_PDATAH           0x19



APDS9900::APDS9900(TwoWire *wire)
{
  _wire = wire;
  _error = 0;
}


bool APDS9900::begin()
{
  if (! isConnected())
  {
    return false;
  }
  //  ENABLE page 18
  //  Enable WEN = Wait, PEN = Prox, AEN = ALS, PON = Power On
  uint8_t enable = 0x0F;
  writeRegister(APDS9900_ENABLE, enable);
  return true;
}


bool APDS9900::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t APDS9900::getAddress()
{
  return _address;
}


//  ENABLE REGISTER page 18
void APDS9900::wakeUp()
{
  //  read back to keep all bits set
  uint8_t value = readRegister(APDS9900_ENABLE);
  //  only write when needed.
  if ((value & 0x01) == 0x00)
  {
    value |= 0x0F;  //  set PON bit  PON = POWER ON, enable all
    writeRegister(APDS9900_ENABLE, value);
  }
}


void APDS9900::sleep()
{
  //  read back to keep all bits set
  uint8_t value = readRegister(APDS9900_ENABLE);
  value &= ~0x0F;  //  clear PON bit  PON = POWER ON, disable all
  writeRegister(APDS9900_ENABLE, value);
}


//  ATIME page 19
void APDS9900::setIntegrationTime(uint16_t milliseconds)
{
  if (milliseconds < 3) milliseconds = 3;
  uint16_t ATIME = round(milliseconds * 0.367647);  //  magic nr.  1/2.72 = 0,3676470588235294...
  if (ATIME > 255) ATIME = 255;
  ATIME = 256 - ATIME;
  writeRegister(APDS9900_ATIME, ATIME);
}


uint16_t APDS9900::getIntegrationTime()
{
  uint8_t value = readRegister(APDS9900_ATIME);
  uint16_t ms = round((256 - value) * 2.72);
  return ms;
}


//  PTIME page 19
void APDS9900::setProximityTime(uint16_t milliseconds)
{
  if (milliseconds < 3) milliseconds = 3;
  uint16_t PTIME = round(milliseconds * 0.367647);  //  magic nr.  1/2.72 = 0,3676470588235294...
  if (PTIME > 255) PTIME = 255;
  PTIME = 256 - PTIME;
  writeRegister(APDS9900_PTIME, PTIME);
}


uint16_t APDS9900::getProximityTime()
{
  uint8_t value = readRegister(APDS9900_PTIME);
  uint16_t ms = round((256 - value) * 2.72);
  return ms;
}


//  WTIME page 19, WLONG page 21
void APDS9900::setWaitTime(uint16_t milliseconds)
{
  bool WLONG = (milliseconds > 696);
  //  first set WLONG register
  writeRegister(APDS9900_CONFIG, WLONG ? 0x02 : 0x00);

  uint16_t WTIME = 0;
  if (WLONG)
  {
    WTIME = round(milliseconds * 0.03125);  //  magic nr.  1/32 = 0,03125  (could be a >> 5.)
  }
  else
  {
    if (milliseconds < 3) milliseconds = 3;
    WTIME = round(milliseconds * 0.367647);  //  magic nr.  1/2.72 = 0,3676470588235294...
  }
  if (WTIME > 255) WTIME = 255;
  WTIME = 256 - WTIME;
  writeRegister(APDS9900_WTIME, WTIME);
}


uint16_t APDS9900::getWaitTime()
{
  bool WLONG = ((readRegister(APDS9900_CONFIG) & 0x02) == 0x02);
  uint8_t value = readRegister(APDS9900_WTIME);

  if (WLONG) return round((256 - value) * 32);
  return round((256 - value) * 2.72);
}


//////////////////////////////////////////////////////////////////////////


bool APDS9900::setALSThresholds(uint16_t lowTH, uint16_t highTH)
{
  if (lowTH >= highTH) return false;
  writeRegister16(APDS9900_AILTL, lowTH);
  writeRegister16(APDS9900_AIHTL, highTH);
  return true;
}


bool APDS9900::setPROXThresholds(uint16_t lowTH, uint16_t highTH)
{
  if (lowTH >= highTH) return false;
  writeRegister16(APDS9900_PILTL, lowTH);
  writeRegister16(APDS9900_PIHTL, highTH);
  return true;
}


//  PPERS page 20
bool APDS9900::setALSInterruptPersistence(uint8_t value)
{
  if (value > 0x0F) return false;
  uint8_t val = readRegister(APDS9900_PERS);
  if ((val & 0x0F) != value)
  {
    val &= 0xF0;
    val |= value;
    writeRegister(APDS9900_PERS, val);
  }
  return true;
}


bool APDS9900::setPROXInterruptPersistence(uint8_t value)
{
  if (value > 0x0F) return false;
  uint8_t val = readRegister(APDS9900_PERS);
  uint8_t tmp = value << 4;
  if ((val & 0xF0) != tmp)
  {
    val &= 0x0F;
    val |= tmp;
    writeRegister(APDS9900_PERS, val);
  }
  return true;
}


//  PPCOUNT P21
void APDS9900::setProximityPulseCount(uint8_t value)
{
  writeRegister(APDS9900_PPCOUNT, value);
}


uint8_t APDS9900::getProximityPulseCount()
{
  uint8_t value = readRegister(APDS9900_PPCOUNT);
  return value;
}


//
//  CONFIGURATION datasheet page 22
//
//  PDRIVE - datasheet page 22
bool APDS9900::setLedDriveStrength(uint8_t strength)
{
  if (strength > 3) return false;
  uint8_t control = readRegister(APDS9900_CONTROL);
  control &= 0x3F;
  control |= (strength << 6);
  writeRegister(APDS9900_CONTROL, control);
  return true;
}

uint8_t APDS9900::getLedDriveStrength()
{
  uint8_t value = readRegister(APDS9900_CONTROL);
  value >>= 6;
  return value;
}

//  PDIODE - datasheet page 22
//  must be 2.
bool APDS9900::setProximityDiodeSelect(uint8_t channel)
{
  if (channel > 3) return false;
  uint8_t control = readRegister(APDS9900_CONTROL);
  control &= 0xCF;
  control |= (channel << 4);
  writeRegister(APDS9900_CONTROL, control);
  return true;
}

uint8_t APDS9900::getProximityDiodeSelect()
{
  uint8_t value = readRegister(APDS9900_CONTROL);
  value >>= 4;
  value &= 0x03;
  return value;
}

//  PGAIN - datasheet page 22
bool APDS9900::setProximityGain(uint8_t gain)
{
  if (gain > 3) return false;
  uint8_t control = readRegister(APDS9900_CONTROL);
  control &= 0xF3;
  control |= (gain << 2);
  writeRegister(APDS9900_CONTROL, control);
  return true;
}

uint8_t APDS9900::getProximityGain()
{
  uint8_t value = readRegister(APDS9900_CONTROL);
  value >>= 2;
  value &= 0x03;
  return value;
}

//  AGAIN - datasheet page 22
//  0 = 1x,  1 = 8x,  2 = 16x,  3 = 120x
bool APDS9900::setALSGain(uint8_t gain)
{
  if (gain > 3) return false;
  uint8_t control = readRegister(APDS9900_CONTROL);
  control &= 0xFC;
  control |= gain;
  writeRegister(APDS9900_CONTROL, control);
  return true;
}

uint8_t APDS9900::getALSGain()
{
  uint8_t value = readRegister(APDS9900_CONTROL);
  value &= 0x03;
  if (value == 0) return 1;
  if (value == 1) return 8;
  if (value == 2) return 16;
  return 120;
}


//
//  MISC
//
//  REV  page 22
uint8_t APDS9900::getRevision()
{
  return readRegister(APDS9900_REV);
}


//  ID  page 23
uint8_t APDS9900::getDeviceID()
{
  return readRegister(APDS9900_ID);
}


uint8_t APDS9900::getStatus()
{
  return readRegister(APDS9900_STATUS);
}

//  LUX datasheet page 9
float APDS9900::getLux(float GA)
{
  //  calibration constants from datasheet page 9
  //  coefficients open air
  float B = 2.23;   //  ??
  float C = 0.7;    //  ??
  float D = 1.42;   //  ??
  float DF = 52;    //  device factor ??

  float channel0 = getALS_CDATA();
  float channel1 = getALS_IRDATA();
  float ALSIT = getIntegrationTime();
  float AGAIN = getALSGain();

  float IAC1 = channel0 - B * channel1;
  if (IAC1 < 0) IAC1 = 0;
  float IAC2 = C * channel0 - D * channel1;
  if (IAC2 < 0) IAC1 = 0;
  float IAC = (IAC1 >= IAC2) ? IAC1 : IAC2;
  float LPC = GA * DF / (ALSIT * AGAIN);
  float LUX = IAC * LPC;

  return LUX;
}

uint16_t APDS9900::getALS_CDATA()
{
  return readRegister16(APDS9900_CDATAL);
}

uint16_t APDS9900::getALS_IRDATA()
{
  return readRegister16(APDS9900_IRDATAL);
}

uint16_t APDS9900::getPROX_DATA()
{
  return readRegister16(APDS9900_PDATAL);
}


//////////////////////////////////////////////////////////////////////////


int APDS9900::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


//////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//

//  All reg are or-ed with 0xA0 to access register and to auto increment register counter.

int APDS9900::writeRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(0xA0 | reg);
  _error = _wire->endTransmission();
  return _error;
}


int APDS9900::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(0xA0 | reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return _error;
}


int APDS9900::writeRegister16(uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(0xA0 | reg);
  _wire->write(value & 0xFF);
  _wire->write(value >> 8);
  _error = _wire->endTransmission();
  return _error;
}


uint8_t APDS9900::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(0xA0 | reg);
  _error = _wire->endTransmission();
  uint8_t bytes = _wire->requestFrom(_address, (uint8_t)1);
  if (bytes == 1)
  {
    return _wire->read();
  }
  //  ERROR HANDLING
  return 0;
}


uint16_t APDS9900::readRegister16(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(0xA0 | reg);
  _error = _wire->endTransmission();
  uint8_t bytes = _wire->requestFrom(_address, (uint8_t)2);
  if (bytes == 2)
  {
    uint16_t value = _wire->read();
    value += (_wire->read() * 256);
    return value;
  }
  //  ERROR HANDLING
  return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//  DERIVED
//
APDS9901::APDS9901(TwoWire * wire) : APDS9900(wire)
{
  //  no specific code yet
}


//  -- END OF FILE --

