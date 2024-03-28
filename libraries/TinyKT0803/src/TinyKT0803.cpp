//
//    FILE: TinyKT0803.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino Library for KT0803 and KT0803K FM transmitter. Tiny edition.
//     URL: https://github.com/RobTillaart/TinyKT0803
//     URL: https://github.com/RobTillaart/KT0803


#include "TinyKT0803.h"


//  REGISTERS on page 7 datasheet


TinyKT0803::TinyKT0803()
{
  _address  = 0x3E;
}


bool TinyKT0803::begin(float freq, bool mute)
{
  if (! isConnected()) return false;
  if (! setMute(mute)) return false;
  return setFrequency(freq);
}


bool TinyKT0803::isConnected()
{
  TinyWireM.beginTransmission(_address);
  return (TinyWireM.endTransmission() == 0);
}


///////////////////////////////////////////////////////////
//
//  FREQUENCY
//
bool TinyKT0803::setFrequency(float MHz)
{
  if ((MHz < 70) || (MHz > 108)) return false;
  //  steps 50 KHz although KT0803 will truncate to 100 KHz.
  return setChannel(round(MHz * 20));
}


//  MHz
float TinyKT0803::getFrequency()
{
  return getChannel() * 0.05;
}


//  steps of 50 KHz.
bool TinyKT0803::setChannel(uint16_t channel)
{
  if ((channel < 1400) || (channel > 2160)) return false;
  //  need to split over 3 registers
  //  register 2 part skipped (always 0) for KT0803
  uint16_t ch = channel >> 1;

  uint8_t register0 = ch & 0xFF;  //  CHSEL[8:1]
  if (writeData(0x00, register0) == false) return false;

  ch >>= 8;
  uint8_t register1 = readData(0x01);
  register1 &= 0xF8;         //  CHSEL[11:9]
  register1 |= (ch & 0x07);  //  CHSEL[11:9]
  return writeData(0x01, register1);
}


uint16_t TinyKT0803::getChannel()
{
  uint16_t channel = readData(0x01) & 0x07;
  channel <<= 8;
  channel |= readData(0x00);
  channel <<= 1;
  return channel;
}


///////////////////////////////////////////////////////////
//
//  GAIN
//
bool TinyKT0803::setPGA(uint8_t pga)
{
  if (pga > 7) return false;
  uint8_t data = readData(0x01);
  data &= 0xC7;   //  keep other bits
  data |= (pga << 3);
  return writeData(0x01, data);
}


uint8_t TinyKT0803::getPGA()
{
  return (readData(0x01) >> 3) & 0x07;
}


bool TinyKT0803::setRFGain(uint8_t rfgain)
{
  if (rfgain > 15) return false;
  //  bits 0 and 1
  uint8_t data = readData(0x01) & 0x3F;
  data |= (rfgain & 0x03) << 6;
  writeData(0x01, data);
  // bit 2
  data = readData(0x13) & 0x7F;
  data |= (rfgain & 0x04) << 5;
  writeData(0x13, data);
  // bit 3
  data = readData(0x02) & 0xBF;
  data |= (rfgain & 0x08) << 3;
  writeData(0x02, data);
  return true;
}


uint8_t TinyKT0803::getRFgain()
{
  uint8_t data = readData(0x01) >> 6;      //  bit 0, 1
  data |= ((readData(0x13) & 0x80) >> 5);  //  bit 2
  data |= ((readData(0x02) & 0x40) >> 3);  //  bit 3
  return data;
}


bool TinyKT0803::setPHTCNST(bool on)
{
  uint8_t data = readData(0x02);
  //  is the bit already OK
  if ((on == true)  && (data & 0x01) == 0x01) return true;
  if ((on == false) && (data & 0x01) == 0x00) return true;
  //  otherwise flip the bit
  data = data ^ 0x01;
  return writeData(0x02, data);
}


///////////////////////////////////////////////////////////
//
//  MISC
//
bool TinyKT0803::getPHTCNST()
{
  return (readData(0x02) & 0x01) > 0;
}


bool TinyKT0803::setPilotToneAdjust(uint8_t mode)
{
  if (mode > 1) return false;
  uint8_t data = readData(0x02);
  //  is the bit already OK
  if ((mode == 1) && (data & 0x04) == 0x04) return true;
  if ((mode == 0) && (data & 0x04) == 0x00) return true;
  //  otherwise flip the bit
  data = data ^ 0x04;
  return writeData(0x02, data);
}


