//
//    FILE: I2C_LCD.cpp
//  AUTHOR: Rob.Tillaart
// VERSION: 0.2.5
//    DATE: 2023-12-16
// PURPOSE: Arduino library for I2C_LCD
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"

//  40 us is a save value at any speed.
//  20 us is a save value for I2C at 400K.
const uint8_t I2C_LCD_CHAR_DELAY = 0;

//  possible fix for #15
//  comment this line if data get garbled after several seconds.
//  might work, or not.
#define I2C_LCD_FAST_SEND          1


///////////////////////////////////////////////////////
//
//  DO NOT CHANGE BELOW THIS LINE
//
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


int I2C_LCD::config (uint8_t address, uint8_t enable, uint8_t readWrite, uint8_t registerSelect,
                      uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7,
                      uint8_t backLight, uint8_t polarity)
{
  if (_address != address)
  {
    _error = I2C_LCD_ERR_ADDRESS;
    return _error;
  }
  _enable         = ( 1 << enable);
  _readWrite      = ( 1 << readWrite);
  _registerSelect = ( 1 << registerSelect);
  _dataPin[0]     = ( 1 << data4);
  _dataPin[1]     = ( 1 << data5);
  _dataPin[2]     = ( 1 << data6);
  _dataPin[3]     = ( 1 << data7);
  _backLightPin   = ( 1 << backLight);
  _backLightPol   = polarity;

  _pin4567 = ((data4 == 4) && (data5 == 5) && (data6 == 6) && (data7 == 7));
  //  if pins are 0,1,2,3 they are also in order
  //  but the shift/mask in send() should be different
  //  4,5,6,7 is most used (assumption).
  return I2C_LCD_OK;
}


bool I2C_LCD::begin(uint8_t columns, uint8_t rows)
{
  //  no check for range, user responsibility, defaults are 20x4
  _columns = columns;
  _rows = rows;

  if (isConnected() == false) 
  {
    //  _error is set in siConnected()
    return false;
  }

  //  ALL LINES LOW.
  _wire->beginTransmission(_address);
  _wire->write(0x00);
  _error = _wire->endTransmission();

  //  Figure 24 for procedure on 4-bit initialization
  //  wait for more than 15 ms
  //  if other objects initialize earlier there will be less blocking time.
  //  => assumes display is started at same time as MCU
  while (millis() < 100) delay(1);

  //  Force 4 bit mode, see datasheet.
  //  times are taken longer for robustness.
  //  note this is typically only called once.
  write4bits(0x03);
  delayMicroseconds(5000);  //  datasheet > 4.1 milliseconds
  write4bits(0x03);
  delayMicroseconds(200);   //  datasheet > 100 microseconds
  write4bits(0x03);
  delayMicroseconds(200);   //  datasheet > 100 microseconds

  //  command to set 4 bit interface
  write4bits(0x02);
  delayMicroseconds(200);

  //  set "two" lines LCD - fixed for now.
  sendCommand(I2C_LCD_FUNCTIONSET | I2C_LCD_2LINE);
  //  default enable display
  display();
  clear();
  //  not tested error after every call except the last.
  return (_error == I2C_LCD_OK);
}


bool I2C_LCD::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == I2C_LCD_OK);
}


/////////////////////////////////////////////////
//
//  BACKLIGHT
//
void I2C_LCD::setBacklightPin(uint8_t pin, uint8_t polarity)
{
  _backLightPin = (1 << pin);
  _backLightPol = polarity;
}


void I2C_LCD::setBacklight(bool on)
{
  _backLight = (on == _backLightPol);
  if (_backLight) display();
  else noDisplay();
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
  _position = 0;
  _row = 0;
  delay(2);
}


void I2C_LCD::clearEOL()
{
  while(_position  < _columns)
  {
    print(' ');
  }
}


void I2C_LCD::home()
{
  sendCommand(I2C_LCD_RETURNHOME);
  _position = 0;
  _row = 0;
  delayMicroseconds(1600);  //  datasheet states 1520.
}


