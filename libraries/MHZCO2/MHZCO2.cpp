//
//    FILE: MHZCO2.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino Library for MHZ series CO2 sensors
//    DATE: 2020-05-05
//     URL: https://github.com/RobTillaart/MHZCO2


#include "MHZCO2.h"


MHZCO2::MHZCO2()
{
  _startTime = millis();
}


void MHZCO2::begin(Stream * str)
{
  _str = str;
  _lastMeasurement = 0;
  _timeout         = 1000;
  _PPM             = 0;
  _CO2             = 0;
  _temperature     = 0;
  _accuracy        = 0;
  _minCO2          = 0;
}


uint32_t MHZCO2::uptime()
{
  return millis() - _startTime;
}


void MHZCO2::setPPM(uint16_t PPM)
{
  _PPM = PPM;
  uint8_t data[9] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  //  as max value is lower than 65536 only two bytes need to be set.
  //  data[4] = 0;
  //  data[5[ = 0;
  data[6] = PPM >> 8;
  data[7] = PPM & 0xFF;
  data[8] = checksum(data);
  send(data, 9);
}


uint16_t MHZCO2::getPPM()
{
  return _PPM;
}


int MHZCO2::measure()
{
  uint8_t data[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  data[8] = checksum(data);
  send(data, 9);

  int rv = receive(data);
  //  allow partial good data?
  if ((rv == MHZCO2_OK) || (rv == MHZCO2_ERROR_CRC))
  {
    _CO2         = data[2] * 256 + data[3];
    _temperature = data[4] - 40;
    _accuracy    = data[5];
    _minCO2      = data[6] * 256 + data[7];
  }
  if (rv == MHZCO2_OK)
  {
    _lastMeasurement = millis();
  }
  return rv;
}


uint32_t MHZCO2::lastMeasurement()
{
  return _lastMeasurement;
}


int MHZCO2::getCO2()
{
  return _CO2;
};


int MHZCO2::getTemperature()
{
  return _temperature;
};


int MHZCO2::getAccuracy()
{
  return _accuracy;
}


int MHZCO2::getMinCO2()
{
  return _minCO2;
};


void MHZCO2::calibrateZero()
{
  uint8_t data[9] = {0xFF, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  data[8] = checksum(data);
  send(data, 9);
}


void MHZCO2::calibrateSpan(uint16_t span)
{
  uint8_t data[9] = {0xFF, 0x01, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  data[3] = span >> 8;
  data[4] = span & 0xFF;
  data[8] = checksum(data);
  send(data, 9);
}


void MHZCO2::calibrateAuto(bool mode)
{
  uint8_t data[9] = {0xFF, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  if (mode) data[3] = 0xA0;
  data[8] = checksum(data);
  send(data, 9);
}


void MHZCO2::setTimeOut(uint16_t timeout)
{
  _timeout = timeout;
}


uint16_t MHZCO2::getTimeOut()
{
  return _timeout;
}



/////////////////////////////////////////////////
//
//  PROTECTED
//
void MHZCO2::send(uint8_t * data, uint8_t len)
{
  _str->write(data, len);
  _str->flush();  //  do not return until all data is sent.
}


int MHZCO2::receive(uint8_t * answer)
{
  uint32_t start = millis();

  //  need to read 9 bytes.
  uint8_t i = 0;
  while (i < 9)
  {
    if (_str->available())
    {
      answer[i] = _str->read();
      i++;
    }
    else
    {
      //  default _timeout = 1000
      if ((_timeout > 0) && (millis() - start > _timeout))
      {
        return MHZCO2_TIMEOUT;
      }
    }
  }
  //  verify checksum
  if (answer[8] != checksum(answer))
  {
    return MHZCO2_ERROR_CRC;
  }

  return MHZCO2_OK;
}


uint8_t MHZCO2::checksum(uint8_t *arr)
{
  uint8_t sum = 0;
  for (uint8_t i = 1; i < 8; i++)
  {
    sum += arr[i];
  }
  sum = 0xFF - sum;
  return sum + 1;
}



/////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
MHZ1311A::MHZ1311A() : MHZCO2()
{
}

MHZ19::MHZ19() : MHZCO2()
{
}

MHZ19B::MHZ19B() : MHZCO2()
{
}

MHZ19C::MHZ19C() : MHZCO2()
{
}

MHZ19D::MHZ19D() : MHZCO2()
{
}

MHZ19E::MHZ19E() : MHZCO2()
{
}



//  -- END OF FILE --

