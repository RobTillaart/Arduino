//
//    FILE: I2C_LCD.cpp
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.0
//    DATE: 2023-12-16
// PUPROSE: Arduino library for I2C_LCD
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"


//  TODO redo simplify names shorter 
//       or keep them compatible?
#define I2C_LCD_CLEARDISPLAY        0x01
#define I2C_LCD_RETURNHOME          0x02
#define I2C_LCD_ENTRYMODESET        0x04
#define I2C_LCD_DISPLAYCONTROL      0x08
#define I2C_LCD_CURSORSHIFT         0x10
#define I2C_LCD_FUNCTIONSET         0x20
#define I2C_LCD_SETCGRAMADDR        0x40
#define I2C_LCD_SETDDRAMADDR        0x80

#define I2C_LCD_ENTRYRIGHT          0x00
#define I2C_LCD_ENTRYLEFT           0x02
#define I2C_LCD_ENTRYSHIFTINCREMENT 0x01
#define I2C_LCD_ENTRYSHIFTDECREMENT 0x00

#define I2C_LCD_DISPLAYON           0x04
#define I2C_LCD_DISPLAYOFF          0x00
#define I2C_LCD_CURSORON            0x02
#define I2C_LCD_CURSOROFF           0x00
#define I2C_LCD_BLINKON             0x01
#define I2C_LCD_BLINKOFF            0x00

#define I2C_LCD_DISPLAYMOVE         0x08
#define I2C_LCD_CURSORMOVE          0x00
#define I2C_LCD_MOVERIGHT           0x04
#define I2C_LCD_MOVELEFT            0x00

#define I2C_LCD_8BITMODE            0x10
#define I2C_LCD_4BITMODE            0x00
#define I2C_LCD_2LINE               0x08
#define I2C_LCD_1LINE               0x00
#define I2C_LCD_5x10DOTS            0x04
#define I2C_LCD_5x8DOTS             0x00


I2C_LCD::I2C_LCD(uint8_t address, TwoWire * wire)
{
  _address = address;
  _wire = wire;
}


void I2C_LCD::config (uint8_t address, uint8_t enable, uint8_t readwrite, uint8_t registerselect, 
                      uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7, 
                      uint8_t backlight)  
{
  if (_address != address) return;  //  compatible
  _enable         = ( 1 << enable);
  _readWrite      = ( 1 << readwrite);
  _registerSelect = ( 1 << registerselect);
  _dataPin[0]     = ( 1 << data4);
  _dataPin[1]     = ( 1 << data5);
  _dataPin[2]     = ( 1 << data6);
  _dataPin[3]     = ( 1 << data7);
  _backLight      = ( 1 << backlight);

  _pinsInOrder = ((data4 < data5) && (data5 < data6) && (data6 < data7));
}


void I2C_LCD::begin(uint8_t cols, uint8_t rows)
{
  _cols = cols;
  _rows = rows;

  //  ALL LOW.
  _wire->beginTransmission(_address);
  _wire->write(0x00);
  _wire->endTransmission();

  //  wait for 50 ms
  delay(50);

  //  Force 4 bit mode  //  todo timing...
  write4bits(0x03);
  delay(5);
  write4bits(0x03);
  delay(1);
  write4bits(0x03);
  delay(1);
  write4bits(0x02);
  delay(1);

  //  set "two" lines LCD - always a 20 x 4 for now.
  sendCommand(I2C_LCD_FUNCTIONSET | I2C_LCD_2LINE);
}


void I2C_LCD::setBacklight(bool on)
{
  if (on) display();   //  todo fix for real.
  else noDisplay();
}


void I2C_LCD::display()
{
  sendCommand(I2C_LCD_DISPLAYCONTROL | I2C_LCD_DISPLAYON );
}


void I2C_LCD::noDisplay()
{
  sendCommand(I2C_LCD_DISPLAYCONTROL | I2C_LCD_DISPLAYOFF);
}


void I2C_LCD::clear()
{
  sendCommand(I2C_LCD_CLEARDISPLAY);
  delay(2);
}


void I2C_LCD::home()
{
  sendCommand(I2C_LCD_RETURNHOME);
  delay(2);
}


void I2C_LCD::setCursor(uint8_t col, uint8_t row)
{
  uint8_t startpos[4] = { 0x00, 0x40, 0x14, 0x54 };
  sendCommand(I2C_LCD_SETDDRAMADDR | (startpos[row] + col) );
}
  

size_t I2C_LCD::write(uint8_t c)
{
  sendData(c);  //  add timestamp..
  return 1;
};


//////////////////////////////////////////////////////////
//
//  PRIVATE
//

//  TODO merge these two
//  optimize 95% identical.
void I2C_LCD::sendCommand(uint8_t value)
{
  uint8_t MSN = _backLight;
  uint8_t LSN = MSN;

  //  pins are in the right order.
  //  TODO determine a flag and 
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
}


void I2C_LCD::sendData(uint8_t value)
{
  uint8_t MSN = _registerSelect | _backLight;
  uint8_t LSN = MSN;

  //  if pins are in the right order speed up.
  //  todo determine a flag in config.
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
  // _wire->endTransmission();
  // _wire->beginTransmission(_address);
  _wire->write(cmd);
  _wire->endTransmission();
}


//  -- END OF FILE --