bool I2C_LCD::setCursor(uint8_t column, uint8_t row)
{
  if ((column >= _columns) || (row >= _rows))
  {
    _error = I2C_LCD_ERR_COLUMN_ROW;
    return false;
  }

  //  more efficient address / offset calculation (no lookup so far).
  uint8_t offset = 0x00;
  if (row & 0x01) offset += 0x40;
  if (row & 0x02) offset += _columns;
  offset += column;
  _position = column;
  _row = row;

  sendCommand(I2C_LCD_SETDDRAMADDR | offset );
  return true;

  //  ORIGINAL SETCURSOR CODE
  //  all start position arrays start with 0x00 0x40
  //  they have an offset of 0x14, 0x10 or 0x0A
  //  so only 3 bytes are needed?
  //  note that e.g. 16x2 only uses the first 2 offsets.
  // uint8_t startPos[4]  = { 0x00, 0x40, 0x14, 0x54 };  //  most displays
  // uint8_t start16x4[4] = { 0x00, 0x40, 0x10, 0x50 };  //  16x4 display
  // uint8_t start10x4[4] = { 0x00, 0x40, 0x0A, 0x4A };  //  10x4 LOGO display

  // //  if out of range exit!
  // if ((column >= _columns) || (row >= _rows)) return false;

  // _position = column;
  // if ((_rows == 4) && (_columns == 16))
  // {
    // sendCommand(I2C_LCD_SETDDRAMADDR | (start16x4[row] + col) );
    // return true;
  // }
  // if ((_rows == 4) && (_columns == 10))
  // {
    // sendCommand(I2C_LCD_SETDDRAMADDR | (start10x4[row] + col) );
    // return true;
  // }
  // sendCommand(I2C_LCD_SETDDRAMADDR | (startPos[row] + col) );
  // return true;
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


void I2C_LCD::moveCursorLeft(uint8_t n)
{
  while ((_position > 0) && (n--))
  {
    sendCommand(I2C_LCD_CURSORSHIFT);
    _position--;
  }
}


void I2C_LCD::moveCursorRight(uint8_t n)
{
  while ((_position < _columns) && (n--))
  {
    sendCommand(I2C_LCD_CURSORSHIFT | I2C_LCD_MOVERIGHT);
    _position++;
  }
}


void I2C_LCD::moveCursorUp()
{
  if (_row > 0)
  {
    setCursor(_position, _row - 1);
  }
}


void I2C_LCD::moveCursorDown()
{
  if (_row < _rows -1)
  {
    setCursor(_position, _row + 1);
  }
}


void I2C_LCD::autoScroll(void)
{
  sendCommand(I2C_LCD_ENTRYMODESET | I2C_LCD_ENTRYSHIFTINCREMENT);
}


void I2C_LCD::noAutoScroll(void)
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
  //  index should be < 8 ERROR?
  sendCommand(I2C_LCD_SETCGRAMADDR | ((index & 0x07) << 3));
  uint8_t previousPosition = _position;
  for (uint8_t i = 0; i < 8; i++)
  {
    _position = 0;
    sendData(charmap[i]);
  }
  _position = previousPosition;
}


size_t I2C_LCD::write(uint8_t c)
{
  size_t n = 0;
  //  handle TAB char(9) - next multiple of 4 (or EndOfLine)
  if (c == (uint8_t)'\t')
  {
    while (((_position % 4) != 0) && (_position < _columns))
    {
      moveCursorRight();   //  increases _position.
      n++;
    }
    return n;
  }

  //  experimental
  //  SPECIAL ASCII CHAR SUPPORT
  //  char(7) == BELL not possible (7 = special character)
  //  char(11) == VERTICAL TAB => next line same position  (NEED COL)

  //  handle BACKSPACE char(8) - one position to the left.
  if (c == (uint8_t)'\b')
  {
    if (_position > 0)
    {
      moveCursorLeft();  //  decreases _position.
      n++;
    }
    return n;
  }

  //  handle NEWLINE char(10) - start of next line.
  if (c == (uint8_t)'\n')
  {
    if (_row < (_rows - 1))
    {
      setCursor(0, _row + 1);
      n++;
    }
    return n;
  }

  //  handle VERTICAL TAB char(11)
  if (c == (uint8_t)'\v')
  {
    if (_row < (_rows - 1))
    {
      setCursor(_position, _row + 1);
      n++;
    }
    return n;
  }

  //  handle FORMFEED char(12) - clear screen.
  if (c == (uint8_t)'\f')
  {
    clear();
    return n;
  }

  //  handle RETURN char(13) - start of current line.
  if (c == (uint8_t)'\r')
  {
    while (_position > 0)
    {
      moveCursorLeft();    //  decreases _position.
      n++;
    }
    return n;
  }

  //  PREP.
  //  handle SO char(14)
  // if (c == 14)
  // {
    // return 0;
  // }
  //  handle SI char(15)
  // if (c == 15)
  // {
    // return 0;
  // }

  //  DEFAULT
  //  handle normal characters.
  if (_position < _columns)   //  overflow protect.
  {
    sendData(c);
    _position++;
    return 1;
  }
  //  not allowed to print beyond display,
  //  prevents garbage, so return 0.
  return 0;
}


