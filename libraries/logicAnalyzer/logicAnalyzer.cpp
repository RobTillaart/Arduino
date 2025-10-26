//
//    FILE: logicAnalyzer.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-10-20
// VERSION: 0.1.0
// PURPOSE: Arduino library for building a logicAnalyzer. (non performant).
//     URL: https://github.com/RobTillaart/logicAnalyzer



#include "logicAnalyzer.h"


//  could be configurable.
const int PULSE_HEIGHT = 16;
const int BASE_STEP = PULSE_HEIGHT * 2;


logicAnalyzer::logicAnalyzer(Stream * str)
{
  _stream = str;
  _count = 0;
}

bool logicAnalyzer::configPins(uint8_t pins[], uint8_t size)
{
  if (size > LA_MAX_CHANNEL) return false;
  if (size == 0) return false;

  _channels = _size = size;
  for (int i = 0 ; i < _size; i++)
  {
    pinMode(pins[i], INPUT);
    _dataPins[i] = pins[i];
  }
  return true;
}

bool logicAnalyzer::configClock(uint8_t clockPin)
{
  pinMode(clockPin, INPUT);
  _clockPin = clockPin;
  return true;
}

bool logicAnalyzer::setChannels(uint8_t channels)
{
  if (channels > LA_MAX_CHANNEL) return false;
  if (channels == 0) return false;
  _channels = channels;
  return true;
}

uint8_t logicAnalyzer::getChannels()
{
  return _channels;
}


///////////////////////////////////////
//
//  CLOCK
//
bool logicAnalyzer::clockChanged()
{
  uint8_t clk = _read(_clockPin);
  bool b = (_lastClock != clk);
  _lastClock = clk;
  return b;
}

bool logicAnalyzer::clockFalling()
{
  uint8_t clk = _read(_clockPin);
  bool b = ((_lastClock == HIGH) and (clk == LOW));
  _lastClock = clk;
  return b;
}

bool logicAnalyzer::clockRising()
{
  uint8_t clk = _read(_clockPin);
  bool b = ((_lastClock == LOW) and (clk == HIGH));
  _lastClock = clk;
  return b;
}

bool logicAnalyzer::clockHIGH()
{
  uint8_t clk = _read(_clockPin);
  _lastClock = clk;
  return clk == HIGH;
}

bool logicAnalyzer::clockLOW()
{
  uint8_t clk = _read(_clockPin);
  _lastClock = clk;
  return clk == LOW;
}


///////////////////////////////////////
//
//  SAMPLE and PLOT
//

// uint32_t logicAnalyzer::samplePlot()  //  all in one.
// {
  // _count++;
  // uint16_t base = 0;
  // for (int i = 0 ; i < _channels; i++)
  // {
    // _data = _read(_dataPins[i]);
    // _stream->print((_data & 1) ? base + PULSE_HEIGHT : base);
    // _stream->print('\t');
    // base += BASE_STEP;
  // }
  // _stream->print('\n');
  // return _data;
// }


uint32_t logicAnalyzer::sample()
{
  _count++;
  _data = 0;
  for (int i = 0 ; i < _size; i++)
  {
    _data <<= 1;
    _data |= _read(_dataPins[i]);
  }
  return _data;
}

void logicAnalyzer::inject(uint32_t data)
{
  _count++;
  _data = data;
}

void logicAnalyzer::plot()
{
  uint32_t mask = 1UL << (_channels - 1);
  uint32_t base = 0;
  while (mask)
  {
    _stream->print((_data & mask) ? base + PULSE_HEIGHT : base);
    _stream->print('\t');
    mask >>= 1;
    base += BASE_STEP;
  }
  _stream->print('\n');
}


void logicAnalyzer::plotRaw()
{
  uint32_t mask = 1 << (_channels - 1);
  while (mask)
  {
    _stream->print((_data & mask) > 0);
    _stream->print('\t');
    mask >>= 1;
  }
  _stream->print('\n');
}


///////////////////////////////////////
//
//  COUNT
//
uint32_t logicAnalyzer::getCount()
{
  return _count;
}

void logicAnalyzer::setCount(uint32_t count)
{
  _count = count;
}



///////////////////////////////////////
//
//  PRIVATE
//



//  -- END OF FILE --

