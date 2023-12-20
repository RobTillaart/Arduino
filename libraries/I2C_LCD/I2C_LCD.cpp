//
//    FILE: I2C_LCD.cpp
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.1
//    DATE: 2023-12-16
// PUPROSE: Arduino library for I2C_LCD
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"


//  keep defines compatible / recognizable
//  the zero valued defines are not used.
#define I2C_LCD_CLEARDISPLAY        0x01
#define I2C_LCD_RETURNHOME          0x02
#define I2C_LCD_ENTRYMODESET        0x04
#define I2C_LCD_DISPLAYCONTROL      0x08
#define I2C_LCD_CURSORSHIFT         0x10
#define I2C_LCD_FUNCTIONSET         0x20
#define I2C_LCD_SETCGRAMADDR        0x40
#define I2C_LCD_SETDDRAMADDR        0x80

#define I2C_LCD_ENTRYLEFT           0x02
#define I2C_LCD_ENTRYSHIFTINCREMENT 0x01

#define I2C_LCD_DISPLAYON           0x04
#define I2C_LCD_CURSORON            0x02
#define I2C_LCD_BLINKON             0x01

#define I2C_LCD_DISPLAYMOVE         0x08
#define I2C_LCD_MOVERIGHT           0x04

#define I2C_LCD_8BITMODE            0x10
#define I2C_LCD_2LINE               0x08
#define I2C_LCD_5x10DOTS            0x04


I2C_LCD::I2C_LCD(uint8_t address, TwoWire * wire)
{
  _address = address;
  _wire = wire;
  _displayControl = I2C_LCD_DISPLAYCONTROL;
}


void I2C_LCD::config (uint8_t address, uint8_t enable, uint8_t readWrite, uint8_t registerSelect,
                      uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7,
                      uint8_t backLight, uint8_t policy)  
{
  if (_address != address) return;  //  compatible?
  _enable         = ( 1 << enable);
  _readWrite      = ( 1 << readWrite);
  _registerSelect = ( 1 << registerSelect);
  _dataPin[0]     = ( 1 << data4);
  _dataPin[1]     = ( 1 << data5);
  _dataPin[2]     = ( 1 << data6);
  _dataPin[3]     = ( 1 << data7);
  _backLightPin   = ( 1 << backLight);
  _backLightPol   = policy;

  _pinsInOrder = ((data4 < data5) && (data5 < data6) && (data6 < data7));
}


void I2C_LCD::begin(uint8_t cols, uint8_t rows)
{
  _cols = cols;
  _rows = rows;

  //  ALL LOW.
  _wire->beginTransmission(_address);
  _wire->write(0x00);
  _wire->write(0x00);
  _wire->endTransmission();

  //  Figure 24 for procedure on 4-bit initialization
  //  wait for more than 15 ms
  delay(60);  //  TODO optimize

  //  Force 4 bit mode
  write4bits(0x03);
  delayMicroseconds(5000);  //  > 4.1 millis
  write4bits(0x03);
  delayMicroseconds(200);   //  > 100 usec
  write4bits(0x03);
  delayMicroseconds(200);   //  > 100 usec

  //  command to set 4 bit interface
  write4bits(0x02);
  delayMicroseconds(200);

  //  set "two" lines LCD - always a 20 x 4 for now.
  sendCommand(I2C_LCD_FUNCTIONSET | I2C_LCD_2LINE);
  //  default enable display
  display();
  clear();
}


bool I2C_LCD::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


/////////////////////////////////////////////////
//
//  BACKLIGHT
//
void I2C_LCD::setBacklightPin(uint8_t pin, uint8_t policy)
{
  _backLightPin = ( 1 << pin);
  _backLightPol = policy;
}


void I2C_LCD::setBacklight(bool on)
{
  _backLight = on;
  display();
}


/////////////////////////////////////////////////
//
//  DISPLAY
//
void I2C_LCD::display()
{
  _displayControl |= I2C_LCD_DISPLAYON;
  sendCommand(_displayControl);
}


void I2C_LCD::noDisplay()
{
  _displayControl &= ~I2C_LCD_DISPLAYON;
  sendCommand(_displayControl);
}


/////////////////////////////////////////////////
//
//  POSITIONING & CURSOR
//
void I2C_LCD::clear()
{
  sendCommand(I2C_LCD_CLEARDISPLAY);
  _pos = 0;
  delay(2);
}


void I2C_LCD::clearEOL()
{
  for (int i = _pos; i < _cols; i++)
  {
    print(' ');
  }
}


void I2C_LCD::home()
{
  sendCommand(I2C_LCD_RETURNHOME);
  _pos = 0;
  delay(2);
}


bool I2C_LCD::setCursor(uint8_t col, uint8_t row)
{
  static uint8_t startpos[4] = { 0x00, 0x40, 0x14, 0x54 };
  if ((col >= _cols) || (row >= _rows)) return false;
  sendCommand(I2C_LCD_SETDDRAMADDR | (startpos[row] + col) );
  _pos = col;
  return true;
}


void I2C_LCD::blink()
{
  _displayControl |= I2C_LCD_BLINKON;
  sendCommand(_displayControl);
}


void I2C_LCD::noBlink()
{
  _displayControl &= ~I2C_LCD_BLINKON;
  sendCommand(_displayControl);
}


