#pragma once
//
//    FILE: Optoma.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2017-11-27
// PURPOSE: Arduino library to control Optoma W305ST beamer over RS232.
//     URL: https://github.com/RobTillaart/Optoma


#include "Arduino.h"

#define OPTOMA_LIB_VERSION        (F("0.1.6"))


class Optoma
{
public:
  Optoma(HardwareSerial * stream = &Serial);

  void     init(int ID, uint32_t baudRate = 9600);
  uint32_t getBaudrate();

  void     switchOn();
  void     switchOff();
  bool     isOn();

  //   VKS = Vertical KeyStone
  void     increaseVKS();
  void     decreaseVKS();

private:
  HardwareSerial * _stream;

  int      _ID = 0;
  bool     _on = false;
  uint32_t _baudrate = 9600;

  void     sendID();
};


//  -- END OF FILE --

