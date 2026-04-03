//
//    FILE: markDownWriter.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-02
// VERSION: 0.1.0
// PURPOSE: Arduino library for creating simple mark down content.
//     URL: https://github.com/RobTillaart/markDownWriter



#include "markDownWriter.h"


markDownWriter::markDownWriter(Print* stream, uint8_t bufferSize)
{
  _bufferSize = constrain(bufferSize, 2, 250);
  _buffer = (char *) malloc(_bufferSize);
  _stream = stream;
  reset();
}

markDownWriter::~markDownWriter()
{
  if (_buffer != NULL) free(_buffer);
}

void markDownWriter::reset()
{
  _bufferIndex = 0;
  _bytesOut = 0;
}


////////////////////////////////////////////////////////////////////
//
// HEADERS
//
void markDownWriter::header(uint8_t level, const char * text)
{
  println();
  for (int i = 0; i < level; i++) print('#');
  print(' ');
  println(text);
  println();
}


////////////////////////////////////////////////////////////////////
//
// TABLES
//
void markDownWriter::tableHeader(uint8_t size, const char headers[][12], const char * align)
{
  _tableSize = size;
  //  headers
  println();
  for (int i = 0; i < _tableSize; i++)
  {
    print("| ");
    print(headers[i]);
    print(" ");
  }
  println("|");
  // alignments
  for (int i = 0; i < _tableSize; i++)
  {
    char c = toupper(align[i]);
    if (c == 'L')      print("|:-------");
    else if (c == 'R') print("|-------:");
    else               print("|:------:");  //  default.
  }
  println("|");
}

void markDownWriter::tableValues(float values[], uint8_t decimals)
{
  print("| ");
  for (int i = 0; i < _tableSize; i++)
  {
    print(values[i], decimals);
    print(" | ");
  }
  println();
}

void markDownWriter::tableRowStart()
{
  print("| ");
};

void markDownWriter::tableRowValue(const char * text)
{
  print(text);
  print(" | ");
}

void markDownWriter::tableRowValue(float value, uint8_t decimals)
{
  print(value, decimals);
  print(" | ");
}

void markDownWriter::tableRowValue(uint32_t value)
{
  print(value);
  print(" | ");
}

void markDownWriter::tableRowValue(int32_t value)
{
  print(value);
  print(" | ");
}

void markDownWriter::tableRowEnd()
{
  println();
}


////////////////////////////////////////////////////////////////////
//
//  LINKS
//
void markDownWriter::URL(const char * text, const char * link)
{
  print("[");
  print(text);
  print("](");
  print(link);
  print(")");
}

void markDownWriter::image(const char * text, const char * link)
{
  print("![");
  print(text);
  print("](");
  print(link);
  print(")");
}

void markDownWriter::link(const char * link)
{
  print("<");
  print(link);
  print(">");
}


////////////////////////////////////////////////////////////////////
//
//  PRINT INTERFACE override
//
void markDownWriter::flush()
{
  _bytesOut += _bufferIndex;
  if (_bufferIndex > 0)
  {
    _buffer[_bufferIndex] = 0;
    _stream->write(_buffer, _bufferIndex);  //  saves ~40 bytes on UNO.
    //  _stream->print(_buffer);
    _bufferIndex = 0;
  }
}



///////////////////////////////////////////////
//
//  PRIVATE
//
size_t markDownWriter::write(uint8_t c)
{
  _buffer[_bufferIndex++] = c;
  if (_bufferIndex == (_bufferSize - 1))
  {
    flush();
  }
  return 1;
}


//  -- END OF FILE --

