//
//    FILE: optoma.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2017-11-27
// PURPOSE: Arduino library to control Optoma W305ST beamer over RS232.
//     URL: https://github.com/RobTillaart/optoma


#include "optoma.h"


Optoma::Optoma(HardwareSerial * stream)
{
  _stream   = stream;
  _ID       = 0;
  _on       = false;
  _baudrate = 9600;
}


void Optoma::init(int ID, uint32_t baudRate)
{
  _ID = ID;
  _stream->begin(baudRate);
  _stream->print("# init : ");
  _stream->print(baudRate);
  _stream->print("\r");
}


uint32_t Optoma::getBaudrate() 
{
  return _baudrate;
};


void Optoma::switchOn()
{
  sendID();
  _stream->print(F("00 1\r"));
  _on = true;
};


void Optoma::switchOff()
{
  sendID();
  _stream->print(F("00 0\r"));
  _on = false;
};


void Optoma::increaseVKS()
{
  sendID();
  _stream->print(F("140 15\r"));
};


void Optoma::decreaseVKS()
{
  sendID();
  _stream->print(F("140 16\r"));
};


bool Optoma::isOn()
{
  return _on;
};


void Optoma::sendID()
{
  _stream->print('~');
  if (_ID < 10) Serial.print('0');
  _stream->print(_ID);
}


//  -- END OF FILE --

