//
//    FILE: AM232X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: AM232X library for AM2320 for Arduino.
//
// HISTORY:
//   0.1.0  2017-12-11 initial version
//   0.1.1  2017-12-12 added CRC checking
//   0.1.2  2017-12-12 get and set functions.
//   0.1.3  2017-12-19 added ESP8266 - issue #86
//                     tested by Viktor Balint
//   0.1.4  2018-10-24 fixed temperature formula - #114
//                     thanks to 9a4gl
//   0.1.5  2020-03-25 refactor, add read() to begin()
//   0.2.0  2020-05-03 made temperature + humidity private, add wrapper functions.
//   0.2.1  2020-05-06 fix temperature function (thanks Chade)
//   0.2.2  2020-05-12 added ESP32 support
//   0.2.3  2020-05-27 update library.json
//

#include <AM232X.h>

#define AM232X_ADDRESS ((uint8_t)0x5C)

////////////////////////////////////////////////////////////////////
//
// PUBLIC
//
#if defined (ESP8266) || defined(ESP32)
void AM232X::begin(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);
  this->read();
}
#endif

void AM232X::begin()
{
  Wire.begin();
  this->read();
}

int AM232X::read()
{
  // READ HUMIDITY AND TEMPERATURE REGISTERS
  int rv = _readRegister(0x00, 4);
  if (rv < 0) return rv;

  // CONVERT AND STORE
  humidity = (bits[2] * 256 + bits[3]) * 0.1;
  temperature = ((bits[4] & 0x7F) * 256 + bits[5]) * 0.1;

  if (bits[4] & 0x80)
  {
    temperature = -temperature;
  }
  return AM232X_OK;
}

int AM232X::getModel()
{
  int rv = _readRegister(0x08, 2);
  if (rv < 0) return rv;

  return (bits[2] * 256) + bits[3];
}

int AM232X::getVersion()
{
  int rv = _readRegister(0x0A, 1);
  if (rv < 0) return rv;

  return bits[2];
}

uint32_t AM232X::getDeviceID()
{
  int rv = _readRegister(0x0B, 4);
  if (rv < 0) return rv;

  uint32_t _deviceID = (bits[2] * 256) + bits[3];
  _deviceID = _deviceID * 256 + bits[4];
  _deviceID = _deviceID * 256 + bits[5];
  return _deviceID;
}

int AM232X::getStatus()
{
  int rv = _readRegister(0x0F, 1);
  if (rv < 0) return rv;

  return bits[2];
}

int AM232X::getUserRegisterA()
{
  int rv = _readRegister(0x10, 2);
  if (rv < 0) return rv;

  return (bits[2] * 256) + bits[3];
}

int AM232X::getUserRegisterB()
{
  int rv = _readRegister(0x12, 2);
  if (rv < 0) return rv;

  return (bits[2] * 256) + bits[3];
}

int AM232X::setStatus(uint8_t value)
{
  int rv = _writeRegister(0x0F, 1, value);
  if (rv < 0) return rv;

  return AM232X_OK;
}

int AM232X::setUserRegisterA(int value)
{
  int rv = _writeRegister(0x10, 2, value);
  if (rv < 0) return rv;

  return AM232X_OK;
}

