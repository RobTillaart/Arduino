//
//    FILE: SD2405.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for I2C SD2405 RTC and compatibles.
// VERSION: 0.2.0
//    DATE: 2022-03-17
//     URL: https://github.com/RobTillaart/SD2405


#include "SD2405.h"


/////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
SD2405::SD2405(TwoWire *wire) : _wire { wire }
{
}


int SD2405::begin()
{
  if (! isConnected() ) return SD2405_ERROR_CONNECT;
  return SD2405_OK;
}


bool SD2405::isConnected()
{
  _wire->beginTransmission(_address);
  _rv = _wire->endTransmission();
  return (_rv == 0);
}


uint8_t SD2405::getAddress()
{
  return _address;
}


/////////////////////////////////////////////////////////
//
//  CORE
//
int SD2405::read()
{
  _wire->beginTransmission(_address);
  _wire->write(SD2405_TIME_BASE);
  _rv = _wire->endTransmission();
  if (_rv != 0) return SD2405_ERROR_I2C;

  if (_wire->requestFrom(_address, (uint8_t)7) != 7)
  {
    return SD2405_ERROR_I2C;
  }
  for (int i = 0; i < 2; i++)
  {
    _reg[i] = bcd2dec(_wire->read());
  }
  _reg[2] = bcd2dec(_wire->read() & 0x3F);  //  use 24 hour format
  for (int i = 3; i < 7; i++)
  {
    _reg[i] = bcd2dec(_wire->read());
  }
  _lastRead = millis();

  return SD2405_OK;
}


int SD2405::write()
{
  _wire->beginTransmission(_address);
  _wire->write(SD2405_TIME_BASE);
  for (int i = 0; i < 2; i++)
  {
    _wire->write(dec2bcd(_reg[i]));
  }
  _wire->write(dec2bcd(_reg[2]) | 0x80);  //  use 24 hour format
  for (int i = 3; i < 7; i++)
  {
    _wire->write(dec2bcd(_reg[i]));
  }
  _rv = _wire->endTransmission();
  if (_rv != 0) return SD2405_ERROR_I2C;
  return SD2405_OK;
}


uint32_t SD2405::lastRead()
{
  return _lastRead;
}


/////////////////////////////////////////////////////////
//
//  GETTERS
//
uint8_t SD2405::seconds() { return _reg[0]; }
uint8_t SD2405::minutes() { return _reg[1]; }
uint8_t SD2405::hours()   { return _reg[2]; }
uint8_t SD2405::weekDay() { return _reg[3]; }
uint8_t SD2405::day()     { return _reg[4]; }
uint8_t SD2405::month()   { return _reg[5]; }
uint8_t SD2405::year()    { return _reg[6]; }


/////////////////////////////////////////////////////////
//
//  SETTERS
//
void SD2405::setSeconds(uint8_t value) { _reg[0] = value; }
void SD2405::setMinutes(uint8_t value) { _reg[1] = value; }
void SD2405::setHours(uint8_t value)   { _reg[2] = value; }
void SD2405::setWeekDay(uint8_t value) { _reg[3] = value; }
void SD2405::setDay(uint8_t value)     { _reg[4] = value; }
void SD2405::setMonth(uint8_t value)   { _reg[5] = value; }
void SD2405::setYear(uint8_t value)    { _reg[6] = value; }


////////////////////////////////////////////////////////////////////
//
//  CONFIGURE INTERRUPT FUNCTIONS
//

