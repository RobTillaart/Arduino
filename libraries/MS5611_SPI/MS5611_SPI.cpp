//
//    FILE: MS5611_SPI.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: MS5611 (SPI) Temperature & Pressure library for Arduino
//     URL: https://github.com/RobTillaart/MS5611_SPI
//
//  HISTORY: see changelog.md


#include "MS5611_SPI.h"


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
MS5611_SPI::MS5611_SPI(uint8_t select, __SPI_CLASS__ * mySPI)
{
  //  _address           = deviceAddress;  // TODO
  _samplingRate      = OSR_ULTRA_LOW;
  _temperature       = MS5611_NOT_READ;
  _pressure          = MS5611_NOT_READ;
  _result            = MS5611_NOT_READ;
  _lastRead          = 0;
  _deviceID          = 0;
  _pressureOffset    = 0;
  _temperatureOffset = 0;
  _compensation      = true;

  //  SPI
  _select   = select;
  _dataIn   = 255;
  _dataOut  = 255;
  _clock    = 255;
  _hwSPI    = true;
  _mySPI    = mySPI;
}


MS5611_SPI::MS5611_SPI(uint8_t select, uint8_t dataOut, uint8_t dataIn, uint8_t clock)
{
  //  _address           = deviceAddress;  // TODO
  _samplingRate      = OSR_ULTRA_LOW;
  _temperature       = MS5611_NOT_READ;
  _pressure          = MS5611_NOT_READ;
  _result            = MS5611_NOT_READ;
  _lastRead          = 0;
  _deviceID          = 0;
  _pressureOffset    = 0;
  _temperatureOffset = 0;
  _compensation      = false;

  //  SPI
  _select   = select;
  _dataIn   = dataIn;
  _dataOut  = dataOut;
  _clock    = clock;
  _hwSPI    = false;
  _mySPI    = NULL;
}


bool MS5611_SPI::begin()
{
  //  print experimental message.
  //  Serial.println(MS5611_SPI_LIB_VERSION);

  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  setSPIspeed(_SPIspeed);

  if(_hwSPI)
  {
    //  _mySPI->begin();  //  FIX #6  
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else
  {
    //  Serial.println("SW_SPI");
    pinMode(_dataIn,  INPUT);
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock,   OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock,   LOW);
  }

  return reset();
}


bool MS5611_SPI::isConnected()
{
  int rv = read();
  return (rv == MS5611_READ_OK);
}


bool MS5611_SPI::reset(uint8_t mathMode)
{
  command(MS5611_CMD_RESET);
  uint32_t start = micros();
  //  while loop prevents blocking RTOS
  while (micros() - start < 3000)     //  increased as first ROM values were missed.
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
    //  _deviceID is a simple SHIFT XOR merge of PROM data
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


int MS5611_SPI::read(uint8_t bits)
{
  //  VARIABLES NAMES BASED ON DATASHEET
  //  ALL MAGIC NUMBERS ARE FROM DATASHEET
  convert(MS5611_CMD_CONVERT_D1, bits);
  //  NOTE: D1 and D2 seem reserved in MBED (NANO BLE)
  uint32_t _D1 = readADC();
  convert(MS5611_CMD_CONVERT_D2, bits);
  uint32_t _D2 = readADC();

  //  Serial.println(_D1);
  //  Serial.println(_D2);

  //   TEST VALUES - comment lines above
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


void MS5611_SPI::setOversampling(osr_t samplingRate)
{
  _samplingRate = (uint8_t) samplingRate;
}


osr_t MS5611_SPI::getOversampling() const
{
  return (osr_t) _samplingRate;
}


float MS5611_SPI::getTemperature() const
{
  if (_temperatureOffset == 0) return _temperature * 0.01;
  return _temperature * 0.01 + _temperatureOffset;
}


float MS5611_SPI::getPressure() const
{
  if (_pressureOffset == 0) return _pressure * 0.01;
  return _pressure * 0.01 + _pressureOffset;
}


void MS5611_SPI::setPressureOffset(float offset)
{
  _pressureOffset = offset;
}


float MS5611_SPI::getPressureOffset()
{
  return _pressureOffset;
}


void MS5611_SPI::setTemperatureOffset(float offset)
{
  _temperatureOffset = offset;
}


float MS5611_SPI::getTemperatureOffset()
{
  return _temperatureOffset;
}


int MS5611_SPI::getLastResult() const
{
  return _result;
}


uint32_t MS5611_SPI::lastRead() const
{
  return _lastRead;
}


uint32_t MS5611_SPI::getDeviceID() const
{
  return _deviceID;
}


void MS5611_SPI::setCompensation(bool flag)
{
  _compensation = flag;
}


bool MS5611_SPI::getCompensation()
{
  return _compensation;
}


//       EXPERIMENTAL
uint16_t MS5611_SPI::getManufacturer()
{
  return readProm(0);
}

//       EXPERIMENTAL
uint16_t MS5611_SPI::getSerialCode()
{
  return readProm(7) >> 4;
}


void MS5611_SPI::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE0);
}


