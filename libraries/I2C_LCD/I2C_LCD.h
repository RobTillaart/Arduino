#pragma once
//
//    FILE: I2C_LCD.h
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.0
//    DATE: 2023-12-16
// PUPROSE: Arduino library for I2C_LCD
//     URL: https://github.com/RobTillaart/I2C_LCD


#define I2C_LCD_LIB_VERSION     (F("0.1.0"))

#include "Arduino.h"
#include "Wire.h"


class I2C_LCD : public Print
{
public:
  explicit  I2C_LCD(uint8_t address, TwoWire * wire = &Wire);

  void      config(uint8_t address, uint8_t enable, uint8_t readwrite, uint8_t registerselect, 
                   uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7, uint8_t backlight);

  void      begin(uint8_t cols = 20, uint8_t rows = 4);

  void      setBacklight(bool on);   //  backlight() / noBacklight()

  void      display();
  void      noDisplay();

  void      clear();
  void      home();
  void      setCursor(uint8_t col, uint8_t row);


//  TODO private..

  //  PRINT INTERFACE
  size_t    write(uint8_t c);

  void      sendData(uint8_t value);
  void      sendCommand(uint8_t value);
  void      write4bits(uint8_t value);


private:
  uint8_t   _address = 0;
  TwoWire * _wire = NULL;

  //  defaults
  uint8_t   _enable;
  uint8_t   _readWrite;
  uint8_t   _registerSelect;
  uint8_t   _backLight;
  uint8_t   _dataPin[4];

  //  TODO backlight status

  uint8_t   _cols = 20;
  uint8_t   _rows = 4;

  bool      _pinsInOrder;
  
};


//  -- END OF FILE --

