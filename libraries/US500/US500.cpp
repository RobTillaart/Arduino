//
//    FILE: US500.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-29
// VERSION: 0.1.1
// PURPOSE: Arduino library for US500 and US4000 underwater distance sensor.
//     URL: https://github.com/RobTillaart/US500



#include "US500.h"


constexpr uint8_t US500_REQUEST_TIMEOUT = 20;


US500::US500(Stream * str)
{
  _stream    = str;
  _buffer[0] = '\0';
  _address   = 0x0005;
}


uint16_t US500::getAddress()
{
  return _address;
}

/////////////////////////////////////////////
//
//  COMMANDS
//
float US500::getDistance()
{
  //  cmd 0x08, size = 0
  uint8_t buf[5] = { 0x08, 0x00, 0x00, 0x000, 0x00};
  int status = _request(buf, 5, 11);
  if (status == 11)
  {
    float distance = (_buffer[8] + 256 * _buffer[9]) * 0.01;
    return distance;
  }
  return status;
}

int US500::setMaxDistance(uint16_t distance)
{
  //  cmd 0x09, size = 2
  uint8_t buf[7] = { 0x09, 0x02 , 0x00 , 0x00 , 0x00 };
  buf[5] = distance & 0xFF;
  buf[6] = distance >> 8;
  
  int status = _request(buf, 7, 10);
  if (status == 10)
  {
    return _buffer[8];  //  0x01 success, 0x00 failed.
  }
  return status;
}


float US500::getTemperature()
{
  //  cmd 0x0A, size = 0
  uint8_t buf[5] = { 0x0A, 0x00, 0x00, 0x000, 0x00};
  int status = _request(buf, 5, 13);
  if (status == 13)
  {
    int32_t t = _buffer[11];
    t <<= 8;
    t += _buffer[10];
    t <<= 8;
    t += _buffer[9];
    t <<= 8;
    t += _buffer[8];
    return t * 0.1;
  }
  return status;
}


void US500::startMeasurement()
{
  //  cmd 0x7B, size = 0
  uint8_t buf[5] = { 0x7B, 0x00, 0x00, 0x000, 0x00};
  _command(buf, 5);
}


void US500::stopMeasurement()
{
  //  cmd 0x7A, size = 0
  uint8_t buf[5] = { 0x7A, 0x00, 0x00, 0x000, 0x00};
  _command(buf, 5);
}


void US500::flush()
{
  while(_stream->available()) _stream->read();
}


///////////////////////////////////////////////
//
//  PRIVATE
//

void US500::_command(uint8_t * arr, uint8_t TXsize)
{
  _stream->write((uint8_t)0x5A);  //  not part of checksum
  _stream->write((uint8_t)_address & 0xFF);
  _stream->write((uint8_t)_address >> 8);
  uint8_t checksum = 0x05 ^0x00;
  _stream->write(arr, TXsize);
  for (int i = 0; i < TXsize; i++) checksum ^= arr[i];
  _stream->write(checksum);
  delay(TXsize);   //  wait for all send
}


int US500::_request(uint8_t * arr, uint8_t TXsize, uint8_t RXsize)
{
  _command(arr, TXsize);

  //  wait for answer
  uint8_t idx = 0;
  uint32_t start = millis();
  while (millis() - start < US500_REQUEST_TIMEOUT)
  {
    if (_stream->available())
    {
      _buffer[idx++] = _stream->read();
      if (idx == RXsize) break;
    }
  }
  //  check timeout
  if (idx != RXsize)
  {
    return US500_TIMEOUT_ERROR;
  }

  /* 
  //  debug
  _buffer[idx] = 0;
  Serial.print("buffer: ");
  for (int i = 0; i < idx; i++)
  {
    if (_buffer[i] < 16) Serial.print(0);
    Serial.print(_buffer[i], HEX);
  }
  Serial.println();
  */

  //  check answer
  if (_buffer[3] != (0x80 | arr[3]))
  {
    return US500_CMD_ERROR;
  }
  uint8_t checksum = 0;
  for (int i = 0; i < RXsize; i++) checksum ^= _buffer[i];
  if (checksum != 0)
  {
    return US500_CRC_ERROR;
  }
  return idx;
}


//  -- END OF FILE --

