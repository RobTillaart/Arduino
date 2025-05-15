//
//    FILE: AD5593R.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-01-30
// PURPOSE: Arduino library for AD5593R, I2C, 8 channel ADC / DAC / GPIO device.
//     URL: https://github.com/RobTillaart/AD5593R


#include "AD5593R.h"


//  CONFIG REGISTERS (aka pointer bytes)
#define AD5593_NOP                      0x00
#define AD5593_ADC_SEQ                  0x02
#define AD5593_GEN_CTRL_REG             0x03
#define AD5593_ADC_CONFIG               0x04
#define AD5593_DAC_CONFIG               0x05
#define AD5593_PULLDOWN_CONFIG          0x06
#define AD5593_LDAC_MODE                0x07
#define AD5593_GPIO_CONFIG              0x08
#define AD5593_GPIO_OUTPUT              0x09
#define AD5593_GPIO_INPUT               0x0A
#define AD5593_POWERDOWN_REF_CTRL       0x0B
#define AD5593_GPIO_OPENDRAIN_CONFIG    0x0C
#define AD5593_IO_TS_CONFIG             0x0D

#define AD5593_SW_RESET                 0x0F


//  IO REGISTERS
#define AD5593_DAC_WRITE(x)             (0x10 + (x))
#define AD5593_ADC_READ                 0x40
#define AD5593_DAC_READ(x)              (0x50 + (x))
#define AD5593_GPIO_READ                0x60
#define AD5593_GPIO_READ_CONFIG         0x70



AD5593R::AD5593R(const uint8_t deviceAddress, TwoWire *wire)
{
  _address = deviceAddress;
  _wire    = wire;
  _error   = AD5593R_OK;
  _Vref    = 2.5;
  _gain    = 1;
}

bool AD5593R::begin()
{
  if (! isConnected()) return false;
  return true;
}

bool AD5593R::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}

uint8_t AD5593R::getAddress()
{
  return _address;
}


////////////////////////////////////////////////////////////
//
//  CONFIGURE ADC / DAC RANGE
//
int AD5593R::setADCRange2x(bool flag)
{
  //  remember for readTemperature().
  if (flag) _gain = 2;
  else      _gain = 1;

  uint16_t bitMask = readConfigRegister(AD5593_GEN_CTRL_REG);
  if (flag) bitMask |= 0x0020;
  else bitMask &= ~0x0020;
  return writeRegister(AD5593_GEN_CTRL_REG, bitMask);
}

int AD5593R::setDACRange2x(bool flag)
{
  uint16_t bitMask = readConfigRegister(AD5593_GEN_CTRL_REG);
  if (flag) bitMask |= 0x0010;
  else bitMask &= ~0x0010;
  return writeRegister(AD5593_GEN_CTRL_REG, bitMask);
}


////////////////////////////////////////////////////////////
//
//  CONFIGURE GENERAL CONTROL
//
int AD5593R::enableADCBufferPreCharge(bool flag)
{
  uint16_t bitMask = readConfigRegister(AD5593_GEN_CTRL_REG);
  if (flag) bitMask |= 0x0200;
  else bitMask &= ~0x0200;
  return writeRegister(AD5593_GEN_CTRL_REG, bitMask);
}

int AD5593R::enableADCBuffer(bool flag)
{
  uint16_t bitMask = readConfigRegister(AD5593_GEN_CTRL_REG);
  if (flag) bitMask |= 0x0100;
  else bitMask &= ~0x0100;
  return writeRegister(AD5593_GEN_CTRL_REG, bitMask);
}

int AD5593R::enableIOLock(bool flag)
{
  uint16_t bitMask = readConfigRegister(AD5593_GEN_CTRL_REG);
  if (flag) bitMask |= 0x0080;
  else bitMask &= ~0x0080;
  return writeRegister(AD5593_GEN_CTRL_REG, bitMask);
}

int AD5593R::writeAllDacs(bool flag)
{
  uint16_t bitMask = readConfigRegister(AD5593_GEN_CTRL_REG);
  if (flag) bitMask |= 0x0040;
  else bitMask &= ~0x0040;
  return writeRegister(AD5593_GEN_CTRL_REG, bitMask);
}


