//
//    FILE: AM232X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: AM232X library for AM2320 for Arduino.
//
// HISTORY:
// 0.1.0 - 2017-12-11 initial version
// 0.1.1 = 2017-12-12 added CRC
//
// Released to the public domain
//

#include <AM232X.h>

////////////////////////////////////////////////////////////////////
//
// PUBLIC
//
AM232X::AM232X()
{
  _deviceAddress = AM232X_ADDRESS;
  _model = -1;
  _version = -1;
  _deviceID = -1;
}

int AM232X::read()
{
  // READ HUMIDITY AND TEMPERATURE REGISTERS
  int rv = _readRegister(0x00, 4);
  if (rv < 0) return AM232X_ERROR_CONNECT;

  // CONVERT AND STORE
  humidity = (bits[2]*256 + bits[3]) * 0.1;
  temperature = (bits[4] & 0x7F)*256 + bits[5] * 0.1;
  
  if (bits[4] & 0x80)
  {
    temperature = -temperature;
  }
  return AM232X_OK;
}

int AM232X::getModel()
{
  int rv = _readRegister(0x08, 2);
  _model = (bits[2] * 256) + bits[3];
  if (rv < 0) return AM232X_ERROR_CONNECT;
  return AM232X_OK; 
}

int AM232X::getVersion()
{
  int rv = _readRegister(0x0A, 1);
  _version = bits[2];
  if (rv < 0) return AM232X_ERROR_CONNECT;
  return AM232X_OK; 
}

uint32_t AM232X::getDeviceID()
{
  int rv = _readRegister(0x0B, 4);
  _deviceID = (bits[2] * 256) + bits[3];
  _deviceID = _deviceID * 256 + bits[4];
  _deviceID = _deviceID * 256 + bits[5];
  if (rv < 0) return AM232X_ERROR_CONNECT;

  return AM232X_OK; 
}

int AM232X::getStatus()
{
  _readRegister(0x0F, 1);
  return bits[2];
}

int AM232X::getUserRegisterA()
{
  _readRegister(0x10, 2);
  return (bits[2] * 256) + bits[3];
}

int AM232X::getUserRegisterB()
{
  _readRegister(0x12, 2);
  return (bits[2] * 256) + bits[3];
}

int AM232X::setUserRegisterA(int value)
{
  // TODO
  _writeRegister(0x10, 2, value);
  return AM232X_OK;
}

int AM232X::setUserRegisterB(int value)
{
  // TODO
  _writeRegister(0x12, 2, value);
  return AM232X_OK;
}

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//
int AM232X::_readRegister(uint8_t reg, uint8_t count)
{
  bool debug = true;
  
  // wake up the sensor - see 8.2
  Wire.beginTransmission(_deviceAddress);
  int rv = Wire.endTransmission();
  delayMicroseconds(1000);          // TODO tune

  // request the data
  Wire.beginTransmission(_deviceAddress);
  Wire.write(0x03);
  Wire.write(reg);
  Wire.write(count);
  rv = Wire.endTransmission();
  if (rv < 0) return rv;

  // request 4 extra, 2 for cmd + 2 for CRC
  uint8_t length = count + 4;
  int bytes = Wire.requestFrom(_deviceAddress, length);
  
  if (debug) Serial.println();
  for (int i = 0; i < bytes; i++)
  {
    bits[i] = Wire.read();
    if (debug) 
    {
      Serial.print(bits[i], HEX);
      Serial.print("\t");
    }
  }
  if (debug) Serial.println();

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
      default: return AM232X_MISSING_BYTES;
    }
  }

  // CRC is LOW Byte first
  uint16_t crc = bits[bytes - 1]*256 + bits[bytes - 2];
  if (crc16(&bits[0], count-2) != crc)
  {
    if (debug) 
    {
      Serial.print("CRC: ");
      Serial.println(crc);
    }
    return AM232X_ERROR_CRC_2;  // read itself has wrong CRC
  }
  return AM232X_OK;
}

int AM232X::_writeRegister(uint8_t reg, uint8_t cnt, int32_t value)
{
  // wake up the sensor - see 8.2
  Wire.beginTransmission(_deviceAddress);
  int rv = Wire.endTransmission();
  delayMicroseconds(1000);          // TODO tune

  // prepare data to send
  bits[0] = 0x10;
  bits[1] = reg;
  bits[2] = cnt;

  if (cnt == 4)
  {
    bits[6] = value & 0xFF;
    bits[5] = (value >> 8) & 0xFF;
    bits[4] = (value >> 8) & 0xFF;
    bits[3] = (value >> 8) & 0xFF;
  }
  else if (cnt == 2)
  {
    bits[4] = value & 0xFF;
    bits[3] = (value >> 8) & 0xFF;
  }
  else if (cnt == 1)
  {
    bits[3] = value & 0xFF;
  }
  uint16_t crc = crc16(bits, cnt + 3);
  
  // send data
  Wire.beginTransmission(_deviceAddress);
  for (int i=0; i< cnt+3; i++)
  {
    Wire.write(bits[i]);
  }
  Wire.write(crc & 0xFF);
  Wire.write(crc >> 8);
  rv = Wire.endTransmission();
  if (rv < 0) return rv;

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
//
// END OF FILE
//