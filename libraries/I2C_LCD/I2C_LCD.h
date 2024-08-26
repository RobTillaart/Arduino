#pragma once
//
//    FILE: I2C_LCD.h
//  AUTHOR: Rob.Tillaart
// VERSION: 0.2.2
//    DATE: 2023-12-16
// PURPOSE: Arduino library for I2C_LCD
//     URL: https://github.com/RobTillaart/I2C_LCD


#define I2C_LCD_LIB_VERSION     (F("0.2.2"))


#include "Arduino.h"
#include "Wire.h"

const uint8_t POSITIVE = 1;
const uint8_t NEGATIVE = 0;


class I2C_LCD : public Print
{
public:
  //  only one constructor
  explicit  I2C_LCD(uint8_t address, TwoWire * wire = &Wire);

  //  adjust pins
  void      config(uint8_t address, uint8_t enable, uint8_t readWrite, uint8_t registerSelect,
                   uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7,
                   uint8_t backLight, uint8_t polarity);

  //  only supports 5x8 char set for now.
  //  blocks up to 100 milliseconds to give LCD time to boot
  bool      begin(uint8_t cols = 20, uint8_t rows = 4);
  bool      isConnected();


  //  BACKLIGHT
  void      setBacklightPin(uint8_t pin, uint8_t polarity);
  void      setBacklight(bool on);
  void      backlight()   { setBacklight(true);  };
  void      noBacklight() { setBacklight(false); };


  //  DISPLAY ON OFF
  void      display();
  void      noDisplay();
  void      on()  { display(); };
  void      off() { noDisplay(); };


  //  POSITIONING & CURSOR
  void      clear();      //  clears whole screen
  void      clearEOL();   //  clears line from current pos.
  void      home();
  bool      setCursor(uint8_t col, uint8_t row);

  void      noBlink();
  void      blink();
  void      noCursor();
  void      cursor();

  void      scrollDisplayLeft();
  void      scrollDisplayRight();
  void      moveCursorRight(uint8_t n = 1);
  void      moveCursorLeft(uint8_t n = 1);

  //  next 4 limited support
  void      autoscroll();
  void      noAutoscroll();
  void      leftToRight();
  void      rightToLeft();


  //  8 definable characters
  void      createChar(uint8_t index, uint8_t * charmap);
  //  clean way to print them
  inline size_t special(uint8_t index) { return write((uint8_t)index); };


  //  PRINT INTERFACE ++
  size_t    write(uint8_t c);
  size_t    center(uint8_t row, const char * message);
  size_t    right(uint8_t col, uint8_t row, const char * message);
  size_t    repeat(uint8_t c, uint8_t times);


  //  DEBUG  development
  uint8_t   getColumn() { return _pos; };  //  works.
  uint32_t  getWriteCount()  { return _count; };  // works


private:

  void      sendData(uint8_t value);
  void      sendCommand(uint8_t value);
  void      send(uint8_t value, bool dataFlag);
  void      write4bits(uint8_t value);

  uint8_t   _address = 0;
  TwoWire * _wire = NULL;

  uint8_t   _enable         = 4;
  uint8_t   _readWrite      = 2;
  uint8_t   _registerSelect = 1;

  uint8_t   _dataPin[4]     = { 16, 32, 64, 128 };  //  == pin 4, 5, 6, 7
  //  minor optimization only for pins = 4,5,6,7
  bool      _pin4567 = true;


  uint8_t   _backLightPin   = 8;
  uint8_t   _backLightPol   = 1;
  uint8_t   _backLight      = 1;

  uint8_t   _cols = 20;
  uint8_t   _rows = 4;

  //  DISPLAYCONTROL bit always on, set in constructor.
  uint8_t   _displayControl = 0;

  //  overflow protection
  uint8_t   _pos = 0;

  uint32_t  _count = 0;
};


//  -- END OF FILE --

