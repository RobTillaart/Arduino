//
//    FILE: MS5837.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2023-11-12
// PURPOSE: Arduino library for MS5837 temperature and pressure sensor.
//     URL: https://github.com/RobTillaart/MS5837


#include "MS5837.h"

//  commands  (MS5611 alike)
#define MS5837_CMD_READ_ADC       0x00
#define MS5837_CMD_READ_PROM      0xA0
#define MS5837_CMD_RESET          0x1E
#define MS5837_CMD_CONVERT_D1     0x4A  //  differs from MS5611
#define MS5837_CMD_CONVERT_D2     0x5A  //  differs from MS5611


//  CONSTRUCTOR
MS5837::MS5837(TwoWire *wire)
{
  _wire = wire;
}

bool MS5837::begin(uint8_t mathMode)
{
  if (! isConnected()) return false;
  reset(mathMode);

  return true;
}

bool MS5837::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}

bool MS5837::reset(uint8_t mathMode)
{
  command(MS5837_CMD_RESET);
  uint32_t start = millis();
  //  while loop prevents blocking RTOS
  while (micros() - start < 10)
  {
    yield();
    delay(1);
  }

  initConstants(mathMode);

  //  SKIP CRC check (for now)

  //  derive the type from mathMode instead of the other way around.
  //  user must provide correct mathMode.
  _type = MS5837_TYPE_30;
  if (mathMode == 1) _type = MS5837_TYPE_02;
  if (mathMode == 2) _type = MS5803_TYPE_01;
  return true;
}

uint8_t MS5837::getType()
{
  return _type;
}

uint8_t MS5837::getAddress()
{
  return _address;
}


//////////////////////////////////////////////////////////////////////
//
//  READ
//
//  datasheet page 7
//  bits determines OSR => nr of samples => accuracy etc
bool MS5837::read(uint8_t bits)
{
  if (isConnected() == false) return false;

  int OSR = constrain(bits, 8, 13);
  OSR -= 8;
  //  datasheet page 2 OSR, ADC maximum conversion time.
  uint8_t waitMillis[6] = { 1, 2, 3, 5, 9, 18 };
  uint8_t wait = waitMillis[OSR];

   //  D1 conversion
  _wire->beginTransmission(_address);
  //  datasheet page 7 adjust command byte based on OSR
  _wire->write(MS5837_CMD_CONVERT_D1 + OSR * 2);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    //  _error = MS5837_I2C_ERROR ?
    return false;
  }

  uint32_t start = millis();

  //  while loop prevents blocking RTOS
  while (micros() - start < wait)
  {
    yield();
    delay(1);
  }
  //  NOTE: names D1 and D2 are reserved in MBED (NANO BLE)
  uint32_t _D1 = readADC();

   //  D2 conversion
  _wire->beginTransmission(_address);
  //  datasheet page 7 adjust command byte based on OSR
  _wire->write(MS5837_CMD_CONVERT_D2 + OSR * 2);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    //  _error = MS5837_I2C_ERROR ?
    return false;
  }

  start = millis();
  //  while loop prevents blocking RTOS
  while (micros() - start < wait)
  {
    yield();
    delay(1);
  }

  //  NOTE: names D1 and D2 are reserved in MBED (NANO BLE)
  uint32_t _D2 = readADC();

  float dT = _D2 - C[5];
  _temperature = 2000 + dT * C[6];

  float offset = C[2] + dT * C[4];
  float sens   = C[1] + dT * C[3];
  _pressure = _D1 * sens + offset;


  //  Second order compensation
  if (_temperature < 20)
  {
    float ti = dT * dT * (11 * 2.91038304567E-11);  //  1 / 2^35
    float t = (_temperature - 2000) * (_temperature - 2000);
    float offset2 = t * (31 * 0.125);  //  1 / 2^3
    float sens2 = t * (63 * 0.03125);  //  1 / 2^5

    offset       -= offset2;
    sens         -= sens2;
    _temperature -= ti;
  }
  //                         1 / 2^21                    C[7] / 100
  _pressure = (_D1 * sens * 4.76837158203E-7 - offset) * C[7] * 0.01;
  _temperature *= 0.01;

  _lastRead = millis();
  return true;
}

