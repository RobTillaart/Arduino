//
//    FILE: MS5611.cpp
//  AUTHOR: Rob Tillaart
//          Erni - testing/fixes
// VERSION: 0.4.0
// PURPOSE: Arduino library for MS5611 temperature and pressure sensor
//     URL: https://github.com/RobTillaart/MS5611
//
//  HISTORY see changelog.md


#include "MS5611.h"


// datasheet page 10
#define MS5611_CMD_READ_ADC       0x00
#define MS5611_CMD_READ_PROM      0xA0
#define MS5611_CMD_RESET          0x1E
#define MS5611_CMD_CONVERT_D1     0x40
#define MS5611_CMD_CONVERT_D2     0x50


/////////////////////////////////////////////////////
//
//  PUBLIC
//
MS5611::MS5611(uint8_t deviceAddress, TwoWire * wire)
{
  _address           = deviceAddress;
  _wire              = wire;
  _samplingRate      = OSR_ULTRA_LOW;
  _temperature       = MS5611_NOT_READ;
  _pressure          = MS5611_NOT_READ;
  _result            = MS5611_NOT_READ;
  _lastRead          = 0;
  _deviceID          = 0;
  _pressureOffset    = 0;
  _temperatureOffset = 0;
  _compensation      = true;
}


bool MS5611::begin()
{
  if ((_address < 0x76) || (_address > 0x77)) return false;
  if (! isConnected()) return false;

  return reset();
}


bool MS5611::isConnected()
{
  _wire->beginTransmission(_address);
   #ifdef ARDUINO_ARCH_NRF52840
   //  needed for NANO 33 BLE
  _wire->write(0);
   #endif
  return (_wire->endTransmission() == 0);
}


bool MS5611::reset(uint8_t mathMode)
{
  command(MS5611_CMD_RESET);
  uint32_t start = micros();

  //  while loop prevents blocking RTOS
  while (micros() - start < 2800)
  {
    yield();
    delayMicroseconds(10);
  }

  //  initialize the C[] array
  initConstants(mathMode);

  //  read factory calibrations from EEPROM.
  bool ROM_OK = true;
  for (uint8_t reg = 0; reg < 7; reg++)
  {
    //  used indices match datasheet.
    //  C[0] == manufacturer - read but not used;
    //  C[7] == CRC - skipped.
    uint16_t tmp = readProm(reg);
    C[reg] *= tmp;
    //  _deviceID is a SHIFT XOR merge of 7 PROM registers, reasonable unique
    _deviceID <<= 4;
    _deviceID ^= tmp;
    //  Serial.println(readProm(reg));
    if (reg > 0)
    {
      ROM_OK = ROM_OK && (tmp != 0);
    }
  }
  return ROM_OK;
}


int MS5611::read(uint8_t bits)
{
  //  VARIABLES NAMES BASED ON DATASHEET
  //  ALL MAGIC NUMBERS ARE FROM DATASHEET

  convert(MS5611_CMD_CONVERT_D1, bits);
  if (_result) return _result;
  //  NOTE: D1 and D2 seem reserved in MBED (NANO BLE)
  uint32_t _D1 = readADC();
  if (_result) return _result;

  convert(MS5611_CMD_CONVERT_D2, bits);
  if (_result) return _result;
  uint32_t _D2 = readADC();
  if (_result) return _result;

  //  Serial.println(_D1);
  //  Serial.println(_D2);

  //  TEST VALUES - comment lines above
  //  uint32_t _D1 = 9085466;
  //  uint32_t _D2 = 8569150;

  //  TEMP & PRESS MATH - PAGE 7/20
  float dT = _D2 - C[5];
  _temperature = 2000 + dT * C[6];

  float offset =  C[2] + dT * C[4];
  float sens = C[1] + dT * C[3];

  if (_compensation)
  {
    //  SECOND ORDER COMPENSATION - PAGE 8/20
    //  COMMENT OUT < 2000 CORRECTION IF NOT NEEDED
    //  NOTE TEMPERATURE IS IN 0.01 C
    if (_temperature < 2000)
    {
      float T2 = dT * dT * 4.6566128731E-10;
      float t = (_temperature - 2000) * (_temperature - 2000);
      float offset2 = 2.5 * t;
      float sens2 = 1.25 * t;
      //  COMMENT OUT < -1500 CORRECTION IF NOT NEEDED
      if (_temperature < -1500)
      {
        t = (_temperature + 1500) * (_temperature + 1500);
        offset2 += 7 * t;
        sens2 += 5.5 * t;
      }
      _temperature -= T2;
      offset -= offset2;
      sens -= sens2;
    }
    //  END SECOND ORDER COMPENSATION
  }

  _pressure = (_D1 * sens * 4.76837158205E-7 - offset) * 3.051757813E-5;

  _lastRead = millis();
  return MS5611_READ_OK;
}


