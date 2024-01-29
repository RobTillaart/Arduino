//
//    FILE: AD5144A.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: I2C digital potentiometer AD5144A
//    DATE: 2021-04-30
//     URL: https://github.com/RobTillaart/AD5144A
//
//  Datasheet: REV-C  7/2019


#include "AD5144A.h"


//  Commands page 29 datasheet
//
//  not implemented (yet)
//  0      NOP
//  4 5    linear RDAC in/decrement
//  6 7    6dB RDAC in/decrement
//  12 13  top scale bottom scale ???


AD51XX::AD51XX(const uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


bool AD51XX::begin(bool doReset)
{
  if (! isConnected()) return false;
  if (doReset) reset();    //  See page 28 datasheet
  return true;
}


uint8_t AD51XX::getAddress()
{
  return _address;
}


bool AD51XX::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t AD51XX::reset()
{
  //  COMMAND 14 - page 29
  return send(0xB0, 0x00);   //  to be tested
  //  read the cache from EEPROM.
  for (uint8_t rdac = 0; rdac < _potCount; rdac++)
  {
    _lastValue[rdac] = readBackEEPROM(rdac);;
  }
}


/////////////////////////////////////////////////////////////////////////////
//
//  READ / WRITE
//
uint8_t AD51XX::read(const uint8_t rdac)
{
  return _lastValue[rdac];
};


uint8_t AD51XX::write(const uint8_t rdac, const uint8_t value)
{
  //  COMMAND 1 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  if (value > _maxValue) return AD51XXA_INVALID_VALUE;
  _lastValue[rdac] = value;
  uint8_t cmd = 0x10 | rdac;
  return send(cmd, _lastValue[rdac]);
}


uint8_t AD51XX::writeAll(const uint8_t value)
{
  if (value > _maxValue) return AD51XXA_INVALID_VALUE;
  //  COMMAND 1 - page 29
  for (uint8_t pm = 0; pm < _potCount; pm++)
  {
    _lastValue[pm] = value;
  }
  uint8_t cmd = 0x18;
  return send(cmd, value);
}


uint8_t AD51XX::zeroAll()
{
  return writeAll(0);
};


uint8_t AD51XX::midScaleAll()
{
  return writeAll((_maxValue + 1)/2);
};


uint8_t AD51XX::maxAll()
{
  return writeAll(_maxValue);
};


uint8_t AD51XX::zero(const uint8_t rdac)
{
  return write(rdac, 0);
};


uint8_t AD51XX::midScale(const uint8_t rdac)
{
  return write(rdac, (_maxValue + 1)/2);
};


uint8_t AD51XX::maxValue(const uint8_t rdac)
{
  return write(rdac, _maxValue);
};


/////////////////////////////////////////////////////////////////////////////
//
//  EEPROM
//
uint8_t AD51XX::storeEEPROM(const uint8_t rdac)
{
  //  COMMAND 9 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x70 | rdac;
  return send(cmd, 0x01);
}


uint8_t AD51XX::recallEEPROM(const uint8_t rdac)
{
  //  COMMAND 10 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  _lastValue[rdac] = readBackEEPROM(rdac);
  uint8_t cmd = 0x70 | rdac;
  return send(cmd, 0x00);
}


uint8_t AD51XX::storeEEPROM(const uint8_t rdac, const uint8_t value)
{
  //  COMMAND 11 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  if (value > _maxValue) return AD51XXA_INVALID_VALUE;
  uint8_t cmd = 0x80 | rdac;
  return send(cmd, value);
}


/////////////////////////////////////////////////////////////////////////////
//
//  SCALE
//
uint8_t AD51XX::setTopScale(const uint8_t rdac)
{
  //  COMMAND 12
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x90 | rdac;
  return send(cmd, 0x81);
}


uint8_t AD51XX::clrTopScale(const uint8_t rdac)
{
  //  COMMAND 12
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x90 | rdac;
  return send(cmd, 0x80);
}


uint8_t AD51XX::setTopScaleAll()
{
  //  COMMAND 12
  uint8_t cmd = 0x98;
  return send(cmd, 0x81);
}


uint8_t AD51XX::clrTopScaleAll()
{
  //  COMMAND 12
  uint8_t cmd = 0x98;
  return send(cmd, 0x80);
}


uint8_t AD51XX::setBottomScale(const uint8_t rdac)
{
  //  COMMAND 13
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x90 | rdac;
  return send(cmd, 0x01);
}


uint8_t AD51XX::clrBottomScale(const uint8_t rdac)
{
  // COMMAND 13
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x90 | rdac;
  return send(cmd, 0x00);
}


uint8_t AD51XX::setBottomScaleAll()
{
  //  COMMAND 13
  uint8_t cmd = 0x98;
  return send(cmd, 0x01);
}


uint8_t AD51XX::clrBottomScaleAll()
{
  //  COMMAND 13
  uint8_t cmd = 0x98;
  return send(cmd, 0x00);
}


/////////////////////////////////////////////////////////////////////////////
//
//  MODE
//
uint8_t AD51XX::setLinearMode(const uint8_t rdac)
{
  //  COMMAND 3
  uint8_t mask = readBack(rdac, 0x02);
  //  COMMAND 16 - page 29
  uint8_t cmd = 0xD0;
  return send(cmd, mask | 0x04);
}


uint8_t AD51XX::setPotentiometerMode(const uint8_t rdac)
{
  //  COMMAND 3
  uint8_t mask = readBack(rdac, 0x02);
  //  COMMAND 16 - page 29
  uint8_t cmd = 0xD0;
  return send(cmd, mask & (~0x04));
}


uint8_t AD51XX::getOperationalMode(const uint8_t rdac)
{
  uint8_t mask = readBack(rdac, 0x02);
  return ((mask & 0x04) > 0);
}


/////////////////////////////////////////////////////////////////////////////
//
//  INCREMENT / DECREMENT
//
uint8_t AD51XX::incrementLinear(const uint8_t rdac)
{
  //  COMMAND 4
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x40 | rdac;
  return send(cmd, 0x01);
}


uint8_t AD51XX::incrementLinearAll()
{
  //  COMMAND 4
  uint8_t cmd = 0x48;
  return send(cmd, 0x01);
}


uint8_t AD51XX::decrementLineair(const uint8_t rdac)
{
  //  COMMAND 4
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x40 | rdac;
  return send(cmd, 0x00);
}


uint8_t AD51XX::decrementLineairAll()
{
  //  COMMAND 4
  uint8_t cmd = 0x48;
  return send(cmd, 0x00);
}


uint8_t AD51XX::increment6dB(const uint8_t rdac)
{
  //  COMMAND 5
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x50 | rdac;
  return send(cmd, 0x01);
}


uint8_t AD51XX::increment6dBAll()
{
  //  COMMAND 5
  uint8_t cmd = 0x58;
  return send(cmd, 0x01);
}


uint8_t AD51XX::decrement6dB(const uint8_t rdac)
{
  //  COMMAND 5
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x50 | rdac;
  return send(cmd, 0x00);
}


uint8_t AD51XX::decrement6dBAll()
{
  //  COMMAND 5
  uint8_t cmd = 0x58;
  return send(cmd, 0x00);
}


/////////////////////////////////////////////////////////////////////////////
//
//  PRELOAD / SYNC
//
uint8_t AD51XX::preload(const uint8_t rdac, const uint8_t value)
{
  //  COMMAND 2 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  if (value > _maxValue) return AD51XXA_INVALID_VALUE;
  uint8_t cmd = 0x20 | rdac;
  return send(cmd, _lastValue[rdac]);
}


uint8_t AD51XX::preloadAll(const uint8_t value)
{
  if (value > _maxValue) return AD51XXA_INVALID_VALUE;
  //  COMMAND 2 - page 29
  uint8_t cmd = 0x28;
  return send(cmd, value);
}


uint8_t AD51XX::sync(const uint8_t mask)
{
  //  COMMAND 8 - page 29
  uint8_t cmd = 0x60 | mask;
  return send(cmd, 0x00);
  //  keep cache correct.
  uint8_t m = 0x01;
  for (uint8_t rdac = 0; rdac < _potCount; rdac++)
  {
    if (mask & m)
    {
      _lastValue[rdac] = readBackRDAC(rdac);
      m <<= 1;
    }
  }
}


/////////////////////////////////////////////////////////////////////////////
//
//  MISC
//
uint8_t AD51XX::pmCount()
{
  return _potCount;
}


uint8_t AD51XX::maxValue()
{
  return _maxValue;
}


uint8_t AD51XX::shutDown()
{
  //  COMMAND 15 - table 29
  //  shutdown all channels
  return send(0xC8, 0x01);   // to be tested
}


uint8_t AD51XX::readBackINPUT(const uint8_t rdac)   
{
  return readBack(rdac, 0x00); 
}


uint8_t AD51XX::readBackEEPROM(const uint8_t rdac)  
{
  return readBack(rdac, 0x01); 
}


uint8_t AD51XX::readBackCONTROL(const uint8_t rdac) 
{
  return readBack(rdac, 0x02); 
}


uint8_t AD51XX::readBackRDAC(const uint8_t rdac)    
{
  return readBack(rdac, 0x03); 
}


uint8_t AD51XX::writeControlRegister(uint8_t mask)
{
  //  COMMAND 16 - page 29
  uint8_t cmd = 0xD0;
  return send(cmd, mask);
}


/////////////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
//  _wire->endTransmission
//  returns   description
//    0:      success
//    1:      data too long to fit in transmit buffer
//    2:      received NACK on transmit of address
//    3:      received NACK on transmit of data
//    4:      other error
//
uint8_t AD51XX::send(const uint8_t cmd, const uint8_t value)
{
  //  COMMAND 1 - page 20
  _wire->beginTransmission(_address);  // returns nothing.
  _wire->write(cmd);                   // returns bytes written
  _wire->write(value);                 // returns bytes written
  return _wire->endTransmission();     // returns status of actual write
}


uint8_t AD51XX::readBack(const uint8_t rdac, const uint8_t mask)
{
  //  COMMAND 3 - page 20
  _wire->beginTransmission(_address);
  _wire->write(0x30 | rdac);
  _wire->write(mask);
  _wire->endTransmission();
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();

  // int a = _wire->write(0x30 | rdac);
  // Serial.print("READBACK cmd: ");
  // Serial.print(a);
  // a = _wire->write(mask);
  // Serial.print(" val: ");
  // Serial.print(a);
  // a = _wire->endTransmission();
  // Serial.print(" TX: ");
  // Serial.println(a);
  // a = _wire->requestFrom(_address, (uint8_t)1);
  // Serial.print(" RF: ");
  // Serial.println(a);
  // return _wire->read();
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
AD5123::AD5123(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 4;
  _maxValue = 127;
}


AD5124::AD5124(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 4;
  _maxValue = 127;
}


AD5143::AD5143(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 4;
  _maxValue = 255;
}


AD5144::AD5144(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 4;
  _maxValue = 255;
}


AD5144A::AD5144A(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 4;
  _maxValue = 255;
}


AD5122A::AD5122A(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 2;
  _maxValue = 127;
}


AD5142A::AD5142A(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 2;
  _maxValue = 255;
}


AD5121::AD5121(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 1;
  _maxValue = 127;
}


AD5141::AD5141(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 1;
  _maxValue = 255;
}


//  -- END OF FILE --

