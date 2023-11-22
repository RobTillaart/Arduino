#pragma once
//
//    FILE: SWSerialOut.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for SWSerialOut, supports only data out (TX).
//    DATE: 2023-09-02
//     URL: https://github.com/RobTillaart/SWSerialOut


#include "Arduino.h"


#define SWSERIALOUT_LIB_VERSION              (F("0.1.1"))


class SWSerialOut : public Stream
{
public:
  SWSerialOut(uint8_t TXpin, bool inverse = false)
  {
    _TX = TXpin;
    _inverse = inverse;
  }


  void begin(uint32_t baudRate)
  {
    _baud  = baudRate;
    _pulse = round(1000000.0 / _baud);
#if defined(ARDUINO_ARCH_AVR)
    _pulse -= 4;
#elif defined(ESP32)
    _pulse -= 1;
#endif
    pinMode(_TX, OUTPUT);
    digitalWrite(_TX, HIGH);
  }


  void begin(uint32_t baudRate, char * params)  //  TODO TEST
  {
    begin(baudRate);
    _bits = constrain(params[0] - '0', 5, 8);
    _parity = params[1];
    _stopBits = constrain(params[2] - '0', 0, 3);
    if (strchr("NEOSM", _parity) == NULL)  //  invalid?
    {
      _parity = 'N';
    }
  }


  //  PRINT interface
  size_t write(uint8_t b)
  {
    if (_disableInterrupts)
    {
      noInterrupts();  //  no IRQ disturbances.
    }

    //  start bit
    uint32_t start = micros();
    digitalWrite(_TX, LOW);
    while(micros() - start < _pulse);

    //  byte
    uint8_t parity = 0;
    uint8_t cnt = _bits;
    uint8_t bit = 0;
    while (cnt-- > 0)
    {
      start = micros();
      bit = b & 0x01;
      if (bit) parity++;       //  count 1's
      digitalWrite(_TX, bit);
      b >>= 1;
      while(micros() - start < _pulse);
    }
    parity &= 0x01;

    //  parity bits
    if (_parity != 'N')
    {
      if (_parity == 'E')      bit = parity;      //  even # 1 bits
      else if (_parity == 'O') bit = 1 - parity;  //  odd  # 1 bits
      else if (_parity == 'S') bit = 0;           //  always 0
      else if (_parity == 'M') bit = 1;           //  always 1
      start = micros();
      digitalWrite(_TX, bit);
      while(micros() - start < _pulse);
    }

    //  stop bits
    digitalWrite(_TX, HIGH);
    delayMicroseconds(_pulse * _stopBits);

    interrupts();

    return 1;
  }


  void disableInterrupts(bool b)
  {
    _disableInterrupts = b;
  }


  //   STREAM interface (for compatibility)
  int  available() { return 0; };
  int  peek()      { return 0; };
  int  read()      { return 0; };
  void flush()     { return; };   //  placeholder to keep build CI happy


  //  DEBUG
  void debug()
  {
    Serial.print("DBG: PIN");
    Serial.print(_TX);
    Serial.print(":");
    Serial.print(_baud);
    Serial.print(':');
    Serial.print(_parity);
    Serial.print(',');
    Serial.print(_bits);
    Serial.print(',');
    Serial.print(_stopBits);
    Serial.print('\t');
    Serial.print(_pulse);
    Serial.print('\t');
    Serial.print(_inverse);
    Serial.print('\t');
    Serial.println(_disableInterrupts);
    delay(100);
  }


private:
  uint8_t   _TX;

  //  configuration
  uint32_t  _baud     = 9600;  //  check range
  char      _parity   = 'N';   //  None, Even, Odd
  uint8_t   _bits     = 8;     //  5,6,7,8
  uint8_t   _stopBits = 1;     //  0,1,2
  bool      _inverse  = false; //  TODO
  bool      _disableInterrupts = false;

  //  timing
  uint32_t  _pulse;


};


//  -- END OF FILE --