size_t I2C_LCD::center(uint8_t row, const char * message)
{
  uint8_t length = strlen(message) + 1;
  setCursor((_columns - length) / 2, row);
  return print(message);
}


size_t I2C_LCD::right(uint8_t col, uint8_t row, const char * message)
{
  uint8_t len = strlen(message);
  setCursor(col - len, row);
  return print(message);
}


size_t I2C_LCD::repeat(uint8_t c, uint8_t times)
{
  size_t n = 0;
  while((times--) && (_position < _columns))
  {
    n += write(c);
  }
  return n;
}


int I2C_LCD::getLastError()
{
  int e = _error;
  _error = I2C_LCD_OK;
  return e;
}


//////////////////////////////////////////////////////////
//
//  PRIVATE
//
void I2C_LCD::sendCommand(uint8_t value)
{
  send(value, false);
}


void I2C_LCD::sendData(uint8_t value)
{
  send(value, true);
}


void I2C_LCD::send(uint8_t value, bool dataFlag)
{
  //  calculate both
  //  MSN == most significant nibble and
  //  LSN == least significant nibble
  uint8_t MSN = 0;
  if (dataFlag)   MSN = _registerSelect;
  if (_backLight) MSN |= _backLightPin;
  uint8_t LSN = MSN;

  if (_pin4567)  //  4,5,6,7 only == most used.
  {
    MSN |= value & 0xF0;
    LSN |= value << 4;
  }
  else  //  ~ 1.7% slower UNO.  (adds 4 us / char)
  {
    for ( uint8_t i = 0; i < 4; i++ )
    {
      if ( value & 0x01 ) LSN |= _dataPin[i];
      if ( value & 0x10 ) MSN |= _dataPin[i];
      value >>= 1;
    }
  }

#ifdef I2C_LCD_FAST_SEND
  //  send two nibbles in one call
  _wire->beginTransmission(_address);
  _wire->write(MSN | _enable);
  _wire->write(MSN);
  _wire->write(LSN | _enable);
  _wire->write(LSN);
  _error = _wire->endTransmission();
#else
  //  send two nibbles in two calls.
  _wire->beginTransmission(_address);
  _wire->write(MSN | _enable);
  _wire->write(MSN);
  _error = _wire->endTransmission();

  delayMicroseconds(10);

  _wire->beginTransmission(_address);
  _wire->write(LSN | _enable);
  _wire->write(LSN);
  _error = _wire->endTransmission();
#endif

  if (I2C_LCD_CHAR_DELAY) delayMicroseconds(I2C_LCD_CHAR_DELAY);
}


//  needed for setup
void I2C_LCD::write4bits(uint8_t value)
{
  uint8_t cmd = 0;

  for ( uint8_t i = 0; i < 4; i++ )
  {
    if ( value & 0x01 ) cmd |= _dataPin[i];
    value >>= 1;
  }

  _wire->beginTransmission(_address);
  _wire->write(cmd | _enable);
  _error = _wire->endTransmission();
  //  check _error?
  _wire->beginTransmission(_address);
  _wire->write(cmd);
  _error = _wire->endTransmission();
}


//  -- END OF FILE --