////////////////////////////////////////////////////////////
//
//  MODE
//
int AD5593R::setMode(const char config[9])
{
  //  all channels need to be addressed
  if (strlen(config) != 8) return -1;
  uint8_t bitMaskDAC = 0x00;
  uint8_t bitMaskADC = 0x00;
  uint8_t bitMaskIn  = 0x00;
  uint8_t bitMaskOut = 0x00;
  uint8_t bitMaskTS  = 0x00;

  //  parse configuration string.
  uint8_t bm = 0x01;
  for (int i = 0; i < 8; i++)
  {
    switch(config[i])
    {
      //  ADC
      case 'a':
      case 'A': bitMaskADC |= bm; break;
      //  DAC
      case 'd':
      case 'D': bitMaskDAC |= bm; break;
      //  INPUT
      case 'i':
      case 'I': bitMaskIn  |= bm; break;
      //  THREE STATE ==> output mode
      case 't':
      case 'T': bitMaskTS  |= bm; bitMaskOut |= bm; break;
      //  OUTPUT
      case 'o':
      case 'O': bitMaskOut |= bm; break;
      default:  break;
    }
    bm <<= 1;
  }
  //  TODO handle return values.
  setADCmode(bitMaskADC);
  setDACmode(bitMaskDAC);
  setINPUTmode(bitMaskIn);
  setOUTPUTmode(bitMaskOut);
  setTHREESTATEmode(bitMaskTS);
  return 0;
}

int AD5593R::setADCmode(uint8_t bitMask)
{
  //  Page 25 / 32
  //  1's => ADC
  return writeRegister(AD5593_ADC_CONFIG, bitMask);
}

int AD5593R::setDACmode(uint8_t bitMask)
{
  //  Page 35
  //  1's => DAC
  return writeRegister(AD5593_DAC_CONFIG, bitMask);
}

int AD5593R::setINPUTmode(uint8_t bitMask)
{
  //  Page 26
  //  1's => INPUT
  return writeRegister(AD5593_GPIO_INPUT, bitMask);
}

int AD5593R::setOUTPUTmode(uint8_t bitMask)
{
  //  Page 26
  //  1's => OUTPUT
  return writeRegister(AD5593_GPIO_CONFIG, bitMask);
}

int AD5593R::setTHREESTATEmode(uint8_t bitMask)
{
  //  Page 26/43
  //  1's => Three state OUTPUT
  return writeRegister(AD5593_IO_TS_CONFIG, bitMask);
}

int AD5593R::setPULLDOWNmode(uint8_t bitMask)
{
  //  page 26/36
  return writeRegister(AD5593_PULLDOWN_CONFIG, bitMask);
}

int AD5593R::setLDACmode(uint8_t mode)
{
  //  page 24
  if (mode > AD5593R_LDAC_RELEASE)
  {
    return AD5593R_LDAC_ERROR;
  }
  return writeRegister(AD5593_LDAC_MODE, mode);
}

int AD5593R::setOpenDrainMode(uint8_t bitMask)
{
  //  Page 26 - output mode
  return writeRegister(AD5593_GPIO_OPENDRAIN_CONFIG, bitMask);
}



////////////////////////////////////////////////////////////
//
//  DIGITAL
//
//  Page 26
uint16_t AD5593R::write1(uint8_t pin, uint8_t value)
{
  if (pin > 7) return AD5593R_PIN_ERROR;
  uint16_t bitMask = readConfigRegister(AD5593_GPIO_OUTPUT);
  if (value == LOW) bitMask &= ~(1 << pin);
  else              bitMask |= (1 << pin);
  return writeRegister(AD5593_GPIO_OUTPUT, bitMask);
}

uint16_t AD5593R::read1(uint8_t pin)
{
  if (pin > 7) return AD5593R_PIN_ERROR;
  uint16_t bitMask = readIORegister(AD5593_GPIO_READ);
  return (bitMask >> pin) & 0x01;
}

uint16_t AD5593R::write8(uint8_t bitMask)
{
  return writeRegister(AD5593_GPIO_OUTPUT, bitMask);
}

uint16_t AD5593R::read8()
{
  return readIORegister(AD5593_GPIO_READ) & 0xFF;
}


////////////////////////////////////////////////////////////
//
//  ANALOG
//
uint16_t AD5593R::writeDAC(uint8_t pin, uint16_t value)
{
  if (pin > 7) return AD5593R_PIN_ERROR;
  //  max 12 bit == 4095 => clipping
  if (value > 0x0FFF)
  {
    value = 0x0FFF;
  }
  return writeRegister(AD5593_DAC_WRITE(pin), value);
}

uint16_t AD5593R::readDAC(uint8_t pin)
{
  if (pin > 7) return AD5593R_PIN_ERROR;
  uint16_t raw = readIORegister(AD5593_DAC_READ(pin));
  //  if ((raw >> 12) != pin) error.
  //  remove four upper bits, contain the pin
  raw &= 0x0FFF;
  return raw;
}

uint16_t AD5593R::readADC(uint8_t pin)
{
  //  allow pin 8 for raw temperature
  if (pin > 8) return AD5593R_PIN_ERROR;
  //  add all to the sequence including temperature.
  //  0x0200 = REPeat bit
  //  0x0100 = TEMPerature include bit
  uint16_t pinmask = 1 << pin;
  writeRegister(AD5593_ADC_SEQ, 0x0200 | pinmask);
  //  read one ADC conversion.
  uint16_t raw = readIORegister(AD5593_ADC_READ);
  //  if ((raw >> 12) != pin) error.
  //  remove four upper bits, contain the pin
  raw &= 0x0FFF;
  return raw;
}