int AM232X::setUserRegisterB(int value)
{
  int rv = _writeRegister(0x12, 2, value);
  if (rv < 0) return rv;

  return AM232X_OK;
}

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//
int AM232X::_readRegister(uint8_t reg, uint8_t count)
{
  // wake up the sensor - see 8.2
  Wire.beginTransmission(AM232X_ADDRESS);
  int rv = Wire.endTransmission();
  delayMicroseconds(1000);          // TODO tune

  // request the data
  Wire.beginTransmission(AM232X_ADDRESS);
  Wire.write(0x03);
  Wire.write(reg);
  Wire.write(count);
  rv = Wire.endTransmission();
  if (rv < 0) return rv;

  // request 4 extra, 2 for cmd + 2 for CRC
  uint8_t length = count + 4;
  int bytes = Wire.requestFrom(AM232X_ADDRESS, length);

  for (int i = 0; i < bytes; i++)
  {
    bits[i] = Wire.read();
  }
  // ANALYZE ERRORS
  // will not detect if we requested 1 byte as that will
  // return 5 bytes as requested. E.g. getStatus()
  // TODO: design a fix.
  if (bytes != length)
  {
    switch(bits[3])
    {
    case 0x80: return AM232X_ERROR_FUNCTION;
    case 0x81: return AM232X_ERROR_ADDRESS;
    case 0x82: return AM232X_ERROR_REGISTER;
    case 0x83: return AM232X_ERROR_CRC_1;  // prev write had a wrong CRC
    case 0x84: return AM232X_ERROR_WRITE_DISABLED;
    default:   return AM232X_ERROR_UNKNOWN;
    }
  }

  // CRC is LOW Byte first
  uint16_t crc = bits[bytes - 1]*256 + bits[bytes - 2];
  if (crc16(&bits[0], bytes - 2) != crc)
  {
    return AM232X_ERROR_CRC_2;  // read itself has wrong CRC
  }
  return AM232X_OK;
}

int AM232X::_writeRegister(uint8_t reg, uint8_t cnt, int16_t value)
{
  // wake up the sensor - see 8.2
  Wire.beginTransmission(AM232X_ADDRESS);
  int rv = Wire.endTransmission();
  delayMicroseconds(1000);          // TODO tune

  // prepare data to send
  bits[0] = 0x10;
  bits[1] = reg;
  bits[2] = cnt;

  // TODO: is the order correct? MSB LSB
  if (cnt == 2)
  {
    bits[4] = value & 0xFF;
    bits[3] = (value >> 8) & 0xFF;
  }
  else
  {
    bits[3] = value & 0xFF;
  }

  // send data
  uint8_t length = cnt + 3;  // 3 = cmd, startReg, #bytes
  Wire.beginTransmission(AM232X_ADDRESS);
  for (int i=0; i< length; i++)
  {
    Wire.write(bits[i]);
  }
  // send the CRC
  uint16_t crc = crc16(bits, length);
  Wire.write(crc & 0xFF);
  Wire.write(crc >> 8);

  rv = Wire.endTransmission();
  if (rv < 0) return rv;

  // wait for the answer
  int bytes = Wire.requestFrom(AM232X_ADDRESS, length);
  for (int i = 0; i < bytes; i++)
  {
    bits[i] = Wire.read();
  }

  // ANALYZE ERRORS
  // will not detect if we requested 1 byte as that will
  // return 5 bytes as requested. E.g. getStatus()
  // TODO: design a fix.
  if (bytes != length)
  {
    switch(bits[3])
    {
    case 0x80: return AM232X_ERROR_FUNCTION;
    case 0x81: return AM232X_ERROR_ADDRESS;
    case 0x82: return AM232X_ERROR_REGISTER;
    case 0x83: return AM232X_ERROR_CRC_1;  // prev write had a wrong CRC
    case 0x84: return AM232X_ERROR_WRITE_DISABLED;
    default: return AM232X_ERROR_UNKNOWN;
    }
  }

  // CRC is LOW Byte first
  crc = bits[bytes - 1]*256 + bits[bytes - 2];
  if (crc16(&bits[0], bytes - 2) != crc)
  {
    return AM232X_ERROR_CRC_2;  // read itself has wrong CRC
  }

  return AM232X_OK;
}

uint16_t AM232X::crc16(uint8_t *ptr, uint8_t len)
{
  uint16_t crc =0xFFFF;

  while (len--)
  {
    crc ^= *ptr++;
    for(int i = 0; i < 8; i++)
    {
      if (crc & 0x01)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }
  return crc;
}

// -- END OF FILE --