void I2C_LCD::cursor()
{
  _displayControl |= I2C_LCD_CURSORON;
  sendCommand(_displayControl);
}
  

void I2C_LCD::noCursor()
{
  _displayControl &= ~I2C_LCD_CURSORON;
  sendCommand(_displayControl);
}


void I2C_LCD::scrollDisplayLeft(void) 
{
   sendCommand(I2C_LCD_CURSORSHIFT | I2C_LCD_DISPLAYMOVE);
}


void I2C_LCD::scrollDisplayRight(void) 
{
   sendCommand(I2C_LCD_CURSORSHIFT | I2C_LCD_DISPLAYMOVE | I2C_LCD_MOVERIGHT);
}


void I2C_LCD::moveCursorLeft(void)
{
   sendCommand(I2C_LCD_CURSORSHIFT);
   _pos--;
}


void I2C_LCD::moveCursorRight(void)
{
  sendCommand(I2C_LCD_CURSORSHIFT | I2C_LCD_MOVERIGHT);
  _pos++;
}


void I2C_LCD::autoscroll(void) 
{
  sendCommand(I2C_LCD_ENTRYMODESET | I2C_LCD_ENTRYSHIFTINCREMENT);
}


void I2C_LCD::noAutoscroll(void) 
{
  sendCommand(I2C_LCD_ENTRYMODESET);
}


void I2C_LCD::leftToRight(void) 
{
  sendCommand(I2C_LCD_ENTRYMODESET | I2C_LCD_ENTRYLEFT);
}


void I2C_LCD::rightToLeft(void) 
{
  sendCommand(I2C_LCD_ENTRYMODESET);
}


/////////////////////////////////////////////////
//
//  CHARMAP
//
void I2C_LCD::createChar(uint8_t index, uint8_t * charmap)
{
  sendCommand(I2C_LCD_SETCGRAMADDR | ((index & 0x07) << 3));
  uint8_t tmp = _pos;
  for (uint8_t i = 0; i < 8; i++)
  {
    _pos = 0;
    write(charmap[i]);
  }
  _pos = tmp;
}


//////////////////////////////////////////////////////////
//
//  PRIVATE
//
size_t I2C_LCD::write(uint8_t c)
{
  size_t n = 0;
  if (c == (uint8_t)'\t')  //  TAB char
  {
    while (_pos % 4 != 0)
    {
      moveCursorRight();  //  increases _pos.
      n++;
    }
    return n;
  }
  if (_pos < _cols)   //  overflow protect
  {
    sendData(c);
    _pos++;
    n++;
    return n;
  }
  //  else blink backlight to indicate error?
  return n;
};



//  TODO merge these two
//  optimize 95% identical.

//  TODO merge these two
//  optimize 95% identical.
void I2C_LCD::sendCommand(uint8_t value)
{
  uint8_t MSN = 0;
  if (_backLight)  MSN |= _backLightPin;
  uint8_t LSN = MSN;

  //  pins are in the right order optimization.
  if (_pinsInOrder)
  {
    MSN |= value & 0xF0;
    LSN |= value << 4;
  }
  else
  {
    uint8_t tmp = value >> 4;
    for ( uint8_t i = 0; i < 4; i++ )
    {
      if ( tmp & 0x01 ) MSN |= _dataPin[i];
      tmp >>= 1;
    }
    tmp = value & 0x0F;
    for ( uint8_t i = 0; i < 4; i++ )
    {
      if ( tmp & 0x01 ) LSN |= _dataPin[i];
      tmp >>= 1;
    }
  }

  _wire->beginTransmission(_address);
  _wire->write(MSN | _enable);
  _wire->write(MSN);
  _wire->write(LSN | _enable);
  _wire->write(LSN);
  _wire->endTransmission();
  delayMicroseconds(40);
}


void I2C_LCD::sendData(uint8_t value)
{
  uint8_t MSN = _registerSelect;
  if (_backLight) MSN |= _backLightPin;
  uint8_t LSN = MSN;

  //  if pins are in the right order speed up.
  if (_pinsInOrder)
  {
    MSN |= value & 0xF0;
    LSN |= value << 4;
  }
  else
  {
    uint8_t tmp = value >> 4;
    for ( uint8_t i = 0; i < 4; i++ )
    {
      if ( tmp & 0x01 ) MSN |= _dataPin[i];
      tmp >>= 1;
    }
    tmp = value & 0x0F;
    for ( uint8_t i = 0; i < 4; i++ )
    {
      if ( tmp & 0x01 ) LSN |= _dataPin[i];
      tmp >>= 1;
    }
  }

  _wire->beginTransmission(_address);
  _wire->write(MSN | _enable);
  _wire->write(MSN);
  _wire->write(LSN | _enable);
  _wire->write(LSN);
  _wire->endTransmission();
  delayMicroseconds(40);
}



//  really needed for setup
void I2C_LCD::write4bits(uint8_t value) 
{
  uint8_t cmd = _backLight;

  for ( uint8_t i = 0; i < 4; i++ )
  {
    if ( value & 0x01 ) cmd |= _dataPin[i];
    value >>= 1;
  }
  
  _wire->beginTransmission(_address);
  _wire->write(cmd | _enable);
  _wire->endTransmission();
  _wire->beginTransmission(_address);
  _wire->write(cmd);
  _wire->endTransmission();
}


//  -- END OF FILE --

