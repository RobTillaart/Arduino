//
//    FILE: ParallelPrinter.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.6
// PURPOSE: parallel printer class that implements the Print interface
//    DATE: 2013-09-30
//     URL: https://github.com/RobTillaart/ParallelPrinter



#include "ParallelPrinter.h"


ParallelPrinter::ParallelPrinter()
{
  uint8_t dataPins[] = {3, 4, 5, 6, 7, 8, 9, 10};
  ParallelPrinter(13, 2, 12, dataPins );
}


ParallelPrinter::ParallelPrinter(uint8_t STROBE, uint8_t BUSY, uint8_t OOP, uint8_t * p )
{
  //  CONTROL LINES
  _strobePin = STROBE;
  _busyPin = BUSY;
  _oopPin = OOP;
  pinMode(_oopPin, INPUT);
  pinMode(_busyPin, INPUT);
  pinMode(_strobePin, OUTPUT);

  //  DATA LINES
  for (uint8_t i = 0; i < 8; i++)
  {
    _pin[i] = p[i];
    pinMode(_pin[i], OUTPUT);
  }
  setLineLength(80);
  setPageLength(60);
  reset();
}


void ParallelPrinter::begin(uint8_t lineLength, uint8_t pageLength)
{
  setLineLength(lineLength);
  setPageLength(pageLength);
  reset();
}


void ParallelPrinter::reset()
{
  _pos             = 0;
  _lineNr          = 0;
  _pageNr          = 0;
  _tabSize         = 2;
  _lineFeed        = 1;
  _strobeDelay     = 2000;
  _printLineNumber = false;
}


//  write() implements the virtual write of the Print class
size_t ParallelPrinter::write(uint8_t c)
{
  if (c == '\t')  //  TAB
  {
    uint8_t spaces = _tabSize - _pos % _tabSize;
    for (uint8_t i = 0; i < spaces; i++) processSingleChar(' ');
    return spaces;
  }
  if (c == '\n')  //  LINEFEED
  {
    for (uint8_t i = 0; i < _lineFeed; i++)
    {
      processSingleChar(c);
      _pos = 0;
      _lineNr++;
    }
    return _lineFeed;
  }
  processSingleChar(c);
  return 1;
}


void ParallelPrinter::processSingleChar(uint8_t c)
{
  _pos++;
  if ((_pos == 1) && _printLineNumber)
  {
    //  not nice - implicit recursion...
    print(_lineNr);
    print('\t');
  }
  if (c == FORMFEED)
  {
    sendByte(c);
    sendByte('\n');
    _pos = 0;
    _lineNr = 0;
    _pageNr++;
  }
  else
  {
    sendByte(c);
  }

  //  HANDLE FULL LINE
  if (_pos > _lineLength)
  {
    _pos = 0;
    for (uint8_t i = 0; i < _lineFeed; i++)
    {
      sendByte('\n');
      _lineNr++;
    }
  }
  //  HANDLE FULL PAGE
  if (_lineNr > _pageLength)
  {
    sendByte(FORMFEED);
    sendByte('\n');
    _pos = 0;
    _lineNr = 0;
    _lineNr = 0;
    _pageNr++;
  }

}


//  lowest level communication
void ParallelPrinter::sendByte(uint8_t c)
{
  //  BLOCK WHEN OUT OF PAPER    TODO
  //  while (digitalRead(_oopPin) == LOW) yield();
  //  indication in hardware?

  Serial.write(c);  //  debugging
  return;


  //  wait until printer is ready.
  while (digitalRead(_busyPin) == HIGH) yield();

  uint8_t mask = 0x80;
  for (uint8_t i = 0; i < 8; i++)
  {
    digitalWrite(_pin[i], c & mask );
    mask >>= 1;
  }
  digitalWrite(_strobePin, LOW);
  //  time consuming part
  if (_strobeDelay) delayMicroseconds(_strobeDelay);
  digitalWrite(_strobePin, HIGH);

  //  wait till data is read by printer.
  while (digitalRead(_busyPin) == LOW) yield();
}


//  -- END OF FILE --