//  note: identical to readADC(8)
float AD5593R::readTemperature()
{
  //  page 19.
  //  0x0200 = REPeat bit
  //  0x0100 = TEMPerature include bit
  writeRegister(AD5593_ADC_SEQ, 0x0200 | 0x0100);
  //  read one ADC conversion.
  uint16_t raw = readIORegister(AD5593_ADC_READ);
  //  if not temperature ADC
  if ((raw & 0xF000) != 0x8000)
  {
    return -273.15;  //  0 Kelvin.
  }
  //  remove four upper bits, contain the pin
  raw &= 0x0FFF;
  //  formulas page 19 refactored to minimize float math.
  //  verified with datasheet indicative numbers.
  //  RAW     CELSIUS   FAHRENHEIT
  //  645  => -40       -40
  //  1035 => +105      +221
  //  1084 => +125      +257
  return -283.59 + raw / 6.635 * _gain * _Vref;

  //  formulas page 19 refactored into one
  //  float gainVref = _gain * _Vref;
  //  float temp = raw - (0.5 * 4095) / gainVref;
  //  temp = temp / (2.654 * (2.5 / gainVref));
  //  return temp + 25.0;
  //
  //  return -283.59 + raw / 6.635 * _gain * _Vref;
  //
  //  float division can be optimized away.
  //  float tmp = -283.59 + raw * 0.1507159 * _Vref;
  //  if (_gain == 2) tmp *= 2;
  //  return tmp;
}


////////////////////////////////////////////////////////////
//
//  V-REFERENCE
//
int AD5593R::setExternalReference(bool flag, float Vref)
{
  //  Page 40
  uint16_t bitMask = readConfigRegister(AD5593_POWERDOWN_REF_CTRL);
  if (flag)  //  external
  {
    bitMask &= ~0x0200;
    _Vref = Vref;
  }
  else       //  internal
  {
    bitMask |= 0x0200;
    _Vref = 2.5;
  }
  return writeRegister(AD5593_POWERDOWN_REF_CTRL, bitMask);
}

int AD5593R::powerDown()
{
  //  Page 40
  uint16_t bitMask = readConfigRegister(AD5593_POWERDOWN_REF_CTRL);
  bitMask |= 0x0400;
  return writeRegister(AD5593_POWERDOWN_REF_CTRL, bitMask);
}

int AD5593R::wakeUp()
{
  _Vref = 2.5;
  //  Page 40
  uint16_t bitMask = readConfigRegister(AD5593_POWERDOWN_REF_CTRL);
  bitMask &= ~0x0400;
  return writeRegister(AD5593_POWERDOWN_REF_CTRL, bitMask);
}

int AD5593R::powerDownDac(uint8_t pin)
{
  //  Page 40
  if (pin > 7) return 0;
  uint16_t bitMask = readConfigRegister(AD5593_POWERDOWN_REF_CTRL);
  bitMask |= (1 << pin);
  return writeRegister(AD5593_POWERDOWN_REF_CTRL, bitMask);
}

int AD5593R::wakeUpDac(uint8_t pin)
{
  //  Page 40
  if (pin > 7) return 0;
  uint16_t bitMask = readConfigRegister(AD5593_POWERDOWN_REF_CTRL);
  bitMask &= ~(1 << pin);
  return writeRegister(AD5593_POWERDOWN_REF_CTRL, bitMask);
}


////////////////////////////////////////////////////////////
//
//  RESET
//
int AD5593R::reset()
{
  //  page 19
  return writeRegister(AD5593_SW_RESET, 0x0DAC);
  _Vref = 2.5;
  _gain = 1;
}


////////////////////////////////////////////////////////////
//
//  PROTECTED
//
//  Figure 36, page 20
int AD5593R::writeRegister(uint8_t reg, uint16_t data)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(data >> 8);
  _wire->write(data & 0xFF);
  _error = _wire->endTransmission();
  return _error;
}


uint16_t AD5593R::readIORegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_wire->requestFrom(_address, (uint8_t)2, (uint8_t)1) != 2)
  {
    _error = AD5593R_I2C_ERROR;
    return 0;
  }
  uint16_t data = _wire->read() << 8;
  data += _wire->read();
  return data;
}


uint16_t AD5593R::readConfigRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(AD5593_GPIO_READ_CONFIG | reg);
  _error = _wire->endTransmission();
  if (_wire->requestFrom(_address, (uint8_t)2, (uint8_t)1) != 2)
  {
    _error = AD5593R_I2C_ERROR;
    return 0;
  }
  uint16_t data = _wire->read() << 8;
  data += _wire->read();
  return data;
}


//  -- END OF FILE --

