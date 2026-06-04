//
//    FILE: A02YY.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-05-07
// VERSION: 0.1.2
// PURPOSE: Arduino library for A02YY serial distance sensor
//     URL: https://github.com/RobTillaart/A02YY


#include "A02YYUW.h"


A02YY::A02YY(Stream * str)
{
  _stream   = str;
  //  reset variables
  _byte = 0;
  _lastRead = 0;
  _lastHeader = 0;
  _millimetres = 0;
  _error = A02YY_OK;
}


void A02YY::begin()
{
  //  empty the stream buffer.
  flush();
  //  reset variables
  _byte = 0;
  _lastRead = 0;
  _lastHeader = 0;
  _millimetres = 0;
  _error = A02YY_OK;
}

bool A02YY::newDistance()
{
  //  need to read 4 bytes from the stream starting
  //  packet == [0xFF header, high, low, checksum]
  //  there is a small chance that the 0xFF is not the header.
  while (_stream->available())
  {
    uint8_t data = _stream->read();
    if ((_byte == 0) && (data == 0xFF))
    {
      _error = A02YY_OK;
      _lastHeader = millis();
      _byte++;
    }
    else if (_byte == 1)
    {
      _byte++;
      _high = data;
    }
    else if (_byte == 2)
    {
      _byte++;
      _low = data;
    }
    else  //  _byte >= 3 to catch all other cases
    {
      //  test checksum
      uint8_t _crc = (_high + _low + 0xFF) & 0xFF;
      if ( _crc != data)
      {
        _error = A02YY_ERR_CRC;
        //  unknown which byte failed, high, low or checkSum byte?
      }
      else
      {
        _error = A02YY_OK;
      }
      //  distance can still be valid if there is an CRC error.
      //  distance in millimetres.
      _millimetres = _high * 256 + _low;
      _lastRead = millis();
      //  prepare for next packet of 4 bytes.
      _byte = 0;
      return true;
    }
  }
  if (millis() - _lastHeader > 250)
  {
    _error = A02YY_ERR_TIMEOUT;
  }
  return false;
}


uint16_t A02YY::getDistanceMM()
{
  return _millimetres;
}


float A02YY::getDistanceCM()
{
  return _millimetres * 0.1;
}


float A02YY::getDistanceINCH()
{
  return _millimetres * (1.0 / 25.4);  //  0.0393700787
}


uint32_t A02YY::lastRead()
{
  return _lastRead;
}


void A02YY::flush()
{
  while (_stream->available()) _stream->read();
}

int A02YY::getLastError()
{
  int e = _error;
  _error = A02YY_OK;
  return e;
}


////////////////////////////////////////////
//
//  DERIVED CLASSES - UART AUTO - A02YYU(W)
//
void A02YYU::setProcessingMode(bool mode)
{
  //  pinMode is already set.
  digitalWrite(_TX, mode ? 1 : 0);
}

bool A02YYU::getProcessingMode()
{
  return (digitalRead(_TX) == HIGH);
}


////////////////////////////////////////////
//
//  DERIVED CLASSES - UART CONTROLLED - A02YYT(W)
//
void A02YYT::request()
{
  //  The UART CONTROLLED module measures a distance
  //  after Pin(RX) receives a falling edge pulse.
  //  a write seems to work.
  _stream->write(0x0F);
}


//  -- END OF FILE --

