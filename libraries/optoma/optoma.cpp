//
//    FILE: optoma.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2017-11-27
// PUPROSE: Arduino library to control Optoma W305ST beamer over RS232. 
//     URL: https://github.com/RobTillaart/optoma
//
//  HISTORY
//  0.1.0   2017-11-27  initial version
//  0.1.1   2020-07-09  initial release
//  0.1.2   2020-01-02  arduino-CI 

#include "optoma.h"

Optoma::Optoma(HardwareSerial* stream)
{
  _stream = stream;
}

void Optoma::init(int ID, uint32_t baudRate)
{
  _ID = ID;
  _stream->begin(baudRate);
  _stream->print("# init : ");
  _stream->print(baudRate);
  _stream->print("\r");
}

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

// -- END OF FILE --