uint32_t MS5611_SPI::getSPIspeed()
{
  return _SPIspeed;
}


bool MS5611_SPI::usesHWSPI()
{
  return _hwSPI;
}



/////////////////////////////////////////////////////
//
//  PRIVATE
//
void MS5611_SPI::convert(const uint8_t addr, uint8_t bits)
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


uint16_t MS5611_SPI::readProm(uint8_t reg)
{
  //  last EEPROM register is CRC - Page 13 datasheet.
  uint8_t promCRCRegister = 7;
  if (reg > promCRCRegister) return 0;

  uint16_t value = 0;
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(MS5611_CMD_READ_PROM + reg * 2);
    value += _mySPI->transfer(0x00);
    value <<= 8;
    value += _mySPI->transfer(0x00);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    swSPI_transfer(MS5611_CMD_READ_PROM + reg * 2);
    value += swSPI_transfer(0x00);
    value <<= 8;
    value += swSPI_transfer(0x00);
  }
  digitalWrite(_select, HIGH);
  return value;
}


uint32_t MS5611_SPI::readADC()
{
  //  command(MS5611_CMD_READ_ADC);

  uint32_t value = 0;

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(0x00);
    value += _mySPI->transfer(0x00);
    value <<= 8;
    value += _mySPI->transfer(0x00);
    value <<= 8;
    value += _mySPI->transfer(0x00);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    swSPI_transfer(0x00);
    value += swSPI_transfer(0x00);
    value <<= 8;
    value += swSPI_transfer(0x00);
    value <<= 8;
    value += swSPI_transfer(0x00);
  }
  digitalWrite(_select, HIGH);
  //  Serial.println(value, HEX);
  return value;
}


int MS5611_SPI::command(const uint8_t command)
{
  yield();
  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(command);
    _mySPI->endTransaction();
  }
  else      //  Software SPI
  {
    swSPI_transfer(command);
  }
  digitalWrite(_select, HIGH);
  return 0;
}


//  simple one mode version
uint8_t MS5611_SPI::swSPI_transfer(uint8_t val)
{
  uint8_t clk = _clock;
  uint8_t dao = _dataOut;
  uint8_t dai = _dataIn;
  uint8_t value = 0;
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao,(val & mask));
    digitalWrite(clk, HIGH);
    value <<= 1;
    if (digitalRead(dai) != 0) value += 1;
    digitalWrite(clk, LOW);
  }
  digitalWrite(dao, LOW);
  //  Serial.print(" # ");
  //  Serial.println(value, HEX);
  return value;
}


void MS5611_SPI::initConstants(uint8_t mathMode)
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

  if (mathMode == 1)      //  Appnote version for pressure.
  {
    C[1] = 65536L;        //  SENSt1
    C[2] = 131072L;       //  OFFt1
    C[3] = 7.8125E-3;     //  TCS
    C[4] = 1.5625e-2;     //  TCO
  }
}


//  -- END OF FILE --