uint32_t MS5837::lastRead()
{
  return _lastRead;
}


float MS5837::getPressure()
{
  return _pressure;
}


float MS5837::getTemperature()
{
  return _temperature;
}


//  https://www.mide.com/air-pressure-at-altitude-calculator
//  https://community.bosch-sensortec.com/t5/Question-and-answers/How-to-calculate-the-altitude-from-the-pressure-sensor-data/qaq-p/5702 (stale link).
//  https://en.wikipedia.org/wiki/Pressure_altitude
float MS5837::getAltitude(float airPressure)
{
  float ratio = _pressure / airPressure;
  return 44330 * (1 - pow(ratio, 0.190294957));
}


//////////////////////////////////////////////////////////////////////
//
//  DENSITY for depth
//
void MS5837::setDensity(float density)
{
  _density = density;
}

float MS5837::getDensity()
{
  return _density;
}

float MS5837::getDepth(float airPressure)
{
  //  9.80665 == Gravity constant.
  //  1 / (_density * 9.80665 * 10)  can be pre-calculated and cached in setDensity.
  //
  //  delta P = rho * g * h  => h = delta P / rho * g
  //  pressure = mbar,
  //  density grams/cm3 => correction factor 0.1 (= 1/10)
  return (_pressure - airPressure)/(_density * 9.80665 * 10);
}


//////////////////////////////////////////////////////////////////////
//
//  ERROR
//
int MS5837::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


//////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
int MS5837::command(uint8_t cmd)
{
  yield();
  _wire->beginTransmission(_address);
  _wire->write(cmd);
  _result = _wire->endTransmission();
  return _result;
}


void MS5837::initConstants(uint8_t mathMode)
{
  //  Constants that were multiplied in read() - datasheet page 8
  //  do this once and you save CPU cycles.
  //
  //  datasheet MS5837_30  page 7
  //
  //                          mathMode         = 0    |   = 1    |   = 2    |
  C[0] = 1;               //  manufacturer
  C[1] = 32768L;          //  SENSt1   = C[1] * 2^15  |  * 2^16  |  * 2^15  |
  C[2] = 65536L;          //  OFFt1    = C[2] * 2^16  |  * 2^17  |  * 2^16  |
  C[3] = 3.90625E-3;      //  TCS      = C[3] / 2^8   |  / 2^7   |  / 2^8   |
  C[4] = 7.8125E-3;       //  TCO      = C[4] / 2^7   |  / 2^6   |  / 2^7   |
  C[5] = 256;             //  Tref     = C[5] * 2^8   |  * 2^8   |  * 2^8   |
  C[6] = 1.1920928955E-7; //  TEMPSENS = C[6] / 2^23  |  / 2^23  |  / 2^23  |
  C[7] = 1.220703125E-4;  //  compensate uses / 2^13  |  / 2^15  |  / 2^15  |

  //  App note version for pressure.
  //  adjustments for MS5837_02
  if (mathMode == 1)
  {
    C[1] *= 2;  //  SENSt1
    C[2] *= 2;  //  OFFt1
    C[3] *= 2;  //  TCS
    C[4] *= 2;  //  TCO
    C[7] /= 4;  //  compensation code has factor 4.
  }

  //  adjustments for MS5803_01
  if (mathMode == 2)
  {
    C[7] /= 4;  //  compensation code has factor 4.
  }


  for (uint8_t i = 0; i < 7 ; i++)
  {
    _wire->beginTransmission(_address);
    _wire->write(MS5837_CMD_READ_PROM + i + i);
    _wire->endTransmission();
    uint8_t length = 2;
    _wire->requestFrom(_address, length);
    uint16_t tmp = _wire->read() << 8;
    tmp |= _wire->read();
    C[i] *= tmp;
  }
}


uint32_t MS5837::readADC()
{
  command(MS5837_CMD_READ_ADC);
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


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//

//////////////////////////////////////////////////////////////////////
//
//  MS5803
//
MS5803::MS5803(TwoWire *wire):MS5837(wire)
{
}

MS5803::MS5803(uint32_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


//  -- END OF FILE --