//  par 5.3, register 0x10, INTS0, INTS1, INTDE, INTAE, INTFE, IM
//  source: 0 = disable,
//          1 = alarm,
//          2 = frequency,
//          3 = timer
//  repeat: single = false,
//          repeat = true until INTAF is reset
//  autoReset: ARST = 0 = false,
//             ARST = 1 = true.
int SD2405::configureInterrupt(uint8_t source, bool repeat, bool autoReset)
{
  const uint8_t IM    = 0x40;
  const uint8_t INTS1 = 0x20;
  const uint8_t INTS0 = 0x10;
  const uint8_t INTDE = 0x04;
  const uint8_t INTAE = 0x02;
  const uint8_t INTFE = 0x01;
  const uint8_t ALL   = IM | INTS0 | INTS1 | INTDE | INTAE | INTFE;  //  0x77

  uint8_t mask = readRegister(SD2405_CONTROL_2);
  uint8_t premask = mask;
  mask &= ~ALL;  //  clear IM, INTS0, INTS1, INTDE, INTAE, INTFE.
  switch (source)
  {
    case 1:
      mask |= (INTS0 | INTAE);
      break;
    case 2:
      mask |= (INTS1 | INTFE);
      break;
    case 3:
      mask |= (INTS0 | INTS1 | INTDE);
      break;
    default:  //  disable, no bits set.
      break;
  }
  if (repeat)
  {
    mask |= IM;
  }
  if (mask != premask)
  {
    writeRegister(SD2405_CONTROL_2, mask);
  }

  //  AUTORESET
  const uint8_t ARST = 0x80;
  mask = readRegister(SD2405_CONTROL_3);
  premask = mask;
  mask &= ~ARST;
  if (autoReset)
  {
    mask |= ARST;
  }
  if (mask != premask)
  {
    return writeRegister(SD2405_CONTROL_3, mask);
  }
  return SD2405_OK;
}


////////////////////////////////////////////////////////////////////
//
//  FREQUENCY INTERRUPT FUNCTIONS
//
//  par 5.3. register 0x11, FS0..FS3
//  bit_mask = 0..15
int SD2405::setFrequencyMask(uint8_t bit_mask)
{
  const uint8_t FSBITS = 0x0F;
  uint8_t mask = readRegister(SD2405_CONTROL_3);
  uint8_t premask = mask;
  mask &= ~FSBITS;   //  clear FS0..FS3 bits
  mask |= bit_mask;
  if (mask != premask)
  {
    return writeRegister(SD2405_CONTROL_3, mask);
  }
  return SD2405_OK;
}


////////////////////////////////////////////////////////////////////
//
//  COUNTDOWN INTERRUPT FUNCTIONS
//
//  par 5.3. register 0x11, FS0..FS3
//  bit_mask =>  RANGE
//      0        1/4096 - 255/4096  => 1/100 ~~ 41/4096
//      1        1 - 255 seconds
//      2        1/64 .. 255/64 seconds
//      3        1 - 255 minutes
int SD2405::setCountDownMask(uint8_t bit_mask)
{
  const uint8_t TDSBITS = 0x30;
  uint8_t mask = readRegister(SD2405_CONTROL_3);
  uint8_t premask = mask;
  mask &= ~TDSBITS;   //  clear TDS0, TDS1 bits
  mask |= (bit_mask << 4);
  if (mask != premask)
  {
    return writeRegister(SD2405_CONTROL_3, mask);
  }
  return SD2405_OK;
}


////////////////////////////////////////////////////////////////////
//
//  TIME TRIMMING FUNCTIONS
//
//  par 5.4. register 0x12, 0..127
//  read the data sheet (twice)
//  oscillator = actual frequency (ist)
//  target     = target frequency (soll)
int SD2405::adjustClockFrequency(int32_t oscillator, int32_t target)
{
  int amount = 0;
  if (oscillator > target)
  {
    amount = (oscillator - target) * 10 + 1;
  }
  else if (oscillator < target)
  {
    amount = 0x80 - (target - oscillator) * 10;
  }
  return writeRegister(SD2405_TIME_TRIMMING, amount);
}


////////////////////////////////////////////////////////////////////
//
//  OTHER FUNCTIONS
//
//  par 5.5. register
//  read the data sheet (twice)
int SD2405::enableWriteRTC()
{
  const uint8_t WRTC1 = 0x80;
  const uint8_t WRTC2 = 0x04;
  const uint8_t WRTC3 = 0x80;

  uint8_t mask = readRegister(SD2405_CONTROL_2);
  mask |= WRTC1;
  writeRegister(SD2405_CONTROL_2, mask);

  mask = readRegister(SD2405_CONTROL_1);
  mask |= (WRTC2 | WRTC3);
  return writeRegister(SD2405_CONTROL_1, mask);
}


