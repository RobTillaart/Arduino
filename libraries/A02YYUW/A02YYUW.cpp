//
//    FILE: A02YYUW.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-05-07
// VERSION: 0.1.1
// PURPOSE: Arduino library for A02YYUW serial distance sensor
//     URL: https://github.com/RobTillaart/A02YYUW


#include "A02YYUW.h"


A02YYUW::A02YYUW(Stream * str, uint8_t TX)
{
  _stream   = str;
  _TX       = TX;
  //  needed? as Serial implies TX == OUTPUT.
  pinMode(_TX, OUTPUT);
  //  reset variables
  _byte = 0;
  _lastRead = 0;
  _millimetres = 0;
  _error = A02YY_OK;
}


void A02YYUW::begin()
{
  //  empty the stream buffer.
  flush();
  //  reset variables
  _byte = 0;
  _lastRead = 0;
  _millimetres = 0;
  _error = A02YY_OK;
}

//  needed for the UART AUTO only
//  true  = processed mode
//  false = real time mode (default)
void A02YYUW::setProcessingMode(bool mode)
{
  //  pinMode is already set.
  digitalWrite(_TX, mode ? 1 : 0);
}


bool A02YYUW::getProcessingMode()
{
  return (digitalRead(_TX) == HIGH);
}


void A02YYUW::request()
{
  //  The UART CONTROLLED module measures a distance
  //  after Pin(RX) receives a falling edge pulse.
  //  a write seems to work.
  _stream->write(0x0F);
}


bool A02YYUW::newDistance()
{
  //  need to read 4 bytes from the stream starting
  //  packet == [0xFF header, high, low, checksum]
  //  there is a small chance that the 0xFF is not the header.
  while (_stream->available())
  {
    uint8_t data = _stream->read();
    if ((_byte == 0) && (data == 0xFF)) _byte++;
    else if (_byte == 1) { _byte++; _high = data; }
    else if (_byte == 2) { _byte++; _low = data;  }
    else  //  _byte == 3 => catch all cases
    {
      //  test HIGH byte <= 0x11 ? == 4500 mm
      //  low byte and checksum can be anything incl 0xFF.
      //  test checksum
      uint8_t _crc = data;
      if ( (_high + _low + 0xFF) != _crc)
      {
        _error = A02YY_ERR_CRC;
      }
      else
      {
        _error = A02YY_OK;
      }
      //  distance can still be valid.
      //  distance in millimetres.
      _millimetres = _high * 256 + _low;
      _lastRead = millis();
      _byte = 0;
      return true;
    }
  }
  return false;
}


uint16_t A02YYUW::getDistanceMM()
{
  return _millimetres;
}


float A02YYUW::getDistanceCM()
{
  return _millimetres * 0.1;
}


float A02YYUW::getDistanceINCH()
{
  return _millimetres * (1.0 / 25.4);  //  0.0393700787
}


uint32_t A02YYUW::lastRead()
{
  return _lastRead;
}


void A02YYUW::flush()
{
  while (_stream->available()) _stream->read();
}

int A02YYUW::getLastError()
{
  int e = _error;
  _error = A02YY_OK;
  return e;
}


//  -- END OF FILE --