void MS5611::setOversampling(osr_t samplingRate)
{
  _samplingRate = (uint8_t) samplingRate;
}


float MS5611::getTemperature() const
{
  if (_temperatureOffset == 0) return _temperature * 0.01;
  return _temperature * 0.01 + _temperatureOffset;
};


float MS5611::getPressure() const
{
  if (_pressureOffset == 0) return _pressure * 0.01;
  return _pressure * 0.01 + _pressureOffset;
};

//       EXPERIMENTAL
uint16_t MS5611::getManufacturer()
{
  return readProm(0);
}

//       EXPERIMENTAL
uint16_t MS5611::getSerialCode()
{
  return readProm(7) >> 4;
}


/////////////////////////////////////////////////////
//
//  PRIVATE
//
void MS5611::convert(const uint8_t addr, uint8_t bits)
{
  //  values from page 3 datasheet - MAX column (rounded up)
  uint16_t del[5] = {600, 1200, 2300, 4600, 9100};

  uint8_t index = bits;
  if (index < 8) index = 8;
  else if (index > 12) index = 12;
  index -= 8;
  uint8_t offset = index * 2;
  command(addr + offset);

  uint16_t waitTime = del[index];
  uint32_t start = micros();
  //  while loop prevents blocking RTOS
  while (micros() - start < waitTime)
  {
    yield();
    delayMicroseconds(10);
  }
}


uint16_t MS5611::readProm(uint8_t reg)
{
  //  last EEPROM register is CRC - Page 13 datasheet.
  uint8_t promCRCRegister = 7;
  if (reg > promCRCRegister) return 0;

  uint8_t offset = reg * 2;
  command(MS5611_CMD_READ_PROM + offset);
  if (_result == 0)
  {
    uint8_t length = 2;
    int bytes = _wire->requestFrom(_address, length);
    if (bytes >= length)
    {
      uint16_t value = _wire->read() * 256;
      value += _wire->read();
      return value;
    }
    return 0;
  }
  return 0;
}


uint32_t MS5611::readADC()
{
  command(MS5611_CMD_READ_ADC);
  if (_result == 0)
  {
    uint8_t length = 3;
    int bytes = _wire->requestFrom(_address, length);
    if (bytes >= length)
    {
      uint32_t value = _wire->read() * 65536UL;
      value += _wire->read() * 256UL;
      value += _wire->read();
      return value;
    }
    return 0UL;
  }
  return 0UL;
}


int MS5611::command(const uint8_t command)
{
  yield();
  _wire->beginTransmission(_address);
  _wire->write(command);
  _result = _wire->endTransmission();
  return _result;
}


void MS5611::initConstants(uint8_t mathMode)
{
  //  constants that were multiplied in read() - datasheet page 8
  //  do this once and you save CPU cycles
  //
  //                               datasheet ms5611     |    appNote
  //                                mode = 0;           |    mode = 1
  C[0] = 1;
  C[1] = 32768L;          //  SENSt1   = C[1] * 2^15    |    * 2^16
  C[2] = 65536L;          //  OFFt1    = C[2] * 2^16    |    * 2^17
  C[3] = 3.90625E-3;      //  TCS      = C[3] / 2^8     |    / 2^7
  C[4] = 7.8125E-3;       //  TCO      = C[4] / 2^7     |    / 2^6
  C[5] = 256;             //  Tref     = C[5] * 2^8     |    * 2^8
  C[6] = 1.1920928955E-7; //  TEMPSENS = C[6] / 2^23    |    / 2^23

  if (mathMode == 1)  //  Appnote version for pressure.
  {
    C[1] = 65536L;          //  SENSt1
    C[2] = 131072L;         //  OFFt1
    C[3] = 7.8125E-3;       //  TCS
    C[4] = 1.5625e-2;       //  TCO
  }
}

// -- END OF FILE --

