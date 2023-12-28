//
//    FILE: KT0803.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino Library for KT0803 FM transmitter
//     URL: https://github.com/RobTillaart/KT0803


#include "KT0803.h"


//  REGISTERS on page 7 datasheet


KT0803::KT0803(TwoWire * wire)  
{
  _address  = 0x3E;
  _wire = wire;
}


bool KT0803::begin()
{
  return isConnected();
}


bool KT0803::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


///////////////////////////////////////////////////////////


bool KT0803::setFrequency(float frequency)
{
  return setChannel(round(frequency * 20));
}


float KT0803::getFrequency()
{
  return getChannel() * 0.05;
}


bool KT0803::setChannel(uint16_t channel)
{
  if (writeData(0x00, channel & 0xFF) == false) return false;

  uint8_t data = readData(0x01);
  data &= 0xF8;   //  keep other bits
  data |= (channel >> 8) & 0x07;
  return writeData(0x01, data);

  //  Reg02  CHSEL[0] = 0 ==> 100 KHz accuracy.
  //  Reg02  CHSEL[0] = 1 ==> 50 KHz accuracy.   //   TODO KT0803K derived class
}


uint16_t KT0803::getChannel()
{
  uint16_t channel = readData(0x01) & 0x07;
  channel <<= 8;
  channel |= readData(0x00);
  return channel;
}


bool KT0803::setPGA(uint8_t pga)
{
  uint8_t data = readData(0x01);
  data &= 0xC7;   //  keep other bits
  data |= (pga << 3);
  return writeData(0x01, data);
}


uint8_t KT0803::getPGA()
{
  return (readData(0x01) >> 3) & 0x07;
}


bool KT0803::setRFGain(uint8_t rfgain)
{
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
  return true;  //  TODO add error handling.
}


uint8_t KT0803::getRFgain()
{
  uint8_t data = readData(0x01) >> 6;     //  bit 0, 1
  data |= ((readData(0x13) & 0x80) >> 5);  //  bit 2
  data |= ((readData(0x02) & 0x40) >> 3);  //  bit 3
  return data;
}


bool KT0803::setPHTCNST(bool on)
{
  uint8_t data = readData(0x02);
  //  is the bit already OK
  if ((on == true)  && (data & 0x01) == 0x01) return true;
  if ((on == false) && (data & 0x01) == 0x00) return true;
  //  otherwise flip the bit
  data = data ^ 0x01;
  return writeData(0x02, data);
}

bool KT0803::getPHTCNST()
{
  return (readData(0x02) & 0x01) > 0;
}


bool KT0803::setPilotToneAdjust(uint8_t mode)
{
  uint8_t data = readData(0x02);
  //  is the bit already OK
  if ((mode == 1) && (data & 0x04) == 0x04) return true;
  if ((mode == 0) && (data & 0x04) == 0x00) return true;
  //  otherwise flip the bit
  data = data ^ 0x04;
  return writeData(0x02, data);
}


uint8_t KT0803::getPilotToneAdjust()
{
  return (readData(0x02) & 0x04) > 0;
}


bool KT0803::setMute(bool mute)
{
  uint8_t data = readData(0x02);
  //  is the bit already OK
  if ((mute == true)  && (data & 0x08) == 0x08) return true;
  if ((mute == false) && (data & 0x08) == 0x00) return true;
  //  otherwise flip the bit
  data = data ^ 0x08;
  return writeData(0x02, data);
}


bool KT0803::getMute()
{
  return (readData(0x02) & 0x08) > 0;
}




///////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
bool KT0803::writeData(uint8_t reg, uint8_t data)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(data);
  return (_wire->endTransmission() == 0);
}


int KT0803::readData(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->endTransmission();

  if (_wire->requestFrom(_address, (uint8_t) 1) == 1)
  {
    uint8_t data = _wire->read();
    return data;
  }
  return -1;
}


//  -- END OF FILE --