int SD2405::disableWriteRTC()
{
  const uint8_t WRTC1 = 0x80;
  const uint8_t WRTC2 = 0x04;
  const uint8_t WRTC3 = 0x80;

  uint8_t mask = readRegister(SD2405_CONTROL_1);
  mask &= ~(WRTC3 | WRTC2);
  writeRegister(SD2405_CONTROL_1, mask);
  mask = readRegister(SD2405_CONTROL_2);
  mask &= ~WRTC1;
  return writeRegister(SD2405_CONTROL_2, mask);
}


int SD2405::setFOBAT(bool flag)
{
  const uint8_t FOBAT = 0x08;
  uint8_t mask = readRegister(SD2405_CONTROL_2);
  uint8_t premask = mask;
  mask &= ~FOBAT;
  if (flag)
  {
    mask |= FOBAT;
  }
  if (mask != premask)
  {
    return writeRegister(SD2405_CONTROL_2, mask);
  }
  return SD2405_OK;
}


bool SD2405::getRCTF()
{
  const uint8_t RCTF = 0x01;
  uint8_t mask = readRegister(SD2405_CONTROL_1);
  return (mask & RCTF) > 0 ;
}


/////////////////////////////////////////////////////////
//
//  SRAM SUPPORT
//
//  SRAM 12 bytes, register 0x14-0x1F
//  index = 0x00..0x0B == 0..11
//  note: no boundary check
int SD2405::SRAMwrite8(uint8_t index, uint8_t value)
{
  uint8_t position = SD2405_SRAM_BASE + index;
  return writeRegister(position, value);
}

int SD2405::SRAMwrite16(uint8_t index, uint16_t value)
{
  uint8_t position = SD2405_SRAM_BASE + index;
  writeRegister(position, value >> 8);
  return writeRegister(position + 1, value & 0xFF);
}

int SD2405::SRAMwrite32(uint8_t index, uint32_t value)
{
  uint32_t val = value;
  uint8_t position = SD2405_SRAM_BASE + index;
  for (int i = 0; i < 4; i++)
  {
    writeRegister(position + i, val & 0xFF);
    val >>= 8;
  }
  return SD2405_OK;
}

uint8_t SD2405::SRAMread8(uint8_t index)
{
  uint8_t position = SD2405_SRAM_BASE + index;
  return readRegister(position);
}

uint16_t SD2405::SRAMread16(uint8_t index)
{
  uint8_t position = SD2405_SRAM_BASE + index;
  uint16_t val = readRegister(position);
  val <<= 8;
  val += readRegister(position + 1);
  return val;
}

uint32_t SD2405::SRAMread32(uint8_t index)
{
  uint32_t val = 0;
  uint8_t position = SD2405_SRAM_BASE + index;
  for (int i = 3; i >= 0; i--)
  {
    val <<= 8;
    val += readRegister(position + i);
  }
  return val;
}




/////////////////////////////////////////////////////////
//
//  LOW LEVEL
//
int SD2405::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _rv = _wire->endTransmission(false);
  if (_rv != 0) return SD2405_ERROR_I2C;

  if (_wire->requestFrom(_address, (uint8_t)1) != 1)
  {
    return SD2405_ERROR_I2C;
  }
  return _wire->read();
}


int SD2405::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _rv = _wire->endTransmission();
  if (_rv != 0) return SD2405_ERROR_I2C;
  return SD2405_OK;
}


/////////////////////////////////////////////////////////
//
//  PROTECTED
//
//  see fast_math library for optimisation of dec2bcd and bcd2dec
uint8_t SD2405::dec2bcd(uint8_t value)
{
  return value + 6 * (value / 10);
}


uint8_t SD2405::bcd2dec(uint8_t value)
{
  return value - 6 * (value >> 4);
}


//  -- END OF FILE --