uint8_t TinyKT0803::getPilotToneAdjust()
{
  return (readData(0x02) & 0x04) > 0;
}


///////////////////////////////////////////////////////////
//
//  MUTE
//
bool TinyKT0803::setMute(bool mute)
{
  uint8_t data = readData(0x02);
  //  is the bit already OK
  if ((mute == true)  && (data & 0x08) == 0x08) return true;
  if ((mute == false) && (data & 0x08) == 0x00) return true;
  //  otherwise flip the bit
  data = data ^ 0x08;
  return writeData(0x02, data);
}


bool TinyKT0803::getMute()
{
  return (readData(0x02) & 0x08) > 0;
}


///////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
bool TinyKT0803::writeData(uint8_t reg, uint8_t data)
{
  TinyWireM.beginTransmission(_address);
  TinyWireM.write(reg);
  TinyWireM.write(data);
  return (TinyWireM.endTransmission() == 0);
}


int TinyKT0803::readData(uint8_t reg)
{
  TinyWireM.beginTransmission(_address);
  TinyWireM.write(reg);
  TinyWireM.endTransmission(false);  //  explicit no STOP  fig 3 page 4

  //  Behaviour differs from TwoWire class
  //  returns 0 if OK, not the bytes available.
  int rv = TinyWireM.requestFrom(_address, (uint8_t) 1);
  if (rv == 0)
  {
    uint8_t data = TinyWireM.read();
    return data;
  }
  return rv;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
TinyKT0803K::TinyKT0803K() : TinyKT0803()
{
}


bool TinyKT0803K::setChannel(uint16_t channel)
{
  if ((channel < 1400) || (channel > 2160)) return false;
  //  need to split over 3 registers
  uint16_t ch = channel;

  uint8_t register2 = readData(0x02) & 0x7F;
  register2 |= (channel & 0x01) << 7;   //  CHSEL[0]
  if (writeData(0x02, register2) == false) return false;
  ch >>= 1;

  uint8_t register0 = ch & 0xFF;  //  CHSEL[8:1]
  if (writeData(0x00, register0) == false) return false;

  ch >>= 8;
  uint8_t register1 = readData(0x01);
  register1 &= 0xF8;         //  CHSEL[11:9]
  register1 |= (ch & 0x07);  //  CHSEL[11:9]
  return writeData(0x01, register1);
}


uint16_t TinyKT0803K::getChannel()
{
  uint16_t channel = readData(0x01) & 0x07;
  channel <<= 8;
  channel |= readData(0x00);
  channel <<= 1;
  channel |= (readData(0x02) >> 7);
  return channel;
}


///////////////////////////////////////////////////////////
//
//  KT0803K SPECIFIC
//
bool TinyKT0803K::setMono()
{
  uint8_t register4 = readData(0x04);
  if (register4 & (1 << 6))
  {
    register4 &= ~(1 << 6);
    return writeData(0x04, register4);
  }
  return true;
}


bool TinyKT0803K::setStereo()
{
  uint8_t register4 = readData(0x04);
  if ((register4 & (1 << 6)) == 0)
  {
    register4 |= (1 << 6);
    return writeData(0x04, register4);
  }
  return true;
}

bool TinyKT0803K::isStereo()
{
  uint8_t register4 = readData(0x04);
  return (register4 & (1 << 6));
}


bool TinyKT0803K::setBass(uint8_t bass)  //  0..3 = 0, 5, 11, 17 dB
{
  if (bass > 3) return false;
  uint8_t register4 = readData(0x04);
  register4 &= ~0x03;  //  mask off bits
  register4 |= bass;
  return writeData(0x04, register4);
}


uint8_t TinyKT0803K::getBass()
{
  uint8_t register4 = readData(0x04);
  return register4 & 0x03;
}


bool TinyKT0803K::powerOK()
{
  uint8_t register0F = readData(0x0F);
  return (register0F & (1 << 4)) > 0;
}


bool TinyKT0803K::silenceDetected()
{
  uint8_t register0F = readData(0x0F);
  return (register0F & (1 << 2)) > 0;
}


//  -- END OF FILE --

